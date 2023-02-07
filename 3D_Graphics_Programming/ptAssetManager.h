#ifndef __PT_ASSET_MANAGER__
#define __PT_ASSET_MANAGER__

#include "ptModel.h"
#include "ptAssetType.h"
#include "ptTexture.h"
#include "ptPipeline.h"
#include "ptMaterial.h"

#include "../../common/danTextureLoader.h"

class ptAssetManager {

	// [REDACTED]
	danTextureLoader myTextureLoader;
	// [REDACTED]

public:

	int l_error = SCE_OK;

	ptPipeline m_myPipeline[PT_PIPELINE_COUNT];

	ptMaterial m_myMaterial[PT_MATERIAL_COUNT];

	ptModel m_myModels[PT_MODEL_COUNT];

	ptTexture m_myTextures[PT_TEXTURE_COUNT];

	bool m_verbose = false;


	// Initialiser for use in the Main program
	void init(LinearAllocator* _garlicAlloc, sce::Gnmx::Toolkit::Allocators* _toolkitAlloc)
	{
		// Initialise the allocators
		garlicAlloc = _garlicAlloc;
		toolkitAlloc = _toolkitAlloc;
		
		// Initialise the texture sampler
	// [REDACTED]


		// PTM Models
		// Cube ----------------------------------------------------------------------------------------------------
		m_myModels[PTM_MODEL_CUBE_PVC_NC].m_filename = "/app0/assets/models/PTM/CubePVC - No Colour.ptm";
		m_myModels[PTM_MODEL_CUBE_PVC_NC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_CUBE_PVC_SC].m_filename = "/app0/assets/models/PTM/CubePVC - Single Colour.ptm";
		m_myModels[PTM_MODEL_CUBE_PVC_SC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_CUBE_SPLIT_NC].m_filename = "/app0/assets/models/PTM/CubeSplitFace - No Colour.ptm";
		m_myModels[PTM_MODEL_CUBE_SPLIT_NC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_CUBE_SPLIT_SC].m_filename = "/app0/assets/models/PTM/CubeSplitFace - Single Colour.ptm";
		m_myModels[PTM_MODEL_CUBE_SPLIT_SC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		// Tetrahedron ---------------------------------------------------------------------------------------------
		m_myModels[PTM_MODEL_TETRA_PVC_NC].m_filename = "/app0/assets/models/PTM/TetraPVC - No Colour.ptm";
		m_myModels[PTM_MODEL_TETRA_PVC_NC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_TETRA_PVC_SC].m_filename = "/app0/assets/models/PTM/TetraPVC - Single Colour.ptm";
		m_myModels[PTM_MODEL_TETRA_PVC_SC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_TETRA_SPLIT_NC].m_filename = "/app0/assets/models/PTM/TetraSplitFace - No Colour.ptm";
		m_myModels[PTM_MODEL_TETRA_SPLIT_NC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_TETRA_SPLIT_SC].m_filename = "/app0/assets/models/PTM/TetraSplitFace - Single Colour.ptm";
		m_myModels[PTM_MODEL_TETRA_SPLIT_SC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		// Octahedron ----------------------------------------------------------------------------------------------
		m_myModels[PTM_MODEL_OCTA_PVC_NC].m_filename = "/app0/assets/models/PTM/OctaPVC - No Colour.ptm";
		m_myModels[PTM_MODEL_OCTA_PVC_NC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_OCTA_PVC_SC].m_filename = "/app0/assets/models/PTM/OctaPVC - Single Colour.ptm";
		m_myModels[PTM_MODEL_OCTA_PVC_SC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_OCTA_SPLIT_NC].m_filename = "/app0/assets/models/PTM/OctaSplitFace - No Colour.ptm";
		m_myModels[PTM_MODEL_OCTA_SPLIT_NC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_OCTA_SPLIT_SC].m_filename = "/app0/assets/models/PTM/OctaSplitFace - Single Colour.ptm";
		m_myModels[PTM_MODEL_OCTA_SPLIT_SC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		// Icosahedron ---------------------------------------------------------------------------------------------
		m_myModels[PTM_MODEL_ICOS_PVC_NC].m_filename = "/app0/assets/models/PTM/IcosPVC - No Colour.ptm";
		m_myModels[PTM_MODEL_ICOS_PVC_NC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_ICOS_PVC_SC].m_filename = "/app0/assets/models/PTM/IcosPVC - Single Colour.ptm";
		m_myModels[PTM_MODEL_ICOS_PVC_SC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_ICOS_SPLIT_NC].m_filename = "/app0/assets/models/PTM/IcosSplitFace - No Colour.ptm";
		m_myModels[PTM_MODEL_ICOS_SPLIT_NC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_ICOS_SPLIT_SC].m_filename = "/app0/assets/models/PTM/IcosSplitFace - Single Colour.ptm";
		m_myModels[PTM_MODEL_ICOS_SPLIT_SC].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		// Complex -------------------------------------------------------------------------------------------------
		m_myModels[PTM_MODEL_SPHERE].m_filename = "/app0/assets/models/PTM/Sphere.ptm";
		m_myModels[PTM_MODEL_SPHERE].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_TEAPOT].m_filename = "/app0/assets/models/PTM/Teapot.ptm";
		m_myModels[PTM_MODEL_TEAPOT].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_TEDDY].m_filename = "/app0/assets/models/PTM/Teddy.ptm";
		m_myModels[PTM_MODEL_TEDDY].m_assetType = PT_ASSET_TYPE::MODEL_PTM;

		m_myModels[PTM_MODEL_FLOOR].m_filename = "/app0/assets/models/PTM/Floor.ptm";
		m_myModels[PTM_MODEL_FLOOR].m_assetType = PT_ASSET_TYPE::MODEL_PTM;


		// OBJ Models ----------------------------------------------------------------------------------------------
		m_myModels[OBJ_MODEL_AIRBOAT].m_filename = "/app0/assets/models/OBJ/airboat.obj";
		m_myModels[OBJ_MODEL_AIRBOAT].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_AL].m_filename = "/app0/assets/models/OBJ/al.obj";
		m_myModels[OBJ_MODEL_AL].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_AL_NORMALS].m_filename = "/app0/assets/models/OBJ/al-normals.obj";
		m_myModels[OBJ_MODEL_AL_NORMALS].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_CESSNA].m_filename = "/app0/assets/models/OBJ/cessna.obj";
		m_myModels[OBJ_MODEL_CESSNA].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_COW].m_filename = "/app0/assets/models/OBJ/cow.obj";
		m_myModels[OBJ_MODEL_COW].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_CUBE].m_filename = "/app0/assets/models/OBJ/cube.obj";
		m_myModels[OBJ_MODEL_CUBE].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_DODECAHEDRON].m_filename = "/app0/assets/models/OBJ/dodecahedron.obj";
		m_myModels[OBJ_MODEL_DODECAHEDRON].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_GOURD].m_filename = "/app0/assets/models/OBJ/gourd.obj";
		m_myModels[OBJ_MODEL_GOURD].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_HUMANOID_QUAD].m_filename = "/app0/assets/models/OBJ/humanoid_quad.obj";
		m_myModels[OBJ_MODEL_HUMANOID_QUAD].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_HUMANOID_TRI].m_filename = "/app0/assets/models/OBJ/humanoid_tri.obj";
		m_myModels[OBJ_MODEL_HUMANOID_TRI].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_ICOS].m_filename = "/app0/assets/models/OBJ/icosahedron.obj";
		m_myModels[OBJ_MODEL_ICOS].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_LAMP].m_filename = "/app0/assets/models/OBJ/lamp.obj";
		m_myModels[OBJ_MODEL_LAMP].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_MAGNOLIA].m_filename = "/app0/assets/models/OBJ/magnolia.obj";
		m_myModels[OBJ_MODEL_MAGNOLIA].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_OCTA].m_filename = "/app0/assets/models/OBJ/octahedron.obj";
		m_myModels[OBJ_MODEL_OCTA].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_SANDAL].m_filename = "/app0/assets/models/OBJ/sandal.obj";
		m_myModels[OBJ_MODEL_SANDAL].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_SHUTTLE].m_filename = "/app0/assets/models/OBJ/shuttle.obj";
		m_myModels[OBJ_MODEL_SHUTTLE].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_SKYSCRAPER].m_filename = "/app0/assets/models/OBJ/skyscraper.obj";
		m_myModels[OBJ_MODEL_SKYSCRAPER].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_SLOT_MACHINE].m_filename = "/app0/assets/models/OBJ/slot_machine.obj";
		m_myModels[OBJ_MODEL_SLOT_MACHINE].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_TEAPOT].m_filename = "/app0/assets/models/OBJ/teapot.obj";
		m_myModels[OBJ_MODEL_TEAPOT].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_TEDDY].m_filename = "/app0/assets/models/OBJ/teddy.obj";
		m_myModels[OBJ_MODEL_TEDDY].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;
		//m_myModels[OBJ_MODEL_TEDDY].m_generateNormals = true;

		m_myModels[OBJ_MODEL_TETRA].m_filename = "/app0/assets/models/OBJ/tetrahedron.obj";
		m_myModels[OBJ_MODEL_TETRA].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_TRUMPET].m_filename = "/app0/assets/models/OBJ/trumpet.obj";
		m_myModels[OBJ_MODEL_TRUMPET].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;

		m_myModels[OBJ_MODEL_VIOLIN_CASE].m_filename = "/app0/assets/models/OBJ/violin_case.obj";
		m_myModels[OBJ_MODEL_VIOLIN_CASE].m_assetType = PT_ASSET_TYPE::MODEL_OBJ;


		// Textures ------------------------------------------------------------------------------------------------
		m_myTextures[PT_TEXTURE_BRICK].m_filename = "/app0/assets/textures/brick.gnf";

		m_myTextures[PT_TEXTURE_COW].m_filename = "/app0/assets/textures/cow.gnf";

		m_myTextures[PT_TEXTURE_COW_TEAPOT].m_filename = "/app0/assets/textures/cowTeapot.gnf";

		m_myTextures[PT_TEXTURE_DAN].m_filename = "/app0/assets/textures/dan.gnf";

		m_myTextures[PT_TEXTURE_ASPHALT].m_filename = "/app0/assets/textures/dark_asphalt.gnf";
		
		m_myTextures[PT_TEXTURE_EARTH].m_filename = "/app0/assets/textures/earth.gnf";
		
		m_myTextures[PT_TEXTURE_GRASS].m_filename = "/app0/assets/textures/grass.gnf";

		m_myTextures[PT_TEXTURE_MERCURY].m_filename = "/app0/assets/textures/mercury.gnf";

		m_myTextures[PT_TEXTURE_MOON].m_filename = "/app0/assets/textures/moon.gnf";
		
		m_myTextures[PT_TEXTURE_OIL].m_filename = "/app0/assets/textures/oil.gnf";

		m_myTextures[PT_TEXTURE_PLUTO].m_filename = "/app0/assets/textures/eris_planet.gnf";

		m_myTextures[PT_TEXTURE_SUN].m_filename = "/app0/assets/textures/sun.gnf";
		
		m_myTextures[PT_TEXTURE_TEDDY].m_filename = "/app0/assets/textures/TeddyTexture.gnf";

		m_myTextures[PT_TEXTURE_WOOD].m_filename = "/app0/assets/textures/woodTex.gnf";

		m_myTextures[PT_TEXTURE_HUD_TEXT].m_filename = "/app0/assets/textures/oolite-font.gnf";


		// Pipelines -----------------------------------------------------------------------------------------------
		// TDM
		m_myPipeline[PT_PIPELINE_TDM].m_vertexShader_filename = "/app0/ptTDMShader_vv.sb";
		m_myPipeline[PT_PIPELINE_TDM].m_pixelShader_filename = "/app0/ptTDMShader_p.sb";
		m_myPipeline[PT_PIPELINE_TDM].m_shaderConstantType = PT_SHADER_CONSTANTS::TDM;
		//m_myPipeline[PT_PIPELINE_TDM].m_textureCount = 5;

		// VVM
		m_myPipeline[PT_PIPELINE_VVM].m_vertexShader_filename = "/app0/ptVVMShader_vv.sb";
		m_myPipeline[PT_PIPELINE_VVM].m_pixelShader_filename = "/app0/ptVVMShader_p.sb";
		m_myPipeline[PT_PIPELINE_VVM].m_shaderConstantType = PT_SHADER_CONSTANTS::VVM;

		// HUD
		m_myPipeline[PT_PIPELINE_HUD].m_vertexShader_filename = "/app0/ptHUDShader_vv.sb";
		m_myPipeline[PT_PIPELINE_HUD].m_pixelShader_filename = "/app0/ptHUDShader_p.sb";


		// Materials -----------------------------------------------------------------------------------------------
		// ...With Textures

		m_myMaterial[PT_MATERIAL_BRICK].initTextures();
		m_myMaterial[PT_MATERIAL_BRICK].setPipelineName(PT_PIPELINE_TDM, 1);
		m_myMaterial[PT_MATERIAL_BRICK].m_myTextureNames[0] = PT_TEXTURE_BRICK;

		m_myMaterial[PT_MATERIAL_COW].initTextures();
		m_myMaterial[PT_MATERIAL_COW].setPipelineName(PT_PIPELINE_TDM, 1);
		m_myMaterial[PT_MATERIAL_COW].m_myTextureNames[0] = PT_TEXTURE_COW;

		m_myMaterial[PT_MATERIAL_COW_TEAPOT].initTextures();
		m_myMaterial[PT_MATERIAL_COW_TEAPOT].setPipelineName(PT_PIPELINE_TDM, 1);
		m_myMaterial[PT_MATERIAL_COW_TEAPOT].m_myTextureNames[0] = PT_TEXTURE_COW_TEAPOT;

		m_myMaterial[PT_MATERIAL_EARTH].initTextures();
		m_myMaterial[PT_MATERIAL_EARTH].setPipelineName(PT_PIPELINE_TDM, 1);
		m_myMaterial[PT_MATERIAL_EARTH].m_myTextureNames[0] = PT_TEXTURE_EARTH;

		m_myMaterial[PT_MATERIAL_TEDDY].initTextures();
		m_myMaterial[PT_MATERIAL_TEDDY].setPipelineName(PT_PIPELINE_TDM, 1);
		m_myMaterial[PT_MATERIAL_TEDDY].m_myTextureNames[0] = PT_TEXTURE_TEDDY;

		m_myMaterial[PT_MATERIAL_OIL].initTextures();
		m_myMaterial[PT_MATERIAL_OIL].setPipelineName(PT_PIPELINE_TDM, 1);
		m_myMaterial[PT_MATERIAL_OIL].m_myTextureNames[0] = PT_TEXTURE_OIL;

		m_myMaterial[PT_MATERIAL_GRASS].initTextures();
		m_myMaterial[PT_MATERIAL_GRASS].setPipelineName(PT_PIPELINE_TDM, 1);
		m_myMaterial[PT_MATERIAL_GRASS].m_myTextureNames[0] = PT_TEXTURE_GRASS;

		m_myMaterial[PT_MATERIAL_DAN].initTextures();
		m_myMaterial[PT_MATERIAL_DAN].setPipelineName(PT_PIPELINE_TDM, 1);
		m_myMaterial[PT_MATERIAL_DAN].m_myTextureNames[0] = PT_TEXTURE_DAN;

		m_myMaterial[PT_MATERIAL_WOOD].initTextures();
		m_myMaterial[PT_MATERIAL_WOOD].setPipelineName(PT_PIPELINE_TDM, 1);
		m_myMaterial[PT_MATERIAL_WOOD].m_myTextureNames[0] = PT_TEXTURE_WOOD;
		m_myMaterial[PT_MATERIAL_WOOD].m_ambientColour = Vector3(0.23125, 0.23125, 0.23125);
		m_myMaterial[PT_MATERIAL_WOOD].m_diffuseColour = Vector3(0.2775, 0.2775, 0.2775);
		m_myMaterial[PT_MATERIAL_WOOD].m_specularColour = Vector3(0.773911, 0.773911, 0.773911);
		m_myMaterial[PT_MATERIAL_WOOD].m_specularPower = 89.6;
		m_myMaterial[PT_MATERIAL_WOOD].m_specularStrength = 100;

		m_myMaterial[PT_MATERIAL_SUN].initTextures();
		m_myMaterial[PT_MATERIAL_SUN].setPipelineName(PT_PIPELINE_TDM, 1);
		m_myMaterial[PT_MATERIAL_SUN].m_myTextureNames[0] = PT_TEXTURE_SUN;

		m_myMaterial[PT_MATERIAL_MERCURY].initTextures();
		m_myMaterial[PT_MATERIAL_MERCURY].setPipelineName(PT_PIPELINE_TDM, 1);
		m_myMaterial[PT_MATERIAL_MERCURY].m_myTextureNames[0] = PT_TEXTURE_MERCURY;

		m_myMaterial[PT_MATERIAL_MOON].initTextures();
		m_myMaterial[PT_MATERIAL_MOON].setPipelineName(PT_PIPELINE_TDM, 1);
		m_myMaterial[PT_MATERIAL_MOON].m_myTextureNames[0] = PT_TEXTURE_MOON;

		m_myMaterial[PT_MATERIAL_PLUTO].initTextures();
		m_myMaterial[PT_MATERIAL_PLUTO].setPipelineName(PT_PIPELINE_TDM, 1);
		m_myMaterial[PT_MATERIAL_PLUTO].m_myTextureNames[0] = PT_TEXTURE_PLUTO;


		m_myMaterial[PT_MATERIAL_HUD].initTextures();
		m_myMaterial[PT_MATERIAL_HUD].setPipelineName(PT_PIPELINE_HUD, 1);
		m_myMaterial[PT_MATERIAL_HUD].m_myTextureNames[0] = PT_TEXTURE_HUD_TEXT;

		// ...Without Textures
		m_myMaterial[PT_MATERIAL_VERT_COL_CHROME].initTextures();
		m_myMaterial[PT_MATERIAL_VERT_COL_CHROME].setPipelineName(PT_PIPELINE_VVM, 0);
		m_myMaterial[PT_MATERIAL_VERT_COL_CHROME].m_ambientColour = Vector3(0.25, 0.25, 0.25);
		m_myMaterial[PT_MATERIAL_VERT_COL_CHROME].m_diffuseColour = Vector3(0.4, 0.4, 0.4);
		m_myMaterial[PT_MATERIAL_VERT_COL_CHROME].m_specularColour = Vector3(0.774597, 0.774597, 0.774597);
		m_myMaterial[PT_MATERIAL_VERT_COL_CHROME].m_specularPower = 76.8;
		m_myMaterial[PT_MATERIAL_VERT_COL_CHROME].m_specularStrength = 100;

		m_myMaterial[PT_MATERIAL_VERT_COL_BRASS].initTextures();
		m_myMaterial[PT_MATERIAL_VERT_COL_BRASS].setPipelineName(PT_PIPELINE_VVM, 0);
		m_myMaterial[PT_MATERIAL_VERT_COL_BRASS].m_ambientColour = Vector3(0.329412, 0.223529, 0.027451);
		m_myMaterial[PT_MATERIAL_VERT_COL_BRASS].m_diffuseColour = Vector3(0.780392, 0.568627, 0.113725);
		m_myMaterial[PT_MATERIAL_VERT_COL_BRASS].m_specularColour = Vector3(0.992157, 0.941176, 0.807843);
		m_myMaterial[PT_MATERIAL_VERT_COL_BRASS].m_specularPower = 27.9874;
		m_myMaterial[PT_MATERIAL_VERT_COL_BRASS].m_specularStrength = 100;

		m_myMaterial[PT_MATERIAL_VERT_COL_GOLD].initTextures();
		m_myMaterial[PT_MATERIAL_VERT_COL_GOLD].setPipelineName(PT_PIPELINE_VVM, 0);
		m_myMaterial[PT_MATERIAL_VERT_COL_GOLD].m_ambientColour = Vector3(0.24725, 0.1995, 0.0745);
		m_myMaterial[PT_MATERIAL_VERT_COL_GOLD].m_diffuseColour = Vector3(0.75164, 0.60648, 0.22648);
		m_myMaterial[PT_MATERIAL_VERT_COL_GOLD].m_specularColour = Vector3(0.628281, 0.555802, 0.366065);
		m_myMaterial[PT_MATERIAL_VERT_COL_GOLD].m_specularPower = 51.2;
		m_myMaterial[PT_MATERIAL_VERT_COL_GOLD].m_specularStrength = 100;

		m_myMaterial[PT_MATERIAL_VERT_COL_EMERALD].initTextures();
		m_myMaterial[PT_MATERIAL_VERT_COL_EMERALD].setPipelineName(PT_PIPELINE_VVM, 0);
		m_myMaterial[PT_MATERIAL_VERT_COL_EMERALD].m_ambientColour = Vector3(0.0215, 0.1745, 0.0215);
		m_myMaterial[PT_MATERIAL_VERT_COL_EMERALD].m_diffuseColour = Vector3(0.07568, 0.61424, 0.07568);
		m_myMaterial[PT_MATERIAL_VERT_COL_EMERALD].m_specularColour = Vector3(0.633, 0.727811, 0.633);
		m_myMaterial[PT_MATERIAL_VERT_COL_EMERALD].m_specularPower = 76.8;
		m_myMaterial[PT_MATERIAL_VERT_COL_EMERALD].m_specularStrength = 55;

		// Ruby
		m_myMaterial[PT_MATERIAL_VERT_COL_RUBY].initTextures();
		m_myMaterial[PT_MATERIAL_VERT_COL_RUBY].setPipelineName(PT_PIPELINE_VVM, 0);
		m_myMaterial[PT_MATERIAL_VERT_COL_RUBY].m_ambientColour = Vector3(0.1745, 0.01175, 0.01175);
		m_myMaterial[PT_MATERIAL_VERT_COL_RUBY].m_diffuseColour = Vector3(0.61424, 0.04136, 0.04136);
		m_myMaterial[PT_MATERIAL_VERT_COL_RUBY].m_specularColour = Vector3(0.727811, 0.626959, 0.626959);
		m_myMaterial[PT_MATERIAL_VERT_COL_RUBY].m_specularPower = 76.8;
		m_myMaterial[PT_MATERIAL_VERT_COL_RUBY].m_specularStrength = 55;

		// Pearl
		m_myMaterial[PT_MATERIAL_VERT_COL_PEARL].initTextures();
		m_myMaterial[PT_MATERIAL_VERT_COL_PEARL].setPipelineName(PT_PIPELINE_VVM, 0);
		m_myMaterial[PT_MATERIAL_VERT_COL_PEARL].m_ambientColour = Vector3(0.25, 0.20725, 0.20725);
		m_myMaterial[PT_MATERIAL_VERT_COL_PEARL].m_diffuseColour = Vector3(1.0, 0.829, 0.829);
		m_myMaterial[PT_MATERIAL_VERT_COL_PEARL].m_specularColour = Vector3(0.296648, 0.296648, 0.296648);
		m_myMaterial[PT_MATERIAL_VERT_COL_PEARL].m_specularPower = 11.264;
		m_myMaterial[PT_MATERIAL_VERT_COL_PEARL].m_specularStrength = 92.2;


		m_myMaterial[PT_MATERIAL_VERT_COL_MATTE].initTextures();
		m_myMaterial[PT_MATERIAL_VERT_COL_MATTE].setPipelineName(PT_PIPELINE_VVM, 0);
		m_myMaterial[PT_MATERIAL_VERT_COL_MATTE].m_ambientColour = Vector3(0.19225, 0.19225, 0.19225);
		m_myMaterial[PT_MATERIAL_VERT_COL_MATTE].m_diffuseColour = Vector3(0.50754, 0.50754, 0.50754);
		m_myMaterial[PT_MATERIAL_VERT_COL_MATTE].m_specularColour = Vector3(0.508273, 0.508273, 0.508273);
		m_myMaterial[PT_MATERIAL_VERT_COL_MATTE].m_specularPower = 10;
		m_myMaterial[PT_MATERIAL_VERT_COL_MATTE].m_specularStrength = 55;

	}//init()


	// Loads the Pipeline - Works fine
	ptPipeline* getPipeline(ptPipelineEnum _pipeline)
	{
		if (m_myPipeline[_pipeline].loadShaders(toolkitAlloc, garlicAlloc) == SCE_OK) {
			if(m_verbose) printf("Pipeline successfully loaded\n");
			m_myPipeline[_pipeline].m_gotPipeline = true;
		}
		else printf("Something went wrong in ptAssetManager::getPipeline()\n");

		return &m_myPipeline[_pipeline];
	}


	// Loads the Material
	ptMaterial* getMaterial(ptMaterialsEnum _material)
	{
		//ptMaterial l_material = m_myMaterial[_material];
		ptPipeline* l_pipeline = NULL;
	// [REDACTED]

		// Check that material has been loaded
		if (!m_myMaterial[_material].m_materialLoaded)
		{
			if (m_verbose) printf("Attempting to load Material\n");

			// Redefine to shorten the reference
			int texCount = m_myMaterial[_material].m_textureCount;
			
			// Load the required pipeline
			l_pipeline = getPipeline(m_myMaterial[_material].m_pipelineName);
			m_myMaterial[_material].setPipeline(l_pipeline);

			// Insert the Texture Sampler
			m_myMaterial[_material].setSampler(&m_myTexSampler);

			// Loop through the texture names array and load the appropriate textures
			for (int i = 0; i < texCount; i++)
			{
				l_texture = getTexture(m_myMaterial[_material].m_myTextureNames[i]);
				m_myMaterial[_material].setTextureType(l_texture, i);

				if (m_verbose) printf("Loading Texture %i in ptAssetManager::getMaterial()\n", i);
			}

			// Confirm the material has been loaded
			m_myMaterial[_material].m_materialLoaded = true;

		}//if() - Check that material has been loaded
		else printf("Material could not be loaded in ptAssetManager::getMaterial()\n");

		return &m_myMaterial[_material];
	}


	// Load specified models only - Used in Main program
	ptModel* getModel(ptModelsEnum _modelName)	// _colour: r for 'random', n for 'none'
	{
		if (m_myModels[_modelName].m_assetType == PT_ASSET_TYPE::MODEL_OBJ) {
			m_myModels[_modelName].m_noColour = true;
		}

		if (!m_myModels[_modelName].m_validData)
		{
			m_myModels[_modelName].loadIfNeeded(garlicAlloc);
			return &m_myModels[_modelName];
		}
		else return &m_myModels[_modelName];
	}

	// Load specified models only - Use this to flag m_verbose from the Main program
	ptModel* getModel(ptModelsEnum _modelName, bool _useVerbose)	// _colour: r for 'random', n for 'none'
	{
		m_myModels[_modelName].m_verbose = _useVerbose;

		if (m_myModels[_modelName].m_assetType == PT_ASSET_TYPE::MODEL_OBJ) {
			m_myModels[_modelName].m_noColour = true;
		}

		if (!m_myModels[_modelName].m_validData)
		{
			m_myModels[_modelName].loadIfNeeded(garlicAlloc);
			return &m_myModels[_modelName];
		}

		return &m_myModels[_modelName];
	}

	// Uses a texture loader function from DanTextureLoader
	// [REDACTED]
	{
		if (!m_myTextures[_texture].m_validData)
		{
			l_error = myTextureLoader.loadTextureFromGnf(	// Params:
				m_myTextures[_texture].m_filename,			// Filename
				m_myTextures[_texture].textureIndex,		// Texture Index
				toolkitAlloc,								// Toolkit Allocators Object
				m_myTextures[_texture].m_texture);			// Gnm::Texture Object

			m_myTextures[_texture].m_validData = true;
		}

		printf("\n");
		return &m_myTextures[_texture].m_texture;
	}

};

#endif // !__PT_ASSET_MANAGER__
