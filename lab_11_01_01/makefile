.PHONY : clean unit
CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion -Werror
LFLAGS = -lm
DFLAGS = -g3 --coverage
UFLAGS = -lcheck
ifeq ($(shell uname), Linux)
	UFLAGS += -lpthread -lrt
endif
# 
INC_DIR = ./inc
OBJ_DIR = ./out
SRC_DIR = ./src
UNIT_DIR = ./unit_tests

SRCS = my_snprintf.c mystring.c
SOURCES = $(addprefix $(SRC_DIR)/,$(SRCS))
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
UNITS = check_main.c check_my_snprintf.c 
UNIT_OBJECTS = $(UNITS:%.c=$(OBJ_DIR)/%.o)
UNIT_OBJECTS += $(OBJECTS)

EXEC_UNIT = unit_tests.exe

.NOTPARALLEL: clean unit

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

unit: $(EXEC_UNIT)
	valgrind --leak-check=full ./$(EXEC_UNIT)
	@echo "\nrc = $$?"
	@echo "\nCoverage report:"
	gcov -f -r $(OBJECTS:%.o=%.gcno)
	
clean:
	rm -f -r $(OBJ_DIR) *.exe *.gcov 

