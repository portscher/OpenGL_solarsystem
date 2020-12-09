#include "stdio.h"
#include "GL/glew.h"
#include "math.h"

#include "source/LoadShader.h"    /* Loading function for shader code */
#include "source/Matrix.h"        /* Functions for matrix handling */
#include "source/OBJParser.h"            /* Loading function for triangle meshes in OBJ format */
#include "source/LoadTexture.h"   /* Loading function for BMP texture */

#include "solarsystem.h"

void createCubeMesh(GLuint* VBO, GLuint* CBO, GLuint* IBO)
{
    GLfloat vertex_buffer_data[] = { /* 8 cube vertices XYZ */
        -1.0, -1.0,  1.0,
         1.0, -1.0,  1.0,
         1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,
        -1.0, -1.0, -1.0,
         1.0, -1.0, -1.0,
         1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0,
    };

    GLfloat color_buffer_data[] = { /* RGB color values for 8 vertices */
        0.0, 0.0, 1.0,
        1.0, 0.0, 1.0,
        1.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
    };

    unsigned int index_buffer_data[] = { /* Indices of 6*2 triangles (6 sides) */
        0, 1, 2,
        2, 3, 0,
        1, 5, 6,
        6, 2, 1,
        7, 6, 5,
        5, 4, 7,
        4, 0, 3,
        3, 7, 4,
        4, 5, 1,
        1, 0, 4,
        3, 2, 6,
        6, 7, 3,
    };

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, CBO);
    glBindBuffer(GL_ARRAY_BUFFER, *CBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
}

/******************************************************************
*
* createQuadMesh
*
* This function creates a simple quad mesh
*
* Input : VBO = pointer to the Vertex buffer object to fill
*         CBO = pointer to the Color buffer object to fill
*         NBO = pointer to the Normal buffer object to fill
*         UVBO = pointer to the UVcoords buffer object to fill
*         IBO = pointer to the Index buffer object to fill
*         rgb = 3D vector containing the color of the object (r=x, g=y, b=z)
*******************************************************************/


void createQuadMesh(GLuint* VBO, GLuint* CBO, GLuint* NBO, GLuint* UVBO, GLuint* IBO, float* rgb)
{
    GLfloat vertex_buffer_data[] = { /* 8 cube vertices XYZ -> size and alignment/position*/
            -1.5, -1.,  -1.5,
            1.5, 0.,  -1.5,
            1.5,  1.,  1.5,
            -1.5,  0.,  1.5,
    };

    GLfloat color_buffer_data[] = { /* RGB values for 8 vertices */
            rgb[0], rgb[1],  rgb[2],
            rgb[0], rgb[1],  rgb[2],
            rgb[0], rgb[1],  rgb[2],
            rgb[0], rgb[1],  rgb[2],
    };

    GLfloat normal_buffer_data[] = { /* Normal coords for 8 vertices */
            0.0, 0.0,  -1.0,
            0.0, 0.0,  -1.0,
            0.0, 0.0,  -1.0,
            0.0, 0.0,  -1.0,
    };

    GLfloat uv_buffer_data[] = { /* UV coords for 8 vertices */
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0,
    };

    unsigned int index_buffer_data[] = { /* Indices of 2 triangles */
            0, 1, 2,
            2, 3, 0,
    };

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, CBO);
    glBindBuffer(GL_ARRAY_BUFFER, *CBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, NBO);
    glBindBuffer(GL_ARRAY_BUFFER, *NBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normal_buffer_data), normal_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, UVBO);
    glBindBuffer(GL_ARRAY_BUFFER, *UVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv_buffer_data), uv_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);
}

/***************************************************************
* Create cube mesh with inwards facing faces
***************************************************************/

