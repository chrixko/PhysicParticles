#pragma once
#include <vector>
#include "entity.h"

class GameScene;

#define PARTICLE_BASE_SPEED 150.0f

#define PARTICLE_TYPE_COUNT 7

enum PARTICLE_TYPE {
	PARTICLE_TYPE_NONE,
	PARTICLE_TYPE_SAND,
	PARTICLE_TYPE_WATER,
	PARTICLE_TYPE_CONCRETE,
	PARTICLE_TYPE_OIL,
	PARTICLE_TYPE_FIRE,
	PARTICLE_TYPE_WOOD
};

class Particle : public Entity {
public:
	Particle(int posX, int posY);
	virtual ~Particle(void);

	std::vector<vector3> Positions;

	Pixel ParticleColor;
	PARTICLE_TYPE ParticleType;
	GameScene* GScene;

	vector3 PreviousPosition;
	vector3 Velocity;
	bool Moved;
	float Mass;
	int Direction;
	float Age;	
	float BurnChance;
	bool Deleted;


	void Init();	
	void Update(float deltaTime);
	virtual void ParticleMove(float deltaTime) {};
	void FixedUpdate(float deltaTime);	
	void Draw(Surface* screen, float deltaTime);
	void Destroy();


	void MoveTo(int posX, int posY);
};