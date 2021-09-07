# Temp until I make a cmakelist.txt
SUBDIRS = obj bin # Auto generated directories

all: test v3

.PHONY: all clean subdirs $(SUBDIRS)

test: v3
	g++ -o bin/testfile -I. test/test.cpp obj/v3.o

v3: inc/v3.h src/v3.cpp
	g++ -c -o obj/v3.o -I. src/v3.cpp

subdirs: $(SUBDIRS)
	ECHO Creating sub directories!

$(SUBDIRS):
	mkdir $@

clean:
	echo cleaning!
	rm -rf obj/
