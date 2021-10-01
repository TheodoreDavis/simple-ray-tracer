#ifndef _MATERIAL_
#define _MATERIAL_

#include <inc/v3.h>
//#include <inc/ray.h>
//#include <inc/shapeList.h>
//#include <inc/cmpfloat.h>

/**
 * Class for holding light and color information of a shape
 * 
 * The following data members:
 * specular_ diffuse_ glass_ absorb_
 * should have a sum of 1
 */
class Material {
    private:
        float specular_;
        float diffuse_;
        float glass_;
        float absorb_;
        float indexOfReflection_;

        /**
         * The base color of this shape
         */
        v3 color_;

    public:
        Material() {
            specular_ = 0;
            diffuse_ = 0;
            glass_ = 0;
            absorb_ = 0.25;
            indexOfReflection_ = 0;
            color_ = v3(0.7,0.7,0);
        }
        
        Material(v3 color) {
            specular_ = 0;
            diffuse_ = 0;
            glass_ = 0;
            absorb_ = 1;
            indexOfReflection_ = 0;
            color_ = color;
        }

        Material(float specular) {
            specular_ = specular;
            diffuse_ = 0;
            glass_ = 0;
            absorb_ = 1.0-specular;
            indexOfReflection_ = 0;
            color_ = v3(0.7,0.7,0);
        }

        Material(float specular, v3 color) {
            specular_ = specular;
            diffuse_ = 0;
            glass_ = 0;
            absorb_ = 1.0-specular;
            indexOfReflection_ = 0;
            color_ = color;
        }

        Material(float specular, float diffuse, float glass, float absorb, float index, v3 color) {
            specular_ = specular;
            diffuse_ = diffuse;
            glass_ = glass;
            absorb_ = absorb;
            indexOfReflection_ = index;
            color_ = color;
        }


        float specular() const {return specular_;}
        float& specular() {return specular_;}
        float diffuse() const {return diffuse_;}
        float& diffuse() {return diffuse_;}
        float glass() const {return glass_;}
        float& glass() {return glass_;}
        float absorb() const {return absorb_;}
        float& absorb() {return absorb_;}
        float indexOfReflection() const {return indexOfReflection_;}
        float& indexOfReflection() {return indexOfReflection_;}
        v3 color() const {return color_;}
        v3& color() {return color_;}
};
#endif
