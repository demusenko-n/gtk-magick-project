#pragma once
#include <gtkmm.h>
#include <queue>
#include <thread>
#include "BackgroundWorker.h"
#include "Image.h"
#include "Watermark.h"

namespace Lib
{

/**
 * \brief Lib::ImageAsync class is a wrapper over Lib::Image for asynchonious (non-blocking) processing.
 */
class ImageAsync final
{
public:
	/**
	 * \brief Asynchronously loads an image from file.
	 * \param imagePath path to the image file.
	 * \param completionHandler function to execute after completion (optional).
	 */
	void load(
		const std::string& imagePath,
		std::function<void()> completionHandler = [] {});

	/**
	 * \brief Asynchronously resizes an image, ignores current aspect ratio.
	 * \param width new width.
	 * \param height new height.
	 * \param completionHandler function to execute after completion (optional).
	 */
	void resize(
		size_t width, size_t height,
		std::function<void()> completionHandler = [] {});

	/**
	 * \brief Asynchronously rotates an image.
	 * \param degrees degrees as decimal number (0-360).
	 * \param completionHandler function to execute after completion (optional).
	 */
	void rotate(
		double degrees, std::function<void()> completionHandler = [] {});

	/**
	 * \brief Asynchronously saves an image on the disk.
	 * \param destinationPath path where to save the image.
	 * \param completionHandler function to execute after completion (optional).
	 */
	void save(
		const std::string& destinationPath,
		std::function<void()> completionHandler = [] {});

	/**
	 * \brief Asynchronously adds the watermark to the image.
	 * \param watermarkPath path to the watermark object.
	 * \param completionHandler function to execute after completion (optional).
	 */
	void addWatermark(
		const std::string& watermarkPath,
		std::function<void()> completionHandler = [] {});

	/**
	 * \brief Asynchronously draws the image on the Gtk::Image object.
	 * \param image Gtk::Image object for drawing.
	 * \param completionHandler function to execute after completion (optional).
	 */
	void setOnImage(Gtk::Image& image);

private:
	BackgroundWorker worker_;
	Lib::Image image_;
};
}  // namespace Lib