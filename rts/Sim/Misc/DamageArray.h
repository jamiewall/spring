/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef DAMAGE_ARRAY_H
#define DAMAGE_ARRAY_H

#include <algorithm>
#include <vector>
#include "System/creg/creg_cond.h"

class DamageArray
{
	CR_DECLARE(DamageArray)

public:
	DamageArray(float damage = 1.0f);
	DamageArray(const DamageArray& other) { *this = other; }
	virtual ~DamageArray() { }

	DamageArray& operator = (const DamageArray& other);
	DamageArray operator * (float damageMult) const;

	float& operator [] (int i)       { return damages.at(i); }
	float  operator [] (int i) const { return damages.at(i); }

	void SetDefaultDamage(float damage);

	int GetNumTypes() const { return damages.size(); }
	float GetTypeDamage(int typeIndex) const { return damages.at(typeIndex); }
	float GetDefaultDamage() const { return damages.at(0); }

	int paralyzeDamageTime;
	float impulseFactor;
	float impulseBoost;
	float craterMult;
	float craterBoost;

private:
	std::vector<float> damages;
};

class DynDamageArray : public DamageArray
{
	CR_DECLARE(DynDamageArray)

public:
	DynDamageArray(float damage = 1.0f);
	~DynDamageArray() { }
	float dynDamageExp;
	float dynDamageMin;
	float dynDamageRange;
	bool dynDamageInverted;
	float craterAreaOfEffect;
	float damageAreaOfEffect;
	float edgeEffectiveness;
	float explosionSpeed;
	int refCount;
};

#endif
