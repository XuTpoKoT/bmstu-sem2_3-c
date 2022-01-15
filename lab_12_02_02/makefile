# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
.PHONY : clean release debug
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -fPIC

INC_DIR = ./inc
OBJ_DIR = ./out
SRC_DIR = ./src

libarr.so: $(OBJ_DIR)/arr.o
	$(CC) -shared $(OBJ_DIR)/arr.o -lgcov -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -MM -I$(INC_DIR) -MT '$(@:.d=.o)' $< > $@

include $(OBJECTS:.o=.d)
	
clean:
	rm -f -r $(OBJ_DIR) *.exe *.so __pycache__ .pytest_cache

