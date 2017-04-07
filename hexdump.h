// Kainoa Seto
// Hexdump program
// 4 - 7 - 2017
// Dumps a file in hexadecimal and ascii to the commandline with custom implementations
// of the integer to hex function.
// hexdump.h

#ifndef __HEXDUMP_H__
#define __HEXDUMP_H__

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// Dumps out the hex from the file handle given
// Params: Pointer to file handle in read binary mode
// Returns none
void Hexdump_dump( FILE* file_to_dump );

#endif //__HEXDUMP_H__
