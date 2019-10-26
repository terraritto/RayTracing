void World::Build()
{
	int numSamples = 16;

	//set View Plane
	mViewPlane.SetHRes(600);
	mViewPlane.SetVRes(400);
	mViewPlane.SetPixelSize(1.0);
	mViewPlane.SetIsShowOutOfGamut(false);
	mViewPlane.SetSampler(std::move(std::make_shared<MultiJittered>(numSamples)));

	//set backgroundColor
	mBackGroundColor = RGBColor(0.0, 0.3 * 0.75, 0.25 * 0.75);

	//set Tracer
	mTracerPtr = std::make_shared<RayCast>(this);

	//Main Light
	std::shared_ptr<Ambient> ambientPtr = std::make_shared<Ambient>();
	ambientPtr->SetScaleRadiance(0.5);
	SetAmbientLight(ambientPtr);

	//Set Camera
	std::shared_ptr<Pinhole> pinholePtr = std::make_shared<Pinhole>();
	pinholePtr->SetEye(7.5, 4, 10);
	pinholePtr->SetLookAt(-1, 3.7, 0);
	pinholePtr->SetViewDistance(340);
	pinholePtr->ComputeUVW();
	SetCamera(pinholePtr);

	//Light
	std::shared_ptr<Directional> lightPtr = std::make_shared<Directional>();
	lightPtr->SetDirection(15, 15, 2.5);
	lightPtr->SetScaleRadiance(2.0);
	AddLight(lightPtr);

	std::shared_ptr<PointLight> lightPtr2 = std::make_shared<PointLight>();
	lightPtr2->SetLocation(15, 15, 2.5);
	lightPtr2->SetScaleRadiance(2.0);
	//AddLight(lightPtr2);

	/*
	std::shared_ptr<Directional> lightPtr = std::make_shared<Directional>();
	lightPtr->SetDirection(1, 1, 0);
	lightPtr->SetScaleRadiance(4.0);
	AddLight(lightPtr);
	*/
	//set object
	std::shared_ptr<Plastic> mattePtr1 = std::make_shared<Plastic>();
	std::shared_ptr<Lambertian> ambientBrdf1 = std::make_shared<Lambertian>();
	std::shared_ptr<Lambertian> diffuseBrdf1 = std::make_shared<Lambertian>();
	std::shared_ptr<GlossySpecular> glossyBrdf1 = std::make_shared<GlossySpecular>();
	ambientBrdf1->SetKa(0.25);
	ambientBrdf1->SetCd(1, 1, 0);
	diffuseBrdf1->SetKd(0.75);
	diffuseBrdf1->SetCd(1, 1, 0);
	glossyBrdf1->SetKs(0.25);
	glossyBrdf1->SetCs(1, 1, 0);
	glossyBrdf1->SetExp(50);

	mattePtr1->SetAmbientBRDF(ambientBrdf1);
	mattePtr1->SetDiffuseBRDF(diffuseBrdf1);
	mattePtr1->SetSpecularBRDF(glossyBrdf1);

	std::shared_ptr<Sphere> spherePtr1 = std::make_shared<Sphere>(Point3D(3.85, 2.3, -2.55), 2.3);
	spherePtr1->SetMaterial(mattePtr1);
	AddObject(spherePtr1);

	std::shared_ptr<Plastic> mattePtr2 = std::make_shared<Plastic>();
	std::shared_ptr<Lambertian> ambientBrdf2 = std::make_shared<Lambertian>();
	std::shared_ptr<Lambertian> diffuseBrdf2 = std::make_shared<Lambertian>();
	std::shared_ptr<GlossySpecular> glossyBrdf2 = std::make_shared<GlossySpecular>();
	ambientBrdf2->SetKa(0.45);
	ambientBrdf2->SetCd(0.75, 0.25, 0);
	diffuseBrdf2->SetKd(0.75);
	diffuseBrdf2->SetCd(0.75, 0.25, 0);
	glossyBrdf2->SetKs(0.25);
	glossyBrdf2->SetCs(0.75, 0.25, 0);
	glossyBrdf2->SetExp(500);

	mattePtr2->SetAmbientBRDF(ambientBrdf2);
	mattePtr2->SetDiffuseBRDF(diffuseBrdf2);
	mattePtr2->SetSpecularBRDF(glossyBrdf2);

	std::shared_ptr<Sphere> spherePtr2 = std::make_shared<Sphere>(Point3D(-0.7, 1, 4.2), 2);
	spherePtr2->SetMaterial(mattePtr2);
	AddObject(spherePtr2);

	/*
	std::shared_ptr<Matte> mattePtr3 = std::make_shared<Matte>();
	mattePtr3->SetKa(0.15);
	mattePtr3->SetKd(0.5);
	mattePtr3->SetCd(0, 0.4, 0.2);
	std::shared_ptr<Plane> planePtr = std::make_shared<Plane>(Point3D(0, 0, -50), Normal(0,0,1));
	planePtr->SetMaterial(mattePtr3);
	AddObject(planePtr);
	*/
}