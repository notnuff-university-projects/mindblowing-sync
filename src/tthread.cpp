#include "tthread.h"
#include <sys/resource.h>

TThread::TThread() : running(false) {}

TThread::~TThread() {
    if (running) {
        join();
    }
}

void* TThread::threadFunction(void* arg) {
    TThread* thread = static_cast<TThread*>(arg);
    thread->run_thread();
    return nullptr;
}

void TThread::start() {
    if (!running) {
        running = true;
        pthread_create(&thread, nullptr, threadFunction, this);
    }
}

void TThread::join() {
    if (running) {
        pthread_join(thread, nullptr);
        running = false;
    }
}
