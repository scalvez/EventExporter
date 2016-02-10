// -*- mode: c++ ; -*-
/* topology_exporter.cc */

#include <falaise/snemo/datamodels/pid_utils.h>

// Standard library
#include <regex>

#include <falaise/snemo/exports/topology_exporter.h>
#include <falaise/snemo/exports/export_topology.h>
#include <falaise/snemo/exports/base_data_bank_exporter.h>

#include <falaise/snemo/datamodels/topology_data.h>
#include <falaise/snemo/datamodels/topology_1e_pattern.h>
#include <falaise/snemo/datamodels/topology_1e1a_pattern.h>
#include <falaise/snemo/datamodels/topology_2e_pattern.h>
#include <falaise/snemo/datamodels/topology_1e1p_pattern.h>
#include <falaise/snemo/datamodels/topology_2p_pattern.h>
#include <falaise/snemo/datamodels/topology_1eNg_pattern.h>
#include <falaise/snemo/datamodels/topology_2eNg_pattern.h>

#include <mctools/utils.h>

#include <geomtools/manager.h>
#include <datatools/things_macros.h>

#include <boost/algorithm/string/replace.hpp>
#include <boost/foreach.hpp>


namespace snemo {

    namespace exports {

      // namespace scm = snemo::core::model;
      namespace sdm = snemo::datamodel;
      // namespace scu = snemo::core::utils;
      namespace se = snemo::exports;

      topology_exporter::topology_exporter ()
      {
        return;
      }

      topology_exporter::~topology_exporter ()
      {
        return;
      }

      void topology_exporter::initialize (const datatools::properties & setup_)
      {
        this->base_data_bank_exporter::initialize(setup_);

        if (setup_.has_flag ("export.topology_2e"))
          {
            this->base_data_bank_exporter::set_exported (se::topology_exporter::EXPORT_TOPOLOGY_2E);
          }

        // If no export directive is given, export all data banks :
        if (base_data_bank_exporter::_export_flags_ == se::topology_exporter::NO_EXPORT)
          {
            this->base_data_bank_exporter::set_exported (se::topology_exporter::EXPORT_ALL);
          }

        // WIP : Maybe there should be flags specific to each data bank

        return;
      }

      // void base_data_bank_exporter::_set_default_bank_labels ()
      // {
      //   base_data_bank_exporter::_set_default_bank_labels();
      //   // Default bank names for "EH", "SD", "CD", "TCD", "TTD" :
      //   base_data_bank_exporter::_bank_labels_[sdm::data_info::default_topology_data_label()]    = sdm::data_info::default_topology_data_label();
      //   return;
      // }

      //static
      std::string topology_exporter::get_export_bit_label (unsigned int bit_)
      {
        if (bit_ == topology_exporter::EXPORT_TOPOLOGY_2E) return "topology_2e";
        return "";
      }

      void topology_exporter::dump (std::ostream & out_) const
      {
        base_data_bank_exporter::dump(out_);

        for (unsigned int bit = 1; bit <= topology_exporter::EXPORT_LAST; bit *=2)
          {
            out_ << "    ";
            if (bit == topology_exporter::EXPORT_LAST)
              {
                out_ << "`-- ";
              }
            else
              {
                out_ << "|-- ";
              }
            out_ << "Export '" << topology_exporter::get_export_bit_label (bit) << "' : ";
            if (_export_flags_ & bit)
              {
                out_ << "yes";
              }
            else
              {
                out_ << "no";
              }
            out_ << std::endl;
            //if (bit == topology_exporter::EXPORT_LAST) break;
          }
        return;
      }

