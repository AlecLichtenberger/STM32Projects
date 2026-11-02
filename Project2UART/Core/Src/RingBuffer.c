/*
 * RingBuffer.c
 *
 *  Created on: Oct 14, 2026
 *      Author: licht
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Inits the ring buffer with specified size
 * @param size size of the varw
 */

uint8_t ringBuffer[128];
const int RING_BUFFER_SIZE = 128;
int headIdx; //idx of the head of the buffer
int tailIdx; //idx of the tail of the buffer
int size;


int ringBufferSize(){
	return sizeof(ringBuffer) / sizeof(ringBuffer[headIdx]);
}

void clearRingBuffer(){
	int bufSize = ringBufferSize();
	for(int i = 0; i<bufSize; i++){
		ringBuffer[i] = 0;
	}
}

void initBuffer(){
	headIdx = 0;
	tailIdx = 0;
	clearRingBuffer();
}

int currTailIdx(){
	return tailIdx;
}

int currHeadIdx(){
	return headIdx;
}

uint8_t peek(){
	return ringBuffer[currHeadIdx()];
}

bool isBufferEmpty(){
	int bufSize = ringBufferSize();
	for(int i = 0; i<bufSize; i++){
		if(ringBuffer[i] != 0){
			return false;
		}
	}

	return true;
}



bool bufferPush(uint8_t* writeByte){
	int futureTailIdx = tailIdx + 1;


	if(futureTailIdx == RING_BUFFER_SIZE){
		futureTailIdx = 0;
	}

	if(futureTailIdx == headIdx){
		printf("Ring Buffer is full, wait to push more data");
		return false;
	}
	
	ringBuffer[futureTailIdx] = *writeByte;

	tailIdx = futureTailIdx;
	return true;
}
