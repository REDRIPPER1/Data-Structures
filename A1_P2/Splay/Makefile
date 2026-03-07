CC 			 := g++
CFLAGS 		 :=

OBJS 		 := splay.o bench.o CustomErrorClass.o
DEPS 		 := splay.h CustomErrorClass.h
TARGET       := bench
.PHONY: clean all


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)

splay.o: splay.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

bench.o: bench.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

CustomErroClass.o: CustomErroClass.cpp CustomErrorClass.h
	$(CC) -c -o $@ $(CFLAGS) $<