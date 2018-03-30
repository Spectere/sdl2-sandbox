/* palette-cga.h - Default CGA text mode color palette. */

#ifndef _PALETTE_CGA_H_
#define _PALETTE_CGA_H_

#include <SDL.h>

#include "video.h"

static const Uint8 PALETTE_CGA[48] = {
	0x00, 0x00, 0x00,	/* 0x00 */
	0x00, 0x00, 0xAA,	/* 0x01 */
	0x00, 0xAA, 0x00,	/* 0x02 */
	0x00, 0xAA, 0xAA,	/* 0x03 */
	0xAA, 0x00, 0x00,	/* 0x04 */
	0xAA, 0x00, 0xAA,	/* 0x05 */
	0xAA, 0x55, 0x00,	/* 0x06 */
	0xAA, 0xAA, 0xAA,	/* 0x07 */
	0x55, 0x55, 0x55,	/* 0x08 */
	0x55, 0x55, 0xFF,	/* 0x09 */
	0x55, 0xFF, 0x55,	/* 0x0A */
	0x55, 0xFF, 0xFF,	/* 0x0B */
	0xFF, 0x55, 0x55,	/* 0x0C */
	0xFF, 0x55, 0xFF,	/* 0x0D */
	0xFF, 0xFF, 0x55,	/* 0x0E */
	0xFF, 0xFF, 0xFF	/* 0x0F */
};

#endif /* _PALETTE_CGA_H_ */
