/*
 * Vector2.h
 *
 *  Created on: 17 Jul 2017
 *      Author: sorokin
 */

#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <iostream>
#include "dbg.h"

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

    void
    set_x( double x )
    { _x = x; }

    void
    set_y( double y )
    { _y = y; }

    Vector2&
    operator+=( const Vector2& rhs ) {
        _x += rhs.x();
        _y += rhs.y();
        return *this;
    }

    Vector2&
    operator-=( const Vector2& rhs ) {
        _x -= rhs.x();
        _y -= rhs.y();
        return *this;
    }

    friend std::istream&
    operator>>( std::istream& is, Vector2& v);

//    template< typename IStreamT >
//    static Vector2
//    deserialize( IStreamT & is )
//    {
//        double x, y;
//        is >> x >> y;
//        return Vector2( x, y );
//    }

    static Vector2
    deserialize( std::istream& is )
    {
        double x, y;
        is >> x >> y;
        return Vector2( x, y );
    }

private:
    double _x = 0;
    double _y = 0;
};



inline Vector2
operator+( Vector2 lhs, Vector2 rhs ) {
    lhs += rhs;
    return lhs;
}



inline Vector2
operator-( Vector2 lhs, Vector2 rhs ) {
    lhs -= rhs;
    return lhs;
}



inline bool
operator==( const Vector2& lhs, const Vector2& rhs ) {
    return lhs.x() == rhs.x()
            and lhs.y() == rhs.y();
}



inline bool
operator!=( const Vector2& lhs, const Vector2& rhs ) {
    return not (lhs == rhs );
}



inline std::ostream&
operator<<( std::ostream& os, const Vector2& v )
{
    return os << v.x() << " " << v.y();
}



inline std::istream&
operator>>( std::istream& is, Vector2& v)
{
    is >> v._x >> v._y;
    return is;
}

#endif /* VECTOR2_H_ */
