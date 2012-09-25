CC = clang
BUILD_DIR = ../build
CFLAGS = -Wall -lm

btree: page.o tree.o test.o main.o
	$(CC) -o $(BUILD_DIR)/btree page.o tree.o test.o main.o $(CFLAGS)

main.o: main.c

page.o: page.c

tree.o: tree.c

test.o: test.c

clean: 
	rm -f $(BUILD_DIR)/btree *.o