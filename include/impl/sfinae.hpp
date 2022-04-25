#pragma once

namespace sfinae
{
	enum class Enabled {};

	enum class Disabled {};

	template <bool predicate>
	constexpr auto when()
	{
		if constexpr (predicate)
			return Enabled{};
		else
			return Disabled{};
	}
}
