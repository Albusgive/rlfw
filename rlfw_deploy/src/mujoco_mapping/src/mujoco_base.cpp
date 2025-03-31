#include "mujoco_base.h"
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <mujoco/mjspec.h>
#include <mujoco/mujoco.h>
#include <mutex>
#include <string>
#include <vector>
mujoco_base::mujoco_base(std::string model_file) {
  // load and compile model
  char error[1000] = "Could not load binary model";
  if (model_file.size() > 4 &&
      model_file.compare(model_file.size() - 4, 4, ".mjb") == 0) {
    m = mj_loadModel(model_file.c_str(), 0);
  } else {
    m = mj_loadXML(model_file.c_str(), 0, error, 1000);
  }
  if (!m) {
    mju_error("Load model error: %s", error);
  }
  mocap_m = m;
  // make data
  d = mj_makeData(m);
  for (int i = 0; i < m->njnt; i++) {
    const char *joint_name = mj_id2name(m, mjOBJ_JOINT, i);
    if (!joint_name)
      continue;
    std::string name(joint_name);
    int joint_id = mj_name2id(m, mjOBJ_JOINT, name.c_str());
    if (joint_id == -1)
      continue;
    int qpos_addr = m->jnt_qposadr[joint_id];
    joint_pos_idx[name] = qpos_addr;
    joint_names.push_back(name);
    last_joint_pos.push_back(0.0);
  }
  for (int i = 0; i < m->nu; i++) {
    const char *actuator_name = mj_id2name(m, mjOBJ_ACTUATOR, i);
    if (!actuator_name)
      continue;
    std::string name(actuator_name);
    int actuator_id = mj_name2id(m, mjOBJ_ACTUATOR, name.c_str());
    if (actuator_id == -1)
      continue;
    joint_action_idx[name] = actuator_id;
    joint_action_idx[name + "_mapping"] = actuator_id;
  }
  for (int i = 0; i < m->nsensor; i++) {
    const char *sensor_name = mj_id2name(m, mjOBJ_SENSOR, i);
    switch (m->sensor_type[i]) {
    case mjSENS_ACCELEROMETER: {
      acc_name = sensor_name;
      break;
    }
    case mjSENS_GYRO: {
      ang_vel_name = sensor_name;
      break;
    }
    case mjSENS_FRAMEQUAT: {
      orientation_name = sensor_name;
      break;
    }
    }
  }
  // 构建动捕模型
  buildLocModel(model_file);
}

mujoco_base::~mujoco_base() {
  destroyRender();
  // free MuJoCo model and data
  mj_deleteData(d);
  mj_deleteModel(m);
  glfwTerminate(); // 终止 GLFW
}

void mujoco_base::buildLocModel(std::string file) {
  mjSpec *spec = mj_parseXML(file.c_str(), NULL, NULL, 0);
  mjsBody *robot = mjs_findBody(spec, "B");
  robot->mocap = 0;
  mjs_addFreeJoint(robot);
  loc_m = mj_compile(spec, NULL);
}

void mujoco_base::load_model(mjModel *m) {
  this->m = new mjModel(*m);
  d = mj_makeData(this->m);
  mj_step(m, d);
}

mjModel *mujoco_base::load_model(std::string model_file) {
  mjModel *m = nullptr;
  char error[1000] = "Could not load binary model";
  if (model_file.size() > 4 &&
      model_file.compare(model_file.size() - 4, 4, ".mjb") == 0) {
    m = mj_loadModel(model_file.c_str(), 0);
  } else {
    m = mj_loadXML(model_file.c_str(), 0, error, 1000);
  }
  if (!m) {
    mju_error("Load model error: %s", error);
  }
  return m;
}

void mujoco_base::step(std::vector<float> action) {
  std::lock_guard<std::mutex> lk(m_mtx);
  mjtNum simstart = d->time;
  // ctrl
  for (int i = 0; i < static_cast<int>(action.size()); i++) {
    d->ctrl[i] = action[i];
  }
  // step
  while (d->time - simstart < m->opt.timestep) {
    mj_step(m, d);
  }
}

void mujoco_base::reset() {
  std::lock_guard<std::mutex> lock(m_mtx);
  mj_resetData(m, d);
}

