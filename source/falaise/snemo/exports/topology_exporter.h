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

#include <datatools/bit_mask.h>
#include <falaise/snemo/datamodels/data_model.h>
#include <falaise/snemo/exports/base_data_bank_exporter.h>

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
            EXPORT_TOPOLOGY_2E           = datatools::bit_mask::bit00,

            EXPORT_ALL =
            EXPORT_TOPOLOGY_2E,
            // | EXPORT_TOPOLOGY_1E1G

            EXPORT_LAST = EXPORT_TOPOLOGY_2E,
          };

        static std::string get_export_bit_label (unsigned int bit_);

      public:

        topology_exporter ();

        ~topology_exporter ();

        void initialize (const datatools::properties & config_);

        int run (const snemo::datamodel::event_record &,
                 snemo::exports::export_topology &);

        uint32_t get_export_flags () const;

        void dump (std::ostream & = std::clog) const;

      protected:

        // void _set_default_bank_labels ();

        void _init_defaults ();

        int _export_topology_2e (const datatools::things &,
                                 snemo::exports::export_topology &);

      };

    } // end of namespace exports

} // end of namespace snemo

#endif // EXPORTS_TOPOLOGY_EXPORTER_H

// end of topology_exporter.h
