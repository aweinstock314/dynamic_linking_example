FILES=shared_library_wrapper.o shared_lib_caller cpp_slib_caller library1.so library2.so
WARNINGS=-Wall -Wextra -pedantic

all: $(FILES)

shared_library_wrapper.o: shared_library_wrapper.hpp shared_library_wrapper.cpp
	g++ -c $^ $(WARNINGS)

shared_lib_caller: shared_lib_caller.c
	gcc $^ -o $@ $(WARNINGS) -ldl
cpp_slib_caller: shared_library_wrapper.o cpp_slib_caller.cpp
	g++ $^ -o $@ $(WARNINGS) -ldl
library1.so: shared_lib.cpp
	g++ $^ -DLIBRARY_PREFIX='"LIBRARY1 "' -shared $(WARNINGS) -o $@
library2.so: shared_lib.cpp
	g++ $^ -DLIBRARY_PREFIX='"LIBRARY2 "' -shared $(WARNINGS) -o $@

clean:
	rm $(FILES)
