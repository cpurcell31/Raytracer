#include "Geometries.hpp"

//Box member functions
Box::Box(float const x2, float const x3, float const y2, float const y3, float const z2, float const z3)
	: x0{ x2 }, x1{ x3 }, y0{ y2 }, y1{ y3 }, z0{ z2 }, z1{ z3 }, hitface{ -1 }
{}

bool Box::hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) {
	float t{};
	bool intersect{ intersectRay(ray, t) };

	// update ShadeRec info about new closest hit
	if (intersect && t < sr.t)
	{
		sr.colour = c;
		sr.t = t;

		sr.hitPoint = ray.o + (ray.d * sr.t);
		//Normal calculation
		sr.normal = calculateNormal(sr);
		sr.mathit = mat;
	}

	return intersect;
}

//3
atlas::math::Vector Box::calculateNormal(ShadeRec& sr) {
	atlas::math::Vector normal{};

	atlas::math::Point center{ (x1 + x0) / 2, (y1 + y0) / 2, (z1 + z0) / 2 };
	atlas::math::Vector p = sr.hitPoint - center;
	float shadowBias = 1.0001f;

	float dx = abs(x1 - x0) / 2;
	float dy = abs(y1 - y0) / 2;
	float dz = abs(z1 - z0) / 2;

	normal = { (int)((p.x / dx) * shadowBias), (int)((p.y / dy) * shadowBias), (int)((p.z / dz) * shadowBias) };

	return glm::normalize(normal);
}

bool Box::intersectRay(atlas::math::Ray<atlas::math::Vector> const& ray, float& tmin) {
	float ox = ray.o.x, oy = ray.o.y, oz = ray.o.z;
	float dx = ray.d.x, dy = ray.d.y, dz = ray.d.z;

	float tx_min, ty_min, tz_min;
	float tx_max, ty_max, tz_max;

	float a = 1.0f / dx;

	if (a >= 0) {
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else {
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}

	float b = 1.0f / dy;

	if (b >= 0) {
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}
	else {
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}

	float cc = 1.0f / dz;

	if (cc >= 0) {
		tz_min = (z0 - oz) * cc;
		tz_max = (z1 - oz) * cc;
	}
	else {
		tz_min = (z1 - oz) * cc;
		tz_max = (z0 - oz) * cc;
	}

	float t0, t1;

	int face_in, face_out;

	if (tx_min > ty_min) {
		t0 = tx_min;
		face_in = (a >= 0.0) ? 0 : 3;
	}
	else {
		t0 = ty_min;
		face_in = (b >= 0.0) ? 1 : 4;
	}

	if (tz_min > t0) {
		t0 = tz_min;
		face_in = (cc >= 0.0) ? 2 : 5;
	}

	if (tx_max < ty_max) {
		t1 = tx_max;
		face_out = (a >= 0.0) ? 3 : 0;
	}
	else {
		t1 = ty_max;
		face_out = (b >= 0.0) ? 4 : 1;
	}

	if (tz_max < t1) {
		t1 = tz_max;
		face_out = (cc >= 0.0) ? 5 : 2;
	}

	if (t0 < t1 && t1 > 0) {
		if (t0 > 0) {
			tmin = t0;
		}
		else {
			tmin = t1;
		}
		return true;
	}
	else {
		return false;
	}
}