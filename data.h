#ifndef DATA_H
#define DATA_H

#include <vector>
#include <random>
#include <string>
#include <pthread.h>
#include <iostream>

class Data {
public:
    // Службові функції для роботи з векторами та матрицями
    double vectorDotProduct(const std::vector<double>& a, const std::vector<double>& b);
    std::vector<std::vector<double>> multiplyMatrices(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b);
    std::vector<double> multiplyMatrixVector(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vec);
    std::vector<std::vector<double>> transposeMatrix(const std::vector<std::vector<double>>& matrix);
    std::vector<double> sortVector(const std::vector<double>& vec);

    std::vector<double> getVector() const;
    std::vector<std::vector<double>> getMatrix() const;

    // Функції для генерації випадкових даних
    std::vector<double> generateRandomVector() const;
    std::vector<std::vector<double>> generateRandomMatrix() const;

    // Функції для введення даних з клавіатури
    std::vector<double> getVectorFromConsole(const std::string& vectorName) const;
    std::vector<std::vector<double>> getMatrixFromConsole(const std::string& matrixName) const;

    // Функції для синхронізованого виводу
    void printVector(const std::string& vectorName, const std::vector<double>& vec) const;
    void printMatrix(const std::string& matrixName, const std::vector<std::vector<double>>& matrix) const;
    void printShortenMatrix(const std::string& matrixName, const std::vector<std::vector<double>>& matrix) const;
    void waitForOutput() const;

    Mode mode;
    int N;  // Розмір векторів та матриць

    mutable pthread_mutex_t inputMutex;
    mutable pthread_mutex_t outputMutex;
    mutable pthread_cond_t outputCondition;
    mutable bool outputReady;

private:
    // Генератор випадкових чисел
    mutable std::random_device rd;
    mutable std::mt19937 gen;
    mutable std::uniform_int_distribution<int> dis;
};

#endif //DATA_H
