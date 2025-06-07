#pragma once

#include "Shape.h"

class CHexagon : public CShape
{
public:
	//struct tRidgeLine
	//{
	//	static const GLuint mIndexCount = 2;
	//	GLuint mIndex[mIndexCount];
	//};
	CHexagon();
	~CHexagon();

	// ï`âÊÇÃé¿çs
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