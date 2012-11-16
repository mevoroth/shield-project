#include "Hope.h"
#include "BulletFactory.h"

using namespace shield;

game::Hope::Hope( const structs::Point& p, int damage )
	: Ship( p, damage ),
	_shield( 0l ),
	_shieldLastTick( 0l ),
	_energy( DEFAULT_ENERGY ),
	_maxEnergy( DEFAULT_MAX_ENERGY ),
	_currentWeapon( 0 )
{
};
void game::Hope::refresh( void )
{
	//game::Element::refresh();
	if ( getCurrentTime() - _shieldLastTick > SHIELD_TIMEOUT )
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
	}
};
bool game::Hope::hit( const Element& e ) const
{
	return false;
};
void game::Hope::move( const structs::Vector3& direction )
{
};
void game::Hope::dash( const structs::Vector3& direction )
{
};
void game::Hope::charge()
{
	if ( _energy > 0 && _accumulator < LV_MAX_CHARGE )
	{
		--_energy;
		++_accumulator;
	}
};
std::list<game::Element*>& game::Hope::shoot( void ) const
{
	std::list<game::Element*> bullets;
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
std::list<game::Element*>& game::Hope::burst( void ) const
{
	return _weapons[_currentWeapon].shoot( getPosition() );
};
void game::Hope::slash()
{
};
void game::Hope::shield()
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
int game::Hope::getEnergy()
{
	return _energy;
};
int game::Hope::getMaxEnergy()
{
	return _maxEnergy;
};
