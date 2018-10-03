DIR = .
CXX = g++
CFLAGS = `root-config --cflags` -I$(INCDIR)/  
LFLAGS = `root-config --glibs`

INCDIR = $(DIR)/inc
SRCDIR = $(DIR)/src
OBJDIR = $(DIR)/obj
EXE = Effi

vpath %.h $(INCDIR) 

#OBJECTS:=$(wildcard $(OBJDIR)/*.o) it requires not to erase .o files
OBJECTS= $(OBJDIR)/Effi.o $(OBJDIR)/Dict.o 

all: $(EXE)

$(EXE): $(OBJECTS) 
	$(CXX) -o $@ $^ $(LFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cxx 
	$(CXX) $(CFLAGS) -c $< -o $@

$(OBJDIR)/Dict.o: Dict.cxx
	 $(CXX) $(CFLAGS) -c $< -o $@ 

Dict.cxx: Effi.h  
	@rootcint -f $@ -c $^ 

.PHONY: clean

clean:
	@rm $(EXE) Dict.* $(OBJDIR)/* 
	
