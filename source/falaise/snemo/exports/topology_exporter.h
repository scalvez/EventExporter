// -*- mode: c++ ; -*-
/* topology_exporter.h
 *
 * Author (s) :
 Francois Mauger <mauger@lpccaen.in2p3.fr>
 Xavier Garrido  <garrido@lal.in2p3.fr>
 Steven Calvez   <calvez@lal.in2p3.fr>
 * Creation date: 2016-02-03
 * Last modified: 2016-02-03
 *
 * License:
 *
 * Description:
 *
 *   Topology exporter
 *
 * History:
 *
 */

#ifndef EXPORTS_TOPOLOGY_EXPORTER_H
#define EXPORTS_TOPOLOGY_EXPORTER_H 1

#include <map>
#include <string>

#include <boost/cstdint.hpp>

#include <falaise/snemo/exports/loggable_support.h>

#include <datatools/bit_mask.h>
#include <falaise/snemo/datamodels/data_model.h>
#include <falaise/snemo/exports/base_data_bank_exporter.h>

#include <falaise/snemo/datamodels/particle_track.h>

namespace export_tools {
  const  std::map<std::string,double> location_to_index = {
    {snemo::datamodel::particle_track::vertex_on_source_foil_label(),0},
    {snemo::datamodel::particle_track::vertex_on_wire_label(),1},
    {snemo::datamodel::particle_track::vertex_on_main_calorimeter_label(),2},
    {snemo::datamodel::particle_track::vertex_on_x_calorimeter_label(),3},
    {snemo::datamodel::particle_track::vertex_on_gamma_veto_label(),4},
    {snemo::datamodel::particle_track::vertex_none_label(),5}
  };
}

namespace geomtools {
  class manager;
}
namespace datatools {
  class properties;
}

namespace snemo {

    namespace exports {

      class export_topology;

      struct topology_exporter : base_data_bank_exporter
      {
      public:
        enum export_bit_type
          {
            NO_EXPORT = 0,
            // Needs 'Topology 2e' :
            EXPORT_EVENT_HEADER           = datatools::bit_mask::bit00,
            EXPORT_TOPOLOGY_1E            = datatools::bit_mask::bit01,
            EXPORT_TOPOLOGY_1E1A          = datatools::bit_mask::bit02,
            EXPORT_TOPOLOGY_2E            = datatools::bit_mask::bit03,
            EXPORT_TOPOLOGY_1E1P          = datatools::bit_mask::bit04,
            EXPORT_TOPOLOGY_2P            = datatools::bit_mask::bit05,
            EXPORT_TOPOLOGY_1E1G          = datatools::bit_mask::bit06,
            EXPORT_TOPOLOGY_1E2G          = datatools::bit_mask::bit07,
            EXPORT_TOPOLOGY_1E3G          = datatools::bit_mask::bit08,
            EXPORT_TOPOLOGY_2E1G          = datatools::bit_mask::bit09,
            EXPORT_TOPOLOGY_2E2G          = datatools::bit_mask::bit10,
            EXPORT_TOPOLOGY_2E3G          = datatools::bit_mask::bit11,

            EXPORT_ALL =
            EXPORT_EVENT_HEADER
            | EXPORT_TOPOLOGY_1E
            | EXPORT_TOPOLOGY_1E1A
            | EXPORT_TOPOLOGY_2E
            | EXPORT_TOPOLOGY_1E1P
            | EXPORT_TOPOLOGY_2P
            | EXPORT_TOPOLOGY_1E1G
            | EXPORT_TOPOLOGY_1E2G
            | EXPORT_TOPOLOGY_1E3G
            | EXPORT_TOPOLOGY_2E1G
            | EXPORT_TOPOLOGY_2E2G
            | EXPORT_TOPOLOGY_2E3G,

            EXPORT_LAST = EXPORT_TOPOLOGY_2E,
          };

        static std::string get_export_bit_label (unsigned int bit_);

      public:

        topology_exporter ();

        ~topology_exporter ();

        void initialize (const datatools::properties & config_);

        int run (const snemo::datamodel::event_record &,
                 snemo::exports::export_topology &);

        void dump (std::ostream & = std::clog) const;

      protected:

        // void _set_default_bank_labels ();

        void _init_defaults ();

        int _export_event_header (const datatools::things &,
                                  snemo::exports::export_topology &);

        int _export_topology_1e (const datatools::things &,
                                 snemo::exports::export_topology &);

        int _export_topology_1e1a (const datatools::things &,
                                   snemo::exports::export_topology &);

        int _export_topology_2e (const datatools::things &,
                                 snemo::exports::export_topology &);

        int _export_topology_1e1p (const datatools::things &,
                                   snemo::exports::export_topology &);

        int _export_topology_2p (const datatools::things &,
                                 snemo::exports::export_topology &);

        int _export_topology_1e1g (const datatools::things &,
                                   snemo::exports::export_topology &);

        int _export_topology_1e2g (const datatools::things &,
                                   snemo::exports::export_topology &);

        int _export_topology_1e3g (const datatools::things &,
                                   snemo::exports::export_topology &);

        int _export_topology_2e1g (const datatools::things &,
                                   snemo::exports::export_topology &);

        int _export_topology_2e2g (const datatools::things &,
                                   snemo::exports::export_topology &);

        int _export_topology_2e3g (const datatools::things &,
                                   snemo::exports::export_topology &);

      };

    } // end of namespace exports

} // end of namespace snemo

#endif // EXPORTS_TOPOLOGY_EXPORTER_H

// end of topology_exporter.h
