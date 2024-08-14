#include "Path.h"

namespace Torc
{
	Path::Path(const TorcStd::string& path)
		: m_path(path.c_str())
	{
	}

	Path::Path(const char* path)
		: m_path(path)
	{
	}

	TorcStd::string Path::GetExtension()
	{
		uint32 len = m_path.Length();
		for (int i = len - 1; i > -1; --i)
		{
			if (m_path[i] == '.')
			{
				return m_path.Data() + i + 1;
			}
		}
		return {};
	}

	TorcStd::string Path::GetDirectory()
	{
		uint32 len = m_path.Length();
		for (int i = len - 1; i > -1; --i)
		{
			if (m_path[i] == '/' || m_path[i] == '\\')
			{
				return TorcStd::string(m_path.c_str(), i);
			}
		}
		return m_path.c_str();
	}

	TorcStd::string Path::GetParentDirectory()
	{
		uint32 len = m_path.Length();
		for (int i = len - 1; i > -1; --i)
		{
			const char c = m_path[i];
			if ((m_path[i] == '/' || m_path[i] == '\\') && i != len - 1)
			{
				TorcStd::string(m_path.c_str(), i);
			}
		}

		return m_path.c_str();
	}

	TorcStd::string Path::GetFilenameWithoutExtension()
	{
		uint32 len = m_path.Length();
		int dotPos = 0;
		int separatorPos = 0;

		for (int i = len - 1; i > -1; --i)
		{
			if (m_path[i] == '.')
			{
				dotPos = i;
			}
			else if (m_path[i] == '/' || m_path[i] == '\\')
			{
				separatorPos = i;
				break;
			}
		}

		if (separatorPos > dotPos)
		{
			return {};
		}

		return TorcStd::string(m_path.Data() + separatorPos + 1, dotPos - separatorPos - 1);
	}

	TorcStd::string Path::GetFilename()
	{
		uint32 len = m_path.Length();
		int dotPos = 0;
		int separatorPos = 0;
		for (int i = len - 1; i > -1; --i)
		{
			if (m_path[i] == '.')
			{
				dotPos = i;
			}
			else if (m_path[i] == '/' || m_path[i] == '\\')
			{
				separatorPos = i;
				break;
			}
		}

		if (separatorPos > dotPos || dotPos == 0)
		{
			return {};
		}

		return TorcStd::string(m_path.Data() + separatorPos + 1, len - separatorPos - 1);
	}

	TorcStd::string Path::ConvertToWindows()
	{
		uint32 len = m_path.Length();

		TorcStd::string newStr;
		newStr.resize(len);

		for (int i = len - 1; i > -1; --i)
		{
			if (m_path[i] == '/')
			{
				newStr[i] = '\\';
			}
			else
			{
				newStr[i] = m_path[i];
			}
		}
		return newStr;
	}

	TorcStd::string Path::ConvertToPOSIX()
	{
		uint32 len = m_path.Length();

		TorcStd::string newStr;
		newStr.resize(len);

		for (int i = len - 1; i > -1; --i)
		{
			if (m_path[i] == '\\')
			{
				newStr[i] = '/';
			}
			else
			{
				newStr[i] = m_path[i];
			}
		}
		return newStr;
	}

	PathView Path::GetView() const
	{
		return m_path;
	}

	Path Path::operator+(const Path& rhs)
	{
		return Path(TorcStd::string{m_path.c_str()} + TorcStd::string{ rhs.m_path.c_str()});
	}
}