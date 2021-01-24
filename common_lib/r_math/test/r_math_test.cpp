#include "r_math/mat4.h"
#include <iostream>

using namespace reality::r_math;
int main(int argc, char **argv)
{
   Mat4f zero;
   std::cout << zero << std::endl;

   Mat4f unit;
   unit.data[0][0] = 1.0f;
   unit.data[1][1] = 1.0f;
   unit.data[2][2] = 1.0f;
   unit.data[3][3] = 1.0f;
   std::cout << unit << std::endl;

   std::cout << "zero * unit = " << std::endl;
   std::cout << zero * unit << std::endl;

   std::cout << "uint * unit = " << std::endl;
   std::cout << unit * unit << std::endl;

   Mat4f general;
   static int idx = 0;
   for (int row = 0; row < 4; row++)
   {
       for (int col = 0; col < 4; col++)
       {
           general.data[row][col] = idx++;
       }
   }
   std::cout << "general = " << std::endl;
   std::cout << general << std::endl;

   std::cout << "zero * general = " << std::endl;
   std::cout << zero * zero << std::endl;

   std::cout << "unit * general = " << std::endl;
   std::cout << unit * general << std::endl;

   std::cout << "general * general = " << std::endl;
   std::cout << general * general << std::endl;

   Mat4f projection = Mat4f::projection(3.1415926f/3.0f, 16.0f/16.0f, 0.1f, 10.0f);
   std::cout << "prjection matrix (fov: 60, aspect = with/height(16/9)) : " << std::endl;
   std::cout << projection << std::endl;

   Vec4f vec4(1.0f, 2.0f, 3.0f, 4.0f);
   std::cout << "zero * vec4 = " << std::endl;
   std::cout << zero * vec4 << std::endl;

   std::cout << "unit * vec4 = " << std::endl;
   std::cout << unit * vec4 << std::endl;

   std::cout << "general * vec4 = " << std::endl;
   std::cout << general * vec4 << std::endl;

   Vec4f vec1(0.57735, 0.57735, -9.0f, 1.0f);
   std::cout << "projection * vec1 = " << std::endl;
   std::cout << projection * vec1 << std::endl;


   return 0;
}
