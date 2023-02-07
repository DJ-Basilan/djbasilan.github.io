#ifndef __PT_LIGHT__
#define __PT_LIGHT__

#include "../../toolkit/toolkit.h"

class ptLight {

public:

	// Colour
	Vector3 m_colour = Vector3(1, 1, 1);

	// Direction and Position
	float x_position = 0;
	float y_position = 6.5;
	float z_position = -12;
	Vector3 m_locationVx = Vector3(x_position, y_position, z_position);		// Default position is just above the 'Sun'

	Vector3 m_directionVx = Vector3(0, -1, 0);		// Spotlight points down by default

	// ADS Components
	float m_ambientFactor = 0.5;
	float m_diffuseFactor = 0.9;
	float m_specularFactor = 0.8;

	// Distance Attenuation
	float m_fixedAttnFactor = 0.7;
	float m_linearAttnFactor = 1.5;
	float m_quadAttnFactor = 1.0;

	// Angle Attenuation
	float m_spotAngleCos = 0.885;		// Smaller value = wider spotlight

	// Flags
	bool m_isInfinite = false;
	bool m_isDirectional = false;
	bool m_isOn = false;		// Light switch
	bool m_useDistanceAttn = false;


	// Light source movement...
	// Left/Right - X-Axis
	void trackLeftRight(float _amount)
	{
		x_position -= _amount;
		m_locationVx = Vector3(x_position, y_position, z_position);
	}//trackLeftRight()

	// Up/Down - Y-Axis
	void trackUpDown(float _amount)
	{
		y_position -= _amount;
		m_locationVx = Vector3(x_position, y_position, z_position);
	}//trackUpDown()

	// Forward/Backward - Z-Axis
	void trackForwardBack(float _amount)
	{
		z_position -= _amount;
		m_locationVx = Vector3(x_position, y_position, z_position);
	}//trackForwardBack()

	// Spotlight focus
	void spotLightFocus(float _amount)
	{
		//float total += _amount;

		if (m_spotAngleCos > 1) m_spotAngleCos = 0.999;
		if (m_spotAngleCos < 0) m_spotAngleCos = 0.001;
		m_spotAngleCos += _amount;
	}

	void resetPosition()
	{
		x_position = 0;
		y_position = 6.5;
		z_position = -12;
		m_locationVx = Vector3(x_position, y_position, z_position);
	}
};

#endif // !__PT_LIGHT__
