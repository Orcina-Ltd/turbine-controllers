ifeq ($(MSYSTEM),MINGW32)
arch = 32
endif
ifeq ($(MSYSTEM),MINGW64)
arch = 64
endif

outdir = Win$(arch)
def = ../../def/BladedControllerWrapper.def
csources := $(wildcard ../../src/*.c)
cppsources := $(wildcard ../../src/*.cpp)
cobjects := $(addprefix $(outdir)/,$(notdir $(patsubst %.c,%.o,$(csources))))
cppobjects := $(addprefix $(outdir)/,$(notdir $(patsubst %.cpp,%.o,$(cppsources))))
objects := $(cobjects) $(cppobjects)
includes := $(wildcard ../../include/*.h) $(wildcard ../../include/*.hpp) $(wildcard ../../include/nlohmann/*.hpp)

flags = -c -O3 -Wall -I../../include -DUNICODE -D_UNICODE

all: $(outdir)/BladedControllerWrapper.dll

$(outdir)/BladedControllerWrapper.dll: $(objects) $(def)
	g++ $(objects) $(def) -lm -lole32 -shared -static -o $@ -Wl,--out-implib,$@.a
	strip --strip-unneeded $@

$(outdir)/%.o: ../../src/%.c $(includes)
	mkdir -p $(outdir)
	gcc $(flags) $< -o $@

$(outdir)/%.o: ../../src/%.cpp $(includes)
	mkdir -p $(outdir)
	g++ $(flags) $< -o $@

clean:
	$(RM) $(objects) $(outdir)/BladedControllerWrapper.*