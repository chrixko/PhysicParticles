#pragma once
#include "particle.h"
class Smoke : public Particle {
public:
	Smoke(int posX, int posY);
	~Smoke(void);

	void ParticleMove(float deltaTime);
};

