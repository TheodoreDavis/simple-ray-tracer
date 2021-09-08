# Temp until I make a cmakelist.txt
ifndef VERBOSE
.SILENT:
endif

SUBDIRS = obj bin # Auto generated directories

all: test-v3

.PHONY: all clean subdirs $(SUBDIRS)

test-v3: test/test-v3.cpp obj/v3.o
	g++ -o bin/$@ -I. $^

obj/v3.o: inc/v3.h src/v3.cpp subdirs
	g++ -c -o $@ -I. src/v3.cpp

subdirs: $(SUBDIRS)

$(SUBDIRS):
	mkdir -p $@

clean:
	echo cleaning!
	rm -rf obj/
	rm -rf bin/
