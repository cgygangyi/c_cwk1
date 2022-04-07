
# code details

EXE = ./library
SRC= main.c book_management.c loans.c reg_log.c users.c utility.c

# generic build details

CC=      gcc
CFLAGS= -std=c99 -Wall
CLINK= 

# compile to object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# build executable: type 'make all'

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CLINK) -o $(EXE) 

all: 
	$(CC) $(CFLAGS) $(SRC) -o $(EXE)

# clean up and remove object code and executable: type 'make clean'

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o: main.c book_management.h utility.h
book_management.o: book_management.c reg_log.h users.h loans.h
loans.o: loans.c book_management.h
reg_log.o: reg_log.c book_management.h users.h
users.o: users.c book_management.h loans.h users.h
utility.o: utility.c utility.h

