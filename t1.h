#ifndef T1_H
#define T1_H

#include "thread_base.h"

class T1 : public ThreadBase {
private:
    std::vector<std::vector<int>> MV;
    std::vector<std::vector<int>> MC;

public:
    T1(Data& data);
    void input() override;
    void compute() override;
};

#endif // T1_H 