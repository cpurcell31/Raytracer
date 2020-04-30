/* References Code from:
1. Ray Tracing From the Ground Up by Kevin Suffern
2. Lectures and Labs by Maurico Rovira Galvez
3. https://blog.johnnovak.net/2016/10/22/the-nim-raytracer-project-part-4-calculating-box-normals/
4. https://realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
*/

#include "Utilities.hpp"

//COMPLETED Features

//Camera System
//Point Lights
//Diffuse Shading
//Jittered multisampling
//Out-of-gamut handling
//Sphere, Box, Plane geometries
//Shadows 1
//Area Lights 1
//Mirror Reflections 1
//Ambient Occlusion 1
//Glossy Reflections 1
//Mesh 1
//Triangle intersection (needed for Meshes) 0
//Basic multithreading 1
//Intermediate multithreading 2




//To IMPLEMENT

//Regular grid? 
//Simple path tracing? 
//Simple Transparency? 


int main()
{
	// Your code here.
	atlas::core::Timer<float> timer{};

	std::shared_ptr<Shape> teapotMesh{ std::make_shared<Mesh>(Mesh{}) };
	teapotMesh->setColour({ 1,0,1 });
	teapotMesh->setMaterial(std::make_shared<Matte>(Matte{ 1.0f, Colour{1,0,1} }));
	std::vector<std::shared_ptr<Shape>> teapot{};
	teapot.push_back(teapotMesh);

	atlas::math::Ray<atlas::math::Vector> ray;
	atlas::math::Ray<atlas::math::Vector> rayShade;

	Camera camera = Camera();
	camera.setD(100.0f);
	camera.setEye({ -150.0f, -80.0f, -50.0f });
	camera.setLookAt({ 0,0,0 });
	camera.setUpVector({ 0,1,0 });
	camera.computeUVW();

	std::vector<std::shared_ptr<Light>> lights{};

	std::shared_ptr<Light> occluder_ptr{};
	occluder_ptr = std::make_shared<AmbientOcclusion>();
	//lights.push_back(occluder_ptr);

	//Ambient light not working atm
	std::shared_ptr<Light> ambient_ptr{};
	ambient_ptr = std::make_shared<Ambient>
		(Ambient{ 1.0f, Colour{1,1,1} });
	//lights.push_back(ambient_ptr);

	std::shared_ptr<Light> directional_ptr{};
	directional_ptr = std::make_shared<Directional>
		(Directional{ 1.0f, atlas::math::Vector{1.0f, 0.25f,-0.25f}, Colour{1,1,1} });
	//lights.push_back(directional_ptr);

	//Point light distance to light intersection thingy happens if too low to ground
	std::shared_ptr<PointLight> point_ptr{};
	point_ptr = std::make_shared<PointLight>(PointLight{ 0.5f, {-250, -150, 0}, Colour{1,1,1} });
	lights.push_back(point_ptr);

	std::shared_ptr<Area> area_ptr = 
		std::make_shared<Area>(Area{ 0.7f, atlas::math::Point{-50, -80, 0}, atlas::math::Vector{0.0f, 1.0f, 0.0f}, 45.0f });
	lights.push_back(area_ptr);

	std::vector<std::shared_ptr<Shape>> objects{};

	std::shared_ptr<Shape> sph_ptr1{};
	sph_ptr1 = std::make_shared<Sphere>(Sphere{ 50,  50 * 50, atlas::math::Point{ -75,0, 100 } });
	sph_ptr1->setColour({ 0.0f,0.0f,1.0f });
	sph_ptr1->setMaterial(std::make_shared<GlossyReflective>(GlossyReflective{ 0.9f, 100.0f, Colour{1,1,1} }));
	teapot.push_back(sph_ptr1);
	//({ 0.0f,0.0f,1.0f });
	//<Plastic>(Plastic{ 1.0f, 1.0f, 10.0f, Colour{0,0,1} }

	std::shared_ptr<Shape> sph_ptr2{};
	sph_ptr2 = std::make_shared<Sphere>(Sphere{ 100,  100 * 100, atlas::math::Point{ -25,0, 275 } });
	sph_ptr2->setColour({ 0.0f,1.0f,1.0f });
	sph_ptr2->setMaterial(std::make_shared<Matte>(Matte{ 1.0f, Colour{0, 1, 1} }));
	teapot.push_back(sph_ptr2);

	std::shared_ptr<Shape> pl_ptr1{};
	pl_ptr1 = std::make_shared<Plane>(Plane{ atlas::math::Vector{ 0,-1,0 }, atlas::math::Point{ 0,50,-10 } });
	pl_ptr1->setColour({ 1,1,1 });
	pl_ptr1->setMaterial(std::make_shared<Plastic>(Plastic{ 1.0f, 0.25f, 10.0f, Colour{0.75f,0.75f,0.75f} }));
	teapot.push_back(pl_ptr1);
	//Reflective>(Reflective{ 0.9f, Colour{1,1,1} })
	//<Plastic>(Plastic{ 1.0f, 1.0f, 10.0f, Colour{1,0,0} })

	std::shared_ptr<Shape> p2_ptr1{};
	p2_ptr1 = std::make_shared<Plane>(Plane{ atlas::math::Vector{ -1,0,0 }, atlas::math::Point{ 150,0,0 } });
	p2_ptr1->setColour({ 0.25f,0.25f,0.25f });
	p2_ptr1->setMaterial(std::make_shared<Reflective>(Reflective{ 0.9f, Colour{1.0f,1.0f,1.0f} }));
	teapot.push_back(p2_ptr1);

	std::shared_ptr<Shape> box_ptr1{};
	box_ptr1 = std::make_shared<Box>(Box{ -50, 50, 0, 100, -50, 50 });
	box_ptr1->setColour({ 1.0f,0.0f,0.0f });
	box_ptr1->setMaterial(std::make_shared<Matte>(Matte{ 1.0f, Colour{1,0,0} }));
	teapot.push_back(box_ptr1);
	//<GlossyReflective>(GlossyReflective{ 0.9f, 32.0f, Colour{1,1,1} })
	//<Matte>(Matte{ 1.0f, Colour{1,0,1} })

	std::shared_ptr<Shape> box_ptr2{};
	box_ptr2 = std::make_shared<Box>(Box{ -100, -50, 25, 100, -50, 50 });
	box_ptr2->setColour({ 1.0f,0.0f,0.0f });
	box_ptr2->setMaterial(std::make_shared<Matte>(Matte{ 1.0f, Colour{1,0,0} }));
	teapot.push_back(box_ptr2);

	std::shared_ptr<Shape> box_ptr3{};
	box_ptr3 = std::make_shared<Box>(Box{ -50, 50, -50, 100, -125, -75 });
	box_ptr3->setColour({ 1.0f,0.25f,0.0f });
	box_ptr3->setMaterial(std::make_shared<GlossyReflective>(GlossyReflective{ 0.9f, 100.0f, Colour{1,1,1} }));
	teapot.push_back(box_ptr3);

	std::shared_ptr<Shape> box_ptr4{};
	box_ptr4 = std::make_shared<Box>(Box{ -125, -100, 0, 100, -100, -50 });
	box_ptr4->setColour({ 1.0f,0.8f,0.9f });
	box_ptr4->setMaterial(std::make_shared<Plastic>(Plastic{ 1.0f, 1.0f, 32.0f, Colour{1.0f, 0.8f, 0.9f} }));
	teapot.push_back(box_ptr4);

	std::shared_ptr<World> world{ std::make_shared<World>() };
	//world->scene = objects;
	world->scene = teapot;
	world->ambient = occluder_ptr;
	//world->ambient = ambient_ptr;
	world->lights = lights;
	world->sampler = std::make_shared<Jittered>(4, 50);
	world->sampler->mapSamplesToHemisphere(10.0f);
	world->height = 1000;
	world->width = 1000;

	timer.start();

	//world->image = camera.renderScene(world, 0, 1000);

	//saveToBMP("render.bmp", world->width, world->height, world->image);

	//threadTesting(world);

	ThreadTesting2(world);

	std::cout << timer.elapsed() << "\n";

	return 0;
}

