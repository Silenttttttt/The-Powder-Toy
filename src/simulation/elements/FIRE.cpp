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
#include "graphics.h"



int K_update(UPDATE_FUNC_ARGS);
int THRM_update(UPDATE_FUNC_ARGS);

int FIRE_update(UPDATE_FUNC_ARGS)
{
	if (parts[i].type != PT_SPRK)
	{

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

		int t = parts[i].type;

		switch (t)
		{
		
		
		case PT_LAVA:
			if (parts[i].ctype == PT_K)
			{
				if (parts[i].temp <= 65.0 + 273)
				{
					//int temp = parts[i].type;
					int templife = parts[i].life;
					sim->part_change_type(i, x, y, parts[i].ctype);
					//	parts[i].temp -= 10;
						//parts[i].ctype = PT_NONE;
					//	parts[i].life = templife;
					return 1;

				}

				//PT_K UPDATE








			//	if (parts[i].life <= 0)
			//	{
			//		int temp = parts[i].type;
			//		//int templife = parts[i].life;
			//		sim->part_change_type(i, x, y, PT_FIRE);
			//		parts[i].ctype = temp;
			//		parts[i].life = RNG::Ref().between(30, 50);//templife;
			//		return 1;
			//	}



			//	int temp = 0;
			//	int oxyposnum = 0;
			//	int oxypos[250][10] = { 0 };
			//	for (int rx = -2; rx <= 2; rx++)
			//		for (int ry = -2; ry <= 2; ry++)
			//			if (BOUNDS_CHECK && (rx || ry))
			//			{
			//				int r = pmap[y + ry][x + rx];
			//				if (RNG::Ref().chance(1, 10) && oxyposnum < 250 && parts[i].life > 0 && (parts[i].temp > 377 + 273 - (sim->air->pv[(y) / CELL][(x) / CELL] / 4) || TYP(r) == PT_FIRE || TYP(r) == PT_PLSM || TYP(r) == PT_EMBR) && (!r || (parts[ID(r)].oxidizer > 0 && parts[ID(r)].containsoxy > 0)))
			//				{
			//					//	parts[i].containsoxy++;

			//					oxypos[oxyposnum][0] = x + rx;
			//					oxypos[oxyposnum][1] = y + ry;

			//					if (!r)
			//					{
			//						oxyposnum++;
			//						continue;
			//					}
			//					else if (parts[ID(r)].oxidizer > 0 && parts[ID(r)].life > 0)
			//					{


			//						oxyposnum += parts[ID(r)].containsoxy;
			//						int randtemp = parts[ID(r)].life - RNG::Ref().between(1, 5);
			//						if (randtemp > 0)
			//						{
			//							parts[ID(r)].life = randtemp;
			//						}
			//						else
			//						{
			//							parts[ID(r)].life = 0;
			//						}

			//					}
			//					else
			//					{
			//						oxyposnum++;
			//					}

			//				}

			//				//continue;
			//				int rt = TYP(r);




			//				if ((RNG::Ref().chance(1, 10) && parts[i].life > 0) && (parts[i].containsoxy > 0 || oxyposnum > 0) && (parts[i].temp > 377 + 273 - (sim->air->pv[(y) / CELL][(x) / CELL] / 4) || rt == PT_FIRE || rt == PT_PLSM))
			//				{

			//					if (oxyposnum > 0 && oxyposnum < 10)
			//					{
			//						sim->air->pv[(y) / CELL][(x) / CELL] += 0.005f;

			//						//int tempx = x + RNG::Ref().between(-1, 1);
			//					//	int tempy = y + RNG::Ref().between(-1, 1);



			//						if (RNG::Ref().chance(1, 10 - oxyposnum))
			//						{
			//							int tempctype = parts[i].ctype;
			//							temp = RNG::Ref().between(1, oxyposnum) - 1;
			//							sim->part_create(-1, oxypos[temp][0], oxypos[temp][1], PT_FIRE);
			//							parts[ID(pmap[oxypos[temp][0]][oxypos[temp][1]])].ctype = tempctype;
			//							parts[ID(pmap[oxypos[temp][0]][oxypos[temp][1]])].temp += 1 * oxyposnum;
			//							parts[ID(pmap[oxypos[temp][0]][oxypos[temp][1]])].life = parts[i].life - RNG::Ref().between(50, 100);;
			//							parts[i].life -= 1 * (oxyposnum / 2);
			//						}
			//					}
			//					else
			//					{
			//						sim->air->pv[(y) / CELL][(x) / CELL] += 0.005f;
			//						parts[i].temp += 1 * (parts[i].containsoxy / 2);
			//						if (RNG::Ref().chance(1, 10))
			//						{
			//							parts[i].life -= 1 * parts[i].containsoxy;
			//						}
			//					}
			//				}

			//				else if (RNG::Ref().chance(1, 10) && parts[i].life > 0 && oxyposnum <= 0 && (parts[i].temp > 377 + 273  || rt == PT_FIRE || rt == PT_PLSM))
			//				{

			//					//parts[i].life--;
			//					parts[i].temp += 1;
			//					sim->air->pv[(y) / CELL][(x) / CELL] += 0.005f;
			//					if (RNG::Ref().chance(1, 10))
			//					{
			//						parts[i].life--;
			//					}
			//				}

			//				//PT_K UPDATE
			//			}


			//			
			//}

				K_update(UPDATE_FUNC_SUBCALL_ARGS);
				return 0;
			}
			else if (parts[i].ctype == PT_THRM)
			{
			THRM_update(UPDATE_FUNC_SUBCALL_ARGS);
			return 0;

				}
			break;





		case PT_PLSM:
			if (parts[i].life <= 1)
			{
				if (parts[i].ctype == PT_NBLE)
				{
					t = PT_NBLE;
					sim->part_change_type(i, x, y, t);
					parts[i].life += RNG::Ref().between(5, 10);
				}
				else if ((parts[i].tmp & 0x3) == 3)
				{
					sim->part_change_type(i, x, y, PT_DSTW);
					parts[i].life = 0;
					parts[i].ctype = PT_FIRE;
				}
			}
			break;
		case PT_FIRE:
			if (parts[i].life <= 5 && parts[i].ctype == PT_GUNP)
			{
				if (RNG::Ref().chance(1, 2))
				{
					if (RNG::Ref().chance(1, 100))
					{
						sim->part_change_type(i, x, y, PT_WTRV);
						parts[i].ctype = PT_NONE;
						parts[i].temp += RNG::Ref().between(1, 2);

					}
					else if (RNG::Ref().chance(1, 2))
					{
						sim->part_change_type(i, x, y, PT_N2);
						parts[i].ctype = PT_NONE;
						parts[i].temp += RNG::Ref().between(1, 2);

					}
					else if (RNG::Ref().chance(1, 10))
					{
						sim->part_change_type(i, x, y, PT_CO);
						parts[i].ctype = PT_NONE;
						parts[i].temp += RNG::Ref().between(1, 2);
						parts[i].life += RNG::Ref().between(5, 10);
					}
					else
					{
						sim->part_change_type(i, x, y, PT_CO2);
						parts[i].ctype = PT_NONE;
						parts[i].temp += RNG::Ref().between(1, 2);
					}
				}
			}
			else if (parts[i].life <= 1)
			{
				if ((parts[i].tmp & 0x3) == 3)
				{
					sim->part_change_type(i, x, y, PT_DSTW);
					parts[i].life = 0;
					parts[i].ctype = PT_FIRE;
				}
				else if (parts[i].temp < 625)
				{
					if (RNG::Ref().chance(1, 4))
					{
						sim->part_change_type(i, x, y, PT_CO2);
						parts[i].life = RNG::Ref().between(250, 269);
					}
				}
			}
			break;
		default:
			break;
		}
		for (int rx = -2; rx <= 2; rx++)
			for (int ry = -2; ry <= 2; ry++)
				if (BOUNDS_CHECK && (rx || ry))
				{
					int r = pmap[y + ry][x + rx];
					if (!r)
						continue;
					int rt = TYP(r);
					//THRM burning
					//if (rt==PT_THRM && (t==PT_FIRE || t==PT_PLSM))
					//{
					//	if (RNG::Ref().chance(1, 500))
					//	{
					//		sim->part_change_type(ID(r),x+rx,y+ry,PT_LAVA);
					//		parts[ID(r)].ctype = PT_BMTL;
					//		parts[ID(r)].temp = 3500.0f;
					//		sim->air->pv[(y+ry)/CELL][(x+rx)/CELL] += 50.0f;
					//	}
					//	else
					//	{
					//		sim->part_change_type(ID(r),x+rx,y+ry,PT_LAVA);
					//		parts[ID(r)].life = 400;
					//		parts[ID(r)].ctype = PT_THRM;
					//		parts[ID(r)].temp = 3500.0f;
					//		parts[ID(r)].tmp = 20;
					//	}
					//	continue;
					//}

					//if ((rt==PT_COAL) || (rt==PT_BCOL))
					//{
					//	if ((t==PT_FIRE || t==PT_PLSM))
					//	{
					//		if (parts[ID(r)].life>100 && RNG::Ref().chance(1, 500))
					//		{
					//			//parts[ID(r)].life = 99;
					//		}
					//	}
					//	else if (t==PT_LAVA)
					//	{
					//		if (parts[i].ctype == PT_FE && RNG::Ref().chance(1, 500))
					//		{
					//			parts[i].ctype = PT_METL;
					//			sim->part_kill(ID(r));
					//		}
					//	}
					//}


					if (t == PT_LAVA)
					{
						// LAVA(CLST) + LAVA(PQRT) + high enough temp = LAVA(CRMC) + LAVA(CRMC)
						if (parts[i].ctype == PT_QRTZ && rt == PT_LAVA && parts[ID(r)].ctype == PT_CLST)
						{
							float pres = std::max(sim->air->pv[y / CELL][x / CELL] * 10.0f, 0.0f);
							if (parts[i].temp >= pres + sim->elements[PT_CRMC].HighTemperatureTransitionThreshold + 50.0f)
							{
								parts[i].ctype = PT_CRMC;
								parts[ID(r)].ctype = PT_CRMC;
							}
						}
						else if (rt == PT_HEAC && parts[i].ctype == PT_HEAC)
						{
							if (parts[ID(r)].temp > sim->elements[PT_HEAC].HighTemperatureTransitionThreshold)
							{
								sim->part_change_type(ID(r), x + rx, y + ry, PT_LAVA);
								parts[ID(r)].ctype = PT_HEAC;
							}
						}
					}

					if ((surround_space || sim->elements[rt].Explosive) &&
						sim->elements[rt].Flammable && RNG::Ref().chance(sim->elements[rt].Flammable + sim->air->pv[(y + ry) / CELL][(x + rx) / CELL] * 10.0f, 1000) &&
						//exceptions, t is the thing causing the flame and rt is what's burning
						((rt != PT_RBDM && rt != PT_LRBD && rt != PT_INSL)) &&
						(t != PT_PHOT || rt != PT_INSL) &&
						(rt != PT_SPNG || parts[ID(r)].life == 0))
					{
						sim->part_change_type(ID(r), x + rx, y + ry, PT_FIRE);
						parts[ID(r)].temp = restrict_flt(sim->elements[PT_FIRE].DefaultProperties.temp + (sim->elements[rt].Flammable / 2), MIN_TEMP, 10000);
						parts[ID(r)].life = RNG::Ref().between(130, 200);
						parts[ID(r)].tmp = parts[ID(r)].ctype = 0;
						if (sim->elements[rt].Explosive)
							sim->air->pv[y / CELL][x / CELL] += 0.25f * CFDS;
					}
				}
		//if (legacy_enable && t!=PT_SPRK) // SPRK has no legacy reactions
			//FIRE_update_legacy(UPDATE_FUNC_SUBCALL_ARGS);


		if (parts[i].life <= 0)
		{
			switch (parts[i].ctype)
			{

			case PT_NONE:
				switch (RNG::Ref().between(2, 50))
				{
				case 7:

					sim->part_change_type(i, x, y, PT_WTRV);
					parts[i].ctype = PT_NONE;
					parts[i].temp += RNG::Ref().between(1, 2);
					parts[i].life += RNG::Ref().between(5, 10);
					break;
				case 2:

					sim->part_change_type(i, x, y, PT_N2);
					parts[i].ctype = PT_NONE;
					parts[i].temp += RNG::Ref().between(1, 2);
					parts[i].life += RNG::Ref().between(5, 10);
					break;
				case 3:

					sim->part_change_type(i, x, y, PT_CO);
					parts[i].ctype = PT_NONE;
					parts[i].temp += RNG::Ref().between(1, 2);
					parts[i].life += RNG::Ref().between(5, 10);
					break;
				case 4:

					sim->part_change_type(i, x, y, PT_CO2);
					parts[i].ctype = PT_NONE;
					parts[i].temp += RNG::Ref().between(1, 2);
					parts[i].life += RNG::Ref().between(5, 10);
					break;
				case 5:

					sim->part_change_type(i, x, y, PT_GAS);
					parts[i].ctype = PT_NONE;
					parts[i].temp += RNG::Ref().between(1, 2);
					parts[i].life += RNG::Ref().between(5, 10);
					break;
				case 6:

					sim->part_change_type(i, x, y, PT_BCOL);
					parts[i].ctype = PT_NONE;
					parts[i].temp += RNG::Ref().between(1, 2);
					parts[i].life += RNG::Ref().between(5, 10);

					break;




				default:
					sim->part_change_type(i, x, y, PT_NONE);
					break;
				}



				break;









			case PT_POIL:
			case PT_WAX:
			case PT_MWAX:
			case PT_BCOL:
			case PT_DESL:
			case PT_COAL:
			case PT_GAS:
			case PT_OIL:
				if (RNG::Ref().chance(1, 100))
				{
					switch (RNG::Ref().between(2, 10))
					{

					case 8:
						if (RNG::Ref().chance(1, 20))
						{
							sim->part_change_type(i, x, y, PT_NBLE);
							parts[i].ctype = PT_GAS;
							parts[i].temp += RNG::Ref().between(1, 2);
							parts[i].life += RNG::Ref().between(5, 10);
							break;
						}
					
					case 7:
						if (RNG::Ref().chance(1, 5))
						{
							sim->part_change_type(i, x, y, PT_WTRV);
							parts[i].ctype = PT_NONE;
							parts[i].temp += RNG::Ref().between(1, 2);
							parts[i].life += RNG::Ref().between(5, 10);
							break;
						}
					
					case 2:
						if (RNG::Ref().chance(1, 20))
						{
							sim->part_change_type(i, x, y, PT_N2);
							parts[i].ctype = PT_NONE;
							parts[i].temp += RNG::Ref().between(1, 2);
							parts[i].life += RNG::Ref().between(5, 10);
							break;
						}
							
						
					case 3:
						if (RNG::Ref().chance(1, 8))
						{
							sim->part_change_type(i, x, y, PT_CO);
							parts[i].ctype = PT_NONE;
							parts[i].temp += RNG::Ref().between(1, 2);
							parts[i].life += RNG::Ref().between(5, 10);
							break;
						}
						
					case 4:
						if (RNG::Ref().chance(1, 5))
						{
							sim->part_change_type(i, x, y, PT_CO2);
							parts[i].ctype = PT_NONE;
							parts[i].temp += RNG::Ref().between(1, 2);
							parts[i].life += RNG::Ref().between(5, 10);
							break;
						}
						
					case 5:
						if (RNG::Ref().chance(1, 5))
						{
							sim->part_change_type(i, x, y, PT_GAS);
							parts[i].ctype = PT_NONE;
							parts[i].temp += RNG::Ref().between(1, 2);
							parts[i].life += RNG::Ref().between(5, 10);
							break;
						}
						
					case 6:
						if (RNG::Ref().chance(1, 5))
						{
							sim->part_change_type(i, x, y, PT_BCOL);
							parts[i].ctype = PT_NONE;
							parts[i].temp += RNG::Ref().between(1, 2);
							parts[i].life += RNG::Ref().between(5, 10);
							break;
						}
						




					default:
						sim->part_change_type(i, x, y, PT_NONE);
						break;
					}
					

				}
				sim->part_change_type(i, x, y, PT_NONE);
				break;


			
					


			case PT_H2:
				switch (RNG::Ref().between(2, 40))
				{
				case 7:

					sim->part_change_type(i, x, y, PT_WTRV);
					parts[i].ctype = PT_NONE;
					parts[i].temp += RNG::Ref().between(1, 2);
					parts[i].life += RNG::Ref().between(5, 10);

					break;


				default:
					sim->part_change_type(i, x, y, PT_NONE);
					break;
				}



				break;
























			default:

				switch (RNG::Ref().between(2, 50))
				{
				case 7:

					sim->part_change_type(i, x, y, PT_WTRV);
					parts[i].ctype = PT_NONE;
					parts[i].temp += RNG::Ref().between(1, 2);
					parts[i].life += RNG::Ref().between(5, 10);

					break;
				case 2:

					sim->part_change_type(i, x, y, PT_N2);
					parts[i].ctype = PT_NONE;
					parts[i].temp += RNG::Ref().between(1, 2);
					parts[i].life += RNG::Ref().between(5, 10);
					break;
				case 3:

					sim->part_change_type(i, x, y, PT_CO);
					parts[i].ctype = PT_NONE;
					parts[i].temp += RNG::Ref().between(1, 2);
					parts[i].life += RNG::Ref().between(5, 10);
					break;
				case 4:

					sim->part_change_type(i, x, y, PT_CO2);
					parts[i].ctype = PT_NONE;
					parts[i].temp += RNG::Ref().between(1, 2);
					parts[i].life += RNG::Ref().between(5, 10);
					break;
				case 5:

					sim->part_change_type(i, x, y, PT_GAS);
					parts[i].ctype = PT_NONE;
					parts[i].temp += RNG::Ref().between(1, 2);
					parts[i].life += RNG::Ref().between(5, 10);
					break;
				case 6:

					sim->part_change_type(i, x, y, PT_BCOL);
					parts[i].ctype = PT_NONE;
					parts[i].temp += RNG::Ref().between(1, 2);
					parts[i].life += RNG::Ref().between(5, 10);


				default:
					sim->part_change_type(i, x, y, PT_NONE);
					break;
				}


				break;

			}
		}
	}
	return 0;
}

