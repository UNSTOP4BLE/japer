/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "japi3.h"

#include "../archive.h"
#include "../mem.h"
#include "../stage.h"
#include "../random.h"
#include "../timer.h"
#include "../animation.h"

//Week 4 background structure
typedef struct
{
	//Stage background base structure
	StageBack back;
	
	//Textures
	IO_Data arc_hench, arc_hench_ptr[2];
	
	Gfx_Tex tex_back0; //Foreground limo
	Gfx_Tex tex_back1; //bop bois
	Gfx_Tex tex_back2; //Sunset
	Gfx_Tex tex_back3; //bop bois 2
	Gfx_Tex tex_back4; //bop bois 3
	Gfx_Tex tex_back5; //bop bois 3

} Back_japi3;

	

void Back_japi3_DrawBG(StageBack *back)
{
	Back_japi3 *this = (Back_japi3*)back;
	
	fixed_t fx, fy;
	
	fixed_t beat_bop;
	if ((stage.song_step & 0x3) == 0)
		beat_bop = FIXED_UNIT - ((stage.note_scroll / 24) & FIXED_LAND);
	else
		beat_bop = 0;

  //Draw foreground limo
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT fglimo_src = {0, 0, 255, 128};
	RECT_FIXED fglimo_dst = {
		FIXED_DEC(-220,1) - fx,
		FIXED_DEC(50,1) - fy,
		FIXED_DEC(256,1),
		FIXED_DEC(128,1)
	};
	
	Stage_DrawTex(&this->tex_back0, &fglimo_src, &fglimo_dst, stage.camera.bzoom);
	fglimo_dst.x += fglimo_dst.w;
	fglimo_dst.y -= (fglimo_dst.h * 22) >> 7;
	fglimo_src.y += 128;
	Stage_DrawTex(&this->tex_back0, &fglimo_src, &fglimo_dst, stage.camera.bzoom);

 //Draw boppers
	fx = stage.camera.x;
	fy = stage.camera.y;

	static const struct Back_japi3_LowerBop
	{
		RECT src;
		RECT_FIXED dst;
	} lbop_piece[] = {
		{{0, 0, 91, 119}, {FIXED_DEC(-180,1), FIXED_DEC(-30,1), FIXED_DEC(91,1), FIXED_DEC(119,1)}},//cat thing amogus
		{{91, 0, 78, 170}, {FIXED_DEC(-80,1), FIXED_DEC(-50,1), FIXED_DEC(78,1), FIXED_DEC(170,1)}},//skid and catdude
		{{0, 128, 255,144 }, {FIXED_DEC(120,1), FIXED_DEC(-20,1), FIXED_DEC(255,1), FIXED_DEC(144,1)}},//pump dude
	};
	
	const struct Back_japi3_LowerBop *lbop_p = lbop_piece;
	for (size_t i = 0; i < COUNT_OF(lbop_piece); i++, lbop_p++)
	{
		RECT_FIXED lbop_dst = {
			lbop_p->dst.x - fx,
			lbop_p->dst.y - fy + (beat_bop << 3),
			lbop_p->dst.w,
			lbop_p->dst.h - (beat_bop << 3),
		};
		Stage_DrawTex(&this->tex_back1, &lbop_p->src, &lbop_dst, stage.camera.bzoom);
	}


	//Draw background limo
	//Use same scroll as henchmen
	//Draw sunset
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT sunset_src = {0, 0, 256, 256};
	RECT_FIXED sunset_dst = {
		FIXED_DEC(-165 - SCREEN_WIDEOADD2,1) - fx,
		FIXED_DEC(-130,1) - fy,
		FIXED_DEC(380 + SCREEN_WIDEOADD,1),
		FIXED_DEC(300,1)
	};
	
	Stage_DrawTex(&this->tex_back2, &sunset_src, &sunset_dst, stage.camera.bzoom);
}