/**
 * Saves a BMP image file based on the given array of pixels. All pixel values
 * have to be in the range [0, 1].
 *
 * @param filename The name of the file to save to.
 * @param width The width of the image.
 * @param height The height of the image.
 * @param image The array of pixels representing the image.
 */
void saveToBMP(std::string const& filename,
	std::size_t width,
	std::size_t height,
	std::vector<Colour> const& image)
{
	std::vector<unsigned char> data(image.size() * 3);

	for (std::size_t i{ 0 }, k{ 0 }; i < image.size(); ++i, k += 3)
	{
		Colour pixel = image[i];
		data[k + 0] = static_cast<unsigned char>(pixel.r * 255);
		data[k + 1] = static_cast<unsigned char>(pixel.g * 255);
		data[k + 2] = static_cast<unsigned char>(pixel.b * 255);
	}

	stbi_write_bmp(filename.c_str(),
		static_cast<int>(width),
		static_cast<int>(height),
		3,
		data.data());
}


void threadTesting(std::shared_ptr<World>& world) {
	std::vector<std::thread> tasks{};
	std::vector<std::future<std::vector<Colour>>> futures;

	std::size_t numThreads{ std::thread::hardware_concurrency() };

	std::size_t index{};
	std::size_t finalIndex{};
	
	std::vector<Colour> finalResult{};

	auto f1 = [&world](std::size_t startIndex, std::size_t endIndex) {
		std::vector<Colour> pixels{};
		Camera camera = Camera();
		camera.setD(100.0f);
		camera.setEye({ -150.0f, -80.0f, -50.0f });
		camera.setLookAt({ 0,0,0 });
		camera.setUpVector({ 0,1,0 });
		camera.computeUVW();
		pixels = camera.renderScene(world, startIndex, endIndex);
		return pixels;
	};

	if (!(world->height % numThreads == 0)) {
		index = world->height / (numThreads-1);
		finalIndex = (numThreads - 1) * index;
	}
	else {
		index = world->height / numThreads;
		finalIndex = (numThreads - 1) * index;
	}

	for (std::size_t i{ 0 }; i < numThreads-1; ++i) {
		std::size_t start{ i * index };
		std::size_t end{ (i + 1) * index };
		auto future = std::async(std::launch::async, f1, start, end);
		futures.push_back(std::move(future));
	}


	futures.push_back(std::move(std::async(std::launch::async, f1, finalIndex, world->height)));

	for (auto& future : futures) {
		auto result = future.get();
		finalResult.insert(finalResult.end(), result.begin(), result.end());
	}
	
	saveToBMP("render.bmp", world->width, world->height, finalResult);
}

void ThreadTesting2(std::shared_ptr<World>& world) {
	std::shared_ptr<Controller> mc;
	mc = std::make_shared<Controller>(Controller{ world });
	std::vector<std::future<int>> futures;
	for (std::size_t i{ 0 }; i < std::thread::hardware_concurrency(); ++i) {
		JobThread* j = new JobThread(world, mc);
		auto future = std::async(std::launch::async, &JobThread::mainJobLoop, j);
		futures.push_back(std::move(future));
	}

	for (auto& future : futures) {
		auto result = future.get();
		if (result == 1) {
			;
		}
	}
	
	std::vector<Colour> finalImage = mc->getImage();
	saveToBMP("render.bmp", world->width, world->height, finalImage);
}



