#include "model.h"
#include <iostream>

model::model()
{
    for (int i=0;i<_size_int;i++) {
        _int[i] = new integrator(0);
    }
}
model::~model()
{
    for (int i=0;i<_size_int;i++) {
        delete _int[i];
    }
}
float model::update(float u, float dt){
    float int1_v =_int[0]->getY_prevValue();
    float int2_v =_int[1]->getY_prevValue();
    float int3_v =_int[2]->getY_prevValue();

    float val = u + (-2)*int1_v + (-5)*int2_v + (-1.5)*int3_v;
    _int[0]->update(val, dt);
    _int[1]->update(int1_v, dt);
    _int[2]->update(int2_v, dt);

    return 0.5*int3_v;
}
