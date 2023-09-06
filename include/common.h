#ifndef COMMON_H_
#define COMMON_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"
// typedef unsigned int u32_t;
typedef int i32_t;

typedef unsigned int u32_t;
typedef unsigned short u16_t;
typedef short i16_t;

extern int about_to_exit;

void myexit(int a);

#endif