#pragma once

#include "Utilities.hpp"

class Light {
public:
	Light(float const i, atlas::math::Vector const& dir, Colour const& c);

	virtual atlas::math::Vector getDirection(ShadeRec const& sr) = 0;

	virtual Colour illumination(ShadeRec const& sr);

	Colour getColour(void);

	float getIntensity(void);

	virtual bool distanceCheck(ShadeRec const& sr, ShadeRec const& srShade);

protected:
	float intensity;
	atlas::math::Vector direction;
	Colour colour;
};