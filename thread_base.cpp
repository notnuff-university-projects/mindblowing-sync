#include "thread_base.h"

ThreadBase::ThreadBase(Data& data, int from, int to)
    : data(data), from(from), to(to), ti(INT_MAX), ei(0) {}

void ThreadBase::execute() {
    // Введення даних
    input();
    
    // Синхронізація введення
    pthread_barrier_wait(&data.barrier);
    
    // Обчислення
    compute();
} 