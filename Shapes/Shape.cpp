#include "Shape.hpp"

//Shape member functions
Shape::Shape() : c{ 0,0,0 }
{
	mat = std::make_shared<Material>(Material{});
}

void Shape::setColour(Colour const& colour) {
	c = colour;
}

void Shape::setMaterial(std::shared_ptr<Material> const& material) {
	mat = material;
}

Colour Shape::getColour(void) const {
	return c;
}

std::shared_ptr<Material> Shape::getMaterial(void) {
	return mat;
}