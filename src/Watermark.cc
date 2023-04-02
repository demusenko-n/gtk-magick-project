#include "Watermark.h"

namespace Lib
{

Watermark::Watermark(const std::string& watermarkPath)
	: watermark_(watermarkPath)
{
	watermark_.alphaChannel(Magick::AlphaChannelOption::SetAlphaChannel);
}

Watermark::Watermark(const std::string& watermarkPath,
					 const double transparencyCoefficient)
	: watermark_(watermarkPath)
{
	watermark_.alphaChannel(Magick::AlphaChannelOption::ActivateAlphaChannel);
	watermark_.alpha(
		static_cast<unsigned int>(QuantumRange * transparencyCoefficient));
}

void Watermark::apply(Magick::Image& image)
{
	auto geometry = image.size();
	geometry.aspect(true);
	watermark_.resize(geometry);
	image.composite(watermark_, MagickCore::GravityType::CenterGravity,
					MagickCore::CompositeOperator::DissolveCompositeOp);
}

};	// namespace Lib