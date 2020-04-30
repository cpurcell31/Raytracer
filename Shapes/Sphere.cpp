#include "Geometries.hpp"

// Sphere member functions
Sphere::Sphere(float radius, float radius2, atlas::math::Point centreP) :
	r{ radius }, r2{ radius2 }, centre{ centreP }
{}

bool Sphere::hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) {
	float t{};
	bool intersect{ intersectRay(ray, t) };

	// update ShadeRec info about new closest hit
	if (intersect && t < sr.t)
	{
		sr.colour = c;
		sr.t = t;

		sr.hitPoint = ray.o + (ray.d * sr.t);
		sr.normal = sr.hitPoint - centre;
		sr.normal = glm::normalize(sr.normal);
		sr.mathit = mat;
	}

	return intersect;
}

bool Sphere::intersectRay(atlas::math::Ray<atlas::math::Vector> const& ray, float& tmin) {
	atlas::math::Vector temp = ray.o - centre;
	const float epsilon = 0.001f;
	float a = glm::dot(ray.d, ray.d);
	float b = 2.0f * glm::dot(temp, ray.d);
	float f = glm::dot(temp, temp) - r2;
	float disc = b * b - 4.0f * a * f;
	float t{};

	if (disc > 0.0f) {

		float e = sqrt(disc);
		float denom = 2.0f * a;
		t = (-b - e) / denom;

		if (t > epsilon) {
			tmin = t;
			return true;
		}

		t = (-b + e) / denom;
		if (t > epsilon) {
			tmin = t;
			return true;
		}
	}
	return false;
}