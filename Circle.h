/*
 * Circle.h
 *
 *  Created on: 17 Jul 2017
 *      Author: sorokin
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

class Circle
{
public:
    Circle( Vector2 center, double r )
    : _center( center ), _radius( r )
    {}

    // One can also add constructors from two points: the center and a point lying on the circle,
    // and from three points lying on the circle.

    Vector2
    center() const
    { return _center; }

    double
    radius() const
    { return _radius; }

    static std::string
    name()
    { return "Square"; }

    std::ostream&
    serialize( std::ostream& os ) const
    {
        os << name() << " ";
        _center.serialize( os );
        os << " ";
        os << _radius;
        os << "\n";
        return os;
    }

    static boost::optional<Circle>
    deserialize( std::istream& is )
    {
        std::string read_name;
        is >> read_name;
        if( read_name != name() ) {
            return {};
        }

        const auto center = Vector2::deserialize( is );
        double radius;
        is >> radius;

        if( not center.is_initialized() or is.fail() or is.bad() ) {
            return {};
        }

        std::string remaining;
        is >> remaining;
        for( auto c : remaining ) {
            if( not std::isspace(c) ) {
                return {};
            }
        }

        return { Circle( center.get(), radius ) };
    }

private:
    Vector2 _center;
    double  _radius;
};




#endif /* CIRCLE_H_ */
