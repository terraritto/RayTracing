# Ray Tracing
I study Ray Tracing now and write Ray Tracer by C++.  
This repositry is aimed that I complete Ray Tracer and test many techiques.  
I refference "Ray Tracing from the ground up" so my code is influenced by this book.
# How to Display
There are many methods to display,   
for example output file .bpm, .png, use API DirectX,OpenGL etc.   
I adopt DX library, which is wrapped DirectX.   
If you run my code, you should DX library.  
[DX library link](https://dxlib.xsrv.jp/index.html)  
# CopyLight  
DX Library Copyright (C) 2001-2019 Takumi Yamada.
## Bare-Bone Ray Tracer
This RayTracer has simle function.  
If you trace, this Tracer can't compute shading.  
Object which you can use are Sphere and Plane.  
![DxLib 2019_08_18 18_42_34](https://user-images.githubusercontent.com/28126083/63223366-36aa8480-c1ef-11e9-9847-fbd02283add2.png)
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
