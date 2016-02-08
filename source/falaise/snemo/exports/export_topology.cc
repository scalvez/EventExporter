// -*- mode: c++ ; -*-
/* export_topology.cc */

#include <falaise/snemo/exports/export_topology.h>
#include <falaise/snemo/exports/topology_exporter.h>

#include <sstream>
#include <limits>

namespace snemo {

    namespace exports {

      /***********************************************/

      base_topology::base_topology ()
      {
        return;
      }

      topology_2e::topology_2e ()
      {
        reset();
        return;
      }

      void topology_2e::reset ()
      {
        electron_minimal_energy = constants::INVALID_DOUBLE;
        electron_maximal_energy = constants::INVALID_DOUBLE;

        electrons_internal_probability = constants::INVALID_DOUBLE;
        electrons_external_probability = constants::INVALID_DOUBLE;

        electrons_angle = constants::INVALID_DOUBLE;

          return;
      }

      /***********************************************/

      export_topology::export_topology ()
      {
        static bool activated = false;
        if (! activated)
          {
            implement_introspection ();
            activated = true;
          }

      reset ();
        return;
      }

      export_topology::~export_topology ()
      {
        return;
      }

      void export_topology::reset ()
      {
        clear_data ();
        return;
      }

      void export_topology::clear_data ()
      {
       _topology_2e_.reset ();
        return;
      }

      void export_topology::print (std::ostream & out_,
                                const std::string & title_,
                                const std::string & indent_) const
      {
        if (! title_.empty ())
          {
            out_ << indent_ << title_ << " : \n";
          }
        out_ << indent_ << "|-- "
             << "Topology 2e : "
             << std::endl;

        return;
      }

      const topology_2e & export_topology::get_2e_topology () const
      {
        return _topology_2e_;
      }

      topology_2e & export_topology::grab_2e_topology ()
      {
        return _topology_2e_;
      }

      void export_topology::implement_introspection ()
      {
        std::clog << "NOTICE: export_topology::implement_introspection: Entering...\n";

        try{
          camp::Class::declare< topology_2e >("topology_2e")
            .tag ("version", 0)
            .constructor0()
            .property ("electron_minimal_energy", &topology_2e::electron_minimal_energy)
            .tag ("ctype", "double")
            .tag ("unit", "MeV")
            .property ("electron_maximal_energy", &topology_2e::electron_maximal_energy)
            .tag ("ctype", "double")
            .tag ("unit", "MeV")
            .property ("electrons_internal_probability", &topology_2e::electrons_internal_probability)
            .tag ("ctype", "double")
            .property ("electrons_external_probability", &topology_2e::electrons_external_probability)
            .tag ("ctype", "double")
            .property ("electrons_angle", &topology_2e::electrons_angle)
            .tag ("ctype", "double")
            .tag ("unit", "radian")
            ;

           /*************************************************************************/

          camp::Class::declare< export_topology >("export_topology")
            .tag ("version", 0)
            .constructor0()
            // Topology 2e :
            .property ("topology_2e", &export_topology::_topology_2e_)

            // more...
            ;

        }
        catch(std::exception & x)
          {
            std::cerr << "ERROR: export_topology::implement_introspection: "
                      << x.what () << std::endl;
          }
        catch(...)
          {
            std::cerr << "ERROR: export_topology::implement_introspection: "
                      << "Unexpected error !" << std::endl;
          }
        std::clog << "NOTICE: export_topology::implement_introspection: Exiting.\n";
      }

    }  // end of namespace exports

}  // end of namespace snemo

/* end of export_topology.cc */
