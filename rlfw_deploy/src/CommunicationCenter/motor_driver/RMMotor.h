#pragma once
#include "PCANBasic.h"
#include <iostream>
#include <cstdint>
#include <cstring>
#include <iomanip>

#define GM6020_1st_ID 0x1FF
#define GM6020_2nd_ID 0x2FF
#define C6X0_1st_ID 0x200
#define C6X0_2nd_ID 0x1FF
enum MotorType
{
    C6X0,   // 单一C6X0电调
    GM6020, // 单一6020
    MERGE,   // 组合电机id
    DMMOTOR
};