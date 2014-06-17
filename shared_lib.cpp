#include <iostream>

using std::cout;
using std::endl;

extern "C"
{
    void function1() { cout << LIBRARY_PREFIX << "Hello, world!" << endl; }
    void function2() { cout << LIBRARY_PREFIX << "\"is a sentence fragment\" is a sentence fragment." << endl; }
    void function3() { cout << LIBRARY_PREFIX << "this function displays text too" << endl; }
}
