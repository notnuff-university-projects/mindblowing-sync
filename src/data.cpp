#include "data.h"
#include <climits>
#include <iostream>
#include <semaphore>

Data::Data() {
    H = N / P;
    t = INT_MAX;  // Ініціалізація t
    
    // Ініціалізація генератора випадкових чисел
    gen.seed(std::time(nullptr));
    dist = std::uniform_int_distribution<int>(0, 9);
    
    // Ініціалізація м'ютексів
    pthread_mutex_init(&mutex_t, nullptr);
    pthread_mutex_init(&mutex_e, nullptr);
    
    // Ініціалізація бар'єру
    pthread_barrier_init(&barrier1, nullptr, P);
    
    // Ініціалізація семафорів
    sem_init(&sem1_1, 0, 0);
    sem_init(&sem2_1, 0, 0);
    sem_init(&sem3_1, 0, 0);
    sem_init(&sem4_1, 0, 0);

    sem_init(&sem1_2, 0, 0);
    sem_init(&sem2_2, 0, 0);
    sem_init(&sem3_2, 0, 0);
    sem_init(&sem4_2, 0, 0);
}

Data::~Data() {
    pthread_mutex_destroy(&mutex_t);
    pthread_mutex_destroy(&mutex_e);
    pthread_barrier_destroy(&barrier1);

    sem_destroy(&sem1_1);
    sem_destroy(&sem2_1);
    sem_destroy(&sem3_1);
    sem_destroy(&sem4_1);

    sem_destroy(&sem1_2);
    sem_destroy(&sem2_2);
    sem_destroy(&sem3_2);
    sem_destroy(&sem4_2);
}

// Скалярний добуток двох векторів
const int Data::multiplyVectorByVector(const TVector& v1, const TVector& v2) {
    if (v1.size() != v2.size())
        throw std::invalid_argument("Vectors must have the same size");

    int result = 0;
    for (size_t i = 0; i < v1.size(); ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

// Сума двох векторів
const TVector& Data::addVectors(const TVector& v1, const TVector& v2) {
    static TVector result;
    if (v1.size() != v2.size())
        throw std::invalid_argument("Vectors must have the same size");

    result.resize(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

// Частковий добуток вектора на матрицю (рядки з from до to)
const std::vector<int>& Data::multiplyVectorByMatrixRange(const TVector& v, const TMatrix& m, int from, int to) {
    static std::vector<int> result;
    if (v.size() != m[0].size())
        throw std::invalid_argument("Vector size must match matrix column count");

    result.resize(to - from);
    for (int i = from; i < to; ++i) {
        int sum = 0;
        for (size_t j = 0; j < v.size(); ++j) {
            sum += v[j] * m[i][j];
        }
        result[i - from] = sum;
    }
    return result;
}

// Частковий добуток матриці на матрицю (рядки з from до to)
const std::vector<TVector>& Data::multiplyMatrixByMatrixRange(const TMatrix& m1, const TMatrix& m2, int from, int to) {
    static std::vector<TVector> result;
    int N = m1.size();
    int M = m2[0].size();
    int K = m2.size();

    result.resize(to - from);
    for (int i = from; i < to; ++i) {
        result[i - from].resize(M);
        for (int j = 0; j < M; ++j) {
            int sum = 0;
            for (int k = 0; k < K; ++k) {
                sum += m1[i][k] * m2[k][j];
            }
            result[i - from][j] = sum;
        }
    }
    return result;
}

// Множення матриці на скаляр
const TMatrix& Data::multiplyByScalar(const TMatrix& m, int s) {
    static TMatrix result;
    result.resize(m.size());
    for (size_t i = 0; i < m.size(); ++i) {
        result[i].resize(m[i].size());
        for (size_t j = 0; j < m[i].size(); ++j) {
            result[i][j] = m[i][j] * s;
        }
    }
    return result;
}

// Множення вектора на скаляр
const TVector& Data::multiplyByScalar(const TVector& v, int s) {
    static TVector result;
    result.resize(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        result[i] = v[i] * s;
    }
    return result;
}

int Data::GetRandomNumber() {
    return dist(gen);
}