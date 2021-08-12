export CC=gcc
export CPP=g++
export CFLAGS= -g -lpthread


CSRCS = $(wildcard *.c)  
COBJS = $(patsubst %.c, %, $(CSRCS))  
CPPSRCS = $(wildcard *.cpp)  
CPPOBJS += $(patsubst %.cpp, %, $(CPPSRCS))  


CHEADERS = $(wildcard *.h)  

OBJ = $(COBJS)
OBJ += $(CPPOBJS)

all: $(OBJ)

%:%.c $(CHEADERS)
	$(CC) $^ -o $@ $(CFLAGS)

%:%.cpp $(CHEADERS)
	$(CPP) $^ -o $@ $(CFLAGS)



clean:
	rm *.o $(OBJ)  -rf

.PHONY:clean
