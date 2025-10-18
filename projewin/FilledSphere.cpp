#include "FilledSphere.h"

const int CFilledSphere::mSlices = 16;
const int CFilledSphere::mStacks = 8;

// 頂点属性を作る
std::vector< CObject::tVertex > CFilledSphere::CreateVertex()
{
    std::vector< CObject::tVertex > vertex;

    for (int j = 0; j <= mStacks; ++j)
    {
        const float t = (static_cast<float>(j)) / (static_cast<float>(mStacks));
        float pi = 3.141593f;
        const float y = cos(pi * t);
        const float r = sin(pi * t);

        for (int i = 0; i <= mSlices; ++i)
        {
            const float s = (static_cast<float>(i)) / (static_cast<float>(mSlices));
            const float z = (r * cos(2 * pi * s));
            const float x = (r * sin(2 * pi * s));

            // 頂点属性
            const CObject::tVertex v = { x, y, z, x, y, z };

            // 頂点属性を追加する
            vertex.emplace_back(v);
        }
    }

    return vertex;
}

// インデックスを作る
std::vector< GLuint > CFilledSphere::CreateIndex()
{
    std::vector< GLuint > index;

    for (int j = 0; j < mStacks; ++j)
    {
        const int k = (mSlices + 1) * j;

        for (int i = 0; i < mSlices; ++i)
        {
            // 頂点のインデックス
            const GLuint k0 = k + i;
            const GLuint k1 = k0 + 1;
            const GLuint k2 = k1 + mSlices;
            const GLuint k3 = k2 + 1;

            // 左下の三角形
            index.emplace_back(k0);
            index.emplace_back(k2);
            index.emplace_back(k3);

            // 右上の三角形
            index.emplace_back(k0);
            index.emplace_back(k3);
            index.emplace_back(k1);
        }
    }

    return index;
}

// 面ごとに法線を変えた六面体の頂点属性
const std::vector< CObject::tVertex > CFilledSphere::mVertex = CFilledSphere::CreateVertex();

// 六面体の稜線の両端点のインデックス
const std::vector< GLuint > CFilledSphere::mWireIndex = CFilledSphere::CreateIndex();

//const GLsizei CHexagon::mRidgeLineCount = 12;
//
//// 六面体の稜線の両端点のインデックス
//const CHexagon::tRidgeLine CHexagon::mWireIndex[mRidgeLineCount] =
//{
//    { 1, 0 }, // (a)
//    { 2, 7 }, // (b)
//    { 3, 0 }, // (c)
//    { 4, 7 }, // (d)
//    { 5, 0 }, // (e)
//    { 6, 7 }, // (f)
//    { 1, 2 }, // (g)
//    { 2, 3 }, // (h)
//    { 3, 4 }, // (i)
//    { 4, 5 }, // (j)
//    { 5, 6 }, // (k)
//    { 6, 1 }  // (l)
//};
//
//const GLsizei CHexagon::mWireIndexCount = tRidgeLine::mIndexCount * mRidgeLineCount;

CFilledSphere::CFilledSphere()
    : CShape(mVertex.size(), mVertex.data(), mWireIndex.size(), mWireIndex.data())
{
}

CFilledSphere::~CFilledSphere()
{
}

// 描画の実行
void CFilledSphere::Execute() const
{
    // 三角形で描画する
    glPointSize(5);
    glDrawElements(GL_TRIANGLES, mWireIndex.size(), GL_UNSIGNED_INT, 0);
    //glDrawElements(GL_LINES, mWireIndex.size(), GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_POINTS, 0, mVertex.size());
}