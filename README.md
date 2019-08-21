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
# Bare-Bone Ray Tracer
This RayTracer has simle function.  
If you trace, this Tracer can't compute shading.  
Object which you can use are Sphere and Plane.  
![DxLib 2019_08_18 18_42_34](https://user-images.githubusercontent.com/28126083/63223366-36aa8480-c1ef-11e9-9847-fbd02283add2.png)
# AntiAliasing
This directory is implemented three techniques about AntiAliasing.  
It is written at world.cpp, so you contain any comment about techniques.  
* simple  
![DxLib 2019_08_20 17_14_01](https://user-images.githubusercontent.com/28126083/63430627-00237280-c458-11e9-9288-b68f7fef742e.png)  
* Regular Sampling   
![DxLib 2019_08_20 17_15_12](https://user-images.githubusercontent.com/28126083/63430671-18938d00-c458-11e9-8733-a726e8615804.png)
* Random Sampling  
![DxLib 2019_08_20 18_56_37](https://user-images.githubusercontent.com/28126083/63430705-32cd6b00-c458-11e9-9e56-6ec6a090200a.png)
* Jittered Sampling  
![DxLib 2019_08_21 5_29_23](https://user-images.githubusercontent.com/28126083/63430735-47a9fe80-c458-11e9-8025-fffec18b4122.png)
