CC = gcc
SRCS = tlog.c
HDRS = tlog.h
OBJS = $(SRCS:.c=.o)
CFLAGS = -g -std=c99 -Wall -W

all : $(OBJS)
	ar  rcf ../$(LIBNAME) $(OBJS)
	
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@
	
install:
	mkdir -p $(PREFIX)/include/tlog
	install -m 644 -t $(PREFIX)/include/tlog/ $(HDRS)
	
clean:
	rm -f *.o *.a