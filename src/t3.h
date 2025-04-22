#ifndef T3_H
#define T3_H

#include "thread_base.h"

class T3 : public ThreadBase {
public:
    explicit T3(Data& data);

protected:
    virtual void execute() override;

    virtual void input() override;
    virtual void after_compute_t_sync() override;
    virtual void after_compute_An_sync() override;
};

#endif // T3_H 