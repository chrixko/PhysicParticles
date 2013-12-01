#include "Input.h"
#include "Sand.h"
#include "Water.h"
#include "Concrete.h"
#include "Oil.h"
#include "Fire.h"
#include "Wood.h"

#include "GameScene.h"

#define BRUSH_SIZE 2

GameScene::GameScene(void) : Scene() {
	Entities.reserve(SCRWIDTH * SCRHEIGHT);	
	for(int x = 0; x < SCRWIDTH; x++) {
		for(int y = 0; y < SCRHEIGHT; y++) {
			Particles[x][y] = 0;
		}
	}
}


GameScene::~GameScene(void) {

}

void GameScene::Init() {
	Scene::Init();

	Selector = new ParticleSelector(10, 10);
	AddEntity(Selector);

	for(int x = 0; x < SCRWIDTH; x++) {
		AddEntity(new Concrete(x, 0));
		AddEntity(new Concrete(x, SCRHEIGHT - 1));		
	}

	for(int y = 0; y < SCRHEIGHT; y++) {
		AddEntity(new Concrete(0, y));
		AddEntity(new Concrete(SCRWIDTH - 1, y));		
	}
}

void GameScene::Update(float deltaTime) {
	Scene::Update(deltaTime);

	if(Input::IsMouseDown(MOUSE_LEFT)) {
		for(int x = -BRUSH_SIZE; x < BRUSH_SIZE; x++) {
			for(int y = -BRUSH_SIZE; y < BRUSH_SIZE; y++) {
				if(Particles[Input::State->MouseX + x][Input::State->MouseY + y] == 0) {

					int posX = Input::State->MouseX + x;
					int posY = Input::State->MouseY + y;

					if(Selector->CurrentType == PARTICLE_TYPE_SAND) {
						AddEntity(new Sand(posX, posY));
					} else if(Selector->CurrentType == PARTICLE_TYPE_WATER) {
						AddEntity(new Water(posX, posY));
					} else if(Selector->CurrentType == PARTICLE_TYPE_CONCRETE) {
						AddEntity(new Concrete(posX, posY));
					} else if(Selector->CurrentType == PARTICLE_TYPE_OIL) {
						AddEntity(new Oil(posX, posY));
					} else if(Selector->CurrentType == PARTICLE_TYPE_FIRE) {
						AddEntity(new Fire(posX, posY));
					} else if(Selector->CurrentType == PARTICLE_TYPE_WOOD) {
						AddEntity(new Wood(posX, posY));
					}
				}
				
			}
		}
	}

	if(Input::IsMouseDown(MOUSE_RIGHT)) {
		for(int x = -BRUSH_SIZE * 2; x < BRUSH_SIZE * 2; x++) {
			for(int y = -BRUSH_SIZE * 2; y < BRUSH_SIZE * 2; y++) {
				int posX = Input::State->MouseX + x;
				int posY = Input::State->MouseY + y;

				if(Particles[posX][posY] != 0) {
					RemoveEntity(Particles[posX][posY]);
					Particles[posX][posY] = 0;
				}
			}
		}
	}
}

void GameScene::FixedUpdate(float deltaTime) {
	Scene::FixedUpdate(deltaTime);
}

void GameScene::Draw(Surface* screen, float deltaTime) {	
	std::string entityCount = "Entities: ";
	entityCount += std::to_string(Entities.size());

	screen->Print(&entityCount[0], SCRWIDTH - 200, 10, 0xFF0000);

	Scene::Draw(screen, deltaTime);
}

bool GameScene::SpotIsFree(int posX, int posY, Particle* askingParticle) {
	return Particles[posX][posY] == 0 || Particles[posX][posY] == askingParticle;
}

PARTICLE_TYPE GameScene::GetParticleType(int posX, int posY) {
	if(SpotIsFree(posX, posY, 0)) {
		return PARTICLE_TYPE_NONE;
	}

	return Particles[posX][posY]->ParticleType;
}

Particle* GameScene::GetParticle(int posX, int posY) {
	return Particles[posX][posY];
}

bool GameScene::HasNeighbourOfType(Particle* particle, PARTICLE_TYPE type) {
	if(GetParticleType(particle->Position.x - 1, particle->Position.y) == type) {
		return true;
	}

	if(GetParticleType(particle->Position.x + 1, particle->Position.y) == type) {
		return true;
	}

	if(GetParticleType(particle->Position.x, particle->Position.y + 1) == type) {
		return true;
	}

	if(GetParticleType(particle->Position.x, particle->Position.y - 1) == type) {
		return true;
	}

	if(GetParticleType(particle->Position.x - 1, particle->Position.y - 1) == type) {
		return true;
	}

	if(GetParticleType(particle->Position.x + 1, particle->Position.y - 1) == type) {
		return true;
	}

	if(GetParticleType(particle->Position.x + 1, particle->Position.y + 1) == type) {
		return true;
	}

	if(GetParticleType(particle->Position.x - 1 , particle->Position.y + 1) == type) {
		return true;
	}

	return false;
}