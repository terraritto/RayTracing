# Ray Tracing
I study Ray Tracing and write Ray Tracer by C++ now.  
This repositry is aimed that I complete Ray Tracer and test many techiques.  
I refference "Ray Tracing from the ground up" so my code is influenced by this book.  
This ray Tracer generate beautiful image.  
I collect many images. If you look at only result, you search in the  Image directory.
# How to Display
There are many methods to display,   
for example output file .bpm, .png, use API DirectX,OpenGL etc.   
I adopt DX library, which is wrapped DirectX.   
If you run my code, you should　download DX library.  
[DX library link](https://dxlib.xsrv.jp/index.html)  
# CopyLight  
DX Library Copyright (C) 2001-2019 Takumi Yamada.
## Bare-Bone Ray Tracer
This RayTracer has simle function.  
If you trace, this Tracer can't compute shading.  
Object which you can use are Sphere and Plane.  
## AntiAliasing
This directory is implemented three techniques about AntiAliasing.  
* Regular Sampling   
* Random Sampling  
* Jittered Sampling  

It is written at world.cpp, so you contain any comment about techniques.  
## Sampling Techniques
This directory is implemented many techniques.  
First, add Sampler Class. We can access sampling techniqes with this class.  

Second, add three new techniques about sampling.  
* N-Rooks Sampling 
* Multi-Jittered Sampling
* Hammersley Sampling  

Third, add convert sampling method.  
* square -> disk (Shirley's concentric map)
* square -> hemispehre

## Perspective Viewing
I add RenderPerspective in SamplingTechniques at world class.  
It's axis-aligned perspective viewing, so you must set value about eye and d.  
eye is center of projection and d is distance between eye and center of viewplane.  
Their values require to make direction and origin about ray.  
default is eye = 100, d = 100

## Camera
this directory is implemented many cameras.  
When we take a picture, it is hidden many effects.  
Camera class can realize them.  
For example , Depth of Field(DOF) by ThinLens.  
I prepare many cameras below.  

* Orthographic Camera
* Pinhole Camera
* ThinLens Camera
* FishEye Projection Camera
* Spherical Panoramic Projection Camera
* Stereo Camera

Build which is member function has these camera's samples.  
You should be refered to them.  
Stereo Camera has another camera to implement binocular disparity.  
this is used by RenderStereo camera class's member function.  
this program is written at Pinhole only.
If you use another cameras, you must implement.

## BRDF
BRDF(Bidirectional Reflectance distribution function) is diffcult theory.  
It models real reflect phenomenon.   
In computer graphics, it uses approximation.  
this directory is implemented below.

* Lambertian Reflection

It's like perfect diffuse reflection (one way of simplest BRDf).

## Light
We must think light for shading.  
I prepare for simple light below. You maybe use it for rasterize.

* Ambient Light
* Directional Light
* Point Light
* Ambient Occuluder  
* Area Light   
* Environment Light

I also prepare for material.  
they can shade more beautiful using by light.  
You have to compare Bare-Bone Ray Tracer. you must be impressed.  
the material is below.

* matte
* phong
* Plastic
* emissive

When you specify light power more stronger, color is out of range.  
I implement tone Mapping that clamps the color.   
this is processed by MaxToOne Function where is World Class member function.

add BRDF for Phong below.  

* Glossy Specular (default is Lewis,1994 method. you can use Blinn,1977 method if you want to calculate other method.)
## will be implemented ......?
* rotation
* Cylindrical Panoramic Projection
* distance attenuation
* Disk for Area Light
