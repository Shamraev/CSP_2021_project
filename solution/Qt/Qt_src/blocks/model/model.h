#ifndef MODEL_H
#define MODEL_H
#include "blocks/gain/gain.h"
#include "blocks/integrator/integrator.h"

class model
{
public:
    model();
    ~model();
    float update(float u, float dt);
private:
    static const int _size_int = 3;
    integrator *_int[_size_int];
};

#endif // MODEL_H
