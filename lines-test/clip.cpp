#include <catch2/catch_amalgamated.hpp>

#include <algorithm>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"


TEST_CASE( "Partially offscreen", "[clip]" )
{
	Surface surface( 640, 480 );
	surface.clear();

	// Only one sample. You may want to extend this with your own variants.
	// Minimally, you should test with lines that aren't axis aligned.
	
	SECTION( "go right" )
	{
		draw_line_solid( surface,
			{ 1.f, 240.f },
			{ 1920.f, 240.f },
			{ 255, 255, 255 }
		);

		auto const pixels = max_col_pixel_count( surface );
		REQUIRE( 1 == pixels );
	}

	SECTION( "half of line is clipped -> horizontal" )
	{
		draw_line_solid( surface,
			{ 100.f, 479.f },
			{ 200.f, 480.f },
			{ 255, 255, 255 }
		);

		auto const pixels = row_pixel_count( surface, 479 );
		
		REQUIRE( std::abs(static_cast<int>(pixels) - 50) < 10 );
	}

	SECTION( "half of line is clipped -> vertical" )
	{
		draw_line_solid( surface,
			{ 639.f, 100.f },
			{ 640.f, 200.f },
			{ 255, 255, 255 }
		);

		auto const pixels = col_pixel_count( surface, 639 );
		
		REQUIRE( std::abs(static_cast<int>(pixels) - 50) < 10 );
	}

	SECTION( "line is clipped on both sides" )
	{
		draw_line_solid( surface,
			{ -100.f, 100.f },
			{ 740.f, 100.f },
			{ 255, 255, 255 }
		);

		auto const pixels = row_pixel_count( surface, 100 );
		
		REQUIRE( pixels == 640 );
	}
}
