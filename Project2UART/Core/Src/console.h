/*
 * console.h
 *
 *  Created on: Aug 29, 2026
 *      Author: licht
 */
#include <stdio.h>

#ifndef SRC_CONSOLE_H_
#define SRC_CONSOLE_H_

#define BUFFER_SIZE 20
extern UART_HandleTypeDef huart2;

extern char buffer[BUFFER_SIZE];
void ConsoleInit(void);

void ConsolePrintStartupMessage(void);

char* ConsoleReceiveInput();

void ConsoleProcessByte(void);

char* ConsoleProcessInput();





#endif /* SRC_CONSOLE_H_ */
