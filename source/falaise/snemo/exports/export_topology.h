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

    struct topology_1e : base_topology
    {
    public:
      topology_1e ();
      virtual void reset ();

    public:

      double electron_energy;
      double electron_angle;
      double electron_track_length;
      double electron_vertex_location;
      double electron_vertex_position_x;
      double electron_vertex_position_y;
      double electron_vertex_position_z;
    };

    struct topology_1e1a : base_topology // maybe make it inherit from 1e topology
    {
    public:
      topology_1e1a ();
      virtual void reset ();

    public:

      double electron_energy;
      double electron_angle;
      double electron_track_length;
      double alpha_angle;
      double alpha_track_length;
      double electron_alpha_angle;
      double electron_alpha_vertices_probability;
      double electron_alpha_vertices_distance_x;
      double electron_alpha_vertices_distance_y;
      double electron_alpha_vertices_distance_z;
      double electron_alpha_vertex_location;
      double alpha_delayed_time;
      double electron_vertex_location;
      double electron_vertex_position_x;
      double electron_vertex_position_y;
      double electron_vertex_position_z;
    };

    struct topology_2e : base_topology
    {
    public:
      topology_2e ();
      virtual void reset ();

    public:

      double electron_minimal_energy;
      double electron_maximal_energy;
      double electrons_energy_difference;
      double electrons_energy_sum;

      double electrons_internal_probability;
      double electrons_external_probability;

      double electrons_vertices_probability;
      double electrons_vertices_distance_x;
      double electrons_vertices_distance_y;
      double electrons_vertices_distance_z;
      double electrons_vertex_location;
      double electrons_vertex_position_x;
      double electrons_vertex_position_y;
      double electrons_vertex_position_z;

      double electrons_angle;
      double electrons_cos_angle;

      double electron_Emin_track_length;
      double electron_Emax_track_length;
    };

    struct topology_1e1p : base_topology
    {
    public:
      topology_1e1p ();
      virtual void reset ();

    public:

      double electron_energy;
      double positron_energy;
      double electron_positron_energy_difference;
      double electron_positron_energy_sum;

      double electron_positron_internal_probability;
      double electron_positron_external_probability;

      double electron_positron_vertices_probability;
      double electron_positron_vertices_distance_x;
      double electron_positron_vertices_distance_y;
      double electron_positron_vertices_distance_z;
      double electron_positron_vertex_location;
      double electron_positron_vertex_position_x;
      double electron_positron_vertex_position_y;
      double electron_positron_vertex_position_z;
      double electron_positron_angle;
      double electron_positron_cos_angle;

      double electron_track_length;
      double positron_track_length;

    };

    struct topology_2p : base_topology
    {
    public:
      topology_2p ();
      virtual void reset ();

    public:

      double positron_minimal_energy;
      double positron_maximal_energy;
      double positrons_energy_difference;
      double positrons_energy_sum;

      double positrons_internal_probability;
      double positrons_external_probability;

      double positrons_vertices_probability;
      double positrons_vertices_distance_x;
      double positrons_vertices_distance_y;
      double positrons_vertices_distance_z;
      double positrons_vertex_location;
      double positrons_vertex_position_x;
      double positrons_vertex_position_y;
      double positrons_vertex_position_z;
      double positrons_angle;
      double positrons_cos_angle;

      double positron_Emin_track_length;
      double positron_Emax_track_length;

    };

    struct topology_1e1g : base_topology
    {
    public:
      topology_1e1g ();
      virtual void reset ();

    public:
      double electron_energy;
      double gamma_energy;
      double electron_gamma_energy_sum;
      double electron_gamma_internal_probability;
      double electron_gamma_external_probability;
      double electron_vertex_location;
      double electron_vertex_position_x;
      double electron_vertex_position_y;
      double electron_vertex_position_z;
    };

    struct topology_1e2g : base_topology
    {
    public:
      topology_1e2g ();
      virtual void reset ();

    public:
      double electron_energy;
      double gamma_min_energy;
      double gamma_max_energy;
      double electron_gammas_energy_sum;
      double electron_gamma_min_internal_probability;
      double electron_gamma_min_external_probability;
      double electron_gamma_max_internal_probability;
      double electron_gamma_max_external_probability;
      double electron_vertex_location;
      double electron_vertex_position_x;
      double electron_vertex_position_y;
      double electron_vertex_position_z;
    };

    struct topology_1e3g : base_topology
    {
    public:
      topology_1e3g ();
      virtual void reset ();

    public:
      double electron_energy;
      double gamma_min_energy;
      double gamma_mid_energy;
      double gamma_max_energy;
      double electron_gammas_energy_sum;
      double electron_gamma_min_internal_probability;
      double electron_gamma_min_external_probability;
      double electron_gamma_mid_internal_probability;
      double electron_gamma_mid_external_probability;
      double electron_gamma_max_internal_probability;
      double electron_gamma_max_external_probability;
      double electron_vertex_location;
      double electron_vertex_position_x;
      double electron_vertex_position_y;
      double electron_vertex_position_z;

    };

    struct topology_2e1g : base_topology
    {
    public:
      topology_2e1g ();
      virtual void reset ();

    public:
      double electron_minimal_energy;
      double electron_maximal_energy;
      double gamma_energy;
      double electrons_energy_difference;
      double electrons_energy_sum;
      double electrons_gammas_energy_sum;

      double electrons_internal_probability;
      double electrons_external_probability;
      double electron_min_gamma_internal_probability;
      double electron_min_gamma_external_probability;
      double electron_max_gamma_internal_probability;
      double electron_max_gamma_external_probability;

      double electrons_vertices_probability;
      double electrons_vertices_distance_x;
      double electrons_vertices_distance_y;
      double electrons_vertices_distance_z;
      double electrons_vertex_location;
      double electrons_vertex_position_x;
      double electrons_vertex_position_y;
      double electrons_vertex_position_z;
      double electrons_angle;
      double electrons_cos_angle;

      double electron_Emin_track_length;
      double electron_Emax_track_length;

    };

    struct topology_2e2g : base_topology
    {
    public:
      topology_2e2g ();
      virtual void reset ();

    public:
      double electron_minimal_energy;
      double electron_maximal_energy;
      double gamma_min_energy;
      double gamma_max_energy;
      double electrons_energy_difference;
      double electrons_energy_sum;
      double electrons_gammas_energy_sum;

      double electrons_internal_probability;
      double electrons_external_probability;
      double electron_min_gamma_min_internal_probability;
      double electron_min_gamma_max_internal_probability;
      double electron_min_gamma_min_external_probability;
      double electron_min_gamma_max_external_probability;
      double electron_max_gamma_min_internal_probability;
      double electron_max_gamma_max_internal_probability;
      double electron_max_gamma_min_external_probability;
      double electron_max_gamma_max_external_probability;

      double electrons_vertices_probability;
      double electrons_vertices_distance_x;
      double electrons_vertices_distance_y;
      double electrons_vertices_distance_z;
      double electrons_vertex_location;
      double electrons_vertex_position_x;
      double electrons_vertex_position_y;
      double electrons_vertex_position_z;
      double electrons_angle;
      double electrons_cos_angle;

      double electron_Emin_track_length;
      double electron_Emax_track_length;

    };

    struct topology_2e3g : base_topology
    {
    public:
      topology_2e3g ();
      virtual void reset ();

    public:
      double electron_minimal_energy;
      double electron_maximal_energy;
      double gamma_min_energy;
      double gamma_mid_energy;
      double gamma_max_energy;
      double electrons_energy_difference;
      double electrons_energy_sum;
      double electrons_gammas_energy_sum;

      double electrons_internal_probability;
      double electrons_external_probability;
      double electron_min_gamma_min_internal_probability;
      double electron_min_gamma_min_external_probability;
      double electron_min_gamma_mid_internal_probability;
      double electron_min_gamma_mid_external_probability;
      double electron_min_gamma_max_internal_probability;
      double electron_min_gamma_max_external_probability;
      double electron_max_gamma_min_internal_probability;
      double electron_max_gamma_min_external_probability;
      double electron_max_gamma_mid_internal_probability;
      double electron_max_gamma_mid_external_probability;
      double electron_max_gamma_max_internal_probability;
      double electron_max_gamma_max_external_probability;

      double electrons_vertices_probability;
      double electrons_vertices_distance_x;
      double electrons_vertices_distance_y;
      double electrons_vertices_distance_z;
      double electrons_vertex_location;
      double electrons_vertex_position_x;
      double electrons_vertex_position_y;
      double electrons_vertex_position_z;
      double electrons_angle;
      double electrons_cos_angle;

      double electron_Emin_track_length;
      double electron_Emax_track_length;

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

      const topology_1e & get_1e_topology () const;

      topology_1e & grab_1e_topology ();

      const topology_1e1a & get_1e1a_topology () const;

      topology_1e1a & grab_1e1a_topology ();

      const topology_2e & get_2e_topology () const;

      topology_2e & grab_2e_topology ();

      const topology_1e1p & get_1e1p_topology () const;

      topology_1e1p & grab_1e1p_topology ();

      const topology_2p & get_2p_topology () const;

      topology_2p & grab_2p_topology ();

      const topology_1e1g & get_1e1g_topology () const;

      topology_1e1g & grab_1e1g_topology ();

      const topology_1e2g & get_1e2g_topology () const;

      topology_1e2g & grab_1e2g_topology ();

      const topology_1e3g & get_1e3g_topology () const;

      topology_1e3g & grab_1e3g_topology ();

      const topology_2e1g & get_2e1g_topology () const;

      topology_2e1g & grab_2e1g_topology ();

      const topology_2e2g & get_2e2g_topology () const;

      topology_2e2g & grab_2e2g_topology ();

      const topology_2e3g & get_2e3g_topology () const;

      topology_2e3g & grab_2e3g_topology ();

    public:

      // Topology 2e data :
      snemo::exports::topology_1e _topology_1e_;
      snemo::exports::topology_1e1a _topology_1e1a_;
      snemo::exports::topology_2e _topology_2e_;
      snemo::exports::topology_1e1p _topology_1e1p_;
      snemo::exports::topology_2p _topology_2p_;
      snemo::exports::topology_1e1g _topology_1e1g_;
      snemo::exports::topology_1e2g _topology_1e2g_;
      snemo::exports::topology_1e3g _topology_1e3g_;
      snemo::exports::topology_2e1g _topology_2e1g_;
      snemo::exports::topology_2e2g _topology_2e2g_;
      snemo::exports::topology_2e3g _topology_2e3g_;

    };

  } // end of namespace exports

} // end of namespace snemo

CAMP_TYPE (snemo::exports::topology_1e);
CAMP_TYPE (snemo::exports::topology_1e1a);
CAMP_TYPE (snemo::exports::topology_2e);
CAMP_TYPE (snemo::exports::topology_1e1p);
CAMP_TYPE (snemo::exports::topology_2p);
CAMP_TYPE (snemo::exports::topology_1e1g);
CAMP_TYPE (snemo::exports::topology_1e2g);
CAMP_TYPE (snemo::exports::topology_1e3g);
CAMP_TYPE (snemo::exports::topology_2e1g);
CAMP_TYPE (snemo::exports::topology_2e2g);
CAMP_TYPE (snemo::exports::topology_2e3g);
CAMP_TYPE (snemo::exports::export_topology);

#endif // SNRECONSTRUCTION_EXPORTS_EXPORT_TOPOLOGY_H

// end of export_topology.h
