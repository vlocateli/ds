CFLAGS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs  -Wredundant-decls -Wshadow -Wsign-conversion -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -std=c17 -ggdb

EXE = vector.bin

.PHONY: all clean run

SAN = 1
DBG = 1
FAST = 1

ifeq ($(FAST), 1)
	CFLAGS += -flto -Ofast
endif

ifeq ($(SAN), 1)
	CFLAGS += -fsanitize=address,undefined
endif

ifeq ($(DBG), 1)
	CFLAGS += -ggdb
endif

SRC = $(wildcard src/*.c)
INCLUDE = $(wildcard include/*.h)

all: $(EXE)

$(EXE): $(SRC) $(INCLUDE)
	$(CC) $(CFLAGS) $(SRC) -o $@
clean: 
	$(RM) $(EXE)
run: $(EXE) 
	./$(EXE)


