CC 			 := g++
CFLAGS 		 :=

OBJS 		 := geneBank.cpp mainSamples.cpp CustomErrorClass.o
DEPS 		 := geneBank.h CustomErrorClass.h
TARGET       := main
.PHONY: clean all


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)

geneBank.o: geneBank.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

mainSamples.o: mainSamples.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

CustomErrorClass.o: CustomErrorClass.cpp CustomErrorClass.h
	$(CC) -c -o $@ $(CFLAGS) $<