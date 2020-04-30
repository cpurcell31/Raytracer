#pragma once

#include "Utilities.hpp"

class Ambient : public Light {
public:
	Ambient(float const i, Colour const& c);

	atlas::math::Vector getDirection([[maybe_unused]] ShadeRec const& sr);

};

class Directional : public Light {
public:
	Directional(float const i, atlas::math::Vector const& dir, Colour const& c);

	atlas::math::Vector getDirection([[maybe_unused]] ShadeRec const& sr);
};


class PointLight : public Light {
public:
	PointLight(float const i, atlas::math::Point const& position, Colour const& c);

	atlas::math::Vector getDirection(ShadeRec const& sr);

	atlas::math::Point getPosition(void);

	float getDistance(atlas::math::Point const& p);

	bool distanceCheck(ShadeRec const& sr, ShadeRec const& srShade) override;

private:
	atlas::math::Point pos;
};

class Area : public Light
{
public:
	Area(float const i, atlas::math::Point const& pos, atlas::math::Vector const& norm, float const& r);

	void setPosition(atlas::math::Point const& pos);

	float getRadius();

	atlas::math::Point getPosition();

	atlas::math::Vector getDirection(ShadeRec const& sr);

	float getDistance(atlas::math::Point const& p);

	atlas::math::Vector getNormal();

	atlas::math::Point sampleUnitDisk();

	Colour illumination(ShadeRec const& sr) override;

	bool distanceCheck(ShadeRec const& sr, ShadeRec const& srShade) override;

private:
	atlas::math::Point position;
	float radius;
	atlas::math::Point samplePoint;
	atlas::math::Vector normal;

};

class AmbientOcclusion : public Light
{
public:
	AmbientOcclusion();

	void setAmbient(Colour min);

	void computeUVW(ShadeRec const& sr);

	Colour illumination(ShadeRec const& sr) override;

	atlas::math::Vector getDirection(ShadeRec const& sr);

private:
	atlas::math::Vector u;
	atlas::math::Vector v;
	atlas::math::Vector w;
	Colour minColour;
};