#ifndef INTEGRATOR_H
#define INTEGRATOR_H


class integrator
{
public:
    integrator(float int_0_value);
    float getY_prevValue() const;
    float getInt_0_value() const;
    float update(float u, float dt);

private:
    float y_prev;
    float u_prev;
    float int_0_value;
};

#endif // INTEGRATOR_H
