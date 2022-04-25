#include <impl/impl.ipp>

class Impl
{
};

template Impl* impl::factory<impl::Feature::DefaultContructible, Impl>(impl::Operation, Impl*);