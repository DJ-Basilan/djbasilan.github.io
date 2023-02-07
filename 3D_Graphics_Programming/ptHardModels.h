
#ifndef __PT_HARD_MODELS__
#define __PT_HARD_MODELS__

#include <scebase.h>

#include "ptVertex.h"


// Define typing for the shapes
enum class PT_HARD_MODEL
{
	CUBE,
	TETRA,
	OCTA,
	ICOS,
	CUBE_PVC,
	TETRA_PVC,
	OCTA_PVC,
	ICOS_PVC
};//PT_HARD_MODEL


// The actual vertex data - a CUBE
static ptVertex s_vertexDataCube[] =
{
	//     Position                     COLOUR
	//  X      Y      Z          R     G     B
	{ -1.0f,  1.0f,  1.0f,		1.0f, 0.0f, 0.0f},			//A-0 alpha
	{ -1.0f, -1.0f,  1.0f,		1.0f, 0.0f, 0.0f}, 			//B-1 alpha
	{  1.0f, -1.0f,  1.0f,		1.0f, 0.0f, 0.0f},			//C-2 alpha
	{  1.0f,  1.0f,  1.0f,		1.0f, 0.0f, 0.0f},			//D-3 alpha

	{  1.0f,  1.0f,  1.0f,		0.0f, 1.0f, 0.0f},			//D-4 beta
	{  1.0f, -1.0f,  1.0f,		0.0f, 1.0f, 0.0f},			//C-5 beta
	{  1.0f, -1.0f, -1.0f,		0.0f, 1.0f, 0.0f},			//F-6 beta
	{  1.0f,  1.0f, -1.0f,		0.0f, 1.0f, 0.0f},			//E-7 beta

	{  1.0f,  1.0f, -1.0f,		0.0f, 0.0f, 1.0f},			//E-8 gamma
	{  1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 1.0f},			//F-9 gamma
	{ -1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 1.0f},			//G-10 gamma
	{ -1.0f,  1.0f, -1.0f,		0.0f, 0.0f, 1.0f},			//H-11 gamma

	{ -1.0f,  1.0f, -1.0f,		1.0f, 0.0f, 1.0f},			//H-12 delta
	{ -1.0f, -1.0f, -1.0f,		1.0f, 0.0f, 1.0f},			//G-13 delta
	{ -1.0f, -1.0f,  1.0f,		1.0f, 0.0f, 1.0f},			//B-14 delta
	{ -1.0f,  1.0f,  1.0f,		1.0f, 0.0f, 1.0f},			//A-15 delta

	{ -1.0f,  1.0f, -1.0f,		1.0f, 1.0f, 0.0f},			//H-16 epsilon
	{ -1.0f,  1.0f,  1.0f,		1.0f, 1.0f, 0.0f},			//A-17 epsilon
	{  1.0f,  1.0f,  1.0f,		1.0f, 1.0f, 0.0f},			//D-18 epsilon
	{  1.0f,  1.0f, -1.0f,		1.0f, 1.0f, 0.0f},			//E-19 epsilon

	{ -1.0f, -1.0f,  1.0f,		0.0f, 1.0f, 1.0f},			//B-20 zeta
	{ -1.0f, -1.0f, -1.0f,		0.0f, 1.0f, 1.0f},			//G-21 zeta
	{  1.0f, -1.0f, -1.0f,		0.0f, 1.0f, 1.0f},			//F-22 zeta
	{  1.0f, -1.0f,  1.0f,		0.0f, 1.0f, 1.0f},			//C-23 zeta

};//sc_vertexData[]

// Index data, defines triangles to produce a CUBE - PS4 uses triangles to draw objects
static uint16_t s_indexDataCube[] =
{
	0, 1, 2,	// alpha
	0, 2, 3,	// 

	4, 5, 6,	// beta
	4, 6, 7,	// 

	8, 9, 10,	// gamma
	8, 10, 11,	// 

	12, 13, 14,	// delta
	12, 14, 15,	// 

	16, 17, 18,	// epsilon
	16, 18, 19,	// 

	20, 21, 22,	// zeta
	20, 22, 23,	// 

};//sc_indexData[]


