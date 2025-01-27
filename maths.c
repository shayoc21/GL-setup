#include "maths.h"
vec3f vec3fAdd(vec3f vec1, vec3f vec2)
{
  return (vec3f)
  {
    vec1.x + vec2.x,
    vec1.y + vec2.y,
    vec1.z + vec2.z
  };
}
void printMat4(const mat4 matrix)
{
    printf("View:\n");
    for (int i = 0; i < 4; i++)  // Loop through rows
    {
        for (int j = 0; j < 4; j++)  // Loop through columns
        {
            printf("%6.2f ", matrix.m[i * 4 + j]);  // Access element at (i, j)
        }
        printf("\n");  // Newline after each row
    }
    printf("\n");
}

mat4 mat4Multiply(mat4 mat1, mat4 mat2)
{
  mat4 returnMatrix;
  memset(returnMatrix.m, 0, sizeof(returnMatrix.m));
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        returnMatrix.m[i*4+j] += mat1.m[i*4+k] * mat2.m[k*4+j];
      }
    }
  }
  return returnMatrix;
}

mat4 lookMat4(vec3f cameraPos, vec3f cameraTarget, vec3f cameraUp)
{
  vec3f f = vec3fNormalize(vec3fSubtract(cameraPos, cameraTarget));
  vec3f r = vec3fNormalize(vec3fCross(cameraUp, f));
  vec3f u = vec3fNormalize(vec3fCross(f, r));
  
  mat4 returnMatrix;
  float m1[16] =
  {
    r.x, r.y, r.z, 0,
    u.x, u.y, u.z, 0,
    f.x, f.y, f.z, 0,
    0  , 0  , 0  , 1
  };
  mat4 left;
  memcpy(left.m, m1, sizeof(m1));
  float m2[16] =
  {
    1, 0, 0, -cameraPos.x,
    0, 1, 0, -cameraPos.y,
    0, 0, 1, -cameraPos.z,
    0, 0, 0, 1
  };
  mat4 right;
  memcpy(right.m, m2, sizeof(m2));

  returnMatrix = mat4Multiply(left, right);
  return returnMatrix;
}

float vec3fLength(vec3f* vector)
{
  return sqrt(vector->x*vector->x + vector->y*vector->y + vector->z*vector->z);
}

vec3f vec3fCross(vec3f vec1, vec3f vec2)
{
  vec3f returnVector = 
  {
    vec1.y*vec2.z - vec1.z*vec2.y,
    vec1.z*vec2.x - vec1.x*vec2.z,
    vec1.x*vec2.y - vec1.y*vec2.x
  };
  return returnVector;
}

vec3f vec3fNormalize(vec3f vector)
{
  float vectorLength = vec3fLength(&vector);

  vec3f returnVector = 
  {
    vector.x / vectorLength,
    vector.y / vectorLength,
    vector.z / vectorLength
  };
  return returnVector;
}

float vec3fDot(vec3f vec1, vec3f vec2)
{
  return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

vec3f vec3fSubtract(vec3f vec1, vec3f vec2)
{
  vec3f returnVector =
  {
    vec1.x - vec2.x,
    vec1.y - vec2.y,
    vec1.z - vec2.z
  };
  return returnVector;
}

mat4 identityMat4()
{
  mat4 returnMatrix;
  static const float identityMatrix[16] =
  {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
  memcpy(returnMatrix.m, identityMatrix, sizeof(identityMatrix));
  return returnMatrix;
}

mat4 mat4Rotate(mat4 matrix, float theta, vec3f axis)
{
  float 
    rx  = axis.x,
    rx2 = rx*rx,
    ry  = axis.y,
    ry2 = ry*ry,
    rz  = axis.z,
    rz2 = rz*rz,

    s = sin(theta),
    c = cos(theta);

  mat4 returnMatrix;

  float rotatedMatrix[16] = 
  {
    c+(rx2*(1-c))   , rx*ry*(1-c)-rz*s, rx*rz*(1-c)+ry*s, 0,
    ry*rx*(1-c)+rz*s, c+ry2*(1-c)     , ry*rz*(1-c)-rx*s, 0,
    rz*rx*(1-c)-ry*s, rz*ry*(1-c)+rx*s, c+rz2*(1-c)     , 0,
    0               , 0               , 0               , 1
  };
  memcpy(returnMatrix.m, rotatedMatrix, sizeof(rotatedMatrix));
  return returnMatrix;
}
    
mat4 orthoMat4(float l, float r, float b, float t, float n, float f)
{
  
  //SMALL PARAM NAMES TO ALLOW FOR MORE READABLE DEFINITION OF RETURNMATRIX
  //::PARAM NAME MEANINGS:://
  //  l - left plane of near view frustrum
  //  r - right plane ^^
  //  b - bottom plane
  //  t - top plane 
  //  n - distance to near plane
  //  f - distance to far plane
 
  mat4 returnMatrix;
  float orthoMatrix[16] =
  {
    2/(r-l), 0      , 0       , -(r+l)/(r-l),
    0      , 2/(t-b), 0       , -(t+b)/(t-b),
    0      , 0      , -2/(f-n), -(f+n)/(f-n),
    0      , 0      , 0       , 1
  };
  memcpy(returnMatrix.m, orthoMatrix, sizeof(orthoMatrix));
  return returnMatrix;
}

mat4 perspectiveMat4(float fov, float aspectRatio, float near, float far)
{
  float 
    tanf = tan(fov/2), 
    ar = aspectRatio,
    n = near,
    f = far;

  mat4 returnMatrix;
  float perspectiveMatrix[16] = 
  {
    1/(ar*tanf), 0     , 0          , 0,
    0          , 1/tanf, 0          , 0,
    0          , 0     , (f+n)/(n-f), 2*f*n/(n-f),
    0          , 0     , -1         , 0
  };
  memcpy(returnMatrix.m, perspectiveMatrix, sizeof(perspectiveMatrix));
  return returnMatrix;
}

mat4 translateMat4(mat4 matrix, vec3f vector)
{
  mat4 returnMatrix = identityMat4();
  returnMatrix.m[ 3] = vector.x;
  returnMatrix.m[ 7] = vector.y;
  returnMatrix.m[11] = vector.z;
  return returnMatrix;
}

float radians(float degrees)
{
  return degrees * (PI/180);
}




















