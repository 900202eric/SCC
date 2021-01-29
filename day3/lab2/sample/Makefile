CC = gcc
CXX = g++
CFLAGS = -lm -O3
lab2: CFLAGS += -pthread
CXXFLAGS = $(CFLAGS)
TARGETS = lab2
CORE = 4
ARGV1 = 5
ARGV2 = 100

.PHONY: all
all: $(TARGETS)

#TARGETS:
#	CXX $(TARGETS).cc -o $(TARGETS)

.PHONY: clean
clean:
	rm -f $(TARGETS) $(TARGETS:=.o)

run:
	srun -psc -c $(CORE) $(TARGETS) $(ARGV1) $(ARGV2)
