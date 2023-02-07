#ifndef __PT_MODEL__
#define __PT_MODEL__

#include <scebase.h>
#include "../../common/allocator.h"
#include "../../common/danFileParser.h"
#include "../../common/danRandom.h"
#include "../../common/danOBJHelpers.h"
using namespace sce;

#include "ptVertex.h"
#include "ptHardModels.h"
#include "ptAssetType.h"

// Main class
class ptModel
{
	size_t m_onionMemorySize = 16 * 1024 * 1024;

public:		// Reminder: Anything before this line is private
	// Vertex data
	ptVertex* m_vertices = NULL;
	uint16_t m_vertexCount = 0;
	size_t m_verticesSize = 0;
	ptVertex* m_verticesGPU;

	// Indices data
	uint16_t* m_indices = NULL;
	uint32_t m_indexCount = 0;
	size_t m_indicesSize = 0;
	uint16_t* m_indicesGPU;

	ptTriangle* m_triangles;

	// For ptAssetManager
	const char* m_filename;
	PT_ASSET_TYPE m_assetType;

	// Allows model creator to specify to use default or no colour 
	bool m_oneColour = false;
	bool m_noColour = false;
	bool m_randomColour = false;

	// Default colour
	Vector3 m_defaultColour = { 0.5, 0.5, 0.5 };

	// Model positioning
	bool m_centralizePositions = false;
	bool m_normalizePositions = false;

	// Model's normals
	bool m_generateNormals = false;

	// Model's texture coordinates
	bool m_gotTexcoords = false;

	// Set to TRUE to allow messages to be shown in the PS4 output
	bool m_verbose = false;

	// Flag for triangle data in PTM
	bool m_genSequentialTris = false;

	// Initialize the vertex buffers pointing to each vertex element
	// these are used to map the input data to the vertex shader 
	// [REDACTED]

	bool m_validData = false;


	// Loads the model if it is called in the Main program
	void loadIfNeeded(LinearAllocator* _garlicAlloc)
	{
		if (m_assetType == PT_ASSET_TYPE::MODEL_PTM)
		{
			loadModelPTM(m_filename, _garlicAlloc);
		}
		if (m_assetType == PT_ASSET_TYPE::MODEL_OBJ)
		{
			loadModelOBJ(m_filename, _garlicAlloc);
		}
	}


	// Loads the vertex and index data of the different 3D shapes
	void loadHardModel(PT_HARD_MODEL _model, LinearAllocator* _garlicAlloc)
	{
		switch(_model)
		{
		case PT_HARD_MODEL::CUBE:
			m_vertices = s_vertexDataCube;
			m_verticesSize = sizeof(s_vertexDataCube);

			m_indices = s_indexDataCube;
			m_indicesSize = sizeof(s_indexDataCube);
			break;

		case PT_HARD_MODEL::CUBE_PVC:
			m_vertices = s_vertexDataCubePVC;
			m_verticesSize = sizeof(s_vertexDataCubePVC);

			m_indices = s_indexDataCubePVC;
			m_indicesSize = sizeof(s_indexDataCubePVC);
			break;

		case PT_HARD_MODEL::OCTA:
			m_vertices = s_vertexDataOcta;
			m_verticesSize = sizeof(s_vertexDataOcta);

			m_indices = s_indexDataOcta;
			m_indicesSize = sizeof(s_indexDataOcta);
			break;

		case PT_HARD_MODEL::OCTA_PVC:
			m_vertices = s_vertexDataOctaPVC;
			m_verticesSize = sizeof(s_vertexDataOctaPVC);

			m_indices = s_indexDataOctaPVC;
			m_indicesSize = sizeof(s_indexDataOctaPVC);
			break;

		case PT_HARD_MODEL::TETRA:
			m_vertices = s_vertexDataTetra;
			m_verticesSize = sizeof(s_vertexDataTetra);

			m_indices = s_indexDataTetra;
			m_indicesSize = sizeof(s_indexDataTetra);
			break;

		case PT_HARD_MODEL::TETRA_PVC:
			m_vertices = s_vertexDataTetraPVC;
			m_verticesSize = sizeof(s_vertexDataTetraPVC);

			m_indices = s_indexDataTetraPVC;
			m_indicesSize = sizeof(s_indexDataTetraPVC);
			break;

		case PT_HARD_MODEL::ICOS:
			m_vertices = s_vertexDataIcos;
			m_verticesSize = sizeof(s_vertexDataIcos);

			m_indices = s_indexDataIcos;
			m_indicesSize = sizeof(s_indexDataIcos);
			break;

		case PT_HARD_MODEL::ICOS_PVC:
			m_vertices = s_vertexDataIcosPVC;
			m_verticesSize = sizeof(s_vertexDataIcosPVC);

			m_indices = s_indexDataIcosPVC;
			m_indicesSize = sizeof(s_indexDataIcosPVC);
			break;

		default:
			printf("No model data found\n");
			break;
		}//switch()

		// Count calculators
		m_vertexCount = m_verticesSize / sizeof(m_vertices[0]);
		m_indexCount = m_indicesSize / sizeof(m_indices[0]);

		int check = copyDataToGPU(_garlicAlloc);	// Call the method and execute its tasks

		// Verify that valid data has been processed
		// Sizes of the vertices and indices must be at least 3 to cover
		// and draw at least one triangle
		if(check == SCE_OK && m_verticesSize >= 3 && m_indicesSize >= 3) {
			m_validData = true;
		}//if(copyDataToGPU == SCE_OK...)

	}//loadHardModel()


