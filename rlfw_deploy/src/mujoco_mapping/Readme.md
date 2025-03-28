## mujoco的jointname要和现实一致,actuator要和jointname一致
## F1 step模式,可以同时控制现实和仿真看关节反馈
## F2 foward模式,发送MIT全0,映射现实关节
## 传感器 位置:jointname+"_p" 速度:jointname+"_v"
## 机器人外面加一层body name传入MappingNode , 机器人位置改为imu位置取负