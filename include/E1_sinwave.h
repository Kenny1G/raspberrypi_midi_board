// 256 entry wave table for an 8-bit sine wave for E1 note
#include <stdint.h>

const uint8_t  E1_sinewave[] =
{
0x80, 0x82, 0x84, 0x87, 0x89, 0x8b, 0x8e, 0x90,
0x92, 0x95, 0x97, 0x99, 0x9c, 0x9e, 0xa0, 0xa2,
0xa5, 0xa7, 0xa9, 0xab, 0xae, 0xb0, 0xb2, 0xb4,
0xb6, 0xb8, 0xba, 0xbd, 0xbf, 0xc1, 0xc3, 0xc5,
0xc7, 0xc9, 0xca, 0xcc, 0xce, 0xd0, 0xd2, 0xd4,
0xd5, 0xd7, 0xd9, 0xdb, 0xdc, 0xde, 0xdf, 0xe1,
0xe2, 0xe4, 0xe5, 0xe7, 0xe8, 0xe9, 0xeb, 0xec,
0xed, 0xee, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5,
0xf6, 0xf7, 0xf7, 0xf8, 0xf9, 0xfa, 0xfa, 0xfb,
0xfc, 0xfc, 0xfd, 0xfd, 0xfe, 0xfe, 0xfe, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfd,
0xfd, 0xfd, 0xfc, 0xfb, 0xfb, 0xfa, 0xfa, 0xf9,
0xf8, 0xf7, 0xf6, 0xf5, 0xf5, 0xf4, 0xf3, 0xf2,
0xf0, 0xef, 0xee, 0xed, 0xec, 0xea, 0xe9, 0xe8,
0xe6, 0xe5, 0xe4, 0xe2, 0xe0, 0xdf, 0xdd, 0xdc,
0xda, 0xd8, 0xd7, 0xd5, 0xd3, 0xd1, 0xd0, 0xce,
0xcc, 0xca, 0xc8, 0xc6, 0xc4, 0xc2, 0xc0, 0xbe,
0xbc, 0xba, 0xb8, 0xb6, 0xb3, 0xb1, 0xaf, 0xad,
0xab, 0xa9, 0xa6, 0xa4, 0xa2, 0x9f, 0x9d, 0x9b,
0x99, 0x96, 0x94, 0x92, 0x8f, 0x8d, 0x8b, 0x88,
0x86, 0x84, 0x81, 0x7f, 0x7d, 0x7a, 0x78, 0x75,
0x73, 0x71, 0x6e, 0x6c, 0x6a, 0x67, 0x65, 0x63,
0x61, 0x5e, 0x5c, 0x5a, 0x58, 0x55, 0x53, 0x51,
0x4f, 0x4d, 0x4a, 0x48, 0x46, 0x44, 0x42, 0x40,
0x3e, 0x3c, 0x3a, 0x38, 0x36, 0x34, 0x32, 0x30,
0x2e, 0x2d, 0x2b, 0x29, 0x27, 0x26, 0x24, 0x22,
0x21, 0x1f, 0x1e, 0x1c, 0x1b, 0x19, 0x18, 0x17,
0x15, 0x14, 0x13, 0x11, 0x10, 0xf, 0xe, 0xd, 
0xc, 0xb, 0xa, 0x9, 0x8, 0x7, 0x7, 0x6, 
0x5, 0x4, 0x4, 0x3, 0x3, 0x2, 0x2, 0x1, 
0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};