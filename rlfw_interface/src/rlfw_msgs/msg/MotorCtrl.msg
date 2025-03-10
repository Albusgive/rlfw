#需要jointname 选择好控制类型剩下的需要什么发什么
#jointname的frame_id为关节名称
std_msgs/Header jointname
#MIT, POS, VEL, TORQUE, POS_VEL,ENABLE(kd为0时失能，不为0使能)
string ctrl_type
# 扭矩
float32 torque
# 位置
float32 angle
# 角速度
float32 ang_vel
float32 kp
float32 kd

