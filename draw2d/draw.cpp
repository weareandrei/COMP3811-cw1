#include "draw.hpp"

#include <algorithm>

#include <cmath>

#include "surface.hpp"

void draw_line_solid(Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor)
{
	// Line gradient
    int dx = std::abs(aBegin.x - aEnd.x);
    int dy = std::abs(aBegin.y - aEnd.y);

	// Direction of each pixel step
    int stepX = aBegin.x < aEnd.x ? 1 : -1;
    int stepY = aBegin.y < aEnd.y ? 1 : -1;
    int err = dx - dy;

	// Initial x,y values
    int x = aBegin.x;
    int y = aBegin.y;

	float threshold = 2;
	
    while (true)
    {
    	// If we drawn all pixels and came to end point then we stop
		if (std::abs(x - aEnd.x) <= threshold && std::abs(y - aEnd.y) <= threshold)
    	{
    		break;
    	}
    	
    	// Simplified clipping
        if (x >= 0 && x < aSurface.get_width() && y >= 0 && y < aSurface.get_height())
        {
        	aSurface.set_pixel_srgb(x, y, aColor);
        }

    	// Bresenham's line drawing algorithm
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x += stepX;
        }
        if (e2 < dx)
        {
            err += dx;
            y += stepY;
        }
    }
}

template<typename T>
T clamp(T value, T min, T max) {
    return std::max(min, std::min(value, max));
}

// Compute area of triangle using its vertices
float triangle_area(const Vec2f& p0, const Vec2f& p1, const Vec2f& p2) {
    return 0.5f * ((p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y));
}

void draw_triangle_solid(Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor) {
    // Calculate bounding box of the triangle
    float minX = std::floor(std::min({aP0.x, aP1.x, aP2.x}));
    float maxX = std::ceil(std::max({aP0.x, aP1.x, aP2.x}));
    float minY = std::floor(std::min({aP0.y, aP1.y, aP2.y}));
    float maxY = std::ceil(std::max({aP0.y, aP1.y, aP2.y}));

    // Iterate over the bounding box
    for (float y = minY; y <= maxY; y++) {
        for (float x = minX; x <= maxX; x++) {
            // Calculate barycentric coordinates
            float alpha = triangle_area(aP1, aP2, {x, y}) / triangle_area(aP1, aP2, aP0);
            float beta = triangle_area(aP2, aP0, {x, y}) / triangle_area(aP2, aP0, aP1);
            float gamma = triangle_area(aP0, aP1, {x, y}) / triangle_area(aP0, aP1, aP2);

            // Check if the point is inside the triangle
            if (alpha >= 0 && beta >= 0 && gamma >= 0) {
            	if (x >= 0 && x < aSurface.get_width() && y >= 0 && y < aSurface.get_height())
            	{
            		aSurface.set_pixel_srgb(static_cast<Surface::Index>(x), static_cast<Surface::Index>(y), aColor);
            	}
            }
        }
    }
}

void draw_triangle_interp( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2 )
{
	// Calculate bounding box of the triangle
	float minX = std::floor(std::min({aP0.x, aP1.x, aP2.x}));
	float maxX = std::ceil(std::max({aP0.x, aP1.x, aP2.x}));
	float minY = std::floor(std::min({aP0.y, aP1.y, aP2.y}));
	float maxY = std::ceil(std::max({aP0.y, aP1.y, aP2.y}));

	// Iterate over the bounding box
	for (float y = minY; y <= maxY; y++) {
		for (float x = minX; x <= maxX; x++) {
			// Calculate barycentric coordinates
			float alpha = triangle_area(aP1, aP2, {x, y}) / triangle_area(aP1, aP2, aP0);
			float beta = triangle_area(aP2, aP0, {x, y}) / triangle_area(aP2, aP0, aP1);
			float gamma = triangle_area(aP0, aP1, {x, y}) / triangle_area(aP0, aP1, aP2);

			// Check if the point is inside the triangle
			if (alpha >= 0 && beta >= 0 && gamma >= 0) {
				// Interpolate color in linear RGB space
				ColorF interpolatedColor = {
					alpha * aC0.r + beta * aC1.r + gamma * aC2.r,
					alpha * aC0.g + beta * aC1.g + gamma * aC2.g,
					alpha * aC0.b + beta * aC1.b + gamma * aC2.b
				};

				// Convert linear RGB to sRGB before setting the pixel color
				ColorU8_sRGB sRGBColor = linear_to_srgb(interpolatedColor);

				// Set pixel color
				if (x >= 0 && x < aSurface.get_width() && y >= 0 && y < aSurface.get_height()) {
					aSurface.set_pixel_srgb(static_cast<Surface::Index>(x), static_cast<Surface::Index>(y), sRGBColor);
				}
			}
		}
	}
}
	
void draw_rectangle_solid( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aMinCorner;   // is properly implemented.
	(void)aMaxCorner;
	(void)aColor;
}

void draw_rectangle_outline( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments
	(void)aMinCorner;
	(void)aMaxCorner;
	(void)aColor;
}
