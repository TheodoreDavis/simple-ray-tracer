Theodore Davis  tcdavis  
Sean Griffen    griffens

# simple-ray-tracer
Ray Tracer for ComS 336

## Project Description
For our main demo scene, there is a pascal red triangle floor (y-aligned triangle), a glass sphere with index of refraction 1.33 in front of a purple sphere, with a specular reflective green sphere next to those.

The scene 1500px high by 2000px wide and is rendered with 4 samples per pixel, with a max recursive depth of 16 for each ray.

## How to use

### Running demo
Run the following commands in the top directory
```bash
make subdirs
make release
./release/ray-tracer
```
The program will print a % status of the image rendering along with how many lines it has completed.
Once image rendering is complete, a message "image wrote to file" will print: this means that the program has successfully rendered the image and wrote it to the specified ppm output file.
For this demo, the output image `output.ppm` will be placed in the `out` directory.

### Changing samples per pixel
In main.cpp, at line 15, there exists:
```
#define MAX_DEPTH 20
```
This controls the maximum recursion depth of a ray. The default is 20.

Also in main.cpp, at line 16 there exists:
```
#define ANTI_ALIASING 4
```
This controls how many rays per pixel to cast. The default is 4.

### Addto/Change scene
In src/ray-tracer.cpp starting at line 32 shapes are added to out shape list for the scene to render.
A shape can either be a sphere or a triangle and can be made diffuse, specular reflective, or glass-like materials.

To create a sphere, call it's constructor ```Sphere(center, radius, material)``` where:
  - ```center``` is a vector defined as ```V3(x,y,z)``` where:
    - ```x``` is a point in the scene on the x-axis
    - ```y``` is a point in the scene on the y-axis
    - ```z``` is a point in the scene on the z-axis
  - ```radius``` is a floating point integer,
  - ```material``` is the material of the sphere defined as:

    - ```Diffuse(color)``` where:
      - ```color``` is a vector defined as ```V3(r,g,b)``` where:
        - ```r``` is a float in the range [0,1] that defines the red component of the Material color
        - ```g``` is a float in the range [0,1] that defines the green component of the Material color
        - ```b``` is a float in the range [0,1] that defines the blue component of the Material color
    - ```Specular(fuzz-factor, color)``` where:
      - ```fuzz-factor``` is a floating point integer that defines the fuzz factor of Specular Material
      - ```color``` is defined in the same way as ```color``` in Diffuse materials
    - ```Glass(index-of-refraction, color)``` where:
      - ```index-of-refraction``` is a floating point integer that defines the index of refraction for glass Materials
      - ```color``` is the defined in the same way as ```color``` in Diffuse materials
    - ```Emitter(brightness, color)``` where:
      - ```brightness``` is how bright this light-emitting object is
      - ```color``` is defined in the same was as ```color``` in Diffuse materials

To create a Triangle, call it's constructor ```Triangle(a, b, c, material)``` where:
  - ```a``` is 1 of 3 points of the Triangle defined as ```V3(x,y,z)``` where:
    - ```x``` is a point in the scene of the x-axis
    - ```y``` is a point in the scene on the y-axis
    - ```z``` is a point in the scene on the z-axis
  - ```b``` is 2 of 3 points of the Triangle defined similarly to ```a```
  - ```c``` is 3 of 3 points of the Triangle defined similarly to ```a```
  - ```material``` is defined similarly to a Sphere's ```material```

### Configuring Camera Location and View
In main.cpp, line 39 defines the camera in the scene.
To create a Camera, call it's constructor ```Camera(h, w, pos, lookat, up, fov, ar)``` where:
  - ```h``` is the height of the image
  - ```w``` is the width of the image
  - ```pos``` is the position of the camera in the scene defined as a vector ```V3(x,y,z)``` where:
    - ```x``` is the 'x' coordinate in space of the camera
    - ```y``` is the 'y' coordinate in space of the camera
    - ```z``` is the 'z' coordinate in space of the camera

  If undefined, this defaults to ```V3(0,0,0)```

  - ```lookat``` is the direction in the scene the camera is looking at, defined as a vector ```V3(x,y,z)``` where:
    - ```x``` is the 'x' direction in space to look at
    - ```y``` is the 'y' direction in space to look at
    - ```z``` is the 'z' direction in space to look at

  If undefined, this defaults to ```V3(0,0,1)```

  - ```up``` is the upwards direction relative to the camera. This defines the camera's roll. ```up``` is defined as a vector``` V3(x,y,z)``` where:
    - ```x``` is the 'x' direction of 'up' relative to the camera
    - ```y``` is the 'y' direction of 'up' relative to the camera
    - ```z``` is the 'z' direction of 'up' relative to the camera
  - ```fov``` is a floating point integer that defines the field-of-view of the Camera in degrees. If undefined, this defaults to ```210 degrees```
  - ```ar``` is a floating point integer that defines the aspect ratio of the camera. If undefined, this defaults to ```w/h```
