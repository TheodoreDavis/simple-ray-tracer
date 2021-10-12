# Temp until I make a cmakelist.txt
ifndef VERBOSE
.SILENT:
endif

SUBDIRS = obj bin # Auto generated directories

CFLAGS 	= -Wall -Werror -g3
CC		= g++

all: test release debug

test: test-V3 test-floatutils test-image test-Sphere test-Triangle

release: src/ray-tracer.cpp obj/V3.o obj/Ray.o obj/Sphere.o obj/Triangle.o obj/image.o obj/Shapelist.o
	mkdir -p release
	$(CC) -Wall -Werror -o release/ray-tracer -I. $^
	echo done -- made release/ray-tracer

debug: src/ray-tracer.cpp obj/V3.o obj/Ray.o obj/Sphere.o obj/Triangle.o obj/image.o obj/Shapelist.o
	mkdir -p debug
	$(CC) $(CFLAGS) -o debug/ray-tracer -I. $^
	echo done -- made debug/ray-tracer

.PHONY: all clean subdirs $(SUBDIRS)

test-V3: test/test-V3.cpp obj/V3.o
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo done -- made bin/test-V3

test-float: inc/floatutils.h test/test-floatutils.cpp
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo done -- made bin/test-floatutils

test-image: test/test-image.cpp obj/image.o obj/V3.o
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo done -- made bin/test-image

test-Sphere: test/test-Sphere.cpp obj/Sphere.o obj/Ray.o obj/V3.o
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo done -- made bin/test-Sphere

test-Triangle: test/test-Triangle.cpp obj/Triangle.o obj/Ray.o obj/V3.o
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo done -- made bin/test-Triangle

#####################################################################
# Source Files
#####################################################################

obj/V3.o: inc/V3.h src/V3.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/V3.cpp

obj/Ray.o: inc/Ray.h src/Ray.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/Ray.cpp

obj/image.o: inc/image.h src/image.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/image.cpp

obj/Sphere.o: inc/Shape.h inc/Sphere.h src/Sphere.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/Sphere.cpp

obj/Triangle.o: inc/Shape.h inc/Triangle.h src/Triangle.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/Triangle.cpp

obj/Shapelist.o: inc/Shape.h inc/ShapeList.h src/ShapeList.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/ShapeList.cpp

subdirs: $(SUBDIRS)

$(SUBDIRS):
	mkdir -p $@

clean:
	rm -rf obj/
	rm -rf bin/
	rm -rf release/
	rm -rf debug/
	rm -rf out/*
	echo done -- cleaned!
