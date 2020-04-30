#pragma once

#include "Utilities.hpp"

class Sampler {
public:
	Sampler(int numSamples, int numSets);
	virtual ~Sampler() = default;

	int getNumSamples(void) const;

	void setupShuffledIndeces();

	virtual void generateSamples() = 0;

	void mapSamplesToHemisphere(float const e);

	atlas::math::Point sampleUnitSquare();

	atlas::math::Point sampleHemisphere();

protected:
	std::vector<atlas::math::Point> samples;
	std::vector<atlas::math::Point> hemisphereSamples;
	std::vector<int> shuffledIndeces;

	int numSamples;
	int numSets;
	unsigned long count;
	int jump;
};