void mujoco_base::render() {
  if (is_show.load())
    return;
  is_show.store(true);
  render_thread = std::thread([this]() {
    initRender(1200, 900, "mujoco_mapping");
    while (is_show.load()) {
      updateRender();
    }
    std::cout << "out render" << std::endl;
    is_render_close.store(true);
    destroyRender();
  });
  render_thread.detach();
}

void mujoco_base::render_and_forward_or_step() {
  if (is_show.load())
    return;
  is_show.store(true);
  render_thread = std::thread([this]() {
    initRender(1280, 720, "mujoco_mapping");
    auto start_time = std::chrono::high_resolution_clock::now();
    while (is_show.load()) {
      auto now = std::chrono::high_resolution_clock::now();
      std::chrono::duration<float> duration_cs = now - start_time;
      if (duration_cs.count() > dt) {
        switch (mode) {
        case mujoco_mode::forward: {
          mj_forward(m, d);
          std::vector<float> dof_pos_;
          std::vector<float> dof_vel_;
          for (auto name : joint_names) {
            dof_pos_.push_back(d->qpos[joint_pos_idx[name]]);
          }
          for (int i = 0; i < static_cast<int>(dof_pos_.size()); i++) {
            dof_vel_.push_back((dof_pos_[i] - last_joint_pos[i]) / dt);
          }
          {
            std::lock_guard<std::mutex> lock(m_mtx);
            joint_data_lambda(joint_names, dof_pos_, dof_vel_);
            ask_joint(joint_names);
          }
          last_joint_pos = dof_pos_;
          break;
        }
        case mujoco_mode::step: {
          for (int i = 0; i < substeps; i++) {
            mj_step(m, d);
          }
          break;
        }
        case mujoco_mode::loc: {
          for (int i = 0; i < substeps; i++) {
            mj_step(m, d);
          }
          auto orientation = get_sensor_data(orientation_name);
          auto base_ang_vel = get_sensor_data(ang_vel_name);
          auto base_acc = get_sensor_data(acc_name);
          imu_data_lambda(orientation, base_ang_vel, base_acc);
          break;
        }
        }
        start_time = now;
      }
      updateRender();
    }
    std::cout << "out render" << std::endl;
    is_render_close.store(true);
    destroyRender();
  });
  render_thread.detach();
}

void mujoco_base::change_mode(std::string mode) {
  auto look_site = [this]() {
    double *mocap_pos = d->mocap_pos + 3 * quat_body_idx;
    lookat[0] = mocap_pos[0];
    lookat[1] = mocap_pos[1];
    lookat[2] = mocap_pos[2];
  };
  auto look_body = [this](std::string name) {
    int body_id = mj_name2id(m, mjOBJ_BODY, name.c_str());
    double *body_pos = d->xpos + 3 * body_id;
    lookat[0] = body_pos[0];
    lookat[1] = body_pos[1];
    lookat[2] = body_pos[2];
  };
  if (mode == "step") {
    this->mode.store(mujoco_mode::step);
    m = mocap_m;
    if (dt > 0.002) {
      substeps = static_cast<int>(dt / 0.002);
      m->opt.timestep = 0.002;
      d = mj_makeData(m);
    } else {
      substeps = 1;
    }
    look_site();
  } else if (mode == "forward") {
    m = mocap_m;
    this->mode.store(mujoco_mode::forward);
    m->opt.timestep = dt;
    d = mj_makeData(m);
    look_site();
  } else if (mode == "loc") {
    m = loc_m;
    this->mode.store(mujoco_mode::loc);
    if (dt > 0.002) {
      substeps = static_cast<int>(dt / 0.002);
      m->opt.timestep = 0.002;
      d = mj_makeData(m);
      look_body(robot_name);
    } else {
      substeps = 1;
    }
  } else {
    std::cout << "mode error" << std::endl;
  }
}

void mujoco_base::close_render() {
  if (!is_show.load())
    return;
  is_show.store(false);
  while (!is_render_close.load()) {
  }
  destroyRender();
  std::cout << "close render" << std::endl;
}

void mujoco_base::setAction(std::string joint_name, float action) {
  std::lock_guard<std::mutex> lk(m_mtx);
  auto it = joint_action_idx.find(joint_name);
  if (it != joint_action_idx.end()) {
    d->ctrl[joint_action_idx[joint_name]] = action;
  }
  if (!getJointData(joint_name)) {
    std::string name = joint_name.erase(joint_name.size() - 8, 8);
    getJointData(name);
  }
}

