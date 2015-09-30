/*
     ascii_conf_reader_example
     =========================
                         An example of using ascii_conf_reader.h in real life, baby. 

     Author:             Spencer M. Hatch, Dartmouth College
     ======= 

     Revision history:
     =================
     2015/09/30           Beginnings
		          
*/


#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <sys/stat.h>

#include "ascii_conf_reader.h"
#include "ascii_conf_reader_example_structs.h"
#include "ascii_conf_reader_example.h"

#define DEF_VERBOSE                       0    //please tell me

#define DEF_STR_SIZE                   1024

int main( int argc, char * argv[] )
{
    //************
    //Declare vars

    char                        szASCIIConfFile[DEF_STR_SIZE];
    uint8_t                     bHaveASCIIConfFile;

    struct suASCIIConf	      * psuASCIIConf;   
		                
    int                         iArgIdx;

    uint8_t                     bVerbose;
    uint8_t                     bDebug;
    int                         err;

    if (argc < 2)
	{
	vUsage();
	return EXIT_SUCCESS;
	}

    //Initialize vars			           
    szASCIIConfFile[0]               = '\0';
    bHaveASCIIConfFile               = 0;

    psuASCIIConf                     = NULL;

    iArgIdx                        = 0;

    bVerbose                       = DEF_VERBOSE;
    bDebug                         = 0;
    err                            = 0;

    for (iArgIdx=1; iArgIdx<argc; iArgIdx++)   //start with 1 to skip input file
	{

	switch (argv[iArgIdx][0])
	    {
	    int iTmp;
	    case '-' :
		switch (argv[iArgIdx][1])
		    {

		    case 'C' :                  /* ASCII conf file */
			iArgIdx++;
			bHaveASCIIConfFile = 1;
			strncpy(szASCIIConfFile, argv[iArgIdx],DEF_STR_SIZE);
			break;

		    case 'v' :                  /* Verbosities */
			bVerbose = 1;
			break;

		    case 'h' :                  /* Help */
			vUsage();
			return EXIT_SUCCESS;
			break;

		    default :
			break;
		    } /* end flag switch */
		break;

	    default :
		vUsage();
		return EXIT_SUCCESS;
		break;

	    } /* end command line arg switch */
	} /* end for all arguments */

    //init ASCII conf struct
    psuASCIIConf = (struct suASCIIConf * ) malloc( sizeof(struct suASCIIConf) );
    if ( bHaveASCIIConfFile )
	err = iInitFromASCII(szASCIIConfFile, psuASCIIConf, bDebug );
    else
	{
	err = EXIT_FAILURE;
	printf("No configuration file specified! Please specify with -C <Configuration file> at the command line.\n");
	}
    if ( err == EXIT_FAILURE )
	{
	printf("Couldn't init ASCII! Exiting...\n");
	return EXIT_FAILURE;
	}

    if (bVerbose) vPrintASCIIConf(psuASCIIConf);

    printf("All done reading %s! (Use '-v' if you want more output)\n",szASCIIConfFile);
    
    //release the mem!
    iASCIIConfFree(psuASCIIConf);

    return EXIT_SUCCESS;
}

