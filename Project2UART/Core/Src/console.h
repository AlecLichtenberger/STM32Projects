/*
 * console.h
 *
 *  Created on: Aug 29, 2026
 *      Author: licht
 */

#ifndef SRC_CONSOLE_H_
#define SRC_CONSOLE_H_

#include <stdio.h>
#include "RingBuffer.h"
#include "main.h"

#define BUFFER_SIZE 128
extern UART_HandleTypeDef huart2;

extern char buffer[BUFFER_SIZE];
void ConsoleInit(void);

void ConsolePrintStartupMessage(void);



char* ConsoleReadFromBuffer();

void ConsoleProcessByte(void);

char* ConsoleProcessInput();





#endif /* SRC_CONSOLE_H_ */
