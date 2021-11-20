/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "xmasp.h"

#include "../mem.h"
#include "../archive.h"
#include "../stage.h"
#include "../main.h"

//Christmas Parents structure
enum
{
	XmasP_ArcMain_Idle0,
	XmasP_ArcMain_Idle1,
	XmasP_ArcMain_Idle2,
	XmasP_ArcMain_Idle3,
	XmasP_ArcMain_LeftA0,
	XmasP_ArcMain_LeftA1,
	XmasP_ArcMain_LeftB0,
	XmasP_ArcMain_LeftB1,
	XmasP_ArcMain_DownA0,
	XmasP_ArcMain_DownA1,
	XmasP_ArcMain_DownB0,
	XmasP_ArcMain_DownB1,
	XmasP_ArcMain_UpA0,
	XmasP_ArcMain_UpA1,
	XmasP_ArcMain_UpB0,
	XmasP_ArcMain_UpB1,
	XmasP_ArcMain_RightA0,
	XmasP_ArcMain_RightA1,
	XmasP_ArcMain_Nyaw0,
	XmasP_ArcMain_Nyaw1,
	XmasP_ArcMain_Nyaw2,
	XmasP_ArcMain_Nyaw3,
	XmasP_ArcMain_Out0,
	XmasP_ArcMain_Out1,
	XmasP_ArcMain_Out2,
	XmasP_ArcMain_Mad0,
	XmasP_ArcMain_Mad1,
	XmasP_ArcMain_Mad2,
	XmasP_ArcMain_Mad3,
	XmasP_ArcMain_Mad4,
	XmasP_ArcMain_Mad5,
	XmasP_ArcMain_Mad6,
	XmasP_ArcMain_Mad7,
	XmasP_ArcMain_Mad8,
	XmasP_ArcMain_Mad9,
	
	XmasP_Arc_Max,


};

typedef struct
{
	//Character base structure
	Character character;
	
	//Render data and state
	IO_Data arc_main;
	IO_Data arc_ptr[XmasP_Arc_Max];
	
	Gfx_Tex tex;
	u8 frame, tex_id;
} Char_XmasP;

//Christmas Parents definitions
static const CharFrame char_xmasp_frame[] = {
	{XmasP_ArcMain_Idle0, {0,   0, 219, 195}, {128, 179}}, //0 idle 1
	{XmasP_ArcMain_Idle1, {0,   0, 219, 191}, {128, 179}}, //1 idle 2
	{XmasP_ArcMain_Idle2, {0,   0, 221, 192}, {130, 179}}, //2 idle 3
	{XmasP_ArcMain_Idle3, {0,   0, 217, 196}, {130, 178}}, //3 idle 4
	
	{XmasP_ArcMain_LeftA0, {0,   0, 214, 190}, {128, 177}}, //4 left a 1
	{XmasP_ArcMain_LeftA1, {0,   0, 214, 190}, {128, 177}}, //5 left a 2
	{XmasP_ArcMain_LeftB0, {0,   0, 197, 200}, {122, 188}}, //6 left b 1
	{XmasP_ArcMain_LeftB1, {0,   0, 201, 200}, {125, 188}}, //7 left b 2
	
	{XmasP_ArcMain_DownA0, {0,   0, 214, 190}, {128, 177}}, //8 down a 1
	{XmasP_ArcMain_DownA1, {0,   0, 214, 190}, {128, 177}}, //9 down a 2
	{XmasP_ArcMain_DownB0, {0,   0, 213, 189}, {121, 177}}, //10 down b 1
	{XmasP_ArcMain_DownB1, {0,   0, 213, 190}, {123, 178}}, //11 down b 2
	
	{XmasP_ArcMain_UpA0, {0,   0, 214, 190}, {128, 177}}, //12 up a 1
	{XmasP_ArcMain_UpA1, {0,   0, 214, 190}, {128, 177}}, //13 up a 2
	{XmasP_ArcMain_UpB0, {0,   0, 197, 204}, {117, 191}}, //14 up b 1
	{XmasP_ArcMain_UpB1, {0,   0, 201, 202}, {119, 190}}, //15 up b 2
	
	{XmasP_ArcMain_RightA0, {0,   0, 214, 190}, {128, 177}}, //16 right a 1
	{XmasP_ArcMain_RightA1, {0,   0, 214, 190}, {128, 177}}, //17 right a 2

	{XmasP_ArcMain_Nyaw0, {0,   0, 214, 190}, {130, 178}}, //19 right b 2
	{XmasP_ArcMain_Nyaw1, {0,   0, 214, 190}, {130, 178}}, //19 right b 2
	{XmasP_ArcMain_Nyaw2, {0,   0, 214, 190}, {130, 178}}, //19 right b 2
	{XmasP_ArcMain_Nyaw3, {0,   0, 214, 190}, {130, 178}}, //19 right b 2

	{XmasP_ArcMain_Out0, {0,   0, 160, 150}, { 96, 136}}, //19 right b 2
	{XmasP_ArcMain_Out1, {0,   0, 160, 150}, { 98, 136}}, //19 right b 2
	{XmasP_ArcMain_Out2, {0,   0, 260, 150}, {100, 136}}, //19 right b 2

	{XmasP_ArcMain_Mad0, {0,   0, 180, 188}, {100, 179}}, //19 right b 2
	{XmasP_ArcMain_Mad1, {0,   0, 180, 188}, { 98, 177}}, //19 right b 2
	{XmasP_ArcMain_Mad2, {0,   0, 180, 188}, {100, 177}}, //19 right b 2
	{XmasP_ArcMain_Mad3, {0,   0, 180, 188}, { 92, 176}}, //19 right b 2
	{XmasP_ArcMain_Mad4, {0,   0, 180, 188}, { 92, 176}}, //19 right b 2
	{XmasP_ArcMain_Mad5, {0,   0, 180, 188}, { 93, 178}}, //19 right b 2
	{XmasP_ArcMain_Mad6, {0,   0, 180, 188}, { 94, 177}}, //19 right b 2
	{XmasP_ArcMain_Mad7, {0,   0, 180, 188}, { 94, 177}}, //19 right b 2
	{XmasP_ArcMain_Mad8, {0,   0, 180, 188}, { 94, 177}}, //19 right b 2
	{XmasP_ArcMain_Mad9, {0,   0, 180, 188}, { 94, 173}}, //19 right b 2
};

