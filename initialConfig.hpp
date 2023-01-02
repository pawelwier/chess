const unsigned short int SIZE = 8;
const unsigned short int FIELD_COUNT = pow(8, 2);
const unsigned short int START_LETTER = 65; // A
const unsigned short int START_NUMBER = 1;

unsigned short int whitePieces[2]{0, 15};
unsigned short int blackPieces[2]{48, 63};

const size_t pawnCount{16};
const size_t rookCount{4};
const size_t knightCount{4};
const size_t bishopCount{4};
const size_t queenCount{2};
const size_t kingCount{2};

const size_t totalCount = pawnCount + rookCount + knightCount + bishopCount + queenCount + kingCount;

// unsigned short int pawnIds[2][2] = {{8, 15}, {48, 55}}; // ??
unsigned short int pawnIds[pawnCount] = {8, 9, 10, 11, 12, 13, 14, 15, 48, 49, 50, 51, 52, 53, 54, 55};
unsigned short int rookIds[rookCount] = {0, 7, 56, 63};
unsigned short int knightIds[knightCount] = {1, 6, 57, 62};
unsigned short int bishopIds[bishopCount] = {2, 5, 58, 61};
unsigned short int queenIds[2] = {3, 60};
unsigned short int kingIds[2] = {4, 59};