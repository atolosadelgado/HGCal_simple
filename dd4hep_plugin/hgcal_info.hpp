#ifndef HGCAL_INFO
#define HGCAL_INFO

#include <vector>
#include <string>
#include <algorithm>  // for std::find
#include <stdexcept>  // for std::out_of_range


struct hgcal_info
{
    public:
    struct hgcal_info_layer
    {
    public:
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

    int getMaterialIndex(const std::string& name) {
        auto it = std::find(material_names.begin(), material_names.end(), name);
        if (it != material_names.end()) {
            return static_cast<int>(std::distance(material_names.begin(), it));
        } else {
            throw std::out_of_range("Material not found: " + name);
        }
    }
        // Required constructor for DD4hep extension system
    hgcal_info(const hgcal_info& original, dd4hep::DetElement /*de*/) {
        layer_v = original.layer_v;
        material_names = original.material_names;
    }

    // Default constructor
    hgcal_info() = default;

};

#endif
