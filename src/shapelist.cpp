#include <inc/shapeList.h>

void shapelist::add(shape* newShape) {
    shapes_.push_back(std::unique_ptr<shape>(newShape));
}

bool shapelist::intersectionAtRay(const ray &casted, hitRecord& rec) const {
    hitRecord curr = hitRecord();
    bool flag = false;

    rec.t() = 3e38f; // close to the max float val
    
    for(auto& s : shapes_) {
        curr = hitRecord();
        if(s->rayIntersections(casted, curr)) {
            // Throw away hits that are behind or at the origin.
            //if(CMPFLOAT_GREATER(curr.t(), 0.05)) {
                flag = true;
                if(CMPFLOAT_LESS((curr.t() * casted.dir()).magnitudeSquared(), (rec.t() * casted.dir()).magnitudeSquared()))
                    rec = curr;
            //}
        }
    }
    return flag;
}