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

public:
    void run_thread();

protected:

    // Загальна функція, в якій відбуваються всі обчислення для кожного потоку
    // Може відрізнятись для 3го потоку, але загалом всі кроки для кожного потоку схожі
    virtual void execute();

    virtual void pre_execute() {};
    virtual void post_execute() {};


    // Чиста віртуальна функція для введення даних
    virtual void input() = 0;

    // Функції для обчислення t для кожного потоку
    int compute_t_local();
    void compute_local_to_data_t(int tLocal);

    virtual void after_compute_t_sync() = 0;

    void safe_copy_ti();
    void safe_copy_ei();

    void compute_An_local();
    virtual void after_compute_An_sync() = 0;

protected:
    int ti = std::numeric_limits<int>::max();
    int ei = std::numeric_limits<int>::max();

};

#endif // THREAD_BASE_H 