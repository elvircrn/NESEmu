#pragma once
#include <stdint.h>

typedef signed char        s8;
typedef short              s16;
typedef int                s32;
typedef long long          s64;
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

inline u8 LO(const u16 &addr) { return addr & 0xff; }
inline u8 HI(const u16 &addr) { return (addr >> 8) & 0xff; }