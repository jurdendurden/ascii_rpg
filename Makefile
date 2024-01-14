CC = gcc
RM = rm
EXE = rom

GCC_FLAGS = -g -ggdb3 -Wall -lm -lncurses -aux-info aux.info

# Source Files
SRC := $(wildcard *.c)

# Object Files
#OBJ_DIR = obj
#OBJ_FILES := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))


#rom: $(OBJ_FILES)
#	$(RM) -f $(EXE)
#	$(CC) -o $(EXE) $(OBJ_FILES) $(L_FLAGS)

#$(OBJ_DIR)/%.o: %.c
#	$(CC) $(C_FLAGS) -c -o $@ $<

#clean:
#	$(RM) -f $(OBJ_FILES) $(EXE) *~ *.bak *.orig *.rej

#distro:
#	make clean
#	cd ../..
#	$(RM) -f log/*.log
#	$(RM) -f log/tp/*.log
#	tar zvcf aragond-`date -I`.tar.gz ../src	

main:
	gcc $(SRC) -o rpg $(GCC_FLAGS)
