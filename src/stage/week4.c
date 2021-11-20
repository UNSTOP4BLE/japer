/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "week4.h"

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

	
	Gfx_Tex tex_back0; //Foreground limo
	Gfx_Tex tex_back1; //bop bois
	Gfx_Tex tex_back2; //Sunset

	//Car state
	fixed_t car_x;
	fixed_t car_timer;

} Back_Week4;

//Week 4 background functions
#define CAR_START_X FIXED_DEC(-500,1)
#define CAR_END_X    FIXED_DEC(500,1)
#define CAR_TIME_A FIXED_DEC(5,1)
#define CAR_TIME_B FIXED_DEC(14,1)
	

void Back_Week4_DrawFG(StageBack *back)
{
	Back_Week4 *this = (Back_Week4*)back;
	
	//Move car
	this->car_timer -= timer_dt;
	if (this->car_timer <= 0)
	{
		this->car_timer = RandomRange(CAR_TIME_A, CAR_TIME_B);
		this->car_x = CAR_START_X;
	}
	
	if (this->car_x < CAR_END_X)
		this->car_x += timer_dt * 2700;
	


}

void Back_Week4_DrawMD(StageBack *back)
{
	Back_Week4 *this = (Back_Week4*)back;
	
	fixed_t fx, fy;
	
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
}

void Back_Week4_DrawBG(StageBack *back)
{
	Back_Week4 *this = (Back_Week4*)back;
	
	fixed_t fx, fy;
	
	fixed_t beat_bop;
	if ((stage.song_step & 0x3) == 0)
		beat_bop = FIXED_UNIT - ((stage.note_scroll / 24) & FIXED_LAND);
	else
		beat_bop = 0;

	//Draw boppers
		fx = stage.camera.x;
	fy = stage.camera.y;
	
	static const struct Back_Week4_LowerBop
	{
		RECT src;
		RECT_FIXED dst;
	} lbop_piece[] = {
		{{0, 0, 80, 102}, {FIXED_DEC(-315,1), FIXED_DEC(-50,1), FIXED_DEC(80,1), FIXED_DEC(102,1)}},
		{{175, 3, 74, 151}, {FIXED_DEC(-120,1), FIXED_DEC(-80,1), FIXED_DEC(74,1), FIXED_DEC(151,1)}},
		{{81, 0, 70, 128}, {FIXED_DEC(30,1), FIXED_DEC(-70,1), FIXED_DEC(70,1), FIXED_DEC(128,1)}},
		{{151, 0, 23, 132}, {FIXED_DEC(100,1), FIXED_DEC(-70,1), FIXED_DEC(23,1), FIXED_DEC(132,1)}},
		{{0, 109, 41, 139}, {FIXED_DEC(123,1), FIXED_DEC(-69,1), FIXED_DEC(41,1), FIXED_DEC(139,1)}},
		{{41, 126, 69, 130}, {FIXED_DEC(164,1), FIXED_DEC(-52,1), FIXED_DEC(69,1), FIXED_DEC(130,1)}},
	};
	
	const struct Back_Week4_LowerBop *lbop_p = lbop_piece;
	for (size_t i = 0; i < COUNT_OF(lbop_piece); i++, lbop_p++)
	{
		RECT_FIXED lbop_dst = {
			lbop_p->dst.x - fx - (beat_bop << 1),
			lbop_p->dst.y - fy + (beat_bop << 3),
			lbop_p->dst.w + (beat_bop << 2),
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

void Back_Week4_Free(StageBack *back) 
{
	Back_Week4 *this = (Back_Week4*)back;

	//Free structure
	Mem_Free(this);
}

StageBack *Back_Week4_New(void)
{
	//Allocate background structure
	Back_Week4 *this = (Back_Week4*)Mem_Alloc(sizeof(Back_Week4));
	if (this == NULL)
		return NULL;
	
	//Set background functions
	this->back.draw_fg = Back_Week4_DrawFG;
	this->back.draw_md = Back_Week4_DrawMD;
	this->back.draw_bg = Back_Week4_DrawBG;
	this->back.free = Back_Week4_Free;
	
	//Load background textures
	IO_Data arc_back = IO_Read("\\WEEK4\\BACK.ARC;1");
	Gfx_LoadTex(&this->tex_back0, Archive_Find(arc_back, "back0.tim"), 0);
	Gfx_LoadTex(&this->tex_back1, Archive_Find(arc_back, "back1.tim"), 0);
	Gfx_LoadTex(&this->tex_back2, Archive_Find(arc_back, "back2.tim"), 0);
	Mem_Free(arc_back);
	
	//Load henchmen textures
	//Initialize car state
	this->car_x = CAR_END_X;
	this->car_timer = RandomRange(CAR_TIME_A, CAR_TIME_B);
	
	//Initialize henchmen state
	
	return (StageBack*)this;
}
