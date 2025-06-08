#include "Hexagon.h"

const GLsizei CHexagon::mCubeVertexCount = 8;

// 六面体の頂点の位置
const CObject::tVertex CHexagon::mCubeVertex[mCubeVertexCount] =
{
    { -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f }, // (0)
    { -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.8f }, // (1)
    { -1.0f,  1.0f,  1.0f, 0.0f, 0.8f, 0.0f }, // (2)
    { -1.0f,  1.0f, -1.0f, 0.0f, 0.8f, 0.8f }, // (3)
    {  1.0f,  1.0f, -1.0f, 0.8f, 0.0f, 0.0f }, // (4)
    {  1.0f, -1.0f, -1.0f, 0.8f, 0.0f, 0.8f }, // (5)
    {  1.0f, -1.0f,  1.0f, 0.8f, 0.8f, 0.0f }, // (6)
    {  1.0f,  1.0f,  1.0f, 0.8f, 0.8f, 0.8f }  // (7)
};

const GLsizei CHexagon::mWireCubeIndexCount = 24;

// 六面体の稜線の両端点のインデックス
const GLuint CHexagon::mWireCubeIndex[mWireCubeIndexCount] =
{
    1, 0, // (a)
    2, 7, // (b)
    3, 0, // (c)
    4, 7, // (d)
    5, 0, // (e)
    6, 7, // (f)
    1, 2, // (g)
    2, 3, // (h)
    3, 4, // (i)
    4, 5, // (j)
    5, 6, // (k)
    6, 1  // (l)
};


//const GLsizei CHexagon::mRidgeLineCount = 12;
//
//// 六面体の稜線の両端点のインデックス
//const CHexagon::tRidgeLine CHexagon::mWireCubeIndex[mRidgeLineCount] =
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
//const GLsizei CHexagon::mWireCubeIndexCount = tRidgeLine::mIndexCount * mRidgeLineCount;


CHexagon::CHexagon()
    : CShape(mCubeVertexCount, mCubeVertex,mWireCubeIndexCount, mWireCubeIndex)
{
}

CHexagon::~CHexagon()
{
}

// 描画の実行
void CHexagon::Execute() const
{
    // 線分群で描画する
    glDrawElements(GL_LINES, mWireCubeIndexCount, GL_UNSIGNED_INT, 0);
}