#ifndef _BUFFER_H
#define _BUFFER_H

#include "stdint.h"

#define BUFFER_SIZE 64

void InBuffer(double byte);
unsigned char OutBufferStr(void);
uint8_t read_buf(void);

#endif