void mujoco_base::getQuatBodyIdx(std::string quat_body_name) {
  int body_id = mj_name2id(m, mjOBJ_BODY, quat_body_name.c_str());
  quat_body_idx = m->body_mocapid[body_id];
}

void mujoco_base::setBodyQuat(float w, float x, float y, float z) {
  if (mode.load() != mujoco_mode::forward)
    return;
  std::lock_guard<std::mutex> lk(m_mtx);
  mjtNum *quat_ = d->mocap_quat + quat_body_idx * 4;
  quat_[0] = w;
  quat_[1] = x;
  quat_[2] = y;
  quat_[3] = z;
}

void mujoco_base::setJointPos(std::string joint_name, float pos) {
  if (mode.load() != mujoco_mode::forward)
    return;
  std::lock_guard<std::mutex> lk(m_mtx);
  auto it = joint_pos_idx.find(joint_name);
  if (it != joint_pos_idx.end()) {
    d->qpos[joint_pos_idx[joint_name]] = pos;
  }
}

void mujoco_base::setDt(float dt) {
  std::lock_guard<std::mutex> lk(m_mtx);
  m->opt.timestep = dt;
  d = mj_makeData(m);
  this->dt = dt;
}

float mujoco_base::getTime() { return d->time; }

void mujoco_base::bindJointData(
    std::function<void(std::vector<std::string> &joint_name,
                       std::vector<float> &pos, std::vector<float> &vel)>
        lambda) {
  joint_data_lambda = lambda;
}

void mujoco_base::bindAskJoint(
    std::function<void(std::vector<std::string> &joint_name)> lambda) {
  ask_joint = lambda;
}

void mujoco_base::bindImuData(
    std::function<void(std::vector<mjtNum> &acc, std::vector<mjtNum> &gyro,
                       std::vector<mjtNum> &mag)>
        lambda) {
  imu_data_lambda = lambda;
}

bool mujoco_base::getJointData(std::string joint_name) {
  auto it = joint_pos_idx.find(joint_name);
  if (it != joint_pos_idx.end()) {
    std::vector<std::string> name;
    name.push_back(joint_name);
    std::vector<float> pos;
    pos.push_back(get_sensor_data(joint_name + "_p")[0]);
    std::vector<float> vel;
    vel.push_back(get_sensor_data(joint_name + "_v")[0]);
    joint_data_lambda(name, pos, vel);
    return true;
  } else {
    return false;
  }
}

void mujoco_base::destroyRender() {
  if (is_render_close.load() && !is_show.load()) {
    std::lock_guard<std::mutex> lock(m_mtx);
    if (window != nullptr) {
      // 销毁 OpenGL 资源
      mjr_freeContext(&con);
      mjv_freeScene(&scn);
      // 销毁窗口
      glfwDestroyWindow(window);
      window = nullptr;
      is_render_close.store(false);
      // std::cout << "close render" << std::endl;
    }
  }
}

void mujoco_base::initRender(int width, int height, std::string title) {
  std::lock_guard<std::mutex> lock(m_mtx);
  if (window != nullptr)
    return;
  // init GLFW
  if (!glfwInit()) {
    mju_error("Could not initialize GLFW");
  }
  // create window, make OpenGL context current, request v-sync
  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate(); // 终止 GLFW
    return;
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  // initialize visualization data structures
  mjv_defaultCamera(&cam);
  mjv_defaultOption(&opt);
  mjv_defaultScene(&scn);
  mjr_defaultContext(&con);

  // create scene and context
  mjv_makeScene(m, &scn, 2000);
  mjr_makeContext(m, &con, mjFONTSCALE_150);

  // install GLFW mouse and keyboard callbacks
  // 在初始化窗口后设置回调函数
  glfwSetWindowUserPointer(window, this);
  glfwSetKeyCallback(window, static_keyboard);
  glfwSetCursorPosCallback(window, static_mouse_move);
  glfwSetMouseButtonCallback(window, static_mouse_button);
  glfwSetScrollCallback(window, static_scroll);

  // 初始化时间
  previousTime = glfwGetTime();
  // std::cout << "Window created-----------------.\n";
  mj_step(m, d);
}

