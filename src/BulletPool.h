#pragma once
#ifndef __BulletPool__
#define __BulletPool__
#include "Target.h"

class BulletPool
{
public:
    BulletPool(int);
    ~BulletPool();

    Target* Spawn();
    void Despawn(Target*);
    std::vector<Target*> all;
private:

    std::vector<Target*> active;
    std::vector<Target*> inactive;
};
#endif
