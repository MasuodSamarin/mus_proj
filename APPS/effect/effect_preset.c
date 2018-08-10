/*
 * effect_preset.c
 *
 *  Created on: Aug 9, 2018
 *      Author: sam
 */

#include "effect.h"
#include "effect_preset.h"
#include  "fv1.h"



/*
 * complete preset effects
 * */
efx_fv1_base_t efx_preset_box[EFX_FV1_PRST_MAX]={
		{"DELAY",	"PING_PONG",	(fv1_type_t){.pin = FV1_CODE_0, .eep = FV1_EEP_A}},
		{"DELAY",	"ONE-SHOT",		(fv1_type_t){.pin = FV1_CODE_1, .eep = FV1_EEP_A}},
		{"DELAY",	"MONO",			(fv1_type_t){.pin = FV1_CODE_2, .eep = FV1_EEP_A}},
		{"DELAY",	"STEREO",		(fv1_type_t){.pin = FV1_CODE_3, .eep = FV1_EEP_A}},
		{"REVERB",	"PLATE1",		(fv1_type_t){.pin = FV1_CODE_4, .eep = FV1_EEP_A}},
		{"REVERB",	"PLATE2",		(fv1_type_t){.pin = FV1_CODE_5, .eep = FV1_EEP_A}},
		{"REVERB",	"SPRING1",		(fv1_type_t){.pin = FV1_CODE_6, .eep = FV1_EEP_A}},
		{"REVERB",	"SPRING2",		(fv1_type_t){.pin = FV1_CODE_7, .eep = FV1_EEP_A}},
		{"CHOROUS",	"POLY1",		(fv1_type_t){.pin = FV1_CODE_0, .eep = FV1_EEP_B}},
		{"CHOROUS",	"POLY2",		(fv1_type_t){.pin = FV1_CODE_1, .eep = FV1_EEP_B}},
		{"DLY-CHR",	"DRY-WET1",		(fv1_type_t){.pin = FV1_CODE_2, .eep = FV1_EEP_B}},
		{"DLY-CHR",	"DRY-WET2",		(fv1_type_t){.pin = FV1_CODE_3, .eep = FV1_EEP_B}},
		{"RVB-CHR",	"PLA-PLY1",		(fv1_type_t){.pin = FV1_CODE_4, .eep = FV1_EEP_B}},
		{"RVB-CHR",	"PLA-PLY2",		(fv1_type_t){.pin = FV1_CODE_5, .eep = FV1_EEP_B}},
		{"DLY-RVB",	"POLY1",		(fv1_type_t){.pin = FV1_CODE_6, .eep = FV1_EEP_B}},
		{"DLY-RVB",	"POLY2",		(fv1_type_t){.pin = FV1_CODE_7, .eep = FV1_EEP_B}},
};
