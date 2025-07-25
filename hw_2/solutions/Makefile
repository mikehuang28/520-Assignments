CC          := gcc
DGEN        := doxygen

# The Target Binary Program
TARGET      := sol

# The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := .
INCDIR      := .
BUILDDIR    := ./build
TARGETDIR   := ./bin
SRCEXT      := c

# Flags, Libraries and Includes
CFLAGS      := -g
LIB         := -lgtest -lpthread -lm
INC         := -I$(INCDIR)
INCDEP      := -I$(INCDIR)

# Files
DGENCONFIG  := docs.config
HEADERS     := solutions.h
SOURCES     := solutions.c unit_tests.c main.c
OBJECTS     := $(patsubst %.c, $(BUILDDIR)/%.o, $(notdir $(SOURCES)))

# Default Make
all: directories $(TARGETDIR)/$(TARGET)

# Remake
remake: cleaner all

# Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

# Make the Documentation
$(DGENCONFIG):
	$(DGEN) -g $(DGENCONFIG)

docs: $(SOURCES) $(HEADERS) $(DGENCONFIG)
	$(DGEN) $(DGENCONFIG)

# Clean only Objects
clean:
	@$(RM) -rf $(BUILDDIR)/*.o

# Full Clean, Objects and Binaries
spotless: clean
	@$(RM) -rf $(TARGETDIR)/$(TARGET) $(DGENCONFIG) *.db
	@$(RM) -rf build bin html latex

# Link
$(TARGETDIR)/$(TARGET): $(OBJECTS) $(HEADERS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)

# Compile
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(HEADERS)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

.PHONY: directories remake clean cleaner apidocs $(BUILDDIR) $(TARGETDIR)
