#include "Materials.hpp"
#include "GlossySpecular.hpp"


//GlossyReflective member functions
GlossyReflective::GlossyReflective() :
	Material{},
	mReflectiveBRDF{ std::make_shared<GlossySpecular>(GlossySpecular{}) }
{}

GlossyReflective::GlossyReflective(float reflectionCoeff, float exp, Colour const& reflectColour) :
	GlossyReflective{}
{
	setReflection(reflectionCoeff);
	setReflectionColour(reflectColour);
	setPhongExp(exp);
}

void GlossyReflective::setReflection(float reflectionCoeff) {
	mReflectiveBRDF->setSpecularReflection(reflectionCoeff);
}

void GlossyReflective::setReflectionColour(Colour const& reflectColour) {
	mReflectiveBRDF->setSpecularColour(reflectColour);
}

void GlossyReflective::setPhongExp(float exp) {
	mReflectiveBRDF->setPhongExp(exp);
}

Colour GlossyReflective::shade(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) {
	ShadeRec srReflect{};
	Plastic material{ Plastic{0.0f, 0.8f, 32.0f, sr.colour} };
	srReflect.world = sr.world;
	srReflect.depth = sr.depth + 1;
	srReflect.mathit = sr.mathit;
	srReflect.t = std::numeric_limits<float>::max();
	float divisor;

	atlas::math::Ray<atlas::math::Vector> reflectRay{};
	Colour reflectionColour = mReflectiveBRDF->f(sr, reflectRay.d, -ray.d, divisor);
	reflectRay.o = sr.hitPoint + sr.normal * 0.01f;

	Colour L{ material.shade(ray, sr) };

	L += reflectionTrace(reflectRay, srReflect) * glm::dot(sr.normal, reflectRay.d) * reflectionColour / divisor;
	return L;
}

Colour GlossyReflective::reflectionTrace(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) {
	if (sr.depth > maxDepth) {
		return { 0,0,0 };
	}
	bool objHit = false;
	for (auto obj : sr.world->scene) {
		if (obj->hit(ray, sr)) {
			objHit = true;
		}
	}
	if (objHit) {
		return sr.mathit->shade(ray, sr);
	}
	else {
		return { 0,0,0 };
	}
}