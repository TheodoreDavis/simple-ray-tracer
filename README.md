Theodore Davis  tcdavis  
Sean Griffen    griffens

# simple-ray-tracer
Ray Tracer for ComS 336

## How to use
Please run the following commands in the top directory
```bash
make release
./release/ray-tracer
``` 
The output image `output.ppm` will be placed in the `out` directory.

## Project Description
For our main we placed in our scenery, the plane, the origin, and a point light. Then placed a blue sphere in the space. Then finding the direction for every pixel from the origin we check if that ray intersects with the sphere.
For fun we added simple shading by comparing the angle between the normal of the sphere at a point to a ray casted to the point-light from that same point. The closer to Pi the angle was, the darker we set the color.
