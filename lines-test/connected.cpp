#include <catch2/catch_amalgamated.hpp>

#include <algorithm>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"


TEST_CASE( "No gaps", "[connect]" )
{
	Surface surface( 200, 200 );
	surface.clear();

	SECTION( "horizontal" )
	{
		draw_line_solid( surface,
			{ 10.f, 170.f },
			{ 110.f, 170.f },
			{ 255, 255, 255 }
		);

		auto const counts = count_pixel_neighbours( surface );

		// There are exactly two pixels with one neighbour: one at each end of
		// the line
		REQUIRE( 2 == counts[1] );

		// There should be a non-zero number of pixels with two neighbours, as
		// the line is longer than 2 pixels.
		REQUIRE( counts[2] > 0 );

		// No pixels should have zero neighbours (=isolated)
		REQUIRE( 0 == counts[0] );

		// There should be no pixels with more than two neighbours!
		for( std::size_t i = 3; i < counts.size(); ++i )
			REQUIRE( 0 == counts[i]  );
	}
	SECTION( "vertical" )
	{
		draw_line_solid( surface,
			{ 64.f, 28.f },
			{ 64.f, 100.f },
			{ 255, 255, 255 }
		);

		auto const counts = count_pixel_neighbours( surface );
		REQUIRE( 2 == counts[1] );
		REQUIRE( counts[2] > 0 );

		REQUIRE( 0 == counts[0] );

		for( std::size_t i = 3; i < counts.size(); ++i )
			REQUIRE( 0 == counts[i]  );
	}

	SECTION( "diagonal" )
	{
		draw_line_solid( surface,
			{ 10.f, 100.f },
			{ 100.f, 10.f },
			{ 255, 255, 255 }
		);

		auto const counts = count_pixel_neighbours( surface );
		REQUIRE( 2 == counts[1] );
		REQUIRE( counts[2] > 0 );

		REQUIRE( 0 == counts[0] );

		for( std::size_t i = 3; i < counts.size(); ++i )
			REQUIRE( 0 == counts[i]  );
	}

	SECTION("line b starts from the end of line a")
	{
		draw_line_solid(surface,
						{10.f, 100.f},
						{100.f, 10.f},
						{255, 0, 0});

		draw_line_solid(surface,
						{100.f, 10.f},
						{150.f, 50.f},
						{0, 255, 0});

		int linearIndex = surface.get_linear_index(100.f, 10.f);

		// Get color of pixel at (100.f, 10.f)
		ColorU8_sRGB actualColor;
		actualColor.r = surface.get_surface_ptr()[linearIndex];
		actualColor.g = surface.get_surface_ptr()[linearIndex + 1];
		actualColor.b = surface.get_surface_ptr()[linearIndex + 2];
		
		ColorU8_sRGB expectedColor;
		expectedColor.r = 0;
		expectedColor.g = 255;
		expectedColor.b = 0;
		
		REQUIRE(actualColor.r == expectedColor.r);
		REQUIRE(actualColor.g == expectedColor.g);
		REQUIRE(actualColor.b == expectedColor.b);
	}

}
