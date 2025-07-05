CC = gcc
EXEC = mssv
CFLAGS = -Wall -g
OBJ = main.o 

$(EXEC) : $(OBJ)
				$(CC) $(OBJ) -o $(EXEC) 
main.o : main.c
				$(CC) $(CFLAGS) -c main.c

clean: 
				rm -f $(EXEC) $(OBJ) 