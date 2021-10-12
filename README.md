Theodore Davis  tcdavis  
Sean Griffen    griffens

# simple-ray-tracer
Ray Tracer for ComS 336

## Project Description
For our main demo scene, a pascal red triangle floor (y-aligned triangle) exists with a blue diffuse sphere and a specular reflective sphere on top of it.
The blue sphere is centered in the image and slightly obscuring the left "corner" of the reflective sphere.
The scene 1500px high by 2000px wide and is rendered with 4 samples per pixel, with a max recursive depth of 16 for each ray.

## How to use

### Running demo
Run the following commands in the top directory
```bash
make release
./release/ray-tracer
```
The program will print a % status of the image rendering along with how many lines it has completed.
Once image rendering is complete, a message "image wrote to file" will print: this means that the program has successfully rendered the image and wrote it to the specified ppm output file.
For this demo, the output image `output.ppm` will be placed in the `out` directory.

### Changing samples per pixel
In src/ray-tracer.cpp, at line 13, there exists:
```
#define MAX_DEPTH 16
```
This controls the maximum recursion depth of a ray. The default is 16.

Also in In src/ray-tracer.cpp, at line 14 there exists:
```
#define ANTI_ALIASING 4
```
This controls how many rays per pixel to cast. The default is 4.

### Addto/Change scene
In src/ray-tracer.cpp starting at line 43 shapes are added to out shape list for the scene to render.
A shape can either be a sphere or a triangle and can be made diffuse, specular reflective, or glass-like materials.
Example shapes with different properties than the default scene are commented out for reference.

To create a sphere, call it's constructor ```Sphere(center, radius, material)``` where:
  - ```center``` is a vector defined as ```V3(x,y,z)``` where:
    - ```x``` is a point in the scene on the x-axis
    - ```y``` is a point in the scene on the y-axis
    - ```z``` is a point in the scene on the z-axis
  - ```radius``` is a floating point integer,
  - ```material``` is the material of the sphere defined as ```Material(Property, effect, fuzz_index, color)``` where:
    - ```Property``` is an enum class that can be can be ```Diffuse```, ```Specular```, or ```Glass```
    - ```effect``` is a floating point integer that, if undefined, defaults to 0.0
    - ```fuzz_index``` is a floating point integer that defines the fuzz factor of Specular Materials. If undefines, this defaults to 0.3
    - ```color``` is a vector defined as ```V3(r,g,b)``` where:
      - ```r``` is a float in the range [0,1] that defines the red component of the Material color
      - ```g``` is a float in the range [0,1] that defines the green component of the Material color
      - ```b``` is a float in the range [0,1] that defines the blue component of the Material color

To create a Triangle, call it's constructor ```Triangle(a, b, c, material)``` where:
  - ```a``` is 1 of 3 points of the Triangle defined as ```V3(x,y,z)``` where:
    - ```x``` is a point in the scene of the x-axis
    - ```y``` is a point in the scene on the y-axis
    - ```z``` is a point in the scene on the z-axis
  - ```b``` is 2 of 3 points of the Triangle defined similarly to ```a```
  - ```c``` is 3 of 3 points of the Triangle defined similarly to ```a```
  - ```material``` is defined similarly to a Sphere's ```material```

### Configuring Camera Location and View
In src/ray-tracer.cpp line 34 ```V3 origin = V3(0,0,0)``` defines the origin of all rays casted into the scene

In src/ray-tracer.cpp line 40 ```V3 plane = V3(0,0,1)``` defines the image plane to cast all rays to in the scene
