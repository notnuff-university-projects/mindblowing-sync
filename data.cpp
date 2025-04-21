#include "data.h"
#include <climits>
#include <iostream>

Data::Data() {
    H = N / P;
    A.resize(N);
    t = INT_MAX;  // Ініціалізація t
    
    // Ініціалізація м'ютексів
    pthread_mutex_init(&mutex_t, nullptr);
    pthread_mutex_init(&mutex_e, nullptr);
    
    // Ініціалізація бар'єру
    pthread_barrier_init(&barrier, nullptr, P);
    
    // Ініціалізація семафорів
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    sem_init(&sem3, 0, 0);
    sem_init(&sem4, 0, 0);
}

Data::~Data() {
    pthread_mutex_destroy(&mutex_t);
    pthread_mutex_destroy(&mutex_e);
    pthread_barrier_destroy(&barrier);
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    sem_destroy(&sem3);
    sem_destroy(&sem4);
}

std::vector<int> Data::multiplyVectorMatrix(const std::vector<int>& v, const std::vector<std::vector<int>>& m) {
    std::vector<int> result(m[0].size(), 0);
    for (size_t j = 0; j < m[0].size(); ++j) {
        for (size_t k = 0; k < v.size(); ++k) {
            result[j] += v[k] * m[k][j];
        }
    }
    return result;
}

std::vector<std::vector<int>> Data::multiplyMatrices(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b) {
    std::vector<std::vector<int>> result(a.size(), std::vector<int>(b[0].size(), 0));
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < b[0].size(); ++j) {
            for (size_t k = 0; k < a[0].size(); ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

int Data::scalarProduct(const std::vector<int>& a, const std::vector<int>& b) {
    int result = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

std::vector<int> Data::multiplyVectorScalar(const std::vector<int>& v, int s) {
    std::vector<int> result(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        result[i] = v[i] * s;
    }
    return result;
}

std::vector<int> Data::addVectors(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] + b[i];
    }
    return result;
} 