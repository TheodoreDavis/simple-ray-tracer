#ifndef _SHAPELIST_
#define _SHAPELIST_

#include <inc/shape.h>
#include <inc/v3.h>
#include <inc/hitRecord.h>
#include <inc/cmpfloat.h>
#include <vector>
#include <memory>

class shapelist {
    private:
        std::vector<std::unique_ptr<shape>> shapes_;
    public:
        shapelist() {}

        void add(shape* newShape);

        bool const intersectionAtRay(const v3& ori, const v3& dir, hitRecord& rec);
};

#endif
