CC = gcc
CFLAGS = -I include/

OBJS = obj/fn_check.o obj/rw_ops.o 


all : $(OBJS) 
	$(CC) src/main.c $(OBJS) -o program -L./lib -l:libfdr.a

obj/fn_check.o : include/fn_check.h src/fn_check.c
	$(CC) $(CFLAGS) -c -o $@ src/fn_check.c

obj/rw_ops.o : include/rw_ops.h src/rw_ops.c
	$(CC) $(CFLAGS) -c -o $@ src/rw_ops.c