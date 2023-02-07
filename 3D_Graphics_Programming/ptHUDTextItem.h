#ifndef __PT_HUD_TEXT_ITEM__
#define __PT_HUD_TEXT_ITEM__

#include <scebase.h>
#include "ptVertex.h"
#include "ptMaterial.h"

#include "../../common/allocator.h"

using namespace sce;


class ptHUDTextItem
{
private:

	// Vertex data
	ptVertex* m_vertices = NULL;
	ptVertex* m_verticesGPU = NULL;
	uint16_t m_vertexCount = 0;
	size_t m_verticesSize = 0;

	// Vertex data descriptions buffers
	Gnm::Buffer m_vertexBuffers[PT_VERTEX_ELEM_COUNT];

	// Indices
	uint16_t* m_indices = NULL;
	uint16_t* m_indicesGPU = NULL;
	uint32_t m_indexCount = 0;
	size_t m_indicesSize = 0;
	ptTriangle* m_triangles = NULL;

	// Shader and world data
	ptMaterial* m_material;

	// Allocator
	LinearAllocator* myGarlicAlloc;

	// String variables
	int m_charCount = 0;
	float m_spacing = 0.011;
	float m_HUDTexCoordSize = 0.0625;	// Size of the area covered by each character in the HUD Characters Texture file
	float m_scale = 0;
	float m_offsetX = 0;
	float m_offsetY = 0;

public:

	bool m_validData = false;
	bool m_verbose = false;

	float x_size = 0.01;	// AKA the base X-coordinate
	float y_size = 0.0177;	// AKA the base Y-coordinate


	// Initialiser
	void init(ptMaterial* _material, LinearAllocator* _garlicAlloc)
	{
		myGarlicAlloc = _garlicAlloc;
		m_material = _material;
	}

