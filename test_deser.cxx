
#define BOOST_TEST_MODULE parse test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "parse.h"

#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "Polygon.h"


BOOST_AUTO_TEST_CASE(parse_normal)
{
    using FeatureTypes = std::tuple<
            Circle,
            Square,
            Triangle,
            Polygon>;

    std::istringstream is(
            "Square 1 1 2 2\n"             // Square 0
            "Square 2 2 4 4\n"             // Square 1
            "Triangle -3 -3 -2 -2 1 1\n"   // Triangle 0
            "Circle -3 -3 5" );            // Circle 0

    auto features = parse<FeatureTypes>( is );

    const auto& squares   = std::get< std::vector<Square> >( features );
    const auto& circles   = std::get< std::vector<Circle> >( features );
    const auto& triangles = std::get< std::vector<Triangle> >( features );
    const auto& polygons  = std::get< std::vector<Polygon> >( features );

    BOOST_CHECK_EQUAL( squares.size(),   2 );
    BOOST_CHECK_EQUAL( triangles.size(), 1 );
    BOOST_CHECK_EQUAL( circles.size(),   1 );
    BOOST_CHECK_EQUAL( polygons.size(),  0 );

    BOOST_CHECK_EQUAL( squares.at(0),   Square( {1,1}, {2,2}) );
    BOOST_CHECK_EQUAL( squares.at(1),   Square( {2,2}, {4,4}) );
    BOOST_CHECK_EQUAL( triangles.at(0), Triangle( {-3, -3}, {-2, -2}, {1, 1} ) );
    BOOST_CHECK_EQUAL( circles.at(0),   Circle( {-3, -3}, 5 ) );
}



BOOST_AUTO_TEST_CASE(parse_with_empty_lines)
{
    using FeatureTypes = std::tuple<
            Circle,
            Square,
            Triangle,
            Polygon>;

    std::istringstream is(
            "Square 1 1 2 2\n"             // Square 0
            "\n"                           //
            "Square 2 2 4 4\n"             // Square 1
            "Triangle -3 -3 -2 -2 1 1\n"   // Triangle 0
            "Circle -3 -3 5\n" );          // Circle 0

    auto features = parse<FeatureTypes>( is );

    const auto& squares   = std::get< std::vector<Square> >( features );
    const auto& circles   = std::get< std::vector<Circle> >( features );
    const auto& triangles = std::get< std::vector<Triangle> >( features );
    const auto& polygons  = std::get< std::vector<Polygon> >( features );

    BOOST_CHECK_EQUAL( squares.size(),   2 );
    BOOST_CHECK_EQUAL( triangles.size(), 1 );
    BOOST_CHECK_EQUAL( circles.size(),   1 );
    BOOST_CHECK_EQUAL( polygons.size(),  0 );

    BOOST_CHECK_EQUAL( squares.at(0),   Square( {1,1}, {2,2}) );
    BOOST_CHECK_EQUAL( squares.at(1),   Square( {2,2}, {4,4}) );
    BOOST_CHECK_EQUAL( triangles.at(0), Triangle( {-3, -3}, {-2, -2}, {1, 1} ) );
    BOOST_CHECK_EQUAL( circles.at(0),   Circle( {-3, -3}, 5 ) );
}



BOOST_AUTO_TEST_CASE(parse_fail_cant_parse_triangle)
{
    using FeatureTypes = std::tuple<
            Circle,
            Square,
            Polygon>;

    std::istringstream is(
            "Square 1 1 2 2\n"             // Square 0
            "Square 2 2 4 4\n"             // Square 1
            "Triangle -3 -3 -2 -2 1 1\n"   // Triangle 0
            "Circle -3 -3 5" );            // Circle 0

    auto features = parse<FeatureTypes>( is );

    BOOST_CHECK( is.fail() );
}



BOOST_AUTO_TEST_CASE(parse_throw_cant_parse_triangle)
{
    using FeatureTypes = std::tuple<
            Circle,
            Square,
            Polygon>;

    std::istringstream is(
            "Square 1 1 2 2\n"             // Square 0
            "Square 2 2 4 4\n"             // Square 1
            "Triangle -3 -3 -2 -2 1 1\n"   // Triangle 0
            "Circle -3 -3 5" );            // Circle 0

    is.exceptions( std::ios::failbit );

    try {
       parse<FeatureTypes>( is );
       BOOST_FAIL( "Must have thrown as Triangle is not in the FeatureTypes");
    }
    catch( parsing_failure& ) {}
}



