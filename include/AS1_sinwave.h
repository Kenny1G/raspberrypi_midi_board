// 256 entry wave table for an 8-bit sine wave for AS1
#include <stdint.h>

const uint8_t  AS1_sinewave[] =
{
0x80, 0x83, 0x86, 0x89, 0x8d, 0x90, 0x93, 0x97,
0x9a, 0x9d, 0xa0, 0xa4, 0xa7, 0xaa, 0xad, 0xb0,
0xb3, 0xb6, 0xb9, 0xbc, 0xbf, 0xc2, 0xc5, 0xc8,
0xca, 0xcd, 0xd0, 0xd2, 0xd5, 0xd7, 0xda, 0xdc,
0xde, 0xe0, 0xe3, 0xe5, 0xe7, 0xe9, 0xea, 0xec,
0xee, 0xf0, 0xf1, 0xf3, 0xf4, 0xf5, 0xf7, 0xf8,
0xf9, 0xfa, 0xfb, 0xfc, 0xfc, 0xfd, 0xfe, 0xfe,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xfe, 0xfe, 0xfd, 0xfc, 0xfb, 0xfb,
0xfa, 0xf9, 0xf7, 0xf6, 0xf5, 0xf4, 0xf2, 0xf1,
0xef, 0xed, 0xec, 0xea, 0xe8, 0xe6, 0xe4, 0xe2,
0xe0, 0xde, 0xdb, 0xd9, 0xd6, 0xd4, 0xd1, 0xcf,
0xcc, 0xca, 0xc7, 0xc4, 0xc1, 0xbe, 0xbb, 0xb8,
0xb5, 0xb2, 0xaf, 0xac, 0xa9, 0xa6, 0xa3, 0x9f,
0x9c, 0x99, 0x96, 0x92, 0x8f, 0x8c, 0x88, 0x85,
0x82, 0x7e, 0x7b, 0x78, 0x74, 0x71, 0x6e, 0x6b,
0x67, 0x64, 0x61, 0x5e, 0x5a, 0x57, 0x54, 0x51,
0x4e, 0x4b, 0x48, 0x45, 0x42, 0x3f, 0x3c, 0x39,
0x37, 0x34, 0x31, 0x2f, 0x2c, 0x29, 0x27, 0x25,
0x22, 0x20, 0x1e, 0x1c, 0x1a, 0x18, 0x16, 0x14,
0x12, 0x11, 0xf , 0xd , 0xc , 0xa , 0x9 , 0x8 , 
0x7 , 0x6 , 0x5 , 0x4 , 0x3 , 0x2 , 0x2 , 0x1 , 
0x1 , 0x0 , 0x0 , 0x0 , 0x0 , 0x0 , 0x0 , 0x0 , 
0x0 , 0x0 , 0x1 , 0x1 , 0x2 , 0x2 , 0x3 , 0x4 , 
0x5 , 0x6 , 0x7 , 0x8 , 0x9 , 0xa , 0xc , 0xd , 
0xf , 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 
0x1e, 0x20, 0x22, 0x25, 0x27, 0x29, 0x2c, 0x2e, 
0x31, 0x34, 0x36, 0x39, 0x3c, 0x3f, 0x42, 0x45, 
0x48, 0x4b, 0x4e, 0x51, 0x54, 0x57, 0x5a, 0x5d, 
0x61, 0x64, 0x67, 0x6a, 0x6e, 0x71, 0x74, 0x78, 
0x7b, 0x7e, 0x82, 0x85, 0x88, 0x8c, 0x8f, 0x92, 
0x95, 0x99, 0x9c, 0x9f, 0xa2, 0xa6, 0xa9, 0xac
};