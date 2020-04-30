#include "Lights.hpp"

//Ambient member functions
Ambient::Ambient(float const i, Colour const& c)
	: Light(i, { 0,0,0 }, c)
{}

atlas::math::Vector Ambient::getDirection([[maybe_unused]] ShadeRec const& sr) {
	return { 0,0,0 };
}