#pragma once
#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();

	GLuint getVertexShader();
	GLuint getFragmentShader();
	GLuint getShaderProgram();
	void checkStatus();

private:
	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"void main () {"
		"     gl_Position = vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
};

