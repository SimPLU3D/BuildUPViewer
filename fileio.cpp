#include "fileio.hpp"
#include <fstream>
#include <boost/lexical_cast.hpp>

void load_lots_shp(const char* file, std::map<int,Lot>& lots)
{
    lots.clear();
    OGRRegisterAll();
    OGRDataSource *poDS = OGRSFDriverRegistrar::Open(file,FALSE);
    OGRLayer *poLayer = poDS->GetLayer(0);
    poLayer->ResetReading();
    OGRFeature *poFeature;

    int index = -1;
    while( (poFeature = poLayer->GetNextFeature()) )
    {
        OGRPolygon* ply = (OGRPolygon*)(poFeature->GetGeometryRef());
        ply->closeRings();
        ++index;
        lots.insert(std::make_pair(index,Lot(index,ply)));
        OGRFeature::DestroyFeature( poFeature );
    }
    OGRDataSource::DestroyDataSource( poDS );
}

void load_bldgsFinal_shp(std::string& dir, int n,std::map<int,std::vector<Building> >& exp_bldgs)
{
    exp_bldgs.clear();
    OGRRegisterAll();

    std::string file;
    for(int i=0; i<n; ++i)
    {
        file = dir + "/bldgs_final_exp"+ boost::lexical_cast<std::string>(i) + ".shp";

        OGRDataSource *poDS = OGRSFDriverRegistrar::Open(file.c_str(),FALSE);
        OGRLayer *poLayer = poDS->GetLayer(0);
        poLayer->ResetReading();
        OGRFeature *poFeature;


        while( (poFeature = poLayer->GetNextFeature()) )
        {
            OGRPolygon* ply = (OGRPolygon*)(poFeature->GetGeometryRef());
            double h = poFeature->GetFieldAsDouble("height");
            int lotID = poFeature->GetFieldAsInteger("lotID");
            exp_bldgs[i].push_back(Building(ply,h,lotID));

            OGRFeature::DestroyFeature( poFeature );
        }
        OGRDataSource::DestroyDataSource( poDS );
    }
}

void load_bldgsEvolution_txt(const char* txt,std::map< int,std::vector<Building> >& iter_bldgs)
{
    std::ifstream in(txt);
    if(in.is_open())
    {
        int iter;
        double x,y,h;
        in>>iter;
        while(!in.eof())
        {

            OGRLinearRing ring;
            for(int i=0; i<5; ++i)
            {
                in>>x;
                in>>y;
                ring.addPoint(x,y);
            }
            in>>h;
            OGRPolygon footprint;
            footprint.addRing(&ring);
            iter_bldgs[iter].push_back(Building(&footprint,h));

            in>>iter;
        }
    }
}
