#include <algorithm>
#include <cstring>
#include <cstddef>
#include "Particle.h"

std::vector<StructProperty> particle::properties = {
	{ "type"   , StructProperty::ParticleType, offsetof(particle, type   ) },
	{ "life"   , StructProperty::Integer     , offsetof(particle, life   ) },
	{ "ctype"  , StructProperty::ParticleType, offsetof(particle, ctype  ) },
	{ "x"      , StructProperty::Float       , offsetof(particle, x      ) },
	{ "y"      , StructProperty::Float       , offsetof(particle, y      ) },
	{ "vx"     , StructProperty::Float       , offsetof(particle, vx     ) },
	{ "vy"     , StructProperty::Float       , offsetof(particle, vy     ) },
	{ "temp"   , StructProperty::Float       , offsetof(particle, temp   ) },
	{ "flags"  , StructProperty::UInteger    , offsetof(particle, flags  ) },
	{ "tmp"    , StructProperty::Integer     , offsetof(particle, tmp    ) },
	{ "tmp2"   , StructProperty::Integer     , offsetof(particle, tmp2   ) },
	{ "dcolour", StructProperty::UInteger    , offsetof(particle, dcolour) },
	{ "dcolor" , StructProperty::UInteger    , offsetof(particle, dcolour) },
	{ "pavg0"  , StructProperty::Float       , offsetof(particle, pavg[0]) },
	{ "pavg1"  , StructProperty::Float       , offsetof(particle, pavg[1]) },
	{ "containsoxy"   , StructProperty::Integer     , offsetof(particle, containsoxy) },
	{ "oxidizer"   , StructProperty::Integer     , offsetof(particle, oxidizer) },
};

std::vector<StructProperty> const &particle::GetProperties()
{
	return properties;
}

StructProperty particle::PropertyByName(const std::string& Name)
{
	auto prop = std::find_if(properties.begin(), properties.end(), [&](StructProperty prop) {
		return prop.Name == Name;
	});
	if (prop == properties.end())
		return properties[0];
	return *prop;
}

int Particle_GetOffset(const char * key, int * format)
{
	int offset;
	if (!strcmp(key, "type"))
	{
		offset = offsetof(particle, type);
		*format = 2;
	}
	else if (!strcmp(key, "life"))
	{
		offset = offsetof(particle, life);
		*format = 0;
	}
	else if (!strcmp(key, "ctype"))
	{
		offset = offsetof(particle, ctype);
		*format = 0;
	}
	else if (!strcmp(key, "temp"))
	{
		offset = offsetof(particle, temp);
		*format = 1;
	}
	else if (!strcmp(key, "tmp"))
	{
		offset = offsetof(particle, tmp);
		*format = 0;
	}
	else if (!strcmp(key, "tmp2"))
	{
		offset = offsetof(particle, tmp2);
		*format = 0;
	}
	else if (!strcmp(key, "vy"))
	{
		offset = offsetof(particle, vy);
		*format = 1;
	}
	else if (!strcmp(key, "vx"))
	{
		offset = offsetof(particle, vx);
		*format = 1;
	}
	else if (!strcmp(key, "x"))
	{
		offset = offsetof(particle, x);
		*format = 1;
	}
	else if (!strcmp(key, "y")) {
		offset = offsetof(particle, y);
		*format = 1;
	}
	else if (!strcmp(key, "dcolour"))
	{
		offset = offsetof(particle, dcolour);
		*format = 3;
	}
	else if (!strcmp(key, "dcolor"))
	{
		offset = offsetof(particle, dcolour);
		*format = 3;
	}
	else if (!strcmp(key, "flags"))
	{
		offset = offsetof(particle, flags);
		*format = 3;
	}
	else if (!strcmp(key, "pavg0"))
	{
		offset = offsetof(particle, pavg[0]);
		*format = 1;
	}
	else if (!strcmp(key, "pavg1"))
	{
		offset = offsetof(particle, pavg[1]);
		*format = 1;
	}
	else
	{
		offset = -1;
	}
	return offset;
}
