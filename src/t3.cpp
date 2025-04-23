#include "t3.h"

#include <iostream>
#include <semaphore>

T3::T3(Data& data) : ThreadBase(data, 2 * data.H, 3 * data.H - 1) {}

void T3::execute() {
    // В execute ми вже завершили чекати на інші потоки, тому можемо просто вивести A
    ThreadBase::execute();

    std::cout << "A is: \n";
    for (int a : data.A) {
        std::cout << a << "\n";
    }
}

void T3::input() {
    std::cout << "T3: Введення Z" << std::endl;
    
    // Ініціалізація Z
    data.Z.resize(data.N);
    for (int i = 0; i < data.N; ++i) {
        data.Z[i] = data.GetRandomNumber();
    }

    data.A.resize(data.N);
}

void T3::after_compute_t_sync() {
    // Сигнал іншим потокам про завершення Обчислення2
    sem_post(&data.sem3_1);
    sem_post(&data.sem3_1);
    sem_post(&data.sem3_1);

    // Чекаємо на завершення Обчислення2 в інших потоках
    sem_wait(&data.sem1_1);
    sem_wait(&data.sem2_1);
    sem_wait(&data.sem4_1);
}

void T3::after_compute_An_sync() {
    // Сигнал потоку 3 про завершення Обчислення3
    sem_wait(&data.sem1_2);
    sem_wait(&data.sem2_2);
    sem_wait(&data.sem4_2);
} 