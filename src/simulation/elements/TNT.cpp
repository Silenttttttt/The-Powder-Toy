/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "simulation/ElementsCommon.h"
#include "simulation/StructProperty.h"


int COAL_graphics(GRAPHICS_FUNC_ARGS);



int TNT_update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	if(parts[i].tmp == 0)
	{
		if(parts[i].temp>=673.0f)
			parts[i].tmp = 1;
		else
			for (rx=-1; rx<2; rx++)
				for (ry=-1; ry<2; ry++)
					if (BOUNDS_CHECK && (rx || ry))
					{
						r = pmap[y+ry][x+rx];
						if (!r)
							continue;
						if (TYP(r)==PT_FIRE || TYP(r)==PT_PLSM || TYP(r)==PT_SPRK || TYP(r)==PT_LIGH)
						{
							parts[i].tmp = 1;
						}
					}
	
	}
	else if(parts[i].tmp == 1)
	{
		if (ID(pmap[y][x]) == (unsigned)i)
		{
			sim->FloodProp(x, y, particle::PropertyByName("tmp"), { 2 });
		}
		parts[i].tmp = 2;
	}
	else if(parts[i].tmp == 2)
	{
		parts[i].tmp = 3;
	}
	else
	{
		float otemp = parts[i].temp-273.15f;
		//Explode!!
		sim->air->pv[y/CELL][x/CELL] += 10.0f;
		parts[i].tmp = 0;
		if(RNG::Ref().chance(1, 3))
		{
			if(RNG::Ref().chance(1, 2))
			{
				sim->part_create(i, x, y, PT_FIRE);
			}
			else
			{
				sim->part_create(i, x, y, PT_CO2);
				parts[i].life = RNG::Ref().between(500, 549);
			}
			parts[i].temp = restrict_flt((10000 /4)+otemp, MIN_TEMP, 10000);
		}
		else
		{
			if(RNG::Ref().chance(1, 15))
			{
				sim->part_create(i, x, y, PT_EMBR);
				parts[i].temp = restrict_flt((10000 /3)+otemp, MIN_TEMP, 10000);
				parts[i].vx = RNG::Ref().between(-10, 10);
				parts[i].vy = RNG::Ref().between(-10, 10);
			}
			else
			{
				sim->part_kill(i);
			}
		}
		return 1;
	}
	return 0;
}

void TNT_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_TNT";
	elem->Name = "TNT";
	elem->Colour = COLPACK(0xFFFF99);
	elem->MenuVisible = 1;
	elem->MenuSection = SC_EXPLOSIVE;
	elem->Enabled = 1;
	 
	elem->Advection = 0.4f;
	elem->AirDrag = 0.04f * CFDS;
	elem->AirLoss = 0.94f;
	elem->Loss = 0.95f;
	elem->Collision = -0.1f;
	elem->Gravity = 0.3f;
	elem->Diffusion = 0.00f;
	elem->HotAir = 0.000f * CFDS;
	elem->Falldown = 1;

	elem->Flammable = 0;
	elem->Explosive = 0;
	elem->Meltable = 0;
	elem->Hardness = 1;

	elem->Weight = (int)(1.65 * 20.0);

	elem->HeatConduct = 88;
	elem->Latent = 0;
	elem->Description = "Trinitrotoluene. Commonly used explosives for military, mining and other applications.";

	elem->Properties = TYPE_PART | PROP_NEUTPENETRATE | PROP_HOT_GLOW;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = IPH;
	elem->HighPressureTransitionElement = NT;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = ITH;
	elem->HighTemperatureTransitionElement = NT;

	elem->Update = &TNT_update;
	elem->Graphics = &COAL_graphics;
	elem->Init = &TNT_init_element;
}
