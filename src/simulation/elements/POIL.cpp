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
//int COAL_graphics(GRAPHICS_FUNC_ARGS);
int POIL_update(UPDATE_FUNC_ARGS)
{

	if (parts[i].temp >= 373.15 - (sim->air->pv[(y) / CELL][(x) / CELL]) && RNG::Ref().chance(1, 1000) || RNG::Ref().chance(1, 100000))
	{
		parts[i].type = PT_GAS;
		parts[i].ctype = PT_POIL;
	}
	else if (parts[i].temp <= (RNG::Ref().between(5, 20)) - 273.15 + (sim->air->pv[(y) / CELL][(x) / CELL]) && RNG::Ref().chance(1, 1000) || RNG::Ref().chance(1, 100000))
	{
		parts[i].type = PT_WAX;
		parts[i].ctype = PT_POIL;
	}




	/*int r, rx, ry;
	for (rx=-1; rx<2; rx++)
		for (ry=-1; ry<2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				if (!r)
					continue;
				if (TYP(r)==PT_SALT && RNG::Ref().chance(1, 50))
				{
					part_change_type(i,x,y,PT_SLTW);
					// on average, convert 3 WATR to SLTW before SALT turns into SLTW
					if (RNG::Ref().chance(1, 3))
						part_change_type(ID(r),x+rx,y+ry,PT_SLTW);
				}
				else if ((TYP(r)==PT_RBDM||TYP(r)==PT_LRBD) && (legacy_enable||parts[i].temp>(273.15f+12.0f)) && RNG::Ref().chance(1, 100))
				{
					part_change_type(i,x,y,PT_FIRE);
					parts[i].life = 4;
					parts[i].ctype = PT_WATR;
				}
				else if (TYP(r)==PT_FIRE && parts[ID(r)].ctype!=PT_WATR)
				{
					sim->part_kill(ID(r));
					if (RNG::Ref().chance(1, 30))
					{
						sim->part_kill(i);
						return 1;
					}
				}
				else if (TYP(r)==PT_SLTW && RNG::Ref().chance(1, 2000))
				{
					part_change_type(i,x,y,PT_SLTW);
				}
				if (TYP(r)==PT_CNCT && RNG::Ref().chance(1, 100))	Concrete+Water to paste, not very popular
				{
					part_change_type(i,x,y,PT_PSTE);
					kill_part(ID(r));
				}
			}*/
	return 0;
}
void POIL_create(ELEMENT_CREATE_FUNC_ARGS)
{
	parts[i].life = RNG::Ref().between(100, 200);
	//parts[i].containsoxy = RNG::Ref().between(1, 2) - 1;
//	if (RNG::Ref().chance(1, 10))
//	{
		//parts[i].containsoxy = RNG::Ref().between(1, 2) - 1;
	//}
}
void POIL_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_POOP";
	elem->Name = "POIL";
	elem->Colour = COLPACK(0x4f5268);
	elem->MenuVisible = 1;
	elem->MenuSection = SC_LIQUID;
	elem->Enabled = 1;

	elem->Advection = 0.6f;
	elem->AirDrag = 0.01f * CFDS;
	elem->AirLoss = 0.98f;
	elem->Loss = 0.95f;
	elem->Collision = 0.0f;
	elem->Gravity = 0.1f;
	elem->Diffusion = 0.00f;
	elem->HotAir = 0.000f	* CFDS;
	elem->Falldown = 2;

	elem->Flammable = 0;
	elem->Explosive = 0;
	elem->Meltable = 0;
	elem->Hardness = 20;

	elem->Weight = (int)(1.2 * 20.0);

	elem->DefaultProperties.temp = R_TEMP - 2.0f + 273.15f;
	elem->HeatConduct = 29;
	elem->Latent = 10000;
	elem->Description = "Crude oil. A fossil fuel, like coal and natural gas. Formed from the remains of ancient marine organisms.";

	elem->Properties = TYPE_LIQUID|PROP_CONDUCTS|PROP_NEUTPASS;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = IPH;
	elem->HighPressureTransitionElement = NT;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = ITH;
	elem->HighTemperatureTransitionElement = NT;

	elem->Update = &POIL_update;
	//elem->Graphics = &COAL_graphics;
	elem->Func_Create = &POIL_create;
	elem->Init = &POIL_init_element;
}