void createCube(GLuint* VBO, GLuint* VAO) {
    float points[] = {
            -10.0f,  10.0f, -10.0f,
            -10.0f, -10.0f, -10.0f,
            10.0f, -10.0f, -10.0f,
            10.0f, -10.0f, -10.0f,
            10.0f,  10.0f, -10.0f,
            -10.0f,  10.0f, -10.0f,

            -10.0f, -10.0f,  10.0f,
            -10.0f, -10.0f, -10.0f,
            -10.0f,  10.0f, -10.0f,
            -10.0f,  10.0f, -10.0f,
            -10.0f,  10.0f,  10.0f,
            -10.0f, -10.0f,  10.0f,

            10.0f, -10.0f, -10.0f,
            10.0f, -10.0f,  10.0f,
            10.0f,  10.0f,  10.0f,
            10.0f,  10.0f,  10.0f,
            10.0f,  10.0f, -10.0f,
            10.0f, -10.0f, -10.0f,

            -10.0f, -10.0f,  10.0f,
            -10.0f,  10.0f,  10.0f,
            10.0f,  10.0f,  10.0f,
            10.0f,  10.0f,  10.0f,
            10.0f, -10.0f,  10.0f,
            -10.0f, -10.0f,  10.0f,

            -10.0f,  10.0f, -10.0f,
            10.0f,  10.0f, -10.0f,
            10.0f,  10.0f,  10.0f,
            10.0f,  10.0f,  10.0f,
            -10.0f,  10.0f,  10.0f,
            -10.0f,  10.0f, -10.0f,

            -10.0f, -10.0f, -10.0f,
            -10.0f, -10.0f,  10.0f,
            10.0f, -10.0f, -10.0f,
            10.0f, -10.0f, -10.0f,
            -10.0f, -10.0f,  10.0f,
            10.0f, -10.0f,  10.0f
    };

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);

    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

