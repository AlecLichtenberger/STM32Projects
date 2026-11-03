/*
 * Unit tests made to test the ring buffer methods
*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


extern void initBuffer(void);
extern bool bufferPush(uint8_t* writeByte);
extern uint8_t bufferPop(void);
extern bool isBufferEmpty(void);

// Push one byte, pop it back, expect the same value
bool testPushPopSingleByte(void){
    initBuffer();

    uint8_t in = 42;
    if(!bufferPush(&in)){
        printf("FAIL: push returned false\r\n");
        return false;
    }

    uint8_t out = bufferPop();
    if(out != in){
        printf("FAIL: expected %u, got %u\r\n", in, out);
        return false;
    }

    printf("PASS: testPushPopSingleByte\r\n");
    return true;
}