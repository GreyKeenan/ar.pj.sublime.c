#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <stdbool.h>

struct Game_Object;

typedef bool(*Game_Object_methodOnPush)(struct Game_Object*, void *, char, char); //temp void* until better plan
typedef void(*Game_Object_methodOnExit)(struct Game_Object*);

typedef struct Game_Object {
	const void* texture;
	bool collides;
	bool isEntity;

	Game_Object_methodOnPush onPush;
	Game_Object_methodOnExit onExit;

} Game_Object;

typedef struct {
	Game_Object gameObject;
	Game_Object *foundation;
	unsigned char x;
	unsigned char y;

} Game_Entity;

Game_Object Game_Object_initialize(const void* texture, const bool collides, Game_Object_methodOnPush onPush, Game_Object_methodOnExit onExit);

Game_Entity Game_Entity_initialize(const void* texture, const bool collides, Game_Object_methodOnPush onPush, Game_Object_methodOnExit onExit, Game_Object *foundation, const unsigned char x, const unsigned char y);


#endif
