// -*- mode: c++ ; -*-
/* export_topology.h
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

        static void implement_introspection ();

        struct introspection_activator
        {
          introspection_activator ();
        };

        void print (std::ostream & out_ = std::clog,
                    const std::string & title_ = "",
                    const std::string & indent_ = "") const;

      public:

        // Topology 2e data :
        topology_2e                     _topology_2e_;

      };

      template<class Type>
      const std::string & get_class_description ()
      {
        static boost::scoped_ptr<std::string> g_description (0);
        if (g_description.get () == 0)
          {
            std::ostringstream oss;

            const camp::Class & meta_class = camp::classByType<Type> ();
            for (int i = 0; i < meta_class.propertyCount(); i++)
              {
                const camp::Property & prop = meta_class.property (i);
                if (i > 0) oss << ';';
                oss << prop.name ();
                if (prop.hasTag ("ctype"))
                  {
                    oss << '/' << prop.tag ("ctype");
                  }
                if (prop.hasTag ("unit"))
                  {
                    oss << '[' << prop.tag ("unit") << ']';
                  }
              }

            g_description.reset (new std::string (oss.str()));
          }
        return *g_description.get();
      }

    } // end of namespace exports

  } // end of namespace reconstruction

} // end of namespace snemo

CAMP_TYPE (snemo::reconstruction::exports::topology_2e);
CAMP_TYPE (snemo::reconstruction::exports::export_topology);

#endif // SNRECONSTRUCTION_EXPORTS_EXPORT_TOPOLOGY_H

// end of export_topology.h