void Back_japi3_DrawFG(StageBack* back)
{	
   Back_japi3* this = (Back_japi3*)back; 

         	fixed_t fx, fy;

           fixed_t beat_bop;
	if ((stage.song_step & 0x3) == 0)
		beat_bop = FIXED_UNIT - ((stage.note_scroll / 24) & FIXED_LAND);
	else
		beat_bop = 0;


	if ((stage.song_step) >= 1754)
	{
	 	fx = stage.camera.x;
	    fy = stage.camera.y;
	
	RECT sunset_src = {0, 0, 256, 256};
	RECT_FIXED sunset_dst = {
		FIXED_DEC(-165 - SCREEN_WIDEOADD2,1) - fx,
		FIXED_DEC(-130,1) - fy,
		FIXED_DEC(500 + SCREEN_WIDEOADD,1),
		FIXED_DEC(500,1)
	};
	
	Stage_DrawTex(&this->tex_back5, &sunset_src, &sunset_dst, stage.camera.bzoom);
	}
     


//Draw boppers
fx = stage.camera.x;
fy = stage.camera.y;



	static const struct Back_japi3_UpperBop
	{
		RECT src;
		RECT_FIXED dst;
	} ubop_piece[] = {
		{{0, 0, 120, 120}, {FIXED_DEC(-250,1), FIXED_DEC(40,1), FIXED_DEC(120,1), FIXED_DEC(120,1)}},
	};
	
	const struct Back_japi3_UpperBop *ubop_p = ubop_piece;
	for (size_t i = 0; i < COUNT_OF(ubop_piece); i++, ubop_p++)
	{
		RECT_FIXED ubop_dst = {
			ubop_p->dst.x - fx,
			ubop_p->dst.y - fy + (beat_bop << 2),
			ubop_p->dst.w,
			ubop_p->dst.h - (beat_bop << 2),
		};
		Stage_DrawTex(&this->tex_back3, &ubop_p->src, &ubop_dst, stage.camera.bzoom);
	}

		//Draw boppers

  fx = stage.camera.x;
fy = stage.camera.y;
	static const struct Back_japi3_UpperBopa
	{
		RECT src;
		RECT_FIXED dst;
	} ubop_piecea[] = {
		{{0, 0, 168, 119}, {FIXED_DEC(50,1), FIXED_DEC(30,1), FIXED_DEC(168,1), FIXED_DEC(119,1)}}
	};
	
	const struct Back_japi3_UpperBopa *ubop_pa = ubop_piecea;
	for (size_t i = 0; i < COUNT_OF(ubop_piecea); i++, ubop_pa++)
	{
		RECT_FIXED ubop_dsta = {
			ubop_pa->dst.x - fx,
			ubop_pa->dst.y - fy + (beat_bop << 2),
			ubop_pa->dst.w,
			ubop_pa->dst.h - (beat_bop << 2),
		};
		Stage_DrawTex(&this->tex_back4, &ubop_pa->src, &ubop_dsta, stage.camera.bzoom);
	}
}


void Back_japi3_Free(StageBack *back)
{
	Back_japi3 *this = (Back_japi3*)back;

    //Free henchmen archive
	Mem_Free(this->arc_hench);

	//Free structure
	Mem_Free(this);
}

StageBack *Back_japi3_New(void)
{
	//Allocate background structure
	Back_japi3 *this = (Back_japi3*)Mem_Alloc(sizeof(Back_japi3));
	if (this == NULL)
		return NULL;
	
	//Set background functions
   this->back.draw_md = NULL;
	this->back.draw_fg = Back_japi3_DrawFG;
	this->back.draw_bg = Back_japi3_DrawBG;
	this->back.free = Back_japi3_Free;
	
	//Load background textures
	IO_Data arc_back = IO_Read("\\JAPI3\\BACK.ARC;1");
	Gfx_LoadTex(&this->tex_back0, Archive_Find(arc_back, "back0.tim"), 0);
	Gfx_LoadTex(&this->tex_back1, Archive_Find(arc_back, "back1.tim"), 0);
	Gfx_LoadTex(&this->tex_back2, Archive_Find(arc_back, "back2.tim"), 0);
	Gfx_LoadTex(&this->tex_back3, Archive_Find(arc_back, "back3.tim"), 0);
    Gfx_LoadTex(&this->tex_back4, Archive_Find(arc_back, "back4.tim"), 0);
	Gfx_LoadTex(&this->tex_back5, Archive_Find(arc_back, "back5.tim"), 0);

	Mem_Free(arc_back);
	
	//Load henchmen textures
	
	
	//Initialize henchmen state
	
	return (StageBack*)this;
}
