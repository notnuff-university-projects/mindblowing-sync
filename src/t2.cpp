#include "t2.h"
#include <iostream>
#include <semaphore>

T2::T2(Data& data) : ThreadBase(data, data.H, 2 * data.H - 1) {}

void T2::input() {
    std::cout << "T2: Введення e, MM" << std::endl;
    
    // Ініціалізація e
    data.e = data.GetRandomNumber();
    
    // Ініціалізація MM
    data.MM.resize(data.N, std::vector<int>(data.N));
    for (int i = 0; i < data.N; ++i) {
        for (int j = 0; j < data.N; ++j) {
            data.MM[i][j] = data.GetRandomNumber();
        }
    }
}

void T2::after_compute_t_sync() {
    // Сигнал іншим потокам про завершення Обчислення2
    sem_post(&data.sem2_1);
    sem_post(&data.sem2_1);
    sem_post(&data.sem2_1);

    // Чекаємо на завершення Обчислення2 в інших потоках
    sem_wait(&data.sem1_1);
    sem_wait(&data.sem3_1);
    sem_wait(&data.sem4_1);
}

void T2::after_compute_An_sync() {
    // Сигнал потоку 3 про завершення Обчислення3
    sem_post(&data.sem2_2);
} 