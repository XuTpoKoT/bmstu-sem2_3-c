CFLAGC = -Wall -Werror -Wextra -Wpedentic
LFLAGS = 
DFLAGS = -g3 --coverage

SRCS = ./src/main.c ./src/matr.c ./src/matr_arr.c
OBJS = ./out/main.o ./out/matr.o ./out/matr_arr.o

release: | .lastrelease app.exe

debug: CFLAGS += $(DFLAGS)
debug: LFLAGS += $(DFLAGS)
debug: | .lastdebug app.exe

.lastrelease: 
	touch .lastrelease
	rm -f .lastdebug out/*.o *exe

.lastdebug: 
	touch .lastdebug
	rm -f .lastrelease out/*.o *exe

app.exe: $(OBJS)
	gcc $(OBJS) $(LFLAGS) -o app.exe

./out/%.o: ./src/%.c
	mkdir -p out
	gcc $(CFLAGS) -I./inc -c $< -o $@

./out/%.d: ./src/%.c
	mkdir -p out
	gcc -MM -I./inc -MT '$(@:.d=.o)' -c $< > $@

include $(OBJS:.o=.d)

clean:
	rm -f -r out *.exe *.gcov .lastrelease .lastdebug
