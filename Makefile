.RECIPEPREFIX := >
.DEFAULT_GOAL := all
.SUFFIXES:
.SECONDARY:

COMMA := ,
RM ?= rm --force --one-file-system --preserve-root=all
CXX ?= g++
CXXFLAGS ?= -flto -O2
CXXFLAGS += -Wall -Wextra
CXXFLAGS += -ffunction-sections -fdata-sections
CXXFLAGS += -fmax-errors=3
LDFLAGS ?= --strip-all
COMPILE := -std=gnu++20 $(CXXFLAGS)
LINKING := $(addprefix -Wl$(COMMA),$(LDFLAGS))
SOURCES := Hydro.cxx Hydro__CmosCheck.cxx PharL__UnpackROM.cxx
OBJECTS := $(SOURCES:%.cxx=%.cxx.o)
DEPENDS := $(SOURCES:%.cxx=%.cxx.d)
PROGRAM := Hydro

-include $(DEPENDS)

%.cxx.o : %.cxx
> $(CXX) $(COMPILE) -c -xc++ $< -o $@ -MT $@ -MF $(@:.o=.d) -MMD

$(PROGRAM) : $(OBJECTS)
> $(CXX) $(LINKING) $^ -lz -o $@

.PHONY : force
clean : force
> $(RM) -- $(OBJECTS) $(DEPENDS)

all : $(PROGRAM)
