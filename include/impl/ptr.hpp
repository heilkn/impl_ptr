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

template <typename Impl, Feature f>
Impl* helper(Operation op, Impl* impl);

template <typename Impl, Feature f = Feature::None>
class ptr
{
	using op_t = Impl*(*)(Operation, Impl*);
	op_t _op = nullptr;
	Impl* _impl = nullptr;

public:
	~ptr() { reset(); }

	ptr(op_t op, Impl* impl)
		: _op(op)
		, _impl(impl)
	{}

	template <sfinae::Enabled = sfinae::when<is_default_constructible(f)>()>
	ptr() : ptr(helper<Impl, f>, helper<Impl, f>(Operation::ConstructDefault, nullptr))
	{}

	//template <sfinae::Disabled = sfinae::when<is_default_constructible(f)>()>
	//ptr() = delete;

	template <sfinae::Enabled = sfinae::when<is_copy_constructible>(f)>
	ptr(ptr const& other)
	{
		_impl = _op(Operation::Copy, other._impl);
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
		if (_op)
			_impl = _op(Operation::Delete, _impl);
	}

	Impl* operator->() { return _impl; }
	Impl& operator*() { return *_impl; }
	Impl const& operator*() const { return *_impl; }

	friend void swap(ptr& self, ptr& other)
	{
		using std::swap;
		swap(self._op, other._op);
		swap(self._impl, other._impl);
	}

	explicit operator bool() const {
		return static_cast<bool>(_impl);
	}

	friend bool operator==(ptr const& self, std::nullptr_t)
	{
		return static_cast<bool>(self);
	}

	friend bool operator==(std::nullptr_t, ptr const& self)
	{
		return static_cast<bool>(self);
	}
};

}