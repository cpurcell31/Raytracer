#include "Light.hpp"

//Light member functions
Light::Light(float const i, atlas::math::Vector const& dir, Colour const& c)
	: intensity{ i }, direction{ dir }, colour{ c }
{}

Colour Light::getColour(void) {
	return colour;
}

float Light::getIntensity(void) {
	return intensity;
}

Colour Light::illumination([[maybe_unused]] ShadeRec const& sr) {
	return intensity * colour;
}

bool Light::distanceCheck([[maybe_unused]] ShadeRec const& sr, [[maybe_unused]] ShadeRec const& srShade) {
	return true;
}