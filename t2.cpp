#include "t2.h"
#include <iostream>

T2::T2(Data& data) : ThreadBase(data, data.H, 2 * data.H - 1) {}

void T2::input() {
    std::cout << "T2: Введення e, MM" << std::endl;
    // Ініціалізація e та MM
    data.e = 1;
    data.MM.resize(data.N, std::vector<int>(data.N, 1));
}

void T2::compute() {
    std::cout << "T2: Початок обчислень" << std::endl;
    
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
    sem_post(&data.sem2);
    sem_post(&data.sem2);
    sem_post(&data.sem2);
    
    // Чекаємо на завершення Обчислення2 в інших потоках
    sem_wait(&data.sem1);
    sem_wait(&data.sem3);
    sem_wait(&data.sem4);
    
    // Копіювання ti = t - КД2
    pthread_mutex_lock(&data.mutex_t);
    ti = data.t;
    pthread_mutex_unlock(&data.mutex_t);
    
    // Копіювання ei = e - КД3
    pthread_mutex_lock(&data.mutex_e);
    ei = data.e;
    pthread_mutex_unlock(&data.mutex_e);
    
    std::cout << "T2: Завершення обчислень" << std::endl;
} 