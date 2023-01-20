//
// Created by yabai on 2023/01/19.
//

#ifndef MACHI_ENGINE_VECTOR_H
#define MACHI_ENGINE_VECTOR_H
#include <simd/simd.h>
#include <type_traits>
#include <Platform/types.h>
namespace Machi{
template<typename Scalar, MUINT N, MUINT M>
class Matrix{
   Scalar* m_data;
    MUINT row;
    MUINT col;
public:


    Matrix():m_data(new Scalar[N*M]){};



    Matrix(const Matrix& other){

    }

    Matrix(Matrix&& other){
        m_data = other.m_data;
       other.m_data = nullptr;
       row = other.row;
       col = other.col;
    }

    virtual ~Matrix(){
        delete[] m_data;
    }

    Matrix& operator*(Matrix& other){

    }

   Scalar* data(){
        return data;
    }

    Scalar* data() const{
        return data;
    }


    Matrix& operator /(Matrix& other){

    }

};



template<MUINT N> using VectorX = class Matrix<float, N, 1>;
using Vector3 = class Matrix<float, 3, 1>;
using Vector2 = class Matrix<float, 2, 1>;
using Matrix3 = class Matrix<float, 3, 3>;
using Matrix4 = class Matrix<float, 4, 4>;





}




#endif //MACHI_ENGINE_VECTOR_H