void mujoco_base::static_keyboard(GLFWwindow *window, int key, int scancode,
                                  int act, int mods) {
  mujoco_base *instance =
      reinterpret_cast<mujoco_base *>(glfwGetWindowUserPointer(window));
  if (instance) {
    instance->keyboard(key, scancode, act, mods);
  }
}

void mujoco_base::static_mouse_move(GLFWwindow *window, double xpos,
                                    double ypos) {
  mujoco_base *instance =
      reinterpret_cast<mujoco_base *>(glfwGetWindowUserPointer(window));
  if (instance) {
    instance->mouse_move(xpos, ypos);
  }
}

void mujoco_base::static_mouse_button(GLFWwindow *window, int button, int act,
                                      int mods) {
  mujoco_base *instance =
      reinterpret_cast<mujoco_base *>(glfwGetWindowUserPointer(window));
  if (instance) {
    instance->mouse_button(button, act, mods);
  }
}

void mujoco_base::static_scroll(GLFWwindow *window, double xoffset,
                                double yoffset) {
  mujoco_base *instance =
      reinterpret_cast<mujoco_base *>(glfwGetWindowUserPointer(window));
  if (instance) {
    instance->scroll(xoffset, yoffset);
  }
}

// keyboard callback
void mujoco_base::keyboard(int key, int scancode, int act, int mods) {
  // backspace: reset simulation
  if (act == GLFW_PRESS && key == GLFW_KEY_BACKSPACE) {
    mj_resetData(m, d);
    mj_forward(m, d);
  }
  if (act == GLFW_PRESS && key == GLFW_KEY_F1) {
    change_mode("step");
  }
  if (act == GLFW_PRESS && key == GLFW_KEY_F2) {
    change_mode("forward");
  }
  if (act == GLFW_PRESS && key == GLFW_KEY_F3) {
    change_mode("loc");
  }

  // update Ctrl state
  if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL) {
    ctrl_pressed = (act == GLFW_PRESS);
  }
}

// mouse button callback
void mujoco_base::mouse_button(int button, int act, int mods) {
  // update button state
  button_left =
      (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
  button_middle =
      (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);
  button_right =
      (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);

  // update mouse position
  glfwGetCursorPos(window, &lastx, &lasty);

  // handle double-click selection
  if (act == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
    double current_time = glfwGetTime();
    if (current_time - last_click_time < 0.3) {
      // double-click detected
      mjrRect viewport = {0, 0, 0, 0};
      glfwGetFramebufferSize(window, &viewport.width, &viewport.height);

      // unproject screen coordinates to 3D ray
      mjtNum selpnt[3];
      int geomid, flexid, skinid;
      // double click
      selected_body = mjv_select(
          m, d, &opt, (mjtNum)viewport.width / viewport.height,
          lastx / viewport.width, (viewport.height - lasty) / viewport.height,
          &scn, selpnt, &geomid, &flexid, &skinid);
      if (selected_body != -1) {
        // 遍历场景中的几何体
        for (int i = 0; i < scn.ngeom; ++i) {
          // 找到与选中 ID 匹配的几何体
          if (scn.geoms[i].objid == selected_body) {
            std::cout << "Selected body ID: " << selected_body << std::endl;
            // 将几何体的颜色设置为红色
            scn.geoms[i].rgba[0] = 1.0; // 红色
            scn.geoms[i].rgba[1] = 0.0; // 绿色
            scn.geoms[i].rgba[2] = 0.0; // 蓝色
            scn.geoms[i].rgba[3] = 1.0; // 不透明度
            // 如果找到匹配的几何体，可以提前退出循环
            break;
          }
        }
      }
    }
    last_click_time = current_time;
  }
}

// mouse move callback
void mujoco_base::mouse_move(double xpos, double ypos) {
  // no buttons down: nothing to do
  if (!button_left && !button_middle && !button_right) {
    return;
  }

  // compute mouse displacement, save
  double dx = xpos - lastx;
  double dy = ypos - lasty;
  lastx = xpos;
  lasty = ypos;

  // get current window size
  int width, height;
  glfwGetWindowSize(window, &width, &height);

  // get shift key state
  bool mod_shift = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
                    glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);

  // determine action based on mouse button
  mjtMouse action;
  if (button_right) {
    action = mod_shift ? mjMOUSE_MOVE_H : mjMOUSE_MOVE_V;
  } else if (button_left) {
    action = mod_shift ? mjMOUSE_ROTATE_H : mjMOUSE_ROTATE_V;
  } else {
    action = mjMOUSE_ZOOM;
  }

  // move camera
  mjv_moveCamera(m, action, dx / height, dy / height, &scn, &cam);

  // apply force if Ctrl is pressed
  if (ctrl_pressed && selected_body != -1) {
    // Calculate force direction and magnitude
    mjtNum force[3] = {dx * 0.1, dy * 0.1, 0.0};
    // Apply force to the center of the selected body
    mj_applyFT(m, d, force, nullptr, nullptr, selected_body, nullptr);
  }
}

