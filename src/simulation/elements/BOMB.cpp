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

int BOMB_update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry, rt, nb;
	for (rx=-1; rx<2; rx++)
		for (ry=-1; ry<2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				if (!r)
					continue;
				rt = TYP(r);
				if (rt!=PT_BOMB && rt!=PT_EMBR && rt!=PT_VIBR && rt!=PT_BCLN && !(sim->elements[rt].Properties&PROP_INDESTRUCTIBLE) && !(sim->elements[rt].Properties&PROP_CLONE))
				{
					int rad = 8, nt;
					int nxi, nxj;
					//TODO: this looks like a bad idea
					pmap[y][x] = 0;
					for (nxj=-rad; nxj<=rad; nxj++)
						for (nxi=-rad; nxi<=rad; nxi++)
							if ((std::pow((float)nxi,2.0f))/(std::pow((float)rad,2.0f))+(std::pow((float)nxj,2.0f))/(std::pow((float)rad,2.0f))<=1)
							{
								int ynxj = y + nxj, xnxi = x + nxi;

								if ((ynxj < 0) || (ynxj >= YRES) || (xnxi <= 0) || (xnxi >= XRES))
									continue;

								nt = TYP(pmap[y+nxj][x+nxi]);
								if (nt!=PT_VIBR && nt!=PT_BCLN && !(sim->elements[nt].Properties&PROP_INDESTRUCTIBLE) && !(sim->elements[nt].Properties&PROP_CLONE))
								{
									if (nt)
										sim->part_kill(ID(pmap[ynxj][xnxi]));
									sim->air->pv[ynxj/CELL][xnxi/CELL] += 0.1f;
									nb = sim->part_create(-3, xnxi, ynxj, PT_EMBR);
									if (nb != -1)
									{
										parts[nb].tmp = 2;
										parts[nb].life = 2;
										parts[nb].temp = 10000;
									}
								}
							}
					for (nxj=-(rad+1); nxj<=(rad+1); nxj++)
						for (nxi=-(rad+1); nxi<=(rad+1); nxi++)
							if ((std::pow((float)nxi,2.0f))/(std::pow((float)(rad+1),2.0f))+(std::pow((float)nxj,2.0f))/(std::pow((float)(rad+1),2.0f))<=1 && !TYP(pmap[y+nxj][x+nxi]))
							{
								nb = sim->part_create(-3, x+nxi, y+nxj, PT_EMBR);
								if (nb != -1)
								{
									parts[nb].tmp = 0;
									parts[nb].life = 50;
									parts[nb].temp = 10000;
									parts[nb].vx = RNG::Ref().between(-20, 20);
									parts[nb].vy = RNG::Ref().between(-20, 20);
								}
							}
					sim->part_kill(i);
					return 1;
				}
			}
	return 0;
}

int BOMB_graphics(GRAPHICS_FUNC_ARGS)
{
	*pixel_mode |= PMODE_FLARE;
	return 1;
}

void BOMB_init_element(ELEMENT_INIT_FUNC_ARGS)
{
	elem->Identifier = "DEFAULT_PT_BOMB";
	elem->Name = "BOMB";
	elem->Colour = COLPACK(0xFFF288);
	elem->MenuVisible = 1;
	elem->MenuSection = SC_EXPLOSIVE;
	elem->Enabled = 1;

	elem->Advection = 0.6f;
	elem->AirDrag = 0.01f * CFDS;
	elem->AirLoss = 0.98f;
	elem->Loss = 0.95f;
	elem->Collision = 0.0f;
	elem->Gravity = 0.1f;
	elem->Diffusion = 0.00f;
	elem->HotAir = 0.000f	* CFDS;
	elem->Falldown = 1;

	elem->Flammable = 0;
	elem->Explosive = 0;
	elem->Meltable = 0;
	elem->Hardness = 20;

	elem->Weight = 30;

	elem->DefaultProperties.temp = R_TEMP - 2.0f + 273.15f;
	elem->HeatConduct = 29;
	elem->Latent = 0;
	elem->Description = "Bomb. Explodes and destroys all surrounding particles when it touches something.";

	elem->Properties = TYPE_PART|PROP_SPARKSETTLE;

	elem->LowPressureTransitionThreshold = IPL;
	elem->LowPressureTransitionElement = NT;
	elem->HighPressureTransitionThreshold = IPH;
	elem->HighPressureTransitionElement = NT;
	elem->LowTemperatureTransitionThreshold = ITL;
	elem->LowTemperatureTransitionElement = NT;
	elem->HighTemperatureTransitionThreshold = ITH;
	elem->HighTemperatureTransitionElement = NT;

	elem->Update = &BOMB_update;
	elem->Graphics = &BOMB_graphics;
	elem->Init = &BOMB_init_element;
}
