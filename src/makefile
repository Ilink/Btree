CC = clang
BUILD_DIR = ../build
CFLAGS = -Wall -lm -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include
LIB = -lglib-2.0 -lintl -liconv -lpcre

btree: page.o btree.o test.o main.o
	$(CC) -o $(BUILD_DIR)/btree page.o btree.o test.o main.o $(CFLAGS) $(LIB)

main.o: main.c

page.o: page.c

btree.o: btree.c

test.o: test.c

clean: 
	rm -f $(BUILD_DIR)/btree *.o