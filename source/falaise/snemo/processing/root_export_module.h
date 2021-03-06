// -*- mode: c++ ; -*-
/* root_export_module.h
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
 *   Module for exporting the SuperNEMO Topology Data in ROOT tree/file(s)
 *
 * History:
 *
 */

#ifndef __root_export_module_h
#define __root_export_module_h 1

#include <string>
#include <fstream>

#include <boost/scoped_ptr.hpp>

#include <dpp/base_module.h>

#include <falaise/snemo/exports/topology_exporter.h>
#include <falaise/snemo/exports/base_data_bank_exporter.h>
#include <falaise/snemo/exports/export_root_topology.h>

#include <datatools/smart_filename.h>

class TFile;
class TTree;

namespace snemo {

  namespace exports {
    class root_export_topology;
  }

  namespace processing {

    class root_export_module : public dpp::base_module
    {
    public:

      struct io_accounting_type
      {
        int max_records_per_file; //!< Maximum number of event records per file
        int max_records_total;    //!< Maximum number of event records to be processed
        int max_files;            //!< Maximum number of data files to be processed
        bool terminated;          //!< Termination flag
        int file_record_counter;  //!< Event record counter in the current file
        int record_counter;       //!< Total event record counter
        int file_index;           //!<Index of the current datafile index

        io_accounting_type ();
        void reset ();
      };

      bool is_terminated () const;

      /// Constructor
      root_export_module(datatools::logger::priority = datatools::logger::PRIO_FATAL);

      /// Destructor
      virtual ~root_export_module();

      /// Initialization
      virtual void initialize(const datatools::properties  & setup_,
                              datatools::service_manager   & service_manager_,
                              dpp::module_handle_dict_type & module_dict_);

      /// Reset
      virtual void reset();

      /// Data record processing
      virtual process_status process(datatools::things & data_);

    protected:

      process_status _process_event (const datatools::things & data_);

      process_status _open_file (const std::string & filename_);

      int _init_tree ();

      int _store_event (const datatools::things & data_);

      int _terminate_tree ();

      int _close_file ();

      /// Give default values to specific class members
      void _set_defaults ();

    private:

      datatools::smart_filename _root_filenames_; //!< Filenames

      exports::topology_exporter   _topology_exporter_;  //!< The exporter
      boost::scoped_ptr<exports::export_root_topology> _root_topology_;
      TFile *                                       _root_sink_;
      TTree *                                       _root_tree_;
      io_accounting_type                            _io_accounting_;

      // Macro to automate the registration of the module :
      DPP_MODULE_REGISTRATION_INTERFACE(root_export_module);

    };

  } // end of namespace processing

} // end of namespace snemo

#endif // __processing__root_export_module_h

// end of root_export_module.h
