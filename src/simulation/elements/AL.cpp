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

int AL_update(UPDATE_FUNC_ARGS)
{
	if (parts[i].life)
	{
		if (sim->air->pv[y/CELL][x/CELL] > 10.0f)
		{
			if (parts[i].temp>9000 && (sim->air->pv[y/CELL][x/CELL] > 30.0f) && RNG::Ref().chance(1, 200))
			{
				part_change_type(i, x, y, PT_EXOT);
				parts[i].life = 1000;
			}
			parts[i].temp += (sim->air->pv[y/CELL][x/CELL])/8;
		}
	}
	return 0;
}

void AL_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_AL";
	elem->Name = "Alpw";
	elem->Colour = COLPACK(0x868686);
	elem->MenuVisible = 1;
	elem->MenuSection = SC_POWDERS;
	elem->Enabled = 1;

	elem->Advection = 0.4f;
	elem->AirDrag = 0.04f * CFDS;
	elem->AirLoss = 0.94f;
	elem->Loss = 0.95f;
	elem->Collision = -0.1f;
	elem->Gravity = 0.18f;
	elem->Diffusion = 0.00f;
	elem->HotAir = 0.000f	* CFDS;
	elem->Falldown = 1;

	elem->Flammable = 0;
	elem->Explosive = 0;
	elem->Meltable = 2;
	elem->Hardness = 2;

	elem->Weight = 90;

	elem->HeatConduct = 121;
	elem->Latent = 0;
	elem->Description = "Aluminium powder. Generally used in thermite.?";

	elem->Properties = TYPE_PART|PROP_CONDUCTS;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = IPH;
	elem->HighPressureTransitionElement = NT;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = 660.3 + 273.15;
	elem->HighTemperatureTransitionElement = PT_LAVA;

	elem->Update = &AL_update;
	elem->Graphics = NULL;
	elem->Init = &AL_init_element;
}