int iInitFromASCII(char * szASCIIConfFile, struct suASCIIConf * psuASCIIConf, uint8_t bDebug )
{
    int iArgIdx;

    FILE              *  psuASCIIConfFile;
    char              *  szLine;
    int                  iLineIdx;
    int                  bufsize;
    char              *  szCodeName;
    char              *  szDataItem;

    //*******************
    //Initialize vars

    /* Values */
    psuASCIIConf->bVal              = 0;
    psuASCIIConf->uVal              = 0;
    psuASCIIConf->ullVal            = 0;
    psuASCIIConf->iVal              = 0;
    psuASCIIConf->llVal             = 0;
    sprintf(psuASCIIConf->szVal,'\0');

    /* Arrays */
    psuASCIIConf->pauArray          = NULL;
    psuASCIIConf->paulArray         = NULL;
    psuASCIIConf->paullArray        = NULL;
    psuASCIIConf->pszArray          = NULL;
    psuASCIIConf->ppauTwoByNArray   = NULL;

    psuASCIIConf->iN_u16            = 0;
    psuASCIIConf->iN_u32            = 0;
    psuASCIIConf->iN_u64            = 0;
    psuASCIIConf->iN_strings        = 0;
    psuASCIIConf->iN_twoelem_pairs  = 0;


    bufsize=DEF_STR_SIZE;

    szLine = (char * )malloc(bufsize*sizeof(char));

    if( szLine == NULL)
    {
        perror("Unable to allocate string buffer\n");
        return EXIT_FAILURE;
    }

    psuASCIIConfFile = (FILE *) fopen(szASCIIConfFile,"r");
    if (psuASCIIConfFile == NULL)
	{
	fprintf(stderr, "Error opening ASCII configuration file! Did you provide one?\n");
	return EXIT_FAILURE;
	}

    //get line from file
    while( ( getline(&szLine,(size_t *)&bufsize,psuASCIIConfFile) ) != -1 )
	{
	// If errors reading line then skip over it
	// Also skip comments, which are marked with "#"
	szCodeName = strtok(szLine, ":");
	szDataItem = strtok(NULL, "\n");

	if ( (szCodeName != NULL) && (szDataItem != NULL) && (szCodeName[0] != '#') ) //One-line value
	    {
	    char * szCodeNameTrimmed;
	    char * szDataItemTrimmed;

	    szCodeNameTrimmed = trimwhitespace(szCodeName);
	    szDataItemTrimmed = trimwhitespace(szDataItem);

	    //	    printf("SzCNTrimmed[%i]:szDataItemTrimmed[%i] --- %s : %s\n",(int)strlen(szCodeNameTrimmed),(int)strlen(szDataItemTrimmed),
	    //szCodeNameTrimmed,szDataItemTrimmed);
	    if(0) {}
	    READ_BOOL_TO_STRUCT(BOOL_VAL,psuASCIIConf,bVal)
	    READ_UINT_TO_STRUCT(UINT_VAL,psuASCIIConf,uVal)
	    READ_ULL_TO_STRUCT(ULL_VAL,psuASCIIConf,ullVal)
	    READ_INT_TO_STRUCT(INT_VAL,psuASCIIConf,iVal)
	    READ_LL_TO_STRUCT(LL_VAL,psuASCIIConf,llVal)
	    READ_STR_TO_STRUCT(STR_VAL,psuASCIIConf,szVal)

	    READ_INT_TO_STRUCT(N_IN_UINT_ARR,psuASCIIConf,iN_u16)
	    READ_INT_TO_STRUCT(N_IN_UL_ARR,psuASCIIConf,iN_u32)
	    READ_INT_TO_STRUCT(N_IN_ULL_ARR,psuASCIIConf,iN_u64)
	    READ_INT_TO_STRUCT(N_IN_STR_ARR,psuASCIIConf,iN_strings)
	    READ_INT_TO_STRUCT(N_PAIRS_IN_N_BY_TWO_ARR,psuASCIIConf,iN_twoelem_pairs)

	    }
	else
	    continue;

	iLineIdx++;
	}

    //With knowledge of num measurements, initialize arrays
    if ( ( psuASCIIConf->iN_u16 > 0 ) && ( psuASCIIConf->iN_u32 > 0 ) && ( psuASCIIConf->iN_u64 > 0 ) &&
	 ( psuASCIIConf->iN_strings > 0 ) && ( psuASCIIConf->iN_twoelem_pairs > 0 ) )
	{
	vInitArrays(psuASCIIConf);
	}
    else
	{
	printf("Didn't find number of measurements in ASCII file!\n");
	printf("(Should be listed as 'N_MEASUREMENTS:  [n_meas]')\n");
	printf("Exiting...\n");
	return EXIT_FAILURE;
	}

    //Finished reading vals, now read arrays
    rewind(psuASCIIConfFile);

    while( ( getline(&szLine,(size_t *)&bufsize,psuASCIIConfFile) ) != -1 )
	{

	// If errors reading line then skip over it
	// Also skip comments, which are marked with "#"
	szCodeName = strtok(szLine, ":");
	szDataItem = strtok(NULL, "\n");

	if ( (szCodeName != NULL) && (szDataItem == NULL) && (szCodeName[0] != '#' ) && !isspace(szCodeName[0]) ) //One-line value
	    {
	    char * szCodeNameTrimmed;

	    szCodeNameTrimmed = trimwhitespace(szCodeName);
	    if (bDebug) printf("**%s\n",szCodeNameTrimmed);

	    if(0) {}  //For dat macro logic
            READ_UINT_ARR_TO_STRUCT(UINT_ARR,psuASCIIConf,pauArray,psuASCIIConf->iN_u16)
            READ_UL_ARR_TO_STRUCT(UL_ARR,psuASCIIConf,paulArray,psuASCIIConf->iN_u32)
            READ_ULL_ARR_TO_STRUCT(ULL_ARR,psuASCIIConf,paullArray,psuASCIIConf->iN_u64)
	    READ_STR_ARR_TO_STRUCT(STR_ARR,psuASCIIConf,pszArray,psuASCIIConf->iN_strings)
            READ_TWO_ELEM_UINT_ARR_TO_STRUCT(N_BY_TWO_UINT_ARR,psuASCIIConf,ppauTwoByNArray,psuASCIIConf->iN_twoelem_pairs)
	    }
	}
    
    fclose(psuASCIIConfFile);

    return EXIT_SUCCESS;
}

