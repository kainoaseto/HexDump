// Kainoa Seto
// Hexdump program
// 4 - 7 - 2017
// Dumps a file in hexadecimal and ascii to the commandline with custom implementations
// of the integer to hex function.
// hexdump.c

#include "hexdump.h"

// Converts unsigned integer to hexadecimal
// Params: character as integer, max length of the hexadecimal
// if the max_len is 0 then no 0 character filling will happen and size will default to 9
// returns: character array of hexadecimal representation
char* itoh( unsigned int char_int, int max_len);

// Resets memory and frees it
// Params: the cstring to free and delete and it's length
// returns: none
void delete( char* cstr, int len );


void Hexdump_dump( FILE* file_to_dump )
{
    // Ascii line of the characters that are printed out in hex
    char ascii_line[16];
    // The current hexadecimal representation of the current ascii char read in via fgetc
    char* hchar;

    // The total character count, current line character count, and the current character read in as an integer
    int total_count, char_count, current_char;

    total_count = 0, char_count = 0;

    printf("    Addr:  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F   ------ASCII-----\n");
    while((current_char = fgetc(file_to_dump)) != EOF)
    {
        // if we have finished printing out the hex print out the ascii
        if (char_count == 16)
        {
            printf("  %s\n", ascii_line);
            char_count = 0;
            // Clear line buffer after we have printed it out
            memset(ascii_line, 0, 16);
        }

        // If we have finished printing out the line then print out the prefix to the next line
        if (char_count == 0)
        {
            char *hline = itoh((unsigned int)total_count, 8);
            printf("%08s: ", hline);
            delete(hline, 9);
        }

        // Print out the converted hex char
        hchar = itoh((unsigned int)current_char, 2);
        printf("%2s ", hchar);
        delete(hchar, 2);

        // Handle char overrides for certain characters we do not want to print out in the ascii table
        if (current_char == '\r' || current_char == '\n' || current_char >= 127 || current_char <= 32)
        {
            ascii_line[char_count] = ' ';
        }
        else
        {
            ascii_line[char_count] = (char) current_char;
        }
        char_count++, total_count++;
    }

    // The EOF must be printed out manually since it is represented as -1 which in hex is FF
    // however, EOF is represented as 1A
    printf("1A ");
    char_count++, total_count++;

    // Each hex char is represented by 3 characters totalling 48 before the ascii gets prinited
    // Find the different and print out spaces for the final ascii line
    printf("  % *s", 48 - 3*char_count, " ");
    printf("%s\n", ascii_line);
    printf("Final Character count: %i (0x%s)", total_count, itoh(total_count, 0));

}

char* itoh( unsigned int char_int, int max_len)
{
    // Hex characters laid out so integers can be converted easily
    char hex_chars[16];
    // This is not the most efficient but it clearly illustrates the relation
    // that is being made between the array of hex chars and the nibbles that access them
    hex_chars[0] = '0';
    hex_chars[1] = '1';
    hex_chars[2] = '2';
    hex_chars[3] = '3';
    hex_chars[4] = '4';
    hex_chars[5] = '5';
    hex_chars[6] = '6';
    hex_chars[7] = '7';
    hex_chars[8] = '8';
    hex_chars[9] = '9';
    hex_chars[10] = 'A';
    hex_chars[11] = 'B';
    hex_chars[12] = 'C';
    hex_chars[13] = 'D';
    hex_chars[14] = 'E';
    hex_chars[15] = 'F';

    // Final hex representation located on the heap that is initialized with all '0'
    char* final_hex;
    // Current nibble from char_int and the count of hex chars
    int currNibble, count;
    // Temp hex representation before transposed onto filled final_hex
    char* temp_hex;
    // Flag if the size is set so we know that we are filling it with the manual length
    int manual_len;

    // If max len is 0 when passed through no automatic filling of the '0' character will occur
    manual_len = max_len;

    if(!manual_len)
        max_len = 9;

    temp_hex = malloc(max_len);
    final_hex = malloc(max_len);

    if(manual_len)
        memset(final_hex, '0', max_len);

    count = 0;

    // Reverse fill the final_hex so that the largest is first and vice versa
    while( char_int )
    {
        currNibble = char_int & 0xF;
        temp_hex[count] = hex_chars[currNibble];
        count++;
        char_int >>= 4;
    }

    // Counts for iterating forwards and backwards through the hex cstrings
    int i, j;
    // Temp for swapping
    char temp;

    // Reverse the hex string
    for (i = 0, j = count-1; i < (count/2); i++, j--)
    {
        temp = temp_hex[i];
        temp_hex[i] = temp_hex[j];
        temp_hex[j] = temp;
    }

    if(manual_len)
    {
        // If it is manual length then copy into final
        for (i = 0, j = max_len-count; i < count; i++, j++)
        {
            final_hex[j] = temp_hex[i];
        }
    }
    else {
        memcpy(final_hex, temp_hex, max_len);
    }

    delete(temp_hex, max_len);
    return final_hex;
}

// Helper to clean up our memory and reset it
void delete( char* cstr, int len )
{
    memset(cstr, 0, len);
    free(cstr);
}