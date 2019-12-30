int numSamples = 16;

//set View Plane
mViewPlane.SetHRes(600);
mViewPlane.SetVRes(350);
mViewPlane.SetPixelSize(1.0);
mViewPlane.SetIsShowOutOfGamut(false);
mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

//set backgroundColor
mBackGroundColor = RGBColor(0.5);

//set Tracer
mTracerPtr = std::make_shared<RayCast>(this);

//Main Light
std::shared_ptr<MultiJittered> samplePtr = std::make_shared<MultiJittered>(numSamples);


std::shared_ptr<AmbientOccluder> ambientPtr = std::make_shared<AmbientOccluder>();
ambientPtr->SetRadiance(1.0);
ambientPtr->SetColor(white);
ambientPtr->SetMinAmount(0.5);
ambientPtr->SetSampler(samplePtr);
SetAmbientLight(ambientPtr);

//Add Light
std::shared_ptr<Directional> light_ptr = std::make_shared<Directional>();
light_ptr->SetDirection(10, 15, 20);
light_ptr->SetScaleRadiance(3.0);
light_ptr->SetIsShadow(true);
AddLight(light_ptr);

//Set Camera
std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
pinholePtr->SetEye(0, 15.75, 50);
pinholePtr->SetLookAt(0, 2, 0);
pinholePtr->SetViewDistance(3500);
pinholePtr->ComputeUVW();
SetCamera(pinholePtr);

//set object
std::shared_ptr<Phong> phong_ptr = std::make_shared<Phong>();
phong_ptr->SetCd(0.7, 0.5, 0);
phong_ptr->SetKa(0.3);
phong_ptr->SetKd(0.75);
phong_ptr->SetKs(0.15);
phong_ptr->SetExp(3.0);

//cylinder param
double radius = 1.0;
double bevel_radius = 0.25;

//short cylinder
double y0 = 0.0, y1 = 2.0;

std::shared_ptr<Instance> cylinder_ptr1 =
std::make_shared<Instance>(
	std::make_shared<BeveledCylinder>(y0, y1, radius, bevel_radius)
	);

cylinder_ptr1->Translate(-2.75, 0, 0);
cylinder_ptr1->SetMaterial(phong_ptr);
AddObject(cylinder_ptr1);

//tall cylinder
y0 = 0.0; y1 = 4.0;
std::shared_ptr<BeveledCylinder> cylinder_ptr2 = std::make_shared<BeveledCylinder>(y0, y1, radius, bevel_radius);
cylinder_ptr2->SetMaterial(phong_ptr);
AddObject(cylinder_ptr2);

// scaled cylinder
y0 = 0.0, y1 = 2.0;

std::shared_ptr<Instance> cylinder_ptr3 =
std::make_shared<Instance>(
	std::make_shared<BeveledCylinder>(y0, y1, radius, bevel_radius)
	);

cylinder_ptr3->Scale(1, 2, 1);
cylinder_ptr3->Translate(2.75, 0, 0);
cylinder_ptr3->SetMaterial(phong_ptr);
AddObject(cylinder_ptr3);

//ground plane
std::shared_ptr<Matte> matte_ptr = std::make_shared<Matte>();
matte_ptr->SetCd(1);
matte_ptr->SetKa(0.25);
matte_ptr->SetKd(1);

std::shared_ptr<Plane> plane_ptr = std::make_shared<Plane>(Point3D(0), Normal(0, 1, 0));
plane_ptr->SetMaterial(matte_ptr);
AddObject(plane_ptr);