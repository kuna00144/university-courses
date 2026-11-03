SRCS = main.c
LIBSRCS = open.c close.c put.c get.c 
TARG = kvs_static
TARG_DYNAMIC = kvs_dynamic
LIBRARY_SO = libkvs.so

CC = gcc
OPTS = -Wall -g

OBJS = $(SRCS:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)
LARS = libkvs.a

all: static dynamic

static: $(TARG)

$(TARG) : $(OBJS) $(LARS)
	$(CC) -o $(TARG) $(OBJS) -L. -lkvs -static

$(LARS) : $(LOBJS)
	ar rs $(LARS) $(LOBJS)

dynamic: $(LIBRARY_SO) $(TARG_DYNAMIC)

$(LIBRARY_SO): $(LOBJS)
	$(CC) -shared -o $(LIBRARY_SO) $(LOBJS)

$(TARG_DYNAMIC): $(OBJS) $(LIBRARY_SO) 
	$(CC) -o $(TARG_DYNAMIC) $(OBJS) -L. -lkvs
clean:
	rm -f $(OBJS) $(LOBJS) $(LARS) $(TARG) $(TARG_DYNAMIC) $(LIBRARY_SO)