      int topology_exporter::run (const sdm::event_record & er_,
                                  se::export_topology & et_)
      {
        // if (! is_initialized ())
        //   {
        //     std::ostringstream message;
        //     message << "snemo::reconstruction::exports::topology_exporter::run: "
        //             << "Topology exporter is not initialized ! ";
        //     throw std::logic_error (message.str ());
        //   }
        base_data_bank_exporter::run();

        et_.clear_data ();

        //twice the work to get the TD bank

        const std::string & td_label = base_data_bank_exporter::_bank_labels_[sdm::data_info::default_topology_data_label()];
        if (! DATATOOLS_THINGS_CHECK_BANK(er_, td_label, sdm::topology_data))
          {
            DT_THROW_IF (true, std::logic_error, "Missing topology data to be processed !");
          }
        DATATOOLS_THINGS_CONST_BANK(er_, td_label, sdm::topology_data, TD);

        const datatools::properties & td_aux = TD.get_auxiliaries();

        DT_THROW_IF (! td_aux.has_key(snemo::datamodel::pid_utils::classification_label_key()), std::logic_error, "Missing TD classification property !");

        const std::string & a_classification = td_aux.fetch_string(snemo::datamodel::pid_utils::classification_label_key());

        DT_THROW_IF (! TD.has_pattern(), std::logic_error, "Missing topology data pattern !");

        if (a_classification == "1e") {
          if (base_data_bank_exporter::is_exported (se::topology_exporter::EXPORT_TOPOLOGY_1E))
            _export_topology_1e (er_, et_);
        } else if (a_classification == "1e1a") {
          if (base_data_bank_exporter::is_exported (se::topology_exporter::EXPORT_TOPOLOGY_1E1A))
            _export_topology_1e1a (er_, et_);
        } else if (a_classification == "2e") {
          if (base_data_bank_exporter::is_exported (se::topology_exporter::EXPORT_TOPOLOGY_2E))
            _export_topology_2e (er_, et_);
        } else if (a_classification == "1e1p") {
          if (base_data_bank_exporter::is_exported (se::topology_exporter::EXPORT_TOPOLOGY_1E1P))
            _export_topology_1e1p (er_, et_);
        } else if (a_classification == "2p") {
          if (base_data_bank_exporter::is_exported (se::topology_exporter::EXPORT_TOPOLOGY_2P))
            _export_topology_2p (er_, et_);
        } else if (a_classification == "1e1g") {
          if (base_data_bank_exporter::is_exported (se::topology_exporter::EXPORT_TOPOLOGY_1E1G))
            _export_topology_1e1g (er_, et_);
        } else if (a_classification == "1e2g") {
          if (base_data_bank_exporter::is_exported (se::topology_exporter::EXPORT_TOPOLOGY_1E2G))
            _export_topology_1e2g (er_, et_);
        } else if (a_classification == "1e3g") {
          if (base_data_bank_exporter::is_exported (se::topology_exporter::EXPORT_TOPOLOGY_1E3G))
            _export_topology_1e3g (er_, et_);
        } else if (std::regex_match(a_classification, std::regex("1e[0-9]+g"))) {
          DT_LOG_DEBUG(get_logging_priority(), "Non supported classification '" <<
                       a_classification << "' for now !");
        } else if (a_classification == "2e1g") {
          if (base_data_bank_exporter::is_exported (se::topology_exporter::EXPORT_TOPOLOGY_2E1G))
            _export_topology_2e1g (er_, et_);
        } else if (a_classification == "2e2g") {
          if (base_data_bank_exporter::is_exported (se::topology_exporter::EXPORT_TOPOLOGY_2E2G))
            _export_topology_2e2g (er_, et_);
        } else if (a_classification == "2e3g") {
          if (base_data_bank_exporter::is_exported (se::topology_exporter::EXPORT_TOPOLOGY_2E3G))
            _export_topology_2e3g (er_, et_);
        } else if (std::regex_match(a_classification, std::regex("2e[0-9]+g"))) {
          DT_LOG_DEBUG(get_logging_priority(), "Non supported classification '" <<
                       a_classification << "' for now !");
        } else {
          DT_LOG_DEBUG(get_logging_priority(), "Non supported classification '" << a_classification << "' !");
        }

        // et_.print (std::clog, "Export topology", "DEVEL: ");
        return 0;
      }

