DEBUG=-g -Wall
CC=gcc
THREAD=-lpthread
TARGET=clsock mprosock

all:$(TARGET)

$(TARGET):clsock.o mprosock.o
	$(CC) $(DEBUG) -o $@ $^ $(THREAD)
clsock.o: clsock.c
	$(CC) $(DEBUG) -c clsock.c
mprosock.o: mprosock.c
	$(CC) $(DEBUG) -c mprosock.c 
clean:
	find ./ -name "*.o" -exec rm -f {} \;
	rm $(TARGET)

