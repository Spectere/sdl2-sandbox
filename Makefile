# A Generic Makefile For Quick and Dirty Projects
#
# This is a great way of kickstarting new projects, prototyping, and learning
# new libraries, but it should not be used for final or large projects.
#
# This Makefile has been tested using GNU make and bash. Your mileage may vary
# with other make implementations and/or shells.

# These two variables set the CFLAGS and LDFLAGS. If you want to make use of
# additional system include files and libraries, edit CFLAGS and LDFLAGS
# respectively.
CFLAGS    = $(shell sdl2-config --cflags)
LDFLAGS   = $(shell sdl2-config --libs)

# The CC variable controls the compiler that is being used and MKDIR indicates
# what utility should be used to create directories. MKDIR should probably be
# left alone, but if you wanted to use C++ features or use a different C
# compiler (such as clang/LLVM), modify CC accordingly.
CC        = cc
MKDIR     = mkdir -p

# These variables control where the intermediate and final binaries are placed.
# OBJDIR contains all of the generated object (*.o) files, BINDIR contains the
# final binary, and ASSETDIR contains any assets that should be copied into
# BINDIR after the build process finishes.
OBJDIR    = ./obj
BINDIR    = ./bin
ASSETDIR  = ./assets

# If you are developing using multiple machines (for example, a Linux and macOS
# system) it's possible that you may need to override some of the above
# settings on one of your other systems. If this is the case, create a file in
# your project's root directory called "Makefile.override" and redefine the
# settings above in the new file. The line below this comment block will
# pull your override settings into this section of the main Makefile. If there
# is no override file, nothing will happen.
-include Makefile.override

# This generates the name of the executable file automatically based on the
# name of your project directory.
OUTFILE   = $(shell basename $(shell pwd))

# This collects the paths of all C files in your project directory. This is
# used in the build steps below.
ALL_C    := $(shell find . -type f -name '*.c')

# This creates a list of intermediate object filenames that correspond to the
# source file list generated above. This takes the list of source files and
# replaces their extension with .o and translates their path to be relative to
# OBJDIR.
OBJFILES := $(addprefix $(OBJDIR)/,$(ALL_C:%.c=%.o))

# This is the default make target. This is effectively an alias to the
# $(OUTFILE) rule.
all: $(OUTFILE)

# This target creates object files based on the C sources. It will create the
# object directory (OBJDIR) if it doesn't exist, then compile each of the
# source files using the settings in CFLAGS.
$(OBJDIR)/%.o: %.c
	$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

# This rule generates an executable binary based on the object files created
# in the above rule. This will create the binary directory (BINDIR) if it
# doesn't exist, link each of the object files (generated in the target above),
# and copy the assets from the asset directory (ASSETDIR) if it exists. If the
# asset directory does not exist, the copy step is skipped.
$(OUTFILE): $(OBJFILES)
	$(MKDIR) $(BINDIR)
	$(CC) $(LDFLAGS) -o $(BINDIR)/$(OUTFILE) $^

	if [ -d $(ASSETDIR) ]; then \
		cp $(ASSETDIR)/* $(BINDIR); \
	fi

# This rule changes into the binary directory and executes the program. If the
# build is out of date, it will compile and link the program before attempting
# to run it.
#
# This does not change the active shell's working directory, making it
# convenient for quick tests.
test: $(OUTFILE)
	cd $(BINDIR);./$(OUTFILE)

# This removes all compiled object files and the main binary from the project
# tree. The filenames are explicitly specified and, as such, this step should
# only delete files that were created by the build process.
clean:
	$(RM) -r $(OBJFILES)
	$(RM) $(BINDIR)/$(OUTFILE)
