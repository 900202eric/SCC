CC 	= gcc
target 	= super_calculator
obj 	= basic_operator.o super_calculator.o tinyexpr.o

.PHONY: all clean

all: $(obj)
	$(CC) -o $(target) $(obj) -lm

%o: %.c
	$(CC) -c $^ -o $@

clean:
	rm -f $(obj) $(target)
