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



int GAS_update(UPDATE_FUNC_ARGS)
{
	if (parts[i].temp <= 283.15 + (sim->air->pv[(y) / CELL][(x) / CELL]) && RNG::Ref().chance(1, 1000) || RNG::Ref().chance(1, 100000))
	{
		if (parts[i].ctype)
		{
			parts[i].type = parts[i].ctype;
		}
		else
		{
			parts[i].type = PT_OIL;
		}
		
	}
	int blockpress = 0;
	for (int nx = -2; nx <= 2; nx++)
	{
		for (int ny = -2; ny <= 2; ny++)
		{
			if ((!nx != !ny) && x + nx >= 0 && y + ny >= 0 && x + nx < XRES && y + ny < YRES)
			{
				if (TYP(pmap[y + ny][x + nx]) == PT_TUNG)
					blockpress++;
			}
		}
	}

	if (blockpress >= 6)
	{
		sim->air->bmap_blockair[y / CELL][x / CELL] = 1;
		sim->air->bmap_blockairh[y / CELL][x / CELL] = 0x8;
	}

	float limit = parts[i].temp / 20;
	if (sim->air->pv[y / CELL][x / CELL] < limit)
		sim->air->pv[y / CELL][x / CELL] += 0.001f * (limit - sim->air->pv[y / CELL][x / CELL]);
	if (sim->air->pv[y / CELL + 1][x / CELL] < limit)
		sim->air->pv[y / CELL + 1][x / CELL] += 0.001f * (limit - sim->air->pv[y / CELL + 1][x / CELL]);
	if (sim->air->pv[y / CELL - 1][x / CELL] < limit)
		sim->air->pv[y / CELL - 1][x / CELL] += 0.001f * (limit - sim->air->pv[y / CELL - 1][x / CELL]);

	sim->air->pv[y / CELL][x / CELL + 1] += 0.001f * (limit - sim->air->pv[y / CELL][x / CELL + 1]);
	sim->air->pv[y / CELL + 1][x / CELL + 1] += 0.001f * (limit - sim->air->pv[y / CELL + 1][x / CELL + 1]);
	sim->air->pv[y / CELL][x / CELL - 1] += 0.001f * (limit - sim->air->pv[y / CELL][x / CELL - 1]);
	sim->air->pv[y / CELL - 1][x / CELL - 1] += 0.001f * (limit - sim->air->pv[y / CELL - 1][x / CELL - 1]);
	parts[i].temp -= 0.001f * (limit - sim->air->pv[y / CELL - 1][x / CELL - 1]);

	int temp = 0;
	int oxyposnum = 0;
	
	for (int rx = -2; rx <= 2; rx++)
		for (int ry = -2; ry <= 2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				int r = pmap[y + ry][x + rx];
				if (RNG::Ref().chance(1, 10) && oxyposnum < 250 && parts[i].life > 0 && (parts[i].temp > 300 + 273 - (sim->air->pv[(y) / CELL][(x) / CELL] / 2) || TYP(r) == PT_FIRE || TYP(r) == PT_PLSM || TYP(r) == PT_EMBR) && (!r || (parts[ID(r)].oxidizer > 0 && parts[ID(r)].containsoxy > 0)))
				{
					//	parts[i].containsoxy++;

					
					if (!r)
					{
						oxyposnum++;
						continue;
					}
					else if (parts[ID(r)].oxidizer > 0 && parts[ID(r)].life > 0)
					{


						oxyposnum += parts[ID(r)].containsoxy;
						int randtemp = parts[ID(r)].life - RNG::Ref().between(1, 5);
						if (randtemp > 0)
						{
							parts[ID(r)].life = randtemp;
						}
						else
						{
							parts[ID(r)].life = 0;
						}

					}
					else
					{
						oxyposnum++;
					}

				}

				//continue;
				int rt = TYP(r);
				if ((RNG::Ref().chance(1, 5) && parts[i].life > 0) && (parts[i].containsoxy > 0 || oxyposnum > 0) && (parts[i].temp > 350 + 273 - (sim->air->pv[(y) / CELL][(x) / CELL] / 1.5) || rt == PT_FIRE || rt == PT_PLSM))
				{

					if (oxyposnum > 0 && oxyposnum < 10)
					{
						sim->air->pv[(y) / CELL][(x) / CELL] += 0.005f;

						//int tempx = x + RNG::Ref().between(-1, 1);
					//	int tempy = y + RNG::Ref().between(-1, 1);



						if (RNG::Ref().chance(1, 10 - oxyposnum))
						{
							float angle, magnitude;
							int n, np;

						//	for (n = 0; n < 2; n++)
						//	{
								np = sim->part_create(-3, x, y, PT_FIRE);
								if (np > -1)
								{
									magnitude = RNG::Ref().between(40, 99) * 0.05f;
									angle = RNG::Ref().between(0, 6283) * 0.001f; //(in radians, between 0 and 2*pi)
									parts[np].vx = parts[i].vx * 0.5f + cosf(angle) * magnitude;
									parts[np].vy = parts[i].vy * 0.5f + sinf(angle) * magnitude;
								
									//	parts[np].tmp2 = RNG::Ref().between(70, 109);
									parts[np].life = RNG::Ref().between(50, 100);
									if (parts[i].ctype)
									{
										parts[np].ctype = parts[i].ctype;
									}
									else 
									{

										parts[np].ctype = parts[i].ctype;
									}
									

								}
						//	}
							parts[i].life -= 1 * (oxyposnum / 2);
						}
					}
					else
					{
						sim->air->pv[(y) / CELL][(x) / CELL] += 0.005f;
						parts[i].temp += 1 * (parts[i].containsoxy / 2);
						if (RNG::Ref().chance(1, 10))
						{
							parts[i].life -= 1 * parts[i].containsoxy;
						} 
					}
				}

				else if (RNG::Ref().chance(1, 5) && parts[i].life > 0 && parts[i].containsoxy <= 0 && (parts[i].temp > 250 + 273 - (sim->air->pv[(y) / CELL][(x) / CELL] / 1.5) || rt == PT_FIRE || rt == PT_PLSM || rt == PT_EMBR))
				{

					//parts[i].life--;
					parts[i].temp += 1;
					sim->air->pv[(y) / CELL][(x) / CELL] += 0.005f;
					if (RNG::Ref().chance(1, 10))
					{
						parts[i].life--;
					}
				}




			}
	if (parts[i].life <= 0)
	{
		if (parts[i].ctype)
		{
			int temp = parts[i].ctype = parts[i].ctype;
		}
		else
		{

			int temp = parts[i].ctype;
		}
		//int templife = parts[i].life;
		sim->part_change_type(i, x, y, PT_FIRE);
		
		
		parts[i].ctype = temp;
		parts[i].life = RNG::Ref().between(30, 50);//templife;
		return 1;
	}
	

	return 0;
}




