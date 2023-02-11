CC = gcc
# CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g
# CLIBS = -lm
EXE = executable
OBJ = obj/
SRC = src/
INCL = modules/
TXT = text/
FILEC = $(wildcard $(SRC)*.c)
FILEH = $(wildcard $(INCL)*.h)
FILEO = $(patsubst $(INCL)%.c, $(OBJ)%.o, $(FILEC))

$(EXE) : $(FILEO)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

$(OBJ)main.o : $(SRC)main.c $(FILEH)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)%.o : $(SRC)%.c $(INCL)%.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -rf $(OBJ)*.o
	rm -rf $(EXE)