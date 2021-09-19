#ifndef _MATERIAL_
#define _MATERIAL_

#include <inc/v3.h>

/**
 * Class for holding light and color information
 */
class material {
    private:
        float specular_;
        float diffuse_;
        v3 color_;

    public:
        material() {
            specular_ = 0;
            diffuse_ = 1;
            color_ = v3(0.7,0.7,0);
        }
        
        material(v3 color) {
            specular_ = 0;
            diffuse_ = 1;
            color_ = color;
        }

        material(float specular, float diffuse) {
            specular_ = specular;
            diffuse_ = diffuse;
            color_ = v3(0.7,0.7,0);
        }

        material(float specular, float diffuse, v3 color) {
            specular_ = specular;
            diffuse_ = diffuse;
            color_ = color;
        }

        v3 color() const {return color_;}
        v3& color() {return color_;}

        float specular() const {return specular_;}
        float& specular() {return specular_;}

        float diffuse() const {return diffuse_;}
        float& diffuse() {return diffuse_;}

        // material& operator=(const material& rhs) {
        //     specular_ = rhs.specular_;
        //     diffuse_ = rhs.diffuse_;
        //     color_ = rhs.color_;

        //     return *this;
        // }
};
#endif
