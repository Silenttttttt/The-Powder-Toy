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

int WOOD_update(UPDATE_FUNC_ARGS)
{







	int temp = 0;
	int oxyposnum = 0;
	int oxypos[250][10] = { 0 };
	for (int rx = -2; rx <= 2; rx++)
		for (int ry = -2; ry <= 2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				int r = pmap[y + ry][x + rx];
				if (RNG::Ref().chance(1, 10) && oxyposnum < 250 && parts[i].life > 0 && (parts[i].temp > 300 + 273 - (sim->air->pv[(y) / CELL][(x) / CELL] / 2) || TYP(r) == PT_FIRE || TYP(r) == PT_PLSM || TYP(r) == PT_EMBR) && (!r || (parts[ID(r)].oxidizer > 0 && parts[ID(r)].containsoxy > 0)))
				{

					oxypos[oxyposnum][0] = x + rx;
					oxypos[oxyposnum][1] = y + ry;

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

				int rt = TYP(r);


				/*if (rt != parts[i].type && abs(parts[i].vx) > 10)
				{
					sim->air->pv[(y) / CELL][(x) / CELL] += abs(parts[i].vx) / 5;
					parts[i].vx /= 2;
				}
				if (rt != parts[i].type && abs(parts[i].vy) > 10)
				{
					sim->air->pv[(y) / CELL][(x) / CELL] += abs(parts[i].vy) / 5;
					parts[i].vy /= 2;
				}*/
				if ((RNG::Ref().chance(1, 10) && parts[i].life > 0) && (parts[i].containsoxy > 0 || oxyposnum > 0) && (parts[i].temp > 250 + 273 + parts[i].life - (sim->air->pv[(y) / CELL][(x) / CELL] / 2) || rt == PT_FIRE || rt == PT_PLSM))
				{

					if (oxyposnum > 0 && oxyposnum < 10)
					{
						sim->air->pv[(y) / CELL][(x) / CELL] += 0.005f;


						if (RNG::Ref().chance(1, 10 - oxyposnum))
						{
							int tempctype = parts[i].ctype;
							temp = RNG::Ref().between(1, oxyposnum) - 1;
							sim->part_create(-1, oxypos[temp][0], oxypos[temp][1], PT_FIRE);
							parts[ID(pmap[oxypos[temp][0]][oxypos[temp][1]])].ctype = tempctype;
							parts[ID(pmap[oxypos[temp][0]][oxypos[temp][1]])].temp += 1 * oxyposnum;
							parts[ID(pmap[oxypos[temp][0]][oxypos[temp][1]])].life = parts[i].life - RNG::Ref().between(50, 100);;

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

				else if (RNG::Ref().chance(1, 10) && parts[i].life > 0 && parts[i].containsoxy <= 0 && (parts[i].temp > 400 + 273 + parts[i].life - (sim->air->pv[(y) / CELL][(x) / CELL] / 2) || rt == PT_FIRE || rt == PT_PLSM || rt == PT_EMBR))
				{

					//parts[i].life--;
					parts[i].temp += 1;
					sim->air->pv[(y) / CELL][(x) / CELL] += 0.005f;
					switch (RNG::Ref().chance(1, parts[i].life + 100))
					{

					case 1:
						parts[i].life = RNG::Ref().between(100, 150) + parts[i].life / 2;
						sim->part_change_type(i, x, y, PT_BCOL);
						break;
					case 2:
					
						break;
						parts[i].life = RNG::Ref().between(100, 150) + parts[i].life / 2;
						sim->part_change_type(i, x, y, PT_CO);
					
					case 3:
						
					

						parts[i].life = RNG::Ref().between(100, 150) + parts[i].life / 2;
						sim->part_change_type(i, x, y, PT_GAS);
					
						break;
					case 4:



						parts[i].life = RNG::Ref().between(100, 150) + parts[i].life / 2;
						sim->part_change_type(i, x, y, PT_SAWD);

						break;
					default:
						break;
							}


				}




			}
	if (parts[i].life <= 0)
	{
		int temp = parts[i].type;
		//int templife = parts[i].life;
		sim->part_change_type(i, x, y, PT_FIRE);
		parts[i].ctype = temp;
		parts[i].life = RNG::Ref().between(30, 50);//templife;
		return 1;
	}









	if (parts[i].temp > 450 && parts[i].temp > parts[i].tmp2)
		parts[i].tmp2 = (int)parts[i].temp;
	return 0;
}

void WOOD_create(ELEMENT_CREATE_FUNC_ARGS)
{
	parts[i].life = RNG::Ref().between(500, 1000);
	//parts[i].containsoxy = RNG::Ref().between(1, 2) - 1;
//	if (RNG::Ref().chance(1, 10))
//	{
		//parts[i].containsoxy = RNG::Ref().between(1, 2) - 1;
	//}
}

int WOOD_graphics(GRAPHICS_FUNC_ARGS)
{
	float maxtemp = std::max((float)cpart->tmp, cpart->temp);
	if (maxtemp > 400)
	{
		*colr -= (int)restrict_flt((maxtemp-400)/3,0,172);
		*colg -= (int)restrict_flt((maxtemp-400)/4,0,140);
		*colb -= (int)restrict_flt((maxtemp-400)/20,0,44);
		if (maxtemp > 450)
			cpart->tmp = (int)maxtemp;
	}
	if (maxtemp < 273)
	{
		*colr -= (int)restrict_flt((273-maxtemp)/5,0,40);
		*colg += (int)restrict_flt((273-maxtemp)/4,0,40);
		*colb += (int)restrict_flt((273-maxtemp)/1.5f,0,150);
	}
	return 0;
}
void WOOD_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_WOOD";
	elem->Name = "WOOD";
	elem->Colour = COLPACK(0xC0A040);
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
	elem->Meltable = 0;
	elem->Hardness = 15;

	elem->Weight = (int)(0.85 * 20.0);

	elem->HeatConduct = 69;
	elem->Latent = 0;
	elem->Description = "Wood. Commonly used as fuel .";

	elem->Properties = TYPE_SOLID | PROP_NEUTPENETRATE;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = IPH;
	elem->HighPressureTransitionElement = NT;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = ITH;
	elem->HighTemperatureTransitionElement = NT;

	elem->Update = &WOOD_update;
	elem->Graphics = &WOOD_graphics;
	elem->Func_Create = &WOOD_create;
	elem->Init = &WOOD_init_element;
}
