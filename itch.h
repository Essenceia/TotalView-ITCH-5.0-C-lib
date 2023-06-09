#ifndef ITCH_H
#define ITCH_H
#include "itch_s.h"
#include <stddef.h>
#define _BSD_SOURCE
#include <endian.h>
#include <stdio.h>

static inline void print_char_t(const char *name, char_t b){ printf("%s %c\n",name,b);}

#define PRINT_CHAR_X_T(X) \
static inline void print_char_##X##_t(const char *name, uint8_t b[ X ]){ \
	printf("%s ", name); \
	for( int i = 0; i < X; i++)printf("%c", b[i]); \
	printf("\n");	\
}

PRINT_CHAR_X_T(2)
PRINT_CHAR_X_T(4)
PRINT_CHAR_X_T(6) // u48_t
PRINT_CHAR_X_T(8)
PRINT_CHAR_X_T(10)
PRINT_CHAR_X_T(20)

static inline void print_u8_t(const char *name, u8_t b){ printf("%s 0x%02x\n",name, b);}

static inline void print_u16_t(const char *name, u16_t b){ printf("%s 0x%04x\n",name,be16toh(b));}
static inline void print_u32_t(const char *name, u32_t b){ printf("%s 0x%08x\n",name,be32toh(b));}
static inline void print_u64_t(const char *name, u64_t b){ printf("%s 0x%016lx\n",name,be64toh(b));}

static inline void print_u48_t(const char *name, u48_t b){ 
	// convert to little endian
	uint8_t b_le[6];
	int h, l;
	h = 5;
	l = 0;
	for( ; h<l; h--, l++){
		b_le[h] = b[l];
		b_le[l] = b[h];
	}
	printf("%s 0x", name);
	for( int i = 5; i > -1; i--)printf("%02x", b_le[i]);
	printf("\n");
}

static inline void print_price_4_t(const char *name, price_4_t b){ printf("%s 0x%08x\n",name,be32toh(b));}
static inline void print_price_8_t(const char *name, price_8_t b){ printf("%s 0x%016lx\n",name,be64toh(b));}

// fill the field of the itch structure corresponding to the
// message type
int  fill_tv_itch5(char msg_type, void* data, size_t data_len, tv_itch5_s *itch_s);

// print the currently valid itch message type
void print_tv_itch5_msg_type(const tv_itch5_s * itch_msg);

void print_tv_itch5(const tv_itch5_s* itch_msg);
#endif // ITCH_H
