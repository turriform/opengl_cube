
CC:= gcc
FLAGS:= -std=c11  -Wall -Wextra -Wpedantic \
          -Wformat=2 -Wno-unused-parameter -Wshadow \
          -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
          -Wredundant-decls -Wnested-externs -Wmissing-include-dirs -g 
          #-fsanitize=address



SRC:= $(wildcard ./src/*.c ./src/graphics/*.c)
SRC+= $(wildcard ./third_party/cglm/src/*.c)

INCLUDE:= -I./include/
INCLUDE+= -I./third_party/cglm/include
INCLUDE+= -I./third_party/glad/include
INCLUDE+= -I./third_party/cJSON/include

GLAD_O:= ./third_party/glad/obj/glad.o
CJSON_O:= ./third_party/cJSON/obj/cJSON.o

SRC+= $(GLAD_O) $(CJSON_O)

LIB:= -L./third_party/cglm/build

LIBS:= -lcglm -lSDL2 -lm

TARGET:= ./bin/prog

all:
	$(CC) $(FLAGS) $(INCLUDE) $(SRC) -o $(TARGET) $(LIB) $(LIBS) && $(TARGET)  

