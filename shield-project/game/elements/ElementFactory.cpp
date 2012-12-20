#include "ElementFactory.h"

#include "Angel.h"
#include "Archangel.h"
#include "Ruler.h"
#include "Authority.h"
#include "Virtue.h"
#include "Dominion.h"
#include "Throne.h"
#include "Cherub.h"
#include "Seraph.h"

using namespace shield;
using namespace shield::game;

Element* ElementFactory::getAngel(
	const structs::Point& p,
	const structs::Vector3& dir,
	int hp,
	int maxHp
)
{
	return new Angel( p, dir, hp, maxHp );
};
Element* ElementFactory::getArchangel(
	const structs::Point& p,
	const structs::Vector3& dir,
	int hp,
	int maxHp
)
{
	return 0;
	//return new Archangel();
};
Element* ElementFactory::getRuler(
	const structs::Point& p,
	const structs::Vector3& dir,
	int hp,
	int maxHp
)
{
	return 0;
	//return new Ruler();
};
Element* ElementFactory::getAuthority(
	const structs::Point& p,
	const structs::Vector3& dir,
	int hp,
	int maxHp
)
{
	return 0;
	//return new Authority();
};
Element* ElementFactory::getVirtue(
	const structs::Point& p,
	const structs::Vector3& dir,
	int hp,
	int maxHp
)
{
	return 0;
	//return new Virtue();
};
Element* ElementFactory::getDominion(
	const structs::Point& p,
	const structs::Vector3& dir,
	int hp,
	int maxHp
)
{
	return 0;
	//return new Dominion();
};
Element* ElementFactory::getThrone(
	const structs::Point& p,
	const structs::Vector3& dir,
	int hp,
	int maxHp
)
{
	return 0;
	//return new Throne();
};
Element* ElementFactory::getCherub(
	const structs::Point& p,
	const structs::Vector3& dir,
	int hp,
	int maxHp
)
{
	return 0;
	//return new Cherub();
};
Element* ElementFactory::getSeraph(
	const structs::Point& p,
	const structs::Vector3& dir,
	int hp,
	int maxHp
)
{
	return 0;
	//return new Seraph();
};
