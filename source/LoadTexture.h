/******************************************************************
*
* LoadTexture.h
*
* Description: Helper routine for loading texture in BMP format.
* Adapted from texture loading code of the online OpenGL Tutorial:
*
* http://www.opengl-tutorial.org/
*
* Computer Graphics Proseminar SS 2018
* 
* Interactive Graphics and Simulation Group
* Institute of Computer Science
* University of Innsbruck
*
*******************************************************************/

#ifndef __LOAD_TEXTURE_H__
#define __LOAD_TEXTURE_H__

/* Structure containing texture RGB array and dimensions  */  
typedef struct 
{
    unsigned char *data;
    unsigned int width, height;
} *TextureDataPtr;

/* Load BMP file specified by filename */
int LoadTexture(const char* filename, TextureDataPtr data);

#endif // __LOAD_SHADER_H__
