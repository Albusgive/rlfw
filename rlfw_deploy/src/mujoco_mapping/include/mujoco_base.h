#pragma once
#include <GLFW/glfw3.h>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <mujoco/mujoco.h>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

enum class mujoco_mode { step, forward, loc };

class mujoco_base {
public:
  mujoco_base() = default;
  mujoco_base(std::string model_file);
  ~mujoco_base();

  static mjModel *load_model(std::string model_file);
  void load_model(mjModel *m);

  std::string robot_name;
  void setRobotName(std::string robot_name) { this->robot_name = robot_name; };
  void buildLocModel(std::string file);

  void step(std::vector<float> action = std::vector<float>());
  void reset();
  // 渲染
  void render();
  void close_render();
  // 切换模式
  void render_and_forward_or_step();
  void change_mode(std::string mode);
  std::atomic<mujoco_mode> mode{mujoco_mode::step};
  void setAction(std::string joint_name, float action);

  float dt;
  int substeps = 1;
  void setDt(float dt);

  // 相机
  double lookat[3] = {0.0, 0.0, 0.0};

  // 关节数组索引
  std::unordered_map<std::string, int> joint_pos_idx;
  std::unordered_map<std::string, int> joint_action_idx;
  std::vector<float> last_joint_pos;
  std::vector<std::string> joint_names;
  float quat[4] = {1.0, 0.0, 0.0, 0.0};
  int quat_body_idx;
  void getQuatBodyIdx(std::string quat_body_name);
  void setBodyQuat(float w, float x, float y, float z);
  void setJointPos(std::string joint_name, float pos);
  float getTime();
  void bindJointData(
      std::function<void(std::vector<std::string> &joint_name,
                         std::vector<float> &pos, std::vector<float> &vel)>
          lambda);
  void bindAskJoint(
      std::function<void(std::vector<std::string> &joint_name)> lambda);
  void bindImuData(
      std::function<void(std::vector<mjtNum> &acc, std::vector<mjtNum> &gyro,
                         std::vector<mjtNum> &mag)>
          lambda);

  // 关节参数
  bool getJointData(std::string joint_name);

private:
  std::function<void(std::vector<std::string> &joint_name,
                     std::vector<float> &pos, std::vector<float> &vel)>
      joint_data_lambda = [=](std::vector<std::string> &, std::vector<float> &,
                              std::vector<float> &) -> void {};
  std::function<void(std::vector<std::string> &joint_name)> ask_joint =
      [=](std::vector<std::string> &) -> void {};
  std::function<void(std::vector<mjtNum> &, std::vector<mjtNum> &,
                     std::vector<mjtNum> &)>
      imu_data_lambda = [=](std::vector<mjtNum> &, std::vector<mjtNum> &,
                       std::vector<mjtNum> &) -> void {};
  std::string orientation_name;
  std::string ang_vel_name;
  std::string acc_name;

  // MuJoCo data structures
  mjModel *m = nullptr; // MuJoCo model
  mjModel *loc_m = nullptr;
  mjModel *mocap_m = nullptr;
  mjData *d = nullptr; // MuJoCo data
  mjvCamera cam;       // abstract camera
  mjvOption opt;       // visualization options
  mjvScene scn;        // abstract scene
  mjrContext con;      // custom GPU context

  // mouse interaction
  bool button_left = false;
  bool button_middle = false;
  bool button_right = false;
  double lastx = 0;
  double lasty = 0;
  double last_mouse_x = 0;
  double last_mouse_y = 0;
  bool ctrl_pressed = false;
  int selected_body = -1;
  double last_click_time = 0;

  double previousTime = 0.0;
  int frameCount = 0;
  double fps = 0.0;

  GLFWwindow *window = nullptr;
  std::mutex m_mtx;

  // 窗口操作
  static void static_keyboard(GLFWwindow *window, int key, int scancode,
                              int act, int mods);
  static void static_mouse_move(GLFWwindow *window, double xpos, double ypos);
  static void static_mouse_button(GLFWwindow *window, int button, int act,
                                  int mods);
  static void static_scroll(GLFWwindow *window, double xoffset, double yoffset);

  void keyboard(int key, int scancode, int act, int mods);
  void mouse_move(double xpos, double ypos);
  void mouse_button(int button, int act, int mods);
  void scroll(double xoffset, double yoffset);

  // 可视化
  std::atomic_bool is_show{false};
  // 可以销毁信号
  std::atomic_bool is_render_close{false};
  void destroyRender();
  void initRender(int width, int height, std::string title);
  std::thread render_thread;

  // 计算并更新 FPS
  void calculateFPS();
  void updateRender();

  std::vector<mjtNum> get_sensor_data(const std::string &sensor_name);
  void draw_line(mjvScene *scn, mjtNum *from, mjtNum *to, float rgba[4]);

  // 上次动作
  std::vector<float> last_action;
};
