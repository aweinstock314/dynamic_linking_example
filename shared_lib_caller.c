#include <stdio.h>
#include <dlfcn.h> /* man 3 dlopen */

int main(int argc, char** argv)
{
    char* so_filename;
    void* so_handle;
    char* error_message;
    char* function_name;
    void (*func)();
    if(argc < 2)
    {
        printf("Usage: %s foo.so [function_name]\n", argv[0]);
        return 1;
    }
    so_filename = argv[1];
    function_name = (argc < 3) ? "function1" : argv[2];
    if((so_handle = dlopen(so_filename,RTLD_NOW)) == NULL)
    {
        printf("dlopen() failed: \"%s\"\n",dlerror());
        return 1;
    }
    /* from "man 3 dlopen":
        the correct way to test for an error is to call dlerror() 
        to clear any old error conditions, then call dlsym(), and 
        then call dlerror() again, saving its return value into a 
        variable, and check whether this saved value is not NULL.
    */
    dlerror();
    *(void**)(&func) = dlsym(so_handle,function_name);
    if((error_message = dlerror()) != NULL)
    {
        printf("dlsym() failed: \"%s\"\n",error_message);
        goto close_handle; /* prevent leak, wrapping dlopen/dlclose with a C++ RAII class would be cleaner */
    }
    (*func)();
    close_handle:
    if(dlclose(so_handle))
    {
        printf("dlclose() failed: \"%s\"\n",dlerror());
        return 1;
    }
    return 0;
}