// The actual vertex data - an OCTAHEDRON
static ptVertex s_vertexDataOcta[] =
{
	//     Position                     COLOUR
	//  X      Y      Z          R     G     B

	// Faces starting at front (0, 0, 1)
	{  0.0f,  0.0f,  1.0f,		1.0f, 0.0f, 0.0f}, 	//A-0 alpha - red
	{  0.0f,  1.0f,  0.0f,		1.0f, 0.0f, 0.0f}, 	//B-1 alpha
	{ -1.0f,  0.0f,  0.0f,		1.0f, 0.0f, 0.0f},	//C-2 alpha
	{  0.0f,  0.0f, -1.0f,		1.0f, 0.0f, 0.0f},	//F-3 alpha - back

	{  0.0f,  0.0f,  1.0f,		0.0f, 1.0f, 0.0f},	//A-4 bravo - green
	{ -1.0f,  0.0f,  0.0f,		0.0f, 1.0f, 0.0f},	//C-5 bravo
	{  0.0f, -1.0f,  0.0f,		0.0f, 1.0f, 0.0f},	//D-6 bravo
	{  0.0f,  0.0f, -1.0f,		0.0f, 1.0f, 0.0f},	//F-7 bravo - back

	{  0.0f,  0.0f,  1.0f,		0.0f, 0.0f, 1.0f},	//A-8 charlie - blue
	{  0.0f, -1.0f,  0.0f,		0.0f, 0.0f, 1.0f},	//D-9 charlie
	{  1.0f,  0.0f,  0.0f,		0.0f, 0.0f, 1.0f},	//E-10 charlie
	{  0.0f,  0.0f, -1.0f,		0.0f, 0.0f, 1.0f},	//F-11 charlie - back

	{  0.0f,  0.0f,  1.0f,		1.0f, 0.0f, 1.0f},	//A-12 delta - magenta
	{  1.0f,  0.0f,  0.0f,		1.0f, 0.0f, 1.0f},	//E-13 delta
	{  0.0f,  1.0f,  0.0f,		1.0f, 0.0f, 1.0f},	//B-14 delta
	{  0.0f,  0.0f, -1.0f,		1.0f, 0.0f, 1.0f},	//F-15 delta - back

	// Faces starting at back (0, 0, -1)
	{  0.0f,  0.0f, -1.0f,		1.0f, 1.0f, 0.0f},	//F-16 echo - yellow
	{  0.0f,  1.0f,  0.0f,		1.0f, 1.0f, 0.0f},	//B-17 echo
	{  1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 0.0f},	//E-18 echo
	{  0.0f,  0.0f, 1.0f,		1.0f, 1.0f, 0.0f},	//A-19 echo - front

	{  0.0f,  0.0f, -1.0f,		0.0f, 1.0f, 1.0f},	//F-20 foxtrot - cyan
	{  1.0f,  0.0f,  0.0f,		0.0f, 1.0f, 1.0f},	//E-21 foxtrot
	{  0.0f, -1.0f,  0.0f,		0.0f, 1.0f, 1.0f},	//D-22 foxtrot
	{  0.0f,  0.0f, 1.0f,		0.0f, 1.0f, 1.0f},	//A-23 foxtrot - front

	{  0.0f,  0.0f, -1.0f,		1.0f, 0.28f, 0.0f},	//F-24 golf - orange
	{  0.0f, -1.0f,  0.0f,		1.0f, 0.28f, 0.0f},	//D-25 golf
	{ -1.0f,  0.0f,  0.0f,		1.0f, 0.28f, 0.0f},	//C-26 golf
	{  0.0f,  0.0f, 1.0f,		1.0f, 0.28f, 0.0f},	//A-27 golf - front

	{  0.0f,  0.0f, -1.0f,		0.0f, 0.0f, 0.0f},	//F-28 hotel - black (try it)
	{ -1.0f,  0.0f,  0.0f,		0.0f, 0.0f, 0.0f},	//C-29 hotel
	{  0.0f,  1.0f,  0.0f,		0.0f, 0.0f, 0.0f},	//B-30 hotel
	{  0.0f,  0.0f, 1.0f,		0.0f, 0.0f, 0.0f},	//A-31 hotel - front

};//sc_vertexData[]

