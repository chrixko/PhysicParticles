#include "surface.h"
#include "template.h"
#include "Helper.h"
#include "game.h"
#include "Scene.h"
#include "Entity.h"

Entity::Entity(void) {
	Inited = false;
	Scene = 0;
	Graphic = 0;
	CurrentAnimation = 0;
	
	SizeX = 26;
	SizeY = 26;

	Hidden = false;
	ZOrder = 0;

	Type = "";
	DrawHitbox = false;
}

Entity::~Entity(void) {	
}

void Entity::Draw(Surface* surface, float deltaTime) {
	if(CurrentAnimation != 0) {
		CurrentAnimation->Update(deltaTime);
		Graphic = CurrentAnimation->GetCurrentSurface();
	}

	if(!Hidden && Graphic != 0) {
		if(Scene != 0) {
			Graphic->AlphaCopyTo(surface, (Position.x + DrawOffset.x) - Scene->Camera.x, (Position.y + DrawOffset.y) - Scene->Camera.y);
		} else {
			Graphic->AlphaCopyTo(surface, (Position.x + DrawOffset.x), (Position.y + DrawOffset.y));
		}
		
	}

	if(DrawHitbox && strcmp(Type, "") != 0) {
		SDL_Rect box = GetHitbox();
		int posX = box.x - Scene->Camera.x;
		int posY = box.y - Scene->Camera.y;
		surface->Box(posX, posY, posX + box.w, posY + box.h, 0xFF0000);
	}
}

Entity* Entity::CollidesWith(char* type) {
	return Scene->Colliding(this, type);	
}

Entity* Entity::CollidesWith(char* type, int nextX, int nextY) {
	return Scene->Colliding(this, type, nextX, nextY);	
}

SDL_Rect Entity::GetHitbox() {
	SDL_Rect hitbox;

	hitbox.x = Position.x + Offset.x;
	hitbox.y = Position.y + Offset.y;
	hitbox.w = SizeX;
	hitbox.h = SizeY;

	return hitbox;
}

bool Entity::CompareByZOrder(const Entity* a, const Entity* b) {
	return a->ZOrder < b->ZOrder;
}