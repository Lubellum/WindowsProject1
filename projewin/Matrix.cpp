#include "Matrix.h"

CMatrix::CMatrix()
{
    LoadIdentity();
}

// 配列の内容で初期化するコンストラクタ
// a: GLfloat 型の 16 要素の配列
// 1 0 0 0  m0 m4 m8  m12
// 0 1 0 0  m1 m5 m9  m13
// 0 0 1 0  m2 m6 m10 m14
// 0 0 0 1  m3 m7 m11 m15
CMatrix::CMatrix(const GLfloat* a)
{
    std::copy(a, a + 16, matrix);
}

CMatrix::~CMatrix()
{
}

// 行列の要素を右辺値として参照する
const GLfloat& CMatrix::operator[](std::size_t i) const
{
    return matrix[i];
}

// 行列の要素を左辺値として参照する
GLfloat& CMatrix::operator[](std::size_t i)
{
    return matrix[i];
}

// 変換行列の配列を返す
const GLfloat* CMatrix::Data() const
{
    return matrix;
}

// 単位行列を設定する
void CMatrix::LoadIdentity()
{
    std::fill(matrix, matrix + 16, 0.0f);
    matrix[0] = 1.0f;
    matrix[5] = 1.0f;
    matrix[10] = 1.0f;
    matrix[15] = 1.0f;
}

// 単位行列を作成する static
CMatrix CMatrix::Identity()
{
    CMatrix t;
    t.LoadIdentity();
    return t;
}

// (x, y, z) だけ平行移動する変換行列を作成する
CMatrix CMatrix::Translate(const GLfloat aX, const GLfloat aY, const GLfloat aZ)
{
    CMatrix t;
    t.LoadIdentity();
    t[12] = aX;
    t[13] = aY;
    t[14] = aZ;

    return t;
}