// -*- mode: c++ ; -*-
/* export_topology.h
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
 *   Module for exporting the SuperNEMO event model(s)
 *
 * History:
 *
 */

#ifndef EXPORTS_EXPORT_TOPOLOGY_H
#define EXPORTS_EXPORT_TOPOLOGY_H 1

#include <string>
#include <vector>
#include <iostream>

#include <boost/cstdint.hpp>
#include <camp/camptype.hpp>
#include <camp/class.hpp>
#include <camp/class.hpp>

#include <falaise/snemo/exports/base_export_data_bank.h>

namespace snemo {

  namespace exports {

    struct base_topology
    {
    public:
      static const int32_t EXPORT_VERSION = 0;
      virtual void reset () = 0;
      base_topology ();
    };

    struct topology_2e : base_topology
    {
    public:
      topology_2e ();
      virtual void reset ();

    public:

      double electron_minimal_energy;
      double electron_maximal_energy;

      double electrons_internal_probability;
      double electrons_external_probability;

      double electrons_angle;
    };

    struct export_topology : base_export_data_bank
    {
    public:
      export_topology ();
      virtual ~export_topology ();
      virtual void reset ();
      virtual void clear_data ();

      virtual void implement_introspection ();

      virtual void print (std::ostream & out_ = std::clog,
                          const std::string & title_ = "",
                          const std::string & indent_ = "") const;

      const topology_2e & get_2e_topology () const;

      struct introspection_activator
      {
        introspection_activator ();
      };

    public:

      // Topology 2e data :
      topology_2e                     _topology_2e_;

    };

  } // end of namespace exports

} // end of namespace snemo

CAMP_TYPE (snemo::exports::topology_2e);
CAMP_TYPE (snemo::exports::export_topology);

#endif // SNRECONSTRUCTION_EXPORTS_EXPORT_TOPOLOGY_H

// end of export_topology.h