      int topology_exporter::_export_topology_1e (const datatools::things & er_,
                                                  se::export_topology & et_)
      {
        const snemo::datamodel::topology_1e_pattern & a_1e_pattern
          = dynamic_cast<const snemo::datamodel::topology_1e_pattern &>(TD.get_pattern());

        return 0;
      }

      int topology_exporter::_export_topology_1e1a (const datatools::things & er_,
                                                  se::export_topology & et_)
      {
        const snemo::datamodel::topology_1e1a_pattern & a_1e1a_pattern
          = dynamic_cast<const snemo::datamodel::topology_1e1a_pattern &>(TD.get_pattern());

        return 0;
      }

      int topology_exporter::_export_topology_2e (const datatools::things & er_,
                                                  se::export_topology & et_)
      {
        const snemo::datamodel::topology_2e_pattern & a_2e_pattern
          = dynamic_cast<const snemo::datamodel::topology_2e_pattern &>(TD.get_pattern());

        return 0;
      }

      int topology_exporter::_export_topology_1e1p (const datatools::things & er_,
                                                  se::export_topology & et_)
      {
        const snemo::datamodel::topology_1e1p_pattern & a_1e1p_pattern
          = dynamic_cast<const snemo::datamodel::topology_2e_pattern &>(TD.get_pattern());

        return 0;
      }

      int topology_exporter::_export_topology_2p (const datatools::things & er_,
                                                  se::export_topology & et_)
      {
        const snemo::datamodel::topology_2p_pattern & a_2p_pattern
          = dynamic_cast<const snemo::datamodel::topology_2p_pattern &>(TD.get_pattern());

        return 0;
      }

      int topology_exporter::_export_topology_1e1g (const datatools::things & er_,
                                                  se::export_topology & et_)
      {
        const snemo::datamodel::topology_1e1g_pattern & a_1e1g_pattern
          = dynamic_cast<const snemo::datamodel::topology_1e1g_pattern &>(TD.get_pattern());

        return 0;
      }

      int topology_exporter::_export_topology_1e2g (const datatools::things & er_,
                                                  se::export_topology & et_)
      {
        const snemo::datamodel::topology_1e2g_pattern & a_1e2g_pattern
          = dynamic_cast<const snemo::datamodel::topology_1e2g_pattern &>(TD.get_pattern());

        return 0;
      }

      int topology_exporter::_export_topology_1e3g (const datatools::things & er_,
                                                  se::export_topology & et_)
      {
        const snemo::datamodel::topology_1e3g_pattern & a_1e3g_pattern
          = dynamic_cast<const snemo::datamodel::topology_1e3g_pattern &>(TD.get_pattern());

        return 0;
      }


      int topology_exporter::_export_topology_2e1g (const datatools::things & er_,
                                                  se::export_topology & et_)
      {
        const snemo::datamodel::topology_2e1g_pattern & a_2e1g_pattern
          = dynamic_cast<const snemo::datamodel::topology_2e1g_pattern &>(TD.get_pattern());

        return 0;
      }

      int topology_exporter::_export_topology_2e2g (const datatools::things & er_,
                                                  se::export_topology & et_)
      {
        const snemo::datamodel::topology_2e2g_pattern & a_2e2g_pattern
          = dynamic_cast<const snemo::datamodel::topology_2e2g_pattern &>(TD.get_pattern());

        return 0;
      }

      int topology_exporter::_export_topology_2e3g (const datatools::things & er_,
                                                  se::export_topology & et_)
      {
        const snemo::datamodel::topology_2e3g_pattern & a_2e3g_pattern
          = dynamic_cast<const snemo::datamodel::topology_2e3g_pattern &>(TD.get_pattern());

        return 0;
      }

    } // end of namespace exports

} // end of namespace snemo

// end of topology_exporter.cc