/******************************************************************
*
* readMeshFile
*
* This function read the content of an OBJ file and then fill the
* buffer objects with the data
*
* Input : filename = name of file.obj
*         scale = scale factor applied to the vertices
*         VBO = pointer to the Vertex buffer object to fill
*         CBO = pointer to the Color buffer object to fill
*         NBO = pointer to the Normal buffer object to fill
*         UVBO = pointer to the UVcoords buffer object to fill
*         IBO = pointer to the Index buffer object to fill
*         rgb = 3D vector containing the color of the object (r=x, g=y, b=z)
*******************************************************************/
void readMeshFile(char* filename, float scale, GLuint* VBO, GLuint* CBO, GLuint* NBO, GLuint* UVBO, GLuint* IBO, float* rgb)
{
    int i;

    /* Structure for loading of OBJ data */
    obj_scene_data data;

    /* Load first OBJ model */
    int success = parse_obj_scene(&data, filename);

    if(!success)
        printf("Could not load file. Exiting.\n");

    /*  Copy mesh data from structs into appropriate arrays */
    int indx = data.face_count;

    unsigned int* index_buffer_data = (unsigned int*) calloc (indx*3, sizeof(unsigned int));
    GLfloat* vertex_buffer_data = (GLfloat*) calloc (indx*9, sizeof(GLfloat));
    GLfloat* normal_buffer_data = (GLfloat*) calloc (indx*9, sizeof(GLfloat));
    GLfloat* color_buffer_data = (GLfloat*) calloc (indx*9, sizeof(GLfloat));
    GLfloat* uv_buffer_data = (GLfloat*) calloc (indx*6, sizeof(GLfloat));

    /* for each triangle... */
    for(i=0; i<indx; i++)
    {
        int offset = i*9;
        int offset3D = i*9;
        int offset2D = i*6;

        /* indices of 3 Vertices of the triangle */
        int idVert1 = (GLushort)(*data.face_list[i]).vertex_index[0];
        int idVert2  = (GLushort)(*data.face_list[i]).vertex_index[1];
        int idVert3  = (GLushort)(*data.face_list[i]).vertex_index[2];
        /* fill VBO for this triangle (x,y,z coords for 3 vertices = 9 values) */
        vertex_buffer_data[offset3D] = (GLfloat)(*data.vertex_list[idVert1]).e[0]*scale;
        vertex_buffer_data[offset3D+1] = (GLfloat)(*data.vertex_list[idVert1]).e[1]*scale;
        vertex_buffer_data[offset3D+2] = (GLfloat)(*data.vertex_list[idVert1]).e[2]*scale;
        vertex_buffer_data[offset3D+3] = (GLfloat)(*data.vertex_list[idVert2]).e[0]*scale;
        vertex_buffer_data[offset3D+4] = (GLfloat)(*data.vertex_list[idVert2]).e[1]*scale;
        vertex_buffer_data[offset3D+5] = (GLfloat)(*data.vertex_list[idVert2]).e[2]*scale;
        vertex_buffer_data[offset3D+6] = (GLfloat)(*data.vertex_list[idVert3]).e[0]*scale;
        vertex_buffer_data[offset3D+7] = (GLfloat)(*data.vertex_list[idVert3]).e[1]*scale;
        vertex_buffer_data[offset3D+8] = (GLfloat)(*data.vertex_list[idVert3]).e[2]*scale;

        /* Normals */
        int idNorm1 = (GLushort)(*data.face_list[i]).normal_index[0];
        int idNorm2  = (GLushort)(*data.face_list[i]).normal_index[1];
        int idNorm3  = (GLushort)(*data.face_list[i]).normal_index[2];
        /* fill NBO for this triangle */
        if(  (*data.face_list[i]).normal_index[0] != -1 )
        {
            normal_buffer_data[offset3D] = (GLfloat)(*data.vertex_normal_list[idNorm1]).e[0];
            normal_buffer_data[offset3D+1] = (GLfloat)(*data.vertex_normal_list[idNorm1]).e[1];
            normal_buffer_data[offset3D+2] = (GLfloat)(*data.vertex_normal_list[idNorm1]).e[2];
            normal_buffer_data[offset3D+3] = (GLfloat)(*data.vertex_normal_list[idNorm2]).e[0];
            normal_buffer_data[offset3D+4] = (GLfloat)(*data.vertex_normal_list[idNorm2]).e[1];
            normal_buffer_data[offset3D+5] = (GLfloat)(*data.vertex_normal_list[idNorm2]).e[2];
            normal_buffer_data[offset3D+6] = (GLfloat)(*data.vertex_normal_list[idNorm3]).e[0];
            normal_buffer_data[offset3D+7] = (GLfloat)(*data.vertex_normal_list[idNorm3]).e[1];
            normal_buffer_data[offset3D+8] = (GLfloat)(*data.vertex_normal_list[idNorm3]).e[2];
        }
        else
        {
            normal_buffer_data[offset3D] = vertex_buffer_data[offset];
            normal_buffer_data[offset3D+1] = vertex_buffer_data[offset3D+1];
            normal_buffer_data[offset3D+2] = vertex_buffer_data[offset3D+2];
            normal_buffer_data[offset3D+3] = vertex_buffer_data[offset3D+3];
            normal_buffer_data[offset3D+4] = vertex_buffer_data[offset3D+4];
            normal_buffer_data[offset3D+5] = vertex_buffer_data[offset3D+5];
            normal_buffer_data[offset3D+6] = vertex_buffer_data[offset3D+6];
            normal_buffer_data[offset3D+7] = vertex_buffer_data[offset3D+7];
            normal_buffer_data[offset3D+8] = vertex_buffer_data[offset3D+8];
        }

        /* fill UV buffer for this triangle */
        if( (*data.face_list[i]).texture_index[0] != -1 )
        {
            int j;
            for(j=0; j<3; j++)
            {
                int idUV = (GLushort)(*data.face_list[i]).texture_index[j];
                uv_buffer_data[offset2D + j*2 ] = (GLfloat)(*data.vertex_texture_list[idUV]).e[0];
                uv_buffer_data[offset2D + j*2 + 1] = (GLfloat)(*data.vertex_texture_list[idUV]).e[1];
            }
        }

        /* fill CBO for this triangle */
        color_buffer_data[offset3D] = (GLfloat)(rgb[0]);
        color_buffer_data[offset3D+1] = (GLfloat)(rgb[1]);
        color_buffer_data[offset3D+2] = (GLfloat)(rgb[2]);
        color_buffer_data[offset3D+3] = (GLfloat)(rgb[0]);
        color_buffer_data[offset3D+4] = (GLfloat)(rgb[1]);
        color_buffer_data[offset3D+5] = (GLfloat)(rgb[2]);
        color_buffer_data[offset3D+6] = (GLfloat)(rgb[0]);
        color_buffer_data[offset3D+7] = (GLfloat)(rgb[1]);
        color_buffer_data[offset3D+8] = (GLfloat)(rgb[2]);

        /* Fill indices buffer for this triangles (3 indices) */
        index_buffer_data[i*3] = (unsigned int) i*3;
        index_buffer_data[i*3+1] = (unsigned int) i*3+1;
        index_buffer_data[i*3+2] = (unsigned int) i*3+2;
    }

    /* Create buffer objects and load data into buffers*/
    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, data.face_count*9*sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, NBO);
    glBindBuffer(GL_ARRAY_BUFFER, *NBO);
    glBufferData(GL_ARRAY_BUFFER, data.face_count*9*sizeof(GLfloat), normal_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, CBO);
    glBindBuffer(GL_ARRAY_BUFFER, *CBO);
    glBufferData(GL_ARRAY_BUFFER, data.face_count*9*sizeof(GLfloat), color_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, UVBO);
    glBindBuffer(GL_ARRAY_BUFFER, *UVBO);
    glBufferData(GL_ARRAY_BUFFER, data.face_count*6*sizeof(GLfloat), uv_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.face_count*3*sizeof(unsigned int), index_buffer_data, GL_STATIC_DRAW);
}

