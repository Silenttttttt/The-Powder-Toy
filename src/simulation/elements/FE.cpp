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

int FE_update(UPDATE_FUNC_ARGS)
{
	int blockpress = 0;
	for (int nx = -2; nx <= 2; nx++)
	{
		for (int ny = -2; ny <= 2; ny++)
		{
			if ((!nx != !ny) && x + nx >= 0 && y + ny >= 0 && x + nx < XRES && y + ny < YRES)
			{
				if (TYP(pmap[y + ny][x + nx]) == PT_FE)
					blockpress++;
			}
		}
	}

	if (blockpress >= 8)
	{
		sim->air->bmap_blockair[y / CELL][x / CELL] = 1;
		sim->air->bmap_blockairh[y / CELL][x / CELL] = 0x8;
	}




	if (parts[i].life)
		return 0;
	for (int rx = -1; rx <= 1; rx++)
		for (int ry = -1; ry <= 1; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				int r = pmap[y+ry][x+rx];
				switch (TYP(r))
				{
				case PT_SALT:
					if (RNG::Ref().chance(1, 47))
						goto succ;
					break;
				case PT_SLTW:
					if (RNG::Ref().chance(1, 67))
						goto succ;
					break;
				case PT_WATR:
					if (RNG::Ref().chance(1, 1200))
						goto succ;
					break;
				case PT_O2:
					if (RNG::Ref().chance(1, 250))
						goto succ;
					break;
				case PT_LO2:
					goto succ;
					break;
				case PT_NONE:
					if (RNG::Ref().chance(1, 400000))
						goto succ;
					break;
				default:
					break;
				}
			}





	int r, rx, ry;
	if (parts[i].tmp > 1)
	{
		parts[i].tmp--;
		for (rx = -1; rx < 2; rx++)
			for (ry = -1; ry < 2; ry++)
				if (BOUNDS_CHECK && (rx || ry))
				{
					r = pmap[y + ry][x + rx];
					if (!r)
						continue;
					if ((TYP(r) == PT_METL || TYP(r) == PT_FE) && RNG::Ref().chance(1, 100))
					{
						part_change_type(ID(r), x + rx, y + ry, PT_FEOX);
						parts[ID(r)].tmp = (parts[i].tmp <= 7) ? parts[i].tmp = 1 : parts[i].tmp - RNG::Ref().between(0, 4);
					}
				}
	}
	else if (parts[i].tmp == 1 && RNG::Ref().chance(1, 1000))
	{
		parts[i].tmp = 0;
		part_change_type(i, x, y, PT_FEOX);
	}



	return 0;
succ:
	sim->part_change_type(i, x, y, PT_FEOX);
	parts[i].tmp = RNG::Ref().between(20, 29);
	return 0;
}

void FE_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_FE";
	elem->Name = "FE";
	elem->Colour = COLPACK(0xa19d94);
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
	elem->HotAir = 0.000f	* CFDS;
	elem->Falldown = 0;

	elem->Flammable = 0;
	elem->Explosive = 0;
	elem->Meltable = 1;
	elem->Hardness = 50;

	elem->Weight = (int) (7.87 * 20);

	elem->HeatConduct = 230;
	elem->Latent = 0;
	elem->Description = "Iron metal. Rusts with salt, can be used for electrolysis of H2O.";

	elem->Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_LIFE_DEC|PROP_HOT_GLOW;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = 1.0f;
	elem->HighPressureTransitionElement = ST;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = 1538.0;
	elem->HighTemperatureTransitionElement = PT_LAVA;

	elem->Update = &FE_update;
	elem->Graphics = NULL;
	elem->Init = &FE_init_element;
}
