#include <impl/ptr.hpp>

class Impl;

class Interf {
	impl::ptr<Impl> impl;
};

#include <iostream>
int main(int, char**)
{
	Interf interf;

	return 0;
}
