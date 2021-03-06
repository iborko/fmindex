# Makefile
#    WARNING: lines must start with tabs instead of spaces

CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
BINDIR := bin
	
# classes start with Uppercase lesser
SOURCES_CPP := $(shell find $(SRCDIR) -type f -name [[:upper:]]*.cpp)
SOURCES_C := $(shell find $(SRCDIR) -type f -name *.c)
OBJECTS_CPP := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES_CPP:.cpp=_cpp.o))
OBJECTS_C := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES_C:.c=_c.o))
CFLAGS := -O2 # -g -pg -Wall
LIB := -pthread
INC := -I include

all: fmindex test

fmindex: $(OBJECTS_CPP) $(OBJECTS_C) $(BUILDDIR)/main.o
	@mkdir -p $(BINDIR)
	@echo " Linking [$@]..."
	@echo " $(CC) $^ -o $(BINDIR)/$@ $(LIB)"; $(CC) $^ -o $(BINDIR)/$@ $(LIB)
	
test: $(OBJECTS_CPP) $(OBJECTS_C) $(BUILDDIR)/test.o
	@mkdir -p $(BINDIR)
	@echo " Linking [$@]..."
	@echo " $(CC) $^ -o $(BINDIR)/$@ $(LIB)"; $(CC) $^ -o $(BINDIR)/$@ $(LIB)

# build of cpp files (only classes)
$(BUILDDIR)/%_cpp.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

# build of c files
$(BUILDDIR)/%_c.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

# special files
$(BUILDDIR)/main.o: $(SRCDIR)/main.cpp
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<
$(BUILDDIR)/test.o: $(SRCDIR)/test.cpp
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean
