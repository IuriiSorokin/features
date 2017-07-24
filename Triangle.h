
#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Vector2.h"
#include <iostream>

class Triangle
{
public:
    Triangle() = default;

    Triangle( Vector2 v0, Vector2 v1, Vector2 v2 )
    : _vertices( { v0, v1, v2 } )
    {}

    static constexpr size_t
    n_vertices()
    { return _n_vertices; }

    Vector2
    vertex( size_t i ) const
    { return _vertices.at(i); } // array::at() check that i <= 3. Don't perform additional check.

private:
    static constexpr size_t _n_vertices = 3;
    std::array< Vector2, _n_vertices> _vertices; // One may consider changing to std::vector to make the _vertices movable
                                                 // at the cost of dynamic memory allocation during construction
};


inline bool
operator==( const Triangle& lhs, const Triangle& rhs )
{
    return lhs.vertex(0) == rhs.vertex( 0 )
            and lhs.vertex( 1 ) == rhs.vertex( 1 )
            and lhs.vertex( 2 ) == rhs.vertex( 2 );
}



inline bool
operator!=( const Triangle& lhs, const Triangle& rhs )
{
    return not (lhs == rhs);
}

#endif /* TRIANGLE_H_ */
