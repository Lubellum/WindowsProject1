#pragma once

// インデックスを使った図形の描画
#include "Shape.h"
#include <vector>

// インデックスを使った三角形による描画
class CFilledSphere : public CShape
{
public:
	//struct tRidgeLine
	//{
	//	static const GLuint mIndexCount = 2;
	//	GLuint mIndex[mIndexCount];
	//};
	CFilledSphere();
	~CFilledSphere();

	// 描画の実行
	virtual void Execute() const override;

private:
	// 球の分割数
	static const int mSlices;
	static const int mStacks;
	static const GLsizei mVertexCount;
	static const std::vector< CObject::tVertex > mVertex;
	static const GLsizei mWireIndexCount;
	static const std::vector< GLuint > mWireIndex;
	//static const GLsizei mRidgeLineCount;
	//static const GLsizei mWireIndexCount;
	//static const tRidgeLine mWireIndex[];
	static std::vector< CObject::tVertex > CreateVertex();
	static std::vector< GLuint > CreateIndex();
};