/*
 * Circle.h
 *
 *  Created on: 17 Jul 2017
 *      Author: sorokin
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Vector2.h"
#include <exception>

class Circle
{
public:
    Circle( Vector2 center, double r );

    Vector2
    center() const
    { return _center; }

    double
    radius() const
    { return _radius; }

private:
    Vector2 _center;
    double  _radius;
};



inline
Circle::Circle( Vector2 center, double r )
: _center( center )
{
    if( r < 0 ) {
        throw std::invalid_argument("Circle radius must be >= 0.");
    }
    _radius = r;
}



inline bool
operator==( const Circle& lhs, const Circle& rhs )
{
    return lhs.center() == rhs.center()
            and lhs.radius() == rhs.radius();
}



inline bool
operator!=( const Circle& lhs, const Circle& rhs )
{
    return not (lhs == rhs);
}

#endif /* CIRCLE_H_ */
