CXX_DIRS=$(CURDIR)


PROJ=$(shell basename $(CURDIR))


CXX=g++
LD=gcc


BASE_FLAGS=-masm=intel -Wall -O3
CXX_FLAGS=-std=c++11 $(BASE_FLAGS)
LD_FLAGS=-lstdc++ -lm



OBJDIR=objs
DEPDIR=deps
OBJDIR_TEMP=objs_temp

CXX_SOURCES=$(foreach DIR,$(CXX_DIRS),$(notdir $(wildcard $(DIR)/*.cpp)))

export VPATH	:=	$(foreach DIR,$(CXX_DIRS),$(CURDIR)/$(DIR))

CXX_OFILES=$(patsubst %.cpp,$(OBJDIR)/%.o,$(CXX_SOURCES))
OFILES=$(CXX_OFILES)

CXX_PFILES=$(patsubst %.cpp,$(DEPDIR)/%.P,$(CXX_SOURCES))
PFILES=$(CXX_PFILES)

CXX_OFILES_TEMP=$(patsubst %.cpp,$(OBJDIR_TEMP)/%.o,$(CXX_SOURCES))
OFILES_TEMP=$(CXX_OFILES_TEMP)


all : all_pre $(OFILES)
	$(LD) $(OBJDIR)/*.o -o $(PROJ) $(LD_FLAGS)

debug : all_pre $(OFILES)
	$(LD) $(OBJDIR)/*.o -o $(PROJ) $(LD_FLAGS) -g

all_objs : all_pre $(OFILES)
	@#

all_pre :
	mkdir -p $(OBJDIR) $(DEPDIR)

$(CXX_OFILES) : $(OBJDIR)/%.o : %.cpp
	@#echo "Generating dependency information for "$@"...."
	@echo $@" was updated or has no object file.  (Re)Compiling...."
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@
	@cp $(OBJDIR)/$*.d $(DEPDIR)/$*.P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(OBJDIR)/$*.d >> $(DEPDIR)/$*.P
	@rm -f $(OBJDIR)/$*.d

-include $(PFILES)


.PHONY : clean
clean :
	rm -rfv $(OBJDIR) $(DEPDIR) $(PROJ) tags *.taghl

.PHONY : clean_objs_with_no_source
clean_objs_with_no_source :
	@mkdir -p $(OBJDIR_TEMP)
	@#ls $(OBJDIR)
	@echo "Removing object files that don't have corresponding source files...."
	@for objfile in $(OFILES); \
	do \
		if [ -f $$objfile ]; \
		then \
			mv $$objfile $(OBJDIR_TEMP); \
		fi; \
	done;
	@#ls $(OBJDIR_TEMP)
	@rm -rf $(OBJDIR)
	@mkdir -p $(OBJDIR)
	@for objfile in $(OFILES_TEMP); \
	do \
		if [ -f $$objfile ]; \
		then \
			mv $$objfile $(OBJDIR); \
		fi; \
	done;
	@#ls $(OBJDIR)
	@rmdir $(OBJDIR_TEMP)
	
	
	
	@#rm -rfv $(OBJDIR_TEMP)



.PHONY : check_build
check_build :
	make clean_objs_with_no_source && make -j8


