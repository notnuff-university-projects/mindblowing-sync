#ifndef T1_H
#define T1_H

#include "thread_base.h"

class T1 : public ThreadBase {
public:
    explicit T1(Data& data);

protected:
    virtual void input() override;
    virtual void after_compute_t_sync() override;
    virtual void after_compute_An_sync() override;
};

#endif // T1_H 