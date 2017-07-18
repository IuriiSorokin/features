/*
 * Circle.h
 *
 *  Created on: 17 Jul 2017
 *      Author: sorokin
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Vector2.h"
#include <iostream>

class Circle
{
public:
    Circle( Vector2 center, double r )
    : _center( center ), _radius( r )
    {}

    Vector2
    center() const
    { return _center; }

    double
    radius() const
    { return _radius; }

    static std::string
    name()
    { return "Circle"; }

    friend std::istream&
    operator>>( std::istream& is, Circle& circle);

private:
    Vector2 _center;
    double  _radius;
};



inline std::ostream&
operator<<( std::ostream& os, const Circle& circle )
{
    return os << circle.name() << " "
            << circle.center() << " "
            << circle.radius();
}



inline  std::istream&
operator>>( std::istream& is, Circle& circle)
{
    std::string read_name;
    is >> read_name
        >> circle._center
        >> circle._radius;
    if( read_name != Circle::name() ) {
        is.setstate(std::ios::failbit);
    }
    return is;
}



#endif /* CIRCLE_H_ */
