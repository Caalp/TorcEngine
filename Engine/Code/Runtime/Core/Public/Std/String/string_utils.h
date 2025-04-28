#pragma once
#include <string>

namespace string::utils
{
	std::wstring ConvertToWideChar(const std::string& src);
	std::string ConvertToChar(const std::wstring& src);
	bool Equal(const char* c1, const char* c2);
}