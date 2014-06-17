FILES=shared_lib_caller cpp_slib_caller library1.so library2.so
WARNINGS=-Wall -Wextra -pedantic

all: $(FILES)

shared_lib_caller: shared_lib_caller.c
	gcc $^ -o $@ $(WARNINGS) -ldl
cpp_slib_caller: cpp_slib_caller.cpp
	g++ $^ -o $@ $(WARNINGS) -ldl
library1.so: shared_lib.cpp
	g++ $^ -DLIBRARY_PREFIX='"LIBRARY1 "' -shared $(WARNINGS) -o $@
library2.so: shared_lib.cpp
	g++ $^ -DLIBRARY_PREFIX='"LIBRARY2 "' -shared $(WARNINGS) -o $@

clean:
	rm $(FILES)
