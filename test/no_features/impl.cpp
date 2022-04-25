#include <impl/impl.ipp>

class Impl
{
	bool& _destroyed;
public:
	~Impl() { _destroyed = true; }
	Impl(bool& destroyed) : _destroyed(destroyed) {}
};

template Impl* impl::factory<impl::Feature::None, Impl>(impl::Operation, Impl*);

impl::ptr<Impl, impl::Feature::None> get(bool& destroyed)
{
	return impl::make_ptr<Impl, impl::Feature::None>(destroyed);
}
