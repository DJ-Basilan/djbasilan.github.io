/* SIE CONFIDENTIAL
PlayStation(R)4 Programmer Tool Runtime Library Release 04.008.061
* Copyright (C) 2015 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/


#include <stdio.h>
#include <stdlib.h>
#include <scebase.h>
#include <kernel.h>
#include <gnmx.h>
#include <video_out.h>
#include "../../toolkit/toolkit.h"
#include "../../common/allocator.h"
#include "../../common/shader_loader.h"
#include "../../common/danGraphicsWrapper.h"

#include "ptVertex.h"			// Vertex Data Structs and Enums
#include "ptModel.h"			// The Models (PTM and OBJ)
#include "ptDrawManager.h"		// Draw Manager
#include "ptController.h"		// Controller (Dualshock)
#include "ptCamera.h"			// Handles Camera
#include "ptObject.h"			// Object Class
#include "ptAssetManager.h"		// Asset Manager Class
#include "ptLight.h"			// Lighting Class
#include "ptAssetType.h"		// Holds all Asset Enums
#include "ptHUDTextItem.h"		

using namespace sce;
using namespace sce::Gnmx;




// Added for convenience when adding and arranging models' positions
Matrix4 m_translationMatrix(double x, double y) { return Matrix4::translation(Vector3(x, y, -8)); }

// Flags to show if the specified buttons have been pressed
bool m_isCrossPressed = false;
bool m_isCirclePressed = false;
bool m_isTrianglePressed = false;
bool m_isSquarePressed = false;

bool m_isLeftPressed = false;
bool m_isRightPressed = false;
bool m_isUpPressed = false;
bool m_isDownPressed = false;

bool m_isR1Pressed = false;
bool m_isR2Pressed = false;
bool m_isR3Pressed = false;

bool m_isL1Pressed = false;
bool m_isL2Pressed = false;
bool m_isL3Pressed = false;

bool m_isOptionsPressed = false;

// Toggles based on the respective buttons
bool m_triangleToggle = false;
bool m_crossToggle = false;
bool m_circleToggle = false;
bool m_squareToggle = false;

bool m_upToggle = false;
bool m_downToggle = false;
bool m_leftToggle = false;
bool m_rightToggle = false;

bool m_R1Toggle = false;
bool m_R2Toggle = false;
bool m_R3Toggle = false;

bool m_L1Toggle = false;
bool m_L2Toggle = false;
bool m_L3Toggle = false;

bool m_optionsToggle = false;

ptController myController;		// Create a (PS4) controller object

// -------------------------------BUTTON TRIGGERS---------------------------------------
// Modified trigger for cross button press
bool allowCrossPress() {
	if (myController.crossPressed() && m_isCrossPressed == false) {
		m_isCrossPressed = true;
		return true;
	}
	else if (myController.crossPressed() && m_isCrossPressed == true) {
		return false;
	}
	else if (!myController.crossPressed()) {
		m_isCrossPressed = false;
		return false;
	}
	return false;
}

// Modified trigger for circle button press
bool allowCirclePress() {
	if (myController.circlePressed() && m_isCirclePressed == false) {
		m_isCirclePressed = true;
		return true;
	}
	else if (myController.circlePressed() && m_isCirclePressed == true) {
		return false;
	}
	else if (!myController.circlePressed()) {
		m_isCirclePressed = false;
		return false;
	}
	return false;
}

// Modified trigger for triangle button press
bool allowTrianglePress() {
	if (myController.trianglePressed() && m_isTrianglePressed == false) {
		m_isTrianglePressed = true;
		return true;
	}
	else if (myController.trianglePressed() && m_isTrianglePressed == true) {
		return false;
	}
	else if (!myController.trianglePressed()) {
		m_isTrianglePressed = false;
		return false;
	}
	return false;
}

// Modified trigger for square button press
bool allowSquarePress() {
	if (myController.squarePressed() && m_isSquarePressed == false) {
		m_isSquarePressed = true;
		return true;
	}
	else if (myController.squarePressed() && m_isSquarePressed == true) {
		return false;
	}
	else if (!myController.squarePressed()) {
		m_isSquarePressed = false;
		return false;
	}
	return false;
}

// Modified trigger for left button press
bool allowLeftPress() {
	if (myController.leftPressed() && m_isLeftPressed == false) {
		m_isLeftPressed = true;
		return true;
	}
	else if (myController.leftPressed() && m_isLeftPressed == true) {
		return false;
	}
	else if (!myController.leftPressed()) {
		m_isLeftPressed = false;
		return false;
	}
	return false;
}

// Modified trigger for right button press
bool allowRightPress() {
	if (myController.rightPressed() && m_isRightPressed == false) {
		m_isRightPressed = true;
		return true;
	}
	else if (myController.rightPressed() && m_isRightPressed == true) {
		return false;
	}
	else if (!myController.rightPressed()) {
		m_isRightPressed = false;
		return false;
	}
	return false;
}

// Modified trigger for up button press
bool allowUpPress() {
	if (myController.upPressed() && m_isUpPressed == false) {
		m_isUpPressed = true;
		return true;
	}
	else if (myController.upPressed() && m_isUpPressed == true) {
		return false;
	}
	else if (!myController.upPressed()) {
		m_isUpPressed = false;
		return false;
	}
	return false;
}

// Modified trigger for down button press
bool allowDownPress() {
	if (myController.downPressed() && m_isDownPressed == false) {
		m_isDownPressed = true;
		return true;
	}
	else if (myController.downPressed() && m_isDownPressed == true) {
		return false;
	}
	else if (!myController.downPressed()) {
		m_isDownPressed = false;
		return false;
	}
	return false;
}

// Modified trigger for R1 button press
bool allowR1Press() {
	if (myController.R1Pressed() && m_isR1Pressed == false) {
		m_isR1Pressed = true;
		return true;
	}
	else if (myController.R1Pressed() && m_isR1Pressed == true) {
		return false;
	}
	else if (!myController.R1Pressed()) {
		m_isR1Pressed = false;
		return false;
	}
	return false;
}

// Modified trigger for R2 button press
bool allowR2Press() {
	if (myController.R2Pressed() && m_isR2Pressed == false) {
		m_isR2Pressed = true;
		return true;
	}
	else if (myController.R2Pressed() && m_isR2Pressed == true) {
		return false;
	}
	else if (!myController.R2Pressed()) {
		m_isR2Pressed = false;
		return false;
	}
	return false;
}

// Modified trigger for R3 button press
bool allowR3Press() {
	if (myController.R3Pressed() && m_isR3Pressed == false) {
		m_isR3Pressed = true;
		return true;
	}
	else if (myController.R3Pressed() && m_isR3Pressed == true) {
		return false;
	}
	else if (!myController.R3Pressed()) {
		m_isR3Pressed = false;
		return false;
	}
	return false;
}

// Modified trigger for L1 button press
bool allowL1Press() {
	if (myController.L1Pressed() && m_isL1Pressed == false) {
		m_isL1Pressed = true;
		return true;
	}
	else if (myController.L1Pressed() && m_isL1Pressed == true) {
		return false;
	}
	else if (!myController.L1Pressed()) {
		m_isL1Pressed = false;
		return false;
	}
	return false;
}

// Modified trigger for L2 button press
bool allowL2Press() {
	if (myController.L2Pressed() && m_isL2Pressed == false) {
		m_isL2Pressed = true;
		return true;
	}
	else if (myController.L2Pressed() && m_isL2Pressed == true) {
		return false;
	}
	else if (!myController.L2Pressed()) {
		m_isL2Pressed = false;
		return false;
	}
	return false;
}

// Modified trigger for L3 button press
bool allowL3Press() {
	if (myController.L3Pressed() && m_isL3Pressed == false) {
		m_isL2Pressed = true;
		return true;
	}
	else if (myController.L3Pressed() && m_isL3Pressed == true) {
		return false;
	}
	else if (!myController.L3Pressed()) {
		m_isL2Pressed = false;
		return false;
	}
	return false;
}

// Modified trigger for Options button press
bool allowOptionsPress() {
	if (myController.optionsPressed() && m_isOptionsPressed == false) {
		m_isOptionsPressed = true;
		return true;
	}
	else if (myController.optionsPressed() && m_isOptionsPressed == true) {
		return false;
	}
	else if (!myController.optionsPressed()) {
		m_isOptionsPressed = false;
		return false;
	}
	return false;
}
// -------------------------------END BUTTON TRIGGERS---------------------------------------


// -------------------------------BUTTON TOGGLES---------------------------------------
// Toggle function for triangle button
bool triangleToggle() {
	if(allowTrianglePress()) {
		m_triangleToggle = !m_triangleToggle;
	}
	if (m_triangleToggle == false) { return false; }
	else if (m_triangleToggle == true) { return true; }

	return false;
}

// Toggle function for cross button
bool crossToggle() {
	if (allowCrossPress()) {
		m_crossToggle = !m_crossToggle;
	}
	if (m_crossToggle == false) { return false; }
	else if (m_crossToggle == true) { return true; }

	return false;
}

// Toggle function for circle button
bool circleToggle() {
	if (allowCirclePress()) {
		m_circleToggle = !m_circleToggle;
	}
	if (m_circleToggle == false) { return false; }
	else if (m_circleToggle == true) { return true; }

	return false;
}

// Toggle function for square button
bool squareToggle() {
	if (allowSquarePress()) {
		m_squareToggle = !m_squareToggle;
	}
	if (m_squareToggle == false) { return false; }
	else if (m_squareToggle == true) { return true; }

	return false;
}

// Toggle function for up button
bool upToggle() {
	if (allowUpPress()) {
		m_upToggle = !m_upToggle;
	}
	if (m_upToggle == false) { return false; }
	else if (m_upToggle == true) { return true; }

	return false;
}

// Toggle function for down button
bool downToggle() {
	if (allowDownPress()) {
		m_downToggle = !m_downToggle;
	}
	if (m_downToggle == false) { return false; }
	else if (m_downToggle == true) { return true; }

	return false;
}

// Toggle function for left button
bool leftToggle() {
	if (allowLeftPress()) {
		m_leftToggle = !m_leftToggle;
	}
	if (m_leftToggle == false) { return false; }
	else if (m_leftToggle == true) { return true; }

	return false;
}

// Toggle function for right button
bool rightToggle() {
	if (allowRightPress()) {
		m_rightToggle = !m_rightToggle;
	}
	if (m_rightToggle == false) { return false; }
	else if (m_rightToggle == true) { return true; }

	return false;
}

// Toggle function for R1 button
bool R1Toggle() {
	if (allowR1Press()) {
		m_R1Toggle = !m_R1Toggle;
	}
	if (m_R1Toggle == false) { return false; }
	else if (m_R1Toggle == true) { return true; }

	return false;
}

// Toggle function for R2 button
bool R2Toggle() {
	if (allowR2Press()) {
		m_R2Toggle = !m_R2Toggle;
	}
	if (m_R2Toggle == false) { return false; }
	else if (m_R2Toggle == true) { return true; }

	return false;
}

// Toggle function for R2 button
bool R3Toggle() {
	if (allowR3Press()) {
		m_R3Toggle = !m_R3Toggle;
	}
	if (m_R3Toggle == false) { return false; }
	else if (m_R3Toggle == true) { return true; }

	return false;
}

// Toggle function for L1 button
bool L1Toggle() {
	if (allowL1Press()) {
		m_L1Toggle = !m_L1Toggle;
	}
	if (m_L1Toggle == false) { return false; }
	else if (m_L1Toggle == true) { return true; }

	return false;
}

// Toggle function for L2 button
bool L2Toggle() {
	if (allowL2Press()) {
		m_L2Toggle = !m_L2Toggle;
	}
	if (m_L2Toggle == false) { return false; }
	else if (m_L2Toggle == true) { return true; }

	return false;
}

// Toggle function for L2 button
bool L3Toggle() {
	if (allowL3Press()) {
		m_L3Toggle = !m_L3Toggle;
	}
	if (m_L3Toggle == false) { return false; }
	else if (m_L3Toggle == true) { return true; }

	return false;
}

// Toggle function for Options button
bool optionsToggle() {
	if (allowOptionsPress()) {
		m_optionsToggle = !m_optionsToggle;
	}
	if (m_optionsToggle == false) { return false; }
	else if (m_optionsToggle == true) { return true; }

	return false;
}
// -------------------------------END BUTTON TOGGLES---------------------------------------

// Resets all flags to FALSE
void allFlagsOff() {
	
	m_isCrossPressed = false;
	m_isCirclePressed = false;
	m_isTrianglePressed = false;
	m_isSquarePressed = false;
	m_isLeftPressed = false;
	m_isRightPressed = false;
	m_isUpPressed = false;
	m_isDownPressed = false;
	m_isR1Pressed = false;
	m_isR2Pressed = false;
	m_isL1Pressed = false;
	m_isL2Pressed = false;
	m_isOptionsPressed = false;

	m_triangleToggle = false;
	m_crossToggle = false;
	m_circleToggle = false;
	m_squareToggle = false;
	m_upToggle = false;
	m_downToggle = false;
	m_leftToggle = false;
	m_rightToggle = false;
	m_R1Toggle = false;
	m_R2Toggle = false;
	m_L1Toggle = false;
	m_L2Toggle = false;
	m_optionsToggle = false;
}

// Same as above but for cross button only - To prevent the program from spamming the model data in the console
void crossFlagsOff() {
	m_isCrossPressed = false;
	m_crossToggle = false;
}


// -------------------------------THUMBSTICKS---------------------------------------
const uint8_t m_stickOffset = 128;	// Monitors thumbstick movement
const float m_stickDeadZone = 9 / m_stickOffset;

// Accessor methods for the LEFT Thumbstick
float leftStickX() {	// Check for movement along X-axis
	float leftX = myController.m_padState.leftStick.x;
	leftX -= m_stickOffset;
	leftX /= m_stickOffset;
	if (leftX >= -m_stickDeadZone && leftX <= m_stickDeadZone) {
		leftX = 0;
	}
	return leftX / 18;
}
float leftStickY() {	// Check for movement along Y-axis
	float leftY = myController.m_padState.leftStick.y;
	leftY -= m_stickOffset;
	leftY /= m_stickOffset;
	if (leftY >= -m_stickDeadZone && leftY <= m_stickDeadZone) {
		leftY = 0;
	}
	return leftY / 18;
}
// END LEFT Thumbstick

// Accessor methods for the RIGHT Thumbstick
float rightStickX() {	// Check for movement along X-axis
	float rightX = myController.m_padState.rightStick.x;
	rightX -= m_stickOffset;
	rightX /= m_stickOffset;
	if (rightX >= -m_stickDeadZone && rightX <= m_stickDeadZone) {
		rightX = 0;
	}
	return rightX / 50;
}
float rightStickY() {	// Check for movement along Y-axis
	float rightY = myController.m_padState.rightStick.y;
	rightY -= m_stickOffset;
	rightY /= m_stickOffset;
	if (rightY >= -m_stickDeadZone && rightY <= m_stickDeadZone) {
		rightY = 0;
	}
	return rightY / 50;
}
// END RIGHT Thumbstick
// -------------------------------END THUMBSTICKS---------------------------------------


// Enum for text rows and number items for the HUD
enum ptHUDItemEnum
{
	// Top-left corner
	PT_HUD_ITEM_SCORE,
	PT_HUD_ITEM_SCORE_NUM,
	PT_HUD_ITEM_OBJECTIVE,
	PT_HUD_ITEM_TARGET,

	// Top-middle
	PT_HUD_ITEM_OBJECTIVE_COMPLETE,
	PT_HUD_ITEM_GAME_START_MESSAGE,

	// Top-right corner
	PT_HUD_ITEM_CURRENT_CAM,
	PT_HUD_ITEM_CURRENT_CAM_NUM,

	// Bottom-left corner
	PT_HUD_ITEM_CONTROLS_HEADER,

	PT_HUD_ITEM_CAM_ELEVATION,			// L3 and R3
	PT_HUD_ITEM_CAM_MOVE,				// Left stick
	PT_HUD_ITEM_CAM_LOOK,				// Right stick
	PT_HUD_ITEM_CAM_ROLL,				// L1 and R1

	PT_HUD_ITEM_LIGHT_ELEVATION,		// L2 and R2
	PT_HUD_ITEM_LIGHT_MOVEMENT,			// D-Pad

	PT_HUD_ITEM_SWITCH_CAM_INFO,		// Triangle and Circle
	PT_HUD_ITEM_SPOTLIGHT_MODE_INFO,	// Square
	PT_HUD_ITEM_CONFIRM_OBJECT_INFO,	// Cross

	PT_HUD_ITEM_COUNT
};


// Enum for objectives
enum objectivesEnum
{
	OBJECTIVE_AIRPLANE,
	OBJECTIVE_SKYSCRAPER,
	OBJECTIVE_TEAPOT,
	OBJECTIVE_SOLAR_SYSTEM,
	OBJECTIVE_VIOLIN,
	OBJECTIVE_FLOWER,
	OBJECTIVE_BRICK,
	OBJECTIVE_GEM,

	OBJECTIVE_COUNT
};


// Method for comparing the positions of the light source and the objective
bool checkDistance(Vector3 _lightVx, Vector3 _objectiveVx)
{
	// Check X-axis distance - Range is between 0 and 5
	// Calculate distance
	float x_result = _objectiveVx.getX() - _lightVx.getX();
	float y_result = _objectiveVx.getY() + _lightVx.getY();
	float z_result = _objectiveVx.getZ() - _lightVx.getZ();

	// Convert from negative to positive
	if (x_result < 0) x_result = x_result * -1;
	if (z_result < 0) z_result = z_result * -1;

	// Confirm distance
	if (x_result > 6.0 || y_result < 2.5 || z_result > 6.0)
	{
		return false;
	}

	return true;
}


// Main method
int main(int _argc, const char* _argv[])
{
	//define the size of our memory heaps
	static const size_t sc_onionMemorySize = 16 * 1024 * 1024;
	static const size_t sc_garlicMemorySize = 64 * 4 * 1024 * 1024;


	// Make a Dualshock controller instance
	myController.initialise();


	// Little check to see if things are working
	printf("Hello World!\n");


	// Utility for error messages
	int l_error;

	// there are several types of memory access available, but we need to do our own memory management
	// the three main types are "CPU" (which is used automatically) "Onion" for larger CPU use and "Garlic" for GPU use
	// Initialize the WB_ONION memory allocator
	LinearAllocator myOnionAllocator;
	// [REDACTED]
	if (l_error != SCE_OK) { printf("Onion allocator failed to initialise: 0x%08X\n", l_error);  return l_error; }

	// Initialize the WC_GARLIC memory allocator
	// NOTE: CPU reads from GARLIC write-combined memory have a very low
	//       bandwidth so they are disabled for safety in this sample
	LinearAllocator myGarlicAllocator;
	// [REDACTED]
	if (l_error != SCE_OK) { printf("Garlic allocator failed to initialise: 0x%08X\n", l_error);  return l_error; }

	// We are using three wrappers to the hardware provided by Sony
	// "Gnm" is their low-level graphics API
	// On top of this they provide "Gnmx" with higher level functionality
	// Both Gnm and Gnmx are accessed through libraries and are part of the standard SCE API
	// There is also "toolkit" which was developed for their sample programs
	// This adds yet more abstraction above Gnm and Gnmx
	// However, it is not part of the standard API and so including it in projects is a little cumbersome
	// Sony advise it is not fit for use in release mode games.

	// Initialize the Toolkit module
	// [REDACTED]

	// Finally, there is a fourth layer of wrapper, the danGraphicsWrapper
	// this is provided by Dan Hodgson for use for students with his tutor series
	// It abstracts away a whole load of hardware stuff including render contexts, video surfaces and concurrency
	danGraphicsWrapper myGraphicsWrapper;
	l_error = myGraphicsWrapper.init(&myOnionAllocator, &myGarlicAllocator);
	if (l_error != SCE_OK) { printf("Graphics Wrapper failed to init: 0x%08X\n", l_error);  return l_error; }


	//// ------------------------------ END Models and Objects ------------------------------

	// Initialise the Asset Manager
	ptAssetManager myAssetManager;
	myAssetManager.init(&myGarlicAllocator, &myToolkitAllocators);
	ptObject myObjects[PT_OBJECT_COUNT];

	// --- Light Source
	//myObjects[PT_OBJECT_LAMP].m_myModel = myAssetManager.getModel(OBJ_MODEL_LAMP);
	//myObjects[PT_OBJECT_LAMP].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_VERT_COL_GOLD);


	// --- Directional indicators
	myObjects[PT_OBJECT_ARROW_FRONT].m_myModel = myAssetManager.getModel(PTM_MODEL_OCTA_SPLIT_NC);
	myObjects[PT_OBJECT_ARROW_FRONT].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_VERT_COL_MATTE);

	myObjects[PT_OBJECT_ARROW_BACK].m_myModel = myAssetManager.getModel(PTM_MODEL_OCTA_SPLIT_NC);
	myObjects[PT_OBJECT_ARROW_BACK].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_VERT_COL_MATTE);

	myObjects[PT_OBJECT_ARROW_LEFT].m_myModel = myAssetManager.getModel(PTM_MODEL_OCTA_SPLIT_NC);
	myObjects[PT_OBJECT_ARROW_LEFT].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_VERT_COL_MATTE);

	myObjects[PT_OBJECT_ARROW_RIGHT].m_myModel = myAssetManager.getModel(PTM_MODEL_OCTA_SPLIT_NC);
	myObjects[PT_OBJECT_ARROW_RIGHT].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_VERT_COL_MATTE);
	// --- END Directional indicators

	// --- Ground
	myObjects[PT_OBJECT_GROUND].m_myModel = myAssetManager.getModel(PTM_MODEL_FLOOR);
	myObjects[PT_OBJECT_GROUND].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_WOOD);

	//// --- Grass Floor
	myObjects[PT_OBJECT_GRASS_FLOOR].m_myModel = myAssetManager.getModel(PTM_MODEL_FLOOR);
	myObjects[PT_OBJECT_GRASS_FLOOR].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_GRASS);

	// --- Cow
	myObjects[PT_OBJECT_TEAPOT].m_myModel = myAssetManager.getModel(PTM_MODEL_TEAPOT);
	myObjects[PT_OBJECT_TEAPOT].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_COW_TEAPOT);

	// --- Airplane
	myObjects[PT_OBJECT_AIRPLANE].m_myModel = myAssetManager.getModel(OBJ_MODEL_CESSNA);
	myObjects[PT_OBJECT_AIRPLANE].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_VERT_COL_GOLD);

	// --- Brick Block
	myObjects[PT_OBJECT_BRICK_BLOCK].m_myModel = myAssetManager.getModel(PTM_MODEL_CUBE_SPLIT_NC);
	myObjects[PT_OBJECT_BRICK_BLOCK].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_BRICK);

	// --- Emerald Gem
	myObjects[PT_OBJECT_GEM].m_myModel = myAssetManager.getModel(OBJ_MODEL_ICOS);
	myObjects[PT_OBJECT_GEM].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_VERT_COL_EMERALD);

	// --- Skyscraper
	myObjects[PT_OBJECT_SKYSCRAPER].m_myModel = myAssetManager.getModel(OBJ_MODEL_SKYSCRAPER);
	myObjects[PT_OBJECT_SKYSCRAPER].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_VERT_COL_CHROME);

	// --- Violin
	myObjects[PT_OBJECT_VIOLIN_CASE].m_myModel = myAssetManager.getModel(OBJ_MODEL_VIOLIN_CASE);
	myObjects[PT_OBJECT_VIOLIN_CASE].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_VERT_COL_BRASS);

	// --- Flower
	myObjects[PT_OBJECT_FLOWER].m_myModel = myAssetManager.getModel(OBJ_MODEL_MAGNOLIA);
	myObjects[PT_OBJECT_FLOWER].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_VERT_COL_RUBY);


	// Solar System ---------------------------------------------------------------------------
	// --- Sun
	myObjects[PT_OBJECT_SUN].m_myModel = myAssetManager.getModel(PTM_MODEL_SPHERE);
	myObjects[PT_OBJECT_SUN].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_SUN);

	// --- Mercury
	myObjects[PT_OBJECT_MERCURY].m_myModel = myAssetManager.getModel(PTM_MODEL_SPHERE);
	myObjects[PT_OBJECT_MERCURY].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_MERCURY);

	// --- Earth
	myObjects[PT_OBJECT_EARTH].m_myModel = myAssetManager.getModel(PTM_MODEL_SPHERE);
	myObjects[PT_OBJECT_EARTH].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_EARTH);

	// --- Moon
	myObjects[PT_OBJECT_MOON].m_myModel = myAssetManager.getModel(PTM_MODEL_SPHERE);
	myObjects[PT_OBJECT_MOON].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_MOON);

	// --- Pluto
	myObjects[PT_OBJECT_PLUTO].m_myModel = myAssetManager.getModel(PTM_MODEL_SPHERE);
	myObjects[PT_OBJECT_PLUTO].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_PLUTO);

	// --- Comet
	myObjects[PT_OBJECT_COMET].m_myModel = myAssetManager.getModel(PTM_MODEL_TEDDY);
	myObjects[PT_OBJECT_COMET].m_myMaterial = myAssetManager.getMaterial(PT_MATERIAL_TEDDY);
	// END Solar System -----------------------------------------------------------------------

	// Object Positions -----------------------------------------------------------------------
	float lamp_x = 0;
	float lamp_y = 5;
	float lamp_z = -12;
	Vector3 lampPosVx = Vector3(lamp_x, lamp_y, lamp_z);

	Vector3 lampFrontVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z - 1);
	Vector3 lampBackVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z + 1);
	Vector3 lampLeftVx = Vector3(lamp_x - 1, lamp_y - 0.8, lamp_z);
	Vector3 lampRightVx = Vector3(lamp_x + 1, lamp_y - 0.8, lamp_z);

	Vector3 groundPosVx = Vector3(0, -9, 0);

	// Objectives objects
	Vector3 objectivesPosVx[OBJECTIVE_COUNT];

	objectivesPosVx[OBJECTIVE_AIRPLANE] = Vector3(-40, -0.5, 10);
	objectivesPosVx[OBJECTIVE_SKYSCRAPER] = Vector3(-45, -3.9, -45);
	objectivesPosVx[OBJECTIVE_TEAPOT] = Vector3(30, -8, -5);
	objectivesPosVx[OBJECTIVE_SOLAR_SYSTEM] = Vector3(0, 0, -12);
	objectivesPosVx[OBJECTIVE_VIOLIN] = Vector3(43, -4, 28);
	objectivesPosVx[OBJECTIVE_FLOWER] = Vector3(-18.5, -4, 0);
	objectivesPosVx[OBJECTIVE_BRICK] = Vector3(42, -5, -40);
	objectivesPosVx[OBJECTIVE_GEM] = Vector3(-3, -6, 40);

	Vector3 grassFloorPos = Vector3(30, -8.9, -5);

	// Initialise the HUD Items
	ptHUDTextItem myHUDItems[PT_HUD_ITEM_COUNT];
	for (int i = 0; i < PT_HUD_ITEM_COUNT; i++)
	{
		myHUDItems[i].init(myAssetManager.getMaterial(PT_MATERIAL_HUD), &myGarlicAllocator);
	}

	// Set the text individually for the HUD items -----------------------------------------
	// Params - (String _text, float _scale, float _offsetX, float _offSetY)
	// NOTE: Offset boundaries are -1 to 1 for both X-axis and Y-axis

	// Top-left
	myHUDItems[PT_HUD_ITEM_SCORE].makeText("Score:", 1.7, -0.95, 0.95);
	myHUDItems[PT_HUD_ITEM_SCORE_NUM].makeNumText(0, 1.7, -0.83, 0.95);
	myHUDItems[PT_HUD_ITEM_OBJECTIVE].makeText("", 1.8, -0.95, 0.85);
	myHUDItems[PT_HUD_ITEM_TARGET].makeText("", 1.8, -0.95, 0.77);

	// Top-right
	myHUDItems[PT_HUD_ITEM_CURRENT_CAM].makeText("Current Camera:", 1.7, 0.5, 0.95);
	myHUDItems[PT_HUD_ITEM_CURRENT_CAM_NUM].makeText("Spotlight", 1.7, 0.79, 0.95);

	const char* camText[2];
	camText[0] = "Spotlight";
	camText[1] = "Free Cam";


	// Top-middle
	myHUDItems[PT_HUD_ITEM_OBJECTIVE_COMPLETE].makeText("", 2.5, -0.13, 0.85);
	myHUDItems[PT_HUD_ITEM_GAME_START_MESSAGE].makeText("Press X (Cross) to start the game", 2.5, -0.41, 0.75);

	// Bottom-left corner
	myHUDItems[PT_HUD_ITEM_CONTROLS_HEADER].makeText("--------- Controls ---------", 1.7, -0.95, -0.38);

	myHUDItems[PT_HUD_ITEM_CAM_ELEVATION].makeText("", 1.5, -0.95, -0.45);
	myHUDItems[PT_HUD_ITEM_CAM_MOVE].makeText("", 1.5, -0.95, -0.5);
	myHUDItems[PT_HUD_ITEM_CAM_LOOK].makeText("", 1.5, -0.95, -0.55);
	myHUDItems[PT_HUD_ITEM_CAM_ROLL].makeText("", 1.5, -0.95, -0.6);

	myHUDItems[PT_HUD_ITEM_LIGHT_ELEVATION].makeText("L2 / R2 : Spotlight Elevation", 1.5, -0.95, -0.65);
	myHUDItems[PT_HUD_ITEM_LIGHT_MOVEMENT].makeText("", 1.5, -0.95, -0.7);

	myHUDItems[PT_HUD_ITEM_SWITCH_CAM_INFO].makeText("Triangle / Circle : Switch Between Cameras", 1.5, -0.95, -0.75);
	myHUDItems[PT_HUD_ITEM_SPOTLIGHT_MODE_INFO].makeText("Square : Full Lighting for 2 seconds", 1.5, -0.95, -0.8);
	myHUDItems[PT_HUD_ITEM_CONFIRM_OBJECT_INFO].makeText("Cross : Confirm Target", 1.5, -0.95, -0.85);
	
	// Array for Objectives text
	const char* objectivesText[OBJECTIVE_COUNT];
	objectivesText[OBJECTIVE_AIRPLANE] = "The Golden Flying Vehicle";
	objectivesText[OBJECTIVE_SKYSCRAPER] = "The tallest object here";
	objectivesText[OBJECTIVE_TEAPOT] = "Milk Tea";
	objectivesText[OBJECTIVE_SOLAR_SYSTEM] = "The Solar System";
	objectivesText[OBJECTIVE_VIOLIN] = "A place to keep your Violin safe";
	objectivesText[OBJECTIVE_FLOWER] = "Red Blossom";
	objectivesText[OBJECTIVE_BRICK] = "A Building block";
	objectivesText[OBJECTIVE_GEM] = "Green, Shiny Rock";


	// Instantiate the draw manager
	ptDrawManager myDrawManager;


	// Solar System Angles - Orbits and Axial Rotations
	float sunAngle = 0;

	float mercuryOrbAngle = 0;
	float mercuryAxiAngle = 0;

	float earthOrbAngle = 0;
	float earthAxiAngle = 0;
	float earthOppOrbAngle = 0;
	
	float moonOrbAngle = 0;
	float moonAxiAngle = 0;

	float plutoOrbAngle = 0;
	float plutoOrbAngle2 = 0;
	float plutoAxiAngle = 0;
	float plutoAxiZAngle = 0;

	float cometOrbAngle = 0;
	float cometAxiAngle = 0;

	float brickAxiAngle = 0;

	float gemAxiAngle = 0;

	float violinAxiAngle = 0;

	float flowerAxiAngle = 0;

	// Light source
	//float lampAxiAngle = 0;
	float lampFrontAxiAngle = 0;
	float lampBackAxiAngle = 0;	
	float lampLeftAxiAngle = 0;
	float lampRightAxiAngle = 0;

	const float t_aspectRatio = float(myGraphicsWrapper.getBufferWidth()) / float(myGraphicsWrapper.getBufferHeight());

	ptCamera myCameras[2];
	myCameras[0].setPerspective(1.5f, t_aspectRatio, 0.001f, 100.0f);
	myCameras[0].m_worldViewMx = Matrix4::translation(Vector3(0.0, -7.5, 12.0));
	myCameras[0].m_worldViewMx = Matrix4::rotationX(1.5708) * myCameras[0].m_worldViewMx;

	myCameras[1].setPerspective(1.5f, t_aspectRatio, 0.001f, 100.0f);

	// Camera index counter
	int cam_cursor = 0;

	ptLight myLight;

	// Configure the light
	myLight.m_colour = Vector3(1, 1, 1);
	myLight.m_isDirectional = true;
	myLight.m_isInfinite = false;
	myLight.m_useDistanceAttn = true;
	myLight.m_isOn = true;

	// Used to count frames for the 'Objective Complete' text
	bool countFrames4Text = false;
	int frameCnt4Text = 0;

	// Timer for the spotlight switch
	bool countFrames4SpotLight = false;
	int frameCnt4SpotLight = 0;
	
	// Flag for Game stuff
	bool gameStarted = false;
	bool textOn = true;
	bool restartGame = false;

	// Score counter
	int score = 0;
	int objectiveIndex = 0;

	//main draw loop
	for (uint32_t t_frameIndex = 0; t_frameIndex < 10000; ++t_frameIndex) //only display for a few seconds
	{
		// Check and update the status of the controller
		myController.update();

		//required to set states ready for draw commands
		myGraphicsWrapper.preDraw();

		//Grab a pointer to the current graphics context, to give us direct access
		Gnmx::GnmxGfxContext* myGFXC = myGraphicsWrapper.getRenderContext();

		
		// New rotation matrices - added in 9-C4
		const Matrix4 sunAxialRotMatrix = Matrix4::rotationY(sunAngle += 0.005);

		const Matrix4 mercuryOrbitalRotMatrix = Matrix4::rotationY(mercuryOrbAngle += 0.005);
		const Matrix4 mercuryAxialRotMatrix = Matrix4::rotationY(mercuryAxiAngle -= 0.005);

		const Matrix4 earthOrbitalRotMatrix = Matrix4::rotationY(earthOrbAngle += 0.004);
		const Matrix4 earthAxialRotMatrix = Matrix4::rotationY(earthAxiAngle += 0.025);
		const Matrix4 earthInclinationRotMatrix = Matrix4::rotationZ(0.4);
		const Matrix4 earthFixInclinRotMatrix = Matrix4::rotationY(earthOppOrbAngle -= 0.004);

		const Matrix4 moonOrbitalRotMatrix = Matrix4::rotationY(moonOrbAngle += 0.01);
		const Matrix4 moonAxialRotMatrix = Matrix4::rotationY(moonAxiAngle += 0.01);

		const Matrix4 plutoOrbitalRotMatrixX = Matrix4::rotationX(plutoOrbAngle += 0.0085);
		const Matrix4 plutoOrbitalRotMatrixZ = Matrix4::rotationZ(plutoOrbAngle2 += 0.005);
		const Matrix4 plutoAxialRotMatrix = Matrix4::rotationX(plutoAxiAngle += 0.033);
		const Matrix4 plutoFixAxialRotMatrixZ = Matrix4::rotationZ(plutoAxiZAngle -= 0.005);

		const Matrix4 cometOrbitalRotMatrix = Matrix4::rotationY(cometOrbAngle += 0.0055);
		const Matrix4 cometAxialRotMatrix = Matrix4::rotationY(cometAxiAngle += 0.025);


		const Matrix4 brickAxialRotMatrix = Matrix4::rotationY(brickAxiAngle -= 0.013);

		const Matrix4 gemAxialRotMatrixY = Matrix4::rotationY(gemAxiAngle += 0.015);
		const Matrix4 gemInclinRotMatrixZ = Matrix4::rotationZ(0.5);

		const Matrix4 violinAxialRotMatrix = Matrix4::rotationY(violinAxiAngle -= 0.02);

		const Matrix4 flowerAxialRotMatrix = Matrix4::rotationY(flowerAxiAngle -= 0.005);

		// Light source
		//const Matrix4 lampAxialRotMatrix = Matrix4::rotationY(lampAxiAngle -= 0.01);
		const Matrix4 lampFrontAxialRotMx = Matrix4::rotationZ(lampFrontAxiAngle);
		const Matrix4 lampBackAxialRotMx = Matrix4::rotationZ(lampBackAxiAngle);
		const Matrix4 lampLeftAxialRotMx = Matrix4::rotationX(lampLeftAxiAngle);
		const Matrix4 lampRightAxialRotMx = Matrix4::rotationX(lampRightAxiAngle);


		// Position Matrices
		const Matrix4 sunPositionMatrix = Matrix4::translation(objectivesPosVx[OBJECTIVE_SOLAR_SYSTEM]);
		const Matrix4 mercuryPositionMatrix = Matrix4::translation(Vector3(0, 0, -2.5));
		const Matrix4 earthPositionMatrix = Matrix4::translation(Vector3(0, 0, -5.5));
		const Matrix4 moonPositionMatrix = Matrix4::translation(Vector3(0, 0.2, -0.7));
		const Matrix4 plutoPositionMatrix = Matrix4::translation(Vector3(0.5, 0, -6.75));
		const Matrix4 cometTetherPosMatrix = Matrix4::translation(Vector3(3.5, 0, -10));
		const Matrix4 cometPositionMatrix = Matrix4::translation(Vector3(0, 0, -8.5));
;
		const Matrix4 grassFloorPositionMatrix = Matrix4::translation(grassFloorPos);

		const Matrix4 groundPositionMatrix = Matrix4::translation(groundPosVx);

		const Matrix4 teapotPositionMatrix = Matrix4::translation(objectivesPosVx[OBJECTIVE_TEAPOT]);

		const Matrix4 airplanePositionMatrix = Matrix4::translation(objectivesPosVx[OBJECTIVE_AIRPLANE]);

		const Matrix4 brickPositionMatrix = Matrix4::translation(objectivesPosVx[OBJECTIVE_BRICK]);

		const Matrix4 gemPositionMatrix = Matrix4::translation(objectivesPosVx[OBJECTIVE_GEM]);

		const Matrix4 skyscraperPositionMatrix = Matrix4::translation(objectivesPosVx[OBJECTIVE_SKYSCRAPER]);

		const Matrix4 violinPositionMatrix = Matrix4::translation(objectivesPosVx[OBJECTIVE_VIOLIN]);

		const Matrix4 flowerPositionMatrix = Matrix4::translation(objectivesPosVx[OBJECTIVE_FLOWER]);

		// Light source
		//const Matrix4 lampPositionMatrix = Matrix4::translation(lampPosVx);
		const Matrix4 lampFrontPosMx = Matrix4::translation(lampFrontVx);
		const Matrix4 lampBackPosMx = Matrix4::translation(lampBackVx);
		const Matrix4 lampLeftPosMx = Matrix4::translation(lampLeftVx);
		const Matrix4 lampRightPosMx = Matrix4::translation(lampRightVx);


		// Scale Matrices
		const Matrix4 sunScaleMatrix = Matrix4::scale(Vector3(1.55));
		const Matrix4 mercuryScaleMatrix = Matrix4::scale(Vector3(0.2));
		const Matrix4 earthScaleMatrix = Matrix4::scale(Vector3(0.215));
		const Matrix4 moonScaleMatrix = Matrix4::scale(Vector3(0.125));
		const Matrix4 plutoScaleMatrix = Matrix4::scale(Vector3(0.15));
		const Matrix4 cometScaleMatrix = Matrix4::scale(Vector3(0.2));

		const Matrix4 groundScaleMatrix = Matrix4::scale(Vector3(15));

		const Matrix4 floorScaleMatrix = Matrix4::scale(Vector3(0.8));
		
		const Matrix4 teapotScaleMatrix = Matrix4::scale(Vector3(2));

		const Matrix4 airplaneScaleMatrix = Matrix4::scale(Vector3(0.1));

		const Matrix4 brickScaleMatrix = Matrix4::scale(Vector3(2));

		const Matrix4 gemScaleMatrix = Matrix4::scale(Vector3(2.6));

		const Matrix4 skyscraperScaleMatrix = Matrix4::scale(Vector3(0.6));

		const Matrix4 violinScaleMatrix = Matrix4::scale(Vector3(2.3));

		const Matrix4 flowerScaleMatrix = Matrix4::scale(Vector3(0.08));


		//const Matrix4 lampScaleMatrix = Matrix4::scale(Vector3(0.175));
		const Matrix4 lampArrowsScaleMx = Matrix4::scale(Vector3(0.25));

		// Assign the model-world matrices of the objects ------------------------------------------------------------------

		// --- Light Source
		//myObjects[PT_OBJECT_LAMP].m_modelWorldMx = lampPositionMatrix * lampAxialRotMatrix * lampScaleMatrix;
		myObjects[PT_OBJECT_ARROW_FRONT].m_modelWorldMx = lampFrontPosMx * lampFrontAxialRotMx * lampArrowsScaleMx;
		myObjects[PT_OBJECT_ARROW_BACK].m_modelWorldMx = lampBackPosMx * lampBackAxialRotMx * lampArrowsScaleMx;
		myObjects[PT_OBJECT_ARROW_LEFT].m_modelWorldMx = lampLeftPosMx * lampLeftAxialRotMx * lampArrowsScaleMx;
		myObjects[PT_OBJECT_ARROW_RIGHT].m_modelWorldMx = lampRightPosMx * lampRightAxialRotMx * lampArrowsScaleMx;


		// --- Sun
		myObjects[PT_OBJECT_SUN].m_modelWorldMx = sunPositionMatrix * sunAxialRotMatrix * sunScaleMatrix;

		// --- Mercury
		myObjects[PT_OBJECT_MERCURY].m_modelWorldMx = sunPositionMatrix * mercuryOrbitalRotMatrix * mercuryPositionMatrix *
			mercuryAxialRotMatrix * mercuryScaleMatrix;

		// --- Earth
		myObjects[PT_OBJECT_EARTH].m_modelWorldMx = sunPositionMatrix * earthOrbitalRotMatrix * earthPositionMatrix *
			earthFixInclinRotMatrix * earthInclinationRotMatrix * earthAxialRotMatrix * earthScaleMatrix;

		// --- Moon
		myObjects[PT_OBJECT_MOON].m_modelWorldMx = sunPositionMatrix * earthOrbitalRotMatrix * earthPositionMatrix *
			moonOrbitalRotMatrix * moonPositionMatrix * moonAxialRotMatrix * moonScaleMatrix;

		// --- Pluto
		myObjects[PT_OBJECT_PLUTO].m_modelWorldMx = sunPositionMatrix * plutoOrbitalRotMatrixX * plutoOrbitalRotMatrixZ *
			plutoPositionMatrix * plutoFixAxialRotMatrixZ * plutoAxialRotMatrix * plutoScaleMatrix;

		// --- Comet
		myObjects[PT_OBJECT_COMET].m_modelWorldMx = cometTetherPosMatrix * cometOrbitalRotMatrix * cometPositionMatrix *
			cometAxialRotMatrix * cometScaleMatrix;

		
		// --- Ground
		myObjects[PT_OBJECT_GROUND].m_modelWorldMx = groundPositionMatrix * groundScaleMatrix;

		//// --- Grass Floor
		myObjects[PT_OBJECT_GRASS_FLOOR].m_modelWorldMx = grassFloorPositionMatrix * floorScaleMatrix;

		// -- Teapot
		myObjects[PT_OBJECT_TEAPOT].m_modelWorldMx = teapotPositionMatrix * teapotScaleMatrix;

		// -- Airplane
		myObjects[PT_OBJECT_AIRPLANE].m_modelWorldMx = airplanePositionMatrix * airplaneScaleMatrix;

		// -- Brick Block
		myObjects[PT_OBJECT_BRICK_BLOCK].m_modelWorldMx = brickPositionMatrix * brickAxialRotMatrix * brickScaleMatrix;

		// --- Emerald Gem
		myObjects[PT_OBJECT_GEM].m_modelWorldMx = gemPositionMatrix * gemInclinRotMatrixZ * gemAxialRotMatrixY * gemScaleMatrix;

		// --- Skyscraper
		myObjects[PT_OBJECT_SKYSCRAPER].m_modelWorldMx = skyscraperPositionMatrix * skyscraperScaleMatrix;

		// --- Violin
		myObjects[PT_OBJECT_VIOLIN_CASE].m_modelWorldMx = violinPositionMatrix * violinAxialRotMatrix * violinScaleMatrix;

		// --- Flower
		myObjects[PT_OBJECT_FLOWER].m_modelWorldMx = flowerPositionMatrix * flowerAxialRotMatrix * flowerScaleMatrix;


		// Solar System-esque layout
		for (int i = 0; i < PT_OBJECT_COUNT; i++) myDrawManager.draw(myGFXC, &myObjects[i], &myCameras[cam_cursor], &myLight);

		// Draw the HUD Text
		for (int i = 0; i < PT_HUD_ITEM_COUNT; i++)
		{
			myHUDItems[i].draw(myGFXC);
		}


		// ------------------------------ Controls Section ------------------------------
		// NOTE: Use the base 'myController' functions instead of the toggles, triggers or even
		// the X and Y angles (used for the analog sticks)...
		// Why this works is unknown, but it may be just that it transforms everything on the
		// screen and not just one object or group of objects and their vertices

		// Main button for the game
		if (allowCrossPress())
		{
			if (gameStarted)
			{
				// The game itself
				if (objectiveIndex < OBJECTIVE_COUNT - 1)
				{
					// Reset the timer for the 'Objective Complete' message
					countFrames4Text = true;
					frameCnt4Text = 0;

					if (!checkDistance(lampPosVx, objectivesPosVx[objectiveIndex]))
					{
						objectiveIndex++;

						// Set the target
						myHUDItems[PT_HUD_ITEM_TARGET].changeText(objectivesText[objectiveIndex]);

						myHUDItems[PT_HUD_ITEM_OBJECTIVE_COMPLETE].changeText("Try again");
					}
					else {
						// Add score and move on to the next target
						score++;
						objectiveIndex++;

						// Set the target
						myHUDItems[PT_HUD_ITEM_TARGET].changeText(objectivesText[objectiveIndex]);
						myHUDItems[PT_HUD_ITEM_OBJECTIVE_COMPLETE].changeText("Well done!");
					}
				}//if() - OBJECTIVE_COUNT
				else
				{
					countFrames4Text = true;

					// Show the 'Game Over' text
					// - Requires double reset because it somehow overlaps with the last text from PT_HUD_ITEM_OBJECTIVE and PT_HUD_ITEM_TARGET
					// - Might be caused by a mix up of data within the garlic allocator
					myHUDItems[PT_HUD_ITEM_OBJECTIVE_COMPLETE].makeText("", 2.5, -0.53, 0.85);
					myHUDItems[PT_HUD_ITEM_OBJECTIVE_COMPLETE].changeText("Congratulations you have finished the game!");

					myHUDItems[PT_HUD_ITEM_GAME_START_MESSAGE].makeText("", 2.5, -0.37, 0.75);
					myHUDItems[PT_HUD_ITEM_GAME_START_MESSAGE].changeText("Press 'Options' to Play Again");

					myHUDItems[PT_HUD_ITEM_OBJECTIVE].changeText("Game Finished");
					myHUDItems[PT_HUD_ITEM_TARGET].changeText("All Targets Found");

					restartGame = true;
				}
			}//if(gameStarted)
			else {

				// Set the initial target
				myHUDItems[PT_HUD_ITEM_TARGET].changeText(objectivesText[objectiveIndex]);

				// Adjust the text fields accordingly
				myHUDItems[PT_HUD_ITEM_GAME_START_MESSAGE].changeText("");
				myHUDItems[PT_HUD_ITEM_OBJECTIVE].changeText("Find the following target:");
				gameStarted = true;
			}
		}//if(allowCrossPress())
		myHUDItems[PT_HUD_ITEM_SCORE_NUM].changeNumText(score);

		// Game Start text - Flashes text on screen
		if (!gameStarted)
		{
			if (textOn) {

				if (frameCnt4Text != 90) {
					frameCnt4Text++;
					myHUDItems[PT_HUD_ITEM_GAME_START_MESSAGE].changeText("Press X (Cross) to start the game");
				}
				else {
					textOn = false;
					frameCnt4Text = 0;
				}
			}

			if (!textOn) {

				if (frameCnt4Text != 60) {
					frameCnt4Text++;
					myHUDItems[PT_HUD_ITEM_GAME_START_MESSAGE].changeText("");
				}
				else {
					textOn = true;
					frameCnt4Text = 0;
				}
			}
		}//if(!gameStarted)
		else
		{
			// Guard to prevent the message from disappearing when the game has ended
			if (!restartGame)
			{
				// Count 180 frames - Equals to 3 secs
				if (countFrames4Text && frameCnt4Text != 180) frameCnt4Text++;
				else {
					myHUDItems[PT_HUD_ITEM_OBJECTIVE_COMPLETE].changeText("");
					countFrames4Text = false;
					frameCnt4Text = 0;
				}
			}//if(!restartGame)
		}


		// Camera controls --------------------------------------------------------------
		// Change camera 
		if (allowTrianglePress())
		{
			if (cam_cursor >= 1) cam_cursor = -1;
			cam_cursor += 1;
		}
		if (allowCirclePress())
		{
			if (cam_cursor <= 0) cam_cursor = 2;
			cam_cursor -= 1;
		}
		myHUDItems[PT_HUD_ITEM_CURRENT_CAM_NUM].changeText(camText[cam_cursor]);


		// Lighting controls --------------------------------------------------------------
			// Spotlight mode
		if (allowSquarePress()) {
			myLight.m_useDistanceAttn = false;
			countFrames4SpotLight = true;
		}
		// Count 300 frames - Equals to 5 secs
		if (countFrames4SpotLight && frameCnt4SpotLight != 120) frameCnt4SpotLight++;
		else {
			myLight.m_useDistanceAttn = true;
			countFrames4SpotLight = false;
			frameCnt4SpotLight = 0;
		}
		// END Lighting controls ----------------------------------------------------------


		// Switches the functionality of the left stick to control the Spolight and its camera only
		if (cam_cursor == 0)
		{
			// Set Spotlight HUD Text
			myHUDItems[PT_HUD_ITEM_CAM_ELEVATION].changeText("L3 / R3 Press : Not Used");
			myHUDItems[PT_HUD_ITEM_CAM_MOVE].changeText("Left Stick : Move Spotlight");
			myHUDItems[PT_HUD_ITEM_CAM_LOOK].changeText("Right Stick : Not Used");
			myHUDItems[PT_HUD_ITEM_CAM_ROLL].changeText("L1 / R1 : Not Used");
			myHUDItems[PT_HUD_ITEM_LIGHT_MOVEMENT].changeText("D-Pad : Not Used");

			// Assign left stick controls...
			lamp_z += leftStickY();
			myLight.trackForwardBack(-leftStickY());
			myCameras[0].trackUpDown(-leftStickY());

			// ...Same here
			lamp_x += leftStickX();
			myLight.trackLeftRight(-leftStickX());
			myCameras[0].trackLeftRight(leftStickX());

			// Rotate the directional indicators accordingly
			if (leftStickY() > 0) lampBackAxiAngle += leftStickY();
			if (leftStickY() < 0) lampFrontAxiAngle += leftStickY();
			if (leftStickX() < 0) lampLeftAxiAngle += leftStickX();
			if (leftStickX() > 0) lampRightAxiAngle += leftStickX();

			lampPosVx = Vector3(lamp_x, lamp_y, lamp_z);

			lampFrontVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z - 1);
			lampBackVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z + 1);
			lampLeftVx = Vector3(lamp_x - 1, lamp_y - 0.8, lamp_z);
			lampRightVx = Vector3(lamp_x + 1, lamp_y - 0.8, lamp_z);
		}//if(cam_cursor == 0)


		// Allows control of spotlight and free cam while in 'Free Cam' mode
		if (cam_cursor == 1)
		{
			// Set Free Cam HUD Text
			myHUDItems[PT_HUD_ITEM_CAM_ELEVATION].changeText("L3 / R3 Press : Camera Elevation");
			myHUDItems[PT_HUD_ITEM_CAM_MOVE].changeText("Left Stick : Move Camera");
			myHUDItems[PT_HUD_ITEM_CAM_LOOK].changeText("Right Stick : Look Around");
			myHUDItems[PT_HUD_ITEM_CAM_ROLL].changeText("L1 / R1 : Roll Camera");
			myHUDItems[PT_HUD_ITEM_LIGHT_MOVEMENT].changeText("D-Pad : Move Spotlight");

			// Forward and back
			myCameras[1].trackForwardBack(leftStickY());

			// Strafe left and right
			myCameras[1].trackLeftRight(leftStickX());

			// Rotations
			myCameras[1].trackYaw(rightStickX());
			myCameras[1].trackPitch(rightStickY());

			// Roll Clockwise / Anti-Clockwise
			if (myController.R1Pressed()) myCameras[1].trackRoll(-0.02);
			if (myController.L1Pressed()) myCameras[1].trackRoll(0.02);

			if (myController.R3Pressed()) myCameras[1].trackUpDown(0.05);
			if (myController.L3Pressed()) myCameras[1].trackUpDown(-0.05);


			// Move light source...
			// Forward and backward - Z-Axis
			if (myController.downPressed())
			{
				lamp_z += 0.07;
				lampBackAxiAngle += 0.07;

				myCameras[0].trackUpDown(-0.07);

				myLight.trackForwardBack(-0.07);
				lampPosVx = Vector3(lamp_x, lamp_y, lamp_z);

				lampFrontVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z - 1);
				lampBackVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z + 1);
				lampLeftVx = Vector3(lamp_x - 1, lamp_y - 0.8, lamp_z);
				lampRightVx = Vector3(lamp_x + 1, lamp_y - 0.8, lamp_z);
			}
			if (myController.upPressed())
			{
				lamp_z -= 0.07;
				lampFrontAxiAngle -= 0.07;

				myCameras[0].trackUpDown(0.07);

				myLight.trackForwardBack(0.07);
				lampPosVx = Vector3(lamp_x, lamp_y, lamp_z);

				lampFrontVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z - 1);
				lampBackVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z + 1);
				lampLeftVx = Vector3(lamp_x - 1, lamp_y - 0.8, lamp_z);
				lampRightVx = Vector3(lamp_x + 1, lamp_y - 0.8, lamp_z);
			}

			// Left and right - X-Axis
			if (myController.leftPressed())
			{
				lamp_x -= 0.07;
				lampLeftAxiAngle -= 0.07;

				myCameras[0].trackLeftRight(-0.07);

				myLight.trackLeftRight(0.07);
				lampPosVx = Vector3(lamp_x, lamp_y, lamp_z);

				lampFrontVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z - 1);
				lampBackVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z + 1);
				lampLeftVx = Vector3(lamp_x - 1, lamp_y - 0.8, lamp_z);
				lampRightVx = Vector3(lamp_x + 1, lamp_y - 0.8, lamp_z);
			}
			if (myController.rightPressed())
			{
				lamp_x += 0.07;
				lampRightAxiAngle += 0.07;

				myCameras[0].trackLeftRight(0.07);

				myLight.trackLeftRight(-0.07);
				lampPosVx = Vector3(lamp_x, lamp_y, lamp_z);

				lampFrontVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z - 1);
				lampBackVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z + 1);
				lampLeftVx = Vector3(lamp_x - 1, lamp_y - 0.8, lamp_z);
				lampRightVx = Vector3(lamp_x + 1, lamp_y - 0.8, lamp_z);
			}
		}//if(cam_cursor == 1)


		// Spotlight Elevation - Y-Axis
		if (myController.L2Pressed())		// Down
		{
			lamp_y -= 0.07;

			myCameras[0].trackForwardBack(-0.07);

			myLight.trackUpDown(0.07);
			lampPosVx = Vector3(lamp_x, lamp_y, lamp_z);

			lampFrontVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z - 1);
			lampBackVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z + 1);
			lampLeftVx = Vector3(lamp_x - 1, lamp_y - 0.8, lamp_z);
			lampRightVx = Vector3(lamp_x + 1, lamp_y - 0.8, lamp_z);
		}
		if (myController.R2Pressed())		// Up
		{
			lamp_y += 0.07;

			myCameras[0].trackForwardBack(0.07);

			myLight.trackUpDown(-0.07);
			lampPosVx = Vector3(lamp_x, lamp_y, lamp_z);

			lampFrontVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z - 1);
			lampBackVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z + 1);
			lampLeftVx = Vector3(lamp_x - 1, lamp_y - 0.8, lamp_z);
			lampRightVx = Vector3(lamp_x + 1, lamp_y - 0.8, lamp_z);
		}


		// Reset the Game
		if (allowOptionsPress() && restartGame)
		{
			// Flags
			restartGame = false;
			gameStarted = false;
			countFrames4Text = false;


			// Counters
			frameCnt4Text = 0;
			score = 0;
			cam_cursor = 0;
			objectiveIndex = 0;


			// Cameras
			myCameras[0].resetCam();
			myCameras[0].m_worldViewMx = Matrix4::translation(Vector3(0.0, -7.5, 12.0));
			myCameras[0].m_worldViewMx = Matrix4::rotationX(1.5708) * myCameras[0].m_worldViewMx;

			myCameras[1].resetCam();


			// Light Source
			myLight.resetPosition();

			lamp_x = 0;
			lamp_y = 5;
			lamp_z = -12;

			lampPosVx = Vector3(lamp_x, lamp_y, lamp_z);

			lampFrontVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z - 1);
			lampBackVx = Vector3(lamp_x, lamp_y - 0.8, lamp_z + 1);
			lampLeftVx = Vector3(lamp_x - 1, lamp_y - 0.8, lamp_z);
			lampRightVx = Vector3(lamp_x + 1, lamp_y - 0.8, lamp_z);


			// HUD Items
			// - Requires double reset because it somehow overlaps with the last text from PT_HUD_ITEM_OBJECTIVE and PT_HUD_ITEM_TARGET
			// - Might be caused by a mix up of data within the garlic allocator
			myHUDItems[PT_HUD_ITEM_OBJECTIVE_COMPLETE].makeText("", 2.5, -0.13, 0.85);
			myHUDItems[PT_HUD_ITEM_OBJECTIVE_COMPLETE].changeText("");

			myHUDItems[PT_HUD_ITEM_GAME_START_MESSAGE].makeText("", 2.5, -0.41, 0.75);
			myHUDItems[PT_HUD_ITEM_GAME_START_MESSAGE].changeText("Press X (Cross) to start the game");

			myHUDItems[PT_HUD_ITEM_OBJECTIVE].changeText("");
			myHUDItems[PT_HUD_ITEM_TARGET].changeText("");
		}

		// ---------------------------- END Controls Section ----------------------------


		// Done after all draw calls, to end the frame.
		myGraphicsWrapper.postDraw();

	}//for(main loop)

	// Tidy up
	myGraphicsWrapper.release();

	// Manually releasing each each allocated resource is not necessary as the linear
	// allocators for ONION and GARLIC are terminated here.
	myOnionAllocator.terminate();
	myGarlicAllocator.terminate();

	return 0;
}//main()
