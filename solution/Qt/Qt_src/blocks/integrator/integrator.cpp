#include "integrator.h"

integrator::integrator(float int_0_value){
    this->int_0_value = int_0_value;
    this->y_prev = int_0_value;
    this->u_prev = 0; //??
}
float integrator::getInt_0_value() const {
    return this->int_0_value;
}
float integrator::getY_prevValue() const {
    return this->y_prev;
}
float integrator::update(float u, float dt){
    float y = y_prev + (u + u_prev)*dt/2;
    y_prev = y;
    u_prev = u;
    return y;
}
