#ifndef T2_H
#define T2_H

#include "thread_base.h"

class T2 : public ThreadBase {
public:
    explicit T2(Data& data);

protected:
    virtual void input() override;
    virtual void after_compute_t_sync() override;
    virtual void after_compute_An_sync() override;
};

#endif // T2_H 