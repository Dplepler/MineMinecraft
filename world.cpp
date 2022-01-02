#include "world.h"


World::World() { }

void World::push_chunk(Chunk* chunk)
{
	this->chunks.push_back(chunk);


}

void World::load_close_chunk(glm::vec3 position)
{
	unsigned int i = 0;
	size_t size = this->chunks.size();

	for (i = 0; i < size; i++)
	{
		if (this->chunks[i]->collision(position))
		{
			this->chunks[i]->print_chunk();
			break;
		}
	}


}