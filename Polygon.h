
#ifndef POLYGON_H_
#define POLYGON_H_

#include "Vector2.h"
#include <iostream>

class Polygon
{
public:
    Polygon( std::vector<Vector2> vertices )
    {
        if( vertices.size() < 3 ) {
            throw std::invalid_argument("Polygon must have at least 3 vertices");
        }
        _vertices = std::move( vertices );
    }

    size_t
    n_vertices() const
    { return _vertices.size(); }

    Vector2
    vertex( size_t i ) const
    { return _vertices.at(i); }

private:
    std::vector< Vector2 > _vertices;
};




inline bool
operator==( const Polygon& lhs, const Polygon& rhs )
{
    if( lhs.n_vertices() != rhs.n_vertices() ) {
        return false;
    }

    for( size_t i_vtx = 0; i_vtx < lhs.n_vertices(); ++i_vtx ) {
        if( lhs.vertex( i_vtx ) != rhs.vertex( i_vtx ) ) {
            return false;
        }
    }

    return true;
}



inline bool
operator!=( const Polygon& lhs, const Polygon& rhs )
{
    return not (lhs == rhs);
}



//inline std::ostream&
//operator<<( std::ostream& os, const Polygon& polygon )
//{
//    os << polygon.name();
//    for( size_t i_vtx = 0; i_vtx < polygon.n_vertices(); ++i_vtx ) {
//        os << " " << polygon.vertex( i_vtx );
//    }
//    return os;
//}
//
//
//
//inline  std::istream&
//operator>>( std::istream& is, Polygon& polygon)
//{
//    auto skip_spaces = []( std::istream& is ) {
//        while( not is.eof() and std::isspace( is.peek() ) ) {
//            is.get();
//        }
//        return true;
//    };
//
//    std::string line_string;
//    std::getline( is, line_string );
//    std::istringstream line( line_string );
//
//    polygon.clear();
//
//    std::string read_name;
//    line >> read_name;
//    while( skip_spaces(line) and not line.eof() ) {
//        Vector2 v;
//        line >> v;
//        polygon.set_vertex( polygon.n_vertices(), v );
//    }
//
//    if( read_name != Polygon::name() ) {
//        is.setstate(std::ios::failbit);
//    }
//
//    if( line.fail() ) {
//        is.setstate(std::ios::failbit);
//    }
//
//    return is;
//}

#endif /* POLYGON_H_ */
