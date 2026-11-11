#ifndef SRC_RINGBUFFER_H_
#define SRC_RINGBUFFER_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define RING_BUFFER_SIZE 128

/* Buffer variables */
extern uint8_t ringBuffer[RING_BUFFER_SIZE];
extern int headIdx;
extern int tailIdx;
extern int size;

/* Function declarations */

/**
 * Returns the size of the ring buffer
 * @return size of the ring buffer
 */
int ringBufferSize(void);

/**
 * Clears all data from the ring buffer
 */
void clearRingBuffer(void);

/**
 * Initializes the ring buffer (sets head and tail to 0, clears data)
 */
void initBuffer(void);

/**
 * Gets the current tail index
 * @return current tail index
 */
int currTailIdx(void);

/**
 * Gets the current head index
 * @return current head index
 */
int currHeadIdx(void);

/**
 * Peeks at the data at the head of the buffer without removing it
 * @return byte at the head of the buffer
 */
uint8_t peek(void);

/**
 * Checks if the ring buffer is empty
 * @return true if buffer is empty, false otherwise
 */
bool isBufferEmpty(void);

/**
 * Pushes a byte onto the tail of the ring buffer
 * @param writeByte pointer to the byte to write
 * @return true if successful, false if buffer is full
 */
bool bufferPush(uint8_t* writeByte);

/**
 * Pops a byte from the head of the ring buffer
 * @return byte from the head, or 0 if buffer is empty
 */
uint8_t bufferPop(void);

#endif /* SRC_RINGBUFFER_H_ */