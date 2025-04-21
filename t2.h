#ifndef T2_H
#define T2_H

#include "thread_base.h"

class T2 : public ThreadBase {
public:
    T2(Data& data);
    void input() override;
    void compute() override;
};

#endif // T2_H 