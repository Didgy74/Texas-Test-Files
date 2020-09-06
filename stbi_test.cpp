
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <Texas/Texas.hpp>

#include <array>
#include <cstring>
#include <iostream>



int main()
{
	std::array pathsToTest = { 
		"data/PNG/valid/01.png",
		"data/PNG/valid/02.png",
		"data/PNG/valid/03.png",
		"data/PNG/valid/04.png",
		};

	for (auto file : pathsToTest)
	{
		std::cout << "File: " << file << std::endl;


		int stbImgWidth = 0;
		int stbImgHeight = 0;
		int stbChannelCount = 0;
		char* stbImg = (char*)stbi_load(file, &stbImgWidth, &stbImgHeight, &stbChannelCount, 0);
		if (!stbImg)
		{
			std::cout << "stbi failed to load the file." << std::endl;
			std::exit(-1);
		}

		Texas::ResultValue<Texas::Texture> texImgResult = Texas::loadFromPath(file);
		if (!texImgResult.isSuccessful())
		{
			std::cout << "Texas failed to load: " << texImgResult.errorMessage() << std::endl;
			std::exit(-1);
		}
		Texas::Texture texImg = std::move(texImgResult.value());

		if (texImg.baseDimensions().width != (uint64_t)stbImgWidth)
		{
			std::cout << "Image width to not match." << std::endl;
			std::exit(-1);
		}

		if (texImg.baseDimensions().height != (uint64_t)stbImgHeight)
		{
			std::cout << "Image height to not match." << std::endl;
			std::exit(-1);
		}

		if (texImg.baseDimensions().depth != 1)
		{
			std::cout << "Image depth does not match." << std::endl;
			std::exit(-1);
		}

		auto memCmpResult = memcmp(stbImg, texImg.rawBufferSpan().data(), texImg.rawBufferSpan().size());
		if (memCmpResult != 0)
		{
			std::cout << "Byte at position " << memCmpResult << " does not match." << std::endl;
			std::exit(-1);
		}
	}
	
	return 0;
}