	// Custom Text constructor
	void makeText(const char* _text, float _scale, float _offsetX, float _offsetY)
	{
		m_validData = false;

		// Delete any previously made text instance
		deleteStoredText();

		while (_text[m_charCount] != '\0')
		{
			m_charCount++;
		}
		if (m_verbose) printf("Character count for HUD Text: %i\n", m_charCount);

		// Make new arrays for each character in the String
		m_vertices = new ptVertex[4 * m_charCount];
		m_indices = new uint16_t[6 * m_charCount];

		// Set the counts and sizes to accommodate the string of characters
		m_vertexCount = 4 * m_charCount;
		m_verticesSize = m_vertexCount * sizeof(ptVertex);
		m_indexCount = 6 * m_charCount;
		m_indicesSize = m_indexCount * sizeof(uint16_t);

		m_triangles = (ptTriangle*)m_indices;

		// Set the parameters
		m_scale = _scale;
		m_offsetX = _offsetX;
		m_offsetY = _offsetY;

		// Fill the appropriate data for each character
		for (int i = 0; i < m_charCount; i++)
		{
			// To make it easy to identify without making the index pointer look weird
			// Vertex Counters
			int j0 = i * 4;
			int j1 = j0 + 1;
			int j2 = j0 + 2;
			int j3 = j0 + 3;

			// Triangle Counters
			int t1 = i * 2;
			int t2 = t1 + 1;

			// Grid positions of the characters on the HUD font file (oolite-font)
			int t_charNumber = (int)_text[i];
			int t_row = t_charNumber / 16;
			int t_column = t_charNumber % 16;
			// NOTE: The TexCoords are (X,Y)
			if (m_verbose) printf("Character at (%i, %i)\n", t_column, t_row);


			// Top-left --------------------------------------
			// Positions
			m_vertices[j0].x = m_scale * (-x_size + (i * m_spacing)) + m_offsetX;
			m_vertices[j0].y = m_scale * (y_size) + m_offsetY;
			m_vertices[j0].z = 0;

			// Colour
			m_vertices[j0].r = 1;
			m_vertices[j0].g = 1;
			m_vertices[j0].b = 1;

			// Normals
			m_vertices[j0].nx = 0;
			m_vertices[j0].ny = 0;
			m_vertices[j0].nz = 1;

			// Texture Coordinates
			m_vertices[j0].u = t_column * m_HUDTexCoordSize;
			m_vertices[j0].v = t_row * m_HUDTexCoordSize;


			// Top-right ------------------------------------
			// Positions
			m_vertices[j1].x = m_scale * (x_size + (i * m_spacing)) + m_offsetX;
			m_vertices[j1].y = m_scale * (y_size) + m_offsetY;
			m_vertices[j1].z = 0;

			// Colour
			m_vertices[j1].r = 1;
			m_vertices[j1].g = 1;
			m_vertices[j1].b = 1;

			// Normals
			m_vertices[j1].nx = 0;
			m_vertices[j1].ny = 0;
			m_vertices[j1].nz = 1;

			// Texture Coordinates
			m_vertices[j1].u = t_column * m_HUDTexCoordSize + m_HUDTexCoordSize;
			m_vertices[j1].v = t_row * m_HUDTexCoordSize;


			// Bottom-right ---------------------------------
			m_vertices[j2].x = m_scale * (x_size + (i * m_spacing)) + m_offsetX;
			m_vertices[j2].y = m_scale * (-y_size) + m_offsetY;
			m_vertices[j2].z = 0;

			// Colour
			m_vertices[j2].r = 1;
			m_vertices[j2].g = 1;
			m_vertices[j2].b = 1;

			// Normals
			m_vertices[j2].nx = 0;
			m_vertices[j2].ny = 0;
			m_vertices[j2].nz = 1;

			// Texture Coordinates
			m_vertices[j2].u = t_column * m_HUDTexCoordSize + m_HUDTexCoordSize;
			m_vertices[j2].v = t_row * m_HUDTexCoordSize + m_HUDTexCoordSize;


			// Bottom-left -----------------------------------
			m_vertices[j3].x = m_scale * (-x_size + (i * m_spacing)) + m_offsetX;
			m_vertices[j3].y = m_scale * (-y_size) + m_offsetY;
			m_vertices[j3].z = 0;

			// Colour
			m_vertices[j3].r = 1;
			m_vertices[j3].g = 1;
			m_vertices[j3].b = 1;

			// Normals
			m_vertices[j3].nx = 0;
			m_vertices[j3].ny = 0;
			m_vertices[j3].nz = 1;

			// Texture Coordinates
			m_vertices[j3].u = t_column * m_HUDTexCoordSize;
			m_vertices[j3].v = t_row * m_HUDTexCoordSize + m_HUDTexCoordSize;


			// Triangles ------------------------------------------
			m_triangles[t1].a = j0;
			m_triangles[t1].b = j3;
			m_triangles[t1].c = j2;

			m_triangles[t2].a = j0;
			m_triangles[t2].b = j2;
			m_triangles[t2].c = j1;

		}//for()

		// Load to the memory
		int l_error = copyDataToGPU(myGarlicAlloc);
		if (l_error != SCE_OK) printf("Unable to copy model data to GPU memory: 0x%08X\n", l_error);
		else m_validData = true;

	}//makeText()

