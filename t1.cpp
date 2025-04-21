#include "t1.h"
#include <iostream>

T1::T1(Data& data) : ThreadBase(data, 0, data.H - 1) {}

void T1::input() {
    std::cout << "T1: Введення MV, MC" << std::endl;
    
    // Ініціалізація MV
    data.MV.resize(data.N, std::vector<int>(data.N));
    for (int i = 0; i < data.N; ++i) {
        for (int j = 0; j < data.N; ++j) {
            data.MV[i][j] = data.dist(data.gen);
        }
    }
    
    // Ініціалізація MC
    data.MC.resize(data.N, std::vector<int>(data.N));
    for (int i = 0; i < data.N; ++i) {
        for (int j = 0; j < data.N; ++j) {
            data.MC[i][j] = data.dist(data.gen);
        }
    }
}

void T1::compute() {
    std::cout << "T1: Початок обчислень" << std::endl;
    
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
    sem_post(&data.sem1);
    sem_post(&data.sem1);
    sem_post(&data.sem1);
    
    // Чекаємо на завершення Обчислення2 в інших потоках
    sem_wait(&data.sem2);
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
    
    std::cout << "T1: Завершення обчислень" << std::endl;
} 