#pragma once


#include "Utilities.hpp"
#include "Material.hpp"

class Shape {
public:
	Shape();
	virtual ~Shape() = default;

	virtual bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) = 0;

	Colour getColour(void) const;

	std::shared_ptr<Material> getMaterial(void);

	void setColour(Colour const& colour);

	void setMaterial(std::shared_ptr<Material> const& material);

protected:
	Colour c;
	std::shared_ptr<Material> mat;
};