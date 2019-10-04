#include "myPipeline.h"


myPipeline::myPipeline()
{
	mScale = Vector3f(1.0f, 1.0f, 1.0f);
	mWorldPos = Vector3f(0.0f, 0.0f, 0.0f);
	mRotateInfo = Vector3f(0.0f, 0.0f, 0.0f);
}

void myPipeline::identity()
{
	mScale = Vector3f(1.0f, 1.0f, 1.0f);
	mWorldPos = Vector3f(0.0f, 0.0f, 0.0f);
	mRotateInfo = Vector3f(0.0f, 0.0f, 0.0f);
}

void myPipeline::scale(float ScaleX, float ScaleY, float ScaleZ)
{
	mScale.x = ScaleX;
	mScale.y = ScaleY;
	mScale.z = ScaleZ;
}

void myPipeline::worldPos(float x, float y, float z)
{
	mWorldPos.x = x;
	mWorldPos.y = y;
	mWorldPos.z = z;
}

void myPipeline::rotate(float RotateX, float RotateY, float RotateZ)
{
	mRotateInfo.x = RotateX;
	mRotateInfo.y = RotateY;
	mRotateInfo.z = RotateZ;
}

void myPipeline::setPerspectiveProj(float FOV, float Width, float Height, float zNear, float zFar)
{
	mPersProj.FOV = FOV;
	mPersProj.Width = Width;
	mPersProj.Height = Height;
	mPersProj.zNear = zNear;
	mPersProj.zFar = zFar;
}

void myPipeline::setCamera(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up)
{
	mCamera.Pos = Pos;
	mCamera.Target = Target;
	mCamera.Up = Up;
}

const Matrix4f& myPipeline::getWorldTrans()
{
	Matrix4f ScaleTrans, RotateTrans, TranslationTrans;

	ScaleTrans.scale(mScale.x, mScale.y, mScale.z);
	RotateTrans.rotate(mRotateInfo.x, mRotateInfo.y, mRotateInfo.z);
	TranslationTrans.translation(mWorldPos.x, mWorldPos.y, mWorldPos.z);

	mWorldTransformation = TranslationTrans * RotateTrans * ScaleTrans;
	return mWorldTransformation;
}

const Matrix4f& myPipeline::getWVPTrans()
{
	getWorldTrans();

	Matrix4f CameraTranslationTrans, CameraRotateTrans, PersProjTrans;

	CameraTranslationTrans.translation(-mCamera.Pos.x, -mCamera.Pos.y, -mCamera.Pos.z);
	CameraRotateTrans.cameraTransform(mCamera.Target, mCamera.Up);
	PersProjTrans.persProjTransform(mPersProj.FOV, mPersProj.Width, mPersProj.Height, mPersProj.zNear, mPersProj.zFar);

	mWVPtransformation = PersProjTrans * CameraRotateTrans * CameraTranslationTrans * mWorldTransformation;
	return mWVPtransformation;
}
