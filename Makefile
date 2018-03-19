all: test

test: algebraic.h test.c
	gcc test.c -o test

algebraic.h: algebraic.pyp.h
	./py_processor.py algebraic.pyp.h 

clean:
	rm algebraic.h test
