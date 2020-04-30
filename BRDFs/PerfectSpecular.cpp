#include "PerfectSpecular.hpp"

//PerfectSpecular member functions

PerfectSpecular::PerfectSpecular() : mReflection{}, mReflectionColour{ 1,1,1 }
{}

PerfectSpecular::PerfectSpecular(Colour reflectColour, float reflectCoefficient) :
	mReflection{ reflectCoefficient }, mReflectionColour{ reflectColour }
{}

void PerfectSpecular::setReflection(float reflectionCoeff) {
	mReflection = reflectionCoeff;
}

void PerfectSpecular::setReflectionColour(Colour const& reflectColour) {
	mReflectionColour = reflectColour;
}

Colour PerfectSpecular::f(ShadeRec const& sr,
	atlas::math::Vector& reflected,
	atlas::math::Vector const& incoming) const
{
	float diffDot = glm::dot(sr.normal, incoming);
	reflected = -incoming + (2.0f * sr.normal * diffDot);
	return (mReflection * mReflectionColour) / fabs(glm::dot(sr.normal, reflected));
}

Colour PerfectSpecular::fn([[maybe_unused]] ShadeRec const& sr,
	[[maybe_unused]] atlas::math::Vector const& reflected,
	[[maybe_unused]] atlas::math::Vector const& incoming) const
{
	return { 0,0,0 };
}

Colour PerfectSpecular::rho([[maybe_unused]] ShadeRec const& sr,
	[[maybe_unused]] atlas::math::Vector const& reflected) const
{
	return { 0,0,0 };
}

Colour Material::shade([[maybe_unused]] atlas::math::Ray<atlas::math::Vector> const& ray, [[maybe_unused]] ShadeRec& sr) {
	Colour result{ 0,0,0 };
	return result;
}