// Index data, defines triangles to produce an OCTAHEDRON
static uint16_t s_indexDataOcta[] =
{
	0, 1, 2,	// alpha

	4, 5, 6,	// bravo

	8, 9, 10,	// charlie

	12, 13, 14,	// delta

	16, 17, 18, // echo

	20, 21, 22, // foxtrot

	24, 25, 26, // golf

	28, 29, 30, // hotel

};//sc_indexData[]


// The actual vertex data - a TETRAHEDRON
static ptVertex s_vertexDataTetra[] =
{
	//     Position                     COLOUR
	//  X      Y      Z          R     G     B

	// Faces reference: ABC(D) - BDC(A) - CDA(B) - DBA(C) 
	{ -1.0f,  1.0f,  1.0f,		1.0f, 0.0f, 0.0f}, 	//A-0 alpha - red
	{  1.0f, -1.0f,  1.0f,		1.0f, 0.0f, 0.0f}, 	//B-1 alpha
	{  1.0f,  1.0f, -1.0f,		1.0f, 0.0f, 0.0f},	//C-2 alpha
	{ -1.0f, -1.0f, -1.0f,		1.0f, 0.0f, 0.0f},	//D-3 alpha - cube corner

	{  1.0f, -1.0f,  1.0f,		0.0f, 1.0f, 0.0f},	//B-4 bravo - green
	{ -1.0f, -1.0f, -1.0f,		0.0f, 1.0f, 0.0f},	//D-5 bravo
	{  1.0f,  1.0f, -1.0f,		0.0f, 1.0f, 0.0f},	//C-6 bravo
	{ -1.0f,  1.0f,  1.0f,		0.0f, 1.0f, 0.0f},	//A-7 bravo - cube corner

	{  1.0f,  1.0f, -1.0f,		0.0f, 0.0f, 1.0f},	//C-8 charlie - blue
	{ -1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 1.0f},	//D-9 charlie
	{ -1.0f,  1.0f,  1.0f,		0.0f, 0.0f, 1.0f},	//A-10 charlie
	{  1.0f, -1.0f,  1.0f,		0.0f, 0.0f, 1.0f},	//B-11 charlie - cube corner

	{ -1.0f, -1.0f, -1.0f,		1.0f, 0.0f, 1.0f},	//D-12 delta - magenta
	{  1.0f, -1.0f,  1.0f,		1.0f, 0.0f, 1.0f},	//B-13 delta
	{ -1.0f,  1.0f,  1.0f,		1.0f, 0.0f, 1.0f},	//A-14 delta
	{  1.0f,  1.0f, -1.0f,		1.0f, 0.0f, 1.0f},	//C-15 delta - cube corner

};//sc_vertexData[]

// Index data, defines triangles to produce a TETRAHEDRON
static uint16_t s_indexDataTetra[] =
{
	0, 1, 2,	// alpha

	4, 5, 6,	// bravo

	8, 9, 10,	// charlie

	12, 13, 14,	// delta

};//sc_indexData[]


