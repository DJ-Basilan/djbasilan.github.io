#ifndef __PT_CAMERA__
#define __PT_CAMERA__

#include "../../toolkit/toolkit.h"
//#include <vectormath.h>
// The 'include' above should be <vectormath.h> according to Tutorial 11-B1 since it
// apparently has the Matrix4 datatype, but it is not explained how to actually extract it...
// Upon checking the declaration of Matrix4, it in fact comes from 'geommath.h'
// which is already built-in to the project (I think) and it doesn't need to be included.
// However, after trying the different 'includes' from Main.cpp in this file, it was found
// that 'toolkit.h' allowed Matrix4 to be defined here because that header also includes
// 'geommath.h'


class ptCamera
{

public:

	Matrix4 m_projectionMx;
	Matrix4 m_worldViewMx;

	float angle = 0;
	float aspectRatio = 0;
	float zNear = 0;
	float zFar = 0;


	// Self-explanatory
	void setPerspective(float _angle, float _aspectRatio, float _zNear, float _zFar)
	{
		angle = _angle;
		aspectRatio = _aspectRatio;
		zNear = _zNear;
		zFar = _zFar;

		m_projectionMx = Matrix4::perspective(angle, aspectRatio, zNear, zFar);
		m_worldViewMx = Matrix4::identity();
	}


	// For Camera movement...
	// Left/Right - X-Axis
	void trackLeftRight(float _amount)
	{
		m_worldViewMx = Matrix4::translation(Vector3(-_amount, 0.0, 0.0)) * m_worldViewMx;
	}//trackLeftRight()

	// Up/Down - Y-Axis
	void trackUpDown(float _amount)
	{
		m_worldViewMx = Matrix4::translation(Vector3(0.0, -_amount, 0.0)) * m_worldViewMx;
	}//trackUpDown()

	// Forward/Backward - Z-Axis
	void trackForwardBack(float _amount)
	{
		m_worldViewMx = Matrix4::translation(Vector3(0.0, 0.0, -_amount)) * m_worldViewMx;
	}//trackForwardBack()


	// For Camera rotation...
	// Yaw - Y-Axis
	void trackYaw(float _amount)
	{
		m_worldViewMx = Matrix4::rotationY(_amount) * m_worldViewMx;
	}//trackYaw()

	// Pitch - X-Axis
	void trackPitch(float _amount)
	{
		m_worldViewMx = Matrix4::rotationX(_amount) * m_worldViewMx;
	}//trackPitch()

	// Roll - Z-Axis
	void trackRoll(float _amount)
	{
		m_worldViewMx = Matrix4::rotationZ(-_amount) * m_worldViewMx;
	}//trackRoll()


	// Reset camera
	void resetCam()
	{
		m_worldViewMx = Matrix4::identity();
	}


	// Setters to allow Main.cpp to interact with the values
	void setAngle(float _angle)
	{
		angle += _angle;
		m_projectionMx = Matrix4::perspective(angle, aspectRatio, zNear, zFar);
	}

	void setAspectRatio(float _aspectRatio)
	{
		aspectRatio += _aspectRatio;
		m_projectionMx = Matrix4::perspective(angle, aspectRatio, zNear, zFar);
	}

	void setZNear(float _zNear)
	{
		zNear += _zNear;
		m_projectionMx = Matrix4::perspective(angle, aspectRatio, zNear, zFar);
	}

	void setZFar(float _zFar)
	{
		zFar += _zFar;
		m_projectionMx = Matrix4::perspective(angle, aspectRatio, zNear, zFar);
	}
};

#endif // !__PT_CAMERA__
