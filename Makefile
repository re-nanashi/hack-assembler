exec = a.out
sources = $(wildcard ./*.c)
objects = $(sources:.c=.g)
flags = -g -Wall -lm -ldl -fPIC -rdynamic

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $c -o $@

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm ./*.o
	-rm new_core

lint: 
	clang-tidy ./*.c ./*.h
