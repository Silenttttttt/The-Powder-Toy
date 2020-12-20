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


int GUNP_update(UPDATE_FUNC_ARGS)
{
	int oxyposnum = 0;
	int temp = 0;
	 
	for (int rx = -2; rx <= 2; rx++)
		for (int ry = -2; ry <= 2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				int r = pmap[y + ry][x + rx];
				if (RNG::Ref().chance(1, 10) && oxyposnum < 250 && parts[i].life > 0 && (parts[i].temp > 300 + 273 - (sim->air->pv[(y) / CELL][(x) / CELL] / 2) || TYP(r) == PT_FIRE  || TYP(r) == PT_PLSM || TYP(r) == PT_EMBR) && (!r || (parts[ID(r)].oxidizer > 0 && parts[ID(r)].containsoxy > 0)))
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

				/*if (rt == PT_NONE || rt == PT_O2 || rt == PT_LO2)
				{
					parts[i].containsoxy++;
					
					oxypos[oxyposnum][0] = x + rx;
					oxypos[oxyposnum][1] = y + ry;
					oxyposnum++;
				}*/

				if (parts[i].containsoxy > 0 && parts[i].temp >= 300 + 273 - (sim->air->pv[(y) / CELL][(x) / CELL] / 2) && RNG::Ref().chance(1, 5))
				{
					if (oxyposnum > 0)
					{
						float angle, magnitude;
						int n, np;

						//for (n = 0; n < 2; n++)
					////	{
						np = sim->part_create(-3, x, y, PT_FIRE);
						if (np > -1)
						{
							magnitude = RNG::Ref().between(40, 99) * 0.05f;
							angle = RNG::Ref().between(0, 6283) * 0.001f; //(in radians, between 0 and 2*pi)
							parts[np].vx = parts[i].vx * 0.5f + cosf(angle) * magnitude;
							parts[np].vy = parts[i].vy * 0.5f + sinf(angle) * magnitude;
							//	parts[np].tmp2 = RNG::Ref().between(70, 109);
							parts[np].life = RNG::Ref().between(30, 70);
							parts[np].ctype = parts[i].type;

						}
						//	}

						parts[i].life -= 1 * (oxyposnum / 2);
					}
					else 
					{
						//	sim->part_change_type(ID(r), x + rx, y + ry, PT_N2);
						//sim->part_change_type(ID(r), x + rx, y + ry, PT_FIRE);
						//parts[ID(r)].ctype = PT_GUNP;
						parts[i].temp += RNG::Ref().between(10, 50);
					//	parts[ID(r)].life += RNG::Ref().between(20, 100);
						sim->air->pv[(y) / CELL][(x) / CELL] += 0.3f;
						parts[i].life -= RNG::Ref().between(1, 5);
					}
				}
				
				else if ((rt == PT_FIRE  || rt == PT_PLSM) && oxyposnum > 0 && (parts[i].containsoxy > 0 || RNG::Ref().chance(1, 5)))
				{
						if (parts[i].life > 20)
						{
							if (!RNG::Ref().chance(1, 5))
							{


								float angle, magnitude;
								int n, np;

								//for (n = 0; n < 2; n++)
							////	{
								np = sim->part_create(-3, x, y, PT_FIRE);
								if (np > -1)
								{
									magnitude = RNG::Ref().between(40, 99) * 0.05f;
									angle = RNG::Ref().between(0, 6283) * 0.001f; //(in radians, between 0 and 2*pi)
									parts[np].vx = parts[i].vx * 0.5f + cosf(angle) * magnitude;
									parts[np].vy = parts[i].vy * 0.5f + sinf(angle) * magnitude;
									parts[np].temp += RNG::Ref().between(10, 20);
									//	parts[np].tmp2 = RNG::Ref().between(70, 109);
									parts[np].life = RNG::Ref().between(25, 75);
									parts[np].ctype = parts[i].type;

								}
								//	}

								parts[i].life -= 1 * (oxyposnum / 2);

								//temp = RNG::Ref().between(1, oxyposnum) - 1;
								//sim->part_create(PT_FIRE, oxypos[temp][0], oxypos[temp][1], -1);
								//parts[ID(pmap[oxypos[temp][0]][oxypos[temp][1]])].ctype = PT_NONE;
								//parts[ID(pmap[oxypos[temp][0]][oxypos[temp][1]])].temp += RNG::Ref().between(10, 20);
								//parts[ID(pmap[oxypos[temp][0]][oxypos[temp][1]])].life += RNG::Ref().between(10, 20);
								////sim->part_change_type(ID(r), x+rx, y+ry, PT_FIRE);
								//parts[i].life -= RNG::Ref().between(5, 10);
								sim->air->pv[(y) / CELL][(x) / CELL] += 1.0f;

							}
							else
							{

								parts[i].life -= RNG::Ref().between(5, 10);
								sim->air->pv[(y) / CELL][(x) / CELL] += 0.3f;
							}
						
						}
						/*else if (RNG::Ref().chance(1, 5))
						{
							sim->part_change_type(i, x, y, PT_BCOL);
							parts[i].ctype = PT_GUNP;
							parts[i].life += RNG::Ref().between(1, 50);
							sim->air->pv[(y) / CELL][(x) / CELL] += 0.3f;
							
						}*/
						else
						{
							sim->part_change_type(i, x, y, PT_FIRE);
							parts[i].ctype = PT_GUNP;
							parts[i].life += RNG::Ref().between(10, 20);
							parts[i].temp += RNG::Ref().between(20, 100);
							sim->air->pv[(y) / CELL][(x) / CELL] += 0.3f;
						}
						//sim->air->pv[(y) / CELL][(x) / CELL] += 0.5f;
					//}
					continue;
				}
				if (parts[i].temp >= 450 + 273 - (sim->air->pv[(y) / CELL][(x) / CELL] / 2) && parts[i].containsoxy <= 0 && oxyposnum <= 0)
				{
					parts[i].temp += RNG::Ref().between(1, 2);
					parts[i].life -= RNG::Ref().between(1, 5);
					sim->air->pv[(y) / CELL][(x) / CELL] += 0.3f;
				}
				/*if ((rt == PT_COAL) || (rt == PT_BCOL))
				{

					if (parts[ID(r)].life > 100 && RNG::Ref().chance(1, 500))
					{
						parts[ID(r)].life = 99;
					}



					if (parts[i].ctype == PT_FE && RNG::Ref().chance(1, 500))
					{
						parts[i].ctype = PT_METL;
						sim->part_kill(ID(r));
					}

				}*/








			}
	if (parts[i].life < 20 && RNG::Ref().chance(1, 3))
	{
		sim->part_change_type(i, x, y, PT_BCOL);
		parts[i].ctype = PT_GUNP;
		parts[i].life += RNG::Ref().between(1, 50);
		sim->air->pv[(y) / CELL][(x) / CELL] += 0.3f;
	}
	return 0;
}

