#include "Particle.h"
#include "Helper.h"
#include "GameScene.h"

Particle::Particle(int posX, int posY) : Entity() {
	Position.x = posX;
	Position.y = posY;
	SizeX = SizeY = 1;

	Type = "particle";
	Moved = true;
	Mass = 1.0f;
	ParticleColor = 0xFFFFFF;
	Direction = 0;
	Age = 0;
	BurnChance = 0.0f;
	Deleted = false;
}

Particle::~Particle(void) {
}

void Particle::Init() {
	GScene = (GameScene*)Scene;
}

void Particle::Update(float deltaTime) {
	PreviousPosition = Position;

	Age += deltaTime;

	GScene->Particles[(int)Position.x][(int)Position.y] = 0;

	ParticleMove(deltaTime);

	if(!Deleted) {
		GScene->Particles[(int)Position.x][(int)Position.y] = this;
	}	
}

void Particle::FixedUpdate(float deltaTime) {	

}

void Particle::Draw(Surface* screen, float deltaTime) {
	screen->Plot(Position.x, Position.y, ParticleColor);	
}

void Particle::MoveTo(int posX, int posY) {
	if(GScene->SpotIsFree(posX, posY, this)) {
		GScene->Particles[(int)Position.x][(int)Position.y] = 0;

		Position.x = posX;
		Position.y = posY;

		GScene->Particles[(int)Position.x][(int)Position.y] = this;
	}	
}

void Particle::Destroy() {
	Deleted = true;
}