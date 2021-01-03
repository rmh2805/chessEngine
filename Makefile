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
main: testMove

#
#	Multiple Targets
#
all: testBoard testDisp

#
#	Executables
#
testBoard: testBoard.o board.o printDisp.o chess.o
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)
	$(ECHO)

testDisp: testDisp.o board.o printDisp.o cursesDisp.o chess.o
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)
	$(ECHO)

testMove: testMove.o board.o printDisp.o cursesDisp.o chess.o pieceMove.o
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
	-rm testMove
