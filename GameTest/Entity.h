#pragma once
#ifndef __ENTITY_H__
#define __ENTITY_H__
#include <cstdint>

typedef uint32_t Entity;
static constexpr Entity INVALID_ENTITY = 0;

/* Creates a Uint32_t that will be the player's ID. */
Entity inline CreateEntity()
{
	static Entity next = 0;
	return ++next;
}

#endif //!__ENTITY_H__