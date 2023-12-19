#ifndef SIMPLE_POOL_H
#define SIMPLE_POOL_H

const int simplePoolSize = 2048;

typedef struct
{
    char data[simplePoolSize];
    int tail;
} simplePool;

simplePool global_simple_pool;

char* getData(int nBytes)
{
    global_simple_pool.tail += nBytes;
    return &global_simple_pool.data[global_simple_pool.tail];
}


#endif