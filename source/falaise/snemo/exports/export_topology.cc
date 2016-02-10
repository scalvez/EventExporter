// -*- mode: c++ ; -*-
/* export_topology.cc */

#include <falaise/snemo/exports/export_topology.h>

#include <sstream>
#include <limits>

namespace snemo {

    namespace exports {

      /***********************************************/

      base_topology::base_topology ()
      {
        return;
      }

      topology_1e::topology_1e ()
      {
        reset();
        return;
      }

      void topology_1e::reset ()
      {
          return;
      }

      topology_1e1a::topology_1e1a ()
      {
        reset();
        return;
      }

      void topology_1e1a::reset ()
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

      topology_1e1p::topology_1e1p ()
      {
        reset();
        return;
      }

      void topology_1e1p::reset ()
      {
          return;
      }

      topology_2p::topology_2p ()
      {
        reset();
        return;
      }

      void topology_2p::reset ()
      {
          return;
      }

      topology_1e1g::topology_1e1g ()
      {
        reset();
        return;
      }

      void topology_1e1g::reset ()
      {
          return;
      }

      topology_1e2g::topology_1e2g ()
      {
        reset();
        return;
      }

      void topology_1e2g::reset ()
      {
          return;
      }

      topology_1e3g::topology_1e3g ()
      {
        reset();
        return;
      }

      void topology_1e3g::reset ()
      {
          return;
      }

      topology_2e1g::topology_2e1g ()
      {
        reset();
        return;
      }

      void topology_2e1g::reset ()
      {
          return;
      }

      topology_2e2g::topology_2e2g ()
      {
        reset();
        return;
      }

      void topology_2e2g::reset ()
      {
          return;
      }

      topology_2e3g::topology_2e3g ()
      {
        reset();
        return;
      }

      void topology_2e3g::reset ()
      {
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
       _topology_1e_.reset ();
       _topology_1e1a_.reset ();
       _topology_2e_.reset ();
       _topology_1e1p_.reset ();
       _topology_2p_.reset ();
       _topology_1e1_.reset ();
       _topology_1e2_.reset ();
       _topology_1e3_.reset ();
       _topology_2e1_.reset ();
       _topology_2e2_.reset ();
       _topology_2e3_.reset ();
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

      const topology_1e & export_topology::get_1e_topology () const
      {
        return _topology_1e_;
      }

      topology_1e & export_topology::grab_1e_topology ()
      {
        return _topology_1e_;
      }

      const topology_1e1a & export_topology::get_1e1a_topology () const
      {
        return _topology_1e1a_;
      }

      topology_1e1a & export_topology::grab_1e1a_topology ()
      {
        return _topology_1e1a_;
      }

      const topology_2e & export_topology::get_2e_topology () const
      {
        return _topology_2e_;
      }

      topology_2e & export_topology::grab_2e_topology ()
      {
        return _topology_2e_;
      }

      const topology_1e1p & export_topology::get_1e1p_topology () const
      {
        return _topology_1e1p_;
      }

      topology_1e1p & export_topology::grab_1e1p_topology ()
      {
        return _topology_1e1p_;
      }

      const topology_2p & export_topology::get_2p_topology () const
      {
        return _topology_2p_;
      }

      topology_2p & export_topology::grab_2p_topology ()
      {
        return _topology_2p_;
      }

      const topology_1e1g & export_topology::get_1e1g_topology () const
      {
        return _topology_1e1g_;
      }

      topology_1e1g & export_topology::grab_1e1g_topology ()
      {
        return _topology_1e1g_;
      }

      const topology_1e2g & export_topology::get_1e2g_topology () const
      {
        return _topology_1e2g_;
      }

      topology_1e2g & export_topology::grab_1e2g_topology ()
      {
        return _topology_1e2g_;
      }

      const topology_1e3g & export_topology::get_1e3g_topology () const
      {
        return _topology_1e3g_;
      }

      topology_1e3g & export_topology::grab_1e3g_topology ()
      {
        return _topology_1e3g_;
      }

      const topology_2e1g & export_topology::get_2e1g_topology () const
      {
        return _topology_2e1g_;
      }

      topology_2e1g & export_topology::grab_2e1g_topology ()
      {
        return _topology_2e1g_;
      }

      const topology_2e2g & export_topology::get_2e2g_topology () const
      {
        return _topology_2e2g_;
      }

      topology_2e2g & export_topology::grab_2e2g_topology ()
      {
        return _topology_2e2g_;
      }

      const topology_2e3g & export_topology::get_2e3g_topology () const
      {
        return _topology_2e3g_;
      }

      topology_2e3g & export_topology::grab_2e3g_topology ()
      {
        return _topology_2e3g_;
      }

      void export_topology::implement_introspection ()
      {
        std::clog << "NOTICE: export_topology::implement_introspection: Entering...\n";

        try{
          camp::Class::declare< topology_1e >("topology_1e")
            .tag ("version", 0)
            .constructor0()
            ;
          camp::Class::declare< topology_1e1a >("topology_1e1a")
            .tag ("version", 0)
            .constructor0()
            ;
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
          camp::Class::declare< topology_1e1p >("topology_1e1p")
            .tag ("version", 0)
            .constructor0()
            ;
          camp::Class::declare< topology_2p >("topology_2p")
            .tag ("version", 0)
            .constructor0()
            ;
          camp::Class::declare< topology_1e1g >("topology_1e1g")
            .tag ("version", 0)
            .constructor0()
            ;
          camp::Class::declare< topology_1e2g >("topology_1e2g")
            .tag ("version", 0)
            .constructor0()
            ;
          camp::Class::declare< topology_1e3g >("topology_1e3g")
            .tag ("version", 0)
            .constructor0()
            ;
          camp::Class::declare< topology_2e1g >("topology_2e1g")
            .tag ("version", 0)
            .constructor0()
            ;
          camp::Class::declare< topology_2e2g >("topology_2e2g")
            .tag ("version", 0)
            .constructor0()
            ;
          camp::Class::declare< topology_2e3g >("topology_2e3g")
            .tag ("version", 0)
            .constructor0()
            ;

           /*************************************************************************/

          camp::Class::declare< export_topology >("export_topology")
            .tag ("version", 0)
            .constructor0()
            // Topology 2e :
            .property ("e", &export_topology::_topology_1e_)
            .property ("1e1a", &export_topology::_topology_1e1a_)
            .property ("2e", &export_topology::_topology_2e_)
            .property ("1e1p", &export_topology::_topology_1e1p_)
            .property ("2p", &export_topology::_topology_2p_)
            .property ("1e1g", &export_topology::_topology_1e1g_)
            .property ("1e2g", &export_topology::_topology_1e2g_)
            .property ("1e3g", &export_topology::_topology_1e3g_)
            .property ("2e1g", &export_topology::_topology_2e1g_)
            .property ("2e2g", &export_topology::_topology_2e2g_)
            .property ("2e3g", &export_topology::_topology_2e3g_)
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
