#ifndef FILEIO_HPP
#define FILEIO_HPP

#include "Lot.hpp"
#include "Building.hpp"
#include <map>
#include <vector>

void load_lots_shp(const char* file, std::map<int,Lot>& lots);
void load_bldgsFinal_shp(std::string& dir, int n,std::map<int,std::vector<Building> >& exp_bldgs);
void load_bldgsEvolution_txt(const char* txt,std::map< int,std::vector<Building> >& iter_bldgs);

#endif
