INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)

OBJS 		 := dsw.o main.o customErrorClass.o
DEPS 		 := dsw.h ${INCLUDE_DIRS}/customErrorClass.h

.PHONY: clean all

all: dsw.o main.o customErrorClass.o 

clean:
	rm $(OBJS) dsw

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

dsw.o: dsw.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

main.o: main.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

dsw: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)