CFLAGS=-Wall -g -I inc
VPATH=src
OBJS=qsort.o test.o
Qsort:$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
clean:
	find ./ -name "*.o" -exec rm {} \; ;rm -f Qsort
