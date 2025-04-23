#ifndef DATA_H
#define DATA_H

#include <pthread.h>
#include <vector>
#include <random>
#include <ctime>
#include <semaphore>

using TVector = std::vector<int>;
using TMatrix = std::vector<TVector>;

class Data {
public:
    Data();
    ~Data();

    // Допоміжні методи
    // Використовуємо для B * MV[i] та для MM[i]*MC[i]
    static const int multiplyVectorByVector(const TVector& v1, const TVector& v2);

    // Використовуємо для отримання A[from, to]
    static TVector addVectors(const TVector& v1, const TVector& v2);

    // Використовуємо для B * MV[from, to]
    static TVector multiplyVectorByMatrixRange(const TVector& v1, const TMatrix& m, int from, int to);
    static TVector multiplyVectorByMatrixPart(const TVector& v, const TMatrix& m);

    // Використовуємо для MM*MC[from, to]
    static std::vector<TVector> multiplyMatrixByMatrixRange(const TMatrix& v1, const TMatrix& m, int from, int to);

    // Використовуємо для e*X
    static TMatrix multiplyByScalar(const TMatrix& v, int s);
    static TVector multiplyByScalar(const TVector& v, int s);


public:
    int GetRandomNumber();

public:
    // Спільні ресурси, які ми копіюємо
    int t;         // КД1
    int e;         // КД3

    // Матриці та вектори
    // Для простоти множення матриці записуються у вигляді M[стовпчик][рядок]
    TMatrix MV;  // Матриця MV
    TMatrix MC;  // Матриця MC
    TMatrix MM;  // Матриця MM

    TVector B;                // Вектор B
    TVector X;                // Вектор X
    TVector Z;                // Вектор Z

    TVector A;                // Вектор A, Результат


    // Механізми синхронізації
    pthread_mutex_t mutex_t;      // Для КД1 та КД2
    pthread_mutex_t mutex_e;      // Для КД3
    pthread_barrier_t barrier1;   // Для синхронізації введення
    sem_t sem1_1, sem2_1, sem3_1, sem4_1;  // Семафори для сигналів між потоками
    sem_t sem1_2, sem2_2, sem3_2, sem4_2;  // Семафори для сигналів між потоками


    const int N = 1000;  // Розмірність векторів та матриць
    const int P = 4;     // Кількість потоків
    int H;         // Розмір частини для кожного потоку

protected:
    // Генератор випадкових чисел
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

};

#endif // DATA_H 