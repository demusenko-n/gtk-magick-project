#pragma once
#include <Magick++.h>

namespace Lib
{

/**
 * \brief Lib::Image class is simple wrapper over Magick::Image for image processing.
 */
class Image
{
public:
	/**
	 * Create a new Image object.
	 * \brief Constructor.
	 */
	Image();

	/**
	 * \brief Checks if object contains valid image.
	 * \returns true if image is valid.
	 */
	bool isInitialized();

	/**
	 * \brief Loads an image from file.
	 * \param imagePath path to the image file.
	 */
	void load(const std::string& imagePath);

	/**
	 * \brief Resizes an image, ignores current aspect ratio.
	 * \param width new width.
	 * \param height new height.
	 */
	void resize(size_t width, size_t height);

	/**
	 * \brief Rotates an image.
	 * \param degrees degrees as decimal number (0-360).
	 */
	void rotate(double degrees);

	/**
	 * \brief Saves an image on the disk.
	 * \param destinationPath path where to save the image.
	 */
	void save(const std::string& destinationPath);

	/**
	 * \brief Converts an image to blob.
	 * \returns blob containing image data.
	 */
	Magick::Blob toBlob();

	/**
	 * \brief Retrieves underlying Magick::Image object.
	 * \returns Underlying object.
	 */
	Magick::Image& raw();

private:
	Magick::Image imageMagick_;
};

};	// namespace Lib
