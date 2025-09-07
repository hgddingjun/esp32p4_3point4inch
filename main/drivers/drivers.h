#ifndef _DRIVERS_H_
#define _DRIVERS_H_

#include <cinttypes>

#include <cstdio>
#include <vector>
#include <memory>

class Drivers {
public: 
    virtual void init() = 0;
    virtual void deinit() = 0;
    virtual void reset() = 0;
    virtual void suspend() = 0;
    virtual void resume() = 0;
    virtual ~Drivers() {}
};
#endif