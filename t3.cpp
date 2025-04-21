#include "t3.h"
#include <iostream>

T3::T3(Data& data) : ThreadBase(data, 2 * data.H, 3 * data.H - 1) {}

void T3::input() {
    std::cout << "T3: Введення Z" << std::endl;
    // Ініціалізація Z
    data.Z.resize(data.N, 1);
}

void T3::compute() {
    std::cout << "T3: Початок обчислень" << std::endl;
    
    // Обчислення1: ti = min(Zn)
    std::vector<int> Zn(data.H);
    for (int i = from; i <= to; ++i) {
        Zn[i - from] = data.Z[i];
        if (data.Z[i] < ti) {
            ti = data.Z[i];
        }
    }
    
    // Обчислення2: t = min(t, ti) - КД1
    pthread_mutex_lock(&data.mutex_t);
    if (ti < data.t) {
        data.t = ti;
    }
    pthread_mutex_unlock(&data.mutex_t);
    
    // Сигнал іншим потокам про завершення Обчислення2
    sem_post(&data.sem3);
    sem_post(&data.sem3);
    sem_post(&data.sem3);
    
    // Чекаємо на завершення Обчислення2 в інших потоках
    sem_wait(&data.sem1);
    sem_wait(&data.sem2);
    sem_wait(&data.sem4);
    
    // Копіювання ti = t - КД2
    pthread_mutex_lock(&data.mutex_t);
    ti = data.t;
    pthread_mutex_unlock(&data.mutex_t);
    
    // Копіювання ei = e - КД3
    pthread_mutex_lock(&data.mutex_e);
    ei = data.e;
    pthread_mutex_unlock(&data.mutex_e);
    
    std::cout << "T3: Завершення обчислень" << std::endl;
} 