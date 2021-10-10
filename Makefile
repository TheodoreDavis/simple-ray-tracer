# Temp until I make a cmakelist.txt
ifndef VERBOSE
.SILENT:
endif

SUBDIRS = obj bin # Auto generated directories

CFLAGS 	= -Wall -Werror -g3
CC		= g++

all: test release debug

test: test-v3 test-floatutils test-image test-sphere test-triangle

release: src/ray-tracer.cpp obj/v3.o obj/ray.o obj/sphere.o obj/triangle.o obj/image.o obj/shapelist.o
	mkdir -p release
	$(CC) -Wall -Werror -o release/ray-tracer -I. $^
	echo done -- made release/ray-tracer.cpp

debug: src/ray-tracer.cpp obj/v3.o obj/ray.o obj/sphere.o obj/triangle.o obj/image.o obj/shapelist.o
	mkdir -p debug
	$(CC) $(CFLAGS) -o debug/ray-tracer -I. $^
	echo done -- made debug/ray-tracer.cpp

.PHONY: all clean subdirs $(SUBDIRS)

test-v3: test/test-v3.cpp obj/v3.o
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo done -- made bin/test-v3

test-float: inc/floatutils.h test/test-floatutils.cpp
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo done -- made bin/test-floatutils

test-image: test/test-image.cpp obj/image.o obj/v3.o
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo done -- made bin/test-image

test-sphere: test/test-sphere.cpp obj/sphere.o obj/ray.o obj/v3.o
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo done -- made bin/test-sphere

test-triangle: test/test-triangle.cpp obj/triangle.o obj/ray.o obj/v3.o
	$(CC) $(CFLAGS) -o bin/$@ -I. $^
	echo done -- made bin/test-triangle

#####################################################################
# Source Files
#####################################################################

obj/v3.o: inc/v3.h src/v3.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/v3.cpp

obj/ray.o: inc/ray.h src/ray.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/ray.cpp

obj/image.o: inc/image.h src/image.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/image.cpp

obj/sphere.o: inc/shape.h inc/sphere.h src/sphere.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/sphere.cpp

obj/triangle.o: inc/shape.h inc/triangle.h src/triangle.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/triangle.cpp

obj/shapelist.o: inc/shape.h inc/shapelist.h src/shapelist.cpp subdirs
	$(CC) $(CFLAGS) -c -o $@ -I. src/shapelist.cpp

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
