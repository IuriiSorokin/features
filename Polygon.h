
#ifndef POLYGON_H_
#define POLYGON_H_

class Polygon
{
public:
    Polygon( std::vector<Vector2> vertices )
    : _vertices( vertices )
    {}

    size_t
    n_vertices() const
    { return _vertices.size(); }

    Vector2
    vertex( size_t i ) const
    { return _vertices.at(i); } // Don't perform additional range check.

private:
    std::vector< Vector2 > _vertices;
};




#endif /* POLYGON_H_ */
