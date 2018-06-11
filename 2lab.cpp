#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <libxml++/libxml++.h>

#include <stdlib.h>
#include <fstream>
#include <vector>
#include <map>
#include <unistd.h>

class District
{
public:
    Glib::ustring district_city;
    std::map<Glib::ustring, int> subway;
    std::vector<Glib::ustring> subway_name;
};

int main(int argc, char *argv[]) {
    std::ofstream fout("output.txt");
    std::locale::global(std::locale(""));

    xmlpp::TextReader reader("data.xml"); 

    int number = 0;
    int spaces = 0;
    Glib::ustring dist;
    std::vector<District> dc;


    try {
        while (reader.read()) {
            int i = 0;
            District obj;
            Glib::ustring sw;

            bool founded_dc, founded_sw = false;
            int depth = reader.get_depth();
            if (depth == 2)
            {
                if (reader.get_name() == "number")
                {
                    reader.read();
                    number++;
                    reader.read();
                } else if (reader.get_name() == "parking_space") {
                    reader.read();
                    int amount = atoi(reader.get_value().c_str()); // string to int
                    spaces = amount;

                    reader.read();
                } else if (reader.get_name() == "district_city") {
                    reader.read();
                    dist = reader.get_value();
                    reader.read();
                } else if (reader.get_name() == "nearest_subway_station") {
                    reader.read();
                    sw = reader.get_value();
                    for (i = 0; i < dc.size(); i++) {
                        if (dist == dc[i].district_city) {
                            founded_dc = true;
                            break;
                        }
                    }
                    if (founded_dc) {
                        dc[i].subway[sw] += spaces;
                        for (int j = 0; j < dc[i].subway_name.size(); j++) {
                            if (sw == dc[i].subway_name[j]) {
                                founded_sw = true;
                                break;
                            }
                        }
                        if (!founded_sw) {
                            dc[i].subway_name.push_back(sw);
                        }

                    } else {
                        obj.district_city = dist;
                        obj.subway[sw] = spaces;
                        obj.subway_name.push_back(sw);
                        dc.push_back(obj);
                    }
                    founded_dc = false;
                    founded_sw = false;
                    reader.read();
                }
            }
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // arguments + output;
    int par=0;

    par = getopt(argc, argv, ":d:"); // -d DistrictName;

    if (par == 'd' )
    {
        for (int j = 0; j < dc.size(); j++) {
            if (dc[j].district_city == optarg) {
                fout << "Район \"" << dc[j].district_city << "\"" << std::endl;

                for (int k = 0; k < dc[j].subway_name.size(); k++) {
                    fout << "Станция метро \"" << dc[j].subway_name[k] << "\": " << dc[j].subway[dc[j].subway_name[k]]
                         << std::endl;
                }
            }
        }
    } else {

            for (int j = 0; j < dc.size(); j++) {
            fout << "Район \"" << dc[j].district_city << "\"" << std::endl;
            for (int k = 0; k < dc[j].subway_name.size(); k++) {
                fout << "Станция метро \"" << dc[j].subway_name[k] << "\": " << dc[j].subway[dc[j].subway_name[k]]
                     << std::endl;
            }
            fout << std::endl;
        }
    }
    fout.close();
    return 0;




    return EXIT_SUCCESS;
}
