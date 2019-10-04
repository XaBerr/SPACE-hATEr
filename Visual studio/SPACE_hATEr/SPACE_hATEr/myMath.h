#ifndef _myMath
#define	_myMath 1

#include <stdio.h>
#ifdef WIN32
#define _USE_MATH_DEFINES 
#include <cmath>
#else
#include <math.h>
#endif

#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /* pi */
#endif

#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

struct Vector2i
{
	int x;
	int y;
};

struct Vector2f
{
	float x;
	float y;

	Vector2f()
	{
	}

	Vector2f(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};


struct Vector3f
{
	float x;
	float y;
	float z;

	Vector3f()
	{
	}

	Vector3f(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f& operator+=(const Vector3f& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}

	Vector3f& operator-=(const Vector3f& r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;

		return *this;
	}

	Vector3f& operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	Vector3f cross(const Vector3f& v) const;

	Vector3f& normalize();

	void rotate(float Angle, const Vector3f& Axis);

	void Print() const
	{
		printf("(%.02f, %.02f, %.02f", x, y, z);
	}
};


inline Vector3f operator+(const Vector3f& l, const Vector3f& r)
{
	Vector3f Ret(l.x + r.x,
				 l.y + r.y,
				 l.z + r.z);

	return Ret;
}

inline Vector3f operator-(const Vector3f& l, const Vector3f& r)
{
	Vector3f Ret(l.x - r.x,
				 l.y - r.y,
				 l.z - r.z);

	return Ret;
}

inline Vector3f operator*(const Vector3f& l, float f)
{
	Vector3f Ret(l.x * f,
				 l.y * f,
				 l.z * f);

	return Ret;
}

struct Vector4f
{
	float x;
	float y;
	float z;
	float w;
};

struct Vector4i
{
	int x;
	int y;
	int z;
	int w;
};

class Matrix4f
{
	public:
		float m[4][4];

		Matrix4f()
		{
		}


		inline void identity()
		{
			m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
			m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
			m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
			m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
		}

		inline Matrix4f operator*(const Matrix4f& Right) const
		{
			Matrix4f Ret;

			for (unsigned int i = 0; i < 4; i++)
				for (unsigned int j = 0; j < 4; j++)
				{
					Ret.m[i][j] = m[i][0] * Right.m[0][j] +
						m[i][1] * Right.m[1][j] +
						m[i][2] * Right.m[2][j] +
						m[i][3] * Right.m[3][j];
				}
		

			return Ret;
		}

		void scale(float ScaleX, float ScaleY, float ScaleZ);
		void rotate(float RotateX, float RotateY, float RotateZ);
		void translation(float x, float y, float z);
		void cameraTransform(const Vector3f& Target, const Vector3f& Up);
		void persProjTransform(float FOV, float Width, float Height, float zNear, float zFar);
};


struct Quaternion
{
	float x, y, z, w;

	Quaternion(float _x, float _y, float _z, float _w);

	void normalize();

	Quaternion conjugate();
};

Quaternion operator*(const Quaternion& l, const Quaternion& r);

Quaternion operator*(const Quaternion& q, const Vector3f& v);

struct Vertex
{
	Vector3f mPos;
	Vector2f mTex;
	Vector3f mNormal;

	Vertex() {}

	Vertex(Vector3f pos, Vector2f tex)
	{
		mPos = pos;
		mTex = tex;
	}

	Vertex(Vector3f pos, Vector2f tex, Vector3f normal)
	{
		mPos = pos;
		mTex = tex;
		mNormal = normal;
	}

	void init(Vector3f pos, Vector2f tex)
	{
		mPos = pos;
		mTex = tex;
	}

	
};

Vector3f gui(Vector3f x);

#endif // !_myMath