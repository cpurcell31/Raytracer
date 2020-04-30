#include "Materials.hpp"
#include "GlossySpecular.hpp"

//Plastic member functions
Plastic::Plastic() :
	Material{},
	mDiffuseBRDF{ std::make_shared<Lambertian>(Lambertian{}) },
	mSpecularBRDF{ std::make_shared<GlossySpecular>(GlossySpecular{}) }
{}

Plastic::Plastic(float const diffuseCoeff, float const specCoeff, float const exp, Colour const& diffuseColour) :
	Plastic{}
{
	setDiffuseReflection(diffuseCoeff);
	setSpecularReflection(specCoeff);
	setPhongExp(exp);
	setDiffuseColour(diffuseColour);
}

void Plastic::setDiffuseReflection(float const diffuseCoeff) {
	mDiffuseBRDF->setDiffuseReflection(diffuseCoeff);
}

void Plastic::setDiffuseColour(Colour const& diffuseColour) {
	mDiffuseBRDF->setDiffuseColour(diffuseColour);
}

void Plastic::setSpecularReflection(float const specCoeff) {
	mSpecularBRDF->setSpecularReflection(specCoeff);
}

void Plastic::setPhongExp(float const exp) {
	mSpecularBRDF->setPhongExp(exp);
}

Colour Plastic::shade(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) {
	Colour result{ 0,0,0 };
	Colour ambient{ 0,0,0 };

	float ambientCoefficient = 0.18f;

	atlas::math::Ray<atlas::math::Vector> rayShade;
	ShadeRec srShade{};
	bool shadow = false;

	Colour baseColour{ sr.colour };

	ambient = sr.world->ambient->illumination(sr) * ambientCoefficient;

	for (auto const& light : sr.world->lights) {
		shadow = false;
		Colour diffuse{ 0,0,0 };
		Colour phong{ 0,0,0 };
		//ambient += light->illumination(sr) * ambientCoefficient;

		//Shadows
		rayShade.d = light->getDirection(sr);
		rayShade.o = sr.hitPoint + sr.normal * 0.001f;
		for (auto obj : sr.world->scene) {
			if (obj->hit(rayShade, srShade) && light->distanceCheck(sr, srShade)) {
				shadow = true;
			}
		}
		if (!shadow) {
			//Diffuse
			float diffuseDot = std::max(0.0f, glm::dot(sr.normal, rayShade.d));
			diffuse = light->illumination(sr) * diffuseDot * mDiffuseBRDF->fn(sr, -ray.d, rayShade.d);

			//Specular
			phong = mSpecularBRDF->fn(sr, -ray.d, rayShade.d) * light->illumination(sr);
		}

		result += ambient + diffuse + phong;
	}

	sr.shading = result;
	return result * baseColour;
}