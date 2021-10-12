#ifndef _SHAPELIST_
#define _SHAPELIST_

#include <vector>
#include <memory>

#include <inc/Shape.h>
#include <inc/V3.h>
#include <inc/HitRecord.h>
#include <inc/floatutils.h>

class Shapelist {
    private:
        std::vector<std::unique_ptr<Shape>> shapes_;
    public:
        Shapelist() {}

        void add(Shape* newShape);

        bool intersectionAtRay(const Ray &casted, HitRecord& rec)  const;
};

#endif
