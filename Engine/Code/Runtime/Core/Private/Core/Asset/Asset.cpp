#include "Asset/Asset.h"

namespace TE
{
	const std::map<TEStd::string, FREE_IMAGE_FORMAT> ImageAssetLoader::s_extensionToImageFormat =
	{
		{"png", FREE_IMAGE_FORMAT::FIF_PNG},
		{"jpg", FREE_IMAGE_FORMAT::FIF_JPEG},
		{"jpeg", FREE_IMAGE_FORMAT::FIF_JPEG},
		{"bmp", FREE_IMAGE_FORMAT::FIF_BMP},
		{"dds", FREE_IMAGE_FORMAT::FIF_DDS}
	};

	TEStd::RefCountedPtr<Asset> Asset::Create(std::string name, const std::string& filepath)
	{
		TEStd::RefCountedPtr<Asset> asset = std::make_shared<Asset>();
		asset->m_name = name;
		asset->m_path = filepath;
		return asset;
	}
}
