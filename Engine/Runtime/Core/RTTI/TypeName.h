#pragma once

namespace Torc
{
	template<typename Type>
	class TypeName
	{
	private:
		static constexpr std::string_view Name()
		{
			std::string_view sv = __FUNCTION__;
			int pos0 = sv.find_first_of("<");
			int pos1 = sv.find_first_of(">");
			return sv.substr(pos0 + 1, (pos1 - pos0 - 1));
		}
	public:
		static constexpr std::string_view value = Name();
	};
}
