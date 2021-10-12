#ifndef _MATERIAL_
#define _MATERIAL_

#include <inc/V3.h>

enum class Property {Specular, Diffuse, Glass};

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
        float fuzz_;
        float indexOfReflection_;

        /**
         * The base color of this shape
         */
        V3 color_;

    public:
        Material() {
            property_ = Property::Diffuse;
            fuzz_ = 0;
            indexOfReflection_ = 0;
            color_ = V3(0.7,0.7,0);
        }

        Material(V3 color) {
            property_ = Property::Diffuse;
            fuzz_ = 0;
            indexOfReflection_ = 0;
            color_ = color;
        }

        Material(Property property) {
            property_ = property;
            fuzz_ = (property == Property::Specular) ? 0.3 : 0;
            indexOfReflection_ = (property == Property::Glass) ? 1.4 : 0;
            color_ = V3(0.7,0.7,0);
        }

        Material(Property property, V3 color) {
            property_ = property;
            fuzz_ = (property == Property::Specular) ? 0.3 : 0;
            indexOfReflection_ = (property == Property::Glass) ? 1.4 : 0;
            color_ = color;
        }

        Material(Property property, float effect, V3 color) {
            property_ = property;
            effect_ = effect;
            fuzz_ = (property == Property::Specular) ? 0.3 : 0;
            indexOfReflection_ = (property == Property::Glass) ? 1.4 : 0;
            color_ = color;
        }

        Material(Property property, float effect, float fuzz_index, V3 color) {
            property_ = property;
            effect_ = effect;
            fuzz_ = (property == Property::Specular) ? fuzz_index : 0;
            indexOfReflection_ = (property == Property::Glass) ? fuzz_index : 0;
            color_ = color;
        }


        Property property() const {return property_;}
        Property& property() {return property_;}
        float fuzz() const {return fuzz_;}
        float& fuzz() {return fuzz_;}
        float indexOfReflection() const {return indexOfReflection_;}
        float& indexOfReflection() {return indexOfReflection_;}
        V3 color() const {return color_;}
        V3& color() {return color_;}
};
#endif
