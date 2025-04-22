#include "t1.h"
#include <iostream>
#include <semaphore>

T1::T1(Data& data) : ThreadBase(data, 0, data.H - 1) {}

void T1::input() {
    std::cout << "T1: Введення MV, MC" << std::endl;


    // Ініціалізація MV
    data.MV.resize(data.N, std::vector<int>(data.N));
    for (int i = 0; i < data.N; ++i) {
        for (int j = 0; j < data.N; ++j) {
            data.MV[i][j] = data.GetRandomNumber();
        }
    }
    
    // Ініціалізація MC
    data.MC.resize(data.N, std::vector<int>(data.N));
    for (int i = 0; i < data.N; ++i) {
        for (int j = 0; j < data.N; ++j) {
            data.MC[i][j] = data.GetRandomNumber();
        }
    }
}

void T1::after_compute_t_sync() {
    // Сигнал іншим потокам про завершення Обчислення2
    sem_post(&data.sem1_1);
    sem_post(&data.sem1_1);
    sem_post(&data.sem1_1);

    // Чекаємо на завершення Обчислення2 в інших потоках
    sem_wait(&data.sem2_1);
    sem_wait(&data.sem3_1);
    sem_wait(&data.sem4_1);
}

void T1::after_compute_An_sync() {
    // Сигнал потоку 3 про завершення Обчислення3
    sem_post(&data.sem1_2);
}
