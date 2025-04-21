#ifndef T3_H
#define T3_H

#include "thread_base.h"

class T3 : public ThreadBase {
public:
    T3(Data& data);
    void input() override;
    void compute() override;
};

#endif // T3_H 