	// Load model from PTM file
	int loadModelPTM(const char* _filename, LinearAllocator* _garlicAlloc)
	{
		int l_error = SCE_OK;

		// Local variable - Memory allocator
		LinearAllocator myOnionAllocator;
			// [REDACTED]

		if (l_error != SCE_OK) { printf("Onion allocator failed to initialise: 0x%08X\n", l_error);  return l_error; }

		// File Parser
		danFileParser myDFP;
		l_error = myDFP.openFile(_filename);

		char l_lineType;

		// Counters for the PTM Model's:
		int pCnt = 0;	// Vertex Position (P)
		int cCnt = 0;	// Colour (C)
		int tCnt = 0;	// Triangle description (T)
		int nCnt = 0;	// Normals (N)
		int uCnt = 0;	// Texture Coordinates (U)

		char l_word[50];
		

		// Check status
		if (l_error != SCE_OK)
		{
			printf("Unable to load file in model\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		// First pass
		while (!myDFP.atEOF()) {
			if (myDFP.getChar(l_lineType)) {
				switch (l_lineType)
				{
				case 'P':
					pCnt++;
					break;

				case 'C':
					cCnt++;
					break;

				case 'T':
					tCnt++;
					break;

				case 'N':
					nCnt++;
					break;

				case 'U':
					uCnt++;
					break;

				case 'X':
					if (myDFP.getWord(l_word))
					{
						if (myDFP.stringCompare(l_word, "CENTRALIZE")) m_centralizePositions = true;
						if (myDFP.stringCompare(l_word, "NORMALIZE")) m_normalizePositions = true;
						if (myDFP.stringCompare(l_word, "SINGLE_COLOUR")) m_oneColour = true;
						if (myDFP.stringCompare(l_word, "NO_COLOUR")) m_noColour = true;
						if (myDFP.stringCompare(l_word, "RANDOM_COLOUR")) m_randomColour = true;

						if (myDFP.stringCompare(l_word, "GEN_SEQUENTIAL_TRIS")) m_genSequentialTris = true;

						if (myDFP.stringCompare(l_word, "GEN_SPLAYED_NORMALS")) m_generateNormals = true;
						if (myDFP.stringCompare(l_word, "GEN_NORMALS")) m_generateNormals = true;
					}//if
					break;
				}//switch()

			}//if()
			myDFP.nextLine();
		}//while()

		// Report data found from the first pass of the PTM file
		if (m_verbose) printf("found %i positions, %i colours and %i normals in %i triangles\n",
			pCnt, cCnt, nCnt, tCnt);

		if (nCnt != pCnt) m_generateNormals = true;

		// Transfer vertex data to Onion Allocator
		m_vertexCount = pCnt;
		m_verticesSize = m_vertexCount * sizeof(ptVertex);
		m_vertices = (ptVertex*)myOnionAllocator.allocate(m_verticesSize, Gnm::kAlignmentOfBufferInBytes);
		if (!m_vertices)
		{
			printf("Unable to allocate memory for m_vertices in ptModel::loadModelPTM\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		// Transfer index data to Onion Allocator
		m_indexCount = tCnt * 3;
		m_indicesSize = m_indexCount * sizeof(uint16_t);
			// [REDACTED]

		if (!m_indices)
		{
			printf("Unable to allocate memory for m_indices in ptModel::loadModelPTM\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		// Report back the status of the memory allocation
		if (m_verbose) {
			printf("Memory allocated: %i for vertices, %i for indices\n",
				(int)m_verticesSize, (int)m_indicesSize);
		}

		// Prepare valid data checkers -------------------------------
		// One way... (Ends at 'myOnionAllocator.terminate()')

		// NOTE: These are actually incorrect because they use the same instance, meaning they end up overwriting each other
		// Position data checker
	// [REDACTED]



		// Or another... (Ends at 'delete[] pCheck') - The more reliable method
		// NOTE: The more reliable method

		// Data checkers
		bool* pCheck = new bool[m_vertexCount];
		bool* cCheck = new bool[m_vertexCount];
		bool* nCheck = new bool[m_vertexCount];
		bool* tCheck = new bool[tCnt];
		bool* uCheck = new bool[m_vertexCount];

		// Sets all elements to false
		for (int i = 0; i < m_vertexCount; i++) {
			pCheck[i] = false;
			cCheck[i] = false;
			nCheck[i] = false;
			uCheck[i] = false;
		}
		for (int i = 0; i < tCnt; i++) {
			tCheck[i] = false;
		}
		// END Valid Data Checkers ----------------------------------------------------------------

		// Prep for second pass
		myDFP.reset();

		m_triangles = (ptTriangle*)m_indices;

		// Variables for the second pass
		int index = 0;
		float a, b, c = 0.0f;
		int t1, t2, t3 = 0;

		// Second pass
		while (!myDFP.atEOF()) {
			if (myDFP.getChar(l_lineType)) {
				switch (l_lineType)
				{
				case 'P':
					// Guard to prevent creation of an element out of bounds
					if (index > m_vertexCount) {
						printf("Position index out of range\n");
						return SCE_ERROR_ERROR_FLAG;
					}

					// Extract the next 'P' line
					if (myDFP.getInt(index) && myDFP.getFloat(a) && myDFP.getFloat(b) && myDFP.getFloat(c))
					{
						// Another (one) guard
						if (pCheck[index]) printf("Duplicate position for index %i, replacing previous data\n", index);

						// Assign the X, Y, and Z coordinates of the vertices in the current index
						m_vertices[index].x = a;
						m_vertices[index].y = b;
						m_vertices[index].z = c;

						// Print current index and its data
						if (m_verbose) printf("Position[%i] = (%f, %f, %f)\n", index, a, b, c);
						pCheck[index] = true;
					}//if()
					else {
						pCheck[index] = false;
					}
					break;

				case 'C':
					// Guards to prevent creation of an element out of bounds
					if (index > m_vertexCount) {		// Uses pCnt not cCnt due to possibility of more colours than positions
						printf("Colour index out of range\n");
						return SCE_ERROR_ERROR_FLAG;
					}

					// Extract the next 'C' line
					if (myDFP.getInt(index) && myDFP.getFloat(a) && myDFP.getFloat(b) && myDFP.getFloat(c))
					{
						// Otherwise assign the RGB colours as normal
						m_vertices[index].r = a;
						m_vertices[index].g = b;
						m_vertices[index].b = c;

						// Print current index and its data
						if (m_verbose) printf("Colour[%i] = (%f, %f, %f)\n", index, a, b, c);
						cCheck[index] = true;
					}//if
					else {
						cCheck[index] = false;
					}
					break;

				case 'N':
					// Guard to prevent creation of an element out of bounds
					if (index > m_vertexCount) {
						printf("Normal (N) index out of range\n");
						return SCE_ERROR_ERROR_FLAG;
					}

					// Extract the next 'N' line
					if (myDFP.getInt(index) && myDFP.getFloat(a) && myDFP.getFloat(b) && myDFP.getFloat(c))
					{
						// Another (one) guard
						if (nCheck[index]) printf("Duplicate normal for index %i, replacing previous data\n", index);

						// Assign the X, Y, and Z coordinates of the vertices in the current index
						m_vertices[index].nx = a;
						m_vertices[index].ny = b;
						m_vertices[index].nz = c;

						// Print current index and its data
						if (m_verbose) printf("Normal[%i] = (%f, %f, %f)\n", index, a, b, c);
						nCheck[index] = true;
					}//if()
					else {
						nCheck[index] = false;
					}
					break;

				case 'U':
					// Guard to prevent creation of an element out of bounds
					if (index > m_vertexCount) {
						printf("Texcoord (U) index out of range\n");
						return SCE_ERROR_ERROR_FLAG;
					}

					// Extract the next 'U' line
					if (myDFP.getInt(index) && myDFP.getFloat(a) && myDFP.getFloat(b))
					{
						// Another (one) guard
						if (uCheck[index]) printf("Duplicate texcoord for index %i, replacing previous data\n", index);

						// Assign the X, Y, and Z coordinates of the vertices in the current index
						m_vertices[index].u = a;
						m_vertices[index].v = b;

						// Print current index and its data
						if (m_verbose) printf("Texcoord[%i] = (%f, %f)\n", index, a, b);
						uCheck[index] = true;
					}//if()
					else {
						uCheck[index] = false;
					}
					break;

				case 'T':
					// Ignore the T lines of the PTM file if this flag is active
					if (m_genSequentialTris) {
						break;
					}

					// Extract the next 'T' line
					if (myDFP.getInt(index) && myDFP.getInt(t1) && myDFP.getInt(t2) && myDFP.getInt(t3))
					{
						// Guards to prevent creation of an element out of bounds
						if (index > tCnt) {
							printf("Triangle index out of range\n");
							return SCE_ERROR_ERROR_FLAG;
						}
						if (tCheck[index]) {
							printf("Duplicate of Triangle index %i was found - Please check PTM file: %s\n", index, _filename);
							return SCE_ERROR_ERROR_FLAG;
						}

						// Check indices of vertex data - Blank comments are there for clarity of the IF statement
						if (t1 < 0 || t1 > (m_vertexCount - 1))
						{
							printf("Invalid FIRST Vertex data (%i) found at Triangle[%i], "
								"integer must be non-negative and no more than %i - Please check PTM file: %s\n",
								t1, index, (m_vertexCount - 1), _filename);
							return SCE_ERROR_ERROR_FLAG;
						}//if()
						if (t2 < 0 || t2 > (m_vertexCount - 1))
						{
							printf("Invalid SECOND Vertex data (%i) found at Triangle[%i], "
								"integer must be non-negative and no more than %i - Please check PTM file: %s\n",
								t2, index, (m_vertexCount - 1), _filename);
							return SCE_ERROR_ERROR_FLAG;
						}//if()
						if (t3 < 0 || t3 > (m_vertexCount - 1))
						{
							printf("Invalid THIRD Vertex data (%i) found at Triangle[%i], "
								"integer must be non-negative and no more than %i - Please check PTM file: %s\n",
								t3, index, (m_vertexCount - 1), _filename);
							return SCE_ERROR_ERROR_FLAG;
						}//if()

						// Assign the X, Y, and Z coordinates of the vertices in the current index
						m_triangles[index].a = t1;
						m_triangles[index].b = t2;
						m_triangles[index].c = t3;

						// Print current index and its data
						if (m_verbose) printf("Triangle[%i] = (%i, %i, %i)\n", index, t1, t2, t3);
						tCheck[index] = true;
					}//if
					else {
						tCheck[index] = false;
					}
					break;

				case 'X':

					break;
					
				//default:
					//printf("Data does not belong in Position (P), Colour (C) or Triangle (T)\n");
					//break;
				}//switch()

			}//if()
			myDFP.nextLine();
		}//while()

		// ------------------------------------------------DATA GENERATION / VALIDATION------------------------------------------------
		
		// Centralise and/or Normalise the positioning of the model' vertices according to conditions met
		if (m_centralizePositions) centralizePositions();
		if (m_normalizePositions) normalizePositions();

		// Validate the position data and its normals
		for (int i = 0; i < m_vertexCount; i++) {
			if (!pCheck[i]) {
				printf("Invalid vertex data found at P[%i]\n", i);
				return SCE_ERROR_ERROR_FLAG;
			}
			//printf("P-check: %d, at index %i\n", pCheck[i], i);	// Checking the status of the pCheck elements for testing purposes
		}//for()

		// Same as above but for normals data specifically
		for (int i = 0; i < m_vertexCount; i++) {
			if (!nCheck[i]) {
				printf("Normals data missing from the model's data. Generating normals...\n");
				m_generateNormals = true;
				break;
			}
		}

		// Same as above but for texcoord specifically
		for (int i = 0; i < m_vertexCount; i++) {
			if (!pCheck[i]) {
				m_gotTexcoords = false;
				printf("Missing Texcoord found at: U[%i]\n", i);
				break;
			}
			else m_gotTexcoords = true;
		}

		// Check that a colour exists in the first C line
		if (m_oneColour && !cCheck[0]) { m_oneColour = false; m_noColour = true; }
		
		// Fill colour vertices according to conditions met
		if (m_oneColour) fillColour(Vector3(m_vertices[0].r, m_vertices[0].g, m_vertices[0].b));
		else if (m_noColour) fillColour(m_defaultColour);
		else if (m_randomColour) fillRandomColour();

		// Check through colour array if both colour checks are false
		if(!m_oneColour && !m_noColour && !m_randomColour) {
			for (int i = 0; i < m_vertexCount; i++) {
				if (!cCheck[i]) {
					// Fill all vertices with default colour
					m_vertices[i].r = m_defaultColour[0];
					m_vertices[i].g = m_defaultColour[1];
					m_vertices[i].b = m_defaultColour[2];

					printf("A missing colour vertex has been detected on C-%i. All colour vertices in this index have been set to default (GREY)\n", i);
				}//if()
			}//for()
		}//else()

		// Validate the position data
		for (int i = 0; i < m_vertexCount; i++) {
			
			//printf("P-check: %d, at index %i\n", pCheck[i], i);	// Checking the status of the pCheck elements for testing purposes
		}

		// Use sequential triangle generator if the related flag
		if (m_genSequentialTris) {
			genSequentialTriangles(&myOnionAllocator, pCnt);
			if (m_verbose) printf("GEN_SEQUENTIAL_TRIS was active in PTM file: %s - Sequential Triangles were generated\n", _filename);
		}

		// Generate normals for the model if the flag has been triggered
		if (m_generateNormals) generateNormals();
		// ----------------------------------------------END DATA GENERATION / VALIDATION----------------------------------------------

		// Transfer data from second pass to Garlic Allocator
		l_error = copyDataToGPU(_garlicAlloc);
		if (l_error != SCE_OK)
		{
			printf("Unable to copy model data to GPU memory: 0x%08X\n", l_error); 
			return l_error;
		}

		// Protects the Draw Manager against bad data
		if ((m_vertexCount > 2) && (m_indexCount > 2)) m_validData = true;

		// End processes
		myOnionAllocator.terminate();
		delete[] pCheck;
		delete[] cCheck;
		delete[] tCheck;

		if (m_verbose) printf("PTM Model successfully loaded ----------------------\n\n");

		return l_error;
	}//loadModelPTM()


	// Load model from OBJ file
	int loadModelOBJ(const char* _filename, LinearAllocator* _garlicAlloc)
	{
		int l_error = SCE_OK;

		m_centralizePositions = true;
		m_normalizePositions = true;

		// Local variable - Memory allocator
		LinearAllocator myOnionAllocator;
			// [REDACTED]

		if (l_error != SCE_OK) { printf("Onion allocator failed to initialise: 0x%08X\n", l_error);  return l_error; }

		// File Parser
		danFileParser myDFP;
		l_error = myDFP.openFile(_filename);

		// Counters for the OBJ Model's:
		int l_pCnt = 0;		// Vertex positions
		int l_uCnt = 0;		// Vertex texture coordinates
		int l_nCnt = 0;		// Vertex normals

		int l_fCnt = 0;		// Faces
		int l_tCnt = 0;		// Triangles
		int l_vCnt = 0;		// Vertex index sets

		char l_lineType[50];		// Read in the data type
		char l_vertexString[50];	// For vertex-index triples
		float a, b, c = 0.0f;		// For float data
		int l_smoothingGroup;		// Keep a track of the smoothing group

		// Check status
		if (l_error != SCE_OK)
		{
			printf("Unable to load file in model\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		// First pass
		while (!myDFP.atEOF())
		{
			if (myDFP.getWord(l_lineType))
			{
				if (myDFP.stringCompare(l_lineType, "v"))
				{
					l_pCnt++;
				}
				if (myDFP.stringCompare(l_lineType, "vt"))
				{
					l_uCnt++;
				}
				if (myDFP.stringCompare(l_lineType, "vn"))
				{
					l_nCnt++;
				}
				if (myDFP.stringCompare(l_lineType, "f"))
				{
					int counter = 0;

					// Increment counter for every string found in 'f' line
					while (myDFP.getWordNoNewLine(l_vertexString)) counter++;

					// Count the...
					l_vCnt += counter;			// Triples
					l_tCnt += counter - 2;		// Number of triangles in current face
					l_fCnt++;					// Faces
				}
			}//if()
			myDFP.nextLine();
		}//while()

		// Report data found from the first pass of the OBJ file
		if (m_verbose) printf("Found %i positions, %i texcoords and %i normals\n",
			l_pCnt, l_uCnt, l_nCnt);
		if (m_verbose) printf("Found %i triangles, in %i faces (using %i vertices)\n",
			l_tCnt, l_fCnt, l_vCnt);

		if (l_nCnt == 0) m_generateNormals = true;

		// ------------------------------------------------------ MEMORY ALLOCATION ------------------------------------------------------
		// Memory allocation for vertex position data (V-Count)
		size_t t_objPosSize = l_pCnt * sizeof(danObjPosition);
			// [REDACTED]

		if (!l_objPositions)
		{
			printf("Unable to allocate memory for ObjPositions in ptModel::loadModelOBJ\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		// Memory allocation for vertex texcoord data (U-Count)
		size_t t_objTexcoordSize = l_uCnt * sizeof(danObjTexcoord);
			// [REDACTED]

		if (!l_objTexcoords)
		{
			printf("Unable to allocate memory for ObjTexcoord in ptModel::loadModelOBJ\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		// Memory allocation for vertex normal data (N-Count)
		size_t t_objNormSize = l_nCnt * sizeof(danObjNormal);
			// [REDACTED]

		if (!l_objNormals)
		{
			printf("Unable to allocate memory for ObjNormal in ptModel::loadModelOBJ\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		// Memory allocation for vertex triples data (V-Count)
		size_t t_objTrplSize = l_vCnt * sizeof(danObjTriple);
			// [REDACTED]

		if (!l_objTriples)
		{
			printf("Unable to allocate memory for ObjTriple in ptModel::loadModelOBJ\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		// 'm_indices' memory. This is will eventually be the final index data
		// Indices will start by using indices to danObjTriple objects
		m_indexCount = l_tCnt * 3;
		m_indicesSize = sizeof(uint16_t) * m_indexCount;
			// [REDACTED]

		if (!m_indices)
		{
			printf("Unable to allocate memory for m_indices in ptModel::loadModelOBJ\n");
			return SCE_ERROR_ERROR_FLAG;
		}
		// ---------------------------------------------------- END MEMORY ALLOCATION ----------------------------------------------------

		myDFP.reset();		// Prep for second pass

		m_triangles = (ptTriangle*)m_indices;

		// Reset all counters
		l_pCnt = 0;		// Vertex positions
		l_uCnt = 0;		// Vertex texture coordinates
		l_nCnt = 0;		// Vertex normals
		l_fCnt = 0;		// Faces
		l_tCnt = 0;		// Triangles
		l_vCnt = 0;		// Vertex index sets

		// Second pass
		while (!myDFP.atEOF())
		{
			if (myDFP.getWord(l_lineType))
			{
				if (myDFP.stringCompare(l_lineType, "v"))
				{
					// Extract the next 'v' line
					if (myDFP.getFloat(a) && myDFP.getFloat(b) && myDFP.getFloat(c))
					{
						// Assign the positional coordinates of the vertices in the current index
						l_objPositions[l_pCnt].x = a;
						l_objPositions[l_pCnt].y = b;
						l_objPositions[l_pCnt].z = c;

						// Print current index and its data
						if (m_verbose) printf("Position[%i] = (%f, %f, %f)\n", l_pCnt, a, b, c);

						l_pCnt++;
					}
				}
				if (myDFP.stringCompare(l_lineType, "vt"))
				{
					// Extract the next 'vt' line
					if (myDFP.getFloat(a) && myDFP.getFloat(b))
					{
						// Assign the vertex texture coordinates of the vertices in the current index
						l_objTexcoords[l_uCnt].u = 1 - a;
						l_objTexcoords[l_uCnt].v = 1 - b;

						// Print current index and its data
						if (m_verbose) printf("Texcoord[%i] = (%f, %f, %f)\n", l_uCnt, a, b, c);

						l_uCnt++;
					}
				}
				if (myDFP.stringCompare(l_lineType, "vn"))
				{
					// Extract the next 'vn' line
					if (myDFP.getFloat(a) && myDFP.getFloat(b) && myDFP.getFloat(c))
					{
						// Assign the vertex normals coordinates of the vertices in the current index
						l_objNormals[l_nCnt].x = a;
						l_objNormals[l_nCnt].y = b;
						l_objNormals[l_nCnt].z = c;

						// Print current index and its data
						if (m_verbose) printf("Normals[%i] = (%f, %f, %f)\n", l_nCnt, a, b, c);

						l_nCnt++;
					}
				}
				if (myDFP.stringCompare(l_lineType, "s"))
				{
					myDFP.getInt(l_smoothingGroup);
					if (l_smoothingGroup < 0 || l_smoothingGroup > __UINT16_MAX__)
					{
						l_smoothingGroup = 0;
					}

					// Print current index and its data
					if (m_verbose) printf("Smoothing Group = (%i)\n", l_smoothingGroup);
				}
				if (myDFP.stringCompare(l_lineType, "f"))
				{
					int t_counter = 0;
					int t_triA = l_vCnt;

					// Parse index data into the ptObjTriples structure
					while (myDFP.getWordNoNewLine(l_vertexString))
					{
						l_objTriples[l_vCnt].parseTriple(l_vertexString, l_pCnt, l_uCnt, l_nCnt, l_smoothingGroup);
						t_counter++;
						l_vCnt++;
					}

					// Create triangles from faces - the logic here is that each face is a triangle fan
					int t_secondCounter = 2;
					while (t_secondCounter < t_counter)
					{
						m_triangles[l_tCnt].a = t_triA;
						m_triangles[l_tCnt].b = t_triA + t_secondCounter - 1;
						m_triangles[l_tCnt].c = t_triA + t_secondCounter;
						t_secondCounter++;
						l_tCnt++;
					}

					if (m_verbose) printf("Face[%i] = Triangles(%i, %i, %i)\n",
						l_fCnt, t_triA, (t_triA + t_secondCounter - 1), (t_triA + t_secondCounter));

					l_fCnt++;
				}
			}//if()
			myDFP.nextLine();
		}//while()

		// ------------------------------------------------DATA GENERATION / VALIDATION------------------------------------------------

		// Centralise and/or Normalise the positioning of the model' vertices according to conditions met
		if (m_centralizePositions) centralizePositions();
		if (m_normalizePositions) normalizePositions();

		// Stage to compress data, by removing duplicate triples
		if (m_verbose) printf("\nCompressing triples data to remove duplicates. Please wait...\n");

		// Find duplicates
		for (int i = 0; i < l_vCnt; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (l_objTriples[i].matchAndMark(&l_objTriples[j], j))
				{
					if (m_verbose) printf("Triple %i is a duplicate of %i\n", i, j);
					j = i;
				}
			}//for(j)
		}//for(i)

		// Mark the "real index" on originals by iterating through them
		int l_rCnt = 0;
		for (int i = 0; i < l_vCnt; i++)
		{
			if (!l_objTriples[i].m_duplicate)
			{
				l_objTriples[i].m_realIndex = l_rCnt;
				l_rCnt++;
			}//if()
		}//for()

		// Create memory for the final vertex data
		m_vertexCount = l_rCnt;
		m_verticesSize = sizeof(ptVertex)*m_vertexCount;
			// [REDACTED]

		if (!m_vertices)
		{
			printf("Unable to allocate memory for m_vertices in ptModel::loadModelOBJ\n");
			return SCE_ERROR_ERROR_FLAG;
		}

		// Copy vertex data from intermediate arrays to final array 
		// Use counter to ONLY transfer the originals and not duplicates 
		int t_counter = 0;
		for (int i = 0; i < l_vCnt; i++)
		{
			if (!l_objTriples[i].m_duplicate)
			{
				if (l_objTriples[i].m_gotPosition)
				{
					m_vertices[t_counter].x = l_objPositions[l_objTriples[i].m_positionIndex].x;
					m_vertices[t_counter].y = l_objPositions[l_objTriples[i].m_positionIndex].y;
					m_vertices[t_counter].z = l_objPositions[l_objTriples[i].m_positionIndex].z;
				}
				t_counter++;
			}//if()
			if (l_objTriples[i].m_gotNormal)
			{
				m_vertices[i].nx = l_objNormals[i].x;
				m_vertices[i].ny = l_objNormals[i].y;
				m_vertices[i].nz = l_objNormals[i].z;
			}
			if (l_objTriples[i].m_gotTexcoord)
			{
				m_vertices[i].u = l_objTexcoords[i].u;
				m_vertices[i].v = l_objTexcoords[i].v;
			}
		}//for()

		// Correct the indices in m_indices to point to correct places in m_vertices
		for (int i = 0; i < m_indexCount; i++)
		{
			if (l_objTriples[m_indices[i]].m_duplicate) m_indices[i] = l_objTriples[l_objTriples[m_indices[i]].m_duplicateIndex].m_realIndex;
			else m_indices[i] = l_objTriples[m_indices[i]].m_realIndex;
		}//for

		// Generate random colours 
		if (m_randomColour) { 
			fillRandomColour();
			printf("Random Colour flag set to ON for OBJ model\n");
		}
		else if (m_noColour) {
			fillColour(m_defaultColour);
			printf("No Colour flag set to ON for OBJ model\n");
		}
		//else if (!m_noColour && !m_randomColour) { fillColour(m_defaultColour); printf("Colour flags set to OFF for OBJ model\n"); }

		// Generate normals for the model if the flag has been triggered
		if (m_generateNormals) generateNormals();
		// ----------------------------------------------END DATA GENERATION / VALIDATION----------------------------------------------

		l_error = copyDataToGPU(_garlicAlloc);
		if (l_error != SCE_OK)
		{
			printf("Unable to copy model data to GPU memory: 0x%08X\n", l_error);
			return l_error;
		}

		m_validData = true;
		myOnionAllocator.terminate();

		if (m_verbose) printf("OBJ Model successfully loaded ----------------------\n\n");

		return l_error;
	}//loadModelOBJ()


	// Averages all of the positions to find the true centre of the model, which is then offset
	// from the local origin (determined by 'm_translationMatrix(x, y)' in the main draw loop)
	void centralizePositions()
	{
		float l_totalX = 0, l_averageX = 0;
		float l_totalY = 0, l_averageY = 0;
		float l_totalZ = 0, l_averageZ = 0;

		// Add all up
		for (int i = 0; i < m_vertexCount; i++)
		{
			l_totalX += m_vertices[i].x;
			l_totalY += m_vertices[i].y;
			l_totalZ += m_vertices[i].z;
		}

		// Find centre
		l_averageX = l_totalX / m_vertexCount;
		l_averageY = l_totalY / m_vertexCount;
		l_averageZ = l_totalZ / m_vertexCount;

		// Offset from local origin
		for (int i = 0; i < m_vertexCount; i++)
		{
			m_vertices[i].x -= l_averageX;
			m_vertices[i].y -= l_averageY;
			m_vertices[i].z -= l_averageZ;
		}
	}//centralizePositions()


	// TL;DR: Rescales the models so that they are all roughly same size
	// - Identifies the distance between model's true centre and the position furthest away from it
	// - using Pythagoras, all positions are then scaled up or down according to that distance
	void normalizePositions()
	{
		float l_largest = 0.0f;
		for (int i = 0; i < m_vertexCount; i++)
		{
			float t_length = sqrt((m_vertices[i].x * m_vertices[i].x) +
				(m_vertices[i].y * m_vertices[i].y) +
				(m_vertices[i].z * m_vertices[i].z));

			if (t_length > l_largest) l_largest = t_length;
		}//for
		if (m_verbose) printf("Normalizing model size by factor %f\n", l_largest);

		for (int i = 0; i < m_vertexCount; i++)
		{
			m_vertices[i].x = m_vertices[i].x / l_largest;
			m_vertices[i].y = m_vertices[i].y / l_largest;
			m_vertices[i].z = m_vertices[i].z / l_largest;
		}//for
	}//normalizePositions()


	// Sets all normals data in 'm_vertices' to 0 (zero)
	void cleanNormals()
	{
		for (int i = 0; i < m_vertexCount; i++)
		{
			m_vertices[i].nx = 0;
			m_vertices[i].ny = 0;
			m_vertices[i].nz = 0;
		}
	}//cleanNormals()


	// Generates new normals for m_vertices after a clean wipe
	void generateNormals()
	{
		cleanNormals();

		int triCount = (m_indexCount / 3);

		for (int i = 0; i < triCount; i++)
		{
			// Extract triangle vertices
			Vector3 t_A(m_vertices[m_triangles[i].a].x, m_vertices[m_triangles[i].a].y, m_vertices[m_triangles[i].a].z);
			Vector3 t_B(m_vertices[m_triangles[i].b].x, m_vertices[m_triangles[i].b].y, m_vertices[m_triangles[i].b].z);
			Vector3 t_C(m_vertices[m_triangles[i].c].x, m_vertices[m_triangles[i].c].y, m_vertices[m_triangles[i].c].z);

			// Coplanar Vectors - for identifying the normals' positioning
			Vector3 t_AB = t_B - t_A;
			Vector3 t_AC = t_C - t_A;

			// Self-explanatory (hopefully)
			Vector3 t_crossProduct = Vectormath::Scalar::Aos::cross(t_AB, t_AC);
			Vector3 t_normalized = Vectormath::Scalar::Aos::normalize(t_crossProduct);

			// Triangle point A
			m_vertices[m_triangles[i].a].nx += t_normalized.getX();
			m_vertices[m_triangles[i].a].ny += t_normalized.getY();
			m_vertices[m_triangles[i].a].nz += t_normalized.getZ();

			// Triangle point B
			m_vertices[m_triangles[i].b].nx += t_normalized.getX();
			m_vertices[m_triangles[i].b].ny += t_normalized.getY();
			m_vertices[m_triangles[i].b].nz += t_normalized.getZ();

			// Triangle point C
			m_vertices[m_triangles[i].c].nx += t_normalized.getX();
			m_vertices[m_triangles[i].c].ny += t_normalized.getY();
			m_vertices[m_triangles[i].c].nz += t_normalized.getZ();
		}

		// Move to next step
		normalizeNormals();
	}//generateNormals()


	// Normalise the generated normals
	void normalizeNormals()
	{
		for (int i = 0; i < m_vertexCount; i++)
		{
			// Extract generated normals from previous step
			Vector3 t_generatedNormals(m_vertices[i].nx, m_vertices[i].ny, m_vertices[i].nz);

			// Self-explanatory (hopefully)
			Vector3 t_normalized = Vectormath::Scalar::Aos::normalize(t_generatedNormals);

			// Re-assign the vertex normals data
			m_vertices[i].nx = t_normalized.getX();
			m_vertices[i].ny = t_normalized.getY();
			m_vertices[i].nz = t_normalized.getZ();
		}

		if (m_verbose) printf("Normals have been successfully generated\n");
	}


	// Fills colour of the model according to the 'X' line in the PTM file
	void fillColour(Vector3 _colour)
	{
		for (int i = 0; i < m_vertexCount; i++) {
			m_vertices[i].r = _colour[0];
			m_vertices[i].g = _colour[1];
			m_vertices[i].b = _colour[2];
		}

		if (m_verbose)
		{
			if (m_oneColour) printf("RGB colour for all vertices has been set to the colour of the first face\n");
			else if (m_noColour) printf("RGB colour for all vertices has been set to GREY\n");
		}
	}//fillColour()


	// Fills model with a random colour
	void fillRandomColour()
	{
		danRandom l_Random;
		for (int i = 0; i < m_vertexCount; i++)
		{
			m_vertices[i].r = l_Random.getFraction();
			m_vertices[i].g = l_Random.getFraction();
			m_vertices[i].b = l_Random.getFraction();
		}//for

		if (m_verbose) printf("RGB colour for all vertices have been randomised\n");
	}//fillColour()


	// Generate triangles in sequence - Works only for Split-Face PTM models
	void genSequentialTriangles(LinearAllocator* _onionAllocator, int _pCnt)
	{
		// Reallocate memory
		m_indicesSize = _pCnt * sizeof(uint16_t);
			// [REDACTED]


		for (int i = 0; i < _pCnt; i++) {

			m_indices[i] = i;
		}
	}//genSequentialTriangles()


	// Load model data to GPU memory
	int copyDataToGPU(LinearAllocator* _garlicAlloc)
	{
		int l_result = SCE_OK;

		// Allocate the vertex buffer memory
			// [REDACTED]


		// Allocate the index buffer memory
			// [REDACTED]


		// Check if data allocation was successful
		if (!m_verticesGPU) {
			l_result = SCE_KERNEL_ERROR_ENOMEM;
			printf("Cannot allocate vertex data\n");
		}
		if (!m_indicesGPU) {
			l_result = SCE_KERNEL_ERROR_ENOMEM;
			printf("Cannot allocate index data\n");
		}
		else {
			// Copy the vertex/index data onto the GPU mapped memory
				// [REDACTED]

						vertexBuffer();
		}

		return l_result;
	}//copyDataToGPU()


	// Set the vertex buffer descriptors 
	void vertexBuffer() {

			// [REDACTED]

	}//vertexBuffer()


	// Read position and colour data from m_verticesGPU of model
	void readVerticesGPU(PT_HARD_MODEL _modelType) {

		// Show in the console which model is being printed out
		switch (_modelType)
		{
		case PT_HARD_MODEL::CUBE:
			printf("********** Printing model data for: CUBE **********\n\n"
				"# Cube model with per-face colouring\n");
			break;

		case PT_HARD_MODEL::CUBE_PVC:
			printf("********** Printing model data for: CUBE PVC **********\n\n"
				"# Cube model with per-vertex colouring\n");
			break;

		case PT_HARD_MODEL::OCTA:
			printf("**********Printing model data for: OCTAHEDRON **********\n\n"
				"# Octahedron model with per-face colouring\n");
			break;

		case PT_HARD_MODEL::OCTA_PVC:
			printf("**********Printing model data for: OCTAHEDRON PVC **********\n\n"
				"# Octahedron model with per-vertex colouring\n");
			break;

		case PT_HARD_MODEL::TETRA:
			printf("**********Printing model data for: TETRAHEDRON **********\n\n"
				"# Tetrahedron model with per-face colouring\n");
			break;

		case PT_HARD_MODEL::TETRA_PVC:
			printf("**********Printing model data for: TETRAHEDRON (PVC) **********\n\n"
				"# Tetrahedron model with per-vertex colouring\n");
			break;

		case PT_HARD_MODEL::ICOS:
			printf("**********Printing model data for: ICOSAHEDRON **********\n\n"
				"# Icosahedron model with per-face colouring\n");
			break;

		case PT_HARD_MODEL::ICOS_PVC:
			printf("**********Printing model data for: ICOSAHEDRON (PVC) **********\n\n"
				"# Icosahedron model with per-vertex colouring\n");
			break;

		default:
			printf("No model data found\n");
			break;
		}//switch()

		// First line of the PTM file
		printf("\nX NORMALIZE\n\n");

		int counter = 0;

		// Extract the Position data
		for (int i = 0; i < m_vertexCount; i++)
		{
			// Compensate for two-digit numbers
			if (i < 10) printf("P %i ", i);
			else printf("P %i", i);

			// Compensate for negative positions
			if (m_verticesGPU[i].x < 0) printf("  %.1f", m_verticesGPU[i].x);
			else  printf("   %.1f", m_verticesGPU[i].x);

			if (m_verticesGPU[i].y < 0) printf("  %.1f", m_verticesGPU[i].y);
			else  printf("   %.1f", m_verticesGPU[i].y);

			if (m_verticesGPU[i].z < 0) printf("  %.1f\n", m_verticesGPU[i].z);
			else  printf("   %.1f\n", m_verticesGPU[i].z);
			
			// Add padding after every 4 vertices
			if (i == 3) {
				counter = i;
				printf("\n");
			}
			if ((i - counter) == 4) {
				counter = i;
				printf("\n");
			}
		}

		printf("\n");	// Padding
		counter = 0;	// Reset counter

		// Extract the Colour data
		for (int i = 0; i < m_vertexCount; i++)
		{
			// Compensate for two-digit numbers
			if (i < 10) printf("C %i ", i);
			else printf("C %i", i);

			printf("   %.1f  %.1f  %.1f\n", m_verticesGPU[i].r, m_verticesGPU[i].g, m_verticesGPU[i].b);

			// Add padding after every 4 vertices
			if (i == 3) {
				counter = i;
				printf("\n");
			}
			if ((i - counter) == 4) {
				counter = i;
				printf("\n");
			}
		}

		// Padding
		printf("\n");
	}

	// Read triangle data from m_indicesGPU of model
	void readIndicesGPU() {

		ptTriangle* t_trianglesGPU = (ptTriangle*)m_indicesGPU;

		// Extract the Colour data
		for (int i = 0; i < m_indexCount / 3; i++)
		{
			// Compensate for two-digit numbers
			if (i < 10) printf("T %i ", i);
			else printf("T %i", i);

			printf("   %i  %i  %i\n", t_trianglesGPU[i].a, t_trianglesGPU[i].b, t_trianglesGPU[i].c);
		}

		printf("# This line MUST be included for padding");

		printf("\n**********Printing COMPLETE**********\n\n");
	}

};//ptModel

#endif // !__PT_MODEL__
