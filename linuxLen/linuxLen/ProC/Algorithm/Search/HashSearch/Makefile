CFLAGS=-Wall -g -I src
VPATH=src
HashS:hash.o main.o
	$(CC) $(CFLAGS) $^ -o $@
.PHONY:clean
clean:
	find ./ -name "*.o" -exec rm {} \; ; rm -f HashS
