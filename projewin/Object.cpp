#pragma once
#include "Object.h"
//#include "iostream" 自分の周りを調べて、無ければ標準ライブラリを見に行く

// コンストラクタ
// size: 頂点の位置の次元
// vertexcount: 頂点の数
// vertex: 頂点属性を格納した配列
CObject::CObject(GLint aSize, GLsizei aVertexcount, const tVertex* aVertex)
    : mVao(), mVbo()
{
    // 頂点配列オブジェクト
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);
    // 頂点バッファオブジェクト
    glGenBuffers(1, &mVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER,
        aVertexcount * sizeof(tVertex), aVertex, GL_STATIC_DRAW);
    // 結合されている頂点バッファオブジェクトを in 変数から参照できるようにする
    glVertexAttribPointer(0, aSize, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
}
// コピーコンストラクタによるコピー禁止
CObject::CObject(const CObject& aValue)
{
}
// デストラクタ
CObject::~CObject()
{
    // 頂点配列オブジェクトを削除する
    glDeleteVertexArrays(1, &mVao);
    // 頂点バッファオブジェクトを削除する
    glDeleteBuffers(1, &mVbo);
}

// 頂点配列オブジェクトの結合
void CObject::Bind() const
{
    // 描画する頂点配列オブジェクトを指定する
    glBindVertexArray(mVao);
}

// 代入によるコピー禁止
CObject& CObject::operator=(const CObject& aValue)
{
    return *this;
}