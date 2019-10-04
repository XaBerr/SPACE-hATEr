#include "myMath.h"

#ifndef _myPipeline
#define _myPipeline 1

class myPipeline
{
	public:
		myPipeline();

		void scale(float ScaleX, float ScaleY, float ScaleZ);
		void rotate(float RotateX, float RotateY, float RotateZ);
		void identity();
		
		void worldPos(float x, float y, float z);
		void setPerspectiveProj(float FOV, float Width, float Height, float zNear, float zFar);
		void setCamera(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up);

		const Matrix4f& getWVPTrans();
		const Matrix4f& getWorldTrans();

	private:
		Vector3f mScale;
		Vector3f mWorldPos;
		Vector3f mRotateInfo;
		Matrix4f mWVPtransformation;
		Matrix4f mWorldTransformation;

		struct 
		{
			float FOV;
			float Width;
			float Height;
			float zNear;
			float zFar;
		} mPersProj;

		struct 
		{
			Vector3f Pos;
			Vector3f Target;
			Vector3f Up;
		} mCamera;

	
};

#endif // !_myPipeline
