// 256 entry wave table for an 8-bit sine wave for DS1 note
#include <stdint.h>

const uint8_t  DS1_sinewave[] =
{
0x80, 0x82, 0x84, 0x86, 0x88, 0x8b, 0x8d, 0x8f,
0x91, 0x94, 0x96, 0x98, 0x9a, 0x9c, 0x9f, 0xa1,
0xa3, 0xa5, 0xa7, 0xa9, 0xab, 0xad, 0xb0, 0xb2,
0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe, 0xc0, 0xc2,
0xc4, 0xc5, 0xc7, 0xc9, 0xcb, 0xcd, 0xce, 0xd0,
0xd2, 0xd4, 0xd5, 0xd7, 0xd9, 0xda, 0xdc, 0xdd,
0xdf, 0xe0, 0xe2, 0xe3, 0xe5, 0xe6, 0xe7, 0xe9,
0xea, 0xeb, 0xec, 0xed, 0xef, 0xf0, 0xf1, 0xf2,
0xf3, 0xf4, 0xf5, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9,
0xf9, 0xfa, 0xfb, 0xfb, 0xfc, 0xfc, 0xfd, 0xfd,
0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xfe, 0xfe, 0xfe, 0xfd, 0xfd, 0xfd, 0xfc,
0xfc, 0xfb, 0xfa, 0xfa, 0xf9, 0xf8, 0xf8, 0xf7,
0xf6, 0xf5, 0xf4, 0xf3, 0xf2, 0xf1, 0xf0, 0xef,
0xee, 0xed, 0xec, 0xea, 0xe9, 0xe8, 0xe7, 0xe5,
0xe4, 0xe2, 0xe1, 0xe0, 0xde, 0xdd, 0xdb, 0xd9,
0xd8, 0xd6, 0xd4, 0xd3, 0xd1, 0xcf, 0xce, 0xcc,
0xca, 0xc8, 0xc6, 0xc4, 0xc3, 0xc1, 0xbf, 0xbd,
0xbb, 0xb9, 0xb7, 0xb5, 0xb3, 0xb1, 0xaf, 0xac,
0xaa, 0xa8, 0xa6, 0xa4, 0xa2, 0xa0, 0x9d, 0x9b,
0x99, 0x97, 0x95, 0x92, 0x90, 0x8e, 0x8c, 0x8a,
0x87, 0x85, 0x83, 0x81, 0x7e, 0x7c, 0x7a, 0x78,
0x75, 0x73, 0x71, 0x6f, 0x6c, 0x6a, 0x68, 0x66,
0x64, 0x62, 0x5f, 0x5d, 0x5b, 0x59, 0x57, 0x55,
0x53, 0x50, 0x4e, 0x4c, 0x4a, 0x48, 0x46, 0x44,
0x42, 0x40, 0x3e, 0x3c, 0x3b, 0x39, 0x37, 0x35,
0x33, 0x31, 0x30, 0x2e, 0x2c, 0x2a, 0x29, 0x27,
0x26, 0x24, 0x22, 0x21, 0x1f, 0x1e, 0x1d, 0x1b,
0x1a, 0x18, 0x17, 0x16, 0x15, 0x13, 0x12, 0x11,
0x10, 0xf, 0xe, 0xd, 0xc, 0xb, 0xa, 0x9, 
0x8, 0x7, 0x7, 0x6, 0x5, 0x5, 0x4, 0x3
};
