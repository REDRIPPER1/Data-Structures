CC 			 := g++
CFLAGS 		 :=

OBJS 		 := llrb.cpp mainRB.cpp CustomErrorClass.o
DEPS 		 := llrb.h CustomErrorClass.h
TARGET       := main
.PHONY: clean all


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)

llrb.o: llrb.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

main.o: mainRB.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

CustomErroClass.o: CustomErroClass.cpp CustomErrorClass.h
	$(CC) -c -o $@ $(CFLAGS) $<