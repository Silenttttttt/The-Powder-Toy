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


int THRM_update(UPDATE_FUNC_ARGS)
{
	//if (parts[i].type == PT_LAVA)
	//{
	//	parts[i].tmp2--;
	//}

	int blockpress = 0;
	for (int nx = -2; nx <= 2; nx++)
	{
		for (int ny = -2; ny <= 2; ny++)
		{
			if ((!nx != !ny) && x + nx >= 0 && y + ny >= 0 && x + nx < XRES && y + ny < YRES)
			{
				if (TYP(pmap[y + ny][x + nx]) == PT_THRM)
					blockpress++;
			}
		}
	}
	if (blockpress >= 6)
	{
		sim->air->bmap_blockair[y / CELL][x / CELL] = 1;
		sim->air->bmap_blockairh[y / CELL][x / CELL] = 0x8;
	}


	//float limit = parts[i].temp / 50;
	//if (sim->air->pv[y / CELL][x / CELL] < limit)
	//	sim->air->pv[y / CELL][x / CELL] += 0.001f * (limit - sim->air->pv[y / CELL][x / CELL]);
	//if (sim->air->pv[y / CELL + 1][x / CELL] < limit)
	//	sim->air->pv[y / CELL + 1][x / CELL] += 0.001f * (limit - sim->air->pv[y / CELL + 1][x / CELL]);
	//if (sim->air->pv[y / CELL - 1][x / CELL] < limit)
	//	sim->air->pv[y / CELL - 1][x / CELL] += 0.001f * (limit - sim->air->pv[y / CELL - 1][x / CELL]);

	//sim->air->pv[y / CELL][x / CELL + 1] += 0.001f * (limit - sim->air->pv[y / CELL][x / CELL + 1]);
	//sim->air->pv[y / CELL + 1][x / CELL + 1] += 0.001f * (limit - sim->air->pv[y / CELL + 1][x / CELL + 1]);
	//sim->air->pv[y / CELL][x / CELL - 1] += 0.001f * (limit - sim->air->pv[y / CELL][x / CELL - 1]);
	//sim->air->pv[y / CELL - 1][x / CELL - 1] += 0.001f * (limit - sim->air->pv[y / CELL - 1][x / CELL - 1]);
	//parts[i].temp -= 0.001f * (limit - sim->air->pv[y / CELL - 1][x / CELL - 1]);










	int temp = 0;
	for (int rx = -2; rx <= 2; rx++)
		for (int ry = -2; ry <= 2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				int r = pmap[y + ry][x + rx];
				if (!r)
					continue;
			

			
				int rt = TYP(r);
				if (RNG::Ref().chance(1, 5) && (parts[i].tmp2 > 0 && parts[i].containsoxy > 0) && (parts[i].temp > 2204 + 273 - (sim->air->pv[(y) / CELL][(x) / CELL]) || rt == PT_FIRE || rt == PT_PLSM || rt == PT_EMBR || rt == PT_SPRK || (rt == PT_LAVA && parts[ID(r)].temp >= 1204 + 273)))
				{

				
				
						sim->air->pv[(y) / CELL][(x) / CELL] += 0.025f;
						parts[i].temp += 50 * (parts[i].containsoxy / 2);
						if (RNG::Ref().chance(1, 10))
						{
							parts[i].tmp2 -= 1 * parts[i].containsoxy;
						}
					
				}

				else if (RNG::Ref().chance(1, 5) && parts[i].tmp2 > 0 && parts[i].containsoxy <= 0 && (parts[i].temp > 2204 + 273 - (sim->air->pv[(y) / CELL][(x) / CELL]) || rt == PT_FIRE || rt == PT_SPRK || rt == PT_PLSM || rt == PT_EMBR))
				{

					//parts[i].tmp2--;
					parts[i].temp += 100;
					sim->air->pv[(y) / CELL][(x) / CELL] += 0.025f;

						parts[i].tmp2--;
					
				}




			}
	if (parts[i].tmp2 <= 0)
	{
		
		
		if (RNG::Ref().chance(2, 3))
			{
			parts[i].temp += 500;
			parts[i].ctype = PT_NONE;
			//parts[i].tmp2 = RNG::Ref().between(30, 50);
			sim->part_change_type(i, x, y, PT_ALO3);
		}
		else
		{
			parts[i].temp += 500;
			parts[i].ctype = PT_NONE;
		//	parts[i].tmp2 = RNG::Ref().between(30, 50);
			sim->part_change_type(i, x, y, PT_BMTL);
		}
	
		
		//temptmp2;

	}
	if (parts[i].tmp2 <= 50)
	{
		float angle, magnitude;
		int tempelem = 0;
		int n, np, randemb;
		randemb = RNG::Ref().between(5, 20);
		for (n = 0; n < randemb; n++)
		{
			np = sim->part_create(-3, x, y, PT_EMBR);
			if (np > -1)
			{
				magnitude = RNG::Ref().between(40, 99) * 0.05f;
				angle = RNG::Ref().between(0, 6283) * 0.001f; //(in radians, between 0 and 2*pi)
				parts[np].vx = parts[i].vx * 0.5f + cosf(angle) * magnitude;
				parts[np].vy = parts[i].vy * 0.5f + sinf(angle) * magnitude;
				parts[np].tmp = 1;
				parts[np].tmp2 = RNG::Ref().between(70, 109);
				parts[np].temp = RNG::Ref().between(3300, 4300);
				sim->air->pv[(y) / CELL][(x) / CELL] += 0.005f;
			}
		}
		sim->air->pv[(y) / CELL][(x) / CELL] += 0.025f; 


		parts[i].temp += parts[i].tmp2;
		if (RNG::Ref().chance(2, 6))
		{
			parts[i].tmp2--;
		}

	}
	return 0;



}



