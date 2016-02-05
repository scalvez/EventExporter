// -*- mode: c++ ; -*-
/* base_data_bank_exporter.h
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

#ifndef EXPORTS_BASE_DATA_BANK_EXPORTER_H
#define EXPORTS_BASE_DATA_BANK_EXPORTER_H 1

#include <map>
#include <string>

#include <boost/cstdint.hpp>

#include <datatools/bit_mask.h>
#include <falaise/snemo/datamodels/data_model.h>
#include <falaise/snemo/exports/export_topology.h>

namespace geomtools {
  class manager;
}
namespace datatools {
  class properties;
}

namespace snemo {

    namespace exports {

      class base_export_data_bank;

      struct base_data_bank_exporter
      {
      public:

        enum export_topic_level
          {
            EXPORT_TOPIC_EXCLUDE    = -1,
            EXPORT_TOPIC_NO_INCLUDE = 0,
            EXPORT_TOPIC_INCLUDE    = 1,
          };

        // static std::string get_export_bit_label (unsigned int bit_);

      public:

        bool is_initialized () const;

        bool has_geom_manager () const;

        void set_geom_manager (const geomtools::manager & gmgr_);

        const geomtools::manager & get_geom_manager () const;

        void unset_exported (unsigned int store_bit_);

        void set_exported (unsigned int store_bit_);

        bool is_exported (unsigned int store_bit_) const;

        int get_topic_export_level(const std::string & topic_label_) const;

        base_data_bank_exporter ();

        ~base_data_bank_exporter ();

        void initialize (const datatools::properties & config_);

        void reset ();

        int run ();

        uint32_t get_export_flags () const;

        void dump (std::ostream & = std::clog) const;

      protected:

        void _set_default_bank_labels ();

        void _init_defaults ();

        int _export_topology_2e (const datatools::things &,
                                 snemo::exports::export_topology &);

        const std::map<std::string, std::string> & get_bank_labels () const;

        uint32_t _export_flags_;

        std::map<std::string, std::string> _bank_labels_; //!< The labels of the bank in the event records
      private:

        bool _initialized_; //!< Initialization flag
        const geomtools::manager * _geom_manager_; //!< The geometry manager


      };

    } // end of namespace exports

} // end of namespace snemo

#endif // EXPORTS_BASE_DATA_BANK_EXPORTER_H

// end of base_data_bank_exporter.h
