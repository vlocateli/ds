CCFLAGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual \
			-Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 \
			-Winit-self -Wlogical-op -Wmissing-declarations \
			-Wmissing-include-dirs -Wnoexcept -Wold-style-cast  \
			-Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion \
			-Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 \
			-Wswitch-default -Wundef -Werror -std=c++17
EXE  = sllist
.PHONY: all clean run $(EXE)
?SAN = 1
?DBG = 1
?FAST = 1

ifeq ($(FAST),1)
CCFLAGS = -flto -Ofast
endif

ifeq ($(SAN),1)
CCFLAGS += -fsanitize=address,undefined -ggdb
endif

ifeq ($(DBG),1)
CCFLAGS += -ggdb
endif

SRC = src/main.cpp
INCLUDE = include/node.hpp\
				include/$(EXE).hpp\
				include/utilities.hpp\
				include/timer.hpp


all: $(EXE)


$(EXE): $(SRC) $(INCLUDE)
	$(CXX) $(CCFLAGS) $(SRC) -o $@

clean:
	$(RM) $(EXE)

run: 
	./$(EXE)


