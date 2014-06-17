FILES=shared_lib_caller library1.so library2.so

all: $(FILES)

shared_lib_caller:
	gcc shared_lib_caller.c -o shared_lib_caller -Wall -ldl
library1.so:
	gcc shared_lib.cpp -DLIBRARY_PREFIX='"LIBRARY1 "' -shared -Wall -o library1.so -lstdc++
library2.so:
	gcc shared_lib.cpp -DLIBRARY_PREFIX='"LIBRARY2 "' -shared -Wall -o library2.so -lstdc++

clean:
	rm $(FILES)