	void changeText(const char* _newText)
	{
		m_validData = false;

		int l_newCharCount = 0;

		// Check character count
		while (_newText[l_newCharCount] != '\0')
		{
			l_newCharCount++;
		}
		if (m_verbose) printf("Old charCount: %i\nNew charCount: %i\n", m_charCount, l_newCharCount);

		
		// Compare if new text has fewer characters than old text...
		if (l_newCharCount <= m_charCount)
		{
			// First loop - Refresh the characters
			// Turn them into blank spaces ASCII 13 (Translates to Grid 13)
			if (m_verbose) printf("New charCount is shorter/same length : Refreshing the old characters...\n");
			for (int i = 0; i < m_charCount; i++)
			{	
				// Vertex Counters
				int j0 = i * 4;
				int j1 = j0 + 1;
				int j2 = j0 + 2;
				int j3 = j0 + 3;

				// Blank space character
				int t_charNumber = (int)char(13);
				int t_row = t_charNumber / 16;
				int t_column = t_charNumber % 16;

				// Texture Coordinates
				m_vertices[j0].u = t_column * m_HUDTexCoordSize;
				m_vertices[j0].v = t_row * m_HUDTexCoordSize;

				m_vertices[j1].u = t_column * m_HUDTexCoordSize + m_HUDTexCoordSize;
				m_vertices[j1].v = t_row * m_HUDTexCoordSize;

				m_vertices[j2].u = t_column * m_HUDTexCoordSize + m_HUDTexCoordSize;
				m_vertices[j2].v = t_row * m_HUDTexCoordSize + m_HUDTexCoordSize;

				m_vertices[j3].u = t_column * m_HUDTexCoordSize;
				m_vertices[j3].v = t_row * m_HUDTexCoordSize + m_HUDTexCoordSize;
			}//for(m_characterCount)
			

			if (m_verbose) printf("And replacing with new ones...\n");
			// Second loop - Insert characters rom the new text
			for (int i = 0; i < l_newCharCount; i++)
			{
				// Vertex Counters
				int j0 = i * 4;
				int j1 = j0 + 1;
				int j2 = j0 + 2;
				int j3 = j0 + 3;

				// Blank space character
				int t_charNumber = (int)_newText[i];
				int t_row = t_charNumber / 16;
				int t_column = t_charNumber % 16;

				// Texture Coordinates
				// Top-left
				m_vertices[j0].u = t_column * m_HUDTexCoordSize;
				m_vertices[j0].v = t_row * m_HUDTexCoordSize;

				// Top-right
				m_vertices[j1].u = t_column * m_HUDTexCoordSize + m_HUDTexCoordSize;
				m_vertices[j1].v = t_row * m_HUDTexCoordSize;

				// Bottom-right
				m_vertices[j2].u = t_column * m_HUDTexCoordSize + m_HUDTexCoordSize;
				m_vertices[j2].v = t_row * m_HUDTexCoordSize + m_HUDTexCoordSize;

				// Bottom-left
				m_vertices[j3].u = t_column * m_HUDTexCoordSize;
				m_vertices[j3].v = t_row * m_HUDTexCoordSize + m_HUDTexCoordSize;

				if (m_verbose) printf("New Character at %i (%i, %i)\n", i, t_column, t_row);
			}//for(m_characterCount)
		}//if() - New char count <= old char count
		else
		{
			if (m_verbose) printf("New charCount is longer : Reconstructing the text content to compensate");
			
			// Overwrite with the longer charCount
			m_charCount = l_newCharCount;

			// Adjust the arrays to accommodate for the longer text
			m_vertices = new ptVertex[4 * m_charCount];
			m_indices = new uint16_t[6 * m_charCount];

			// Expand the counts and sizes
			m_vertexCount = 4 * m_charCount;
			m_verticesSize = m_vertexCount * sizeof(ptVertex);
			m_indexCount = 6 * m_charCount;
			m_indicesSize = m_indexCount * sizeof(uint16_t);

			m_triangles = (ptTriangle*)m_indices;

			// Fill the appropriate data for each character
			for (int i = 0; i < m_charCount; i++)
			{
				// To make it easy to identify without making the index pointer look weird
				// Vertex Counters
				int j0 = i * 4;
				int j1 = j0 + 1;
				int j2 = j0 + 2;
				int j3 = j0 + 3;

				// Triangle Counters
				int t1 = i * 2;
				int t2 = t1 + 1;

				// Grid positions of the characters on the HUD font file (oolite-font)
				int t_charNumber = (int)_newText[i];
				int t_row = t_charNumber / 16;
				int t_column = t_charNumber % 16;
				if (m_verbose) printf("New Character at %i (%i, %i)\n", i, t_column, t_row);


				// Top-left --------------------------------------
				// Positions
				m_vertices[j0].x = m_scale * (-x_size + (i * m_spacing)) + m_offsetX;
				m_vertices[j0].y = m_scale * (y_size)+m_offsetY;
				m_vertices[j0].z = 0;

				// Colour
				m_vertices[j0].r = 1;
				m_vertices[j0].g = 1;
				m_vertices[j0].b = 1;

				// Normals
				m_vertices[j0].nx = 0;
				m_vertices[j0].ny = 0;
				m_vertices[j0].nz = 1;

				// Texture Coordinates
				m_vertices[j0].u = t_column * m_HUDTexCoordSize;
				m_vertices[j0].v = t_row * m_HUDTexCoordSize;


				// Top-right ------------------------------------
				// Positions
				m_vertices[j1].x = m_scale * (x_size + (i * m_spacing)) + m_offsetX;
				m_vertices[j1].y = m_scale * (y_size)+m_offsetY;
				m_vertices[j1].z = 0;

				// Colour
				m_vertices[j1].r = 1;
				m_vertices[j1].g = 1;
				m_vertices[j1].b = 1;

				// Normals
				m_vertices[j1].nx = 0;
				m_vertices[j1].ny = 0;
				m_vertices[j1].nz = 1;

				// Texture Coordinates
				m_vertices[j1].u = t_column * m_HUDTexCoordSize + m_HUDTexCoordSize;
				m_vertices[j1].v = t_row * m_HUDTexCoordSize;


				// Bottom-right ---------------------------------
				m_vertices[j2].x = m_scale * (x_size + (i * m_spacing)) + m_offsetX;
				m_vertices[j2].y = m_scale * (-y_size) + m_offsetY;
				m_vertices[j2].z = 0;

				// Colour
				m_vertices[j2].r = 1;
				m_vertices[j2].g = 1;
				m_vertices[j2].b = 1;

				// Normals
				m_vertices[j2].nx = 0;
				m_vertices[j2].ny = 0;
				m_vertices[j2].nz = 1;

				// Texture Coordinates
				m_vertices[j2].u = t_column * m_HUDTexCoordSize + m_HUDTexCoordSize;
				m_vertices[j2].v = t_row * m_HUDTexCoordSize + m_HUDTexCoordSize;


				// Bottom-left -----------------------------------
				m_vertices[j3].x = m_scale * (-x_size + (i * m_spacing)) + m_offsetX;
				m_vertices[j3].y = m_scale * (-y_size) + m_offsetY;
				m_vertices[j3].z = 0;

				// Colour
				m_vertices[j3].r = 1;
				m_vertices[j3].g = 1;
				m_vertices[j3].b = 1;

				// Normals
				m_vertices[j3].nx = 0;
				m_vertices[j3].ny = 0;
				m_vertices[j3].nz = 1;

				// Texture Coordinates
				m_vertices[j3].u = t_column * m_HUDTexCoordSize;
				m_vertices[j3].v = t_row * m_HUDTexCoordSize + m_HUDTexCoordSize;


				// Triangles ------------------------------------------
				m_triangles[t1].a = j0;
				m_triangles[t1].b = j3;
				m_triangles[t1].c = j2;

				m_triangles[t2].a = j0;
				m_triangles[t2].b = j2;
				m_triangles[t2].c = j1;

			}//for(l_charCount) - Overwritten charCount
		}//else - New char count > old char count

		// Load to the memory
		int l_error = copyDataToGPU(myGarlicAlloc);
		if (l_error != SCE_OK) printf("Unable to copy model data to GPU memory: 0x%08X\n", l_error);
		else m_validData = true;
	}//changeText()