int THRM_graphics(GRAPHICS_FUNC_ARGS)
{
	
	if (cpart->tmp2 <= 50)
	{
		*firea = 255;
		*firer = 255;
		*fireg = *colg;
		*fireb = 255;
		*pixel_mode |= FIRE_ADD;
	}
	else if ( cpart->temp >= 700)
	{

		*firea = 20;
		*firer = *colr;
		*fireg = *colg;
		*fireb = *colb;
		*pixel_mode |= FIRE_ADD;
	}
	else if (cpart->temp < 700)
	{
		*firea = 0;
		
	}
	else if (cpart->tmp2 > 50)
	{
		*firea = 0;
		
	}
	//Returning 0 means dynamic, do not cache
	return 0;
}

void THRM_create(ELEMENT_CREATE_FUNC_ARGS)
{
	parts[i].tmp2 = RNG::Ref().between(80, 120);
	parts[i].containsoxy = RNG::Ref().between(2, 3) - 1;
	//if (RNG::Ref().chance(1, 10))
	//{
		//parts[i].containsoxy = RNG::Ref().between(1, 2) - 1;
	//}
}



void THRM_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_THRM";
	elem->Name = "THRM";
	elem->Colour = COLPACK(0x88300b);
	elem->MenuVisible = 1;
	elem->MenuSection = SC_EXPLOSIVE;
	elem->Enabled = 1;

	elem->Advection = 0.4f;
	elem->AirDrag = 0.02f * CFDS;
	elem->AirLoss = 0.98f;
	elem->Loss = 0.98f;
	elem->Collision = -0.1f;
	elem->Gravity = 0.7f;
	elem->Diffusion = 0.00f;
	elem->HotAir = 0.000f	* CFDS;
	elem->Falldown = 1;

	elem->Flammable = 0;
	elem->Explosive = 0;
	elem->Meltable = 0;
	elem->Hardness = 2;

	elem->Weight = (int)(0.7 * 20.0);

	elem->HeatConduct = 101;
	elem->Latent = 0;
	elem->Description = "Thermite. Burns at extremely high temperature.";

	elem->Properties = TYPE_PART | PROP_CONDUCTS | PROP_HOT_GLOW;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = IPH;
	elem->HighPressureTransitionElement = NT;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = 660 + 273.15 + RNG::Ref().between(100, 400);
	elem->HighTemperatureTransitionElement = PT_LAVA;


	elem->Func_Create = &THRM_create;
	elem->Update = &THRM_update;
	elem->Graphics = &THRM_graphics;
	elem->Init = &THRM_init_element;
}
