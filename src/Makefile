CC = gcc
# CFLAGS= -O2 -Wall -Wextra -Werror
CLIBS= -lm
EXE = executable
OBJ = main.o\
	actions.o\
	cards.o\
	display.o\
	players.o
SRC = src/
INCL = modules/
# FILEC = $(wildcard $(SRC)*.c)
# FILEH = $(wildcard $(INCL)*.h)
# FILEO:= $(patsubst $(SRC)%.c,$(OBJ)%.o,$(FILEC))


$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

main.o : main.c include/actions.h include/cards.h include/display_standars.h include/players.h
actions.o : include/actions.c include/actions.h include/cards.h include/display_standars.h
cards.o : include/cards.c include/cards.h
players.o : include/players.c include/players.h

%.o : %.c
	$(CC) $(CFLAGS) -c $<

# $(EXE) : $(FILEO)
# 	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

# $(OBJ)main.o : $(SRC)main.c $(FILEH)
# 	$(CC) $(CFLAGS) -o $@ -c $<

# $(OBJ)%.o : $(SRC)%.c $(INCL)%.h
# 	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -rf $(OBJ)*.o
	rm -rf $(EXE)