	void makeNumText(uint32_t _number, float _scale, float _offsetX, float _offsetY)
	{
		m_validData = false;

		// Delete any previously made text instance 
		deleteStoredText();

		// Character width of the maximum number 'uint32_t' can reach
		m_charCount = 10;

		// MUST be stored in a separate variable as the given number is used later on
		uint32_t t_value = _number;

		// Check the character width of the given number
		int t_digitCount = 1;
		while (t_value > 9)
		{
			t_value /= 10;
			t_digitCount++;
		}
		if (m_verbose) printf("%i digits found\n", t_digitCount);

		// Make new arrays for each character in the String
		m_vertices = new ptVertex[4 * m_charCount];
		m_indices = new uint16_t[6 * m_charCount];

		// Set the counts and sizes to accommodate the string of characters
		m_vertexCount = 4 * m_charCount;
		m_verticesSize = m_vertexCount * sizeof(ptVertex);
		m_indexCount = 6 * m_charCount;
		m_indicesSize = m_indexCount * sizeof(uint16_t);

		m_triangles = (ptTriangle*)m_indices;

		// Set the parameters
		m_scale = _scale;
		m_offsetX = _offsetX;
		m_offsetY = _offsetY;

		// Fill the appropriate data for each character
		for (int i = 0; i < m_charCount; i++)
		{
			// To make it easy to identify without making the index pointer look weird
			// Vertex Counters
			int j0 = i * 4;
			int j1 = j0 + 1;
			int j2 = j0 + 2;
			int j3 = j0 + 3;

			// Triangle Counters
			int t1 = i * 2;
			int t2 = t1 + 1;

			// Find the highest denomination digit
			uint32_t t_util = _number;
			for (int i = 0; i < t_digitCount - 1; i++) t_util /= 10;
			if (m_verbose) printf("%i\n", (int)t_util);

			// Removes the current digit from the given number - so that it is not included in the next iteration
			uint32_t t_digit = t_util;
			for (int i = 0; i < t_digitCount - 1; i++) t_util *= 10;
			_number -= t_util;
			t_digitCount--;

			// Get the grid coordinates for the number
			int t_charNumber = (int)(t_digit + 48);		// 48+ is the digit characters
			if (t_digitCount < 0) t_charNumber = 13;

			int t_row = t_charNumber / 16;
			int t_column = t_charNumber % 16;
			if (m_verbose)
			{
				printf("Character at %i (%i, %i)\n", t_charNumber, t_column, t_row);
			}


			// Top-left --------------------------------------
			// Positions
			m_vertices[j0].x = m_scale * (-x_size + (i * m_spacing)) + m_offsetX;
			m_vertices[j0].y = m_scale * (y_size)+m_offsetY;
			m_vertices[j0].z = 0;

			// Colour
			m_vertices[j0].r = 1;
			m_vertices[j0].g = 1;
			m_vertices[j0].b = 1;

			// Normals
			m_vertices[j0].nx = 0;
			m_vertices[j0].ny = 0;
			m_vertices[j0].nz = 1;

			// Texture Coordinates
			m_vertices[j0].u = t_column * m_HUDTexCoordSize;
			m_vertices[j0].v = t_row * m_HUDTexCoordSize;


			// Top-right ------------------------------------
			// Positions
			m_vertices[j1].x = m_scale * (x_size + (i * m_spacing)) + m_offsetX;
			m_vertices[j1].y = m_scale * (y_size)+m_offsetY;
			m_vertices[j1].z = 0;

			// Colour
			m_vertices[j1].r = 1;
			m_vertices[j1].g = 1;
			m_vertices[j1].b = 1;

			// Normals
			m_vertices[j1].nx = 0;
			m_vertices[j1].ny = 0;
			m_vertices[j1].nz = 1;

			// Texture Coordinates
			m_vertices[j1].u = t_column * m_HUDTexCoordSize + m_HUDTexCoordSize;
			m_vertices[j1].v = t_row * m_HUDTexCoordSize;


			// Bottom-right ---------------------------------
			m_vertices[j2].x = m_scale * (x_size + (i * m_spacing)) + m_offsetX;
			m_vertices[j2].y = m_scale * (-y_size) + m_offsetY;
			m_vertices[j2].z = 0;

			// Colour
			m_vertices[j2].r = 1;
			m_vertices[j2].g = 1;
			m_vertices[j2].b = 1;

			// Normals
			m_vertices[j2].nx = 0;
			m_vertices[j2].ny = 0;
			m_vertices[j2].nz = 1;

			// Texture Coordinates
			m_vertices[j2].u = t_column * m_HUDTexCoordSize + m_HUDTexCoordSize;
			m_vertices[j2].v = t_row * m_HUDTexCoordSize + m_HUDTexCoordSize;


			// Bottom-left -----------------------------------
			m_vertices[j3].x = m_scale * (-x_size + (i * m_spacing)) + m_offsetX;
			m_vertices[j3].y = m_scale * (-y_size) + m_offsetY;
			m_vertices[j3].z = 0;

			// Colour
			m_vertices[j3].r = 1;
			m_vertices[j3].g = 1;
			m_vertices[j3].b = 1;

			// Normals
			m_vertices[j3].nx = 0;
			m_vertices[j3].ny = 0;
			m_vertices[j3].nz = 1;

			// Texture Coordinates
			m_vertices[j3].u = t_column * m_HUDTexCoordSize;
			m_vertices[j3].v = t_row * m_HUDTexCoordSize + m_HUDTexCoordSize;


			// Triangles ------------------------------------------
			m_triangles[t1].a = j0;
			m_triangles[t1].b = j3;
			m_triangles[t1].c = j2;

			m_triangles[t2].a = j0;
			m_triangles[t2].b = j2;
			m_triangles[t2].c = j1;

		}//for()

		// Load to the memory
		int l_error = copyDataToGPU(myGarlicAlloc);
		if (l_error != SCE_OK) printf("Unable to copy model data to GPU memory: 0x%08X\n", l_error);
		else m_validData = true;
	}

