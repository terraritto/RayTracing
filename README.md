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
https://github.com/nmwsharp/happly
# Implement Techniques
## Tracer
* AreaLights
* RayCast
* Whitted
* PathTrace
* GlobalTrace
    
 
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
* Orthographic Camera
* Pinhole Camera
* ThinLens Camera
* FishEye Projection Camera
* Spherical Panoramic Projection Camera
* Stereo Camera

## BRDF
* Lambertian Reflection
* Glossy Specular (default is Lewis,1994 method. you can use Blinn,1977 method if you want to calculate other method.)
* Perfect Specular
* Fresnel Reflector

## BTDF
* PerfectTransmitter
* FresnelTransmitter

## Light
* Ambient Light
* Directional Light
* Point Light
* Ambient Occuluder  
* Area Light   
* Environment Light

## Material
* Matte
* Phong
* Plastic
* Emissive
* Reflective
* GlossyReflector
* Transparent
* Dielectric

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

## File Format
* .ply  
in grid, .ply can be read.  
warning: you must '\n' for a new line, not '\r'.