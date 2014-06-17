#include <iostream>
#include <string>
#include <exception>
#include <dlfcn.h>

using std::cout;
using std::endl;
using std::string;

class dynamic_linking_exception : public std::exception
{
    private:
    string message;
    public:
    dynamic_linking_exception(const char* fn, const char* msg) throw()
    {
        message += fn;
        message += ": ";
        message += msg;
    }
    virtual ~dynamic_linking_exception() throw() {}
    virtual const char* what() const throw() { return message.c_str(); }
};

class shared_object_handle
{
    private:
    void* c_handle;
    public:
    shared_object_handle(const char* filename, int flags)
    {
        if((c_handle = dlopen(filename, flags)) == NULL) { throw dynamic_linking_exception("dlopen",dlerror()); }
    }
    ~shared_object_handle()
    {
        if(dlclose(c_handle)) { throw dynamic_linking_exception("dlclose",dlerror()); }
    }
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

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout << "Usage: " << argv[0] << " foo.so [function_name]" << endl;
        return 1;
    }
    const char* so_filename = argv[1];
    const char* function_name = (argc < 3) ? "function1" : argv[2];
    void (*func)();
    shared_object_handle so(so_filename,RTLD_NOW);
    func = so.get_function<void(*)()>(function_name);
    (*func)();
    return 0;
}
