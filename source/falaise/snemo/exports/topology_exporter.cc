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

      if (setup_.has_flag ("export.topology_1e"))
        {
          this->base_data_bank_exporter::set_exported (se::topology_exporter::EXPORT_TOPOLOGY_1E);
        }

      if (setup_.has_flag ("export.topology_1e1a"))
        {
          this->base_data_bank_exporter::set_exported (se::topology_exporter::EXPORT_TOPOLOGY_1E1A);
        }

      if (setup_.has_flag ("export.topology_2e"))
        {
          this->base_data_bank_exporter::set_exported (se::topology_exporter::EXPORT_TOPOLOGY_2E);
        }

      if (setup_.has_flag ("export.topology_1e1p"))
        {
          this->base_data_bank_exporter::set_exported (se::topology_exporter::EXPORT_TOPOLOGY_1E1P);
        }

      if (setup_.has_flag ("export.topology_2p"))
        {
          this->base_data_bank_exporter::set_exported (se::topology_exporter::EXPORT_TOPOLOGY_2P);
        }

      if (setup_.has_flag ("export.topology_1e1g"))
        {
          this->base_data_bank_exporter::set_exported (se::topology_exporter::EXPORT_TOPOLOGY_1E1G);
        }

      if (setup_.has_flag ("export.topology_1e2g"))
        {
          this->base_data_bank_exporter::set_exported (se::topology_exporter::EXPORT_TOPOLOGY_1E2G);
        }

      if (setup_.has_flag ("export.topology_1e3g"))
        {
          this->base_data_bank_exporter::set_exported (se::topology_exporter::EXPORT_TOPOLOGY_1E3G);
        }

      if (setup_.has_flag ("export.topology_2e1g"))
        {
          this->base_data_bank_exporter::set_exported (se::topology_exporter::EXPORT_TOPOLOGY_2E1G);
        }

      if (setup_.has_flag ("export.topology_2e2g"))
        {
          this->base_data_bank_exporter::set_exported (se::topology_exporter::EXPORT_TOPOLOGY_2E2G);
        }

      if (setup_.has_flag ("export.topology_2e3g"))
        {
          this->base_data_bank_exporter::set_exported (se::topology_exporter::EXPORT_TOPOLOGY_2E3G);
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
      if (bit_ == topology_exporter::EXPORT_TOPOLOGY_1E)   return "topology_1e";
      if (bit_ == topology_exporter::EXPORT_TOPOLOGY_1E1A) return "topology_1e1a";
      if (bit_ == topology_exporter::EXPORT_TOPOLOGY_2E)   return "topology_2e";
      if (bit_ == topology_exporter::EXPORT_TOPOLOGY_1E1P) return "topology_1e1p";
      if (bit_ == topology_exporter::EXPORT_TOPOLOGY_2P)   return "topology_2p";
      if (bit_ == topology_exporter::EXPORT_TOPOLOGY_1E1G) return "topology_1e1g";
      if (bit_ == topology_exporter::EXPORT_TOPOLOGY_1E2G) return "topology_1e2g";
      if (bit_ == topology_exporter::EXPORT_TOPOLOGY_1E3G) return "topology_1e3g";
      if (bit_ == topology_exporter::EXPORT_TOPOLOGY_2E1G) return "topology_2e1g";
      if (bit_ == topology_exporter::EXPORT_TOPOLOGY_2E2G) return "topology_2e2g";
      if (bit_ == topology_exporter::EXPORT_TOPOLOGY_2E3G) return "topology_2e3g";
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

      // const std::string & td_label = base_data_bank_exporter::_bank_labels_[sdm::data_info::default_topology_data_label()];
      const std::string & td_label = base_data_bank_exporter::_bank_labels_["TD"];
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
        // logging not recognized
        // DT_LOG_DEBUG (get_logging_priority (),"Non supported classification '" <<
        //               a_classification << "' for now !" );
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
        // logging not recognized
        // DT_LOG_DEBUG(get_logging_priority(), "Non supported classification '" <<
        //              a_classification << "' for now !");
      } else {
        // logging not recognized
        // DT_LOG_DEBUG(get_logging_priority(), "Non supported classification '" << a_classification << "' !");
      }

      // et_.print (std::clog, "Export topology", "DEVEL: ");
      return 0;
    }

    int topology_exporter::_export_topology_1e (const datatools::things & er_,
                                                se::export_topology & et_)
    {
      const std::string & td_label =
        base_data_bank_exporter::_bank_labels_["TD"];
        // base_data_bank_exporter::_bank_labels_[sdm::data_info::default_topology_data_label()];

      if (! DATATOOLS_THINGS_CHECK_BANK(er_, td_label, sdm::topology_data)) {
        DT_THROW_IF (true, std::logic_error, "Missing topology data to be processed !");
      }
      DATATOOLS_THINGS_CONST_BANK(er_, td_label, sdm::topology_data, TD);

      DT_THROW_IF (! TD.has_pattern(), std::logic_error, "Missing topology data pattern !");

      const snemo::datamodel::topology_1e_pattern & a_1e_pattern
        = dynamic_cast<const snemo::datamodel::topology_1e_pattern &>(TD.get_pattern());

      et_.grab_1e_topology().electron_energy = a_1e_pattern.get_electron_energy();
      et_.grab_1e_topology().electron_angle = a_1e_pattern.get_electron_angle();
      et_.grab_1e_topology().electron_track_length = a_1e_pattern.get_electron_track_length();

      return 0;
    }

    int topology_exporter::_export_topology_1e1a (const datatools::things & er_,
                                                  se::export_topology & et_)
    {
      const std::string & td_label =
        base_data_bank_exporter::_bank_labels_["TD"];
        // base_data_bank_exporter::_bank_labels_[sdm::data_info::default_topology_data_label()];

      if (! DATATOOLS_THINGS_CHECK_BANK(er_, td_label, sdm::topology_data)) {
        DT_THROW_IF (true, std::logic_error, "Missing topology data to be processed !");
      }
      DATATOOLS_THINGS_CONST_BANK(er_, td_label, sdm::topology_data, TD);

      DT_THROW_IF (! TD.has_pattern(), std::logic_error, "Missing topology data pattern !");

      const snemo::datamodel::topology_1e1a_pattern & a_1e1a_pattern
        = dynamic_cast<const snemo::datamodel::topology_1e1a_pattern &>(TD.get_pattern());

      et_.grab_1e1a_topology().electron_energy = a_1e1a_pattern.get_electron_energy();
      et_.grab_1e1a_topology().electron_angle = a_1e1a_pattern.get_electron_angle();
      et_.grab_1e1a_topology().electron_track_length = a_1e1a_pattern.get_electron_track_length();
      et_.grab_1e1a_topology().alpha_angle = a_1e1a_pattern.get_alpha_angle();
      et_.grab_1e1a_topology().alpha_track_length = a_1e1a_pattern.get_alpha_track_length();
      et_.grab_1e1a_topology().electron_alpha_angle = a_1e1a_pattern.get_electron_alpha_angle();
      et_.grab_1e1a_topology().electron_alpha_vertices_probability = a_1e1a_pattern.get_electron_alpha_vertices_probability();
      et_.grab_1e1a_topology().alpha_delayed_time = a_1e1a_pattern.get_alpha_delayed_time();

      return 0;
    }

    int topology_exporter::_export_topology_2e (const datatools::things & er_,
                                                se::export_topology & et_)
    {
      const std::string & td_label =
        base_data_bank_exporter::_bank_labels_["TD"];
        // base_data_bank_exporter::_bank_labels_[sdm::data_info::default_topology_data_label()];

      if (! DATATOOLS_THINGS_CHECK_BANK(er_, td_label, sdm::topology_data)) {
        DT_THROW_IF (true, std::logic_error, "Missing topology data to be processed !");
      }
      DATATOOLS_THINGS_CONST_BANK(er_, td_label, sdm::topology_data, TD);

      DT_THROW_IF (! TD.has_pattern(), std::logic_error, "Missing topology data pattern !");

      const snemo::datamodel::topology_2e_pattern & a_2e_pattern
        = dynamic_cast<const snemo::datamodel::topology_2e_pattern &>(TD.get_pattern());

      et_.grab_2e_topology().electron_minimal_energy = a_2e_pattern.get_electron_minimal_energy();
      et_.grab_2e_topology().electron_maximal_energy = a_2e_pattern.get_electron_maximal_energy();
      et_.grab_2e_topology().electrons_energy_difference = a_2e_pattern.get_electrons_energy_difference();
      et_.grab_2e_topology().electrons_energy_sum = a_2e_pattern.get_electrons_energy_sum();

      // if(a_2e_pattern.get_electrons_energy_sum()>4)
      //   std::cout << "Emin Emax  " << a_2e_pattern.get_electron_minimal_energy() << "  "
      //             << a_2e_pattern.get_electron_maximal_energy() << std::endl;

      et_.grab_2e_topology().electrons_internal_probability = a_2e_pattern.get_electrons_internal_probability();
      et_.grab_2e_topology().electrons_external_probability = a_2e_pattern.get_electrons_external_probability();

      et_.grab_2e_topology().electrons_vertices_probability = a_2e_pattern.get_electrons_vertices_probability();
      et_.grab_2e_topology().electrons_angle = a_2e_pattern.get_electrons_angle();
      et_.grab_2e_topology().electrons_cos_angle = std::cos(a_2e_pattern.get_electrons_angle());

      double length_Emin = datatools::invalid_real();
      if (TD.get_pattern().get_particle_track(a_2e_pattern.get_minimal_energy_electron_name()).has_trajectory()) {
        const snemo::datamodel::tracker_trajectory & a_trajectory =
          TD.get_pattern().get_particle_track(a_2e_pattern.get_minimal_energy_electron_name()).get_trajectory();
        const snemo::datamodel::base_trajectory_pattern & a_track_pattern = a_trajectory.get_pattern();
        length_Emin = a_track_pattern.get_shape().get_length();
      } else {
        DT_THROW_IF(true,std::logic_error,"Electron of minimal energy has no attached trajectory !");
      }
      double length_Emax = datatools::invalid_real();
      if (TD.get_pattern().get_particle_track(a_2e_pattern.get_maximal_energy_electron_name()).has_trajectory()) {
        const snemo::datamodel::tracker_trajectory & a_trajectory =
          TD.get_pattern().get_particle_track(a_2e_pattern.get_maximal_energy_electron_name()).get_trajectory();
        const snemo::datamodel::base_trajectory_pattern & a_track_pattern = a_trajectory.get_pattern();
        length_Emax = a_track_pattern.get_shape().get_length();
      } else {
        DT_THROW_IF(true,std::logic_error,"Electron of maximal energy has no attached trajectory !");
      }

      et_.grab_2e_topology().electron_Emin_track_length = length_Emin;
      et_.grab_2e_topology().electron_Emax_track_length = length_Emax;
      return 0;
    }

    int topology_exporter::_export_topology_1e1p (const datatools::things & er_,
                                                  se::export_topology & et_)
    {
      const std::string & td_label =
        base_data_bank_exporter::_bank_labels_["TD"];
        // base_data_bank_exporter::_bank_labels_[sdm::data_info::default_topology_data_label()];

      if (! DATATOOLS_THINGS_CHECK_BANK(er_, td_label, sdm::topology_data)) {
        DT_THROW_IF (true, std::logic_error, "Missing topology data to be processed !");
      }
      DATATOOLS_THINGS_CONST_BANK(er_, td_label, sdm::topology_data, TD);

      DT_THROW_IF (! TD.has_pattern(), std::logic_error, "Missing topology data pattern !");

      const snemo::datamodel::topology_1e1p_pattern & a_1e1p_pattern
        = dynamic_cast<const snemo::datamodel::topology_1e1p_pattern &>(TD.get_pattern());

      et_.grab_1e1p_topology().electron_energy = a_1e1p_pattern.get_electron_energy();
      et_.grab_1e1p_topology().positron_energy = a_1e1p_pattern.get_positron_energy();
      et_.grab_1e1p_topology().electron_positron_energy_difference = std::abs(a_1e1p_pattern.get_electron_energy()-a_1e1p_pattern.get_positron_energy());
      et_.grab_1e1p_topology().electron_positron_energy_sum = a_1e1p_pattern.get_electron_energy()+a_1e1p_pattern.get_positron_energy();
      et_.grab_1e1p_topology().electron_positron_internal_probability = a_1e1p_pattern.get_electron_positron_internal_probability();
      et_.grab_1e1p_topology().electron_positron_external_probability = a_1e1p_pattern.get_electron_positron_external_probability();
      et_.grab_1e1p_topology().electron_positron_vertices_probability = a_1e1p_pattern.get_electron_positron_vertices_probability();
      et_.grab_1e1p_topology().electron_positron_angle = a_1e1p_pattern.get_electron_positron_angle();
      et_.grab_1e1p_topology().electron_positron_cos_angle = std::cos(a_1e1p_pattern.get_electron_positron_angle());
      et_.grab_1e1p_topology().electron_track_length = a_1e1p_pattern.get_electron_track_length();
      et_.grab_1e1p_topology().positron_track_length = a_1e1p_pattern.get_positron_track_length();

      return 0;
    }

    int topology_exporter::_export_topology_2p (const datatools::things & er_,
                                                se::export_topology & et_)
    {
      const std::string & td_label =
        base_data_bank_exporter::_bank_labels_["TD"];
        // base_data_bank_exporter::_bank_labels_[sdm::data_info::default_topology_data_label()];

      if (! DATATOOLS_THINGS_CHECK_BANK(er_, td_label, sdm::topology_data)) {
        DT_THROW_IF (true, std::logic_error, "Missing topology data to be processed !");
      }
      DATATOOLS_THINGS_CONST_BANK(er_, td_label, sdm::topology_data, TD);

      DT_THROW_IF (! TD.has_pattern(), std::logic_error, "Missing topology data pattern !");

      const snemo::datamodel::topology_2p_pattern & a_2p_pattern
        = dynamic_cast<const snemo::datamodel::topology_2p_pattern &>(TD.get_pattern());

      et_.grab_2p_topology().positron_minimal_energy = a_2p_pattern.get_positron_minimal_energy();
      et_.grab_2p_topology().positron_maximal_energy = a_2p_pattern.get_positron_maximal_energy();
      et_.grab_2p_topology().positrons_energy_difference = a_2p_pattern.get_positrons_energy_difference();
      et_.grab_2p_topology().positrons_energy_sum = a_2p_pattern.get_positrons_energy_sum();

      // if(a_2p_pattern.get_positrons_energy_sum()>4)
      //   std::cout << "Emin Emax  " << a_2p_pattern.get_positron_minimal_energy() << "  "
      //             << a_2p_pattern.get_positron_maximal_energy() << std::endl;

      et_.grab_2p_topology().positrons_internal_probability = a_2p_pattern.get_positrons_internal_probability();
      et_.grab_2p_topology().positrons_external_probability = a_2p_pattern.get_positrons_external_probability();

      et_.grab_2p_topology().positrons_vertices_probability = a_2p_pattern.get_positrons_vertices_probability();
      et_.grab_2p_topology().positrons_angle = a_2p_pattern.get_positrons_angle();
      et_.grab_2p_topology().positrons_cos_angle = std::cos(a_2p_pattern.get_positrons_angle());

      double length_Emin = datatools::invalid_real();
      if (TD.get_pattern().get_particle_track(a_2p_pattern.get_minimal_energy_positron_name()).has_trajectory()) {
        const snemo::datamodel::tracker_trajectory & a_trajectory =
          TD.get_pattern().get_particle_track(a_2p_pattern.get_minimal_energy_positron_name()).get_trajectory();
        const snemo::datamodel::base_trajectory_pattern & a_track_pattern = a_trajectory.get_pattern();
        length_Emin = a_track_pattern.get_shape().get_length();
      } else {
        DT_THROW_IF(true,std::logic_error,"Positron of minimal energy has no attached trajectory !");
      }
      double length_Emax = datatools::invalid_real();
      if (TD.get_pattern().get_particle_track(a_2p_pattern.get_maximal_energy_positron_name()).has_trajectory()) {
        const snemo::datamodel::tracker_trajectory & a_trajectory =
          TD.get_pattern().get_particle_track(a_2p_pattern.get_maximal_energy_positron_name()).get_trajectory();
        const snemo::datamodel::base_trajectory_pattern & a_track_pattern = a_trajectory.get_pattern();
        length_Emax = a_track_pattern.get_shape().get_length();
      } else {
        DT_THROW_IF(true,std::logic_error,"Positron of maximal energy has no attached trajectory !");
      }

      et_.grab_2p_topology().positron_Emin_track_length = length_Emin;
      et_.grab_2p_topology().positron_Emax_track_length = length_Emax;

      return 0;
    }

    int topology_exporter::_export_topology_1e1g (const datatools::things & er_,
                                                  se::export_topology & et_)
    {
      const std::string & td_label =
        base_data_bank_exporter::_bank_labels_["TD"];
        // base_data_bank_exporter::_bank_labels_[sdm::data_info::default_topology_data_label()];

      if (! DATATOOLS_THINGS_CHECK_BANK(er_, td_label, sdm::topology_data)) {
        DT_THROW_IF (true, std::logic_error, "Missing topology data to be processed !");
      }
      DATATOOLS_THINGS_CONST_BANK(er_, td_label, sdm::topology_data, TD);

      DT_THROW_IF (! TD.has_pattern(), std::logic_error, "Missing topology data pattern !");

      const snemo::datamodel::topology_1eNg_pattern & a_1eNg_pattern
        = dynamic_cast<const snemo::datamodel::topology_1eNg_pattern &>(TD.get_pattern());

      et_.grab_1e1g_topology().electron_energy = a_1eNg_pattern.get_electron_energy();
      std::vector<double> energies;
      a_1eNg_pattern.fetch_gammas_energies(energies);
      et_.grab_1e1g_topology().gamma_energy = energies.at(0);
      et_.grab_1e1g_topology().electron_gamma_energy_sum = a_1eNg_pattern.get_electron_energy() + energies.at(0);
      //This choice assumes that the gamma is emitted along with the electron (it does not include events where the gamma can first interact in a block, then with the source to create the electron, and eventually carry on to interact more with the calorimeter)
      std::vector<std::vector<double> > internal_probabilities;
      a_1eNg_pattern.fetch_electron_gammas_internal_probabilities(internal_probabilities);
      et_.grab_1e1g_topology().electron_gamma_internal_probability = internal_probabilities.at(0).front();
      std::vector<std::vector<double> > external_probabilities;
      a_1eNg_pattern.fetch_electron_gammas_external_probabilities(external_probabilities);
      et_.grab_1e1g_topology().electron_gamma_external_probability = external_probabilities.at(0).back();

      return 0;
    }

    int topology_exporter::_export_topology_1e2g (const datatools::things & er_,
                                                  se::export_topology & et_)
    {
      const std::string & td_label =
        base_data_bank_exporter::_bank_labels_["TD"];
        // base_data_bank_exporter::_bank_labels_[sdm::data_info::default_topology_data_label()];

      if (! DATATOOLS_THINGS_CHECK_BANK(er_, td_label, sdm::topology_data)) {
        DT_THROW_IF (true, std::logic_error, "Missing topology data to be processed !");
      }
      DATATOOLS_THINGS_CONST_BANK(er_, td_label, sdm::topology_data, TD);

      DT_THROW_IF (! TD.has_pattern(), std::logic_error, "Missing topology data pattern !");

      const snemo::datamodel::topology_1eNg_pattern & a_1eNg_pattern
        = dynamic_cast<const snemo::datamodel::topology_1eNg_pattern &>(TD.get_pattern());

      return 0;
    }

    int topology_exporter::_export_topology_1e3g (const datatools::things & er_,
                                                  se::export_topology & et_)
    {
      const std::string & td_label =
        base_data_bank_exporter::_bank_labels_["TD"];
        // base_data_bank_exporter::_bank_labels_[sdm::data_info::default_topology_data_label()];

      if (! DATATOOLS_THINGS_CHECK_BANK(er_, td_label, sdm::topology_data)) {
        DT_THROW_IF (true, std::logic_error, "Missing topology data to be processed !");
      }
      DATATOOLS_THINGS_CONST_BANK(er_, td_label, sdm::topology_data, TD);

      DT_THROW_IF (! TD.has_pattern(), std::logic_error, "Missing topology data pattern !");

      const snemo::datamodel::topology_1eNg_pattern & a_1eNg_pattern
        = dynamic_cast<const snemo::datamodel::topology_1eNg_pattern &>(TD.get_pattern());

      return 0;
    }


    int topology_exporter::_export_topology_2e1g (const datatools::things & er_,
                                                  se::export_topology & et_)
    {
      const std::string & td_label =
        base_data_bank_exporter::_bank_labels_["TD"];
        // base_data_bank_exporter::_bank_labels_[sdm::data_info::default_topology_data_label()];

      if (! DATATOOLS_THINGS_CHECK_BANK(er_, td_label, sdm::topology_data)) {
        DT_THROW_IF (true, std::logic_error, "Missing topology data to be processed !");
      }
      DATATOOLS_THINGS_CONST_BANK(er_, td_label, sdm::topology_data, TD);

      DT_THROW_IF (! TD.has_pattern(), std::logic_error, "Missing topology data pattern !");

      const snemo::datamodel::topology_2eNg_pattern & a_2eNg_pattern
        = dynamic_cast<const snemo::datamodel::topology_2eNg_pattern &>(TD.get_pattern());

      return 0;
    }

    int topology_exporter::_export_topology_2e2g (const datatools::things & er_,
                                                  se::export_topology & et_)
    {
      const std::string & td_label =
        base_data_bank_exporter::_bank_labels_["TD"];
      // base_data_bank_exporter::_bank_labels_[sdm::data_info::default_topology_data_label()];

      if (! DATATOOLS_THINGS_CHECK_BANK(er_, td_label, sdm::topology_data)) {
        DT_THROW_IF (true, std::logic_error, "Missing topology data to be processed !");
      }
      DATATOOLS_THINGS_CONST_BANK(er_, td_label, sdm::topology_data, TD);

      DT_THROW_IF (! TD.has_pattern(), std::logic_error, "Missing topology data pattern !");

      const snemo::datamodel::topology_2eNg_pattern & a_2eNg_pattern
        = dynamic_cast<const snemo::datamodel::topology_2eNg_pattern &>(TD.get_pattern());

      return 0;
    }

    int topology_exporter::_export_topology_2e3g (const datatools::things & er_,
                                                  se::export_topology & et_)
    {
      const std::string & td_label =
        base_data_bank_exporter::_bank_labels_["TD"];
        // base_data_bank_exporter::_bank_labels_[sdm::data_info::default_topology_data_label()];

      if (! DATATOOLS_THINGS_CHECK_BANK(er_, td_label, sdm::topology_data)) {
        DT_THROW_IF (true, std::logic_error, "Missing topology data to be processed !");
      }
      DATATOOLS_THINGS_CONST_BANK(er_, td_label, sdm::topology_data, TD);

      DT_THROW_IF (! TD.has_pattern(), std::logic_error, "Missing topology data pattern !");

      const snemo::datamodel::topology_2eNg_pattern & a_2eNg_pattern
        = dynamic_cast<const snemo::datamodel::topology_2eNg_pattern &>(TD.get_pattern());

      return 0;
    }

  } // end of namespace exports

} // end of namespace snemo

// end of topology_exporter.cc
