# A Generic Makefile For Quick and Dirty Projects
#
# This Makefile has been tested using GNU make and bash. Your mileage may vary
# with other make implementations and/or shells.

CFLAGS    = $(shell sdl2-config --cflags)
LDFLAGS   = $(shell sdl2-config --libs)

CC        = cc
MKDIR     = mkdir -p

OBJDIR    = ./obj
BINDIR    = ./bin
RESDIR    = ./resources
ASSETDIR  = ./assets

# System-specific Makefile overrides.
-include Makefile.override

# The rest of these settings should are automatically configured. Tweak at your
# own peril! :P
OUTFILE   = $(shell basename $(shell pwd))
ALL_C    := $(shell find . -type f -name '*.c')
OBJFILES := $(addprefix $(OBJDIR)/,$(ALL_C:%.c=%.o))

all: $(OUTFILE)

$(OBJDIR)/%.o: %.c
	$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUTFILE): $(OBJFILES)
	$(MKDIR) $(BINDIR)
	$(CC) $(LDFLAGS) -o $(BINDIR)/$(OUTFILE) $^

	if [ -d $(ASSETDIR) ]; then \
		cp $(ASSETDIR)/* $(BINDIR); \
	fi

test: $(OUTFILE)
	cd $(BINDIR);./$(OUTFILE)

clean:
	$(RM) -r $(OBJFILES)
	$(RM) $(BINDIR)/$(OUTFILE)
