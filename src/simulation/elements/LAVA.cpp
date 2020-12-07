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

int FIRE_update(UPDATE_FUNC_ARGS);

int LAVA_graphics(GRAPHICS_FUNC_ARGS)
{
	*colr = cpart->temp / 2;
	*colg = cpart->temp / 2;
	*colb = cpart->temp / 2;
	if (*colr>255) *colr = 255;
	if (*colg>192) *colg = 192;
	if (*colb>128) *colb = 128;
	*firea = (cpart->temp / 500);
	*firer =  *colr;
	*fireg = *colg;
	*fireb =  *colb;
	*pixel_mode |= FIRE_ADD;
	*pixel_mode |= PMODE_BLUR;
	//Returning 0 means dynamic, do not cache
	return 0;
}

void LAVA_create(ELEMENT_CREATE_FUNC_ARGS)
{		


	if (parts[i].ctype == PT_NONE && parts[i].life == 0)
	{
		parts[i].life = RNG::Ref().between(240, 359);
		parts[i].temp = R_TEMP + 1500.0f + 273.15f;

	}
}

void LAVA_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_LAVA";
	elem->Name = "LAVA";
	elem->Colour = COLPACK(0xE05010);
	elem->MenuVisible = 1;
	elem->MenuSection = SC_LIQUID;
	elem->Enabled = 1;

	elem->Advection = 0.3f;
	elem->AirDrag = 0.02f * CFDS;
	elem->AirLoss = 0.95f;
	elem->Loss = 0.80f;
	elem->Collision = 0.0f;
	elem->Gravity = 0.15f;
	elem->Diffusion = 0.00f;
	elem->HotAir = 0.0003f	* CFDS;
	elem->Falldown = 2;

	elem->Flammable = 0;
	elem->Explosive = 0;
	elem->Meltable = 0;
	elem->Hardness = 2;
	elem->PhotonReflectWavelengths = 0x3FF00000;

	elem->Weight = (int)(3.1 * 20);

	elem->DefaultProperties.temp = R_TEMP + 273.15f;
	elem->HeatConduct = 50;
	elem->Latent = 0;
	elem->Description = "Molten lava.";

	elem->Properties = TYPE_LIQUID|PROP_LIFE_DEC | PROP_HOT_GLOW;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = IPH;
	elem->HighPressureTransitionElement = NT;
	elem->LowTemperatureTransitionThreshold = MAX_TEMP; // check for lava solidification at all temperatures
	elem->LowTemperatureTransitionElement = ST;
	elem->HighTemperatureTransitionThreshold = ITH;
	elem->HighTemperatureTransitionElement = NT;

	elem->Update = &FIRE_update;
	elem->Graphics = &LAVA_graphics;
	elem->Func_Create = &LAVA_create;
	elem->Init = &LAVA_init_element;
}
