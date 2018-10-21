/*
 * effect_preset.c
 *
 *  Created on: Aug 9, 2018
 *      Author: sam
 */

//#include "effect_preset.h"
#include  "fv1.h"
#include "effect.h"

#define EFX_PRESET_STATIC


#ifdef EFX_PRESET_STATIC

/*
 * complete preset effects in static mode
 * */

efx_fv1_base_t *efx_preset_box[EFX_FV1_PRST_MAX] = {

		&((efx_fv1_base_t){ .name = "MONO ECHO 1", .comments = "PING_PONG",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_0, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "MONO ECHO 2", .comments = "ONE-SHOT",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_1, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "MONO ECHO 3", .comments = "MONO",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_2, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "MONO ECHO 4", .comments = "STEREO",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_3, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "MULTI PONG", .comments = "PLATE1",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_4, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "PING PONG", .comments = "PLATE2",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_5, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "ECHO + DELAY", .comments = "SPRING1",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_6, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "ECHO + REVERB", .comments = "SPRING2",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_7, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "VOICE DELAY", .comments = "POLY1",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_0, .eep = FV1_EEP_B})}),

		&((efx_fv1_base_t){ .name = "VOICE REVERB", .comments = "POLY2",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_1, .eep = FV1_EEP_B})}),

		&((efx_fv1_base_t){ .name = "HALL REVERB", .comments = "DRY-WET1",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_2, .eep = FV1_EEP_B})}),

		&((efx_fv1_base_t){ .name = "REVERB + FLNG", .comments = "DRY-WET1",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_3, .eep = FV1_EEP_B})}),

		&((efx_fv1_base_t){ .name = "ECHO + FLANG", .comments = "PLT-PLY1",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_4, .eep = FV1_EEP_B})}),

		&((efx_fv1_base_t){ .name = "VOICE FLANG", .comments = "PLT-PLY2",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_5, .eep = FV1_EEP_B})}),

		&((efx_fv1_base_t){ .name = "VOICE PLATE", .comments = "POLY1",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_6, .eep = FV1_EEP_B})}),

		&((efx_fv1_base_t){ .name = "VOICE CHUOROS", .comments = "POLY2",
			.vol_nums = 2, .volA_name = "REAPEAT", .volB_name = "TIME", .volC_name = NULL,
			.fv1 = &((fv1_type_t){ .pin = FV1_CODE_7, .eep = FV1_EEP_B})}),
};

#else

efx_fv1_base_t  *efx_preset_box[EFX_FV1_PRST_MAX];

char  *efx_preset_name[EFX_FV1_PRST_MAX]={
	"DELAY",
	"DELAY",
	"DELAY",
	"DELAY",
	"REVERB",
	"REVERB",
	"REVERB",
	"REVERB",
	"CHOROUS",
	"CHOROUS",
	"DLY-CHR",
	"DLY-CHR",
	"RVB-CHR",
	"RVB-CHR",
	"DLY-RVB",
	"DLY-RVB"
};

char *efx_preset_comment[EFX_FV1_PRST_MAX] = {
	"PING_PONG",
	"ONE-SHOT",
	"MONO",
	"STEREO",
	"PLATE1",
	"PLATE2",
	"SPRING1",
	"SPRING2",
	"POLY1",
	"POLY2",
	"DRY-WET1",
	"DRY-WET2",
	"PLA-PLY1",
	"PLA-PLY2",
	"POLY1",
	"POLY2"
};





void efx_init_preset_box(void){

	for (fv1_eep_t eep = FV1_EEP_RESET; eep < FV1_EEP_B; ++eep) {
		for (fv1_code_t code = FV1_CODE_0; code <= FV1_CODE_7; ++code) {

			efx_fv1_base_t *base = malloc(sizeof(*base));
			fv1_type_t *type = malloc(sizeof(*base));
			/*TODO: check malloc*/
			if(!base || !type){
				_Error_Handler(__FILE__, __LINE__);
				return;
			}
			type->eep = eep + 1;
			type->pin = code;

			base->name = efx_preset_name[(eep * FV1_CODE_7) + code];
			base->comments = efx_preset_comment[(eep * FV1_CODE_7) + code];
			base->fv1 = type;

			efx_preset_box[(eep * FV1_CODE_7) + code] = base;
		}
	}
}

void efx_deinit_preset_box(void){

	for (fv1_eep_t eep = FV1_EEP_RESET; eep < FV1_EEP_B; ++eep) {
		for (fv1_code_t code = FV1_CODE_0; code <= FV1_CODE_7; ++code) {

			efx_fv1_base_t *base = efx_preset_box[(eep * FV1_CODE_7) + code];

			free(base->fv1);
			free(base);
		}
	}
}

#endif

efx_fv1_base_t* efx_get_fv1_effect(efx_fv1_preset pst){
	return (efx_preset_box[pst]);
}
