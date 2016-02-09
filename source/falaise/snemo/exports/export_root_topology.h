// -*- mode: c++ ; -*-
/* export_root_topology.h
 *
 * Author (s) :
 Francois Mauger <mauger@lpccaen.in2p3.fr>
 Xavier Garrido  <garrido@lal.in2p3.fr>
 Steven Calvez   <calvez@lal.in2p3.fr>
 * Creation date: 2016-02-04
 * Last modified: 2016-02-04
 *
 * License:
 *
 * Description:
 *
 *   Module for exporting the Topology Data to ROOT file(s)
 *
 * History:
 *
 */

#ifndef EXPORTS_EXPORT_ROOT_TOPOLOGY_H
#define EXPORTS_EXPORT_ROOT_TOPOLOGY_H 1

#include <iostream>

// #include <falaise/snemo/exports/export_topology.h>
#include <falaise/snemo/exports/root_utils.h>
#include <falaise/snemo/exports/loggable_support.h>

class TTree;

namespace snemo {

    namespace exports {

      struct export_root_topology : public export_topology,
                                    public loggable_support
      {
      public:

        /// Default constructor
        export_root_topology ();

        /// Destructor
        virtual ~export_root_topology ();

        /// Construct the ROOT tree branch structure
        void construct (unsigned int store_bits_,
                        const std::map<std::string,int> topics_,
                        unsigned int store_version_ = 0);

        /// Setup a ROOT tree from the internal structure of branches
        void setup_tree (TTree * tree_);

        /// Detach ROOT tree branches
        void detach_branches ();

        /// Fill all branches
        void fill_memory ();

        /// Fill the memory associated to a given branch
        void fill_branch_memory (branch_entry_type &);

        /// Smart print
        void print (std::ostream & out_ = std::clog,
                    const std::string & title_ = "",
                    const std::string & indent_ = "") const;

        /// Reset
        virtual void reset();

      private:
        uint32_t       _store_bits_; /// Store bits
        branch_manager _branch_manager_; /// Branch manager

      };

    } // end of namespace exports

} // end of namespace snemo

#endif // EXPORTS_EXPORT_ROOT_TOPOLOGY_H

// end of export_root_topology.h
