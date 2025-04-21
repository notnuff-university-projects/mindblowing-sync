#ifndef THREAD_BASE_H
#define THREAD_BASE_H

#include "data.h"
#include "tthread.h"

class ThreadBase : public TThread {
protected:
    Data& data;
    int from;
    int to;
    int ti;  // Локальне значення min(Z)
    int ei;  // Локальна копія e

public:
    ThreadBase(Data& data, int from, int to);
    virtual ~ThreadBase() = default;

    // Чиста віртуальна функція для введення даних
    virtual void input() = 0;
    
    // Чиста віртуальна функція для обчислень
    virtual void compute() = 0;
    
    // Реалізація execute з TThread
    void execute() override;
};

#endif // THREAD_BASE_H 