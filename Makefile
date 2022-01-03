graphics = LinuxText


ccsrc = $(wildcard IntroCPP/*.cc) \
        $(wildcard Graphics/$(graphics)/*.cc) \
        $(wildcard Example/*.cc)

obj = $(ccsrc:.cc=.o)
dep = $(obj:.o=.d)  # one dependency file for each source

CXXFLAGS =  -I./AbstractClasses/
CXXFLAGS += -I./IntroCPP/
CXXFLAGS += -I./Graphics/$(graphics)/
LDFLAGS  = -lncurses

mygame: $(obj)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)
