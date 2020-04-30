#pragma once

#include "Utilities.hpp"

class Sphere : public Shape {
public:
	Sphere(float const radius, float const radius2, atlas::math::Point const centreP);

	bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr);

private:
	bool intersectRay(atlas::math::Ray<atlas::math::Vector> const& ray, float& tmin);
	float r;
	float r2;
	atlas::math::Point centre;
};

class BoundingBox {
public:
	BoundingBox(float const x2, float const x3, float const y2, float const y3, float const z2, float const z3);

	bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr);

private:
	float x0;
	float x1;
	float y0;
	float y1;
	float z0;
	float z1;
};

class Plane : public Shape {

public:
	Plane(atlas::math::Vector const normal, atlas::math::Point const q);

	bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr);

private:
	bool intersectRay(atlas::math::Ray<atlas::math::Vector> const& ray, float& tmin);
	atlas::math::Vector norm;
	atlas::math::Point p;
};

class Triangle : public Shape {
public:

	Triangle(atlas::math::Point const& p, atlas::math::Point const& q, atlas::math::Point const& r);

	bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr);

	void calculateNormal();

private:
	bool intersectRay(atlas::math::Ray<atlas::math::Vector> const& ray, float& tmin);
	atlas::math::Point a;
	atlas::math::Point b;
	atlas::math::Point c;
	atlas::math::Vector normal;
};

class Box : public Shape {
public:

	Box(float const x2, float const x3, float const y2, float const y3, float const z2, float const z3);

	bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr);

	atlas::math::Vector calculateNormal(ShadeRec& sr);

	int hitface;
private:
	bool intersectRay(atlas::math::Ray<atlas::math::Vector> const& ray, float& tmin);
	float x0;
	float x1;
	float y0;
	float y1;
	float z0;
	float z1;
};

class Mesh : public Shape {
public:
	Mesh();

	std::shared_ptr<BoundingBox> getBBox();

	void setBBox(std::shared_ptr<BoundingBox> const& box);

	void setTriangles(std::vector<std::shared_ptr<Shape>> const& mesh);

	bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr);

	void transformMesh(glm::mat4 transform);

private:
	float xmax;
	float xmin;
	float ymax;
	float ymin;
	float zmax;
	float zmin;
	std::shared_ptr<BoundingBox> bbox;
	std::vector<std::shared_ptr<Shape>> triangles;
};