static const Animation char_xmasp_anim[CharAnim_Max] = {
	{2, (const u8[]){ 0,  1,  2,  3, ASCR_BACK, 1}}, //CharAnim_Idle
	{2, (const u8[]){ 4,  5, ASCR_BACK, 1}},         //CharAnim_Left
	{2, (const u8[]){22, 22, 23, 23, 24, 24, 24, 24, ASCR_BACK, 1}},  //CharAnim_LeftAlt
	{2, (const u8[]){ 8,  9, ASCR_BACK, 1}},         //CharAnim_Down
	{2, (const u8[]){10, 11, ASCR_BACK, 1}},         //CharAnim_DownAlt
	{2, (const u8[]){12, 13, ASCR_BACK, 1}},         //CharAnim_Up
	{2, (const u8[]){22, 22, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, ASCR_BACK, 1}},  //CharAnim_UpAlt
	{2, (const u8[]){16, 17, ASCR_BACK, 1}},         //CharAnim_Right
	{1, (const u8[]){19, 20, 20, 21, 21, ASCR_BACK, 1}},         //CharAnim_RightAlt
	{2, (const u8[]){22, 22, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, ASCR_BACK, 1}}, //CharAnim_Special
	{1, (const u8[]){25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, ASCR_BACK, 1}},         //CharAnim_Special2
};

//Christmas Parents functions
void Char_XmasP_SetFrame(void *user, u8 frame)
{
	Char_XmasP *this = (Char_XmasP*)user;
	
	//Check if this is a new frame
	if (frame != this->frame)
	{
		//Check if new art shall be loaded
		const CharFrame *cframe = &char_xmasp_frame[this->frame = frame];
		if (cframe->tex != this->tex_id)
			Gfx_LoadTex(&this->tex, this->arc_ptr[this->tex_id = cframe->tex], 0);
	}
}

void Char_XmasP_Tick(Character *character)
{
	Char_XmasP *this = (Char_XmasP*)character;
	
	//Perform idle dance
	if ((character->pad_held & (INPUT_LEFT | INPUT_DOWN | INPUT_UP | INPUT_RIGHT)) == 0)
		Character_PerformIdle(character);



    //Stage specific animations
		if (stage.note_scroll >= 0)
		{
			switch (stage.stage_id)
			{
				case StageId_1_4: //Tight Bars 
					if ((stage.song_step) == 125)
					character->set_anim(character, CharAnim_RightAlt);
					if ((stage.song_step) == 541)
						character->set_anim(character, CharAnim_RightAlt);
					if ((stage.song_step) == 812)
						character->set_anim(character, CharAnim_RightAlt);
					if ((stage.song_step) == 1453)
						character->set_anim(character, CharAnim_RightAlt);
					if ((stage.song_step) == 1745)
				    	character->set_anim(character, CharAnim_Special);
					break;
				case StageId_1_2:
				    if ((stage.song_step) == 1381)
						character->set_anim(character, CharAnim_Special2);
					break;

				default:
					break;
			}
		}
	
	
	//Animate and draw
	Animatable_Animate(&character->animatable, (void*)this, Char_XmasP_SetFrame);
	Character_Draw(character, &this->tex, &char_xmasp_frame[this->frame]);
}

