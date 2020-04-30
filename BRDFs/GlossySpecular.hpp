#pragma once

#include "Utilities.hpp"
#include "BRDF.hpp"

class GlossySpecular : public BRDF
{
public:
	GlossySpecular();
	GlossySpecular(Colour specColour, float specularReflection, float exp);

	Colour fn(ShadeRec const& sr,
		atlas::math::Vector const& reflected,
		atlas::math::Vector const& incoming) const override;

	Colour f(ShadeRec const& sr,
		atlas::math::Vector& reflected,
		atlas::math::Vector const& incoming,
		float& divisor) const;

	Colour rho(ShadeRec const& sr,
		atlas::math::Vector const& reflected) const override;

	void setSpecularReflection(float kd);

	void setPhongExp(float const exp);

	void setSpecularColour(Colour const& specColour);

private:
	float mSpecularReflection;
	float phongExp;
	Colour mSpecularColour;
};