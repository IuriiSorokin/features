
#define BOOST_TEST_MODULE deser test
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



BOOST_AUTO_TEST_CASE(parse_with_empty_line)
{
    using FeatureTypes = std::tuple<
            Circle,
            Square,
            Triangle,
            Polygon>;

    std::istringstream is(
            "Square 1 1 2 2\n"             // Square 0
            "\n"
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