// scroll callback
void mujoco_base::scroll(double xoffset, double yoffset) {
  // emulate vertical mouse motion = 5% of window height
  mjv_moveCamera(m, mjMOUSE_ZOOM, 0, -0.05 * yoffset, &scn, &cam);
}

// 计算并更新 FPS
void mujoco_base::calculateFPS() {
  double currentTime = glfwGetTime();
  double deltaTime = currentTime - previousTime;

  frameCount++;

  if (deltaTime >= 1.0) {
    fps = double(frameCount) / deltaTime;
    frameCount = 0;
    previousTime = currentTime;
  }
}

void mujoco_base::updateRender() {
  // std::lock_guard<std::mutex> lock(m_mtx);
  if (window != nullptr) {
    if (!glfwWindowShouldClose(window)) {
      // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      // 计算并更新FPS
      calculateFPS();

      // ---------------------look at ------------------------
      cam.lookat[0] = lookat[0];
      cam.lookat[1] = lookat[1];
      cam.lookat[2] = lookat[2];
      // ---------------------look at ------------------------

      // get framebuffer viewport
      mjrRect viewport = {0, 0, 0, 0};
      glfwGetFramebufferSize(window, &viewport.width, &viewport.height);
      // update scene and render
      mjv_updateScene(m, d, &opt, nullptr, &cam, mjCAT_ALL, &scn);

      mjr_render(viewport, &scn, &con);

      // 创建 FPS 文本
      std::string fpsText = "FPS: " + std::to_string(fps) + "   mode: ";
      switch (mode.load()) {
      case mujoco_mode::forward: {
        fpsText += "   forward";
        break;
      }
      case mujoco_mode::step: {
        fpsText += "   step";
        break;
      }
      case mujoco_mode::loc: {
        fpsText += "   loc";
        break;
      }
      }

      // 使用 mjr_overlay 显示 FPS
      mjr_overlay(mjFONT_NORMAL, mjGRID_TOPLEFT, viewport, fpsText.c_str(),
                  nullptr, &con);

      // swap OpenGL buffers (blocking call due to v-sync)
      glfwSwapBuffers(window);

      // process pending GUI events, call GLFW callbacks
      glfwPollEvents();
    } else {
      is_show.store(false);
    }
  }
}

std::vector<mjtNum>
mujoco_base::get_sensor_data(const std::string &sensor_name) {
  int sensor_id = mj_name2id(m, mjOBJ_SENSOR, sensor_name.c_str());
  if (sensor_id == -1) {
    std::cout << "no found sensor" << std::endl;
    return std::vector<mjtNum>();
  }
  int data_pos = 0;
  for (int i = 0; i < sensor_id; i++) {
    data_pos += m->sensor_dim[i];
  }
  std::vector<mjtNum> sensor_data(m->sensor_dim[sensor_id]);
  for (int i = 0; i < static_cast<int>(sensor_data.size()); i++) {
    sensor_data[i] = d->sensordata[data_pos + i];
  }
  return sensor_data;
}
void mujoco_base::draw_line(mjvScene *scn, mjtNum *from, mjtNum *to,
                            float rgba[4]) {
  scn->ngeom += 1;
  mjvGeom *geom = scn->geoms + scn->ngeom - 1;
  mjv_initGeom(geom, mjGEOM_SPHERE, nullptr, nullptr, nullptr, rgba);
  mjv_connector(geom, mjGEOM_ARROW, 0.03, from, to);
}