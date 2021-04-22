#include "modeld.h"
#include <iostream>
using namespace std;

modelD::modelD(float A[SIZE_X][SIZE_X], float B[SIZE_X], float C[SIZE_X], float D)
{
    // Копируем многомерные массивы
    memcpy(_A, A, sizeof(_A));
    memcpy(_B, B, sizeof(_B));
    memcpy(_C, C, sizeof(_C));
    _D = D;
    _x[0] = 0; _x[1] = 0; _x[2] = 0;
    _y = 0;

}

modelD::~modelD()
{

}

float modelD::update(float u)
{
    _y = (_C[0]*_x[0] + _C[1]*_x[1] + _C[2]*_x[2]) + _D*u;

    // x_{k+1}
    float x_next[SIZE_X];
    x_next[0] = _A[0][0]*_x[0] + _A[0][1]*_x[1] + _A[0][2]*_x[2] + _B[0]*u;
    x_next[1] = _A[1][0]*_x[0] + _A[1][1]*_x[1] + _A[1][2]*_x[2] + _B[1]*u;
    x_next[2] = _A[2][0]*_x[0] + _A[2][1]*_x[1] + _A[2][2]*_x[2] + _B[2]*u;

    memcpy(_x, x_next, sizeof(_x));
    return _y;
}

float modelD::getY()
{
    return _y;
}
