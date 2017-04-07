// Kainoa Seto
// Hexdump program
// 4 - 7 - 2017
// Dumps a file in hexadecimal and ascii to the commandline with custom implementations
// of the integer to hex function.
// main.c

#include "hexdump.h"

int main(int argc, char* argv[])
{
    if( argc < 2 )
    {
        printf( "Usage: %s a_file_path\n", argv[0] );
        return -1;
    }

    if ( strcmp(argv[1],  "/?") == 0)
    {
        printf("This program will print out the hexadecimal and ascii text for a given file as a second argument to the program\n");
        printf(" Usage:   hexdump a_file_path\n");
        return 0;
    }

    // File handle to dump hex for
    FILE* file;
    file = fopen( argv[1], "rb" );

    if( file == NULL )
    {
        printf( "Error: failed to open file\n" );
        return -1;
    }

    Hexdump_dump( file );

    fclose( file );

    return 0;
}