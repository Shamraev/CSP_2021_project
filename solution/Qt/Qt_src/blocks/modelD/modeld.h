#ifndef MODELD_H
#define MODELD_H

#define SIZE_X 3
class modelD
{
private:
    float _x[SIZE_X];
    float _y;
    float _A[SIZE_X][SIZE_X];
    float _B[SIZE_X];
    float _C[SIZE_X];
    float _D;
public:
    modelD(float A[SIZE_X][SIZE_X], float B[SIZE_X],float C[SIZE_X],float D);
    ~modelD();
    float update(float u);
    float getY();
};

#endif // MODELD_H
