#define BOOST_TEST_MODULE features test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Canvas.h"
#include <unordered_set>


class TestableCanvas: public Canvas
{
protected:
    template<typename T>
    struct dummy_hash {
        size_t operator()( const T& x) const
        { return 1; }
    };

public:
    std::unordered_set< std::pair<Vector2, Vector2>, dummy_hash<std::pair<Vector2, Vector2>> > _lines;
    std::unordered_set< std::tuple<Vector2, double > , dummy_hash<std::tuple<Vector2, double >> > _circles;

protected:
    void
    drawLine( Vector2 v0, Vector2 v1 ) override
    {
        _lines.insert( std::make_pair(v0, v1) );
        Canvas::drawLine(v0, v1);
    }

    void
    drawCircle( Vector2 center, double radius ) override
    {
        _circles.insert( std::make_tuple(center, radius) );
        Canvas::drawCircle(center, radius);
    }
};



BOOST_AUTO_TEST_CASE(Canvas_draw_triangle)
{
    Triangle triangle( { {0,0}, {1,1}, {2,2} } );

    TestableCanvas canvas;
    canvas.draw( triangle );

    BOOST_CHECK_EQUAL( canvas._lines.size(), 3 );
    BOOST_CHECK_EQUAL( canvas._lines.count( std::make_pair( Vector2(0,0),Vector2(1,1) ) ), 1 );
    BOOST_CHECK_EQUAL( canvas._lines.count( std::make_pair( Vector2(1,1),Vector2(2,2) ) ), 1 );
    BOOST_CHECK_EQUAL( canvas._lines.count( std::make_pair( Vector2(2,2),Vector2(0,0) ) ), 1 );
}

