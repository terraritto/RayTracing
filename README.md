# Ray Tracing
I study Ray Tracing and write Ray Tracer by C++ now.  
This repositry is aimed that I complete Ray Tracer and test many techiques.  
I refference "Ray Tracing from the ground up" so my code is influenced by this book.  
This ray Tracer generate beautiful image.  
I collect many images. If you look at only result, you search in the  Image directory.
# Directory
I write many new techniques in Light Directory.  
If you want to try something, you use this directory's code.
# How to Display
There are many methods to display,   
for example output file .bpm, .png, use API DirectX,OpenGL etc.   
I adopt DX library, which is wrapped DirectX.   
If you run my code, you should download DX library.  
[DX library link](https://dxlib.xsrv.jp/index.html)  
# CopyLight  
DX Library Copyright (C) 2001-2019 Takumi Yamada.
# Implement Techniques
## Bare-Bone Ray Tracer
This RayTracer has simle function.  
If you trace, this Tracer can't compute shading.  
Object which you can use are Sphere and Plane.    
 
## Sampling Techniques 
* Regular Sampling   
* Random Sampling  
* Jittered Sampling  
* N-Rooks Sampling 
* Multi-Jittered Sampling
* Hammersley Sampling  

## Convert samplihng method
 
* square -> disk (Shirley's concentric map)
* square -> hemispehre



## Camera
I implement many cameras, but I often use Pinhole camera.  
Therefore I don't write to use RayCast class with other cameras.
If you want to use, you must write function:TraceRay(ray,depth).

* Orthographic Camera
* Pinhole Camera
* ThinLens Camera
* FishEye Projection Camera
* Spherical Panoramic Projection Camera
* Stereo Camera

## BRDF
* Lambertian Reflection
* Glossy Specular (default is Lewis,1994 method. you can use Blinn,1977 method if you want to calculate other method.)
## Light
* Ambient Light
* Directional Light
* Point Light
* Ambient Occuluder  
* Area Light   
* Environment Light

## Material
* matte
* phong
* Plastic
* emissive

## Foundation Objects
* Geometric object  
use to make primitive object.
* Compound  
use to combine many Geometric objects or Compound Objects.
* Instance  
use to transform object(affine transform)
* Mesh  
use to manage vertexes for mesh triangle
* Mesh Triangle  
use to make mesh Triangles for smooth shading or flat shading

## Objects
* Bounding Box
* Beveled Cylinder
* Box
* ConcaveSphere
* Disk
* OpenCylinder
* PartSphere
* Plane
* Rectangle
* SolidCylinder
* Sphere
* Torus
* Triangle
* Smooth Triangle (for smooth shading)
* Flat Mesh Triangle
* Smooth Mesh Triangle

## Acceleration Scheme
* Grid  
It's Regular Grids.