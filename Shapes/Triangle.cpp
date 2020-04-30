#include "Geometries.hpp"

//Triangle member functions
Triangle::Triangle(atlas::math::Point const& p, atlas::math::Point const& q, atlas::math::Point const& r) :
	a{ p }, b{ q }, c{ r }, Shape{}
{
	calculateNormal();
}

bool Triangle::hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) {
	float t{};
	bool intersect{ intersectRay(ray, t) };

	// update ShadeRec info about new closest hit
	if (intersect && t < sr.t)
	{
		sr.colour = c;
		sr.t = t;

		sr.hitPoint = ray.o + (ray.d * sr.t);
		//Normal calculation
		sr.normal = normal;
		sr.mathit = mat;
	}

	return intersect;
}

bool Triangle::intersectRay(atlas::math::Ray<atlas::math::Vector> const& ray, float& tmin) {
	float a1 = a.x - b.x, b1 = a.x - c.x, c1 = ray.d.x, d1 = a.x - ray.o.x;
	float e1 = a.y - b.y, f1 = a.y - c.y, g1 = ray.d.y, h1 = a.y - ray.o.y;
	float i1 = a.z - b.z, j1 = a.z - c.z, k1 = ray.d.z, l1 = a.z - ray.o.z;

	float m1 = (f1 * k1 - g1 * j1);
	float n1 = (h1 * k1 - g1 * l1);
	float p1 = (f1 * l1 - h1 * j1);
	float q1 = (g1 * i1 - e1 * k1);
	float s1 = (e1 * j1 - f1 * i1);

	float denominator = 1.0f / ((a1 * m1) + (b1 * q1) + (c1 * s1));

	float beta = ((d1 * m1) - (b1 * n1) - (c1 * p1)) * denominator;

	if (beta < 0.0f) {
		return false;
	}

	float r1 = e1 * l1 - h1 * i1;

	float gamma = ((a1 * n1) + (d1 * q1) + (c1 * r1)) * denominator;

	if (gamma < 0.0f) {
		return false;
	}

	if (beta + gamma > 1.0f) {
		return false;
	}

	float t = ((a1 * p1) - (b1 * r1) + (d1 * s1)) * denominator;

	if (t < 0.0f) {
		return false;
	}

	tmin = t;

	return true;

}

void Triangle::calculateNormal() {
	normal = glm::normalize(glm::cross(b - a, c - a));
}