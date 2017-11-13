#include "TextureLoader.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <GL/glew.h>

TextureLoader::TextureLoader()
{
}


TextureLoader::~TextureLoader()
{
}

GLuint TextureLoader::load(std::string path, GLuint programId)
{
	cv::Mat image = cv::imread(path);
	// cv::imshow("texture image", image);
	// cv::waitKey(1);

	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, image.ptr());

	glActiveTexture(GL_TEXTURE0);
	glGenerateMipmap(GL_TEXTURE_2D);

	image.release();

	return textureId;
}
