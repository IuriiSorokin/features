/*
 * serdes.h
 *
 *  Created on: 24 Jul 2017
 *      Author: sorokin
 */

#ifndef SERDES_H_
#define SERDES_H_

#include "Features.h"
#include <iostream>
#include <string>

namespace serdes {

template<typename FeatureT>
std::string
name();

template<typename Type >
void
serialize(const Type& obj, std::ostream& os )
{
    os << obj << " ";
}



template< typename FeatureT,
          std::enable_if_t< is_feature<FeatureT>::value, bool > = true >
void
serialize_with_name(const FeatureT& obj, std::ostream& os )
{
    os << name<FeatureT>() << " ";
    serialize( obj, os );
}



template<typename Type >
Type
deserialize(std::istream& is)
{
    Type obj;
    is >> obj;
    return obj;
}



template<> std::string name<Circle>()   { return "Circle";   }
template<> std::string name<Triangle>() { return "Triangle"; }
template<> std::string name<Square>()   { return "Square";   }
template<> std::string name<Polygon>()  { return "Polygon";  }



template<>
void
serialize<Vector2>( const Vector2& vector, std::ostream& os )
{
    serialize( vector.x(), os );
    serialize( vector.y(), os );
}



template<>
Vector2
deserialize<Vector2>( std::istream& is )
{
    const auto x = deserialize<double>( is );
    const auto y = deserialize<double>( is );
    return Vector2( x, y );
}



template<>
void
serialize( const Circle& circle, std::ostream& os )
{
    serialize( circle.center(), os );
    serialize( circle.radius(), os );
}



template<>
Circle
deserialize<Circle>( std::istream& is )
{
    const auto center = deserialize<Vector2>( is );
    const auto radius = deserialize<double>( is );
    return Circle( center, radius );
}



template<>
void
serialize( const Square& square, std::ostream& os )
{
    serialize( square.vertex(0), os );
    serialize( square.vertex(1), os );
}



template<>
Square
deserialize<Square>( std::istream& is )
{
    const auto vertex0 = deserialize<Vector2>( is );
    const auto vertex1 = deserialize<Vector2>( is );
    return Square( vertex0, vertex1 );
}



template<>
void
serialize( const Triangle& triangle, std::ostream& os )
{
    serialize( triangle.vertex(0), os );
    serialize( triangle.vertex(1), os );
    serialize( triangle.vertex(2), os );
}



template<>
Triangle
deserialize<Triangle>( std::istream& is )
{
    const auto vertex0 = deserialize<Vector2>( is );
    const auto vertex1 = deserialize<Vector2>( is );
    const auto vertex2 = deserialize<Vector2>( is );
    return Triangle( vertex0, vertex1, vertex2 );
}



template<>
void
serialize( const Polygon& polygon, std::ostream& os )
{
    serialize( polygon.n_vertices(), os );
    for( size_t iVtx = 0; iVtx < polygon.n_vertices(); ++iVtx ) {
        serialize( polygon.vertex( iVtx ), os );
    }
}



template<>
Polygon
deserialize<Polygon>( std::istream& is )
{
    const auto n_vertices = deserialize<size_t>(is);
    std::vector<Vector2> vertices;
    vertices.reserve( n_vertices );
    for( size_t iVtx = 0; iVtx < n_vertices; ++iVtx ) {
        vertices.push_back( deserialize<Vector2>( is ) );
    }
    return Polygon( vertices );
}


}





#endif /* SERDES_H_ */
