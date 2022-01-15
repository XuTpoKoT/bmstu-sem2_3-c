CFLAGC = -Wall -Werror -Wextra -Wpedentic
LFLAGS = 
DFLAGS = -g3 --coverage
UFLAGS = -lcheck -lpthread -lrt

SRCS = main.c stack.c queue.c
OBJS = main.o stack.o queue.o
UNITS = check_main.o check_queue.o

release: app.exe

debug: CFLAGS += $(DFLAGS)
debug: LFLAGS += $(DFLAGS)
debug: debug.exe

app.exe: $(OBJS)
	gcc $(OBJS) $(LFLAGS) -o $@

debug.exe: $(OBJS)
	gcc $(OBJS) $(LFLAGS) -o $@

unit.exe: $(UNITS)
	gcc $(UNITS) $(LFLAGS) $(UFLAGS) -o $@

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

%.d: %.c
	gcc -MM -c $< > $@

include $(OBJS:.o=.d)

clean:
	rm -f -r *.exe *.d *.o
