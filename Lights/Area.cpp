#include "Lights.hpp"

//Area member functions
Area::Area(float const i, atlas::math::Vector const& pos, atlas::math::Vector const& norm, float const& r) :
	position{ pos }, radius{ r }, normal{ norm }, samplePoint{ atlas::math::Point{0,0,0} },
	Light{ i, {0,0,0}, {1,1,1} }
{}

void Area::setPosition(atlas::math::Vector const& pos)
{
	position = pos;
}

float Area::getRadius()
{
	return radius;
}

atlas::math::Vector Area::getPosition()
{
	return position;
}

atlas::math::Vector Area::getNormal()
{
	return glm::normalize(normal);
}

atlas::math::Vector Area::getDirection(ShadeRec const& sr)
{
	samplePoint = sampleUnitDisk();
	samplePoint = position + samplePoint;
	atlas::math::Vector wi{ samplePoint - sr.hitPoint };
	return glm::normalize(wi);
}

float Area::getDistance(atlas::math::Point const& p) {
	return glm::length(samplePoint - p);
}

Colour Area::illumination(ShadeRec const& sr) {
	atlas::math::Vector wi{ glm::normalize(samplePoint - sr.hitPoint) };

	float dot = glm::dot(-normal, wi);
	//float distance = glm::length(samplePoint - sr.hitPoint);
	return (colour * intensity) * (dot); // /(distance * distance);
}

atlas::math::Point Area::sampleUnitDisk()
{
	atlas::math::Random<float> engine;
	atlas::math::Point p{};
	do {
		p = { engine.getRandomRange(0.0f, 1.0f), engine.getRandomRange(0.0f, 1.0f), 0 };
		p = p * 2.0f - atlas::math::Point{ 1,1,0 };
	} while (glm::dot(p, p) >= 1.0f);
	return p * radius;
}

bool Area::distanceCheck(ShadeRec const& sr, ShadeRec const& srShade) {
	float dToLight{ getDistance(sr.hitPoint) };
	float dToObj{ glm::length(srShade.hitPoint - sr.hitPoint) };
	if (dToObj < dToLight) {
		return true;
	}
	else {
		return false;
	}
}