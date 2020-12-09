/******************************************************************
*
* Matrix.c
*
* Description: Helper routine for matrix computations.
*
* Interactive Graphics and Simulation Group
* Institute of Computer Science
* University of Innsbruck
*
*******************************************************************/

/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define M_PI 3.14159265358979323846

/******************************************************************
*
* SetIdentityMatrix
*
*******************************************************************/

void SetIdentityMatrix(float* result)
{
    float identity[16] = {
        1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0,
    };

    memcpy(result, identity, 16*sizeof(float));
}

/******************************************************************
*
* SetScaleMatrix
*
*******************************************************************/

void SetScaleMatrix(float scalex, float scaley,float scalez,float* result)
{
    float scale[16] = {
        scalex, 0.0, 0.0, 0.0,
    0.0, scaley, 0.0, 0.0,
    0.0, 0.0, scalez, 0.0,
    0.0, 0.0, 0.0, 1.0,
    };

    memcpy(result, scale, 16*sizeof(float));
}

/******************************************************************
*
* SetRotationX
*
*******************************************************************/

void SetRotationX(float anglex, float* result)
{
    anglex = M_PI/180 * anglex;   /* Conversion angle from degree to radians */

    float temp[16] =
    {
        1.0,           0.0,          0.0, 0.0,
    0.0,  cosf(anglex),-sinf(anglex), 0.0,
    0.0,  sinf(anglex), cosf(anglex), 0.0,
    0.0,           0.0,          0.0, 1.0
    };

    memcpy(result, temp, 16*sizeof(float));
}


/******************************************************************
*
* SetRotationY
*
*******************************************************************/

void SetRotationY(float angley, float* result)
{
    angley = M_PI/180 * angley;   /* Conversion angle from degree to radians */

    float temp[16] =
    {
        cosf(angley),  0.0,   sinf(angley),  0.0,
             0.0,  1.0,            0.0,  0.0,
       -sinf(angley),  0.0,   cosf(angley),  0.0,
             0.0,  0.0,            0.0,  1.0
    };

    memcpy(result, temp, 16*sizeof(float));
}


/******************************************************************
*
* SetRotationZ
*
*******************************************************************/

void SetRotationZ(float anglez, float* result)
{
    anglez = M_PI/180 * anglez;   /* Conversion angle from degree to radian */

    float temp[16] =
    {
        cosf(anglez), -sinf(anglez),  0.0,  0.0,
        sinf(anglez),  cosf(anglez),  0.0,  0.0,
                 0.0,           0.0,  1.0,  0.0,
                 0.0,           0.0,  0.0,  1.0
    };

    memcpy(result, temp, 16*sizeof(float));
}


/******************************************************************
*
* SetTranslation
*
*******************************************************************/

void SetTranslation(float x, float y, float z, float* result)
{
  float temp[16] =
  {
      1.0,  0.0,  0.0,    x,
      0.0,  1.0,  0.0,    y,
      0.0,  0.0,  1.0,    z,
      0.0,  0.0,  0.0,  1.0
  };

  memcpy(result, temp, 16*sizeof(float));
}


/******************************************************************
*
* MultiplyMatrix
*
*******************************************************************/

void MultiplyMatrix(float* m1, float* m2, float* result)
{
    int i;
    float temp[16];

    for (i = 0; i < 16; i++)
        temp[i] = 0.0;

    temp[0] = m1[0]*m2[0] + m1[1]*m2[4] + m1[2]*m2[8] + m1[3]*m2[12];
    temp[1] = m1[0]*m2[1] + m1[1]*m2[5] + m1[2]*m2[9] + m1[3]*m2[13];
    temp[2] = m1[0]*m2[2] + m1[1]*m2[6] + m1[2]*m2[10] + m1[3]*m2[14];
    temp[3] = m1[0]*m2[3] + m1[1]*m2[7] + m1[2]*m2[11] + m1[3]*m2[15];

    temp[4] = m1[4]*m2[0] + m1[5]*m2[4] + m1[6]*m2[8] + m1[7]*m2[12];
    temp[5] = m1[4]*m2[1] + m1[5]*m2[5] + m1[6]*m2[9] + m1[7]*m2[13];
    temp[6] = m1[4]*m2[2] + m1[5]*m2[6] + m1[6]*m2[10] + m1[7]*m2[14];
    temp[7] = m1[4]*m2[3] + m1[5]*m2[7] + m1[6]*m2[11] + m1[7]*m2[15];

    temp[8] = m1[8]*m2[0] + m1[9]*m2[4] + m1[10]*m2[8] + m1[11]*m2[12];
    temp[9] = m1[8]*m2[1] + m1[9]*m2[5] + m1[10]*m2[9] + m1[11]*m2[13];
    temp[10] = m1[8]*m2[2] + m1[9]*m2[6] + m1[10]*m2[10] + m1[11]*m2[14];
    temp[11] = m1[8]*m2[3] + m1[9]*m2[7] + m1[10]*m2[11] + m1[11]*m2[15];

    temp[12] = m1[12]*m2[0] + m1[13]*m2[4] + m1[14]*m2[8] + m1[15]*m2[12];
    temp[13] = m1[12]*m2[1] + m1[13]*m2[5] + m1[14]*m2[9] + m1[15]*m2[13];
    temp[14] = m1[12]*m2[2] + m1[13]*m2[6] + m1[14]*m2[10] + m1[15]*m2[14];
    temp[15] = m1[12]*m2[3] + m1[13]*m2[7] + m1[14]*m2[11] + m1[15]*m2[15];

    memcpy(result, temp, 16*sizeof(float));
}

