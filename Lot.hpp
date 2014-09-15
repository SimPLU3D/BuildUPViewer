#ifndef LOT_HPP
#define LOT_HPP

#include <gdal/ogrsf_frmts.h>
#include <map>
#include <string>
#include <boost/lexical_cast.hpp>

class Lot
{
public:
    Lot():_polygon(0) {}
    Lot(int id, OGRPolygon* ply): _id(id),_polygon((OGRPolygon*)(ply->clone())){}

    //be careful, not all memebers are copied; currently only called by std::map insert
    Lot(const Lot& o){
        _id = o._id;
        _polygon = (OGRPolygon*)(o._polygon->clone());
    }
    ~Lot(){if(_polygon) _polygon->empty();}

    inline OGRPolygon* polygon() const{return _polygon;}

private:
    int _id;
    OGRPolygon* _polygon;
};


#endif // LOT_HPP
