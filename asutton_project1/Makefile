COMPILE_FLAGS	:= -Wstrict-prototypes -Wshadow -Wpointer-arith -Wcast-qual \
   -Wcast-align -Wwrite-strings -Wnested-externs -Winline \
   -W -Wundef -Wmissing-prototypes  -O0 -g
LIBS		:= -lm

LINK_FLAGS	:= $(LIBS)

#
# Programs
#
all:	suttonterm 

suttonterm:	suttonterm.o parselibs.o
	$(CC) $(LINK_FLAGS) -o $@ $^

#
# Objects
#

%.o: %.c
	$(CC) $(CFLAGS) $(COMPILE_FLAGS) -c $< -o $@

clean:
	rm -f *.o suttonterm 

