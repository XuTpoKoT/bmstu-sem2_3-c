.PHONY : clean release debug func unit
CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion 
LFLAGS = 
DFLAGS = -g3 --coverage
UFLAGS = -lcheck
ifeq ($(shell uname), Linux)
	UFLAGS += -lpthread -lrt
endif

INC_DIR = ./inc
OBJ_DIR = ./out
SRC_DIR = ./src
UNIT_DIR = ./unit_tests

SRCS = arr.c main.c
SOURCES = $(addprefix $(SRC_DIR)/,$(SRCS))
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
UNITS = $(SOURCES:$(SRC_DIR)/%.c=$(UNIT_DIR)/check_%.c)
UNIT_OBJECTS = $(UNITS:$(UNIT_DIR)/%.c=$(OBJ_DIR)/%.o)
UNIT_OBJECTS += $(OBJECTS)

EXEC_APP = app.exe
EXEC_UNIT = unit_tests.exe

.NOTPARALLEL: clean func unit

release : CFLAGS += -g0
release : lastrelease | $(EXEC_APP)

debug : CFLAGS += $(DFLAGS)
debug : LFLAGS += $(DFLAGS)
debug : lastdebug | $(EXEC_APP) 

lastrelease:
	touch lastrelease
	rm -f *.exe out/* lastdebug

lastdebug:
	touch lastdebug
	rm -f *.exe out/* lastrelease

$(EXEC_APP): $(OBJ_DIR) | $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@
	@echo

$(EXEC_UNIT): CFLAGS += $(DFLAGS)
$(EXEC_UNIT): LFLAGS += $(DFLAGS)
$(EXEC_UNIT): $(OBJ_DIR) | $(filter-out $(OBJ_DIR)/main.o, $(UNIT_OBJECTS))
	$(CC) $(LFLAGS) $(filter-out $(OBJ_DIR)/main.o, $(UNIT_OBJECTS)) $(UFLAGS) -o $@ 
	@echo

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) -MMD -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(UNIT_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

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
	rm -f -r $(OBJ_DIR) *.exe *.gcov lastrelease lastdebug

