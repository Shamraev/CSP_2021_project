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
    _prev_u = 0;

}

modelD::~modelD()
{

}

float modelD::update(float u)
{
    float y = getY();

    float x_tmp[SIZE_X];
    memcpy(x_tmp, _x, sizeof(x_tmp));

    _x[0] = _A[0][0]*x_tmp[0] + _A[0][1]*x_tmp[1] + _A[0][2]*x_tmp[2] + _B[0]*u;
    _x[1] = _A[1][0]*x_tmp[0] + _A[1][1]*x_tmp[1] + _A[1][2]*x_tmp[2] + _B[1]*u;
    _x[2] = _A[2][0]*x_tmp[0] + _A[2][1]*x_tmp[1] + _A[2][2]*x_tmp[2] + _B[2]*u;

    _prev_u = u;
    return y;
}

float modelD::getY()
{
    return (_C[0]*_x[0] + _C[1]*_x[1] + _C[2]*_x[2]) + _D*_prev_u;
}
