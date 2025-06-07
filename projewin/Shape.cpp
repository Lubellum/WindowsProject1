#include "Shape.h"

// コンストラクタ
// size: 頂点の位置の次元
// vertexcount: 頂点の数
// vertex: 頂点属性を格納した配列
// indexcount: 頂点のインデックスの要素数
// index: 頂点のインデックスを格納した配列
CShape::CShape(GLint aSize, GLsizei aVertexcount, const CObject::tVertex* aVertex, GLsizei aIndexcount, const GLuint* aIndex)
    : mObject(new CObject(aSize, aVertexcount, aVertex, aIndexcount, aIndex))
    , mVertexcount(aVertexcount)
{
}

CShape::~CShape()
{
}

// 描画
void CShape::Draw() const
{
    // 頂点配列オブジェクトを結合する
    mObject->Bind();
    // 描画を実行する
    Execute();
}

// 描画の実行
void CShape::Execute() const
{
    // 折れ線で描画する
    glDrawArrays(GL_LINE_LOOP, 0, mVertexcount);
}