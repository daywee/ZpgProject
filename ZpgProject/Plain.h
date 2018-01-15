#pragma once

const int plainVertexCount = 6;

const float plain[] = {
	// pos - x3		normal - x3		coord - x2
	1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	-1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
};

GLuint plainIndices[] =
{
	0, 1, 3, // First Triangle
	1, 2, 3  // Second Triangle
};