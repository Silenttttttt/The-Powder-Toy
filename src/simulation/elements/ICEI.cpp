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

int ICE_update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	if (parts[i].ctype == PT_FRZW)//get colder if it is from FRZW
	{
		parts[i].temp = restrict_flt(parts[i].temp-1.0f, MIN_TEMP, 10000);
	}
	for (rx=-1; rx<2; rx++)
		for (ry=-1; ry<2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				if (!r)
					continue;
				if (TYP(r)==PT_SALT || TYP(r)==PT_SLTW)
				{
					if (parts[i].temp > sim->elements[PT_SLTW].LowTemperatureTransitionThreshold && RNG::Ref().chance(1, 200))
					{
						sim->part_change_type(i, x, y, PT_SLTW);
						sim->part_change_type(ID(r), x+rx, y+ry, PT_SLTW);
						return 0;
					}
				}
				else if ((TYP(r)==PT_FRZZ) && RNG::Ref().chance(1, 200))
				{
					sim->part_change_type(ID(r),x+rx,y+ry,PT_ICEI);
					parts[ID(r)].ctype = PT_FRZW;
				}
			}
	return 0;
}

void ICEI_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_ICEI";
	elem->Name = "ICE";
	elem->Colour = COLPACK(0xA0C0FF);
	elem->MenuVisible = 1;
	elem->MenuSection = SC_SOLIDS;
	elem->Enabled = 1;

	elem->Advection = 0.0f;
	elem->AirDrag = 0.00f * CFDS;
	elem->AirLoss = 0.90f;
	elem->Loss = 0.00f;
	elem->Collision = 0.0f;
	elem->Gravity = 0.0f;
	elem->Diffusion = 0.00f;
	elem->HotAir = -0.0003f* CFDS;
	elem->Falldown = 0;

	elem->Flammable = 0;
	elem->Explosive = 0;
	elem->Meltable = 0;
	elem->Hardness = 20;

	elem->Weight = 100;

	elem->DefaultProperties.temp = R_TEMP - 50.0f + 273.15f;
	elem->HeatConduct = 46;
	elem->Latent = 1095;
	elem->Description = "Crushes under pressure. Cools down air.";

	elem->Properties = TYPE_SOLID|PROP_LIFE_DEC|PROP_NEUTPASS;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = 0.8f;
	elem->HighPressureTransitionElement = PT_SNOW;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = 252.05f;
	elem->HighTemperatureTransitionElement = ST;

	elem->DefaultProperties.ctype = PT_WATR;

	elem->Update = &ICE_update;
	elem->Graphics = NULL;
	elem->Init = &ICEI_init_element;
}
