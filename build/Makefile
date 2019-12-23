#===============================================================================
#
#FILE:              Makefile
#
#DESCRIPTION:       This is an all purpose Makefile
#
#COMPILER:          Linux make 

#NOTES:             Put other information here ...
#
#MODIFICATION HISTORY:
#
#Author                  Date               Version
#================================================================================
#Shawn Ray       	    2018-10-06          Version 1.0 started Assignment
#
#================================================================================
#
CC = g++
CXXFLAGS = -pedantic -std=c++14 -Wall -g
#
#Building will be done from the build directory
SRCXXDIR = ../src/
HEADXXDIR = ../headers/
BUILDXXDIR = ../build/
#
#
OUTPUT 	= main
#
OBJXXFILES = main.o BinaryNode.o BinaryNodeTree.o BinarySearchTree.o  

all: $(OUTPUT)
#$(OUTPUT): $(wildcard $(BUILDXXDIR)*.o)
#	$(CC) $(CXXFLAGS) -o $(OUTPUT) $(wildcard $(BUILDXXDIR)*.o)

$(OUTPUT): $(OBJXXFILES)
#$(OUTPUT):  $(wildcard $(BUILDXXDIR)* -not -name Makefile)
	$(CC) $(CXXFLAGS) -o $(OUTPUT) $(OBJXXFILES)
	#$(CC) $(CXXFLAGS) -o $(OUTPUT) $(BUILDXXDIR)*.o


main.o: $(addprefix $(SRCXXDIR), main.cpp) 
	$(CC) $(CXXFLAGS) -c $(addprefix $(SRCXXDIR), main.cpp) -o main.o

BinaryNode.o: $(addprefix $(SRCXXDIR), BinaryNode.cpp) 
	$(CC) $(CXXFLAGS) -c $(addprefix $(SRCXXDIR), BinaryNode.cpp) -o BinaryNode.o

BinaryNodeTree.o: $(addprefix $(SRCXXDIR), BinaryNodeTree.cpp)  
	$(CC) $(CXXFLAGS) -c $(addprefix $(SRCXXDIR), BinaryNodeTree.cpp) -o BinaryNodeTree.o

BinarySearchTree.o: $(addprefix $(SRCXXDIR), BinarySearchTree.cpp) 
	$(CC) $(CXXFLAGS) -c $(addprefix $(SRCXXDIR), BinarySearchTree.cpp) -o BinarySearchTree.o



#
#$(foreach FILE, $(wildcard $(SRCXXDIR)*), $(call myRECIPE, $(FILE)))
#


#define myRECIPE = $(eval $(addsuffix .o, $(basename $1)): $(addsuffix .cpp, $(basename $1)) $(CC) $(CXXFLAGS) -c $(addsuffix .cpp, $(basename $1)) -o $(addsuffix .o, $(basename $1)))
#endef
#
#
#
#
#	for FILE in $(wildcard $(SRCXXDIR)*) ; do
#		$(basename $(FILE)).o: $(FILE)
#		$(CC) $(CXXFLAGS) -c $(FILE) -o $(basename $(FILE)).o ;
#	done
#
#test:
#	$(foreach FILE, $(wildcard $(SRCXXDIR)*), $(call TESTRECIPE, $(FILE)))
	

#define TESTRECIPE 
#	@echo $1
#endef
#
#
#
#
clean:
#	
	rm -f $(OUTPUT)
	rm -f *.o
	reset
	@echo
	@echo
	@echo
	@echo Make clean, removed object and executable files ...
	@echo Contents in this Directory ...
	ls -lt
	@echo
	@echo
	@echo
#
#
#
#

