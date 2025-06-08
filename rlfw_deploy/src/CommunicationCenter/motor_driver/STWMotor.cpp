#include "STWMotor.h"
#include "ComCfg.hpp"
STWMotor::STWMotor() { motor_type = "DM"; }
STWMotor::~STWMotor() {}

STWCANMsg *STWMotor::enableMotor(uint8_t motor_id, bool enable,
                                 bool clear_fault) {
  uint32_t state;
  if (enable)
    state = 8;
  else
    state = 1;

  STWCANMsg msg;
  msg.ID = (motor_id << 5) | SET_STATE_ID;
  msg.MSGTYPE = CAN_STANDARD;
  msg.LEN = 4;
  memcpy(msg.DATA, &state, 4);
  stw_can_msg = msg;
  return &stw_can_msg;
}

MotorBack STWMotor::decode(CANMSG msg) {
  STWCANMsg dm_msg(msg);
  MotorBack motor;
  uint32_t cmd_id = msg.ID & 0x1F;
  motor.id = msg.ID >> 5;
  switch (cmd_id) {
  case HEARTBEAT_ID: {
    if (msg.LEN >= 8) {
      motor.is_update = false;
      memcpy(&motor.errorCode, msg.DATA, 4);
      // state = msg.DATA[4];
      uint8_t flags = msg.DATA[5];
      motor.lifeCounter = msg.DATA[7];
      if (flags & 0x01)
        motor.warning = MotorWarning::MotorError;
      else if (flags & 0x02)
        motor.warning = MotorWarning::MagneticEncoding;
      else if (flags & 0x04)
        motor.warning = MotorWarning::ControllerError;
      else if (flags & 0x80) {
        // trajectoryDone = flags & 0x80;
      }
    }
  } break;
  case ENCODER_FEEDBACK_ID:
    motor.is_update = false;
    memcpy(&motor.angle, msg.DATA, 4);
    memcpy(&motor.vel, msg.DATA + 4, 4);
    break;
  case CURRENT_FEEDBACK_ID:
    motor.is_update = false;
    memcpy(&motor.current, msg.DATA + 4, 4);
    break;
  case MIT_CONTROL_ID: {
    motor.is_update = true;
    motor.angle =
        ((float)(msg.DATA[1] << 8 | msg.DATA[2]) * 25.0f / 65535) - 12.5f;
    motor.vel =
        ((float)(msg.DATA[3] << 4 | msg.DATA[4] >> 4) * 130.0f / 4095.0f) -
        65.0f;
    motor.torque =
        ((float)(((msg.DATA[4] & 0xF) << 8) | msg.DATA[5]) * 100.0f / 4095.0f) -
        50.0f;
    // std::cout<<"MIT REV ---motor.angle:"<<motor.angle<<std::endl;
  }break;
  default:
    motor.is_update = false;
    break;
  }
  return motor;
}

