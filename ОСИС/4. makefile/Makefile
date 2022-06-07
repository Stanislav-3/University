all: build run clean

build: main.o 
	gcc main.o -o program

run:
	./program

main.o: main.c
	gcc -c main.c

DublyLinkedList.o: DublyLinkedList.h
	gcc -c DublyLinkedList.h -o DublyLinkedList.o

Client.o: Client.h
	gcc -c Client.h -o Client.o

ClintList.o: ClintList.h
	gcc -c ClintList.h -o ClintList.o

Goods.o: Goods.h
	gcc -c Goods.h -o Goods.o

GoodsList.o: GoodsList.h
	gcc -c GoodsList.h -o GoodsList.o

ListStrings.o: ListStrings.h
	gcc -c ListStrings.h -o ListStrings.o


clean:
	