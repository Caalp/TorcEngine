#include "pch.h"

#include "Common/StringUtils.h"

std::wstring String::Utils::ConvertToWideChar(const std::string& src)
{
	std::wstring wstr(src.size() + 1, 0);
	size_t numOfCharsConverted;
	mbstowcs_s(&numOfCharsConverted, wstr.data(), (size_t)(src.size()+1), src.c_str(), src.size());
	if (numOfCharsConverted > 0)
	{
		wstr.resize(numOfCharsConverted - 1);
		return wstr;
	}
	return {};
}
