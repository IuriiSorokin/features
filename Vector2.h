/*
 * Vector2.h
 *
 *  Created on: 17 Jul 2017
 *      Author: sorokin
 */

#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <iostream>
#include <boost/optional.hpp>

class Vector2
{
public:
    Vector2() = default;

    Vector2( double x, double y )
    : _x( x ), _y( y )
    {}

    double
    x() const
    { return _x; }

    double
    y() const
    { return _y; }

    std::ostream&
    serialize( std::ostream& os ) const
    { return os << _x << " " << _y; }

    static boost::optional<Vector2>
    deserialize( std::istream& is )
    {
        double x;
        double y;
        is >> x >> y;
        if( is.bad() or is.fail() ) {
            return {};
        }
        return { Vector2{x,y} };
    }

private:
    double _x = 0;
    double _y = 0;
};



inline
Vector2
operator+( const Vector2& lhs, const Vector2& rhs ) {
    return Vector2( lhs.x() + rhs.x(), lhs.y() + rhs.y() );
}



inline
Vector2
operator-( const Vector2& lhs, const Vector2& rhs ) {
    return Vector2( lhs.x() - rhs.x(), lhs.y() - rhs.y() );
}



inline
bool
operator==( const Vector2& lhs, const Vector2& rhs ) {
    return lhs.x() == rhs.x()
            and lhs.y() == rhs.y();
}



inline std::ostream&
operator<<( std::ostream& os, const Vector2& v )
{
    return v.serialize( os );
}

#endif /* VECTOR2_H_ */
