// Copyright 2021 DeepMind Technologies Limited
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cstdio>
#include <cstring>

#include <GLFW/glfw3.h>
#include <mujoco/mujoco.h>
#include <iostream>
#include <vector>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"

// MuJoCo data structures
mjModel *m = NULL; // MuJoCo model
mjData *d = NULL;  // MuJoCo data
mjvCamera cam;     // abstract camera
mjvOption opt;     // visualization options
mjvScene scn;      // abstract scene
mjrContext con;    // custom GPU context

// mouse interaction
bool button_left = false;
bool button_middle = false;
bool button_right = false;
double lastx = 0;
double lasty = 0;

std::vector<mjtNum> get_sensor_data(const mjModel *model, const mjData *data, const std::string &sensor_name)
{
    int sensor_id = mj_name2id(model, mjOBJ_SENSOR, sensor_name.c_str());
    if (sensor_id == -1)
    {
        std::cout << "no found sensor" << std::endl;
        return std::vector<mjtNum>();
    }
    int sensor_output_size = model->sensor_dim[sensor_id];
    std::vector<mjtNum> sensor_data(sensor_output_size);
    for (int i = 0; i < sensor_output_size; i++)
    {
        sensor_data[i] = data->sensordata[sensor_id * sensor_output_size + i];
    }
    return sensor_data;
}

// keyboard callback
void keyboard(GLFWwindow *window, int key, int scancode, int act, int mods)
{
    // backspace: reset simulation
    if (act == GLFW_PRESS && key == GLFW_KEY_BACKSPACE)
    {
        mj_resetData(m, d);
        mj_forward(m, d);
    }
}

// mouse button callback
void mouse_button(GLFWwindow *window, int button, int act, int mods)
{
    // update button state
    button_left = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
    button_middle = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);
    button_right = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);

    // update mouse position
    glfwGetCursorPos(window, &lastx, &lasty);
}

// mouse move callback
void mouse_move(GLFWwindow *window, double xpos, double ypos)
{
    // no buttons down: nothing to do
    if (!button_left && !button_middle && !button_right)
    {
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
    if (button_right)
    {
        action = mod_shift ? mjMOUSE_MOVE_H : mjMOUSE_MOVE_V;
    }
    else if (button_left)
    {
        action = mod_shift ? mjMOUSE_ROTATE_H : mjMOUSE_ROTATE_V;
    }
    else
    {
        action = mjMOUSE_ZOOM;
    }

    // move camera
    mjv_moveCamera(m, action, dx / height, dy / height, &scn, &cam);
}

// scroll callback
void scroll(GLFWwindow *window, double xoffset, double yoffset)
{
    // emulate vertical mouse motion = 5% of window height
    mjv_moveCamera(m, mjMOUSE_ZOOM, 0, -0.05 * yoffset, &scn, &cam);
}

float quat[4];
class MultiThreadedSubscriber : public rclcpp::Node
{
public:
    MultiThreadedSubscriber(std::string node_name)
        : Node(node_name)
    {
        subscription_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "/nz_imu", 10, std::bind(&MultiThreadedSubscriber::callback, this, std::placeholders::_1));
    }

    void callback(const sensor_msgs::msg::Imu::SharedPtr msg)
    {
        std::lock_guard<std::mutex> lock(mutex_); // 确保线程安全
        // 处理消息
        quat[0]=msg->orientation.w;
        quat[1]=msg->orientation.x;
        quat[2]=msg->orientation.y;
        quat[3]=msg->orientation.z;
    }

    void spin()
    {
        while (rclcpp::ok())
        {
            rclcpp::spin_some(this->get_node_base_interface());
        }
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr subscription_;
    std::mutex mutex_; // 保护共享数据的互斥量
};

// main function
int main(int argc, const char **argv)
{
    rclcpp::init(argc, argv);
    auto mujoco_mapping_node = std::make_shared<MultiThreadedSubscriber>("mujoco_mapping");
    std::thread spin_thread([mujoco_mapping_node]()
                            { mujoco_mapping_node->spin(); });

    char error[1000] = "Could not load binary model";
    // load and compile model
    m = mj_loadXML("/home/albusgive2/wheel_legged_genesis/assets/mjcf/nz/scene.xml", 0, error, 1000);

    // make data
    d = mj_makeData(m);

    // init GLFW
    if (!glfwInit())
    {
        mju_error("Could not initialize GLFW");
    }

    // create window, make OpenGL context current, request v-sync
    GLFWwindow *window = glfwCreateWindow(1200, 900, "MUJOCO", NULL, NULL);
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
    glfwSetKeyCallback(window, keyboard);
    glfwSetCursorPosCallback(window, mouse_move);
    glfwSetMouseButtonCallback(window, mouse_button);
    glfwSetScrollCallback(window, scroll);

    int body_id = mj_name2id(m, mjOBJ_BODY, "B");
    // run main loop, target real-time simulation and 60 fps rendering
    while (!glfwWindowShouldClose(window) && rclcpp::ok())
    {
        // advance interactive simulation for 1/60 sec
        //  Assuming MuJoCo can simulate faster than real-time, which it usually can,
        //  this loop will finish on time for the next frame to be rendered at 60 fps.
        //  Otherwise add a cpu timer and exit this loop when it is time to render.
        mjtNum simstart = d->time;
        while (d->time - simstart < 1.0 / 60.0)
        {
            mj_step(m, d);
        }
        
        int mocap_id = m->body_mocapid[body_id];
        mjtNum* quat_ = d->mocap_quat+mocap_id * 4 ;
        for(int i=0;i<4;i++)
        {
            quat_[i]=quat[i];
            std::cout<<quat[i]<<"   ";
        }
        std::cout<<std::endl;

        // get framebuffer viewport
        mjrRect viewport = {0, 0, 0, 0};
        glfwGetFramebufferSize(window, &viewport.width, &viewport.height);

        // update scene and render
        mjv_updateScene(m, d, &opt, NULL, &cam, mjCAT_ALL, &scn);
        mjr_render(viewport, &scn, &con);

        // swap OpenGL buffers (blocking call due to v-sync)
        glfwSwapBuffers(window);

        // process pending GUI events, call GLFW callbacks
        glfwPollEvents();
    }

    // free visualization storage
    mjv_freeScene(&scn);
    mjr_freeContext(&con);

    // free MuJoCo model and data
    mj_deleteData(d);
    mj_deleteModel(m);

    // terminate GLFW (crashes with Linux NVidia drivers)
#if defined(__APPLE__) || defined(_WIN32)
    glfwTerminate();
#endif

    return 1;
}