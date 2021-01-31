#include "r_math/mat4.h"
#include "glm.hpp"
namespace reality
{
    namespace r_math
    {
        Mat4f::Mat4f() {}

        Mat4f::Mat4f(const Vec4f &v1, const Vec4f &v2,
                    const Vec4f &v3, const Vec4f &v4)
        {
            data[0][0] = v1.x;
            data[1][0] = v1.y;
            data[2][0] = v1.z;
            data[3][0] = v1.w;

            data[0][1] = v2.x;
            data[1][1] = v2.y;
            data[2][1] = v2.z;
            data[3][1] = v2.w;

            data[0][2] = v3.x;
            data[1][2] = v3.y;
            data[2][2] = v3.z;
            data[3][2] = v3.w;

            data[0][3] = v4.x;
            data[1][3] = v4.y;
            data[2][3] = v4.z;
            data[3][3] = v4.w;
        }

        Mat4f Mat4f::operator*(const Mat4f &other)
        {
            Mat4f ret;
            for (int row = 0; row < 4; row++)
            {
                for (int col = 0; col < 4; col++)
                {
                    ret.data[row][col] = data[row][0] * other.data[0][col] +
                                         data[row][1] * other.data[1][col] +
                                         data[row][2] * other.data[2][col] +
                                         data[row][3] * other.data[3][col];
                }
            }

            return ret;
        }

        Vec4f Mat4f::operator*(const Vec4f &vec4f)
        {
            Vec4f ret;

            ret.x = data[0][0] * vec4f.x + data[0][1] * vec4f.y + data[0][2] * vec4f.z + data[0][3] * vec4f.w;
            ret.y = data[1][0] * vec4f.x + data[1][1] * vec4f.y + data[1][2] * vec4f.z + data[1][3] * vec4f.w;
            ret.z = data[2][0] * vec4f.x + data[2][1] * vec4f.y + data[2][2] * vec4f.z + data[2][3] * vec4f.w;
            ret.w = data[3][0] * vec4f.x + data[3][1] * vec4f.y + data[3][2] * vec4f.z + data[3][3] * vec4f.w;

            return ret;
        }

        Mat4f Mat4f::projection(float fov, float aspect, float near, float far)
        {
            Mat4f proj;

            float height = 2 * std::tan(fov / 2.0f) * near;
            std::cout <<std::tan(fov /2.0f) << std::endl;
            float width = aspect * height;
            std::cout << "height: " << height << ", width: " << width << std::endl;
            proj.data[0][0] = 2 * near / width;
            proj.data[1][1] = 2 * near / height;
            proj.data[2][2] = -(far + near) / (far - near);
            proj.data[3][2] = -1;
            proj.data[2][3] = -(2 * far * near) / (far - near);

            return proj;
        }

        Mat4f Mat4f::translate(float x, float y, float z)
        {
            Mat4f tran;
            tran.data[0][0] = 1.0f;
            tran.data[1][1] = 1.0f;
            tran.data[2][2] = 1.0f;
            tran.data[3][3] = 1.0f;
            tran.data[0][3] = x;
            tran.data[1][3] = y;
            tran.data[2][3] = z;

            return tran;
        }

        Mat4f Mat4f::scale(float x, float y, float z)
        {
            Mat4f scal;
            scal.data[0][0] = x;
            scal.data[1][1] = y;
            scal.data[2][2] = z;
            scal.data[3][3] = 1.0f;

            return scal;
        }

        Mat4f Mat4f::rotate(float angle, Vec3f axis)
        {
            Mat4f rot;

            axis.normalize();
            float a = std::cos(angle/2.0f);
            float b = std::sin(angle/2.0f) * axis.x;
            float c = std::sin(angle/2.0f) * axis.y;
            float d = std::sin(angle/2.0f) * axis.z;

            rot.data[0][0] = 1 - 2 * c * c - 2 * d * d;
            rot.data[0][1] = 2 * b * c - 2 * a * d;
            rot.data[0][2] = 2 * a * c + 2 * b * d;
            rot.data[1][0] = 2 * b * c + 2 * a * d;
            rot.data[1][1] = 1 - 2 * b * b - 2 * d * d;
            rot.data[1][2] = 2 * c * d - 2 * a * b;
            rot.data[2][0] = 2 * b * d - 2 * a * c;
            rot.data[2][1] = 2 * a * b + 2 * c * d;
            rot.data[2][2] = 1 - 2 * b * b - 2 * c * c;
            rot.data[3][3] = 1.0f;

            return rot;
        }

        Mat4f Mat4f::reflect_x()
        {
            Mat4f rx;
            rx.data[0][0] = 1.0f;
            rx.data[1][1] = -1.0f;
            rx.data[2][2] = 1.0f;
            rx.data[3][3] = 1.0f;

            return rx;
        }

        std::ostream &operator<<(std::ostream &os, const Mat4f &mat)
        {
            os << "[ ";
            for (int row = 0; row < 4; row++)
            {
                if (row != 0)
                {
                    std::cout << "  ";
                }
                for (int col = 0; col < 4; col++)
                {
                    os << mat.data[row][col] << " ";
                }
                if (row == 3)
                {
                    std::cout << " ]";
                }
                os << std::endl;
            }

            return  os;
        }
    }
}
