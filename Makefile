# Temp until I make a cmakelist.txt
ifndef VERBOSE
.SILENT:
endif

SUBDIRS = obj bin # Auto generated directories

CFLAGS 	= -Wall -Werror -g3
CC		= g++

all: test-v3 test-cmpfloat

.PHONY: all clean subdirs $(SUBDIRS)

test-v3: test/test-v3.cpp obj/v3.o
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	
test-cmpfloat: inc/cmpfloat.h test/test-cmpfloat.cpp
	$(CC) $(CFLAGS) -o bin/$@ -I. $^

obj/v3.o: inc/v3.h src/v3.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/v3.cpp

subdirs: $(SUBDIRS)

$(SUBDIRS):
	mkdir -p $@

clean:
	echo cleaning!
	rm -rf obj/
	rm -rf bin/
