#include "Hope.h"
#include "BulletFactory.h"
#include "..\..\Service.h"

using namespace shield;
using namespace shield::game;

Hope::Hope(
	const structs::Point& p,
	const structs::Vector3& dir,
	int hp,
	int hpmax,
	int energy,
	int maxEnergy
)
	: Ship(
		p,
		structs::Vector3(0.f, .1f, 0.f),
		Service::getMeshLoader()->load("resources/meshes/hope.fbx"),
		hp,
		hpmax
	),
	_shield( 0l ),
	_shieldLastTick( 0l ),
	_energy( energy ),
	_maxEnergy( maxEnergy ),
	_currentWeapon( 0 )
{
};
void Hope::update( LONGLONG elapsedTime )
{
	Element::update( elapsedTime );
	/*if ( getCurrentTime() - _shieldLastTick > SHIELD_TIMEOUT )
	{
		 _shield = 0;
	}
	if ( _shield == 0 )
	{
		_energy += 1;
	}
	if ( _energy > getMaxEnergy() )
	{
		_energy = getMaxEnergy();
	}*/
};
bool Hope::hit( const Element& e )
{
	return false;
};
bool Hope::_isOutOfBounds(
	const structs::Point& p,
	const structs::Vector3& d
)
{
	float x = p.x + d.dx;
	float z = p.z + d.dz;
	return x < 0.f || x >= 4.f
		|| z < 0.f || z >= 4.f;
};
void Hope::move( const structs::Vector3& direction )
{
	structs::Point p = getPosition();
	if ( _isOutOfBounds(p, direction) )
	{
		return;
	}
	_moveTo( getPosition() + direction );
	std::vector<Mesh*>* mesh = getMesh();
	for ( std::vector<Mesh*>::iterator it = mesh->begin();
		it != mesh->end();
		++it )
	{
		**it += direction;
	}
};
void Hope::dash( const structs::Vector3& direction )
{
	// Change
	move(direction);
};
void Hope::charge( void )
{
	if ( _energy > 0 && _accumulator < LV_MAX_CHARGE )
	{
		--_energy;
		++_accumulator;
	}
};
std::list<Element*> Hope::shoot( void ) const
{
	std::list<Element*> bullets;
	// TODO: Rendu énergie
	if ( _accumulator <= LV_0_CHARGE )
	{
		bullets.push_back(
			BulletFactory::getLaserBeamBulletLv0(getPosition())
		);
	}
	else if ( _accumulator <= LV_1_CHARGE )
	{
		bullets.push_back(
			BulletFactory::getLaserBeamBulletLv1(getPosition())
		);
	}
	else if ( _accumulator <= LV_2_CHARGE )
	{
		bullets.push_back(
			BulletFactory::getLaserBeamBulletLv2(getPosition())
		);
	}
	else // LV_MAX_CHARGE
	{
		bullets.push_back(
			BulletFactory::getLaserBeamBulletLvMax(getPosition())
		);
	}
	return bullets;
};
std::list<Element*> Hope::burst( void ) const
{
	return _weapons[_currentWeapon]->shoot( getPosition() );
};
void Hope::slash()
{
};
void Hope::shield( LONGLONG elapsedTime )
{
	unsigned long long prevTick = _shieldLastTick;
	_shieldLastTick = GetTickCount64();
	if (_shield == 0)
	{
		_shield = _shieldLastTick;
		return;
	}
	_energy -= _shieldLastTick - prevTick;
};
int Hope::getEnergy( void )
{
	return _energy;
};
int Hope::getMaxEnergy( void )
{
	return _maxEnergy;
};
void Hope::addWeapon( Weapon* w )
{
	_weapons.push_back( w );
};
void Hope::setCurrentWeapon( int weapon )
{
	_currentWeapon = weapon;
};
void Hope::update( const HopeAction& action, void* params )
{

};
void Hope::damage( int damage )
{
	if ( _shield > 0 )
	{
		if ( _shield > SHIELD_MIRROR )
		{
			Service::getEventsManager()->notify(
				BULLET_REFLECTED,
				(void*)damage
			);
		}
	}
	else
	{
		Ship::damage( damage );
	}
};