BOOST_AUTO_TEST_CASE(parse_recover_after_errors_wexceptions)
{
    using FeatureTypes = std::tuple<
            Circle,
            Square,
            Triangle,
            Polygon>;

    std::istringstream is(
            "Square 1 1 2 2\n"                  // Square 0
            "Square 2 2 4 4\n"                  // Square 1
            "Hexagon 1 1 2 2 3 3 4 4 5 5 6 6\n" // Some Feature we want to skip
            "Triangle -3 -3 -2 -2 1 1\n"        // Triangle 0
            "Circle -3 -3 5"                    // Circle 0
            );

    is.exceptions( std::ios::failbit );

    using FeatureVectors = tuple_of_vectors_t<FeatureTypes>;

    FeatureVectors features;

    while( not is.eof() ) {
        try {
            parse<FeatureTypes>( is, features );
        }
        catch( parsing_failure& e ) {
            auto is_starts_with = []( std::string str, std::string pattern ) { return 0 == str.compare( 0, pattern.size(), pattern ); };
            if( is_starts_with( e.line(), "Hexagon") ) {
                continue;  // We know there are Hexagons, but we don't want to handle them
            }
            else {
                throw;
            }
        }
        catch ( ... ) {
            BOOST_FAIL("Should be no other exceptions");
        }
    }

    const auto& squares   = std::get< std::vector<Square> >( features );
    const auto& circles   = std::get< std::vector<Circle> >( features );
    const auto& triangles = std::get< std::vector<Triangle> >( features );
    const auto& polygons  = std::get< std::vector<Polygon> >( features );

    BOOST_CHECK_EQUAL( squares.size(),   2 );
    BOOST_CHECK_EQUAL( triangles.size(), 1 );
    BOOST_CHECK_EQUAL( circles.size(),   1 );
    BOOST_CHECK_EQUAL( polygons.size(),  0 );

    BOOST_CHECK_EQUAL( squares.at(0),   Square( {1,1}, {2,2}) );
    BOOST_CHECK_EQUAL( squares.at(1),   Square( {2,2}, {4,4}) );
    BOOST_CHECK_EQUAL( triangles.at(0), Triangle( {-3, -3}, {-2, -2}, {1, 1} ) );
    BOOST_CHECK_EQUAL( circles.at(0),   Circle( {-3, -3}, 5 ) );

}



BOOST_AUTO_TEST_CASE(parse_recover_after_errors_using_flags)
{
    using FeatureTypes = std::tuple<
            Circle,
            Triangle,
            Square,
            Polygon>;

    std::istringstream is(
            "Square 1 1 2 2\n"                  // Square 0
            "Square 2 2 4 4\n"                  // Square 1
            "Hexagon 1 1 2 2 3 3 4 4 5 5 6 6\n" // Some Feature we want to skip
            "Triangle -3 -3 -2 -2 1 1\n"        // Triangle 0
            "Circle -3 -3 5" );                 // Circle 0

    using FeatureVectors = tuple_of_vectors_t<FeatureTypes>;

    FeatureVectors features;

    while( not is.eof() and not is.bad() ) {
        parse<FeatureTypes>( is, features );
        if( is.fail() ) {
            is.clear( is.rdstate() & ( ~ std::ios::failbit) );
        }
        BOOST_CHECK( not is.bad() );
    }

    const auto& squares   = std::get< std::vector<Square> >( features );
    const auto& circles   = std::get< std::vector<Circle> >( features );
    const auto& triangles = std::get< std::vector<Triangle> >( features );
    const auto& polygons  = std::get< std::vector<Polygon> >( features );

    BOOST_CHECK_EQUAL( squares.size(),   2 );
    BOOST_CHECK_EQUAL( triangles.size(), 1 );
    BOOST_CHECK_EQUAL( circles.size(),   1 );
    BOOST_CHECK_EQUAL( polygons.size(),  0 );

    BOOST_CHECK_EQUAL( squares.at(0),   Square( {1,1}, {2,2}) );
    BOOST_CHECK_EQUAL( squares.at(1),   Square( {2,2}, {4,4}) );
    BOOST_CHECK_EQUAL( triangles.at(0), Triangle( {-3, -3}, {-2, -2}, {1, 1} ) );
    BOOST_CHECK_EQUAL( circles.at(0),   Circle( {-3, -3}, 5 ) );
}

