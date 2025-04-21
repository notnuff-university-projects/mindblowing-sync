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
    
    // Обчислення3: An = ti*(B*MVn) + ei*X*(MM*MCn)
    std::vector<int> temp1 = Data::multiplyVectorMatrix(data.B, data.MV);
    std::vector<int> part1 = Data::multiplyVectorScalar(temp1, ti);
    
    std::vector<std::vector<int>> temp2 = Data::multiplyMatrices(data.MM, data.MC);
    std::vector<int> temp3 = Data::multiplyVectorMatrix(data.X, temp2);
    std::vector<int> part2 = Data::multiplyVectorScalar(temp3, ei);
    
    std::vector<int> result = Data::addVectors(part1, part2);
    
    // Збереження результату
    for (int i = from; i <= to; ++i) {
        data.A[i] = result[i - from];
    }
    
    std::cout << "T2: Завершення обчислень" << std::endl;
} 