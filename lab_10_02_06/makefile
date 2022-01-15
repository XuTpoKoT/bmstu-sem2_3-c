.PHONY : clean release debug func unit
CC = gcc
CFLAGS = -std=gnu99 -Wall -Werror -pedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion
LFLAGS = -lm
DFLAGS = -g3 --coverage
UFLAGS = -lcheck
ifeq ($(shell uname), Linux)
	UFLAGS += -lpthread -lrt
endif

INC_DIR = ./inc
OBJ_DIR = ./out
SRC_DIR = ./src
UNIT_DIR = ./unit_tests

SRCS = main.c matr.c sparse_matr.c mystring.c cmp.c
SOURCES = $(addprefix $(SRC_DIR)/,$(SRCS))
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
UNITS = $(UNIT_DIR)/check_main.c $(UNIT_DIR)/check_matr.c $(UNIT_DIR)/check_sparse_matr.c
UNIT_OBJECTS = $(UNITS:$(UNIT_DIR)/%.c=$(OBJ_DIR)/%.o)
UNIT_OBJECTS += $(OBJECTS)

EXEC_APP = app.exe
EXEC_UNIT = unit_tests.exe

.NOTPARALLEL: clean func unit

release : CFLAGS += -g0
release : | .last_build_state_release $(EXEC_APP)

debug : CFLAGS += $(DFLAGS)
debug : LFLAGS += $(DFLAGS)
debug : | .last_build_state_debug $(EXEC_APP) 

.last_build_state_release:
	touch .last_build_state_release
	rm -f *.exe out/*.o .last_build_state_debug

.last_build_state_debug:
	touch .last_build_state_debug
	rm -f *.exe out/*.o .last_build_state_release

$(EXEC_APP): $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o $@
	@echo

$(EXEC_UNIT): CFLAGS += $(DFLAGS)
$(EXEC_UNIT): LFLAGS += $(DFLAGS)
$(EXEC_UNIT): $(filter-out $(OBJ_DIR)/main.o, $(UNIT_OBJECTS))
	$(CC) $(filter-out $(OBJ_DIR)/main.o, $(UNIT_OBJECTS)) $(LFLAGS) $(UFLAGS) -o $@ 
	@echo

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(UNIT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -MM -I$(INC_DIR) -MT '$(@:.d=.o)' $< > $@

$(OBJ_DIR)/%.d: $(UNIT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -MM -I$(INC_DIR) -MT '$(@:.d=.o)' $< > $@

include $(OBJECTS:.o=.d)
include $(UNIT_OBJECTS:.o=.d)

func: debug
	@cd func_tests && ./all_test.sh	
	@echo "\nCoverage report:" 
	gcov -f -r $(OBJECTS:%.o=%.gcno)

unit: $(EXEC_UNIT)
	valgrind --leak-check=full ./$(EXEC_UNIT)
	@echo "\nrc = $$?"
	@echo "\nCoverage report:"
	gcov -f -r $(OBJECTS:%.o=%.gcno)
	
clean:
	rm -f -r $(OBJ_DIR) *.exe *.gcov .last_build_state_release .last_build_state_debug

