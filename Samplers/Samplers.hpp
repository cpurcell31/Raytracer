#pragma once

#include "Utilities.hpp"

class Regular : public Sampler {
public:
	Regular(int nSamples, int nSets);

	void generateSamples(void);
};

class Jittered : public Sampler {
public:
	Jittered(int nSamples, int nSets);

	void generateSamples(void);
};