// The actual vertex data - an ICOSAHEDRON (D20)
static ptVertex s_vertexDataIcos[] =
{
	//     Position                     COLOUR					
	//   X       Y       Z           R     G     B     		 
	{ 1.618, 1.0, 0.0, 0.7, 0.0, 0.0, },//0 A
	{ 0.0, 1.618, 1.0, 0.7, 0.0, 0.0, },//1 B
	{ 1.0, 0.0, 1.618, 0.7, 0.0, 0.0, },//2 C

	{ 1.618, 1.0, 0.0, 0.0, 0.7, 0.0, },//3 A
	{ 1.0, 0.0, -1.618, 0.0, 0.7, 0.0, },//4 D
	{ 0.0, 1.618, -1.0, 0.0, 0.7, 0.0, },//5 E

	{ 1.618, -1.0, 0.0, 0.0, 0.0, 0.7, },//6 F
	{ 1.0, 0.0, 1.618, 0.0, 0.0, 0.7, },//7 C
	{ 0.0, -1.618, 1.0, 0.0, 0.0, 0.7, },//8 G

	{ 1.618, -1.0, 0.0, 0.5, 0.0, 0.0, },//9 F
	{ 0.0, -1.618, -1.0, 0.5, 0.0, 0.0, },//10 H
	{ 1.0, 0.0, -1.618, 0.5, 0.0, 0.0, },//11 D

	{ -1.618, 1.0, 0.0, 0.0, 0.5, 0.0, },//12 I
	{ -1.0, 0.0, 1.618, 0.0, 0.5, 0.0, },//13 J
	{ 0.0, 1.618, 1.0, 0.0, 0.5, 0.0, },//14 B

	{ -1.618, 1.0, 0.0, 0.0, 0.0, 0.5, },//15 I
	{ 0.0, 1.618, -1.0, 0.0, 0.0, 0.5, },//16 E
	{ -1.0, 0.0, -1.618, 0.0, 0.0, 0.5, },//17 K

	{ -1.618, -1.0, 0.0, 0.5, 0.5, 0.0, },//18 L
	{ 0.0, -1.618, 1.0, 0.5, 0.5, 0.0, },//19 G
	{ -1.0, 0.0, 1.618, 0.5, 0.5, 0.0, },//20 J

	{ -1.618, -1.0, 0.0, 0.5, 0.0, 0.5, },//21 L
	{ -1.0, 0.0, -1.618, 0.5, 0.0, 0.5, },//22 K
	{ 0.0, -1.618, -1.0, 0.5, 0.0, 0.5, },//23 H

	{ 1.618, 1.0, 0.0, 0.0, 0.5, 0.5, },//24 A
	{ 0.0, 1.618, -1.0, 0.0, 0.5, 0.5, },//25 E
	{ 0.0, 1.618, 1.0, 0.0, 0.5, 0.5, },//26 B

	{ -1.618, 1.0, 0.0, 0.7, 0.2, 0.0, },//27 I
	{ 0.0, 1.618, 1.0, 0.7, 0.2, 0.0, },//28 B
	{ 0.0, 1.618, -1.0, 0.7, 0.2, 0.0, },//29 E

	{ 1.618, -1.0, 0.0, 0.7, 0.0, 0.2, },//30 F
	{ 0.0, -1.618, 1.0, 0.7, 0.0, 0.2, },//31 G
	{ 0.0, -1.618, -1.0, 0.7, 0.0, 0.2, },//32 H

	{ -1.618, -1.0, 0.0, 0.2, 0.7, 0.0, },//33 L
	{ 0.0, -1.618, -1.0, 0.2, 0.7, 0.0, },//34 H
	{ 0.0, -1.618, 1.0, 0.2, 0.7, 0.0, },//35 G

	{ 1.0, 0.0, 1.618, 0.0, 0.7, 0.2, },//36 C
	{ 1.618, -1.0, 0.0, 0.0, 0.7, 0.2, },//37 F
	{ 1.618, 1.0, 0.0, 0.0, 0.7, 0.2, },//38 A

	{ 1.0, 0.0, -1.618, 0.2, 0.0, 0.7, },//39 D
	{ 1.618, 1.0, 0.0, 0.2, 0.0, 0.7, },//40 A
	{ 1.618, -1.0, 0.0, 0.2, 0.0, 0.7, },//41 F

	{ -1.0, 0.0, 1.618, 0.0, 0.2, 0.7, },//42 J
	{ -1.618, 1.0, 0.0, 0.0, 0.2, 0.7, },//43 I
	{ -1.618, -1.0, 0.0, 0.0, 0.2, 0.7, },//44 L

	{ -1.0, 0.0, -1.618, 0.7, 0.5, 0.2, },//45 K
	{ -1.618, -1.0, 0.0, 0.7, 0.5, 0.2, },//46 L
	{ -1.618, 1.0, 0.0, 0.7, 0.5, 0.2, },//47 I

	{ 0.0, 1.618, 1.0, 0.7, 0.2, 0.5, },//48 B
	{ -1.0, 0.0, 1.618, 0.7, 0.2, 0.5, },//49 J
	{ 1.0, 0.0, 1.618, 0.7, 0.2, 0.5, },//50 C

	{ 0.0, -1.618, 1.0, 0.5, 0.7, 0.2, },//51 G
	{ 1.0, 0.0, 1.618, 0.5, 0.7, 0.2, },//52 C
	{ -1.0, 0.0, 1.618, 0.5, 0.7, 0.2, },//53 J

	{ 0.0, 1.618, -1.0, 0.2, 0.7, 0.5, },//54 E
	{ 1.0, 0.0, -1.618, 0.2, 0.7, 0.5, },//55 D
	{ -1.0, 0.0, -1.618, 0.2, 0.7, 0.5, },//56 K

	{ 0.0, -1.618, -1.0, 0.5, 0.2, 0.7, },//57 H
	{ -1.0, 0.0, -1.618, 0.5, 0.2, 0.7, },//58 K
	{ 1.0, 0.0, -1.618, 0.5, 0.2, 0.7, },//59 D
};//sc_vertexData[]

