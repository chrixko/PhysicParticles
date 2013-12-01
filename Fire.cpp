#include "Helper.h"
#include "GameScene.h"
#include "Smoke.h"

#include "Fire.h"

Fire::Fire(int posX, int posY) : Particle(posX, posY) {
	ParticleColor = 0xFF0000;
	ParticleType = PARTICLE_TYPE_FIRE;
	Burning = false;
}


Fire::~Fire(void)
{
}

void Fire::ParticleMove(float deltaTime) {
	if(!Burning) {	
		Velocity.y = (PARTICLE_BASE_SPEED / Mass) * deltaTime;

		vector3 pos = Position + Velocity;

		for(int i = 0; i< pos.y - Position.y; i++) {
			if(!GScene->SpotIsFree(pos.x, Position.y + i, this)) {
				pos.y = Position.y + i;
				break;
			}
		}

		Particle* under = GScene->GetParticle(pos.x, pos.y);

		if(under != 0 && under->BurnChance > 0) {
			Burning = true;
			GScene->RemoveEntity(GScene->GetParticle(pos.x, pos.y));
			Position = pos;
		} else if (under != 0 && !under->BurnChance > 0 && under->ParticleType != PARTICLE_TYPE_FIRE) {
			Burning = true;
		} else if(GScene->SpotIsFree(pos.x, pos.y, this)) {
			Position = pos;
		}
	}

	if(Burning) {
		Particle* left = GScene->GetParticle(Position.x - 1, Position.y);
		Particle* right = GScene->GetParticle(Position.x + 1, Position.y);
		Particle* upLeft = GScene->GetParticle(Position.x - 1, Position.y - 1);
		Particle* bottomLeft = GScene->GetParticle(Position.x - 1, Position.y + 1);
		Particle* upRight = GScene->GetParticle(Position.x + 1, Position.y - 1);
		Particle* bottomRight= GScene->GetParticle(Position.x + 1, Position.y + 1);
			
		SetOnFire(left);
		SetOnFire(right);
		SetOnFire(upLeft);
		SetOnFire(bottomLeft);
		SetOnFire(upRight);
		SetOnFire(bottomRight);
	}

	if(Age >= 0.4f) {
		Scene->RemoveEntity(this);
		//Smoke* s = new Smoke(Position.x, Position.y);
		//GScene->AddEntity(s);
		GScene->Particles[(int)Position.x][(int)Position.y] = 0;
	}
}

void Fire::SetOnFire(Particle* p) {
	if(p != 0 && p->BurnChance > 0 && Helper::GetRandomInt(0, 100) < p->BurnChance) {
		GScene->RemoveEntity(p);
		Fire* f = new Fire(p->Position.x, p->Position.y);
		f->Burning = true;
		GScene->AddEntity(f);
		GScene->Particles[(int)Position.x][(int)Position.y] = f;
	}
}