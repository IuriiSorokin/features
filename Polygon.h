
#ifndef POLYGON_H_
#define POLYGON_H_

#include "Vector2.h"
#include <iostream>

class Polygon
{
public:
    Polygon() = default;

    Polygon( std::vector<Vector2> vertices )
    : _vertices( vertices )
    {}

    size_t
    n_vertices() const
    { return _vertices.size(); }

    Vector2
    vertex( size_t i ) const
    { return _vertices.at(i); }

    void
    set_vertex( size_t i, Vector2 v ) {
        if( i >= _vertices.size() ) {
            _vertices.resize( i );
        }
        _vertices.at( i ) = v;
    }

    void
    reset()
    { _vertices.clear(); }

    static std::string
    name()
    { return "Polygon"; }

    friend std::istream&
    operator>>( std::istream& is, Polygon& polygon);

private:
    std::vector< Vector2 > _vertices;
};



inline std::ostream&
operator<<( std::ostream& os, const Polygon& polygon )
{
    os << polygon.name();
    for( size_t i_vtx = 0; i_vtx < polygon.n_vertices(); ++i_vtx ) {
        os << " " << polygon.vertex( i_vtx );
    }
    return os;
}



inline  std::istream&
operator>>( std::istream& is, Polygon& polygon)
{
    std::string line_string;
    std::getline( is, line_string );
    std::istringstream line( line_string );

    polygon.reset();

    std::string read_name;
    line >> read_name;
    while( not line.eof() ) {
        Vector2 v;
        line >> v;
        polygon.set_vertex( polygon.n_vertices(), v );
    }
    if( read_name != Polygon::name() ) {
        is.setstate(std::ios::failbit);
    }

    if( line.fail() ) {
        is.setstate(std::ios::failbit);
    }

    if( line.bad() ) {
        is.setstate(std::ios::badbit);
    }

    return is;
}

#endif /* POLYGON_H_ */
