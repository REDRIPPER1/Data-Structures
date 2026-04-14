CC 			 := g++
CFLAGS 		 :=

OBJS 		 := hash.o mainHash.o CustomErrorClass.o avl.o
DEPS 		 := hash.h CustomErrorClass.h AVL/avl.h
TARGET       := main
INSPECTOR    := dataset_inspector
TABLE_GEN    := benchmark_table
.PHONY: clean all inspector table


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

inspector: dataset_inspector.o
	$(CC) -o $(INSPECTOR) dataset_inspector.o

table: benchmark_table.o hash.o CustomErrorClass.o avl.o
	$(CC) -o $(TABLE_GEN) benchmark_table.o hash.o CustomErrorClass.o avl.o

dataset_inspector.o: dataset_inspector.cpp
	$(CC) -c -o $@ $(CFLAGS) $<

benchmark_table.o: benchmark_table.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(TARGET) dataset_inspector.o $(INSPECTOR) benchmark_table.o $(TABLE_GEN)

hash.o: hash.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

mainHash.o: mainHash.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

CustomErrorClass.o: CustomErrorClass.cpp CustomErrorClass.h
	$(CC) -c -o $@ $(CFLAGS) $<

avl.o: AVL/avl.cpp AVL/avl.h
	$(CC) -c -o $@ $(CFLAGS) $<