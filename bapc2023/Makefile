CXX := g++
CXXFLAGS := -std=gnu++17 -O3 -Ofast -march=native -pipe -flto -funroll-loops -DNDEBUG
LDFLAGS := -flto -Wl,--as-needed

# Only keep source files that actually exist
SRCS := $(wildcard A.cpp B.cpp C.cpp D.cpp E.cpp F.cpp G.cpp H.cpp I.cpp J.cpp K.cpp L.cpp K-real.cpp M.cpp)
EXES := $(SRCS:.cpp=)

.PHONY: all clean

all: $(EXES)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(EXES) *.o
