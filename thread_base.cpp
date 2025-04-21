#include "thread_base.h"

ThreadBase::ThreadBase(Data& data, int from, int to)
    : data(data), from(from), to(to) {}


void ThreadBase::compute_t() {
    auto tLocal = compute_t_local();
    compare_local_to_data_t(tLocal);
}

int ThreadBase::compute_t_local() {
    // Обчислення1: ti = min(Zn)

    int tLocal = std::numeric_limits<int>::max();
    for (int i = from; i <= to; ++i) {
        tLocal = std::min(data.Z[i], tLocal);
    }
    return tLocal;
}

void ThreadBase::compare_local_to_data_t(int tLocal) {
    // Обчислення2: t = min(t, ti) - КД1
    pthread_mutex_lock(&data.mutex_t);
    data.t = std::min(data.t, tLocal);
    pthread_mutex_unlock(&data.mutex_t);
}

void ThreadBase::execute() {
    // Введення даних
    input();

    // Синхронізація введення для всіх потоків B1
    pthread_barrier_wait(&data.barrier1);

    // Обчислення
    compute();
} 