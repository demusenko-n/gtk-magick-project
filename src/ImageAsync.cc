#include "ImageAsync.h"

namespace Lib
{
void ImageAsync::load(const std::string& imagePath,
					  std::function<void()> completionHandler)
{
	worker_.addTask(
		[this, imagePath, completionHandler = std::move(completionHandler)]
		{
			image_.load(imagePath);
			completionHandler();
		});
}

void ImageAsync::resize(const size_t width, const size_t height,
						std::function<void()> completionHandler)
{
	worker_.addTask(
		[this, width, height, completionHandler = std::move(completionHandler)]
		{
			image_.resize(width, height);
			completionHandler();
		});
}

void ImageAsync::rotate(const double degrees,
						std::function<void()> completionHandler)
{
	worker_.addTask(
		[this, degrees, completionHandler = std::move(completionHandler)]
		{
			image_.rotate(degrees);
			completionHandler();
		});
}

void ImageAsync::save(const std::string& destinationPath,
					  std::function<void()> completionHandler)
{
	worker_.addTask(
		[this, destinationPath,
		 completionHandler = std::move(completionHandler)]
		{
			image_.save(destinationPath);
			completionHandler();
		});
}

void ImageAsync::addWatermark(const std::string& watermarkPath,
							  std::function<void()> completionHandler)
{
	worker_.addTask(
		[this, watermarkPath, completionHandler = std::move(completionHandler)]
		{
			Lib::Watermark watermark(watermarkPath);
			watermark.apply(image_.raw());
			completionHandler();
		});
}

void ImageAsync::setOnImage(Gtk::Image& image)
{
	worker_.addTask(
		[this, &image]
		{
			auto blob = image_.toBlob();
			auto pixbuf_loader = Gdk::PixbufLoader::create();
			pixbuf_loader->write(reinterpret_cast<const guint8*>(blob.data()),
								 blob.length());
			pixbuf_loader->close();
			Glib::signal_idle().connect_once(
				[this, &image, pixbuf_loader]
				{ image.set(pixbuf_loader->get_pixbuf()); });
		});
}
};	// namespace Lib
