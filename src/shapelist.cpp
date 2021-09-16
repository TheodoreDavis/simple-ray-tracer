#include <inc/shapeList.h>

void shapelist::add(shape* newShape) {
    shapes_.push_back(std::unique_ptr<shape>(newShape));
}

bool const shapelist::intersectionAtRay(const ray &casted, hitRecord& rec) {
    hitRecord curr;
    bool flag = false;

    rec.t() = 3e38f; // close to the max float val
    
    for(auto& s : shapes_) {
        if(s->rayIntersections(casted, curr)) {
                flag = true;
            if(CMPFLOAT_LESS(curr.t(), rec.t()))
                rec = curr;
        }
    }
    return flag;
}