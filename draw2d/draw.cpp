#include "draw.hpp"

#include <algorithm>

#include <cmath>

#include "surface.hpp"

// Unfinished function
Vec2f clip_coordinates_on_line(Vec2f point, int dx, int dy, int surfaceWidth, int surfaceHeight)
{
	// Calculate region codes for the two endpoints
	int code1 = 0, code2 = 0;

	if (point.x < 0) code1 |= 1;       // Left of the surface
	if (point.x > surfaceWidth) code1 |= 2;  // Right of the surface
	if (point.y < 0) code1 |= 4;       // Above the surface
	if (point.y > surfaceHeight) code1 |= 8;  // Below the surface

	// Check if both endpoints are inside the surface
	if (code1 == 0) {
		return point;
	}

	// Both endpoints are outside the surface, so the line is completely outside
	if ((code1 & code2) != 0) {
		return point; // Return the original point (it will be clipped later by the main function)
	}

	// Calculate the intersection point and update the corresponding endpoint
	if (code1 & 1) {
		point.y += dy * (0 - point.x) / dx;
		point.x = 0;
	} else if (code1 & 2) {
		point.y += dy * (surfaceWidth - point.x) / dx;
		point.x = surfaceWidth;
	} else if (code1 & 4) {
		point.x += dx * (0 - point.y) / dy;
		point.y = 0;
	} else if (code1 & 8) {
		point.x += dx * (surfaceHeight - point.y) / dy;
		point.y = surfaceHeight;
	}

	return point;
}

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
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: Remove the following when you start your implementation!
	//TODO: This draws a solid triangle until you implement the function
	//TODO: properly. (This is such that you can see the asteroids with solid
	//TODO: shading until that point.)
	draw_triangle_solid( aSurface, aP0, aP1, aP2, linear_to_srgb( aC0 ) );
	(void)aC1;
	(void)aC2;
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
