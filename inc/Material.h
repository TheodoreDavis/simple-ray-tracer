#ifndef _MATERIAL_
#define _MATERIAL_

#include <inc/V3.h>

enum class Property {Specular, Diffuse, Glass, Light};

/**
 * Class for holding light and color information of a shape
 *
 * The following data members:
 * specular_ diffuse_ glass_ absorb_
 * should have a sum of 1
 */
class Material {
    private:
        Property property_;
        float effect_;

        /**
         * The base color of this shape
         */
        V3 color_;

    public:
        Material() {
            property_ = Property::Diffuse;
            effect_ = 1.0;
            color_ = V3(0.7,0.7,0);
        }

        Material(V3 color) {
            property_ = Property::Diffuse;
            effect_ = 1.0;
            color_ = color;
        }

        Material(Property property) {
            property_ = property;
            if (property == Property::Specular) { effect_ = 0.3; }
            else if (property == Property::Glass) { effect_ = 1.3; }
            else { effect_ = 1.0; }
            color_ = V3(0.7,0.7,0);
        }

        Material(Property property, V3 color) {
            property_ = property;
            if (property == Property::Specular) { effect_ = 0.3; }
            else if (property == Property::Glass) { effect_ = 1.3; }
            else { effect_ = 1.0; }
            color_ = color;
        }

        Material(Property property, float effect, V3 color) {
            property_ = property;
            effect_ = effect;
            color_ = color;
        }

        Property property() const {return property_;}
        Property& property() {return property_;}
        float effect() const {return effect_;}
        float& effect() {return effect_;}
        float fuzz() const {return effect_;}
        float& fuzz() {return effect_;}
        float indexOfReflection() const {return effect_;}
        float& indexOfReflection() {return effect_;}
        V3 color() const {return color_;}
        V3& color() {return color_;}
};
#endif
