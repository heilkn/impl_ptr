/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  This Source Code Form is "Incompatible With Secondary Licenses", as
  defined by the Mozilla Public License, v. 2.0.
*/

#include "ptr.hpp"

#include <stdexcept>
#include <type_traits>

namespace impl {

template <typename Impl>
constexpr Feature features();


template <typename Impl, Feature f = features<Impl>(), typename ...Args>
ptr<Impl, f> make_ptr(Args&& ...args);


template <typename Impl>
constexpr Feature features()
{
	Feature f;
	if constexpr (std::is_default_constructible_v<Impl>)
		f = f | Feature::DefaultContructible;
	if constexpr (std::is_copy_constructible_v<Impl>)
		f = f | Feature::CopyConstructible;

	return f;
}


template <Feature f, typename Impl>
Impl* factory(Operation op, Impl* impl)
{
	static_assert(!is_default_constructible(f) || std::is_default_constructible_v<Impl>,
		"ptr was declared to be default constructible, but Impl is not.");
	static_assert(!is_copy_constructible(f) || std::is_copy_constructible_v<Impl>,
		"ptr was declared to be copy constructible, but Impl is not.");
	switch (op)
	{
	case Operation::Delete:
	{
		delete impl;
		return nullptr; 
	}
	case Operation::Copy:
		if constexpr (is_copy_constructible(f))
			return new Impl{ *impl };
		else
			throw std::logic_error("ptr was declared to be copy constructible, but Impl is not.");
	case Operation::ConstructDefault:
		if constexpr (is_default_constructible(f))
			return new Impl{};
		else
			throw std::logic_error("ptr was declared to be default constructible, but Impl is not.");
	default:
		throw std::logic_error("Forgot to implement case.");
	}
}

template <typename Impl, Feature f, typename ...Args>
ptr<Impl, f> make_ptr(Args&& ...args)
{
	return { new Impl(std::forward<Args>(args)...) };
}

}
