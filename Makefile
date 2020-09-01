# -*- Makefile -*-
# WARNING: Makefile is picky about TAB characters. They must be a single TAB character AND NOT a sequence of spaces
# TODO:    ADD SUPPORT FOR .so AND .a libraries
# TODO:    ADD support for nesting in OBJ/ (i chose not to do this for some reason)
#######################################################################

### DIRECTORY ###

# root
#	PROG_EXE
#	MAIN/
#		PROG_FILE.c
#		SRC/
#			../*.c
#		HEADERS/
#			../*.h
#	OBJ/
#		./*.o

# Main folder containing runnable c code and source code and headers
MAIN := src

# runnable c file (int main)
PROG_FILE := main.c # ALWAYS IN MAIN/ 
PROG_EXE  := $(basename $(PROG_FILE)) # ALWAYS UNDER ROOT/

SRC     := impl# MAIN/SRC is where all code to be converted to object files should go
HEADERS := headers# MAIN/HEADERS
OBJ     := bin# object file dump (no nesting)

#######################################################################

### COMPILER ###

CC       := clang # COMPILER
CPPFLAGS := # PRE PROCESSOR FLAGS
CFLAGS   := -Wall
LDFLAGS  := # L LIBRARY (?) FLAGS
LDLIBS   := -lSDL2 -lm # LINKER FLAGS

#######################################################################

# Finds full path of all C files (src/.../foo.c)
IMPL_FILE_PATHS := $(shell find $(MAIN)/$(SRC) -name "*.c")

# Gets only the name of the file (foo.c => foo)
IMPL_FILE_NAMES := $(basename $(IMPL_FILE_PATHS))

# The path of the object files (always OBJ/name_of_c_file.o)
OBJ_FILE_PATHS := $(addprefix $(OBJ)/, $(notdir $(addsuffix .o, $(basename $(IMPL_FILE_PATHS)))))

#######################################################################

### RECIPES ###

.PHONY: all clean

# update then create an executable
all: update
	@echo Preprocessing and compiling to $(PROG_EXE); \
	echo --- $(CC) $(LDFLAGS) $(LDLIBS) $(MAIN)/$(PROG_FILE) $(OBJ_FILE_PATHS) -o $(PROG_EXE); \
	$(CC) $(LDFLAGS) $(LDLIBS) $(MAIN)/$(PROG_FILE) $(OBJ_FILE_PATHS) -o $(PROG_EXE) && echo --- Created $(PROG_EXE);

# compile source into object files
update:
	@echo Updating object files; \
	for file in $(IMPL_FILE_NAMES); do \
		echo --- Created $(OBJ)/$${file##*/}.o; \
		$(CC) $(CPPFLAGS) $(CFLAGS) -c $${file}.c -o $(OBJ)/$${file##*/}.o; \
	done

# remove object files
clean:
	@$(RM) -r $(OBJ)/* && echo cleaned $(OBJ)/

# remove directory file structures
remove-dir:
	@echo Are you sure you want to attempt to delete directories? [ press any key to enter ]; \
	read; \
	rm $(PROG_EXE) && echo --- Deleting target exe; \
	rm -rf $(MAIN) && echo --- Deleting main directory; \
	rm -rf $(OBJ) && echo --- Deleting object directory;

# create directory file structures
create-dir:
	@echo Are you sure you want to attempt to create directories? [ press any key to enter ]; \
	read; \
	mkdir $(MAIN) && echo --- Creating main directory; \
	mkdir $(MAIN)/$(SRC) && echo --- Creating source directory; \
	mkdir $(OBJ) && echo --- Creating object directory; \
	mkdir $(MAIN)/$(HEADERS) && echo --- Creating headers directory; \
	echo  "int main(void){}" > $(MAIN)/$(PROG_FILE) && echo --- Creating prog file; 

reset-dir: remove-dir clear-dir
#######################################################################

### DEV ###

# Enter any variable name to try to print its value
print-%: 
	@echo $($*)