STWCANMsg *STWMotor::locomotion(uint8_t motor_id, float torque, float pos,
                                float vel, float kp, float kd) {
  // 数据转换
  uint16_t pos_int = static_cast<uint16_t>((pos + 12.5f) * 65535.0f / 25.0f);
  uint16_t vel_int = static_cast<uint16_t>((vel + 65.0f) * 4095.0f / 130.0f);
  uint16_t kp_int = static_cast<uint16_t>(kp * 4095.0f / 500.0f);
  uint16_t kd_int = static_cast<uint16_t>(kd * 4095.0f / 5.0f);
  uint16_t t_int = static_cast<uint16_t>((torque + 50.0f) * 4095.0f / 100.0f);

  // 数据打包 (8字节CAN帧)
  STWCANMsg msg;
  msg.ID = (motor_id << 5) | MIT_CONTROL_ID;
  msg.MSGTYPE = CAN_STANDARD;
  msg.LEN = 8;

  // 位置 (16位): BYTE0(高8位), BYTE1(低8位)
  msg.DATA[0] = static_cast<uint8_t>((pos_int >> 8) & 0xFF);
  msg.DATA[1] = static_cast<uint8_t>(pos_int & 0xFF);

  // 速度 (12位): BYTE2(高8位), BYTE3[7-4](低4位)
  msg.DATA[2] = static_cast<uint8_t>((vel_int >> 4) & 0xFF);
  msg.DATA[3] = static_cast<uint8_t>((vel_int & 0x0F) << 4);

  // KP (12位): BYTE3[3-0](高4位), BYTE4(低8位)
  msg.DATA[3] |= static_cast<uint8_t>((kp_int >> 8) & 0x0F);
  msg.DATA[4] = static_cast<uint8_t>(kp_int & 0xFF);

  // KD (12位): BYTE5(高8位), BYTE6[7-4](低4位)
  msg.DATA[5] = static_cast<uint8_t>((kd_int >> 4) & 0xFF);
  msg.DATA[6] = static_cast<uint8_t>((kd_int & 0x0F) << 4);

  // 扭矩 (12位): BYTE6[3-0](高4位), BYTE7(低8位)
  msg.DATA[6] |= static_cast<uint8_t>((t_int >> 8) & 0x0F);
  msg.DATA[7] = static_cast<uint8_t>(t_int & 0xFF);

  // msg.print();

  stw_can_msg = msg;
  return &stw_can_msg;
}

/**
 * @brief 设置控制器模式
 * @param controlMode 控制模式：
 *                    0：电压控制
 *                    1：力矩控制
 *                    2：速度控制
 *                    3：位置控制
 * @param inputMode 输入模式：
 *                  0：闲置
 *                  1：直接控制
 *                  2：速度斜坡
 *                  3：位置滤波
 *                  5：梯形曲线
 *                  6：力矩斜坡
 *                  9：运动控制（MIT）
 * @return true 设置成功
 * @return false 设置失败
 */
STWCANMsg *STWMotor::setCtrlType(uint8_t motor_id) {
  
  // 准备数据
  uint32_t controlMode, inputMode;
  switch (ctrl_type) {
  case MotorCtrlType::POS: {
    controlMode = 3;
    inputMode = 9;
  } break;
  case MotorCtrlType::VEL: {
    controlMode = 2;
    inputMode = 9;
  } break;
  case MotorCtrlType::TORQUE: {
    controlMode = 1;
    inputMode = 9;
  } break;
  }
  STWCANMsg msg;
  msg.ID = (motor_id << 5) | SET_CTRL_MODE_ID;
  msg.MSGTYPE = CAN_STANDARD;
  msg.LEN = 8;
  memcpy(msg.DATA, &controlMode, 4);
  memcpy(msg.DATA + 4, &inputMode, 4);
  stw_can_msg = msg;
  return &stw_can_msg;
}

STWCANMsg *STWMotor::clearErr(uint8_t motor_id) {
  STWCANMsg msg;
  msg.ID = (motor_id << 5) | 0x018;
  msg.MSGTYPE = CAN_STANDARD;
  msg.LEN = 0;
  stw_can_msg = msg;
  return &stw_can_msg;
}

STWCANMsg *STWMotor::setZeroPoint(uint8_t motor_id) {
  STWCANMsg dm_msg;
  dm_msg.ID = motor_id;
  dm_msg.MSGTYPE = CAN_STANDARD;
  dm_msg.LEN = 8;
  dm_msg.DATA[0] = 0xFF;
  dm_msg.DATA[1] = 0xFF;
  dm_msg.DATA[2] = 0xFF;
  dm_msg.DATA[3] = 0xFF;
  dm_msg.DATA[4] = 0xFF;
  dm_msg.DATA[5] = 0xFF;
  dm_msg.DATA[6] = 0xFF;
  dm_msg.DATA[7] = 0xFE;
  stw_can_msg = dm_msg;
  return &stw_can_msg;
};