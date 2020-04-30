#pragma once

#include "BRDF.hpp"

class Lambertian : public BRDF
{
public:
	Lambertian();
	Lambertian(Colour diffuseColor, float diffuseReflection);

	Colour fn(ShadeRec const& sr,
		atlas::math::Vector const& reflected,
		atlas::math::Vector const& incoming) const override;

	Colour rho(ShadeRec const& sr,
		atlas::math::Vector const& reflected) const override;

	void setDiffuseReflection(float kd);

	void setDiffuseColour(Colour const& colour);

private:
	Colour mDiffuseColour;
	float mDiffuseReflection;
};