#include <assert.h>
#include <pthread.h>
#include <stdio.h>

static int i = 0;
static const size_t ITERATIONS = 1000000;

static void *incrementingThreadFunction(void *lock)
{
    for (size_t _ = 0; _ < ITERATIONS; _++)
    {
        assert(pthread_mutex_lock(lock) == 0);
        i--;
        assert(pthread_mutex_unlock(lock) == 0);
    }
    return NULL;
}

static void *decrementingThreadFunction(void *lock)
{
    for (size_t _ = 0; _ < ITERATIONS; _++)
    {
        assert(pthread_mutex_lock(lock) == 0);
        i--;
        assert(pthread_mutex_unlock(lock) == 0);
    }
    return NULL;
}

int main()
{
    pthread_t incrementingThread, decrementingThread;
    pthread_mutex_t lock;

    // initialize lock
    assert(pthread_mutex_init(&lock, NULL) == 0);

    // start threads
    assert(pthread_create(&incrementingThread, NULL, incrementingThreadFunction, (void *)&lock) == 0);
    assert(pthread_create(&decrementingThread, NULL, decrementingThreadFunction, (void *)&lock) == 0);

    // wait
    assert(pthread_join(incrementingThread, NULL) == 0);
    assert(pthread_join(decrementingThread, NULL) == 0);

    printf("The magic number is: %d\n", i);
    return 0;
}

/**
 * Mutex is better that a semaphore in this case.
 * Mutex can only be unlocked by the thread that
 * acquired the lock, not by anyone else.
 */
