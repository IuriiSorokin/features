
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

    void
    set_vertex( size_t i, const Vector2& v )
    { _vertices.at( i ) = v; }

    static std::string
    name()
    { return "Triangle"; }

    friend std::istream&
    operator>>( std::istream& is, Triangle& v);

private:
    static constexpr size_t _n_vertices = 3;
    std::array< Vector2, _n_vertices> _vertices; // One may consider changing to std::vector to make the _vertices movable
                                                 // at the cost of dynamic memory allocation during construction
};



inline std::ostream&
operator<<( std::ostream& os, const Triangle& triangle )
{
    return os << triangle.name() << " "
            << triangle.vertex(0) << " "
            << triangle.vertex(1) << " "
            << triangle.vertex(2);
}



inline std::istream&
operator>>( std::istream& is, Triangle& triangle)
{
    std::string read_name;
    is >> read_name
        >> triangle._vertices.at(0)
        >> triangle._vertices.at(1)
        >> triangle._vertices.at(2);
    if( read_name != Triangle::name() ) {
        is.setstate(std::ios::failbit);
    }
    return is;
}


#endif /* TRIANGLE_H_ */
