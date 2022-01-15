# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
.PHONY : clean func release_static debug_static release_dll debug_dll release_dul debug_dul
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wvla -Wfloat-equal -Wfloat-conversion -Werror -Wno-cast-function-type
LFLAGS = -lm -larr
DFLAGS = -g3 --coverage

INC_DIR = ./inc
OBJ_DIR = ./out
SRC_DIR = ./src

SRCS = main.c arr.c main_dul.c
SOURCES = $(addprefix $(SRC_DIR)/,$(SRCS))
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.NOTPARALLEL: clean func

# static
release_static : | .last_build_state_release_static app_static.exe

debug_static: CFLAGS += $(DFLAGS)
debug_static: LFLAGS += $(DFLAGS)
debug_static: | .last_build_state_debug_static app_static.exe

.last_build_state_release_static:	
	rm -f *.exe out/*.o .last_build_state_debug_static
	touch .last_build_state_release_static

.last_build_state_debug_static:
	rm -f *.exe out/*.o .last_build_state_release_static
	touch .last_build_state_debug_static

libarr.a: $(OBJ_DIR)/arr.o
	ar cr libarr.a $(OBJ_DIR)/arr.o 
	ranlib libarr.a

app_static.exe: libarr.a $(OBJ_DIR)/main.o
	$(CC) $(OBJ_DIR)/main.o -I$(INC_DIR) -L. $(LFLAGS) -o $@

# dll
release_dll : | .last_build_state_release_dll app_dll.exe

debug_dll: CFLAGS += $(DFLAGS)
debug_dll: LFLAGS += $(DFLAGS) 
debug_dll: | .last_build_state_debug_dll app_dll.exe

.last_build_state_release_dll:	
	rm -f *.exe out/*.o .last_build_state_debug_dll
	touch .last_build_state_release_dll

.last_build_state_debug_dll:
	rm -f *.exe out/*.o .last_build_state_release_dll
	touch .last_build_state_debug_dll

libarr.so: CFLAGS += -fPIC
libarr.so: $(OBJ_DIR)/arr.o
	$(CC) -shared $(OBJ_DIR)/arr.o -lgcov -o $@

app_dll.exe: libarr.so $(OBJ_DIR)/main.o
	$(CC) $(OBJ_DIR)/main.o -I$(INC_DIR) -L. $(LFLAGS) -o $@

# dul
release_dul : | .last_build_state_release_dul app_dul.exe

debug_dul: CFLAGS += $(DFLAGS)
debug_dul: LFLAGS += $(DFLAGS)
debug_dul: | .last_build_state_debug_dul app_dul.exe

.last_build_state_release_dul:	
	rm -f *.exe out/*.o .last_build_state_debug_dul
	touch .last_build_state_release_dul

.last_build_state_debug_dul:
	rm -f *.exe out/*.o .last_build_state_release_dul
	touch .last_build_state_debug_dul

app_dul.exe: LFLAGS += -ldl
app_dul.exe: libarr.so $(OBJ_DIR)/main_dul.o
	$(CC) $(OBJ_DIR)/main_dul.o -I$(INC_DIR) $(filter-out -larr, $(LFLAGS)) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -MM -I$(INC_DIR) -MT '$(@:.d=.o)' $< > $@

include $(OBJECTS:.o=.d)

func:
	@rename -f -v "s/app_static/app/" app_static.exe
	@cd func_tests && ./all_test.sh	
	@echo "\nCoverage report:" 
	gcov -f -r $(OBJECTS:%.o=%.gcno)
	
clean:
	rm -f -r $(OBJ_DIR) *.exe *.gcov .last_build_state* *.a *.so

