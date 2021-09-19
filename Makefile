CC = gcc
CFLAGS = -Wall -O0
TARGET_LIB = libqlearn.a

all:
	$(CC) $(CFLAGS) -c *.c 
	ar rcs $(TARGET_LIB) *.o

clean:
	rm -f *.o

allclean:
	rm -f *.o
	rm -f *.a