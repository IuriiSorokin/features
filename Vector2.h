/*
 * Vector2.h
 *
 *  Created on: 17 Jul 2017
 *      Author: sorokin
 */

#ifndef VECTOR2_H_
#define VECTOR2_H_

class Vector2
{
public:
    Vector2( double x, double y )
    : _x( x ), _y( y )
    {}

    double
    x() const
    { return _x; }

    double
    y() const
    { return _y; }

private:
    double _x;
    double _y;
};



inline Vector2
operator+( Vector2 lhs, Vector2 rhs ) {
    const auto x = lhs.x()  + rhs.x();
    const auto y = lhs.y()  + rhs.y();
    return Vector2( x, y );
}



inline Vector2
operator-( Vector2 lhs, Vector2 rhs ) {
    const auto x = lhs.x()  - rhs.x();
    const auto y = lhs.y()  - rhs.y();
    return Vector2( x, y );
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

#endif /* VECTOR2_H_ */
