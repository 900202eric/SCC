CC = mpicc
CXX = mpicxx
#CXXFLAGS = -std=c++17 -O3
CFLAGS = -O3
TARGETS = lab1
NODE = 4
ARGV1 = 5
ARGV2 = 100

.PHONY: all
all: $(TARGETS)

TARGETS:
	CXX $(TARGETS).cc -o $(TARGETS)

.PHONY: clean 
clean:
	rm -f $(TARGETS)

run:
	srun -psc -n $(NODE) $(TARGETS) $(ARGV1) $(ARGV2)
