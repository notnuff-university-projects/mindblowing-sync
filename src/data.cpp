#include "data.h"
#include <climits>
#include <iostream>
#include <semaphore>

Data::Data() {
    H = N / P;
    t = INT_MAX;  // Ініціалізація t
    
    // Ініціалізація генератора випадкових чисел
    gen.seed(std::time(nullptr));
    dist = std::uniform_int_distribution<int>(0, 99);
    
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
TVector Data::addVectors(const TVector& v1, const TVector& v2) {
    TVector result;
    if (v1.size() != v2.size())
        throw std::invalid_argument("Vectors must have the same size");

    result.resize(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

// Частковий добуток вектора на матрицю, стовпці у діапазоні [from; to]
std::vector<int> Data::multiplyVectorByMatrixRange(const TVector& v, const TMatrix& m, int from, int to) {
    std::vector<int> result;
    if (v.size() != m[0].size())
        throw std::invalid_argument("Vector size must match matrix column count");

    auto extend = to - from;
    result.resize(extend + 1);
    for (int i = 0; i <= extend; ++i) {
        auto columnI = from + i;
        const auto& column = m[columnI];

        result[i] = multiplyVectorByVector(v, column);
    }

    return result;
}

TVector Data::multiplyVectorByMatrixPart(const TVector &v, const TMatrix &m) {
    std::vector<int> result;
    if (v.size() != m[0].size())
        throw std::invalid_argument("Vector size must match matrix column count");

    result.resize(m.size());
    for (int i = 0; i < m.size(); ++i) {
        const auto& column = m[i];

        result[i] = multiplyVectorByVector(v, column);
    }

    return result;
}

// Частковий добуток матриці на матрицю (стовпці з from до to)
std::vector<TVector> Data::multiplyMatrixByMatrixRange(const TMatrix& m1, const TMatrix& m2, int from, int to) {
    std::vector<TVector> result;

    int rows = m1[0].size();     // Кількість рядків у m1
    int cols = m1.size();        // Кількість стовпців у m1 == кількість рядків у m2
    int extend = to - from;  // Кількість стовпців у результаті

    result.resize(extend + 1, TVector(rows, 0));

    // Ітеруємо по кожному стовпцю з діапазону [from, to]
    for (int j = from; j <= to; ++j) {
        const TVector& colM2 = m2[j]; // Стовпець з m2
        TVector& colRes = result[j - from]; // Відповідний стовпець у результаті

        // Для кожного рядка результатного стовпця
        for (int i = 0; i < rows; ++i) {
            int sum = 0;
            // Добуток відповідного рядка з m1 та стовпця з m2
            for (int k = 0; k < cols; ++k) {
                sum += m1[k][i] * colM2[k];
            }
            colRes[i] = sum;
        }
    }

    return result;
}

// Множення матриці на скаляр
TMatrix Data::multiplyByScalar(const TMatrix& m, int s) {
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
TVector Data::multiplyByScalar(const TVector& v, int s) {
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