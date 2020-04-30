#include "GlossySpecular.hpp"

// GlossySpecular member functions

GlossySpecular::GlossySpecular() : mSpecularColour{ 1,1,1 }, mSpecularReflection{}, phongExp{}
{}

GlossySpecular::GlossySpecular(Colour specColour, float specularReflection, float exp) :
	mSpecularColour{ specColour }, mSpecularReflection{ specularReflection }, phongExp{ exp }
{}

Colour GlossySpecular::fn(ShadeRec const& sr,
	atlas::math::Vector const& reflected,
	atlas::math::Vector const& incoming) const
{
	float diffuseDot = std::max(0.0f, glm::dot(sr.normal, incoming));
	atlas::math::Vector r = incoming + 2.0f * glm::dot(sr.normal, -incoming) * sr.normal;
	float phongDot = std::max(0.0f, glm::dot(r, -reflected));
	return powf(phongDot, phongExp) * diffuseDot * mSpecularReflection * mSpecularColour;
}

Colour GlossySpecular::f(ShadeRec const& sr,
	atlas::math::Vector& reflected,
	atlas::math::Vector const& incoming,
	float& divisor) const
{
	atlas::math::Vector r = -incoming + (2.0f * glm::dot(sr.normal, incoming) * sr.normal);
	atlas::math::Vector w = r;
	atlas::math::Vector u = glm::normalize(glm::cross({ 0.0075f, 1, 0.0065f }, w));
	atlas::math::Vector v = glm::cross(u, w);

	atlas::math::Point samplePoint = sr.world->sampler->sampleHemisphere();

	reflected = samplePoint.x * u + samplePoint.y * v + samplePoint.z * w;

	float refDot = glm::dot(sr.normal, reflected);
	if (refDot < 0.0f) {
		reflected = -samplePoint.x * u - samplePoint.y * v + samplePoint.z * w;
	}
	float phong = pow(glm::dot(r, reflected), phongExp);
	divisor = phong * glm::dot(sr.normal, reflected);
	return  phong * mSpecularReflection * mSpecularColour;
}

Colour GlossySpecular::rho([[maybe_unused]] ShadeRec const& sr,
	[[maybe_unused]] atlas::math::Vector const& reflected) const {
	return { 0,0,0 };
}

void GlossySpecular::setSpecularReflection(float kd) {
	mSpecularReflection = kd;
}

void GlossySpecular::setPhongExp(float const exp) {
	phongExp = exp;
}

void GlossySpecular::setSpecularColour(Colour const& specColour) {
	mSpecularColour = specColour;
}
