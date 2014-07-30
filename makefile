objects= pda.o rngstream.o
global_flags= -g -Wall -Wextra -Werror -pedantic -fopenmp -lgomp # -pthread
CFLAGS:= $(CFLAGS) $(global_flags) -std=c99
CXXFLAGS:= $(CXXFLAGS) $(global_flags) -std=c++0x
LDFLAGS:= -lm -lprofiler -fopenmp
binary: $(objects)
	$(CXX) $(objects) -o gepda.out $(CXXFLAGS) $(LDFLAGS)
pda.o: rngstream.h omprng.h
rngstream.o: rngstream.h omprng.h
.PHONY: clean
clean:
	rm *.out *.o
# -O3: optimize level 3
# -g3: debug level 3
# -c: compile the source file into a object file only (no link)
# ldflags: library loader dynamic flags
# -lm: link library math
# -o: output
# -Wall: warning all
# -Wextra: warning extra
# -Werror: warnings as errors
# -L: secondary directory of libraries
# -I: secondary directory of headers
# -pthread: posix thread
# -static: static link libraries
