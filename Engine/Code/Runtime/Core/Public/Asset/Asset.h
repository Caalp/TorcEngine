#pragma once

#include <Singleton/Singleton.h>
#include <Base.h>
#include <IO/FileIOBase.h>
#include <Logging/Logger.h>

#include <FreeImage/FreeImage.h>


#define TE_SINGLETON(_class, _uuid, ...)\
	friend class Singleton<_class>;

namespace TE
{

	struct DirectoryRegistry
	{
		enum For
		{
			Image,
			Sound,
			Shader,
			Material
		};

		TEStd::string ToString(For type)
		{
			switch (type)
			{
			case For::Image:
			return "img";
			case For::Sound:
			return "sound:";
			default:
			return "";
			}
		}

		TEStd::string GetCurrentDir() const;
		void SetCurrentDir(const TEStd::string& path);

		TEStd::string GetAssetFolderPath() const;
		void SetAssetFolderPath(const TEStd::string& path) const;

	};

	class Asset
	{
	public:
		enum class Type
		{
			Image,
			Mesh,
			Animation,
			Sound,
			Unknown
		};

		enum class State
		{
			Preload,
			Loading,
			Loaded,
			Unloaded,
			Unknown
		};

		static TEStd::RefCountedPtr<Asset> Create(std::string name, const std::string& filepath);

		State GetState();
		bool IsLoaded();
		
		uint32 GetRefCount() const;
		uint32 GetSize();
		uint64 GetId() const;
		const TEStd::string& GetPath() const;
		const TEStd::string& GetFullPath() const;
		Name GetName() const;
		Type GetAssetType() const;

		//GetStatus
	protected:
		Name m_name;
		TEStd::string m_path;
		State m_assetState;
	};

	struct Result
	{
		enum
		{
			Fail,
			Success
		};

		uint64 ownerId; // task owner class Id
		uint64 taskId;
		uint64 creatorId; // requesterId
	};

	struct LoadTask
	{
		TEStd::RefCountedPtr<TE::Asset> m_asset;
	};

	struct Job
	{

	};

	struct Receipt
	{

	};

	class JobManager
	{
	public:
		struct Config
		{
			int32 m_numberOfWorkers;
		};

		void Configure(const Config& config);
		void Reconfigure(const Config& config);
		bool IsConfigured() const;

		Receipt* Submit(const Job& job);
		bool IsComplete(const Receipt& receipt) const;
		void QueryResult(const Receipt& receipt);
		Receipt* Schedule(const Job& job);
	private:
		// NOTE(Cagri): temporarily use thread safe task queue
		

	};
	
	static Asset::Type GetAssetTypeFromFilename(const std::string& file)
	{
		size_t idx = file.rfind('.');
		if (idx == -1)
		{
			//TE_Warning("Asset", "Asset file doesn't have an extension, type deemed as unknown");
			return Asset::Type::Unknown;
		}

		std::string extension = file.substr(idx+1, file.length() - idx);

		if (extension == "bmp" || extension == "png" || extension == "jpeg")
		{
			return Asset::Type::Image;
		}
	}

	static TEStd::string GetFileExtensionFromFilename(const TEStd::string& file)
	{
		size_t idx = file.rfind('.');
		if (idx == -1)
		{
			//TE_Warning("Asset", "Asset file doesn't have an extension, type deemed as unknown");
			return "";
		}

		return file.substr(idx + 1, file.length() - idx);
	}

	struct AssetInfo
	{
		Asset::Type m_type = Asset::Type::Unknown;
		TE::Name m_name;
		TEStd::string m_absolutePath;
		TEStd::string m_relativePath;
	};

	class AssetManager final
	{
		TE_SINGLETON(AssetManager, "UUID");
	public:
		//TE_CLASS(AssetManager, "UUID", Parents);

		static AssetManager& Init()
		{
			return *Singleton<AssetManager>::Get();
		}

		uint64 Load(const AssetInfo& assetInfo)
		{
			return 0;
		}

		uint64 Unload(const AssetInfo& assetInfo);
		uint64 FindOrLoad(const AssetInfo& info);

		bool IsLoaded(TE::Name assetName) const;
		TEStd::RefCountedPtr<Asset> GetAssetByName(TE::Name name) const;
		const AssetInfo& GetAssetInfo(TE::Name name) const;

