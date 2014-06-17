#include "shared_library_wrapper.hpp"

dynamic_linking_exception::dynamic_linking_exception(const char* fn, const char* msg) throw()
{
    message += fn;
    message += ": ";
    message += msg;
}
dynamic_linking_exception::~dynamic_linking_exception() throw() {}
const char* dynamic_linking_exception::what() const throw() { return message.c_str(); }

shared_object_handle::shared_object_handle(const char* filename, int flags)
{
    if((c_handle = dlopen(filename, flags)) == NULL) { throw dynamic_linking_exception("dlopen",dlerror()); }
}
shared_object_handle::~shared_object_handle()
{
    if(dlclose(c_handle)) { throw dynamic_linking_exception("dlclose",dlerror()); }
}
