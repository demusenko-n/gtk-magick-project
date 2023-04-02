#include "Image.h"

namespace Lib
{
Image::Image() = default;

bool Image::isInitialized()
{
	return imageMagick_.isValid();
}

void Image::load(const std::string& imagePath)
{
	imageMagick_.read(imagePath);
}

void Image::resize(const size_t width, const size_t height)
{
	Magick::Geometry geometry(width, height);
	geometry.aspect(true);
	imageMagick_.resize(geometry);
}

void Image::rotate(const double degrees)
{
	imageMagick_.rotate(degrees);
}


void Image::save(const std::string& destinationPath)
{
	imageMagick_.write(destinationPath);
}

Magick::Blob Image::toBlob()
{
	Magick::Blob blob;
	imageMagick_.write(&blob);
	return blob;
}

Magick::Image& Image::raw() {
	return imageMagick_;
}
}  // namespace Lib