INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)

OBJS 		 := bst.o mainbst.o customErrorClass.o
DEPS 		 := bst.h ${INCLUDE_DIRS}/customErrorClass.h

.PHONY: clean all

all: bst.o mainbst.o customErrorClass.o

clean:
	rm $(OBJS) bst

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

bst.o: bst.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

mainbst.o: mainbst.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $< 

bst: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)