void vInitArrays(struct suASCIIConf * psuASCIIConf)
{

    int iArgIdx;

    if ( psuASCIIConf->iN_u16 > 0 )
	psuASCIIConf->pauArray                      = (uint16_t *  ) malloc(psuASCIIConf->iN_u16*sizeof(uint16_t));
    else
	psuASCIIConf->pauArray                      = NULL;

    if ( psuASCIIConf->iN_u32 > 0 )            
	psuASCIIConf->paulArray                     = (uint32_t *  ) malloc(psuASCIIConf->iN_u32*sizeof(uint32_t));
    else
	psuASCIIConf->paulArray                     = NULL;

    if ( psuASCIIConf->iN_u64 > 0 )            
	psuASCIIConf->paullArray                    = (uint64_t *  ) malloc(psuASCIIConf->iN_u64*sizeof(uint64_t));
    else
	psuASCIIConf->paullArray                    = NULL;

    if ( psuASCIIConf->iN_strings > 0 )
	{
	psuASCIIConf->pszArray                      = (char     ** ) malloc(psuASCIIConf->iN_strings*sizeof(char *));
	for( iArgIdx = 0; iArgIdx < psuASCIIConf->iN_strings; iArgIdx++ )
	    {
	    psuASCIIConf->pszArray[iArgIdx]         = ( char     * ) malloc(DEF_STR_SIZE*sizeof(uint16_t));
	    }
	}
    else
	psuASCIIConf->pszArray                      = NULL;

    if ( psuASCIIConf->iN_twoelem_pairs > 0 )
	{
	psuASCIIConf->ppauTwoByNArray               = (uint16_t ** ) malloc(psuASCIIConf->iN_twoelem_pairs*sizeof(uint16_t *));
	for( iArgIdx = 0; iArgIdx < psuASCIIConf->iN_twoelem_pairs; iArgIdx++ )
	    {
	    psuASCIIConf->ppauTwoByNArray[iArgIdx]  = ( uint16_t * ) malloc(2*sizeof(uint16_t));
	    }
	}
    else
	psuASCIIConf->ppauTwoByNArray               = NULL;

}

int iASCIIConfFree(struct suASCIIConf * psuASCIIConf)
{
    int iArgIdx;

    if ( psuASCIIConf->pauArray   != NULL )
	free( psuASCIIConf->pauArray   );

    if ( psuASCIIConf->paulArray  != NULL )
	free( psuASCIIConf->paulArray  );

    if ( psuASCIIConf->paullArray != NULL )
	free( psuASCIIConf->paullArray );

    if ( ( psuASCIIConf->pszArray          != NULL  ) && ( psuASCIIConf->iN_strings       > 0 ) )
	{
	for( iArgIdx = 0; iArgIdx < psuASCIIConf->iN_strings;       iArgIdx++ )
	    {
		if ( psuASCIIConf->pszArray[iArgIdx]        != NULL )
		    free ( psuASCIIConf->pszArray[iArgIdx]        );
	    }
	if ( psuASCIIConf->pszArray        != NULL )
	    free (psuASCIIConf->pszArray);
	}

    if ( ( psuASCIIConf->ppauTwoByNArray   != NULL ) && ( psuASCIIConf->iN_twoelem_pairs > 0 ) )
	{
	for( iArgIdx = 0; iArgIdx < psuASCIIConf->iN_twoelem_pairs; iArgIdx++ )
	    {
		if ( psuASCIIConf->ppauTwoByNArray[iArgIdx] != NULL )
		    free ( psuASCIIConf->ppauTwoByNArray[iArgIdx] );
	    }
	if ( psuASCIIConf->ppauTwoByNArray != NULL )
	    free (psuASCIIConf->ppauTwoByNArray);
	}

    free( psuASCIIConf );

    return (EXIT_SUCCESS);
}

