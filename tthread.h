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
    // Перевірка чи потік запущений
    bool isRunning() const { return running; }
    // Встановлення пріоритету потоку

protected:
    // Чиста віртуальна функція, яку мають реалізувати нащадки
    virtual void execute() = 0;

private:
    pthread_t thread;
    bool running;
    int currentPriority;

    // Статична функція для запуску потоку
    static void* threadFunction(void* arg);
};

#endif // TTHREAD_H 