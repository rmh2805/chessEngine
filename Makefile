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

# Misc
EXECUTABLES=dispTest notationParserTest

#
#	Main Target
#
main: notationParserTest

#
#	Multiple Targets
#

all: dispTest notationParserTest

#
#	Executables
#

dispTest: dispTest.o chessDisp.o chessBoard.o chessGame.o
	$(CC) $(CFLAGS) -o dispTest $^ $(CLIBS)
	$(ECHO)

notationParserTest: notationParserTest.o notationParser.o chessDisp.o chessBoard.o piece.o chessGame.o
	$(CC) $(CFLAGS) -o notationParserTest $^ $(CLIBS)
	$(ECHO)

#
#	Object Files
#
dispTest.o: dispTest.c chessConst.h
	$(CC) $(CFLAGS) -c -o dispTest.o dispTest.c

notationParserTest.o: notationParserTest.c
	$(CC) $(CFLAGS) -c -o notationParserTest.o notationParserTest.c

notationParser.o: notationParser.c notationParser.h
	$(CC) $(CFLAGS) -c -o notationParser.o notationParser.c

chessDisp.o: chessDisp.c chessDisp.h
	$(CC) $(CFLAGS) -c -o chessDisp.o chessDisp.c
	
chessBoard.o: chessBoard.c chessBoard.h 
	$(CC) $(CFLAGS) -c -o chessBoard.o chessBoard.c

piece.o: piece.c piece.h
	$(CC) $(CFLAGS) -c -o piece.o piece.c

chessGame.o: chessGame.c chessGame.h
	$(CC) $(CFLAGS) -c -o chessGame.o chessGame.c

#
#	Utils
# 
clean:
	rm *.o > /dev/null

cleanExe:
	rm $(EXECUTABLES) > /dev/null

realclean: 
	-@make clean
	-@make cleanExe 
