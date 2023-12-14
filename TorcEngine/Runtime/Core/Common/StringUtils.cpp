#include "pch.h"
#include "StringUtils.h"

std::wstring string::utils::ConvertToWideChar(const std::string& src)
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

std::string string::utils::ConvertToChar(const std::wstring& src)
{
	size_t size = (src.size() + 1) * 2;
	size_t ret;
	char* converted = new char[size];
	int res = wcstombs_s(&ret, converted, (src.size() + 1) * 2, src.c_str(), src.size() * 2);
	
	if (res == 0)
	{
		std::string str(converted);
		delete converted;
		return str;
	}
	else
	{
		delete converted;
		LOG_WARN(LogChannel::LC_Core, "String Conversion failed");
		return "";
	}
}