void Char_XmasP_SetAnim(Character *character, u8 anim)
{
	//Set animation
	Animatable_SetAnim(&character->animatable, anim);
	Character_CheckStartSing(character);
}

void Char_XmasP_Free(Character *character)
{
	Char_XmasP *this = (Char_XmasP*)character;
	
	//Free art
	Mem_Free(this->arc_main);
}

Character *Char_XmasP_New(fixed_t x, fixed_t y)
{
	//Allocate Christmas Parents object
	Char_XmasP *this = Mem_Alloc(sizeof(Char_XmasP));
	if (this == NULL)
	{
		sprintf(error_msg, "[Char_XmasP_New] Failed to allocate Christmas Parents object");
		ErrorLock();
		return NULL;
	}
	
	//Initialize character
	this->character.tick = Char_XmasP_Tick;
	this->character.set_anim = Char_XmasP_SetAnim;
	this->character.free = Char_XmasP_Free;
	
	Animatable_Init(&this->character.animatable, char_xmasp_anim);
	Character_Init((Character*)this, x, y);
	
	//Set character information
	this->character.spec = 0;
	
	this->character.health_i = 5;
	
	this->character.focus_x = FIXED_DEC(70,1);
	this->character.focus_y = FIXED_DEC(-75,1);
	this->character.focus_zoom = FIXED_DEC(1,1);
	
	//Load art
	this->arc_main = IO_Read("\\CHAR\\XMASP.ARC;1");
	
	const char **pathp = (const char *[]){
		"idle0.tim",   //XmasP_ArcMain_Idle0
		"idle1.tim",   //XmasP_ArcMain_Idle1
		"idle2.tim",   //XmasP_ArcMain_Idle2
		"idle3.tim",   //XmasP_ArcMain_Idle3
		"lefta0.tim",  //XmasP_ArcMain_LeftA0
		"lefta1.tim",  //XmasP_ArcMain_LeftA1
		"leftb0.tim",  //XmasP_ArcMain_LeftB0
		"leftb1.tim",  //XmasP_ArcMain_LeftB1
		"downa0.tim",  //XmasP_ArcMain_DownA0
		"downa1.tim",  //XmasP_ArcMain_DownA1
		"downb0.tim",  //XmasP_ArcMain_DownB0
		"downb1.tim",  //XmasP_ArcMain_DownB1
		"upa0.tim",    //XmasP_ArcMain_UpA0
		"upa1.tim",    //XmasP_ArcMain_UpA1
		"upb0.tim",    //XmasP_ArcMain_UpB0
		"upb1.tim",    //XmasP_ArcMain_UpB1
		"righta0.tim", //XmasP_ArcMain_RightA0
		"righta1.tim", //XmasP_ArcMain_RightA1
		"nyaw0.tim", //XmasP_ArcMain_RightA0
		"nyaw1.tim", //XmasP_ArcMain_RightA1
		"nyaw2.tim", //XmasP_ArcMain_RightB0
		"nyaw3.tim", //XmasP_ArcMain_RightB1
		"out0.tim", //XmasP_ArcMain_RightA0
		"out1.tim", //XmasP_ArcMain_RightA1
		"out2.tim", //XmasP_ArcMain_RightB0
		"mad0.tim", //XmasP_ArcMain_RightA0
		"mad1.tim", //XmasP_ArcMain_RightA1
		"mad2.tim", //XmasP_ArcMain_RightB0
		"mad3.tim", //XmasP_ArcMain_RightB1
		"mad4.tim", //XmasP_ArcMain_RightA0
		"mad5.tim", //XmasP_ArcMain_RightA1
		"mad6.tim", //XmasP_ArcMain_RightB0
		"mad7.tim", //XmasP_ArcMain_RightB1
		"mad8.tim", //XmasP_ArcMain_RightB1
		"mad9.tim", //XmasP_ArcMain_RightB1
		NULL
	};
	IO_Data *arc_ptr = this->arc_ptr;
	for (; *pathp != NULL; pathp++)
		*arc_ptr++ = Archive_Find(this->arc_main, *pathp);
	
	//Initialize render state
	this->tex_id = this->frame = 0xFF;
	
	return (Character*)this;
}
