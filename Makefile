graphics = LinuxText


ccsrc = $(wildcard SimpleGame/*.cc) \
        $(wildcard Graphics/$(graphics)/*.cc) \
        $(wildcard Example/*.cc)

obj = $(ccsrc:.cc=.o)
dep = $(obj:.o=.d)  # one dependency file for each source

CXXFLAGS =  -I./AbstractClasses/
CXXFLAGS += -I./SimpleGame/
CXXFLAGS += -I./Graphics/$(graphics)/
LDFLAGS  = -lncurses

mygame: $(obj)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

clean:
	rm SimpleGame/*.o
	rm Graphics/$(graphics)/*.o
	rm Example/*.o


