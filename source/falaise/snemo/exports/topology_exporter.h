// -*- mode: c++ ; -*-
/* topology_exporter.h
 *
 * Author (s) :
 Francois Mauger <mauger@lpccaen.in2p3.fr>
 Xavier Garrido  <garrido@lal.in2p3.fr>
 Steven Calvez   <steven@lal.in2p3.fr>
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

namespace geomtools {
  class manager;
}
namespace datatools {
  class properties;
}

namespace snemo {

    namespace exports {

      class export_topology;

      struct topology_exporter
      {
      public:
        enum export_bit_type
          {
            NO_EXPORT = 0,
            // Needs 'Topology 2e' :
            EXPORT_TOPOLOGY_2E           = datatools::bit_mask::bit00,

            EXPORT_ALL =
            EXPORT_TOPOLOGY_2E
            // | EXPORT_TOPOLOGY_1E1G

            EXPORT_LAST = EXPORT_TOPOLOGY_2E,
          };

        enum export_topic_level
          {
            EXPORT_TOPIC_EXCLUDE    = -1,
            EXPORT_TOPIC_NO_INCLUDE = 0,
            EXPORT_TOPIC_INCLUDE    = 1,
          };

        static std::string get_export_bit_label (unsigned int bit_);

      public:

        bool is_initialized () const;

        bool has_geom_manager () const;

        void set_geom_manager (const geomtools::manager & gmgr_);

        const geomtools::manager & get_geom_manager () const;

        void unset_exported (unsigned int store_bit_);

        void set_exported (unsigned int store_bit_);

        bool is_exported (unsigned int store_bit_) const;

        int get_topic_export_level(const std::string & topic_label_) const;

        topology_exporter ();

        ~topology_exporter ();

        void initialize (const datatools::properties & config_);

        void reset ();

        int run (const snemo::datamodel::event_record &,
                 snemo::reconstruction::exports::export_topology &);

        uint32_t get_export_flags () const;

        void dump (std::ostream & = std::clog) const;

      protected:

        void _set_default_bank_labels ();

        void _init_defaults ();

        int _export_topology_2e (const datatools::things &,
                                 snemo::reconstruction::exports::export_topology &);

        const std::map<std::string, std::string> & get_bank_labels () const;

      private:

        bool _initialized_; //!< Initialization flag
        const geomtools::manager * _geom_manager_; //!< The geometry manager

        std::map<std::string, std::string> _bank_labels_; //!< The labels of the bank in the event records
        uint32_t _export_flags_;

      };

    } // end of namespace exports

} // end of namespace snemo

#endif // EXPORTS_TOPOLOGY_EXPORTER_H

// end of topology_exporter.h
