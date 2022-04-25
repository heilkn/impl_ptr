#pragma once

#include "feature.hpp"
#include "sfinae.hpp"

namespace impl
{

enum class Operation {
	Delete,
	Copy,
	ConstructDefault
};

template <Feature f, typename Impl>
Impl* factory(Operation op, Impl* impl);

template <typename Impl, Feature f = Feature::None>
class ptr
{
	Impl* _impl = nullptr;

public:
	~ptr() { reset(); }

	ptr(Impl* impl) : _impl(impl) {}

	template <sfinae::enabled = sfinae::when<is_default_constructible(f)>()>
	ptr() : ptr(factory<f>(Operation::ConstructDefault, _impl))
	{}

	template <sfinae::enabled = sfinae::when<is_copy_constructible>(f)>
	ptr(ptr const& other)
	{
		_impl = factory<f>(Operation::Copy, other._impl);
	}

	ptr(ptr&& other)
	{
		swap(*this, other);
	}

	ptr& operator=(ptr&& other)
	{
		reset();
		swap(*this, other);
		return *this;
	}

	void reset()
	{
		_impl = factory<f>(Operation::Delete, _impl);
	}

	Impl* operator->() { return _impl; }
	Impl& operator*() { return *_impl; }
	Impl const& operator*() const { return *_impl; }

	friend void swap(ptr& self, ptr& other)
	{
		using std::swap;
		swap(self._impl, other._impl);
	}

	explicit operator bool() const {
		return static_cast<bool>(_impl);
	}

	friend bool operator!=(ptr const& self, std::nullptr_t)
	{
		return static_cast<bool>(self);
	}

	friend bool operator!=(std::nullptr_t, ptr const& self)
	{
		return static_cast<bool>(self);
	}

	friend bool operator==(ptr const& self, std::nullptr_t)
	{
		return !static_cast<bool>(self);
	}

	friend bool operator==(std::nullptr_t, ptr const& self)
	{
		return !static_cast<bool>(self);
	}
};

}