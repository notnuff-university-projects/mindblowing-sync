#ifndef T4_H
#define T4_H

#include "thread_base.h"

class T4 : public ThreadBase {
public:
    explicit T4(Data& data);

protected:
    virtual void input() override;
    virtual void after_compute_t_sync() override;
    virtual void after_compute_An_sync() override;
};

#endif // T4_H 