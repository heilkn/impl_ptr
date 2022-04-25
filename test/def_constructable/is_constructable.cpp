#include <impl/ptr.hpp>

#include <stdexcept>

class Impl;

class Interf {
	impl::ptr<Impl, impl::Feature::DefaultContructible> impl;

public:
	Interf() {
		if (impl == nullptr)
			throw std::logic_error("impl was not constructed.");
	}
};

#include <iostream>
int main(int, char**)
{
	Interf interf;

	return 0;
}
