#pragma once
#include <GL/glew.h>

// 図形データ
class CObject
{
public:
    // 頂点属性
    struct tVertex
    {
        // 位置
        GLfloat mPosition[3];

        // 法線
        GLfloat mNormal[3];
    };

    // コンストラクタ
    // vertexcount: 頂点の数
    // vertex: 頂点属性を格納した配列
    CObject(GLsizei aVertexcount, const tVertex* aVertexGLsizei, GLsizei aIndexcount, const GLuint* aIndex);

    // デストラクタ
    virtual ~CObject();

    // 頂点配列オブジェクトの結合
    void Bind() const;

private:
    // コピーコンストラクタによるコピー禁止
    CObject(const CObject& aValue);
    // 代入によるコピー禁止
    CObject& operator=(const CObject& aValue);

    // 頂点配列オブジェクト名
    GLuint mVao;
    // 頂点バッファオブジェクト名
    GLuint mVbo;
    // インデックスの頂点バッファオブジェクト
    GLuint mIbo;
};