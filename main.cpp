#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

#include "Building.hpp"
#include "Lot.hpp"
#include "fileio.hpp"
#include "osg.hpp"


int main(int argc , char** argv)
{
    int quit = 0;
    while(!quit)
    {
        std::cout<<"\nPlease choose your option:\n";
        std::cout<<"1: Visualize final results of all experiments\n";
        std::cout<<"2: Visualize evolution of one experiment \n";
        std::cout<<"3: Quit\n";

        int option;
        std::cin>>option;
        switch (option){
        case 1:
        {
	    std::string dir;
            std::cout<<"\nEnter or drag the result folder here:\n";
	    std::cin>>dir;
	    if(dir.back()=='\'')
	      dir.pop_back();
	    if(dir.front()=='\'')
	      dir.erase(0,1);
	  
	    std::cout<<"dir:"<<dir<<"\n";

            //get number of shapefile in the directory
            std::string ext = ".shp";
            int n=0;
            namespace fs = boost::filesystem;
            for(fs::directory_iterator it(dir);it!=fs::directory_iterator();++it)
                if(fs::is_regular_file(it->status()) && it->path().extension()==ext)
                    ++n;

            std::map<int,std::vector<Building> > exp_bldgs;
            load_bldgsFinal_shp(dir,n-1,exp_bldgs);

            //load parcel file which should be in the same directory
            std::string fileLots(dir+"/parcelle.shp");
            std::map<int,Lot> lots;
            load_lots_shp(fileLots.c_str(),lots);

            display(exp_bldgs,lots);
            break;
        }
        case 2:
        {
            std::string file;
            std::cout<<"\nEnter or drag the evolution file here:\n";
            std::cin>>file;

	    if(file.back()=='\'')
	      file.pop_back();
	    if(file.front()=='\'')
	      file.erase(0,1);

	    std::cout<<"file:"<<file<<"\n";

            std::map<int, std::vector<Building> > iter_bldgs;
            load_bldgsEvolution_txt( file.c_str(),iter_bldgs);

            //load parcel file which should be in the same directory
            boost::filesystem::path p(file);
            std::string fileLots(p.parent_path().string() + "/parcelle.shp");
            std::map<int,Lot> lots;
            load_lots_shp(fileLots.c_str(),lots);

            display(iter_bldgs,lots);

            break;
        }
        case 3:
        {
            quit = 1;
            break;
        }

        default:
            std::cerr<<"invalid option; choose again\n";
        }

    }

    return 0;
}

