#ifndef T4_H
#define T4_H

#include "thread_base.h"

class T4 : public ThreadBase {
public:
    T4(Data& data);
    void input() override;
    void compute() override;
};

#endif // T4_H 