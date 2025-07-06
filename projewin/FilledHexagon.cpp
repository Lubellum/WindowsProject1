#include "FilledHexagon.h"

const GLsizei CFilledHexagon::mCubeVertexCount = 24;

// 面ごとに法線を変えた六面体の頂点属性
const CObject::tVertex CFilledHexagon::mCubeVertex[mCubeVertexCount] =
{
    // 左
    { -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f },
    { -1.0f, -1.0f,  1.0f, -1.0f, 0.0f, 0.0f },
    { -1.0f,  1.0f,  1.0f, -1.0f, 0.0f, 0.0f },
    { -1.0f,  1.0f, -1.0f, -1.0f, 0.0f, 0.0f },
    // 裏
    {  1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f },
    { -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f },
    { -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f },
    {  1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f },
    // 下
    { -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f },
    {  1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f },
    {  1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f },
    { -1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f },
    // 右
    {  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f },
    {  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f },
    {  1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f },
    {  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f },
    // 上
    { -1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f },
    { -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f },
    {  1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f },
    {  1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f },
    // 前
    { -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f },
    {  1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f },
    {  1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f },// 本来は0.8, 0.8, 0.1
    { -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f }
};

const GLsizei CFilledHexagon::mWireCubeIndexCount = 36;

// 六面体の稜線の両端点のインデックス
const GLuint CFilledHexagon::mWireCubeIndex[mWireCubeIndexCount] =
{
     0,  1,  2,  0,  2,  3, // 左
     4,  5,  6,  4,  6,  7, // 裏
     8,  9, 10,  8, 10, 11, // 下
    12, 13, 14, 12, 14, 15, // 右
    16, 17, 18, 16, 18, 19, // 上
    20, 21, 22, 20, 22, 23  // 前
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

CFilledHexagon::CFilledHexagon()
    : CShape(mCubeVertexCount, mCubeVertex, mWireCubeIndexCount, mWireCubeIndex)
{
}

CFilledHexagon::~CFilledHexagon()
{
}

// 描画の実行
void CFilledHexagon::Execute() const
{
    // 三角形で描画する
    glDrawElements(GL_TRIANGLES, mWireCubeIndexCount, GL_UNSIGNED_INT, 0);
}