//2015/09/30
//Structures containing information read from ASCII

#ifndef _ASCII_STRUCTS
#define _ASCII_STRUCTS

static char   * szASCIIConfValNames[]   = {"BOOL_VAL",
					   "UINT_VAL",
					   "ULL_VAL",
					   "INT_VAL",
					   "LL_VAL",
					   "STR_VAL"};

static char  * szASCIIArrayNames[]   = {"UINT_ARR",
					"UL_ARR",
					"ULL_ARR",
					"STR_ARR",
					"N_BY_TWO_UINT_ARR"};

struct suASCIIConf
{
    uint8_t         bVal;
    uint16_t        uVal;
    uint64_t        ullVal;
    int16_t         iVal;
    int64_t         llVal;
    char            szVal[128];

    //Arrays to hold info from ASCII file
    uint16_t  *     pauArray;
    uint32_t  *     paulArray;
    uint64_t  *     paullArray;
    char      **    pszArray;
    uint16_t  **    ppauTwoByNArray;

    int16_t         iN_u16;
    int16_t         iN_u32;
    int16_t         iN_u64;
    int16_t         iN_strings;
    int16_t         iN_twoelem_pairs;
};

#endif //end #ifndef _ASCII_STRUCTS
