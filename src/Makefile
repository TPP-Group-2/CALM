.DEFAULT_GOAL := all

CXX = g++

CXXFLAGS = -std=c++11
CPPFLAGS = -g -Wall -Wextra -Werror -Wno-unused

LDFLAGS = -lm


TARGETS = calm.so main 
calm.so: Chef.o Func.o Kitchen.o 
main: main.o calm.so 
main: LDFLAGS += -Wl,-rpath=.

all: $(TARGETS)
	@

clean:
	-$(RM) $(OBJECTS)
	-$(RM) compress.cpp

one-file:
	-$(RM) $(BUILD_DIR)compress.cpp
	cat myStruct.h Kitchen.h Chef.h Func.h | sed 's/\s*\#include\s*\"/\/\/ \#include \"/' > $(BUILD_DIR)compress
	cat Kitchen.cpp Chef.cpp Func.cpp main.cpp | sed 's/\s*\#include\s*\"/\/\/ \#include \"/' >> $(BUILD_DIR)compress
	mv $(BUILD_DIR)compress $(BUILD_DIR)compress.cpp

test: one-file
	$(CXX) -o $(BUILD_DIR)compress$(EXEEXT) compress.cpp $(LDFLAGS)

BACKUP = test -f $(1) && mv $(1) $(1).old || true
DELETE_BACKUP = test -f $(1).old && $(RM) $(1) $(1).old || true

.PHONY: all clean one-file test

OBJECTS = $(patsubst %cpp,%o,$(wildcard *.cpp))

$(OBJECTS):%o:%cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

PRE_BUILD_TARGETS = $(filter %.so,$(TARGETS))
POST_BUILD_TARGETS = $(filter-out $(PRE_BUILD_TARGETS),$(TARGETS))

$(PRE_BUILD_TARGETS): CPPFLAGS += -fPIC
$(PRE_BUILD_TARGETS): LDFLAGS += -shared
$(PRE_BUILD_TARGETS):
	$(CXX) -o $(BUILD_DIR)$@ $^ $(LDFLAGS)

$(POST_BUILD_TARGETS):
	$(CXX) -o $(BUILD_DIR)$@$(EXEEXT) $^ $(LDFLAGS)