/* AddMatrix adds a and b
 * vec3 a
 * vec3 b
 * vec3 result
 */
void AddMatrix(float* a, float* b, float* result)
{
    float temp[3];

    temp[0] = a[0] + b[0];
    temp[1] = a[1] + b[1];
    temp[2] = a[2] + b[2];

    memcpy(result, temp, 3*sizeof(float));
}

/* SubstractMatrix substracts a and b
 * vec3 a
 * vec3 b
 * vec3 result
 */
void SubstractMatrix(float* a, float* b, float* result)
{
    float temp[3];

    temp[0] = a[0] - b[0];
    temp[1] = a[1] - b[1];
    temp[2] = a[2] - b[2];

    memcpy(result, temp, 3*sizeof(float));
}


/* CrossProduct calculates the cross product of a and b
 *
 * vec3 a
 * vec3 b
 * vec3 result
 */
void CrossProduct(float* a, float* b, float* result)
{
    float temp[3];

    temp[0] = (a[1] * b[2]) - (a[2] * b[1]);
    temp[1] = (a[2] * b[0]) - (a[0] * b[2]);
    temp[2] = (a[0] * b[1]) - (a[1] * b[0]);

    memcpy(result, temp, 3*sizeof(float));
}

/* Normalize normalizes a vector. A normalized vector representes a direction
 * vec3 a
 * vec3 result
 */
void NormalizeVector(float* a, float* result)
{
    float length = sqrt((a[0]*a[0])+(a[1]*a[1])+(a[2]*a[2]));

    float temp[3];
    temp[0] = a[0] / length;
    temp[1] = a[1] / length;
    temp[2] = a[2] / length;

    memcpy(result, temp, 3*sizeof(float));
}

/******************************************************************
*
* SetPerspectiveMatrix
*
*******************************************************************/

void SetPerspectiveMatrix(float fov, float aspect, float nearPlane,
                          float farPlane, float* result)
{
    float f = 1.0 / tan(fov * 3.1415926/360.0);
    float c1 = -(farPlane + nearPlane) / (farPlane - nearPlane);
    float c2 = -(2.0 * farPlane * nearPlane) / (farPlane - nearPlane);

    float temp[16] =
    {
        f/aspect,  0.0,   0.0,  0.0,
         0.0,    f,   0.0,  0.0,
         0.0,  0.0,    c1,   c2,
             0.0,  0.0,  -1.0,  0.0
    };

    memcpy(result, temp, 16*sizeof(float));
}

float radians(float deg)
{
    return M_PI/180 * deg;
}

/* ScalarMultiplication multiplies scalar a with vec3 b
 *
 * float a
 * vec3 b
 * vec3 result
 */
void ScalarMultiplication(float a, float* b, float* result)
{
    float temp[3] =
    {
        b[0] * a,
        b[1] * a,
        b[2] * a
    };

    memcpy(result, temp, 3*sizeof(float));
}

/* AdditionMatrix addition of a and b
 * vec3 a
 * vec3 b
 * vec3 result
 */
void AdditionMatrix(float* a, float* b, float* result)
{
    float temp[3];

    temp[0] = a[0] + b[0];
    temp[1] = a[1] + b[1];
    temp[2] = a[2] + b[2];

    memcpy(result, temp, 3*sizeof(float));
}
