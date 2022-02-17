graphics = LinuxText


ccsrc = $(wildcard SimpleGame/*.cc) \
        $(wildcard Graphics/$(graphics)/*.cc) \
        $(wildcard Example/*.cc)

obj = $(ccsrc:.cc=.o)
dep = $(obj:.o=.d)  # one dependency file for each source

CXXFLAGS =  -I./AbstractClasses/
CXXFLAGS += -I./SimpleGame/
CXXFLAGS += -I./Graphics/$(graphics)/
ifdef debug
CXXFLAGS += -DDEBUG0 -DDEBUG1 -DDEBUG2 -DDEBUG3 -DDEBUG4 -DDEBUG5 -DDEBUG6 -DDEBUG7 -DDEBUG8 -DDEBUG9
DEBUG_ENABLE = 1
endif
ifdef debug0
CXXFLAGS += -DDEBUG0
DEBUG_ENABLE = 1
endif
ifdef debug1
CXXFLAGS += -DDEBUG1
DEBUG_ENABLE = 1
endif
ifdef debug2
CXXFLAGS += -DDEBUG2
DEBUG_ENABLE = 1
endif
ifdef debug3
CXXFLAGS += -DDEBUG3
DEBUG_ENABLE = 1
endif
ifdef debug4
CXXFLAGS += -DDEBUG4
DEBUG_ENABLE = 1
endif
ifdef debug5
CXXFLAGS += -DDEBUG5
DEBUG_ENABLE = 1
endif
ifdef debug6
CXXFLAGS += -DDEBUG6
DEBUG_ENABLE = 1
endif
ifdef debug7
CXXFLAGS += -DDEBUG7 
DEBUG_ENABLE = 1
endif
ifdef debug8
CXXFLAGS += -DDEBUG8
DEBUG_ENABLE = 1
endif
ifdef debug9
CXXFLAGS += -DDEBUG9
DEBUG_ENABLE = 1
endif

ifdef DEBUG_ENABLE
CXXFLAGS += -DDISABLE_GRAPHICS
endif

LDFLAGS  = -lncurses

mygame: $(obj)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f SimpleGame/*.o
	rm -f Graphics/$(graphics)/*.o
	rm -f Example/*.o


