#pragma once

#include <algorithm>
#include <GL/glew.h>
#include <cmath>
#include <cassert>

// 変換行列
class CMatrix
{
public:
	CMatrix();
	~CMatrix();
	// 配列の内容で初期化するコンストラクタ
	// a: GLfloat 型の 16 要素の配列
	CMatrix(const GLfloat* a);

	// 行列の要素を右辺値として参照する
	const GLfloat& operator[](std::size_t i) const;

	// 行列の要素を左辺値として参照する
	GLfloat& operator[](std::size_t i);

	// 変換行列の配列を返す
	const GLfloat* Data() const;

	// 法線ベクトルの変換行列を求める
	void getNormalMatrix(GLfloat* aM) const;

	// 単位行列を設定する
	void LoadIdentity();
	
	// 単位行列を作成する
	static CMatrix Identity();

	// (x, y, z) だけ平行移動する変換行列を作成する
	static CMatrix Translate(const GLfloat aX, const GLfloat aY, const GLfloat aZ);

	// (x, y, z) 倍に拡大縮小する変換行列を作成する
	static CMatrix Scale(const GLfloat aX, const GLfloat aY,const GLfloat aZ);

	// (x, y, z) を軸に a 回転する変換行列を作成する
	static CMatrix Rotate(const GLfloat aA, const GLfloat aX, const GLfloat aY, const GLfloat aZ);

	// 乗算
	CMatrix operator*(const CMatrix& aMatrix) const;

	// ビュー変換行列を作成する
	static CMatrix LookAt(GLfloat aEx, GLfloat aEy, GLfloat aEz,  // 視点の位置
						  GLfloat aGx, GLfloat aGy, GLfloat aGz,  // 目標点の位置
						  GLfloat aUx, GLfloat aUy, GLfloat aUz); // 上方向のベクトル

	static CMatrix Orthogonal(GLfloat aLeft, GLfloat aRight,
							  GLfloat aBottom, GLfloat aTop,
							  GLfloat aZNear, GLfloat aZFar);

	static CMatrix Frustum(GLfloat aLeft, GLfloat aRight,
						   GLfloat aBottom, GLfloat atop,
						   GLfloat aZNear, GLfloat aZFar);

	static CMatrix Perspective(GLfloat aFovy, GLfloat aAspect, GLfloat aZNear, GLfloat aZFar);

private:
	GLfloat mMatrix[16];

};