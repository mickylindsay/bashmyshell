#Compiler to be used
CC := gcc

#Directories
TARGETDIR := bin
BUILDDIR := build
INCLUDEDIR := include
SRCDIR := src

#File Extensions
SRCEXT := c
OBJEXT := o

#Compiler arguments
CFLAGS := -g -Wall -Werror
LIB := 
INC := -I $(INCLUDEDIR)

#Executables to be built
TARGETS := bin/test bin/yes bin/xargs

#Builds all targets
all: $(TARGETS)

#Compiles individual object files
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

#Clears out the target and building directories
clean:
	@echo Removing generated files
	@rm $(BUILDDIR)/* $(TARGETDIR)/*

.PHONY: clean

#Build rules for each individual executable
#Should probably find a better solution or automate the addition of each
test_OBJECTS := build/test.o
$(TARGETDIR)/test: $(test_OBJECTS)
	@echo "Linking $@"
	@$(CC) $^ -o $@ $(LIB)

yes_OBJECTS := build/yes.o
$(TARGETDIR)/yes: $(yes_OBJECTS)
	@echo "Linking $@"
	@$(CC) $^ -o $@ $(LIB)

xargs_OBJECTS := build/xargs.o
$(TARGETDIR)/xargs: $(xargs_OBJECTS)
	@echo "Linking $@"
	@$(CC) $^ -o $@ $(LIB)
