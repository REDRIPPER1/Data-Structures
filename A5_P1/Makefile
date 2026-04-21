INCLUDE_DIRS := Includes
CXX := g++
CXXFLAGS := -I$(INCLUDE_DIRS) -std=c++17 -Wall -Wextra

OBJS := binomial.o main.o CustomErrorClass.o
DEPS := binomial.h CustomErrorClass.h

.PHONY: clean all run

all: binomial

clean:
	rm -f $(OBJS) binomial

CustomErrorClass.o: CustomErrorClass.cpp ${DEPS}
	$(CXX) -c -o $@ $(CXXFLAGS) $<

binomial.o: binomial.cpp ${DEPS}
	$(CXX) -c -o $@ $(CXXFLAGS) $<

main.o: main.cpp ${DEPS}
	$(CXX) -c -o $@ $(CXXFLAGS) $<

binomial: $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

run: binomial
	./binomial