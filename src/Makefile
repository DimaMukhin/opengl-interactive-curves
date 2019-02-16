# For OS X
# Must run make from the src directory, and run the executables there too; e.g.
#  ../build/example1

CC=clang++
CFLAGS=-Wall -std=c++11 -g -DDEBUG

SRC=.
OUT=../build
GLM=../glm
GLEW=../glew

LIBDIRS=-L$(GLEW)/lib
LIBS=-lGLEW
INCLUDES=-I$(GLM) -I$(GLEW)/include
FRAMEWORKS=-framework OpenGL -framework GLUT

examples = $(notdir $(basename $(wildcard $(SRC)/example*)))
sources = $(filter-out $(wildcard $(SRC)/example*),$(wildcard $(SRC)/*.cpp $(SRC)/*.c $(SRC)/*.C))
target_source := $(wildcard $(SRC)/$@.cpp $(SRC)/$@.c $(SRC)/$@.C)

all: $(examples)

example%:	$(wildcard $(SRC)/$@.cpp $(SRC)/$@.c $(SRC)/$@.C) $(sources) $(wildcard $(SRC)/*.hpp $(SRC)/*.h $(SRC)/*.H)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBDIRS) $(LIBS) $(FRAMEWORKS) $(wildcard $(SRC)/$@.cpp $(SRC)/$@.c $(SRC)/$@.C) $(sources) -o $(OUT)/$@

clean:
	rm -f $(addprefix $(OUT)/,$(examples))
	rm -rf $(addsuffix .dSYM,$(addprefix $(OUT)/,$(examples)))
