#include "t4.h"
#include <iostream>

T4::T4(Data& data) : ThreadBase(data, 3 * data.H, data.N - 1) {}

void T4::input() {
    std::cout << "T4: Введення B, X" << std::endl;
    // Ініціалізація B та X
    data.B.resize(data.N, 1);
    data.X.resize(data.N, 1);
}

void T4::compute() {
    std::cout << "T4: Початок обчислень" << std::endl;
    
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
    sem_post(&data.sem4);
    sem_post(&data.sem4);
    sem_post(&data.sem4);
    
    // Чекаємо на завершення Обчислення2 в інших потоках
    sem_wait(&data.sem1);
    sem_wait(&data.sem2);
    sem_wait(&data.sem3);
    
    // Копіювання ti = t - КД2
    pthread_mutex_lock(&data.mutex_t);
    ti = data.t;
    pthread_mutex_unlock(&data.mutex_t);
    
    // Копіювання ei = e - КД3
    pthread_mutex_lock(&data.mutex_e);
    ei = data.e;
    pthread_mutex_unlock(&data.mutex_e);
    
    std::cout << "T4: Завершення обчислень" << std::endl;
} 