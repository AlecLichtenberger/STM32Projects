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
extern void clearRingBuffer(void);
extern int currHeadIdx(void);
extern int currTailIdx(void);
extern uint8_t peek(void);

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

// Push several bytes, pop them back in FIFO order
bool testPushPopMultiple(void){
    initBuffer();

    for(uint8_t i = 1; i <= 5; i++){
        if(!bufferPush(&i)){
            printf("FAIL: push %u returned false\r\n", i);
            return false;
        }
    }

    for(uint8_t i = 1; i <= 5; i++){
        uint8_t out = bufferPop();
        if(out != i){
            printf("FAIL: expected %u, got %u\r\n", i, out);
            return false;
        }
    }

    printf("PASS: testPushPopMultiple\r\n");
    return true;
}

// Push/pop more bytes than the buffer size so the indices wrap, and check the full case
bool testWrapAround(void){
    initBuffer();

    // Move head and tail near the end of the buffer
    for(int i = 0; i < 120; i++){
        uint8_t v = (uint8_t)(i + 1);
        bufferPush(&v);
        bufferPop();
    }

    // These pushes cross the end of the array
    for(uint8_t i = 1; i <= 20; i++){
        if(!bufferPush(&i)){
            printf("FAIL: wrap push %u returned false\r\n", i);
            return false;
        }
    }
    for(uint8_t i = 1; i <= 20; i++){
        uint8_t out = bufferPop();
        if(out != i){
            printf("FAIL: wrap expected %u, got %u\r\n", i, out);
            return false;
        }
    }

    // Capacity is 127 (one slot left unused): 128th push must fail
    initBuffer();
    uint8_t v = 7;
    for(int i = 0; i < 127; i++){
        if(!bufferPush(&v)){
            printf("FAIL: push %d returned false before full\r\n", i);
            return false;
        }
    }
    if(bufferPush(&v)){
        printf("FAIL: push succeeded on a full buffer\r\n");
        return false;
    }

    printf("PASS: testWrapAround\r\n");
    return true;
}

// Empty after init, not empty after push, empty again after pop and after clear
bool testIsEmptyAndClear(void){
    initBuffer();

    if(!isBufferEmpty()){
        printf("FAIL: new buffer not empty\r\n");
        return false;
    }

    uint8_t v = 0; // a zero byte must still count as data
    bufferPush(&v);
    if(isBufferEmpty()){
        printf("FAIL: buffer empty after push\r\n");
        return false;
    }

    bufferPop();
    if(!isBufferEmpty()){
        printf("FAIL: buffer not empty after pop\r\n");
        return false;
    }

    v = 9;
    bufferPush(&v);
    bufferPush(&v);
    clearRingBuffer();
    initBuffer();
    if(!isBufferEmpty()){
        printf("FAIL: buffer not empty after clear\r\n");
        return false;
    }

    printf("PASS: testIsEmptyAndClear\r\n");
    return true;
}

// Init resets indices and zeroes the storage
bool testInit(void){
    uint8_t v = 5;
    bufferPush(&v);
    bufferPush(&v);
    bufferPop();

    initBuffer();

    if(currHeadIdx() != 0 || currTailIdx() != 0){
        printf("FAIL: indices not reset (head=%d, tail=%d)\r\n", currHeadIdx(), currTailIdx());
        return false;
    }
    if(!isBufferEmpty()){
        printf("FAIL: buffer not empty after init\r\n");
        return false;
    }
    if(peek() != 0){
        printf("FAIL: storage not zeroed after init\r\n");
        return false;
    }

    printf("PASS: testInit\r\n");
    return true;
}

bool runAllRingBufferTests(void){
    bool ok = true;
    ok &= testPushPopSingleByte();
    ok &= testPushPopMultiple();
    ok &= testWrapAround();
    ok &= testIsEmptyAndClear();
    ok &= testInit();
    return ok;
}

