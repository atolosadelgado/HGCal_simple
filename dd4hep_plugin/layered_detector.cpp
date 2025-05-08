#include "DD4hep/DetFactoryHelper.h"
#include "DD4hep/Detector.h"
#include "DD4hep/Volumes.h"
#include "DD4hep/Printout.h"
#include "DD4hep/DetElement.h"

#include <unordered_set>

static const std::unordered_set<std::string> absorber_materials = {
    "Lead" , "WCu", "Iron", "StainlessSteel", "Copper", "Steel235"
};

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

#include <vector>
#include <string>
#include <algorithm>  // for std::find
#include <stdexcept>  // for std::out_of_range

int getMaterialIndex(const std::vector<std::string>& materials, const std::string& name) {
    auto it = std::find(materials.begin(), materials.end(), name);
    if (it != materials.end()) {
        return static_cast<int>(std::distance(materials.begin(), it));
    } else {
        throw std::out_of_range("Material not found: " + name);
    }
}



static dd4hep::Ref_t create_layered_detector(dd4hep::Detector& description, xml_h e, dd4hep::SensitiveDetector sens ) {
    xml_det_t  x_det = e;
    std::string det_name = x_det.nameStr();
    // Setup which kind of sensitive detector is
    sens.setType("tracker");


    // Detector envelope volume
    dd4hep::DetElement det(det_name, x_det.id());
    dd4hep::Assembly assembly(det_name + "_assembly");

    // Read x, y dimensions
    xml_dim_t dim = x_det.child("dimensions");
    double dx = dim.attr<double>("x");
    double dy = dim.attr<double>("y");
    // Start stacking slices along z
    double z_offset = 0.0;
    int slice_num = 0;

    for (xml_coll_t slice(x_det, _U(slice)); slice; ++slice, ++slice_num) {
        double thickness = slice.attr<double>("thickness") * dd4hep::mm;
        std::string material = slice.attr<std::string>("material");
        std::string name = slice.hasAttr("name") ? slice.attr<std::string>("name") : ("slice" + std::to_string(slice_num));

        // Create box for slice
        dd4hep::Box box(dx / 2.0, dy / 2.0, thickness / 2.0);
        dd4hep::Material slice_material =  description.material(material);
        dd4hep::Volume slice_vol(name, box, slice_material);



        if( material == "Silicon" )
        {
            slice_vol.setVisAttributes( description.visAttributes("sensor_vis") );
            std::cout << name.c_str() << std::endl;

        }
        else if( 0 < absorber_materials.count(material) )
        {
            slice_vol.setVisAttributes( description.visAttributes("absorber_vis") );
            std::cout << name.c_str() << std::endl;

        }
        else {
            slice_vol.setVisAttributes( description.visAttributes("no_vis") );

        }
        slice_vol.setSensitiveDetector(sens);

        // Place slice
        double zpos = z_offset + thickness / 2.0;
        dd4hep::Position pos = dd4hep::Position(0, 0, zpos);
        dd4hep::PlacedVolume pv = assembly.placeVolume(slice_vol, pos);
        pv.addPhysVolID("layer", slice_num);
        auto material_index = getMaterialIndex( material_names, material );

        pv.addPhysVolID("material", material_index );

        z_offset += thickness;
    }

    // Create envelope box to wrap the stacked slices
    dd4hep::Box envelope_box(dx / 2.0, dy / 2.0, z_offset / 2.0);
    dd4hep::Volume envelope(det_name + "_envelope", envelope_box, description.material("Air"));
    envelope.setVisAttributes(description.visAttributes("envelope_vis"));
    envelope.setRegion  ( description, x_det.regionStr() );
    envelope.setLimitSet( description, x_det.limitsStr() );
//   envelope.setSensitiveDetector(sens);
    dd4hep::PlacedVolume assembly_pv = envelope.placeVolume(assembly, dd4hep::Position(0, 0, -z_offset / 2.0));
//

    // Place our mother volume in the world
    dd4hep::Volume wVol = description.pickMotherVolume(det);
    auto envelope_pv = wVol.placeVolume( envelope, dd4hep::Position(0, 0, z_offset / 2.0) );
    envelope_pv.addPhysVolID("system", 1);
    det.setPlacement(envelope_pv);
    // Register the detector
//     description.add(det_name, det);
    return det;
}

DECLARE_DETELEMENT(MyLayeredDetector, create_layered_detector)

