
#include <atlas/math/Math.hpp>
#include <atlas/math/Ray.hpp>
#include <atlas\math\Random.hpp>
#include <atlas\core\Float.hpp>
#include <atlas/utils/LoadObjFile.hpp>
#include <atlas\core\Timer.hpp>
#include "Sampler.hpp"
#include "Shape.hpp"
#include "Camera.hpp"
#include "Geometries.hpp"
#include "Light.hpp"
#include "Lights.hpp"
#include "Material.hpp"
#include "Materials.hpp"
#include "Multithreading.hpp"
#include "Samplers.hpp"

#include <fmt/printf.h>
#include <stb_image.h>
#include <stb_image_write.h>

#include <vector>
#include <iostream>
#include <random>
#include <thread>
#include <future>
#include <mutex>
#include <queue>

using namespace atlas;
using Colour = math::Vector;

static const float kInfinity = std::numeric_limits<float>::max();
static const int maxDepth = 5;

std::mutex futures_lock;
std::mutex jobs_lock;

void saveToBMP(std::string const& filename,
	std::size_t width,
	std::size_t height,
	std::vector<Colour> const& image);

struct World
{
	std::size_t width, height;
	Colour background;
	std::shared_ptr<Sampler> sampler;
	std::vector<std::shared_ptr<Shape>> scene;
	std::vector<Colour> image;
	std::vector<std::shared_ptr<Light>> lights;
	std::shared_ptr<Light> ambient;
};

struct ShadeRec {
	Colour colour;
	Colour shading;
	float t;
	bool hit;
	atlas::math::Point hitPoint;
	atlas::math::Vector normal;
	std::shared_ptr<Material> mathit;
	std::shared_ptr<World> world;
	int depth;
};