#include "Lights.hpp"

//Directional member functions
Directional::Directional(float const i, atlas::math::Vector const& dir, Colour const& c)
	: Light{ i, dir, c }
{}

atlas::math::Vector Directional::getDirection([[maybe_unused]] ShadeRec const& sr) {
	return -glm::normalize(direction);
}
