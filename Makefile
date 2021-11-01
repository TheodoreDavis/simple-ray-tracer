# Temp until I make a cmakelist.txt
ifndef VERBOSE
.SILENT:
endif

SUBDIRS = obj bin # Auto generated directories

CFLAGS_DEBUG 	= -Wall -Werror -g3 -std=c++17
CFLAGS_RELEASE 	= -Wall -Werror -std=c++17
CC				= g++

all: test release debug

test: test-V3 test-Sphere test-Triangle test-image test-floatutils

release: main.cpp obj/V3.o obj/Ray.o obj/Material.o obj/Sphere.o obj/Triangle.o obj/ShapeList.o obj/Camera.o obj/image.o
	mkdir -p release
	$(CC) $(CFLAGS_RELEASE) -o release/cs336-raytracer -I. $^
	echo done -- made $@/cs336-raytracer

debug: main.cpp obj/V3.o obj/Ray.o obj/Material.o obj/Sphere.o obj/Triangle.o obj/ShapeList.o obj/Camera.o obj/image.o
	mkdir -p debug
	$(CC) $(CFLAGS_DEBUG) -o debug/cs336-raytracer -I. $^
	echo done -- made $@/cs336-raytracer

.PHONY: all clean subdirs $(SUBDIRS)

test-V3: test/test-V3.cpp obj/V3.o
	$(CC) $(CFLAGS_DEBUG) -o bin/$@ -I. $^
	echo done -- made bin/$@

test-Sphere: test/test-Sphere.cpp obj/Sphere.o obj/Ray.o obj/V3.o
	$(CC) $(CFLAGS_DEBUG) -o bin/$@ -I. $^
	echo done -- made bin/$@

test-Triangle: test/test-Triangle.cpp obj/Triangle.o obj/Ray.o obj/V3.o
	$(CC) $(CFLAGS_DEBUG) -o bin/$@ -I. $^
	echo done -- made bin/$@

test-image: test/test-image.cpp obj/image.o obj/V3.o
	$(CC) $(CFLAGS_DEBUG) -o bin/$@ -I. $^
	echo done -- made bin/$@

test-floatutils: inc/floatutils.h test/test-floatutils.cpp
	$(CC) $(CFLAGS_DEBUG) -o bin/$@ -I. $^
	echo done -- made bin/$@

#####################################################################
# Source Files
#####################################################################

obj/V3.o: inc/V3.h src/V3.cpp subdirs
	$(CC) $(CFLAGS_DEBUG) -c -o $@ -I. src/V3.cpp
	echo made $@

obj/Ray.o: inc/Ray.h src/Ray.cpp subdirs
	$(CC) $(CFLAGS_DEBUG) -c -o $@ -I. src/Ray.cpp
	echo made $@

obj/image.o: inc/image.h src/image.cpp subdirs
	$(CC) $(CFLAGS_DEBUG) -c -o $@ -I. src/image.cpp
	echo made $@

obj/Material.o: inc/Material.h src/Material.cpp subdirs
	$(CC) $(CFLAGS_DEBUG) -c -o $@ -I. src/Material.cpp
	echo made $@

obj/Sphere.o: inc/Shape.h inc/Sphere.h src/Sphere.cpp obj/Material.o subdirs
	$(CC) $(CFLAGS_DEBUG) -c -o $@ -I. src/Sphere.cpp
	echo made $@

obj/Triangle.o: inc/Shape.h inc/Triangle.h src/Triangle.cpp obj/Material.o subdirs
	$(CC) $(CFLAGS_DEBUG) -c -o $@ -I. src/Triangle.cpp
	echo made $@

obj/ShapeList.o: inc/Shape.h inc/ShapeList.h src/ShapeList.cpp subdirs
	$(CC) $(CFLAGS_DEBUG) -c -o $@ -I. src/ShapeList.cpp
	echo made $@

obj/Camera.o: inc/Camera.h src/Camera.cpp subdirs
	$(CC) $(CFLAGS_DEBUG) -c -o $@ -I. src/Camera.cpp
	echo made $@

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
