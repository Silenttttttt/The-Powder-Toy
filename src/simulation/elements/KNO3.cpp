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

int KNO3_update(UPDATE_FUNC_ARGS)
{
	/*
	int temp = 0;
	int oxyposnum = 0;
	int oxypos[250][10] = { 0 };
	for (int rx = -2; rx <= 2; rx++)
		for (int ry = -2; ry <= 2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				int r = pmap[y + ry][x + rx];
				if (!r || (parts[ID(r)].oxidizer > 0 && parts[ID(r)].containsoxy > 0))
				{
				//	parts[i].containsoxy++;

					oxypos[oxyposnum][0] = x + rx;
					oxypos[oxyposnum][1] = y + ry;
					oxyposnum++;
					if (!r)
					{
						continue;
					}
				}

					//continue;
				int rt = TYP(r);

				
				
			
				if ((RNG::Ref().chance(1, 10) && parts[i].life > 0) && (parts[i].containsoxy >  0 || oxyposnum > 0) && (parts[i].temp > 300 + 273 || rt == PT_FIRE  || rt == PT_PLSM))
				{
					
					if (oxyposnum > 0 && oxyposnum < 10)
					{
						sim->air->pv[(y) / CELL][(x) / CELL] += 0.005f;
						
						//int tempx = x + RNG::Ref().between(-1, 1);
					//	int tempy = y + RNG::Ref().between(-1, 1);
						

					
						if (RNG::Ref().chance(1, 10-oxyposnum))
						{
							int tempctype = parts[i].ctype;
							temp = RNG::Ref().between(1, oxyposnum) - 1;
							sim->part_create(-1, oxypos[temp][0], oxypos[temp][1], PT_FIRE);
							parts[ID(pmap[oxypos[temp][0]][oxypos[temp][1]])].ctype = tempctype;
							parts[ID(pmap[oxypos[temp][0]][oxypos[temp][1]])].temp += 1 * oxyposnum;
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

				else if (RNG::Ref().chance(1, 10) && parts[i].life > 0 && parts[i].containsoxy <= 0 && (parts[i].temp > 300 + 273 || rt == PT_FIRE  || rt == PT_PLSM))
				{

					//parts[i].life--;
					parts[i].temp+=1;
					sim->air->pv[(y) / CELL][(x) / CELL] += 0.005f;
					if (RNG::Ref().chance(1, 10))
					{
						parts[i].life--;
					}
				}




			}
	if (parts[i].life <= 0)
	{
		int temp = parts[i].ctype;

		sim->part_create(i, x, y, PT_FIRE);
		parts[i].ctype = temp;
		return 1;
	}

	

	//if(100-parts[i].life > parts[i].tmp2)
	//	parts[i].tmp2 = 100-parts[i].life;
	//if(parts[i].tmp2 < 0) parts[i].tmp2 = 0;
	//for ( trade = 0; trade<4; trade ++)
	//{
	//	rx = RNG::Ref().between(-2, 2);
	//	ry = RNG::Ref().between(-2, 2);
	//	if (BOUNDS_CHECK && (rx || ry))
	//	{
	//		r = pmap[y+ry][x+rx];
	//		if (!r)
	//			continue;
	//		if ((TYP(r)==PT_COAL || TYP(r)==PT_BCOL)&&(parts[i].tmp2>parts[ID(r)].tmp2)&&parts[i].tmp2>0)//diffusion
	//		{
	//			int temp = parts[i].tmp2 - parts[ID(r)].tmp2;
	//			if(temp < 10)
	//				continue;
	//			if (temp ==1)
	//			{
	//				parts[ID(r)].tmp2 ++;
	//				parts[i].tmp2 --;
	//			}
	//			else if (temp>0)
	//			{
	//				parts[ID(r)].tmp2 += temp/2;
	//				parts[i].tmp2 -= temp/2;
	//			}
	//		}
	//	}
	//}
	if(parts[i].temp > parts[i].tmp2)
		parts[i].tmp2 = (int)parts[i].temp;
	*/

if (parts[i].life <= 0)
{
	
	sim->part_change_type(i, x, y, PT_K);

	sim->air->pv[(y) / CELL][(x) / CELL] += 0.005f;
	


}











return 0;
	
}

void KNO3_create(ELEMENT_CREATE_FUNC_ARGS)
{
	parts[i].life = RNG::Ref().between(50, 100);
	parts[i].containsoxy = 3;
	parts[i].oxidizer = 1;
//	if (RNG::Ref().chance(1, 10))
//	{
		//parts[i].containsoxy = RNG::Ref().between(1, 2) - 1;
	//}
}


void KNO3_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_KNO3";
	elem->Name = "KNO3";
	elem->Colour = COLPACK(0xF0F0F0);
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
	elem->PhotonReflectWavelengths = 0x00000000;

	elem->Weight = (int) (2.1 * 20);

	elem->HeatConduct = 150;
	elem->Latent = 0;
	elem->Description = "Potassium nitrate. a common oxidizer, ingredient in blackpowder.";

	elem->Properties = TYPE_PART;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = IPH;
	elem->HighPressureTransitionElement = NT;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = ITH;
	elem->HighTemperatureTransitionElement = NT;


	elem->Update = &KNO3_update;
	elem->Func_Create = &KNO3_create;
	//elem->Graphics = &COAL_graphics;
	elem->Init = &KNO3_init_element;
}
