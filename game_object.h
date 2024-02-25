#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <stdbool.h>


typedef struct {
	const void* texture;
	bool collides;
	bool isEntity;

	bool (*onPush)(const char directionX, const char directionY);
	void (*onExit)();

} Game_Object;

typedef struct {
	Game_Object gameObject;
	Game_Object *foundation;
	unsigned char x;
	unsigned char y;

} Game_Entity;

Game_Object Game_Object_initialize(const void* texture, const bool collides);

Game_Entity Game_Entity_initialize(const void* texture, const bool collides, Game_Object *foundation, const unsigned char x, const unsigned char y);



#endif
