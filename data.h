#ifndef DATA_H
#define DATA_H

#include <pthread.h>
#include <vector>

class Data {
public:
    int N = 1000;  // Розмірність векторів та матриць
    int P = 4;     // Кількість потоків
    int H;         // Розмір частини для кожного потоку

    // Спільні ресурси
    int t;         // КД1
    int e;         // КД3
    std::vector<int> B;
    std::vector<int> X;
    std::vector<std::vector<int>> MM;
    std::vector<int> A;           // Результат

    // Механізми синхронізації
    pthread_mutex_t mutex_t;      // Для КД1
    pthread_mutex_t mutex_e;      // Для КД3
    pthread_barrier_t barrier;    // Для синхронізації введення
    pthread_sem_t sem1, sem2, sem3, sem4;  // Семафори для сигналів між потоками

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