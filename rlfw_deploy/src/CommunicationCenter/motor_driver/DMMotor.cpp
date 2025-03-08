#include "DMMotor.h"
DMMotor::DMMotor() {}
DMMotor::~DMMotor() {}

DMCANMsg* DMMotor::enableMotor(uint8_t motor_id, bool enable, bool clear_fault) {
  DMCANMsg dm_msg;
  dm_msg.ID = motor_id;
  dm_msg.MSGTYPE = CAN_STANDARD;
  dm_msg.LEN = 8;
  if (enable) {
    dm_msg.DATA[0] = 0xFF;
    dm_msg.DATA[1] = 0xFF;
    dm_msg.DATA[2] = 0xFF;
    dm_msg.DATA[3] = 0xFF;
    dm_msg.DATA[4] = 0xFF;
    dm_msg.DATA[5] = 0xFF;
    dm_msg.DATA[6] = 0xFF;
    dm_msg.DATA[7] = 0xFC;
  } else {
    dm_msg.DATA[0] = 0xFF;
    dm_msg.DATA[1] = 0xFF;
    dm_msg.DATA[2] = 0xFF;
    dm_msg.DATA[3] = 0xFF;
    dm_msg.DATA[4] = 0xFF;
    dm_msg.DATA[5] = 0xFF;
    dm_msg.DATA[6] = 0xFF;
    dm_msg.DATA[7] = 0xFD;
  }
  if(clear_fault){}
  dm_can_msg = dm_msg;
  return &dm_can_msg;
}

MotorBack DMMotor::decode(CANMSG msg) {
  DMCANMsg dm_msg(msg);
  MotorBack motor;
  // 解码
  float p_int = (dm_msg.DATA[1] << 8) | dm_msg.DATA[2];
  float v_int = (dm_msg.DATA[3] << 4) | (dm_msg.DATA[4] >> 4);
  float t_int = ((dm_msg.DATA[4] & 0xF) << 8) | dm_msg.DATA[5];
  float position = uint_to_float(p_int, DM_P_MIN, DM_P_MAX, 16); // (-12.5,12.5)
  float velocity = uint_to_float(v_int, DM_V_MIN, DM_V_MAX, 12); // (-45.0,45.0)
  float torque = uint_to_float(t_int, DM_T_MIN, DM_T_MAX, 12);   // (-18.0,18.0)
  motor.angle = position;
  motor.ang_vel = velocity;
  motor.torque = torque;
  motor.id = (int)((dm_msg.DATA[0]) & 0x0F);
  motor.temperature = dm_msg.DATA[7]; // 线圈温度 DATA[6]：MOS管温度
  if (dm_msg.ID == 0) {
    motor.warning = MotorWarning::Unenable;
  } else if (dm_msg.ID == 1) {

  } else if (dm_msg.ID == 8) {
    motor.warning = MotorWarning::Overvoltage;
  } else if (dm_msg.ID == 9) {
    motor.warning = MotorWarning::Undervoltage;
  } else if (dm_msg.ID == 0xA) {
    motor.warning = MotorWarning::Overcurrent;
  } else if (dm_msg.ID == 0xB) {
    motor.warning = MotorWarning::MosOverTemperature;
  } else if (dm_msg.ID == 0xC) {
    motor.warning = MotorWarning::CoilOverTemperature;
  } else if (dm_msg.ID == 0xD) {
    motor.warning = MotorWarning::NoneCom;
  } else if (dm_msg.ID == 0xE) {
    motor.warning = MotorWarning::OverLoad;
  }
  return motor;
}

DMCANMsg* DMMotor::locomotion(uint8_t motor_id, float torque, float pos,
                             float ang_vel, float kp, float kd) {
  DMCANMsg dm_msg;
  dm_msg.ID = motor_id;
  dm_msg.MSGTYPE = CAN_STANDARD;
  dm_msg.LEN = 8;
  uint16_t pos_tmp, vel_tmp, kp_tmp, kd_tmp, tor_tmp;
  pos_tmp = float_to_uint(pos, DM_P_MIN, DM_P_MAX, 16);
  vel_tmp = float_to_uint(ang_vel, DM_V_MIN, DM_V_MAX, 12);
  kp_tmp = float_to_uint(kp, DM_KP_MIN, DM_KP_MAX, 12);
  kd_tmp = float_to_uint(kd, DM_KD_MIN, DM_KD_MAX, 12);
  tor_tmp = float_to_uint(torque, DM_T_MIN, DM_T_MAX, 12);
  dm_msg.DATA[0] = (pos_tmp >> 8);
  dm_msg.DATA[1] = pos_tmp;
  dm_msg.DATA[2] = (vel_tmp >> 4);
  dm_msg.DATA[3] = ((vel_tmp & 0xF) << 4) | (kp_tmp >> 8);
  dm_msg.DATA[4] = kp_tmp;
  dm_msg.DATA[5] = (kd_tmp >> 4);
  dm_msg.DATA[6] = ((kd_tmp & 0xF) << 4) | (tor_tmp >> 8);
  dm_msg.DATA[7] = tor_tmp;

  dm_can_msg = dm_msg;
  return &dm_can_msg;
}

uint16_t DMMotor::float_to_uint(float x, float x_min, float x_max, int bits)
{
    /// Converts a float to an unsigned int, given range and number of bits
    float span = x_max - x_min;
    float offset = x_min;
    return (uint16_t)((x - offset) * ((float)((1 << bits) - 1)) / span);
}

float DMMotor::uint_to_float(int x_int, float x_min, float x_max, int bits) {
  float span = x_max - x_min;
  float offset = x_min;
  return ((float)x_int) * span / ((float)((1 << bits) - 1)) + offset;
}