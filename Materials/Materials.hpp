#pragma once

#include "Utilities.hpp"
#include "Lambertian.hpp"

class Matte : public Material
{
public:
	Matte();
	Matte(float const diffuseCoeff, Colour diffuseColour);

	void setDiffuseReflection(float const diffuseCoeff);

	void setDiffuseColour(Colour const& diffColour);

	Colour shade(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) override;
private:
	std::shared_ptr<Lambertian> mDiffuseBRDF;
};

class Reflective : public Material
{
public:
	Reflective();
	Reflective(float reflectionCoeff, Colour const& reflectColour);

	Colour shade(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) override;

	Colour reflectionTrace(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr);

	void setReflection(float reflectionCoeff);

	void setReflectionColour(Colour const& reflectColour);
private:
	std::shared_ptr<PerfectSpecular> mReflectiveBRDF;
};

class GlossyReflective : public Material
{
public:
	GlossyReflective();
	GlossyReflective(float reflectionCoeff, float exp, Colour const& reflectColour);

	Colour shade(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr) override;

	Colour reflectionTrace(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr);

	void setReflection(float reflectionCoeff);

	void setReflectionColour(Colour const& reflectColour);

	void setPhongExp(float exp);

private:
	std::shared_ptr<GlossySpecular> mReflectiveBRDF;
};

class Plastic : public Material
{
public:
	Plastic();
	Plastic(float diffuseCoeff, float const specCoeff, float const exp, Colour const& diffuseColour);

	void setDiffuseReflection(float const diffuseCoeff);

	void setDiffuseColour(Colour const& diffColour);

	void setSpecularReflection(float const specCoeff);

	void setPhongExp(float const exp);

	Colour shade(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& sr);
private:
	std::shared_ptr<Lambertian> mDiffuseBRDF;
	std::shared_ptr<GlossySpecular> mSpecularBRDF;
};
