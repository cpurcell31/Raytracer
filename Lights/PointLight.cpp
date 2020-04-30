#include "Lights.hpp"

//Point member functions
PointLight::PointLight(float const i, atlas::math::Point const& position, Colour const& c)
	: pos{ position }, Light(i, { 0,0,0 }, c)
{}

atlas::math::Vector PointLight::getDirection(ShadeRec const& sr) {
	direction = glm::normalize(pos - sr.hitPoint);
	return direction;
}

float PointLight::getDistance(atlas::math::Point const& p) {
	return glm::length(pos - p);
}

atlas::math::Point PointLight::getPosition(void) {
	return pos;
}

bool PointLight::distanceCheck(ShadeRec const& sr, ShadeRec const& srShade) {
	float dToLight{ getDistance(sr.hitPoint) };
	float dToObj{ glm::length(srShade.hitPoint - sr.hitPoint) };
	if (dToObj < dToLight) {
		return true;
	}
	else {
		return false;
	}
}