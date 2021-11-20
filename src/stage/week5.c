/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "week5.h"

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
	Gfx_Tex tex_back0; //Back wall
	Gfx_Tex tex_back2; //Lower bop
	Gfx_Tex tex_back3; //Lower bop 2
	Gfx_Tex tex_back4; //Lower bop 2
	
	
} Back_week5;


//Week 4 background functions
#define CAR_START_X FIXED_DEC(-500,1)
#define CAR_END_X    FIXED_DEC(500,1)
#define CAR_TIME_A FIXED_DEC(5,1)
#define CAR_TIME_B FIXED_DEC(14,1)

void Back_week5_DrawFG(StageBack *back)
{
	Back_week5 *this = (Back_week5*)back;
	
	fixed_t fx, fy;

	fixed_t beat_bop;
	if ((stage.song_step & 0x3) == 0)
		beat_bop = FIXED_UNIT - ((stage.note_scroll / 24) & FIXED_LAND);
	else
		beat_bop = 0;

	if (((stage.stage_id == StageId_5_2)) && (stage.song_step) >= 900)
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
	
	Stage_DrawTex(&this->tex_back4, &sunset_src, &sunset_dst, stage.camera.bzoom);
	}

	fx = stage.camera.x;
	fy = stage.camera.y;
	static const struct Back_Week5_LowerBop
	{
		RECT src;
		RECT_FIXED dst;
	} lbop_piece[] = {
	{{0, 0, 106, 105}, {FIXED_DEC(-120,1), FIXED_DEC(-60,1), FIXED_DEC(107,1), FIXED_DEC(105,1)}}, 
	};
	
	const struct Back_Week5_LowerBop *lbop_p = lbop_piece;
	for (size_t i = 0; i < COUNT_OF(lbop_piece); i++, lbop_p++)
	{
		RECT_FIXED lbop_dst = {
			lbop_p->dst.x - fx - (beat_bop << 1),
			lbop_p->dst.y - fy + (beat_bop << 3),
			lbop_p->dst.w + (beat_bop << 2),
			lbop_p->dst.h - (beat_bop << 3),
		};
		Stage_DrawTex(&this->tex_back2, &lbop_p->src, &lbop_dst, stage.camera.bzoom);
	}

		//Draw boppers 2
	fx = stage.camera.x;
	fy = stage.camera.y;
	static const struct Back_Week5_LowerBop2
	{
		RECT src;
		RECT_FIXED dst;
	} lbop_piece1[] = {
		{{0, 0, 197, 181}, {FIXED_DEC(-450,1), FIXED_DEC(-120,1), FIXED_DEC(197,1), FIXED_DEC(181,1)}},
		//done^^^^^^^^
	};
	
	const struct Back_Week5_LowerBop2 *lbop_p1 = lbop_piece1;
	for (size_t i = 0; i < COUNT_OF(lbop_piece); i++, lbop_p++)
	{
		RECT_FIXED lbop_dst1 = {
			lbop_p1->dst.x - fx - (beat_bop << 1),
			lbop_p1->dst.y - fy + (beat_bop << 3),
			lbop_p1->dst.w + (beat_bop << 2),
			lbop_p1->dst.h - (beat_bop << 3),
		};
		Stage_DrawTex(&this->tex_back3, &lbop_p1->src, &lbop_dst1, stage.camera.bzoom);
	}
	
}

void Back_week5_DrawMD(StageBack *back)
{
	Back_week5 *this = (Back_week5*)back;
	
	fixed_t fx, fy;

		fixed_t beat_bop;
	if ((stage.song_step & 0x3) == 0)
		beat_bop = FIXED_UNIT - ((stage.note_scroll / 24) & FIXED_LAND);
	else
		beat_bop = 0;
}

void Back_week5_DrawBG(StageBack *back)
{
	Back_week5 *this = (Back_week5*)back;
	
	fixed_t fx, fy;
		fixed_t beat_bop;
	if ((stage.song_step & 0x3) == 0)
		beat_bop = FIXED_UNIT - ((stage.note_scroll / 24) & FIXED_LAND);
	else
		beat_bop = 0;

			//Draw boppers
	fx = stage.camera.x;
	fy = stage.camera.y;
	static const struct Back_Week5_LowerBop
	{
		RECT src;
		RECT_FIXED dst;
	} lbop_piece[] = {
		{{175, 3, 74, 151}, {FIXED_DEC(83,1), FIXED_DEC(-77,1), FIXED_DEC(74,1), FIXED_DEC(151,1)}}, 
		{{108, 0, 45, 137}, {FIXED_DEC(30,1), FIXED_DEC(-80,1), FIXED_DEC(45,1), FIXED_DEC(137,1)}}, 
		{{151, 0, 23, 137}, {FIXED_DEC(60,1), FIXED_DEC(-80,1), FIXED_DEC(23,1), FIXED_DEC(137,1)}}, 
		{{0, 109, 41, 139}, {FIXED_DEC(157,1), FIXED_DEC(-119,1), FIXED_DEC(41,1), FIXED_DEC(191,1)}}, 
	};
	
	const struct Back_Week5_LowerBop *lbop_p = lbop_piece;
	for (size_t i = 0; i < COUNT_OF(lbop_piece); i++, lbop_p++)
	{
		RECT_FIXED lbop_dst = {
			lbop_p->dst.x - fx - (beat_bop << 1),
			lbop_p->dst.y - fy + (beat_bop << 3),
			lbop_p->dst.w + (beat_bop << 2),
			lbop_p->dst.h - (beat_bop << 3),
		};
		Stage_DrawTex(&this->tex_back2, &lbop_p->src, &lbop_dst, stage.camera.bzoom);
	}
	
	//Draw sunset
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT sunset_src = {0, 0, 256, 256};
	RECT_FIXED sunset_dst = {
		FIXED_DEC(-400 - SCREEN_WIDEOADD2,1) - fx,
		FIXED_DEC(-240,1) - fy,
		FIXED_DEC(600 + SCREEN_WIDEOADD,1),
		FIXED_DEC(350,1)
	};
	
	Stage_DrawTex(&this->tex_back0, &sunset_src, &sunset_dst, stage.camera.bzoom);
}

void Back_week5_Free(StageBack *back)
{
	Back_week5 *this = (Back_week5*)back;
	
	
	//Free structure
	Mem_Free(this);
}

StageBack *Back_week5_New(void)
{
	//Allocate background structure
	Back_week5 *this = (Back_week5*)Mem_Alloc(sizeof(Back_week5));
	if (this == NULL)
		return NULL;
	
	//Set background functions
	this->back.draw_fg = Back_week5_DrawFG;
	this->back.draw_md = Back_week5_DrawMD;
	this->back.draw_bg = Back_week5_DrawBG;
	this->back.free = Back_week5_Free;
	
	//Load background textures
	IO_Data arc_back = IO_Read("\\WEEK5\\BACK.ARC;1");
	Gfx_LoadTex(&this->tex_back0, Archive_Find(arc_back, "back0.tim"), 0);
	Gfx_LoadTex(&this->tex_back2, Archive_Find(arc_back, "back2.tim"), 0);
	Gfx_LoadTex(&this->tex_back3, Archive_Find(arc_back, "back3.tim"), 0);
	Gfx_LoadTex(&this->tex_back4, Archive_Find(arc_back, "back4.tim"), 0);
	Mem_Free(arc_back);
	
	
	return (StageBack*)this;
}