// Index data, defines triangles to produce a ICOSAHEDRON (D20)
static uint16_t s_indexDataIcos[] =
{
	0, 1, 2,
	3, 4, 5,
	6, 7, 8,
	9, 10, 11,
	12, 13, 14,
	15, 16, 17,
	18, 19, 20,
	21, 22, 23,
	24, 25, 26,
	27, 28, 29,
	30, 31, 32,
	33, 34, 35,
	36, 37, 38,
	39, 40, 41,
	42, 43, 44,
	45, 46, 47,
	48, 49, 50,
	51, 52, 53,
	54, 55, 56,
	57, 58, 59,
};//sc_indexData[]


//========================== 3D Shapes with Per-Vertex colour (PVC) =================
// Interpolating the colour between the vertices, no need to colour each face

// Vertex data for a CUBE
static ptVertex s_vertexDataCubePVC[] =
{
	//     Position                     COLOUR					
	//  X      Y      Z          R     G     B     		 
	{ -1.0f,  1.0f,  1.0f, 	   1.0f, 0.0f, 0.0f, },//A- 0,
	{ -1.0f, -1.0f,  1.0f,     0.0f, 1.0f, 0.0f, },//B- 1,
	{  1.0f, -1.0f,  1.0f,     0.0f, 0.0f, 1.0f, },//C- 2,
	{  1.0f,  1.0f,  1.0f,     1.0f, 1.0f, 0.0f, },//D- 3,
	{  1.0f,  1.0f, -1.0f,     1.0f, 0.0f, 1.0f, },//E- 4,
	{  1.0f, -1.0f, -1.0f,     0.0f, 1.0f, 1.0f, },//F- 5,
	{ -1.0f, -1.0f, -1.0f,     0.5f, 0.0f, 0.7f, },//G- 6,
	{ -1.0f,  1.0f, -1.0f,     0.0f, 0.8f, 0.2f, },//H- 7,
};//sc_vertexData[]

// Draw the triangles for the CUBE - Looks like a Smash Cube
static uint16_t s_indexDataCubePVC[] =
{
	0, 1, 2,	//ABC
	0, 2, 3,	//ACD
	5, 3, 2,	//FDC
	5, 4, 3,	//FED
	4, 5, 6,	//EFG
	4, 6, 7,	//EGH
	7, 6, 1,	//HGB
	7, 1, 0,	//HBA
	3, 7, 0,	//DHA
	3, 4, 7,	//DEH
	1, 6, 5,	//BGF
	1, 5, 2,	//BFC
};//sc_indexData[]


// The actual vertex data - an OCTAHEDRON with per-vertex colour
static ptVertex s_vertexDataOctaPVC[] =
{
	//     Position                     COLOUR
	//  X      Y      Z          R     G     B

	{  0.0f,  0.0f,  1.0f,		1.0f, 0.0f, 0.0f}, 	//A-0 red
	{  0.0f,  1.0f,  0.0f,		0.0f, 1.0f, 0.0f}, 	//B-1 blue
	{ -1.0f,  0.0f,  0.0f,		1.0f, 0.0f, 1.0f},	//C-2 green
	{  0.0f, -1.0f,  0.0f,		1.0f, 1.0f, 0.0f},	//D-3 yellow
	{  1.0f,  0.0f,  0.0f,		0.0f, 1.0f, 1.0f},	//E-4 cyan
	{  0.0f,  0.0f, -1.0f,		1.0f, 0.0f, 1.0f},	//F-5 magenta

};//sc_vertexData[]

