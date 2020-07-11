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

all: 

#
#	Executables
#


#
#	Object Files
#


#
#	Utils
# 
clean:
	rm *.o > /dev/null

realclean: clean
	
