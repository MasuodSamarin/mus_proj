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

		&((efx_fv1_base_t){ .name = "DELAY", .comments = "PING_PONG",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_0, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "DELAY", .comments = "ONE-SHOT",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_1, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "REVERB", .comments = "MONO",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_2, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "REVERB", .comments = "STEREO",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_3, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "REVERB", .comments = "PLATE1",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_4, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "REVERB", .comments = "PLATE2",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_5, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "CHOROUS", .comments = "SPRING1",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_6, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "CHOROUS", .comments = "SPRING2",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_7, .eep = FV1_EEP_A})}),

		&((efx_fv1_base_t){ .name = "DLY-CHR", .comments = "POLY1",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_0, .eep = FV1_EEP_B})}),

		&((efx_fv1_base_t){ .name = "DLY-CHR", .comments = "POLY2",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_1, .eep = FV1_EEP_B})}),

		&((efx_fv1_base_t){ .name = "RVB-CHR", .comments = "DRY-WET1",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_2, .eep = FV1_EEP_B})}),

		&((efx_fv1_base_t){ .name = "RVB-CHR", .comments = "DRY-WET1",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_3, .eep = FV1_EEP_B})}),

		&((efx_fv1_base_t){ .name = "DLY-RVB", .comments = "PLT-PLY1",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_4, .eep = FV1_EEP_B})}),

		&((efx_fv1_base_t){ .name = "DLY-RVB", .comments = "PLT-PLY2",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_5, .eep = FV1_EEP_B})}),

		&((efx_fv1_base_t){ .name = "DELAY", .comments = "POLY1",
								.fv1 = &((fv1_type_t){ .pin = FV1_CODE_6, .eep = FV1_EEP_B})}),

		&((efx_fv1_base_t){ .name = "DELAY", .comments = "POLY2",
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
