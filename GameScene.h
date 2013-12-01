#pragma once
#include <map>
#include "Particle.h"
#include "ParticleSelector.h"
#include "scene.h"

class GameScene : public Scene {
public:
	GameScene(void);
	~GameScene(void);

	ParticleSelector* Selector;
	Particle* Particles[SCRWIDTH][SCRHEIGHT];

	void Init();
	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Draw(Surface* screen, float deltaTime);

	bool SpotIsFree(int posX, int posY, Particle* askingParticle);
	PARTICLE_TYPE GetParticleType(int posX, int posY);
	Particle* GetParticle(int posX, int posY);
	bool HasNeighbourOfType(Particle* particle, PARTICLE_TYPE type);

};