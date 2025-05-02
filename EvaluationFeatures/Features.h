#ifndef FEATURES_H
#define FEATURES_H

constexpr int mg_pawn_table[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    42, 113, 55, 23, 46, 60, 39, -14,
    -64, -7, 5, 92, 130, 35, -11, -59,
    -93, -49, 17, 101, 142, 40, -52, -87,
    -22, 23, 55, 100, 43, -34, -5, -17,
    42, 101, 7, 36, 28, 59, 72, 78,
    85, 124, 183, -70, 39, 109, 347, 94,
    0, 0, 0, 0, 0, 0, 0, 0
};

constexpr int eg_pawn_table[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    122, 152, 152, 62, 125, 66, 170, 183,
    35, 85, 64, 128, 121, 32, 45, 44,
    -47, -38, 24, 85, 117, 32, -52, -47,
    17, 34, 57, 81, 19, -48, -12, 6,
    72, 112, 5, 47, 25, 51, 38, 82,
    133, 133, 211, -37, 67, 85, 311, 109,
    0, 0, 0, 0, 0, 0, 0, 0
};

constexpr int mg_knight_table[64] = {
    -266, -63, -16, -18, 14, 68, -95, -260,
    -22, 20, 14, 90, 73, -41, 23, -49,
    -15, 145, 115, 251, 185, 127, 48, -138,
    213, 204, 311, 265, 236, 280, 167, 193,
    332, 226, 363, 266, 293, 347, 225, 313,
    165, 271, 177, 404, 400, 158, 464, 236,
    116, 237, 456, 373, 396, 533, 223, 163,
    -181, 192, 265, 118, 45, 344, -292, -389
};

constexpr int mg_bishop_table[64] = {
    111, 282, 99, 23, 53, 94, 279, 182,
    242, 334, 331, 220, 97, 201, 300, 405,
    285, 255, 274, 152, 169, 143, 260, 216,
    340, 146, 102, 207, 243, 161, 161, 199,
    266, 283, 197, 297, 210, 109, 185, 165,
    353, 420, 196, 145, 214, 236, 382, 341,
    101, 203, 180, 181, 155, 111, 237, 183,
    201, 316, 93, 355, 68, 152, 313, 57
};

constexpr int mg_rook_table[64] = {
    56, 125, 200, 220, 211, 140, 161, 78,
    17, 245, 107, 149, 102, 124, 55, -43,
    121, 196, 101, 157, 107, 88, 180, 138,
    199, 227, 164, 169, 142, 154, 84, 176,
    331, 370, 325, 334, 266, 295, 340, 378,
    463, 474, 410, 448, 271, 335, 442, 389,
    19, 28, 158, 123, 70, 38, -57, 67,
    421, 475, 477, 405, 287, 334, 324, 481
};

constexpr int mg_queen_table[64] = {
    617, 447, 504, 715, 475, 445, 491, 564,
    461, 567, 701, 564, 546, 651, 629, 603,
    593, 622, 596, 594, 604, 545, 695, 583,
    472, 612, 572, 563, 414, 615, 644, 598,
    747, 632, 681, 683, 635, 690, 732, 574,
    813, 999, 762, 893, 938, 964, 964, 845,
    597, 566, 847, 747, 746, 787, 566, 709,
    515, 752, 824, 702, 936, 822, 804, 416
};

constexpr int mg_king_table[64] = {
    -64, 8, -33, -103, -55, -61, -5, -58,
    -50, -28, 2, 24, 3, -9, -10, -34,
    -49, 70, 106, 121, 147, 75, 41, -15,
    35, 127, 195, 236, 233, 195, 101, -20,
    50, 205, 252, 262, 327, 217, 149, 64,
    150, 323, 354, 354, 363, 295, 206, 12,
    5, 328, 227, 244, 405, 262, 231, 70,
    -228, 132, 210, 262, 238, 114, 117, -266
};

constexpr int eg_king_table[64] = {
    -73, -49, -67, -106, -10, -12, -3, -88,
    -91, -10, 36, 48, 28, 32, 50, 5,
    -30, 63, 127, 152, 187, 114, 63, 19,
    44, 169, 231, 290, 289, 253, 141, 18,
    81, 202, 300, 325, 400, 284, 191, 104,
    145, 334, 387, 421, 430, 341, 228, 30,
    -22, 310, 239, 321, 462, 282, 217, 45,
    -266, 62, 177, 305, 202, 128, 69, -323
};

// constexpr int PawnBonuses[8] = {
//     0, -28, 36, 98, 96, 172, 401, 0
// };

// constexpr int PawnBonusesEG[8] = {
//     0, -23, 41, 103, 101, 182, 421, 0
// };

constexpr int PAWN_VALUE_MG = 295;
constexpr int PAWN_VALUE_EG = 295;
constexpr int KNIGHT_VALUE_MG = 1081;
constexpr int KNIGHT_VALUE_EG = 1071;
constexpr int BISHOP_VALUE_MG = 1194;
constexpr int BISHOP_VALUE_EG = 1189;
constexpr int ROOK_VALUE_MG = 1938;
constexpr int ROOK_VALUE_EG = 1948;
constexpr int QUEEN_VALUE_MG = 3972;
constexpr int QUEEN_VALUE_EG = 4002;
constexpr int PASSEDPAWN_MG = 63;
constexpr int PASSEDPAWN_EG = 93;
constexpr int DOUBLEDPAWN_MG = -68;
constexpr int DOUBLEDPAWN_EG = -63;
constexpr int ISOLATEDPAWN_MG = -82;
constexpr int ISOLATEDPAWN_EG = -77;
constexpr int KNIGHTOUTPOST_MG = 181;
constexpr int KNIGHTOUTPOST_EG = 171;
constexpr int KNIGHTMOBILITY_MG = 35;
constexpr int KNIGHTMOBILITY_EG = 34;
constexpr int BISHOPMOBILITY_MG = 32;
constexpr int BISHOPMOBILITY_EG = 31;
constexpr int ROOKMOBILITY_MG = 16;
constexpr int ROOKMOBILITY_EG = 16;
constexpr int ROOKOPENFILE_MG = 71;
constexpr int ROOKOPENFILE_EG = 76;
constexpr int ROOKBACKRANK_MG = 195;
constexpr int ROOKBACKRANK_EG = 193;
constexpr int TWOBISHOPS_MG = 30;
constexpr int TWOBISHOPS_EG = 40;
constexpr int BISHOPFIXEDPAWNS_MG = -20;
constexpr int BISHOPFIXEDPAWNS_EG = -18;
constexpr int NOPAWNSHIELD_MG = 59;
constexpr int NOPAWNSHIELD_EG = 69;
constexpr int VQUEENSCOREMG = -16;
constexpr int VQUEENSCOREEG = -11;

#endif