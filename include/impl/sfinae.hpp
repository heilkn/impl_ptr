#pragma once

namespace sfinae
{
	enum class enabled {};

	enum class disabled {};

	template <bool predicate>
	constexpr auto when()
	{
		if constexpr (predicate)
			return enabled{};
		else
			return disabled{};
	}
}
