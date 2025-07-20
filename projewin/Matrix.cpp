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
    std::copy(a, a + 16, mMatrix);
}

CMatrix::~CMatrix()
{
}

// 行列の要素を右辺値として参照する
const GLfloat& CMatrix::operator[](std::size_t i) const
{
    return mMatrix[i];
}

// 行列の要素を左辺値として参照する
GLfloat& CMatrix::operator[](std::size_t i)
{
    return mMatrix[i];
}

// 変換行列の配列を返す
const GLfloat* CMatrix::Data() const
{
    return mMatrix;
}

// 法線ベクトルの変換行列を求める
void CMatrix::getNormalMatrix(GLfloat* aM) const
{
    aM[0] = ((mMatrix[ 5] * mMatrix[10]) - (mMatrix[ 6] * mMatrix[ 9]));
    aM[1] = ((mMatrix[ 6] * mMatrix[ 8]) - (mMatrix[ 4] * mMatrix[10]));
    aM[2] = ((mMatrix[ 4] * mMatrix[ 9]) - (mMatrix[ 5] * mMatrix[ 8]));
    aM[3] = ((mMatrix[ 9] * mMatrix[ 2]) - (mMatrix[10] * mMatrix[ 1]));
    aM[4] = ((mMatrix[10] * mMatrix[ 0]) - (mMatrix[ 8] * mMatrix[ 2]));
    aM[5] = ((mMatrix[ 8] * mMatrix[ 1]) - (mMatrix[ 9] * mMatrix[ 0]));
    aM[6] = ((mMatrix[ 1] * mMatrix[ 6]) - (mMatrix[ 2] * mMatrix[ 5]));
    aM[7] = ((mMatrix[ 2] * mMatrix[ 4]) - (mMatrix[ 0] * mMatrix[ 6]));
    aM[8] = ((mMatrix[ 0] * mMatrix[ 5]) - (mMatrix[ 1] * mMatrix[ 4]));
}

