
#ifndef _MCU_LIB_H_
#define _MCU_LIB_H_

#include "stm32f1xx_hal.h"
#ifdef WIN32
#include "win_type.h"
#else
#endif

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;


typedef int64_t s64;
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef uint64_t u64;
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef float f32;
typedef double  f64;




#endif

