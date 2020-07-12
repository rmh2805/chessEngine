#
#	Commands
#

# Compilers
CC=gcc

# Misc
ECHO=@echo

#
#	Misc Variables
#

# C Flags
CLIBS=-lm -lncurses
CFLAGS=-Wall -std=c99 -Wextra -pedantic -ggdb

#
#	Main Target
#
main: testDisp

#
#	Multiple Targets
#
all: testBoard testDisp

#
#	Executables
#
testBoard: testBoard.o board.o
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)
	$(ECHO)

testDisp: testDisp.o board.o boardDisp.o
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)
	$(ECHO)

#
#	Object Files
#
%.o: %.c
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -c -o $@ $^

#
#	Utils
# 
clean:
	rm *.o > /dev/null

realclean: clean
	-rm testBoard
	-rm testDisp
	
