#pragma once

#include "Utilities.hpp"

class BRDF
{
public:
	virtual ~BRDF() = default;

	virtual Colour fn(ShadeRec const& sr,
		atlas::math::Vector const& reflected,
		atlas::math::Vector const& incoming) const = 0;
	virtual Colour rho(ShadeRec const& sr,
		atlas::math::Vector const& reflected) const = 0;

};