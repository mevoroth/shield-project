#include "Enemy.h"

using namespace shield;
using namespace shield::game;

Enemy::Enemy(
	const structs::Point& p,
	const structs::Vector3& dir,
	const std::vector<Mesh*>& meshes
)
	: Element( p, dir, meshes )
{
};
