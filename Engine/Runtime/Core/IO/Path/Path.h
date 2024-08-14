#pragma once
#include "Core/Base.h"
#include "Core/TorcStd/String/string.h"

namespace Torc
{
	static constexpr int MaxPathLength = 1024;
	typedef CString<MaxPathLength> PathView;

	//! Represents generic Path type for platform with specific path length
	class Path
	{
	public:
		Path() = default;
		Path(const TorcStd::string& path);
		Path(const char* path);
		TorcStd::string GetExtension();
		TorcStd::string GetDirectory();
		TorcStd::string GetParentDirectory();
		TorcStd::string GetFilenameWithoutExtension();
		TorcStd::string GetFilename();
		TorcStd::string ConvertToWindows();
		TorcStd::string ConvertToPOSIX();
		PathView GetView() const;

		Path operator+(const Path& rhs);
	private:
		 PathView m_path;
	};
}
