#ifndef GENERATOR_H
#define GENERATOR_H

#include "blocks/gain/gain.h"
#include "blocks/integrator/integrator.h"

class generator
{
public:
    generator();
    ~generator();
    float update(float dt);
private:
    integrator *int1;
    integrator *int2;
    gain *gain1;
    float u;
};

#endif // GENERATOR_H
