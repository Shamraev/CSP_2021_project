#include "generator.h"
#include <math.h>
using namespace std;

generator::generator(){
    int1 = new integrator(-0.3*std::sin(1));
    int2 = new integrator(3*std::cos(1));
    gain1 = new gain(-0.01);
    u = 0;
}
generator::~generator(){
    delete int1;
    delete int2;
    delete gain1;
}
float generator::update(float dt){
    u = int2->update(int1->update(gain1->update(u), dt), dt);
    return u;
}
