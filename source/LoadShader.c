/******************************************************************
*
* LoadShader.c
*
* Description: Helper routine for loading shader source code.
*
* Interactive Graphics and Simulation Group
* Institute of Computer Science
* University of Innsbruck
*
*******************************************************************/

/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------*/


/******************************************************************
*
* LoadShader
*
* This function reads and returns a string from the file 'filename';
* it is used to load the shader source code
*
*******************************************************************/

const char* LoadShader(const char* filename)
{
#ifdef WIN32
    FILE* infile;
    fopen_s(&infile, filename, "rb");
#else
    FILE* infile = fopen(filename, "rb");
#endif // WIN32

    if (!infile) 
    {
        fprintf(stderr, "Could not open shader file %s\n", filename);
        exit(0);
    }

    fseek(infile, 0, SEEK_END);
    int len = ftell(infile);
    fseek(infile, 0, SEEK_SET);

    char* source = malloc(sizeof(char) * (len+1));

    fread(source, 1, len, infile);
    fclose(infile);

    source[len] = 0;

    return (const char*)(source);
}
