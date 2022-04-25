#include <impl/impl.ipp>

class Impl
{
};

//template void impl::instantiate_constructors<Impl, impl::Feature::DefaultContructible>();
template Impl* impl::helper<Impl, impl::Feature::DefaultContructible>(impl::Operation, Impl*);