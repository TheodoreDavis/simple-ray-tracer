#include <inc/ShapeList.h>

void Shapelist::add(Shape* newShape) {
    shapes_.push_back(std::unique_ptr<Shape>(newShape));
}

bool Shapelist::intersectionAtRay(const Ray &casted, HitRecord& rec) const {
    HitRecord curr = HitRecord();
    bool flag = false;

    rec.t() = 3e38f; // close to the max float val
    
    for(auto& s : shapes_) {
        curr = HitRecord();
        if(s->rayIntersections(casted, curr)) {
            // Throw away hits that are behind or at the origin.
            if(CMPFLOAT_GREATER(curr.t(), 0.005)) {
                flag = true;
                if(CMPFLOAT_LESS((curr.t() * casted.dir()).magnitudeSquared(), (rec.t() * casted.dir()).magnitudeSquared()))
                    rec = curr;
            }
        }
    }
    return flag;
}