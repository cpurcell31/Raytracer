#include "Geometries.hpp"

//BoundingBox member functions
BoundingBox::BoundingBox(float const x2, float const x3, float const y2, float const y3, float const z2, float const z3) :
	x0{ x2 }, x1{ x3 }, y0{ y2 }, y1{ y3 }, z0{ z2 }, z1{ z3 }
{}

bool BoundingBox::hit(atlas::math::Ray<atlas::math::Vector> const& ray, [[maybe_unused]] ShadeRec& sr) {
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


	if (tx_min > ty_min) {
		t0 = tx_min;
	}
	else {
		t0 = ty_min;
	}

	if (tz_min > t0) {
		t0 = tz_min;
	}

	if (tx_max < ty_max) {
		t1 = tx_max;
	}
	else {
		t1 = ty_max;
	}

	if (tz_max < t1) {
		t1 = tz_max;
	}

	if (t0 < t1 && t1 > 0) {
		return true;
	}
	else {
		return false;
	}
}