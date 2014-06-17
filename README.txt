A fairly minimal complete example of dynamic linking on POSIX systems.

Resources/acknowledgements:
"http://stackoverflow.com/questions/1142103/how-do-i-load-a-shared-object-in-c" 
(which was found via a google search for "loading a shared object in c") 
pointed me at the man page for dlopen, and 
"http://stackoverflow.com/questions/3347774/dynamic-linking-a-library-successful-when-executable-is-built-same-setup-fail"
(via query on the error message "undefined symbol: _ZSt4cout") contained 
sufficient hints to resolve the error via adding "-lstdc++" to the linker flags 
for building the shared library (allowing cout to be invoked from C, 
essentially).
