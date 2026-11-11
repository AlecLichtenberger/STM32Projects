/*
 * console.c
 *
 *  Created on: Aug 29, 2026
 *      Author: licht
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "console.h"


char buffer[BUFFER_SIZE];
static uint8_t rxByte;

extern void initBuffer(void);
extern bool isBufferEmpty(void);
extern bool bufferPush(uint8_t* writeByte);
extern uint8_t bufferPop(void);

void ConsolePrintStartupMessage(){
	printf("Welcome to the UART Terminal\r\n");
	printf("Input a command to get started:\r\n");
}



/**
 * Clear input buffer
 * Reset current input position
 * print startup message and input message
 */
void ConsoleInit(){

	memset(buffer, 0, sizeof(buffer));
	initBuffer();
	HAL_UART_Receive_IT(&huart2, &rxByte, 1);
	printf("\n\n\n\n");
	ConsolePrintStartupMessage();
}



/**
 * Called by the HAL from the USART2 interrupt when one byte has been received.
 * Pushes the byte into the ring buffer and re-arms the interrupt receive.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2){
		bufferPush(&rxByte);
		HAL_UART_Receive_IT(&huart2, &rxByte, 1);
	}
}

/**
 * Reads bytes from the ring buffer until Enter is pressed or the line is full.
 * Returns the null-terminated line.
 */
char* ConsoleProcessInput(){
	int bufferIdx = 0;

	while(bufferIdx < BUFFER_SIZE - 1){
		if(isBufferEmpty()){
			continue;
		}

		uint8_t c = bufferPop();

		if(c == '\b' || c == 0x7F){
			if(bufferIdx > 0){
				bufferIdx--;
				printf("\b \b");
			}
		}
		else if(c == '\r' || c == '\n'){
			break;
		}
		else{
			buffer[bufferIdx] = c;
			bufferIdx++;
			printf("%c", c);
		}
	}

	buffer[bufferIdx] = '\0';
	printf("\r\n");
	return buffer;
}


void ConsoleBuildString(char* input){
	if(input == NULL){
		return;
	}

	char *cmd = strtok(input, " \t\n");

	if(cmd == NULL){
		return;
	}


	if(strcmp(cmd, "help") == 0){
		printf("Available commands:\r\n");
		printf("  help - Show this help message\r\n");
		printf("  exit - Exit the terminal\r\n");
		printf("  Hello - Say hello over serial\r\n");
	}
	else if(strcmp(cmd, "exit") == 0){
		printf("Exiting terminal...\r\n");
	}
	else if(strcmp(cmd, "Hello") == 0){
		printf("Hello over serial!\r\n");
	}
	else{
		printf("Unknown command: %s\r\n", cmd);
	}
	printf("\r\n");
}







