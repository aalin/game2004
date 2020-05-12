FILES = $(basename $(wildcard *.cpp))
OBJS = $(addsuffix .o, $(FILES))
TARGET = ../game

GREEN = "\\033[32m"
YELLOW = "\\033[33m"
RESET = "\\033[0m"

CC=g++
CFLAGS=-Wall -Wextra -ggdb

ifeq ($(shell uname), Darwin)
  LFLAGS=
else
  LFLAGS=-lglfw -lGLESv2 -lm -lEGL
  CFLAGS+=
endif

%.o: %.cpp %.hpp
	@echo -e "$(YELLOW)Compiling $< => $@$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

all: $(TARGET)

run: $(TARGET)
	./game

test: $(TARGET)
	./game test

info:
	@echo "CC: $(CC)"
	@echo "LFLAGS: $(LFLAGS)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo

$(TARGET): $(OBJS)
	@echo
	@echo -e "$(GREEN)Linking $(OBJS) => game$(RESET)"
	@$(CC) $(OBJS) $(LFLAGS) -o $(TARGET)

clean:
	rm -f *.o $(TARGET)

.PHONY: info all demo clean
