/*
 * effect.c
 *
 *  Created on: Aug 9, 2018
 *      Author: sam
 */


#include "effect.h"

#define EFX_PRESET_NUM	10
efx_base_t efx_preset[EFX_PRESET_NUM]={
		{"DELAY",	"PING_PONG",	EFX_TYPE_FV1,	/*fv1 pins*/},
		{"DELAY",	"ONE-SHOT",		EFX_TYPE_FV1,	/*fv1 pins*/},
		{"DELAY",	"MONO",			EFX_TYPE_FV1,	/*fv1 pins*/},
		{"DELAY",	"STEREO",		EFX_TYPE_FV1,	/*fv1 pins*/},
		{"REVERB",	"PLATE1",		EFX_TYPE_FV1,	/*fv1 pins*/},
		{"REVERB",	"PLATE2",		EFX_TYPE_FV1,	/*fv1 pins*/},
		{"REVERB",	"SPRING1",		EFX_TYPE_FV1,	/*fv1 pins*/},
		{"REVERB",	"SPRING2",		EFX_TYPE_FV1,	/*fv1 pins*/},
		{"CHOROUS",	"POLY1",		EFX_TYPE_FV1,	/*fv1 pins*/},
		{"CHOROUS",	"POLY2",		EFX_TYPE_FV1,	/*fv1 pins*/},
};
