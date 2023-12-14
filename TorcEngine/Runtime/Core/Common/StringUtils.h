#pragma once
namespace string::utils
{
	std::wstring ConvertToWideChar(const std::string& src);
	std::string ConvertToChar(const std::wstring& src);
}