void vPrintASCIIConf (struct suASCIIConf * psuASCIIConf)
{
    int iArgIdx;

    printf("                                                   \n");
    printf("***************************************************\n");
    printf("***************ASCII Configuration*****************\n");
    printf("VALUES                                             \n");
    printf("------                                             \n");
    printf("Boolean                              :   %10" PRIu8  "\n",psuASCIIConf->bVal);
    printf("Unsigned integer (16-bit)            :   %10" PRIu16 "\n",psuASCIIConf->uVal);
    printf("Unsigned integer (64-bit)            :   %10" PRIu64 "\n",psuASCIIConf->ullVal);
    printf("Integer          (16-bit)            :   %10" PRIi16 "\n",psuASCIIConf->iVal);
    printf("Integer          (64-bit)            :   %10" PRIi64 "\n",psuASCIIConf->llVal);
    printf("String                               :   %s\n",psuASCIIConf->szVal);
    printf("                                                   \n");
    printf("ARRAYS                                             \n");
    printf("------                                             \n");
    if ( psuASCIIConf->iN_u16 > 0 )
	{
	printf("**uint16_t Array                                     \n");
	for (iArgIdx = 0; iArgIdx < psuASCIIConf->iN_u16; iArgIdx++)
	    {
	    printf("#%3i   :   %" PRIu16 "\n",iArgIdx+1,psuASCIIConf->pauArray[iArgIdx]);
	    }
	printf("                                                   \n");
	}
    
    if ( psuASCIIConf->iN_u32 > 0 )
	{
	printf("**uint32_t Array                                     \n");
	for (iArgIdx = 0; iArgIdx < psuASCIIConf->iN_u32; iArgIdx++)
	    {
	    printf("#%3i   :   %" PRIu32 "\n",iArgIdx+1,psuASCIIConf->paulArray[iArgIdx]);
	    }
	printf("                                                   \n");
	}
    
    if ( psuASCIIConf->iN_u64 > 0 )
	{
	printf("**uint64_t Array                                     \n");
	for (iArgIdx = 0; iArgIdx < psuASCIIConf->iN_u64; iArgIdx++)
	    {
	    printf("#%3i   :   %" PRIu64 "\n",iArgIdx+1,psuASCIIConf->paullArray[iArgIdx]);
	    }
	printf("                                                   \n");
	}
    
    if ( psuASCIIConf->iN_strings > 0 )
	{
	printf("**Strings Array                                     \n");
	for (iArgIdx = 0; iArgIdx < psuASCIIConf->iN_strings; iArgIdx++)
	    {
	    printf("#%3i   :   %s\n",iArgIdx+1,psuASCIIConf->pszArray[iArgIdx]);
	    }
	printf("                                                   \n");
	}

    if ( psuASCIIConf->iN_twoelem_pairs > 0 )
	{
	printf("**uint16_t 2xN Array                                 \n");
	for (iArgIdx = 0; iArgIdx < psuASCIIConf->iN_twoelem_pairs; iArgIdx++)
	    {
	    printf("#%3i   :   [%u,%u]\n",iArgIdx+1,psuASCIIConf->ppauTwoByNArray[iArgIdx][0],psuASCIIConf->ppauTwoByNArray[iArgIdx][1]);
	    }
	printf("                                                   \n");
	}
}


void vUsage(void)
{
    printf("                                                                                \n");
    printf("ascii_conf_reader_example                                                       \n");
    printf("Show how awesome it can be to read an ASCII configuration file                  \n");
    printf("                                                                                \n");
    printf("Usage: ascii_conf_reader_example [parameters]                                   \n");
    printf("                                                                                \n");
    printf("   PARAMETERS                                                                   \n");
    printf("   -C           Configuration file                                      [none]  \n");
    printf("                 *Open ASCII_conf_header.conf to see the format                 \n");
    printf("   -v           Verbose                                                 [%i]    \n",DEF_VERBOSE);
    printf("   -h           Help (this menu)                                                \n");
}
