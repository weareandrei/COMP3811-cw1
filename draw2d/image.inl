inline
ColorU8_sRGB_Alpha ImageRGBA::get_pixel( Index aX, Index aY ) const
{
	assert( aX < mWidth && aY < mHeight ); // Leave this at the top of the function.
	
	Index index = get_linear_index(aX, aY);
	
	// Retrieve the color at the calculated index
	ColorU8_sRGB_Alpha pixelColor = reinterpret_cast<ColorU8_sRGB_Alpha*>(mData)[index];

	return pixelColor;
}

inline
auto ImageRGBA::get_width() const noexcept -> Index
{
	return mWidth;
}
inline
auto ImageRGBA::get_height() const noexcept -> Index
{
	return mHeight;
}

inline
std::uint8_t* ImageRGBA::get_image_ptr() noexcept
{
	return mData;
}
inline
std::uint8_t const* ImageRGBA::get_image_ptr() const noexcept
{
	return mData;
}

inline
ImageRGBA::Index ImageRGBA::get_linear_index( Index aX, Index aY ) const noexcept
{
	Index bytesPerPixel = sizeof(ColorU8_sRGB_Alpha);
	Index linearIndex = (aY * mWidth + aX) * bytesPerPixel;
	return linearIndex;
}