/******************************************************************
 *
 * AddShader
 *
 * This function creates and adds individual shaders
 *
 *******************************************************************/
void AddShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType)
{
    /* Create shader object */
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0)
    {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    /* Associate shader source code string with shader object */
    glShaderSource(ShaderObj, 1, &ShaderCode, NULL);

    GLint success = 0;
    GLchar InfoLog[1024];

    /* Compile shader source code */
    glCompileShader(ShaderObj);
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    /* Associate shader with shader program */
    glAttachShader(ShaderProgram, ShaderObj);

    glDeleteShader(ShaderObj);
}


/******************************************************************
 *
 * CreateShaderProgram
 *
 * This function creates the shader program; vertex and fragment
 * shaders are loaded and linked into program; final shader program
 * is put into the rendering pipeline
 *
 *******************************************************************/
void CreateShaderProgram(int programIndex, char* vsPath, char* fsPath, char* gsPath)
{
    /* Allocate shader object */
    programs[programIndex] = glCreateProgram();

    if (programs[programIndex] == 0)
    {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    /* Load shader code from file */
    const char* VertexShaderString = LoadShader(vsPath);
    const char* FragmentShaderString = LoadShader(fsPath);

    /* Separately add vertex and fragment shader to program */
    AddShader(programs[programIndex], VertexShaderString, GL_VERTEX_SHADER);
    AddShader(programs[programIndex], FragmentShaderString, GL_FRAGMENT_SHADER);
    if (gsPath != NULL) {
        const char* GeometryShaderString = LoadShader(gsPath);
        AddShader(programs[programIndex], GeometryShaderString, GL_GEOMETRY_SHADER);
    }

    GLint Success = 0;
    GLchar ErrorLog[1024];

    /* Link shader code into executable shader program */
    glLinkProgram(programs[programIndex]);

    /* Check results of linking step */
    glGetProgramiv(programs[programIndex], GL_LINK_STATUS, &Success);
    if (Success == 0)
    {
        glGetProgramInfoLog(programs[programIndex], sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    /* Check if shader program can be executed */
    glValidateProgram(programs[programIndex]);
    glGetProgramiv(programs[programIndex], GL_VALIDATE_STATUS, &Success);
    if (!Success)
    {
        glGetProgramInfoLog(programs[programIndex], sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }
}

/******************************************************************
 *
 * SetupTexture
 *
 * This function is called to load the texture and initialize
 * texturing parameters
 *
 * Input: TextureID = id of the texture to setup
 *        filename = path to bitmap file to read
 *******************************************************************/
void SetupTexture(GLuint *TextureID, char* filename)
{
    /* Allocate texture container */
    TextureDataPtr Texture = malloc(sizeof(TextureDataPtr));

    int success = LoadTexture(filename, Texture);
    if (!success)
    {
        printf("Error loading texture. Exiting.\n");
        exit(-1);
    }

    /* Create texture name and store in handle */
    glGenTextures(1, TextureID);

    /* Bind texture */
    glBindTexture(GL_TEXTURE_2D, *TextureID);

    /* Load texture image into memory */
    glTexImage2D(GL_TEXTURE_2D,     /* Target texture */
            0,                 /* Base level */
            GL_RGBA,            /* Each element is RGB triple, A for alpha blending*/
            Texture->width,    /* Texture dimensions */
            Texture->height,
            0,                 /* Border should be zero */
            GL_BGR,            /* Data storage format for BMP file */
            GL_UNSIGNED_BYTE,  /* Type of pixel data, one byte per channel */
            Texture->data);    /* Pointer to image data  */

    /* Next set up texturing parameters */

    /* Repeat texture on edges when tiling */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /* Linear interpolation for magnification */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Trilinear MIP mapping for minification */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    /* Note: MIP mapping not visible due to fixed, i.e. static camera */
}

/***************************************************************
* Setup texture for cubemap, returns cube map texture ID
***************************************************************/

void SetUpCubeMapTexture(GLuint *textureID) {

    glGenTextures(1, textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, *textureID);

    char *filenames[6] = {
        "data/nebula/right.bmp",
        "data/nebula/left.bmp",
        "data/nebula/up.bmp",
        "data/nebula/down.bmp",
        "data/nebula/back.bmp",
        "data/nebula/front.bmp",
    };
    
    int i;
    for (i = 0; i < 6; i++) {

        /* Allocate texture container */
        TextureDataPtr Texture = malloc(sizeof(TextureDataPtr));

        int success = LoadTexture(filenames[i], Texture);
        if (!success)
        {
            printf("Error loading texture. Exiting.\n");
            exit(-1);
        }

        /* Load texture image into memory */
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,     /* Target texture, iterates through all sides of the cube */
                     0,                 /* Base level */
                     GL_RGBA,            /* Each element is RGB triple, A for alpha blending*/
                     Texture->width,    /* Texture dimensions */
                     Texture->height,
                     0,                 /* Border should be zero */
                     GL_BGR,            /* Data storage format for BMP file */
                     GL_UNSIGNED_BYTE,  /* Type of pixel data, one byte per channel */
                     Texture->data);    /* Pointer to image data  */

    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

/******************************************************************
* BindUniform4f, BindUniform3f, BindUniform1f
*
* Helper funtions to save a matrix, vector or value in the GPU

*******************************************************************/
void BindUniform4f(char* name, GLuint program, float* mat)
{
    GLint uniform = glGetUniformLocation(program, name);
    if (uniform == -1)
    {
        fprintf(stderr, "Could not bind uniform %s on program\n", name);
        exit(-1);
    }
    glUniformMatrix4fv(uniform, 1, GL_TRUE, mat);
}

/* A vector is saved in a buffer at the GPU */
void BindUniform3f(char* name, GLuint program, float* vec)
{
    GLint uniform = glGetUniformLocation(program, name);
    glUniform3f(uniform, vec[0], vec[1], vec[2]);

}

/* A value is saved in a buffer at the GPU */
void BindUniform1f(char* name, GLuint program, float val)
{
    GLint uniform = glGetUniformLocation(program, name);
    glUniform1f(uniform, val);
}

void BindUniform1i(char* name, GLuint program, int val)
{
    GLint uniform = glGetUniformLocation(program, name);
    glUniform1i(uniform, val);
}

/*
 *  VBO vertex buffer object
 *  CBO color buffe object
 *  NBO normal buffer object
 *  IBO index buffer object
 *  UVBO uv buffer object
 */
int BindBasics(GLuint VBO, GLuint CBO, GLuint IBO, GLuint NBO, GLuint UVBO)
{
    /* Bind buffer with vertex data of currently active object */
    glEnableVertexAttribArray(vPosition);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

    /* Bind color buffer */
    glEnableVertexAttribArray(vColor);
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glVertexAttribPointer(vColor, 3, GL_FLOAT,GL_FALSE, 0, 0);

    /* Bind normal buffer */
    if (NBO != 0) {
        glEnableVertexAttribArray(vNormal);
        glBindBuffer(GL_ARRAY_BUFFER, NBO);
        glVertexAttribPointer(vNormal, 3, GL_FLOAT,GL_FALSE, 0, 0);
    }

    /* Bind uv buffer */
    if (UVBO != 0) {
        glEnableVertexAttribArray(vUV);
        glBindBuffer(GL_ARRAY_BUFFER, UVBO);
        glVertexAttribPointer(vUV, 2, GL_FLOAT,GL_FALSE, 0, 0);
    }

    /* Bind index buffer */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    GLint size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

    return size/sizeof(unsigned int);
}

/******************************************************************
* printMatrix
*
* Helper funtion to print a matrix

*******************************************************************/
void printMatrix(float* mat)
{
    int i;
    for(i = 0; i < 16; i++) {
        if (fmod(i, 4) == 0) {
            printf("\n");
        }
        printf("%g ", mat[i]);
    }
}

/*******************************************************************
 * LookAt calculates the view matrix. Similar to the glm::LookAt function
 * first it creates a new matrix, with the basis of the camera, then multiplies it
 * with the negative of the camera position. The camera position is negative,
 * because we want to project the world in the opposite direction
 *
 * vec3 position    the camera position on the global world
 * vec3 target      what the camera is pointing towards
 * vec3 up          camera up vector
 * mat4 result      final viewMatrix
 *
 *******************************************************************/
void LookAt(float* position, float* target, float* uup, float* result)
{

    float direction[3]; // also called f vector
    // at = direction = target - position
    SubstractMatrix(position, target, direction);
    NormalizeVector(direction, direction);

    float right[3]; // also called l or s vector
    // left = right = direction * up
    CrossProduct(uup, direction, right);
    NormalizeVector(right, right);

    float up[3];
    // recalculate the up vector
    CrossProduct(direction, right, up);

    float temp[16] =
    {
        right[0],       right[1],       right[2],       0.0,
        up[0],          up[1],          up[2],          0.0,
        direction[0],   direction[1],   direction[2],   0.0,
        0.0,            0.0,            0.0,            1.0
    };
    /* float temp[16] = */
    /* { */
    /*     right[0],       up[0],       -direction[0],     0.0, */
    /*     right[1],       up[1],       -direction[1],     0.0, */
    /*     right[2],       up[2],       -direction[2],     0.0, */
    /*     0.0,            0.0,         0.0,               1.0 */
    /* }; */

    float t[16];
    SetTranslation(-position[0], -position[1], -position[2], t);
    MultiplyMatrix(temp, t, temp);

    memcpy(result, temp, 16*sizeof(float));
}

/***************************************************************
* clamp
*
* Helper funtion to truncate the value val between max and min
***************************************************************/
float clamp(float val, float max, float min)
{
    if (val < min) {
        return min;
    } else if (val > max) {
        return max;
    }
    return val;
}

void createAndAttachColorBuffer(GLuint* id, int i)
{
    glBindTexture(GL_TEXTURE_2D, *id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, winWidth, winHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // we clamp to the edge as the blur filter would otherwise
    // sample repeated texture values!
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // attach
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, *id, 0);
}

void DrawFrontScreen()
{
    if (frontScreen.VAO == 0) {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };

        glGenVertexArrays(1, &frontScreen.VAO); // create "array"
        glGenBuffers(1, &frontScreen.VBO); // generate new buffer

        glBindVertexArray(frontScreen.VAO); // make "array" active

        // bind buffer
        glBindBuffer(GL_ARRAY_BUFFER, frontScreen.VBO); // make buffer active
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW); // bind data to buffer

        // bind position vertex attribute
        glEnableVertexAttribArray(0); // index 0
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

        // bind UV vertex attribute
        glEnableVertexAttribArray(1); // index 1
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }

    glBindVertexArray(frontScreen.VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void EnableTexture(char* name, GLuint program, int index)
{
    /* Get texture uniform handle from fragment shader (myTestureSampler is the name of the uniform from the shader)*/
    GLuint TextureUniform = glGetUniformLocation(program, name);

    /* Set location of uniform sampler variable */
    glUniform1i(TextureUniform, index);
}
void ActivateTexture(int index, GLuint TextureId)
{
    glActiveTexture(GL_TEXTURE0+index);
    glBindTexture(GL_TEXTURE_2D, TextureId);
}
