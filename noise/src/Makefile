LIBTOOL=`which libtool`

# defines source files and vpaths
include Sources

DEPENDS=$(SOURCES:.c=.d)

# What source objects are we building?
OBJECTS=$(SOURCES:.c=.o)

.PHONY: all clean cleandeps cleanobjs cleanlib libnoise libnoise.so libnoise.so.0

# hooks for future makefiles being able to make multiple SOs, or older SOs
libnoise: libnoise.so libnoise.a libnoise.la
libnoise.so: libnoise.so.0
libnoise.so.0: libnoise.so.0.1

# Real build targets
libnoise.so.0.1: $(OBJECTS)
	$(LIBTOOL) --mode=link $(CXX) $(LDFLAGS) -shared -Wl,-soname=libnoise.so.0 -o libnoise.so.0.1 $(OBJECTS:.o=.lo)

libnoise.a: $(OBJECTS)
	$(LIBTOOL) --mode=link $(CXX) $(LDFLAGS) -o $@ $(OBJECTS)
libnoise.la: $(OBJECTS)
	$(LIBTOOL) --mode=link $(CXX) $(LDFLAGS) -o $@ $(OBJECTS:.o=.lo)

clean:	cleandeps cleanobjs cleanlib
cleandeps:
	-rm $(DEPENDS)
cleanobjs:
	-rm $(OBJECTS)
	-rm $(OBJECTS:.o=.lo) #clean up after libtool
	-rm -rf .libs
cleanlib:
	-rm libnoise.so.0.1
	-rm libnoise.a
	-rm libnoise.la

# Utility rules
# Generates dependancy files:
%.d: %.cpp
	@set -e; rm -f $@; \
         $(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

# C and C++ libtool (rather than raw CXX/CC) use
%.o %.lo: %.cpp
	$(LIBTOOL) --mode=compile $(CXX) $(CXXFLAGS) -c $< -o $@

%.o %.lo: %.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -c $< -o $@

# If dependancies have never been built this will produce a horde of
# "file not found" warnings and *then* build the deps.  Very odd.
include $(SOURCES:.c=.d)
