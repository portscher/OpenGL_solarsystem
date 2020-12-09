#ifndef SOLAR_SYSTEM_HELPERS
#define SOLAR_SYSTEM_HELPERS

void createCubeMesh(GLuint* VBO, GLuint* CBO, GLuint* IBO);
void createQuadMesh(GLuint* VBO, GLuint* CBO, GLuint* NBO, GLuint* UVBO, GLuint* IBO, float* rgb);
void createCube(GLuint* VBO, GLuint* VAO);
void readMeshFile(char* filename, float scale, GLuint* VBO, GLuint* CBO, GLuint* NBO, GLuint* UVBO, GLuint* IBO, float* rgb);
void AddShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType);
void CreateShaderProgram(int programIndex, char* vsPath, char* fsPath, char* gsPath);
void SetupTexture(GLuint *TextureID, char* filename);
void SetUpCubeMapTexture(GLuint *TextureID);
void BindUniform4f(char* name, GLuint program, float* mat);
void BindUniform3f(char* name, GLuint program, float* vec);
void BindUniform1f(char* name, GLuint program, float val);
void BindUniform1i(char* name, GLuint program, int val);
int BindBasics(GLuint VBO, GLuint CBO, GLuint IBO, GLuint NBO, GLuint UVBO);
void printMatrix(float* mat);
void LookAt(float* position, float* target, float* uup, float* result);
float clamp(float val, float max, float min);

void createAndAttachColorBuffer(GLuint* id, int i);
void DrawFrontScreen();
void EnableTexture(char* name, GLuint program, int index);
void ActivateTexture(int index, GLuint TextureId);

#endif
