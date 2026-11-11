/*
 * RingBuffer.c
 *
 *  Created on: Oct 14, 2026
 *      Author: licht
 */


/**
 * Inits the ring buffer with specified size
 * @param size size of the varw
 */

#include "RingBuffer.h"

uint8_t ringBuffer[RING_BUFFER_SIZE];
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
	return headIdx == tailIdx;
}

bool bufferPush(uint8_t* writeByte){
	int futureTailIdx = currTailIdx() + 1;

	if(futureTailIdx == RING_BUFFER_SIZE){
		futureTailIdx = 0;
	}

	if(futureTailIdx == headIdx){
		printf("Ring Buffer is full, wait to push more data");
		return false;
	}

	ringBuffer[tailIdx] = *writeByte;

	tailIdx = futureTailIdx;
	return true;
}

// Returns 0 if the buffer is empty
uint8_t bufferPop(){
	if(isBufferEmpty()){
		return 0;
	}

	uint8_t popVal = peek();

	int futureHeadIdx = currHeadIdx() + 1;

	if(futureHeadIdx == RING_BUFFER_SIZE){
		futureHeadIdx = 0;
	}

	headIdx = futureHeadIdx;

	return popVal;
}
