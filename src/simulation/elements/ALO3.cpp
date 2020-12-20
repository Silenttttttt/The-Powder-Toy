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



int ALO3_update(UPDATE_FUNC_ARGS)
{








	





	//if (abs(parts[i].vx) > 20)
	//{
	//	sim->air->pv[y / CELL][x / CELL] += abs(parts[i].vx) / 2;
	////	if (parts[i].vx > 0)
	////	{
	//		parts[i].vx /= 3;
	//	//}
	////	else 
	////	{

	//	//}

	//}
	//if (abs(parts[i].vy) > 20)
	//{
	//	sim->air->pv[y / CELL][x / CELL] += abs(parts[i].vy) / 2;


	//	parts[i].vy /= 3;
	//}








	
	
	return 0;
}

void ALO3_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_ALO3";
	elem->Name = "AlO3";
	elem->Colour = COLPACK(0xFFFFFF);
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
	elem->Meltable = 0;
	elem->Hardness = 2;

	elem->Weight = (int)(3.987 * 20.0);

	elem->HeatConduct = 121;
	elem->Latent = 0;
	elem->Description = "Aluminium oxide (Al2O3). Commonly called alumina, high melting point";

	elem->Properties = TYPE_PART|PROP_HOT_GLOW;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = IPH;
	elem->HighPressureTransitionElement = NT;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = 2072 + 273.15;
	elem->HighTemperatureTransitionElement = PT_LAVA;

	elem->Update = &ALO3_update;
	elem->Graphics = &COAL_graphics;
	elem->Init = &ALO3_init_element;
}
