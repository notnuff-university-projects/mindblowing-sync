#ifndef TTHREAD_H
#define TTHREAD_H

#include <pthread.h>
#include <functional>

class TThread {
public:
    TThread();
    virtual ~TThread();

    // Запуск потоку
    void start();
    // Очікування завершення потоку
    void join();

protected:
    // Чиста віртуальна функція, яку мають реалізувати нащадки
    virtual void run_thread () = 0;

private:
    pthread_t thread;
    bool running;

    // Статична функція для запуску потоку
    static void* threadFunction(void* arg);
};

#endif // TTHREAD_H 