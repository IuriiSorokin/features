
#define BOOST_TEST_MODULE Parser test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Parser.h"
#include "streamers.h"

BOOST_AUTO_TEST_CASE(parse_normal)
{

    std::istringstream is(
            "Square 1 1 2 2\n"                     // Square 0  Format is: "Square x0 y0 x1 y1". Other two vertices are evaluated. Vertices numbered counterclockwise.
            "Square 2 2 4 4\n"                     // Square 1
            "Triangle -3 -3 -2 -2 1 1\n"           // Triangle 0
            "Circle -3 -3 5\n"                     // Circle 0
            "Polygon 6 1 1 2 2 3 3 4 4 5 5 6 6" ); // Polygon 0   Format is: "Polygon N x0 y0 x1 y1 ... xN yN" where N - number of vertices

    auto features = Parser<Features>().parse( is );

    const auto& squares   = std::get< std::vector<Square> >( features );
    const auto& circles   = std::get< std::vector<Circle> >( features );
    const auto& triangles = std::get< std::vector<Triangle> >( features );
    const auto& polygons  = std::get< std::vector<Polygon> >( features );

    BOOST_CHECK_EQUAL( squares.size(),   2 );
    BOOST_CHECK_EQUAL( triangles.size(), 1 );
    BOOST_CHECK_EQUAL( circles.size(),   1 );
    BOOST_CHECK_EQUAL( polygons.size(),  1 );

    BOOST_CHECK_EQUAL( squares.at(0),   Square( {1,1}, {2,2}) );
    BOOST_CHECK_EQUAL( squares.at(1),   Square( {2,2}, {4,4}) );
    BOOST_CHECK_EQUAL( triangles.at(0), Triangle( {-3, -3}, {-2, -2}, {1, 1} ) );
    BOOST_CHECK_EQUAL( circles.at(0),   Circle( {-3, -3}, 5 ) );
    BOOST_CHECK_EQUAL( polygons.at(0),  Polygon( {{1., 1.}, {2., 2.}, {3., 3.}, {4., 4.}, {5., 5.}, {6., 6.}  } ) );
}



BOOST_AUTO_TEST_CASE(parse_recover_after_errors_wexceptions)
{
    std::istringstream is( "Circle   5.2 6.3 1.7  "   // Circle 0
                           "Square   1 1 1 1      "   // Square 0
                           "Triangle 1 1 1 1      "   // incomplete
                           "Square 2 2 2          "   // incomplete
                           "safasdf               "   // garbage
                           "Polygon 10 1 1        "   // incomplete
                           "Square 3 3 3 3 3      "   // Square 1 and trailing garbage
                           "Square 4 4 4 4        "   // Square 2
            );
    is.exceptions( std::ios::failbit );

    FeatureVectors fv;
    Parser<Features> parser;

    while( is.good() ) {
        try {
            parser.parse( is, fv );
        }
        catch( std::ios::failure& e ) {
            is.clear( is.rdstate() & (~std::ios::failbit) );
        }
        catch ( ... ) {
            BOOST_FAIL("Should not throw other exceptions");
        }
    }

    const auto& squares   = std::get< std::vector<Square> >( fv );
    const auto& circles   = std::get< std::vector<Circle> >( fv );
    const auto& triangles = std::get< std::vector<Triangle> >( fv );
    const auto& polygons  = std::get< std::vector<Polygon> >( fv );

    BOOST_CHECK_EQUAL( squares.size(),   3 );
    BOOST_CHECK_EQUAL( triangles.size(), 0 );
    BOOST_CHECK_EQUAL( circles.size(),   1 );
    BOOST_CHECK_EQUAL( polygons.size(),  0 );

    BOOST_CHECK_EQUAL( circles.at(0),   Circle( { 5.2, 6.3},  1.7 ) );

    BOOST_CHECK_EQUAL( squares.at(0),   Square( {1,1}, {1,1}) );
    BOOST_CHECK_EQUAL( squares.at(1),   Square( {3,3}, {3,3}) );
    BOOST_CHECK_EQUAL( squares.at(2),   Square( {4,4}, {4,4}) );

}



BOOST_AUTO_TEST_CASE(parse_recover_after_errors_using_flags)
{
    std::istringstream is( "Circle   5.2 6.3 1.7  "   // Circle 0
                           "Square   1 1 1 1      "   // Square 0
                           "Triangle 1 1 1 1      "   // incomplete
                           "Square 2 2 2          "   // incomplete
                           "safasdf               "   // garbage
                           "Polygon 10 1 1        "   // incomplete
                           "Square 3 3 3 3 3      "   // Square 1 and trailing garbage
                           "Square 4 4 4 4        "   // Square 2
            );

    FeatureVectors fv;
    Parser<Features> parser;

    while( is.good() ) {
        parser.parse( is, fv );
        is.clear( is.rdstate() & (~std::ios::failbit) );
    }

    const auto& squares   = std::get< std::vector<Square> >( fv );
    const auto& circles   = std::get< std::vector<Circle> >( fv );
    const auto& triangles = std::get< std::vector<Triangle> >( fv );
    const auto& polygons  = std::get< std::vector<Polygon> >( fv );

    BOOST_CHECK_EQUAL( squares.size(),   3 );
    BOOST_CHECK_EQUAL( triangles.size(), 0 );
    BOOST_CHECK_EQUAL( circles.size(),   1 );
    BOOST_CHECK_EQUAL( polygons.size(),  0 );

    BOOST_CHECK_EQUAL( circles.at(0),   Circle( { 5.2, 6.3},  1.7 ) );

    BOOST_CHECK_EQUAL( squares.at(0),   Square( {1,1}, {1,1}) );
    BOOST_CHECK_EQUAL( squares.at(1),   Square( {3,3}, {3,3}) );
    BOOST_CHECK_EQUAL( squares.at(2),   Square( {4,4}, {4,4}) );

}

