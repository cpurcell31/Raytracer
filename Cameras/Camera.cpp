#include "Camera.hpp"

//Camera member functions
Camera::Camera() :
	eye{ 0.0f, 0.0f, 500.0f },
	l{ 0.0f },
	up{ 0.0f, 1.0f, 0.0f },
	u{ 1.0f, 0.0f, 0.0f },
	v{ 0.0f, 1.0f, 0.0f },
	w{ 0.0f, 0.0f, 1.0f }
{}

void Camera::computeUVW(void) {
	w = eye - l;
	w = glm::normalize(w);

	u = glm::cross(up, w);
	u = glm::normalize(u);

	v = glm::cross(w, u);
	v = glm::normalize(v);
}

atlas::math::Vector Camera::convertToVS(atlas::math::Vector const& p) {
	atlas::math::Vector newDirection = p.x * u + p.y * v - d * w;
	return glm::normalize(newDirection);
}

atlas::math::Point Camera::getEye(void) {
	return eye;
}

atlas::math::Vector Camera::getU(void) {
	return u;
}

atlas::math::Vector Camera::getV(void) {
	return v;
}

void Camera::setEye(atlas::math::Point const& e) {
	eye = e;
}

void Camera::setLookAt(atlas::math::Point const& look) {
	l = look;
}

void Camera::setUpVector(atlas::math::Vector const& UP) {
	up = UP;
}

void Camera::setD(float const& dist) {
	d = dist;
}

/////////
std::vector<Colour> Camera::renderScene(std::shared_ptr<World>& world, std::size_t startIndex, std::size_t endIndex)
{
	using atlas::math::Point;
	using atlas::math::Ray;
	using atlas::math::Vector;

	atlas::math::Ray<atlas::math::Vector> ray;
	atlas::math::Ray<atlas::math::Vector> rayShade;

	Colour pixel = { 0,0,0 };
	std::vector<Colour> pixels{};

	ShadeRec sr{};
	ShadeRec srShade{};

	sr.world = world;

	for (std::size_t y{ startIndex }; y < endIndex; ++y) {
		for (std::size_t x{ 0 }; x < world->width; ++x) {
			pixel = { 0,0,0 };
			for (std::size_t p{ 0 }; p < world->sampler->getNumSamples(); ++p) {

				//Set-up
				sr.t = std::numeric_limits<float>::max();
				sr.colour = { 0,0,0 };
				sr.shading = { 0,0,0 };
				atlas::math::Point sample = world->sampler->sampleUnitSquare();

				//Sampling
				float originX = (x - 0.5f * world->width + sample.x);
				float originY = (y - 0.5f * world->height + sample.y);

				//Camera View conversion
				ray.o = { originX, originY, eye.z };
				ray.d = convertToVS(ray.o);
				ray.o = eye;

				//Trace ray, evaluate shading and shadows
				for (auto obj : world->scene) {
					sr.depth = 0;
					if (obj->hit(ray, sr)) {
						sr.shading = sr.mathit->shade(ray, sr);
					}
				}

				sr.colour = sr.shading;

				//Out of gamut limitting
				float max = std::max(sr.colour.r, std::max(sr.colour.g, sr.colour.b));
				if (max > 1.0f) {
					sr.colour = sr.colour / max;
				}

				pixel += sr.colour;
			}
			pixels.push_back(pixel / (float)world->sampler->getNumSamples());
			//world->image.push_back(pixel / (float)world->sampler->getNumSamples());
		}

	}
	return pixels;
}