#include "t4.h"
#include <iostream>
#include <semaphore>

T4::T4(Data& data) : ThreadBase(data, 3 * data.H, data.N - 1) {}

void T4::input() {
    std::cout << "T4: Введення B, X" << std::endl;
    
    // Ініціалізація B
    data.B.resize(data.N);
    for (int i = 0; i < data.N; ++i) {
        data.B[i] = data.GetRandomNumber();
    }
    
    // Ініціалізація X
    data.X.resize(data.N);
    for (int i = 0; i < data.N; ++i) {
        data.X[i] = data.GetRandomNumber();
    }
}

void T4::after_compute_t_sync() {
    // Сигнал іншим потокам про завершення Обчислення2
    sem_post(&data.sem4_1);
    sem_post(&data.sem4_1);
    sem_post(&data.sem4_1);

    // Чекаємо на завершення Обчислення2 в інших потоках
    sem_wait(&data.sem1_1);
    sem_wait(&data.sem2_1);
    sem_wait(&data.sem3_1);
}

void T4::after_compute_An_sync() {
    // Сигнал потоку 3 про завершення Обчислення3
    sem_post(&data.sem4_2);
} 