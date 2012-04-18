// Include the SOIL library for loading images into OpenGL
#include SOIL.h

// Create a GLuint texture reference by loading an image using SOIL
GLuint texture = SOIL_load_OGL_texture("texture.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

// Check texture was properly loaded
if(texture == 0)
	cout << "SOIL loading error: " << SOIL_last_result();
	
// Bind our texture
glBindTexture(GL_TEXTURE_2D, texture);

// Apply properties
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

// Enable texture mapping
glEnable(GL_TEXTURE_2D);

// Apply texture map - assuming quadrilaterals since we are doing a sierpinski carpet fractal
// Assign a series of texture coordinates and vertices
glBegin(GL_QUADS);
// glTexCoord2d(double, double);
// glVertex2d(double, double);

// glTextCoord2d(double, double);
// glVertex2d(double, double);
// ...
glEnd();