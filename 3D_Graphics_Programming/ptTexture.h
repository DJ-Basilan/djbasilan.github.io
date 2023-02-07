#ifndef __PT_TEXTURE__
#define __PT_TEXTURE__

#include <gnmx.h>
#include "ptAssetType.h"

using namespace sce;

// Holds the texture data for the Object and Material
class ptTexture {


public:
	Gnm::Texture m_texture;
	const char* m_filename = NULL;
	PT_ASSET_TYPE m_assetType = PT_ASSET_TYPE::TEXTURE_GNF;
	bool m_validData = false;
	uint8_t textureIndex = 0;

};

#endif // !__PT_TEXTURE__
