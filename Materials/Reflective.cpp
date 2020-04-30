#include "Materials.hpp"
#include "PerfectSpecular.hpp"


//Reflective member functions
Reflective::Reflective() :
	Material{},
	mReflectiveBRDF{ std::make_shared<PerfectSpecular>(PerfectSpecular{}) }
{}

Reflective::Reflective(float const reflectionCoeff, Colour const& reflectColour) :
	Reflective{}
{
	setReflection(reflectionCoeff);
	setReflectionColour(reflectColour);
}

void Reflective::setReflection(float const reflectionCoeff) {
	mReflectiveBRDF->setReflection(reflectionCoeff);
}

void Reflective::setReflectionColour(Colour const& reflectColour) {
	mReflectiveBRDF->setReflectionColour(reflectColour);
}


Colour Reflective::shade(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) {
	ShadeRec srReflect{};
	Plastic material{ Plastic{0.0f, 0.5f, 100.0f, sr.colour} };
	srReflect = sr;
	srReflect.world = sr.world;
	srReflect.depth = sr.depth + 1;
	srReflect.mathit = sr.mathit;
	srReflect.colour = sr.colour;
	srReflect.normal = sr.normal;
	srReflect.t = std::numeric_limits<float>::max();

	atlas::math::Ray<atlas::math::Vector> reflectRay{};
	Colour reflectionColour = mReflectiveBRDF->f(sr, reflectRay.d, -ray.d);
	reflectRay.o = sr.hitPoint + sr.normal * 0.00001f;

	Colour L{ material.shade(ray, sr) };

	L += reflectionTrace(reflectRay, srReflect) * reflectionColour * glm::dot(sr.normal, reflectRay.d);
	return L;
}

Colour Reflective::reflectionTrace(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) {
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