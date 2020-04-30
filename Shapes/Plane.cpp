#include "Geometries.hpp"

//Plane member functions
Plane::Plane(atlas::math::Vector normal, atlas::math::Point q) :
	norm{ glm::normalize(normal) }, p{ q }
{}

bool Plane::hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) {
	float t{};
	bool intersect{ intersectRay(ray, t) };

	// update ShadeRec info about new closest hit
	if (intersect && t < sr.t)
	{
		sr.colour = c;
		sr.t = t;

		sr.hitPoint = ray.o + (ray.d * sr.t);
		sr.normal = norm;
		sr.mathit = mat;
	}

	return intersect;
}

bool Plane::intersectRay(atlas::math::Ray<atlas::math::Vector> const& ray, float& tmin) {
	float t = glm::dot((p - ray.o), norm) / glm::dot(ray.d, norm);
	const float epsilon = 0.001f;
	if (t > epsilon) {
		tmin = t;
		return true;
	}
	return false;
}