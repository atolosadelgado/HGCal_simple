#ifndef HGCAL_INFO
#define HGCAL_INFO

#include <vector>
#include <string>

struct hgcal_info
{

    struct hgcal_info_layer
    {
        double zini={0};
        double zfin={0};
        int matindex={-1};
    };
    std::vector<hgcal_info_layer> layer_v;
    std::vector<std::string> material_names = {
                                                "Air",
                                                "Vacuum",
                                                "Aluminium",
                                                "Ar_50pct_plus_CO_2_50pct",
                                                "CFM",
                                                "Copper",
                                                "G10",
                                                "Iron",
                                                "Kapton",
                                                "Lead",
                                                "PCB",
                                                "Polystyrene",
                                                "Polystyrole",
                                                "Scintillator",
                                                "Silicon",
                                                "StainlessSteel",
                                                "Steel235",
                                                "WCu"
                                                };
};

#endif