void GUNP_create(ELEMENT_CREATE_FUNC_ARGS)
{
	parts[i].life = RNG::Ref().between(100, 150);
	parts[i].containsoxy = RNG::Ref().between(1, 3) - 1;
}


void GUNP_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_GUNP";
	elem->Name = "GUNP";
	elem->Colour = COLPACK(0x464650);
	elem->MenuVisible = 1;
	elem->MenuSection = SC_EXPLOSIVE;
	elem->Enabled = 1;

	elem->Advection = 0.7f;
	elem->AirDrag = 0.02f * CFDS;
	elem->AirLoss = 0.94f;
	elem->Loss = 0.80f;
	elem->Collision = -0.1f;
	elem->Gravity = 0.1f;
	elem->Diffusion = 0.00f;
	elem->HotAir = 0.000f	* CFDS;
	elem->Falldown = 1;

	elem->Flammable = 0;
	elem->Explosive = 0;
	elem->Meltable = 0;
	elem->Hardness = 10;

	elem->Weight = (int) (1.7*20);

	elem->HeatConduct = 97;
	elem->Latent = 0;
	elem->Description = "Blackpowder. Earliest known explosive. Made from a mix of sulfur, coal and potassium nitrate.";

	elem->Properties = TYPE_PART;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = IPH;
	elem->HighPressureTransitionElement = NT;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = ITH;
	elem->HighTemperatureTransitionElement = NT;


	

	elem->Update = NULL;
	elem->Graphics = NULL;
	elem->Init = &GUNP_init_element;
	elem->Func_Create = &GUNP_create;
	elem->Update = &GUNP_update;
}

