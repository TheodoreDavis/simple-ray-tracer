# Temp until I make a cmakelist.txt
ifndef VERBOSE
.SILENT:
endif

SUBDIRS = obj bin # Auto generated directories

CFLAGS 	= -Wall -Werror -g3
CC		= g++

all: test release debug

test: test-v3 test-cmpfloat test-sphere test-image

release: src/ray-tracer.cpp obj/v3.o obj/sphere.o obj/triangle.o obj/image.o
	mkdir -p release
	$(CC) -Wall -Werror -o release/ray-tracer -I. $^
	echo made release/ray-tracer

debug:

.PHONY: all clean subdirs $(SUBDIRS)

test-v3: test/test-v3.cpp obj/v3.o
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo made bin/test-v3
	
test-cmpfloat: inc/cmpfloat.h test/test-cmpfloat.cpp
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo made bin/test-cmpfloat
	
test-image: test/test-image.cpp obj/image.o obj/v3.o
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo made bin/test-image

test-sphere: test/test-sphere.cpp obj/sphere.o obj/v3.o
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo made bin/test-sphere
	
test-triangle: test/test-triangle.cpp obj/triangle.o obj/v3.o
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo made bin/test-triangle

#####################################################################
# Source Files
#####################################################################

obj/v3.o: inc/v3.h src/v3.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/v3.cpp
	
obj/image.o: inc/image.h src/image.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/image.cpp

obj/sphere.o: inc/shape.h inc/sphere.h src/sphere.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/sphere.cpp
	
obj/triangle.o: inc/shape.h inc/triangle.h src/triangle.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/triangle.cpp

subdirs: $(SUBDIRS)

$(SUBDIRS):
	mkdir -p $@

clean:
	rm -rf obj/
	rm -rf bin/
	rm -rf release/
	rm -rf debug/
	rm -rf out/*
	echo cleaned!
