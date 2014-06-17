#include <iostream>
#include "shared_library_wrapper.hpp"

using std::cout;
using std::endl;


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
