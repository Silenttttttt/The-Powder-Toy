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

int BMTL_update(UPDATE_FUNC_ARGS)
{





	int r, rx, ry;
	if (parts[i].temp > 323.15f)//250.0f+273.15f
	{
		
		for (rx = -1; rx < 2; rx++)
			for (ry = -1; ry < 2; ry++)
				if (BOUNDS_CHECK && (rx || ry))
				{
					r = pmap[y + ry][x + rx];
					if (!r)
						continue;


					int rt = TYP(r);












					/*if (rt != parts[i].type && abs(parts[i].vx) > 10)
					{
						sim->air->pv[(y) / CELL][(x) / CELL] += abs(parts[i].vx) / 2;
						parts[i].vx /= 2.5;
					}
					if (rt != parts[i].type && abs(parts[i].vy) > 10)
					{
						sim->air->pv[(y) / CELL][(x) / CELL] += abs(parts[i].vy) / 2;
						parts[i].vy /= 2.5;
					}*/



















					if (TYP(r) == PT_AL && RNG::Ref().chance(1, 1000))
					{
						if (RNG::Ref().chance(1, 2))
						{
							sim->part_create(ID(r), x + rx, y + ry, PT_THRM);
						}
						else
							sim->part_create(i, x, y, PT_THRM);
						//part_change_type(ID(r),x+rx,y+ry,PT_BMTL);
						//parts[ID(r)].tmp = (parts[i].tmp<=7) ? parts[i].tmp = 1 : parts[i].tmp - RNG::Ref().between(0, 4);
					}
				}







		
	}

	
	return 0;
}

void BMTL_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_BMTL"; 
	elem->Name = "Fepw";
	elem->Colour = COLPACK(0xa19d94);
	elem->MenuVisible = 1;
	elem->MenuSection = SC_POWDERS;
	elem->Enabled = 1;

	elem->Advection = 0.4f;
	elem->AirDrag = 0.04f * CFDS;
	elem->AirLoss = 0.94f;
	elem->Loss = 0.95f;
	elem->Collision = -0.1f;
	elem->Gravity = 0.4f;
	elem->Diffusion = 0.00f;
	elem->HotAir = 0.000f * CFDS;
	elem->Falldown = 1;

	elem->Flammable = 0;
	elem->Explosive = 0;
	elem->Meltable = 0;
	elem->Hardness = 1;

	elem->Weight = (int)(7.87 * 20);

	elem->HeatConduct = 230;
	elem->Latent = 0;
	elem->Description = "Iron metal powder.";

	elem->Properties = TYPE_PART|PROP_CONDUCTS|PROP_HOT_GLOW;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = IPH;
	elem->HighPressureTransitionElement = NT;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = 1538 + 273;
	elem->HighTemperatureTransitionElement = PT_LAVA;

	elem->Update = &BMTL_update;
	elem->Graphics = NULL;
	elem->Init = &BMTL_init_element;
}
