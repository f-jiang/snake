snake: main.o gameobj.o view.o linked_list.o
	cc -o snake main.o gameobj.o view.o linked_list.o -lncurses

main.o: src/main.c
	cc -c src/main.c

gameobj.o: src/gameobj.c
	cc -c src/gameobj.c

view.o: src/view.c
	cc -c src/view.c

linked_list.o: src/linked_list.c
	cc -c src/linked_list.c

clean:
	rm *.o snake
