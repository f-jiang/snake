snake: main.o gameobj.o view.o
	cc -o snake main.o gameobj.o view.o -lncurses

main.o: src/main.c
	cc -c src/main.c

gameobj.o: src/gameobj.c
	cc -c src/gameobj.c

view.o: src/view.c
	cc -c src/view.c

clean:
	rm *.o snake
