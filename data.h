#ifndef DATA_H
#define DATA_H

#include <pthread.h>
#include <vector>
#include <random>
#include <ctime>
#include <bits/semaphore.h>

class Data {
public:
    int N = 1000;  // Розмірність векторів та матриць
    int P = 4;     // Кількість потоків
    int H;         // Розмір частини для кожного потоку

    // Генератор випадкових чисел
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

    // Спільні ресурси
    int t;         // КД1
    int e;         // КД3
    
    // Матриці та вектори
    std::vector<std::vector<int>> MV;  // Матриця MV
    std::vector<std::vector<int>> MC;  // Матриця MC
    std::vector<std::vector<int>> MM;  // Матриця MM
    std::vector<int> B;                // Вектор B
    std::vector<int> X;                // Вектор X
    std::vector<int> Z;                // Вектор Z
    std::vector<int> A;                // Вектор A, Результат

    // Механізми синхронізації
    pthread_mutex_t mutex_t;      // Для КД1
    pthread_mutex_t mutex_e;      // Для КД3
    pthread_barrier_t barrier1;   // Для синхронізації введення
    sem_t sem1, sem2, sem3, sem4;  // Семафори для сигналів між потоками

    Data();
    ~Data();

    // Допоміжні методи
    static std::vector<int> multiplyVectorMatrix(const std::vector<int>& v, const std::vector<std::vector<int>>& m);
    static std::vector<std::vector<int>> multiplyMatrices(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b);
    static int scalarProduct(const std::vector<int>& a, const std::vector<int>& b);
    static std::vector<int> multiplyVectorScalar(const std::vector<int>& v, int s);
    static std::vector<int> addVectors(const std::vector<int>& a, const std::vector<int>& b);
};

#endif // DATA_H 