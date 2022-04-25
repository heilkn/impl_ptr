#include <impl/ptr.hpp>

#include <stdexcept>
#include <utility>

class Impl;

extern impl::ptr<Impl, impl::Feature::None> get(bool&);

void moving(impl::ptr<Impl> in, impl::ptr<Impl>& out)
{
	out = std::move(in);
}

int main(int, char**)
{
	bool destroyed1 = false;
	bool destroyed2 = false;

	auto impl1 = get(destroyed1);
	auto impl2 = get(destroyed2);
	moving(std::move(impl1), impl2);

	if (!destroyed2)
		throw std::runtime_error("Destructor not called.");

	if (destroyed1)
		throw std::runtime_error("Destructor called too early.");

	return 0;
}
