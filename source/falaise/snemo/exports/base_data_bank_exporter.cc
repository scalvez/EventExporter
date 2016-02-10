// -*- mode: c++ ; -*-
/* base_data_bank_exporter.cc */

#include <falaise/snemo/exports/base_data_bank_exporter.h>
#include <falaise/snemo/exports/export_topology.h>

#include <mctools/simulated_data.h>

#include <mctools/utils.h>
// #include <sncore/utils/utils.h>

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

      bool base_data_bank_exporter::is_initialized () const
      {
        return _initialized_;
      }

      bool base_data_bank_exporter::has_geom_manager () const
      {
        return _geom_manager_ != 0;
      }

      const geomtools::manager & base_data_bank_exporter::get_geom_manager () const
      {
        return *_geom_manager_;
      }

      void base_data_bank_exporter::set_geom_manager (const geomtools::manager & gmgr_)
      {
        DT_THROW_IF (is_initialized (), std::logic_error, "Topology exporter is already initialized ! ");
        _geom_manager_ = &gmgr_;

        // Check setup label:
        const std::string & setup_label = _geom_manager_->get_setup_label ();

        // DT_THROW_IF(setup_label != "snemo" && setup_label != "snemo::tracker_commissioning",
        //             std::logic_error, "Setup label '" << setup_label << "' is not supported !");

        return;
      }

      uint32_t base_data_bank_exporter::get_export_flags () const
      {
        return _export_flags_;
      }

      void base_data_bank_exporter::unset_exported (unsigned int export_bit_)
      {
        _export_flags_ &= ~export_bit_;
        return;
      }

      void base_data_bank_exporter::set_exported (unsigned int export_bit_)
      {
        _export_flags_ |= export_bit_;
        return;
      }

      bool base_data_bank_exporter::is_exported (unsigned int export_bit_) const
      {
        return (_export_flags_ & export_bit_);
      }

      int base_data_bank_exporter::get_topic_export_level(const std::string & topic_label_) const
      {
        // if (topic_label_ == "CAT")
        //   {
        //     if (_export_cat_infos_) return EXPORT_TOPIC_INCLUDE;
        //   }
        return EXPORT_TOPIC_NO_INCLUDE;
      }

      base_data_bank_exporter::base_data_bank_exporter ()
      {
        _initialized_ = false;
        _init_defaults ();
        return;
      }

      base_data_bank_exporter::~base_data_bank_exporter ()
      {
        if (is_initialized ())
          {
            reset ();
          }
        return;
      }

      void base_data_bank_exporter::initialize (const datatools::properties & setup_)
      {
        {
          datatools::properties::keys_col_type bank_label_keys;
          setup_.keys_starting_with(bank_label_keys, "export.bank.label.");
          for (datatools::properties::keys_col_type::const_iterator i
                 = bank_label_keys.begin ();
               i != bank_label_keys.end ();
               i++)
            {
              std::string bank_label = *i;
              boost::algorithm::replace_first(bank_label, "export.bank.label.", "");
              _bank_labels_[bank_label] = setup_.fetch_string (*i);
            }
        }

        //dump (std::clog);

        _initialized_ = true;
        return;
      }

      void base_data_bank_exporter::reset ()
      {
        DT_THROW_IF (! is_initialized (), std::logic_error,  "Data bank exporter is not initialized ! ");
        _initialized_ = false;
        _init_defaults ();
        return;
      }

      void base_data_bank_exporter::_set_default_bank_labels ()
      {
        _bank_labels_.clear ();
        // Default bank names for "EH", "SD", "CD", "TCD", "TTD" :
        _bank_labels_[sdm::data_info::default_topology_data_label()]    = sdm::data_info::default_topology_data_label();
        return;
      }

      void base_data_bank_exporter::_init_defaults ()
      {
        _set_default_bank_labels ();
        _export_flags_ = 0; //NO_EXPORT;
        _geom_manager_ = 0;
        return;
      }

      void base_data_bank_exporter::dump (std::ostream & out_) const
      {
        out_ << "Event exporter: " << std::endl;
        out_ << "|-- " << "Initialized : " << is_initialized () << std::endl;
        out_ << "|-- " << "Geometry manager : ";
        if (_geom_manager_ != 0 )
          {
            out_ << _geom_manager_->get_setup_label () << ' '
                 << _geom_manager_->get_setup_version () << ' ';
          }
        else
          {
            out_ << "<none>";
          }
        out_ << std::endl;
        out_ << "|-- " << "Bank labels : " << std::endl;
        for (std::map<std::string, std::string>::const_iterator i
               = _bank_labels_.begin();
             i != _bank_labels_.end();
             i++)
          {
            std::map<std::string, std::string>::const_iterator j = i;
            j++;
            out_ << "|   ";
            if (j == _bank_labels_.end())
              {
                out_ << "`-- ";
              }
            else
              {
                out_ << "|-- ";
              }
            out_ << i->first << " : " << "'" << i->second << "'" << std::endl;
          }

        out_ << "`-- " << "Export flags : " << '[' << _export_flags_ << ']' << std::endl;

        return;
      }

      int base_data_bank_exporter::run ()
      {
        if (! is_initialized ())
          {
            std::ostringstream message;
            message << "snemo::exports::base_data_bank_exporter::run: "
                    << "Data bank(s) exporter is not initialized ! ";
            throw std::logic_error (message.str ());
          }

        return 0;
      }

      const std::map<std::string, std::string> &
      base_data_bank_exporter::get_bank_labels () const
      {
        return _bank_labels_;
      }

    } // end of namespace exports

} // end of namespace snemo

// end of topology_exporter.cc