	void changeNumText(uint32_t _number)
	{
		m_validData = false;

		// Character width of the maximum number 'uint32_t' can reach
		m_charCount = 10;

		// MUST be stored in a separate variable as the given number is used later on
		uint32_t t_value = _number;

		// Check the character width of the given number
		int t_digitCount = 1;
		while (t_value > 9)
		{
			t_value /= 10;
			t_digitCount++;
		}
		if (m_verbose) printf("%i digits found\n", t_digitCount);

		// Fill the appropriate data for each character
		for (int i = 0; i < m_charCount; i++)
		{
			// To make it easy to identify without making the index pointer look weird
			// Vertex Counters
			int j0 = i * 4;
			int j1 = j0 + 1;
			int j2 = j0 + 2;
			int j3 = j0 + 3;

			// Find the highest denomination digit
			uint32_t t_util = _number;
			for (int i = 0; i < t_digitCount - 1; i++) t_util /= 10;
			if (m_verbose) printf("%i\n", (int)t_util);

			// Removes the current digit from the given number - so that it is not included in the next iteration
			uint32_t t_digit = t_util;
			for (int i = 0; i < t_digitCount - 1; i++) t_util *= 10;
			_number -= t_util;
			t_digitCount--;

			// Get the grid coordinates for the number
			int t_charNumber = (int)(t_digit + 48);		// 48+ is the digit characters
			if (t_digitCount < 0) t_charNumber = 13;

			int t_row = t_charNumber / 16;
			int t_column = t_charNumber % 16;
			if (m_verbose)
			{
				printf("Character at %i (%i, %i)\n", t_charNumber, t_column, t_row);
			}

			// Top-left
			m_vertices[j0].u = t_column * m_HUDTexCoordSize;
			m_vertices[j0].v = t_row * m_HUDTexCoordSize;

			// Top-right
			m_vertices[j1].u = t_column * m_HUDTexCoordSize + m_HUDTexCoordSize;
			m_vertices[j1].v = t_row * m_HUDTexCoordSize;

			// Bottom-right
			m_vertices[j2].u = t_column * m_HUDTexCoordSize + m_HUDTexCoordSize;
			m_vertices[j2].v = t_row * m_HUDTexCoordSize + m_HUDTexCoordSize;

			// Bottom-left
			m_vertices[j3].u = t_column * m_HUDTexCoordSize;
			m_vertices[j3].v = t_row * m_HUDTexCoordSize + m_HUDTexCoordSize;

		}//for()

		// Load to the memory
		int l_error = copyDataToGPU(myGarlicAlloc);
		if (l_error != SCE_OK) printf("Unable to copy model data to GPU memory: 0x%08X\n", l_error);
		else m_validData = true;
	}


	// Change offsets
	void setXOffset(float _offsetX) { m_offsetX = _offsetX; }
	void setYOffset(float _offsetY) { m_offsetY = _offsetY; }


	// Clears the data
	void deleteStoredText()
	{
		delete m_vertices;
		delete m_indices;
	}


	// Load model data to GPU memory
	int copyDataToGPU(LinearAllocator* _garlicAlloc)
	{
	// [REDACTED]

		return l_result;
	}//copyDataToGPU()


	// Set the vertex buffer descriptors 
	void vertexBuffer() {

	// [REDACTED]
	}//vertexBuffer()


	// Draw function just for the HUD Text
	// [REDACTED]

	}//draw()
};

#endif // !__PT_HUD_TEXT_ITEM__