#pragma once

#include <memory>
// 図形データ
#include "Object.h"
// 図形の描画
class Shape
{
public:
    // コンストラクタ
    // size: 頂点の位置の次元
    // vertexcount: 頂点の数
    // vertex: 頂点属性を格納した配列
    Shape(GLint aSize, GLsizei aVertexcount, const CObject::tVertex* aVertex);
    ~Shape();
    // 描画
    void Draw() const;
    // 描画の実行
    virtual void Execute() const;

protected:
    // 描画に使う頂点の数
    const GLsizei mVertexcount;

private:
    std::shared_ptr<const CObject> mObject;
};