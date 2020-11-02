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


int COAL_graphics(GRAPHICS_FUNC_ARGS);



int BRMT_update(UPDATE_FUNC_ARGS)
{














	if (abs(parts[i].vx) > 10)
	{
		sim->air->pv[y / CELL][x / CELL] += abs(parts[i].vx) / 2;
	//	if (parts[i].vx > 0)
	//	{
			parts[i].vx /= 2.5;
		//}
	//	else 
	//	{

		//}

	}
	if (abs(parts[i].vy) > 10)
	{
		sim->air->pv[y / CELL][x / CELL] += abs(parts[i].vy) / 2;


		parts[i].vy /= 2.5;
	}








	int r, rx, ry;
	if (parts[i].temp > 523.15f)//250.0f+273.15f
	{
		int tempFactor = 1000 - (int)((523.15f-parts[i].temp)*2);
		if(tempFactor < 2)
			tempFactor = 2;
		for (rx=-1; rx<2; rx++)
			for (ry=-1; ry<2; ry++)
				if (BOUNDS_CHECK && (rx || ry))
				{
					r = pmap[y+ry][x+rx];
					if (!r)
						continue;


					int rt = TYP(r);












					if (rt != parts[i].type && abs(parts[i].vx) > 10)
					{
						sim->air->pv[(y) / CELL][(x) / CELL] += abs(parts[i].vx) / 2;
						parts[i].vx /= 2.5;
					}
					if (rt != parts[i].type && abs(parts[i].vy) > 10)
					{
						sim->air->pv[(y) / CELL][(x) / CELL] += abs(parts[i].vy) / 2;
						parts[i].vy /= 2.5;
					}



















					if (TYP(r) == PT_BREL && RNG::Ref().chance(1, tempFactor))
					{
						if(RNG::Ref().chance(1, 2))
						{
							sim->part_create(ID(r), x+rx, y+ry, PT_THRM);
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

void BRMT_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_BRMT";
	elem->Name = "BRMT";
	elem->Colour = COLPACK(0xa19d94);
	elem->MenuVisible = 1;
	elem->MenuSection = SC_POWDERS;
	elem->Enabled = 1;

	elem->Advection = 0.4f;
	elem->AirDrag = 0.04f * CFDS;
	elem->AirLoss = 0.94f;
	elem->Loss = 0.95f;
	elem->Collision = -0.1f;
	elem->Gravity = 0.3f;
	elem->Diffusion = 0.00f;
	elem->HotAir = 0.000f	* CFDS;
	elem->Falldown = 1;

	elem->Flammable = 0;
	elem->Explosive = 0;
	elem->Meltable = 2;
	elem->Hardness = 2;

	elem->Weight = (int)(5 * 20.0);

	elem->HeatConduct = 211;
	elem->Latent = 0;
	elem->Description = "Broken metal.";

	elem->Properties = TYPE_PART|PROP_CONDUCTS|PROP_LIFE_DEC|PROP_HOT_GLOW;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = IPH;
	elem->HighPressureTransitionElement = NT;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = 1273.0f;
	elem->HighTemperatureTransitionElement = ST;

	elem->Update = &BRMT_update;
	elem->Graphics = &COAL_graphics;
	elem->Init = &BRMT_init_element;
}
