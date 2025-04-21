#include "t4.h"
#include <iostream>
#include <semaphore.h>

T4::T4(Data& data) : ThreadBase(data, 3 * data.H, data.N - 1) {}

void T4::input() {
    std::cout << "T4: Введення B, X" << std::endl;
    
    // Ініціалізація B
    data.B.resize(data.N);
    for (int i = 0; i < data.N; ++i) {
        data.B[i] = data.dist(data.gen);
    }
    
    // Ініціалізація X
    data.X.resize(data.N);
    for (int i = 0; i < data.N; ++i) {
        data.X[i] = data.dist(data.gen);
    }
}

void T4::compute() {
    std::cout << "T4: Початок обчислень" << std::endl;

    compute_t();

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
    auto ti = data.t;
    pthread_mutex_unlock(&data.mutex_t);
    
    // Копіювання ei = e - КД3
    pthread_mutex_lock(&data.mutex_e);
    auto ei = data.e;
    pthread_mutex_unlock(&data.mutex_e);
    
    // Обчислення3: An = ti*(B*MVn) + ei*X*(MM*MCn)
    std::vector<int> temp1 = Data::multiplyVectorMatrix(data.B, data.MV);
    std::vector<int> part1 = Data::multiplyVectorScalar(temp1, ti);
    
    std::vector<std::vector<int>> temp2 = Data::multiplyMatrices(data.MM, data.MC);
    std::vector<int> temp3 = Data::multiplyVectorMatrix(data.X, temp2);
    std::vector<int> part2 = Data::multiplyVectorScalar(temp3, ei);
    
    std::vector<int> result = Data::addVectors(part1, part2);
    
    // Збереження результату у відповідній частині A
    for (int i = from; i <= to; ++i) {
        data.A[i] = result[i - from];
    }
    
    std::cout << "T4: Завершення обчислень" << std::endl;
} 