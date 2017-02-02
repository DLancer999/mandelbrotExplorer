
#*************************************************************************#
#License
#    Copyright (c) 2017 Kavvadias Ioannis.
#    
#    This file is part of mandelbrotExplorer.
#    
#    Licensed under the MIT License. See LICENSE file in the project root for 
#    full license information.  
#
#Description
#    Makefile for mandelbrotExplorer project.
#
#************************************************************************#

MYPROGRAM = mandelbrotExplorer
OBJ= mandelbrotExplorer.o \
	globalFunctions.o \
	Camera.o \
	WindowAttrib.o \
	Mouse.o \
	FractalSettings.o \
	Fractal2D.o \
	Shader.o 

LIBS = -lGL -lGLEW `pkg-config --static --libs glfw3` 
LDIR =

MYFOLDER = $(shell pwd)
ODIR    = obj
DEPSDIR = deps
SRCDIR  = src
IDIR    = $(MYFOLDER)/$(SRCDIR)

OPTFLAGS= -g -O3 -flto 
#-march=native 
#-mtune=native
CPPFLAGS= $(OPTFLAGS) -Wall -Weffc++ -pedantic -pedantic-errors \
	-Wextra -Wcast-align -Wcast-qual \
	-Wchar-subscripts  -Wcomment -Wconversion \
	-Wdisabled-optimization -Wfloat-equal  -Wformat  -Wformat=2 \
	-Wformat-nonliteral -Wformat-security -Wformat-y2k \
	-Wimport  -Winit-self  -Winvalid-pch   \
	-Wunsafe-loop-optimizations  -Wlong-long -Wmissing-braces \
	-Wmissing-field-initializers -Wmissing-format-attribute   \
	-Wmissing-include-dirs -Wmissing-noreturn \
	-Wpacked  -Wparentheses  -Wpointer-arith \
	-Wredundant-decls -Wreturn-type \
	-Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector \
	-Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default \
	-Wswitch-enum -Wtrigraphs  -Wuninitialized \
	-Wunknown-pragmas  -Wunreachable-code -Wunused \
	-Wunused-function  -Wunused-label  -Wunused-parameter \
	-Wunused-value  -Wunused-variable  -Wvariadic-macros \
	-Wvolatile-register-var  -Wwrite-strings -std=c++0x \
	`pkg-config --cflags glfw3`

EXE_INC = \
	-I$(IDIR)

_OBJ =  $(patsubst %,$(ODIR)/%,$(OBJ))
_DEPS = $(patsubst %,$(DEPSDIR)/%,$(OBJ:.o=.dep))

all: compileExe

ifneq ($(MAKECMDGOALS),clean)
-include $(_DEPS)
endif

$(DEPSDIR)/%.dep: $(SRCDIR)/%.cpp | $(DEPSDIR)
	@echo "Generating DEPENDENCIES for" $<
	@set -e; rm -f $*.dep; \
	$(CXX) -MM $(EXE_INC) $(CPPFLAGS) $< > $(DEPSDIR)/$*.dep.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(ODIR)/\1.o $(DEPSDIR)/$*.dep : ,g' < $(DEPSDIR)/$*.dep.$$$$ > $(DEPSDIR)/$*.dep; \
	rm -f $(DEPSDIR)/$*.dep.$$$$

$(ODIR)/%.o: $(SRCDIR)/%.cpp | $(ODIR)
	@echo
	@echo  " ----------> Compiling Object <----------"
	$(CXX) $(EXE_INC) $(CPPFLAGS) -c $< -o $@

$(ODIR):
	@echo
	@echo  " -----> Creating Objects Directory <-----"
	@mkdir $(ODIR)

$(DEPSDIR):
	@echo
	@echo  " ---> Creating Dependecies Directory <---"
	@mkdir $(DEPSDIR)
	@echo

$(MYPROGRAM).exe : $(_OBJ)  
	@echo
	@echo  " --------------> Linking <---------------"
	$(CXX) $(_OBJ) $(CPPFLAGS) $(LDIR) $(LIBS)  -o $@

compileExe: $(MYPROGRAM).exe 
	@echo 
	@echo  " -------> Compilation Successful <-------" 

.PRECIOUS: %.dep
.PHONY: clean

clean:
	@rm -rf $(ODIR) $(DEPSDIR) $(MYPROGRAM).exe 

