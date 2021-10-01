#ifndef _MATERIAL_
#define _MATERIAL_

#include <inc/V3.h>

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
        V3 color_;

    public:
        Material() {
            specular_ = 0;
            diffuse_ = 0;
            glass_ = 0;
            absorb_ = 0.25;
            indexOfReflection_ = 0;
            color_ = V3(0.7,0.7,0);
        }
        
        Material(V3 color) {
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
            color_ = V3(0.7,0.7,0);
        }

        Material(float specular, V3 color) {
            specular_ = specular;
            diffuse_ = 0;
            glass_ = 0;
            absorb_ = 1.0-specular;
            indexOfReflection_ = 0;
            color_ = color;
        }

        Material(float specular, float diffuse, float glass, float absorb, float index, V3 color) {
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
        V3 color() const {return color_;}
        V3& color() {return color_;}
};
#endif
