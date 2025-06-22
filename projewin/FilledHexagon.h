#pragma once

// インデックスを使った図形の描画
#include "Shape.h"

// インデックスを使った三角形による描画
class CFilledHexagon : public CShape
{
public:
	//struct tRidgeLine
	//{
	//	static const GLuint mIndexCount = 2;
	//	GLuint mIndex[mIndexCount];
	//};
	CFilledHexagon();
	~CFilledHexagon();

	// 描画の実行
	virtual void Execute() const override;

private:
	static const GLsizei mCubeVertexCount;
	static const CObject::tVertex mCubeVertex[];
	static const GLsizei mWireCubeIndexCount;
	static const GLuint mWireCubeIndex[];
	//static const GLsizei mRidgeLineCount;
	//static const GLsizei mWireCubeIndexCount;
	//static const tRidgeLine mWireCubeIndex[];
};