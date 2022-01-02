#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include "blocks.h"


class World
{

public:
	
	// C'Tor
	World();
	void push_chunk(Chunk* chunk);
	void load_close_chunk(glm::vec3 position);



	std::vector<Chunk*> chunks;
	




};










#endif