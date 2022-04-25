#pragma once

/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  This Source Code Form is "Incompatible With Secondary Licenses", as
  defined by the Mozilla Public License, v. 2.0.
*/

namespace impl
{
	enum class Feature : unsigned {
		None = 0b00,
		DefaultContructible = 0b01,
		CopyConstructible = 0b10
	};

	namespace detail
	{
		constexpr auto cast(Feature f)
		{
			return static_cast<unsigned>(f);
		}
	}

	constexpr Feature operator&(Feature fst, Feature snd)
	{
		using detail::cast;
		return Feature { cast(fst) & cast(snd) };
	}

	constexpr Feature operator|(Feature fst, Feature snd)
	{
		using detail::cast;
		return Feature{ cast(fst) | cast(snd) };
	}

	namespace detail
	{
		template <Feature test>
		constexpr bool isSet(Feature f) {
			return (test & f) != Feature::None;
		}
	}

	constexpr bool is_copy_constructible(Feature f)
	{
		return detail::isSet<Feature::CopyConstructible>(f);
	}

	constexpr bool is_default_constructible(Feature f)
	{
		return detail::isSet<Feature::DefaultContructible>(f);
	}
}
