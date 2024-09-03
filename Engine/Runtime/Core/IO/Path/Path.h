#pragma once
#include "Core/Base.h"
#include "Core/Std/String/string.h"

namespace Torc
{
	static constexpr int MaxPathLength = 1024;
	typedef CString<MaxPathLength> PathView;

	//! Represents generic Path type for platform with specific path length
	class Path
	{
	public:
		Path() = default;
		Path(const Std::string& path);
		Path(const char* path);
		Std::string GetExtension();
		Std::string GetDirectory();
		Std::string GetParentDirectory();
		Std::string GetFilenameWithoutExtension();
		Std::string GetFilename();
		Std::string ConvertToWindows();
		Std::string ConvertToPOSIX();
		PathView GetView() const;

		Path operator+(const Path& rhs);
	private:
		 PathView m_path;
	};
}