void GAS_create(ELEMENT_CREATE_FUNC_ARGS)
{
	
		parts[i].life = RNG::Ref().between(100, 200);
	
//	parts[i].containsoxy = RNG::Ref().between(1, 2) - 1;
	if (RNG::Ref().chance(1, 10))
	{
		parts[i].containsoxy = RNG::Ref().between(1, 2) - 1;
	}
}







void GAS_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_GAS";
	elem->Name = "GAS";
	elem->Colour = COLPACK(0xE0FF20);
	elem->MenuVisible = 1;
	elem->MenuSection = SC_GAS;
	elem->Enabled = 1;

	elem->Advection = 1.0f;
	elem->AirDrag = 0.01f * CFDS;
	elem->AirLoss = 0.99f;
	elem->Loss = 0.30f;
	elem->Collision = -0.1f;
	elem->Gravity = 0.01f;
	elem->Diffusion = 0.75f;
	elem->HotAir = 0.001f	* CFDS;
	elem->Falldown = 0;

	elem->Flammable = 0;
	elem->Explosive = 0;
	elem->Meltable = 0;
	elem->Hardness = 1;

	elem->Weight = (int)(0.68 * 20.0);

	elem->DefaultProperties.temp = R_TEMP + 273.15f;
	elem->HeatConduct = 42;
	elem->Latent = 0;
	elem->Description = "Natural gas. Very flammable, condenses into oil.";

	elem->Properties = TYPE_GAS|PROP_NEUTPASS;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = IPH;
	elem->HighPressureTransitionElement = NT;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = ITH;
	elem->HighTemperatureTransitionElement = NT;

	elem->Update = &GAS_update;
	elem->Func_Create = &GAS_create;
	//elem->Graphics = &COAL_graphics;
	elem->Init = &GAS_init_element;
}
