#ifndef _PARSE_PCM
#define _PARSE_PCM

//function declarations
int iInitFromASCII(char * szASCIIConfFile, struct suASCIIConf * psuASCIIConf, uint8_t bDebug );
void vInitArrays(struct suASCIIConf * psuASCIIConf);

//Routines for freeing memory
int iASCIIConfFree(struct suASCIIConf * psuASCIIConf);

void vPrintASCIIConf (struct suASCIIConf * psuASCIIConf);

void vUsage(void);

#endif //end #ifndef _PARSE_PCM
