#ifndef SHARED_LIBRARY_WRAPPER_HPP
#define SHARED_LIBRARY_WRAPPER_HPP

#include <string>
#include <exception>
#include <dlfcn.h>

class dynamic_linking_exception : public std::exception
{
    private:
    std::string message;
    public:
    dynamic_linking_exception(const char* fn, const char* msg) throw();
    virtual ~dynamic_linking_exception() throw();
    virtual const char* what() const throw();
};

class shared_object_handle
{
    private:
    void* c_handle;
    public:
    shared_object_handle(const char* filename, int flags);
    ~shared_object_handle();
    template <class funcptr> funcptr get_function(const char* name)
    {
        /* from "man 3 dlopen":
            the correct way to test for an error is to call dlerror() 
            to clear any old error conditions, then call dlsym(), and 
            then call dlerror() again, saving its return value into a 
            variable, and check whether this saved value is not NULL.
        */
        dlerror();
        funcptr func;
        *(void**)(&func) = dlsym(c_handle,name);
        char* error_message;
        if((error_message = dlerror()) != NULL) { throw dynamic_linking_exception("dlsym",error_message); }
        return func;
    }
};

#endif
