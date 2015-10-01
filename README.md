# ascii_conf_reader
Are you, as I have been, sick of trying to read values and arrays into a C program? Well, I have some news.
This repository contains a  bunch of macros for reading values and arrays from custom ASCII .conf files into a C struct,
and simple examples of the use of each macro are included.

###Version history
==================
2015/09/30		v0.1	Wrote ascii_conf_reader_example.{c,h}

###Included macros
==================

####-->For single values
--------------------
Macro name            | Data type
----------------------|----------
*READ_BOOL_TO_STRUCT  | (uint8_t)
*READ_UINT_TO_STRUCT  | (uint16_t)
*READ_ULL_TO_STRUCT   | (uint64_t)
*READ_LL_TO_STRUCT    | (int64_t)
*READ_STR_TO_STRUCT   | (char *)
			         
####-->For arrays of text
--------------------------	         

Macro name                       | Data type
---------------------------------|--------------
*READ_UINT_ARR_TO_STRUCT         | (uint16_t *)
*READ_UL_ARR_TO_STRUCT	         | (uint32_t *)
*READ_ULL_ARR_TO_STRUCT          | (uint64_t *)
*READ_STR_ARR_TO_STRUCT          | (char ** )
*READ_TWO_ELEM_UINT_ARR_TO_STRUCT| (uint16_t **)

... and a bonus function for trimming leading or trailing whitespace from a string!

###Example: ascii_conf_reader_example
==================================
The included program, aptly titled "ascii_conf_reader_example", is meant to be used as a template for any of the macros.