#include <impl/impl.ipp>

class Impl
{
	bool& _destroyed;
public:
	~Impl() { _destroyed = true; }
	Impl(bool& destroyed) : _destroyed(destroyed) {}
};

impl::ptr<Impl, impl::Feature::None> get(bool& destroyed)
{
	return impl::make_ptr<Impl, impl::Feature::None>(destroyed);
}
