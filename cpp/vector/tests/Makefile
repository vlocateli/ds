CFLAGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -std=c++17 -ggdb -fsanitize=address,undefined

EXE = vector.bin

.PHONY: all clean run


ifeq ($(FAST), 1)
	CFLAGS += -flto -Ofast
endif

ifeq ($(SAN), 1)
	CFLAGS += -fsanitize=address,undefined
endif


SRC = $(wildcard src/*.cpp)
INCLUDE = $(wildcard include/*.hpp)

all: $(EXE)

$(EXE): $(SRC) $(INCLUDE)
	$(CXX) $(CFLAGS) $(SRC) -o $@
clean: 
	$(RM) $(EXE)
run: $(EXE) 
	./$(EXE)


