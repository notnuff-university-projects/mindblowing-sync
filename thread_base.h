#ifndef THREAD_BASE_H
#define THREAD_BASE_H

#include "data.h"

class ThreadBase  {
protected:
    Data& data;
    int from;
    int to;

public:
    ThreadBase(Data& data, int from, int to);
    virtual ~ThreadBase() = default;

    // Чиста віртуальна функція для введення даних
    virtual void input() = 0;

    // Функції для обчислення t для кожного потоку
    void compute_t();
    int compute_t_local();
    void compare_local_to_data_t(int tLocal);

    // Чиста віртуальна функція для обчислень
    virtual void compute() = 0;

    void execute();
};

#endif // THREAD_BASE_H 