		~AssetManager() = default;
	protected:
		AssetManager() = default;

		int32 m_taskCount;

	};

	template<typename TLoader>
	class AssetLoader
	{
	public:

	private:
		TLoader m_loaderClass;

	};

	/*
	* Asset loader class that uses FreeImage library to load the images
	*/
	class ImageAssetLoader
	{
		
	public:

		// loads image by first reading image file into memory and
		// after loading, gets pixel bytes and returns it

		// returns image info and byte color data array
		uint8* Load(const AssetInfo& info)
		{
			//if (info.m_relativePath.empty() && info.m_absolutePath.empty())
			//{
			//	// invalid path
			//	return nullptr;
			//}

			//TEStd::string pathToUse;
			//bool isUsingAbsPath = false;
			//if (!info.m_absolutePath.empty())
			//{
			//	pathToUse = info.m_absolutePath;
			//	isUsingAbsPath = true;
			//}
			//else
			//{
			//	pathToUse = info.m_relativePath;
			//}

			//if (!fs::IsFileExist(pathToUse.c_str()))
			//{
			//	if (!isUsingAbsPath)
			//	{
			//		pathToUse = info.m_relativePath;
			//		if (!fs::IsFileExist(pathToUse.c_str()))
			//		{
			//			// file is not exists in the given path
			//			return nullptr;
			//		}
			//	}
			//}

			//TORC_HANDLE fileHandle = fs::OpenFile(pathToUse.c_str(), FileAccessMode::Access_Read, FileShareMode::Share_None, FileCreationFlag::Open_Existing);

			//uint8* data = nullptr;
			//uint32 size = 0;
			//if (fs::IsOpen(fileHandle))
			//{
			//	size = fs::GetSize(fileHandle);
			//	data = new uint8[size];
			//	uint32 bytesRead = fs::ReadFile(fileHandle, data, size);

			//	if (bytesRead != size)
			//	{
			//		delete data;
			//		fs::CloseFile(fileHandle);
			//		return nullptr;
			//	}
			//	fs::CloseFile(fileHandle);
			//}


			////FreeImage_Initialise();
			//FIBITMAP* bmp = nullptr;
			//FIMEMORY* fimem = FreeImage_OpenMemory(data, size);
			//if (data)
			//{
			//	TEStd::string extension = GetFileExtensionFromFilename(pathToUse);
			//	
			//	auto pair = s_extensionToImageFormat.find(extension);
			//	if (pair == s_extensionToImageFormat.end())
			//	{
			//		delete data;
			//		FreeImage_DeInitialise();
			//		FreeImage_CloseMemory(fimem);
			//		return nullptr;
			//	}
			//	bmp = FreeImage_LoadFromMemory(pair->second, fimem);
			//}

			//if (!bmp)
			//{
			//	TE_Warning(LogChannel::LC_Core, "FreeImage_LoadFromMemory returned null!");
			//	delete data;
			//	FreeImage_DeInitialise();
			//	FreeImage_CloseMemory(fimem);
			//	return nullptr;
			//}
			//else
			//{
			//	uint32 width = FreeImage_GetWidth(bmp);
			//	uint32 height = FreeImage_GetHeight(bmp);

			//	uint32 pixelSize = FreeImage_GetBPP(bmp);

			//	if (pixelSize != 32)
			//	{
			//		FIBITMAP* oldImage = bmp;
			//		bmp = FreeImage_ConvertTo32Bits(oldImage);
			//		FreeImage_Unload(oldImage);
			//	}	

			//	int32 totalSize = width*height*(FreeImage_GetBPP(bmp) / 8);
			//	uint8* imageData = new uint8[totalSize];		

			//	Torc::Platform::MemCopy(imageData, FreeImage_GetBits(bmp), totalSize);
			//	FreeImage_Unload(bmp);

			//	return imageData;;
			//}
			return nullptr;
		}

		// loads image from byte array of image file
		uint8* Load(const uint8* bytes)
		{

		}

	private:
		static const std::map<TEStd::string, FREE_IMAGE_FORMAT> s_extensionToImageFormat;
	};

	template<class T>
	T* Singleton<T>::m_instance = nullptr;
}
