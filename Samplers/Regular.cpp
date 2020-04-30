#include "Samplers.hpp"

Regular::Regular(int const nSamples, int const nSets) : Sampler(nSamples, nSets)
{
	generateSamples();
}

void Regular::generateSamples(void) {
	int n = static_cast<int>(glm::sqrt(static_cast<float>(numSamples)));

	for (int j = 0; j < numSets; ++j)
	{
		for (int p = 0; p < n; ++p)
		{
			for (int q = 0; q < n; ++q)
			{
				samples.push_back(atlas::math::Point{ (q + 0.5f) / n, (p + 0.5f) / n, 0.0f });
			}
		}
	}
}