// Index data, defines triangles to produce an OCTAHEDRON with interpolated colours
static uint16_t s_indexDataOctaPVC[] =
{
	0, 1, 2,	// ABC

	0, 2, 3,	// ACD

	0, 3, 4,	// ADE

	0, 4, 1,	// AEB

	5, 1, 4,	// FBE

	5, 4, 3,	// FED

	5, 3, 2,	// FDC

	5, 2, 1,	// FCB

};//sc_indexData[]


// The actual vertex data - a TETRAHEDRON with per-vertex colour
static ptVertex s_vertexDataTetraPVC[] =
{
	//     Position                     COLOUR
	//  X      Y      Z          R     G     B

	{ -1.0f,  1.0f,  1.0f,		1.0f, 0.0f, 0.0f}, 	//A-0 red
	{  1.0f, -1.0f,  1.0f,		0.0f, 1.0f, 0.0f}, 	//B-1 blue
	{  1.0f,  1.0f, -1.0f,		0.0f, 0.0f, 1.0f},	//C-2 green
	{ -1.0f, -1.0f, -1.0f,		1.0f, 1.0f, 0.0f},	//D-3 yellow - cube corner

};//sc_vertexData[]

// Index data, defines triangles to produce a TETRAHEDRON with interpolated colours
static uint16_t s_indexDataTetraPVC[] =
{
	0, 1, 2,	// ABC

	1, 3, 2,	// BDC

	2, 3, 0,	// CDA

	3, 1, 0,	// DBA

};//sc_indexData[]


// Vertex data of the D20 with per-vertex colour
static ptVertex s_vertexDataIcosPVC[] =
{
	//     Position                     COLOUR					
	//   X       Y       Z           	R     G     B     		 
	{	1.618,  1.0,    0.0,		0.7,  0.0,  0.0, },// A 0,
	{  0.0,    1.618,  1.0,			0.0,  0.5,  0.0, },// B 1,
	{	1.0,    0.0,    1.618,		0.0,  0.0,  0.7, },// C 2,
	{	1.0,    0.0,   -1.618,		0.0,  0.7,  0.0, },// D 3,
	{  0.0,    1.618, -1.0,			0.0,  0.0,  0.5, },// E 4,
	{	1.618, -1.0,    0.0,		0.5,  0.0,  0.0, },// F 5,
	{	0.0,  -1.618,  1.0,			0.5,  0.5,  0.0, },// G 6,
	{  0.0,   -1.618, -1.0,			0.5,  0.0,  0.5, },// H 7,
	{ -1.618,	1.0,    0.0,		0.7,  0.2,  0.0, },// I 8,
	{ -1.0,    0.0,    1.618,		0.0,  0.2,  0.7, },// J 9,
	{ -1.0,    0.0,   -1.618,		0.7,  0.5,  0.2, },// K 10,
	{ -1.618,  -1.0,    0.0,		0.2,  0.7,  0.0, },// L 11,
};//sc_vertexData[]

// Draw the triangles with interpolated colours for the D20
static uint16_t s_indexDataIcosPVC[] =
{
	  0, 1, 2, // ABC
	  0, 3, 4, // ADE
	  5, 2, 6, // FCG
	  5, 7, 3, // FHD
	  8, 9, 1, // IJB
	  8, 4, 10, // IEK
	  11, 6, 9, // LGJ
	  11, 10, 7, // LKH
	  0, 4, 1, // AEB
	  8, 1, 4, // IBE
	  5, 6, 7, // FGH
	  11, 7, 6, // LHG
	  2, 5, 0, // CFA
	  3, 0, 5, // DAF
	  9, 8, 11, // JIL
	  10, 11, 8, // KLI
	  1, 9, 2, // BJC
	  6, 2, 9, // GCJ
	  4, 3, 10, // EDK
	  7, 10, 3, // HKD
};//sc_indexData[]

#endif // !__PT_HARD_MODELS__
