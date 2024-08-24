CC=gcc
CFLAGS=-Wall -g -I inc
VPATH=src:usr
OBJS=stack.o test.o
test:$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
clean:
	find ./ -name "*.o" -exec rm {} \; ;rm -f test
