#pragma once

#include "Utilities.hpp"
#include "BRDF.hpp"

class PerfectSpecular : public BRDF
{
public:
	PerfectSpecular();
	PerfectSpecular(Colour reflectColour, float reflectCoefficient);

	Colour fn(ShadeRec const& sr,
		atlas::math::Vector const& reflected,
		atlas::math::Vector const& incoming) const override;

	Colour f(ShadeRec const& sr,
		atlas::math::Vector& reflected,
		atlas::math::Vector const& incoming) const;

	Colour rho(ShadeRec const& sr,
		atlas::math::Vector const& reflected) const override;

	void setReflection(float const reflectionCoeff);

	void setReflectionColour(Colour const& reflectColour);

private:
	float mReflection;
	Colour mReflectionColour;
};