int FIRE_graphics(GRAPHICS_FUNC_ARGS)
{
	int caddress = (int)restrict_flt(restrict_flt((float)cpart->life, 0.0f, 200.0f)*3, 0.0f, (200.0f*3)-3);
	*colr = (unsigned char)flm_data[caddress] + (cpart->temp / 50) + 70;
	*colg = (unsigned char)flm_data[caddress+1] + (cpart->temp / 80);
	*colb = (unsigned char)flm_data[caddress+2] + (cpart->temp / 150);
	
	*firea = (cpart->temp / 10) + 10;
	*firer = *colr;
	*fireg = *colg;
	*fireb = *colb + (cpart->temp / 80);
	
	*pixel_mode = PMODE_NONE; //Clear default, don't draw pixel
	*pixel_mode |= FIRE_ADD;
	//Returning 0 means dynamic, do not cache
	return 0;
}
void FIRE_create(ELEMENT_CREATE_FUNC_ARGS)
{
	if (parts[i].ctype == PT_NONE || parts[i].life != 0)
	{
		parts[i].life = RNG::Ref().between(40, 70);
		parts[i].temp = RNG::Ref().between(50, 80) + 800.0f + 273.15f;

	}
	
}

void FIRE_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_FIRE";
	elem->Name = "FIRE";
	elem->Colour = COLPACK(0xFF1000);
	elem->MenuVisible = 1;
	elem->MenuSection = SC_EXPLOSIVE;
	elem->Enabled = 1;

	elem->Advection = 0.9f;
	elem->AirDrag = 0.04f * CFDS;
	elem->AirLoss = 0.97f;
	elem->Loss = 0.20f;
	elem->Collision = 0.0f;
	elem->Gravity = -0.1f;
	elem->Diffusion = 0.00f;
	elem->HotAir = 0.001f	* CFDS;
	elem->Falldown = 1;

	elem->Flammable = 0;
	elem->Explosive = 0;
	elem->Meltable = 0;
	elem->Hardness = 1;

	elem->Weight = (int) (1 * 20.0);

	elem->DefaultProperties.temp = RNG::Ref().between(50, 80) + 800.0f + 273.15f;
	elem->HeatConduct = 128;
	elem->Latent = 0;
	elem->Description = "Fire. The rapid oxidation of a material in the exothermic chemical process of combustion.";

	elem->Properties = TYPE_GAS|PROP_LIFE_DEC;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = IPH;
	elem->HighPressureTransitionElement = NT;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = ITH;
	elem->HighTemperatureTransitionElement = NT;

	elem->Update = &FIRE_update;
	elem->Graphics = &FIRE_graphics;
	elem->Func_Create = &FIRE_create;
	elem->Init = &FIRE_init_element;
}
