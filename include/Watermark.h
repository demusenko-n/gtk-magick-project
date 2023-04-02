#pragma once
#include <Magick++.h>

namespace Lib
{

/**
 * \brief Lib::Watermark class is a wrapper over Magick::Image with meaning of watermark.
 */
class Watermark
{
public:
	/**
	 * \brief Create a new Watermark object keeping its transparency (use only for png) 
	 * \param watermarkPath Path to the watermark image.
	 */
	Watermark(const std::string& watermarkPath);

	/**
	 * \brief Create a new Watermark object with specified transparency coefficient
	 * \param watermarkPath Path to the watermark image.
	 * \param transparencyCoefficient alpha (0.0 - 1.0).
	 */
	Watermark(const std::string& watermarkPath, double transparencyCoefficient);

	/**
	 * \brief Apply the watermark to the image
	 * \param image Image to apply a watermark.
	 * \param transparencyCoefficient alpha (0.0 - 1.0).
	 */
	void apply(Magick::Image& image);

private:
	Magick::Image watermark_;
};
};	// namespace Lib