// 単位行列を設定する
void CMatrix::LoadIdentity()
{
    std::fill(mMatrix, mMatrix + 16, 0.0f);
    mMatrix[0] = 1.0f;
    mMatrix[5] = 1.0f;
    mMatrix[10] = 1.0f;
    mMatrix[15] = 1.0f;
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

// (x, y, z) 倍に拡大縮小する変換行列を作成する
CMatrix CMatrix::Scale(const GLfloat aX, const GLfloat aY, const GLfloat aZ)
{
    CMatrix t;
    t.LoadIdentity();
    t[0] = aX;
    t[5] = aY;
    t[10] = aZ;

    return t;
}

// (x, y, z) を軸に a 回転する変換行列を作成する
CMatrix CMatrix::Rotate(const GLfloat aA, const GLfloat aX, const GLfloat aY, const GLfloat aZ)
{
    CMatrix t;
    const GLfloat d(sqrt(aX * aX + aY * aY + aZ * aZ));

    if (d > 0.0f)
    {
        const GLfloat l(aX / d), m(aY / d), n(aZ / d);
        const GLfloat l2(l * l), m2(m * m), n2(n * n);
        const GLfloat lm(l * m), mn(m * n), nl(n * l);
        const GLfloat c(cos(aA)), c1(1.0f - c), s(sin(aA));

        t.LoadIdentity();
        t[0] = (1.0f - l2) * c + l2;
        t[1] = lm * c1 + n * s;
        t[2] = nl * c1 - m * s;
        t[4] = lm * c1 - n * s;
        t[5] = (1.0f - m2) * c + m2;
        t[6] = mn * c1 + l * s;
        t[8] = nl * c1 + m * s;
        t[9] = mn * c1 - l * s;
        t[10] = (1.0f - n2) * c + n2;
    }

    return t;
}

CMatrix CMatrix::operator*(const CMatrix& aMatrix) const
{
    CMatrix t;

    for (int column = 0; column < 4; column++)
    {
        for (int row = 0; row < 4; row++)
        {
            const int columnRow = ((column * 4) + row);

            GLfloat dot = 0.0f;
            for (int k = 0; k < 4; k++)
            {
                dot += mMatrix[((k * 4) + row)] * aMatrix[((column * 4) + k)];
            }

            t[columnRow] = dot;
        }
    }

    return t;
}

// ビュー変換行列を作成する
CMatrix CMatrix::LookAt(GLfloat aEx, GLfloat aEy, GLfloat aEz,  // 視点の位置
                        GLfloat aGx, GLfloat aGy, GLfloat aGz,  // 目標点(注視点)の位置
                        GLfloat aUx, GLfloat aUy, GLfloat aUz)  // 上方向のベクトル(カメラの向き)
{
    // 平行移動の変換行列
    const CMatrix tv = Translate(-aEx, -aEy, -aEz);

    // t 軸 = e - g
    const GLfloat tx = (aEx - aGx);
    const GLfloat ty = (aEy - aGy);
    const GLfloat tz = (aEz - aGz);

    // r 軸 = u x t 軸
    const GLfloat rx = ((aUy * tz) - (aUz * ty));
    const GLfloat ry = ((aUz * tx) - (aUx * tz));
    const GLfloat rz = ((aUx * ty) - (aUy * tx));

    // s 軸 = t 軸 x r 軸
    const GLfloat sx = ((ty * rz) - (tz * ry));
    const GLfloat sy = ((tz * rx) - (tx * rz));
    const GLfloat sz = ((tx * ry) - (ty * rx));

    // s 軸の長さのチェック
    const GLfloat s2 = ((sx * sx) + (sy * sy) + (sz * sz));
    if (s2 == 0.0f)
    {
        return tv;
    }

    // 回転の変換行列
    CMatrix rv;
    rv.LoadIdentity();

    // r 軸を正規化して配列変数に格納
    const GLfloat r = sqrt((rx * rx) + (ry * ry) + (rz * rz));
    rv[0] = (rx / r);
    rv[4] = (ry / r);
    rv[8] = (rz / r);

    // s 軸を正規化して配列変数に格納
    const GLfloat s = sqrt(s2);
    rv[1] = (sx / s);
    rv[5] = (sy / s);
    rv[9] = (sz / s);

    // t 軸を正規化して配列変数に格納
    const GLfloat t = sqrt((tx * tx) + (ty * ty) + (tz * tz));
    rv[2] = (tx / t);
    rv[6] = (ty / t);
    rv[10] = (tz / t);

    // 視点の平行移動の変換行列に視線の回転の変換行列を乗じる
    return rv * tv;
}

CMatrix CMatrix::Orthogonal(GLfloat aLeft, GLfloat aRight,
                            GLfloat aBottom, GLfloat aTop,
                            GLfloat aZNear, GLfloat aZFar)
{
    CMatrix t;
    const GLfloat dx = (aRight - aLeft);
    const GLfloat dy = (aTop - aBottom);
    const GLfloat dz = (aZFar - aZNear);

    //// if文パターン1
    //if (dx != 0.0f)
    //{
    //    if (dy != 0.0f)
    //    {
    //        if (dz != 0.0f)
    //        {
    //            t[0] = (2.0f / dx);
    //            t[5] = (2.0f / dy);
    //            t[10] = -(2.0f / dz);
    //            t[12] = -((aRight + aLeft) / dx);
    //            t[13] = -((aTop + aBottom) / dy);
    //            t[14] = -((aZFar + aZNear) / dz);
    //        }
    //    }
    //}
    //return t;

    //// if文パターン2
    //// 関数化するために抜き出しやすい
    //if (dx == 0.0f)
    //{
    //    return t;
    //}

    //if (dy == 0.0f)
    //{
    //    return t;
    //}

    //if (dz == 0.0f)
    //{
    //    return t;
    //}
    //
    //t[0] = (2.0f / dx);
    //t[5] = (2.0f / dy);
    //t[10] = -(2.0f / dz);
    //t[12] = -((aRight + aLeft) / dx);
    //t[13] = -((aTop + aBottom) / dy);
    //t[14] = -((aZFar + aZNear) / dz);

    //return t;

    //// if文パターン3
    //if (dx != 0.0f && dy != 0.0f && dz != 0.0f)
    //{
    //    t[0] = (2.0f / dx);
    //    t[5] = (2.0f / dy);
    //    t[10] = -(2.0f / dz);
    //    t[12] = -((aRight + aLeft) / dx);
    //    t[13] = -((aTop + aBottom) / dy);
    //    t[14] = -((aZFar + aZNear) / dz);
    //}

    // if文パターン4 採用
    assert(dx != 0.0f); // assert　こうであって欲しい
    assert(dy != 0.0f);
    assert(dz != 0.0f);
    //assert(dx != 0.0f && dy != 0.0f && dz != 0.0f); //まとめてもOK
    t[0] = (2.0f / dx);
    t[5] = (2.0f / dy);
    t[10] = -(2.0f / dz);
    t[12] = -((aRight + aLeft) / dx);
    t[13] = -((aTop + aBottom) / dy);
    t[14] = -((aZFar + aZNear) / dz);

    return t;
}

CMatrix CMatrix::Frustum(GLfloat aLeft, GLfloat aRight, GLfloat aBottom, GLfloat aTop, GLfloat aZNear, GLfloat aZFar)
{
    CMatrix t;
    const GLfloat dx = (aRight - aLeft);
    const GLfloat dy = (aTop - aBottom);
    const GLfloat dz = (aZFar - aZNear);

    assert(dx != 0.0f);
    assert(dy != 0.0f);
    assert(dz != 0.0f);

    t[0] = ((2.0f * aZNear) / dx);
    t[5] = ((2.0f * aZNear) / dy);
    t[8] = ((aRight + aLeft) / dx);
    t[9] = ((aTop + aBottom) / dy);
    t[10] = -((aZFar + aZNear) / dz);
    t[11] = -1.0f;
    t[14] = -((2.0f * aZFar * aZNear) / dz);
    t[15] = 0.0f;

    return t;
}

CMatrix CMatrix::Perspective(GLfloat aFovy, GLfloat aAspect, GLfloat aZNear, GLfloat aZFar)
{
    CMatrix t;
    const GLfloat dz = (aZFar - aZNear);

    assert(dz != 0.0f);

    GLfloat y = (1.0f / tan(aFovy * 0.5f));
    t[0] = y / aAspect;
    t[5] = y;
    t[10] = -((aZFar - aZNear) / dz);
    t[11] = -1.0f;
    t[14] = -((2.0f * aZFar * aZNear) / dz);
    t[15] = 0.0f;

    return t;
}
