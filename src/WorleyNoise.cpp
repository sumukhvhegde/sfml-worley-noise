#include "include/WorleyNoise.hpp"

#include <random>
#include <cmath>
#include <limits>

WorleyNoise::WorleyNoise(unsigned int seed) : m_seed(seed), m_gridSize(12) {
	generateFeaturePoints();
}

void WorleyNoise::generateFeaturePoints() {
	m_featurePoints.clear();

	std::mt19937 rng(m_seed);
	std::uniform_real_distribution<float> dist(0.f, 1.f);

	float cellSize = 1.f / static_cast<float>(m_gridSize);

	for (int y = 0; y < m_gridSize; ++y) {
		for (int x = 0; x < m_gridSize; ++x) {
			float fx = (x + dist(rng)) * cellSize;
			float fy = (y + dist(rng)) * cellSize;

			m_featurePoints.emplace_back(fx, fy);
		}
	}
}

float WorleyNoise::sample(float x, float y) const {
	float minDist = std::numeric_limits<float>::max();
	
	for (const auto& point : m_featurePoints) {
		float dx = x - point.x;
		float dy = y - point.y;

		float dist = std::sqrt(dx * dx + dy * dy);

		if (dist < minDist) {
			minDist = dist;
		}
	}

	return minDist;
}