/*
 * effect.h
 *
 *  Created on: Aug 9, 2018
 *      Author: sam
 */

#ifndef EFFECT_H_
#define EFFECT_H_


typedef struct {
	// effect number (0-99)
	// effect names	{from a list of effects}
	// effect comments {some explain to show in lcd}

	// effect types union {spin, isd117xx}

	// effect mode {user-defined, system-preset}

	// volumes and pwm's {input volume reading, output pwm's value}

	// spins and eep's {4 pin for spin, 2 pind for power of eep's}

	// effect status {enable, disable}

} efx_handle_t;
#endif /* EFFECT_H_ */
