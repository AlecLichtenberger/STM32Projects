/*
 * console.c
 *
 *  Created on: Aug 29, 2026
 *      Author: licht
 */

#include <stdio.h>
#include <string.h>
#include "main.h"
#include "console.h"

char buffer[BUFFER_SIZE];

void ConsolePrintStartupMessage(){
	printf("Welcome to the UART Terminal\r\n");
	printf("Input a command to get started:\r\n");
}

char* ConsoleProcessInput(){
	uint8_t c;

	int bufferIdx = 0;
	for(int i = 0; i<20; i++){
		HAL_UART_Receive(&huart2, &c, 1, HAL_MAX_DELAY);
		if(c == '\b' || c == 0x7F){
			i++;
		}
		else if(c == '\r' || c == '\n'){
			buffer[bufferIdx] = '\0';
			return buffer;
		}
		else{
			buffer[bufferIdx] = c;
			bufferIdx++;
			printf("%c", c);
		}
	}

	return buffer;
}


/**
 * Clear input buffer
 * Reset current input position
 * print startup message and input message
 */
void ConsoleInit(){

	memset(buffer, 0, sizeof(buffer));
	printf("\n\n\n\n");
	ConsolePrintStartupMessage();
}





