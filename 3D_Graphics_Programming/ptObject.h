#ifndef __PT_OBJECT__
#define __PT_OBJECT__

#include "ptModel.h"
#include "ptPipeline.h"
#include "ptMaterial.h"
#include "../../toolkit/toolkit.h"

#include <gnmx.h>

// Holds the model data and its positional data in the world
class ptObject
{

public:

	ptModel* m_myModel;
	ptMaterial* m_myMaterial;

	Matrix4 m_modelWorldMx = Matrix4(0);

};
#endif // !__PT_OBJECT__

