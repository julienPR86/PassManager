all : main clean

main : tmp/main.o tmp/add.o tmp/file.o tmp/get.o tmp/help.o tmp/inputs.o tmp/list.o tmp/manager.o tmp/remove.o tmp/str.o tmp/utils.o
	gcc -o main tmp/main.o tmp/add.o tmp/file.o tmp/get.o tmp/help.o tmp/inputs.o tmp/list.o tmp/manager.o tmp/remove.o tmp/str.o tmp/utils.o

tmp/main.o : main.c
	gcc -o tmp/main.o -c main.c

tmp/add.o : scripts/add.c
	gcc -o tmp/add.o -c scripts/add.c

tmp/file.o : scripts/file.c
	gcc -o tmp/file.o -c scripts/file.c

tmp/get.o : scripts/get.c
	gcc -o tmp/get.o -c scripts/get.c

tmp/help.o : scripts/help.c
	gcc -o tmp/help.o -c scripts/help.c

tmp/inputs.o : scripts/inputs.c
	gcc -o tmp/inputs.o -c scripts/inputs.c

tmp/list.o : scripts/list.c
	gcc -o tmp/list.o -c scripts/list.c

tmp/manager.o : scripts/manager.c
	gcc -o tmp/manager.o -c scripts/manager.c

tmp/remove.o : scripts/remove.c
	gcc -o tmp/remove.o -c scripts/remove.c

tmp/str.o : scripts/str.c
	gcc -o tmp/str.o -c scripts/str.c

tmp/utils.o : scripts/utils.c
	gcc -o tmp/utils.o -c scripts/utils.c

clean :
	rm -f tmp/*.o