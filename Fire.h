#pragma once
#include "particle.h"
class Fire : public Particle {
public:
	Fire(int posX, int posY);
	~Fire(void);

	bool Burning;

	void ParticleMove(float deltaTime);
	void SetOnFire(Particle* p);
};