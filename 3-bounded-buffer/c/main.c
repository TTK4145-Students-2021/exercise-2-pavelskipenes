// compile with:  gcc -g main.c ringbuf.c -lpthread

#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ringbuf.h"

struct BoundedBuffer
{
    struct RingBuffer *buf;
    pthread_mutex_t mtx;
    sem_t empty;
    sem_t full;
};

#define SHARE_THREADS 0

struct BoundedBuffer *buf_new(int size)
{
    struct BoundedBuffer *buf = malloc(sizeof(struct BoundedBuffer));
    assert(buf != NULL);
    buf->buf = rb_new(size);

    assert(pthread_mutex_init(&buf->mtx, NULL) == 0);
    assert(sem_init(&buf->full, SHARE_THREADS, size) == 0);
    assert(sem_init(&buf->empty, SHARE_THREADS, size) == 0);

    return buf;
}

void buf_destroy(struct BoundedBuffer *buf)
{
    rb_destroy(buf->buf);
    pthread_mutex_destroy(&buf->mtx);
    sem_destroy(&buf->empty);
    sem_destroy(&buf->full);
    free(buf);
}

void buf_push(struct BoundedBuffer *buf, int val)
{
    // block if buffer is full
    sem_wait(&buf->full);
    pthread_mutex_lock(&buf->mtx);
    rb_push(buf->buf, val);
    pthread_mutex_unlock(&buf->mtx);
}

int buf_pop(struct BoundedBuffer *buf)
{
    // block if buffer is empty
    sem_wait(&buf->empty);
    pthread_mutex_lock(&buf->mtx);
    int val = rb_pop(buf->buf);
    pthread_mutex_unlock(&buf->mtx);
    // decrement full semaphore
    sem_post(&buf->full);
    return val;
}

void *producer(void *args)
{
    struct BoundedBuffer *buf = (struct BoundedBuffer *)(args);

    // push 10 values
    for (int i = 0; i < 10; i++)
    {
        nanosleep(&(struct timespec){0, 100 * 1000 * 1000}, NULL);
        printf("[producer]: pushing %d\n", i);
        buf_push(buf, i);
    }
    return NULL;
}

void *consumer(void *args)
{
    struct BoundedBuffer *buf = (struct BoundedBuffer *)(args);

    // give the producer a 1-second head start
    nanosleep(&(struct timespec){1, 0}, NULL);
    // consume values continuously
    while (1)
    {
        printf("[consumer]: %d\n", buf_pop(buf));
        nanosleep(&(struct timespec){0, 50 * 1000 * 1000}, NULL);
    }
}

int main()
{

    struct BoundedBuffer *buf = buf_new(5);

    pthread_t producer_thr, consumer_thr;

    pthread_create(&producer_thr, NULL, producer, buf);
    pthread_create(&consumer_thr, NULL, consumer, buf);

    pthread_join(producer_thr, NULL);
    pthread_cancel(consumer_thr);

    buf_destroy(buf);

    return 0;
}
