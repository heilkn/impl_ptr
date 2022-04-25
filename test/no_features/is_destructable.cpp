#include <impl/ptr.hpp>

#include <stdexcept>

class Impl;

extern impl::ptr<Impl, impl::Feature::None> get(bool&);

int main(int, char**)
{
	auto destroyed = false;
	{
		auto impl = get(destroyed);
		if (destroyed)
			throw std::runtime_error("Destructor called too early.");
	}
	if (!destroyed)
		throw std::runtime_error("Destructor not called.");
	return 0;
}