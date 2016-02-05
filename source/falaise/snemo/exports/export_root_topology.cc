// -*- mode: c++ ; -*-
/* export_root_topology.cc */

#include <falaise/snemo/exports/export_root_topology.h>
#include <falaise/snemo/exports/topology_exporter.h>
#include <falaise/snemo/exports/base_data_bank_exporter.h>

#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

#include <limits>

#include <TTree.h>

namespace snemo {

    namespace exports {

      export_root_topology::export_root_topology ()
      {
        _store_bits_ = 0;
        return;
      }

      export_root_topology::~export_root_topology ()
      {
        _branch_manager_.reset ();
        _store_bits_ = 0;
        return;
      }

      void export_root_topology::construct (unsigned int store_bits_,
                                            const std::map<std::string,int> topics_,
                                            unsigned int store_version_)
      {
        _store_bits_ = store_bits_;

        for (std::map<std::string,int>::const_iterator i = topics_.begin();
             i != topics_.end();
             i++)
          {
            _branch_manager_.add_topic(i->first, i->second);
          }

        // EXPORT_TOPOLOGY_2E :
        if (_store_bits_ & topology_exporter::EXPORT_TOPOLOGY_2E)
          {
            // "bank" to change with "topology"
            std::string bank_description;
            int32_t bank_version;
            bank_description = "topology_2e";
            bank_export_version<topology_2e>(bank_version);
            _branch_manager_.init_bank_from_camp ("2e",
                                                  topology_exporter::EXPORT_TOPOLOGY_2E,
                                                  bank_version,
                                                  bank_description,
                                                  branch_entry_type::SCALAR_DATA);
          }

        return;
      }

      void export_root_topology::detach_branches ()
      {
        branch_manager::bi_col_type & bis = _branch_manager_.grab_branch_infos ();
        for (size_t i = 0; i < bis.size (); i++)
          {
            branch_entry_type & bi = *(bis[i]);
            bi.detach_branch ();
          }
        return;
      }

      void export_root_topology::setup_tree (TTree * tree_)
      {
        DT_LOG_TRACE (get_logging_priority (), "Entering...");
        if (is_debug())
          {
            DT_LOG_DEBUG (get_logging_priority (), "Export ROOT topology");
            print ();
          }
        branch_manager::bi_col_type & bis = _branch_manager_.grab_branch_infos ();
        for (size_t i = 0; i < bis.size (); i++)
          {
            branch_entry_type & bi = *(bis[i]);
            if (bi.is_activated ())
              {
                bi.make_branch (tree_);
              }
          }
        DT_LOG_TRACE (get_logging_priority (), "Exiting.");
        return;
      }

      void export_root_topology::print (std::ostream & out_,
                                        const std::string & title_,
                                        const std::string & indent_) const
      {

        if (! title_.empty ())
          {
            out_ << indent_ << title_ << ": \n";
          }
        const branch_manager::bi_col_type & bis = _branch_manager_.get_branch_infos ();
        for (size_t i = 0; i < bis.size (); i++)
          {
            std::string tag = "|-- ";
            std::string tag2 = "|   ";
            if (i+1 == bis.size ())
              {
                tag = "`-- ";
                tag2 = "    ";
              }
            const branch_entry_type & bi = *(bis[i]);
            out_ << indent_ << tag
                 << "Branch '" << bi.get_name () << "'\n";
            std::ostringstream indent_oss;
            indent_oss << indent_ << tag2;
            bi.print (out_, "", indent_oss.str ());
          }
        return;
      }

      void export_root_topology::fill_branch_memory (branch_entry_type & branch_info_)
      {
        DT_LOG_TRACE (get_logging_priority (), "Entering...");
        const std::string & bi_name = branch_info_.get_name ();
        if (branch_info_.is_inhibited ())
          {
            DT_LOG_TRACE (get_logging_priority (), "Branch '" << bi_name << " is inhibited ! Exiting.");
            return;
          }
        if (boost::ends_with (bi_name, "@version"))
          {
            DT_LOG_TRACE (get_logging_priority (), "Branch '" << bi_name << "' doesn't need filling ! Exiting.");
            return;
          }
        const camp::Class & topology_class = camp::classByName ("export_topology");
        const export_topology & ET = static_cast<const export_topology &>(*this);
        camp::UserObject proxyET (ET);
        if (boost::ends_with (bi_name, "@size"))
          {
            DT_LOG_TRACE (get_logging_priority (), "Branch '" << bi_name << "' is the size of a data array !");
            camp::Value bankSizeVal = topology_class.property(bi_name).get (proxyET);
            DT_LOG_TRACE (get_logging_priority (), "Set array size '" << bankSizeVal << "'");
            branch_info_.set_branch_value (bankSizeVal);
            DT_LOG_TRACE (get_logging_priority (), "Exiting.");
            return;
          }
        const std::string & branch_parent_name = branch_info_.get_parent_name ();
        DT_THROW_IF (! topology_class.hasProperty (branch_parent_name), std::logic_error,
                     "Cannot find parent for branch '" << bi_name
                     << "' as a property named '" << branch_parent_name << "' !");
        if (get_logging_priority () >= datatools::logger::PRIO_TRACE)
          {
            DT_LOG_TRACE (get_logging_priority (), "Go branch '" << bi_name << "'...");
            branch_info_.print (std::clog);
          }
        const bool array = branch_info_.is_array ();
        const camp::Property & propParent = topology_class.property(branch_parent_name);
        if (array)
          {
            // Check if the parent property is an empty array :
            if ((dynamic_cast<const camp::ArrayProperty &>(propParent)).size (proxyET) == 0)
              {
                DT_LOG_TRACE (get_logging_priority (), "Array branch '" << bi_name << "' has no element ! Exiting.");
                return;
              }
          }
        camp::Value parentVal = propParent.get (proxyET);
        if (get_logging_priority () >= datatools::logger::PRIO_TRACE)
          {
            DT_LOG_TRACE (get_logging_priority (), "Go branch '" << bi_name << "'...");
            branch_info_.print (std::clog);
          }
        camp::UserObject proxyParent = parentVal.to<camp::UserObject>();
        if (array)
          {
            // Array data :
            DT_LOG_TRACE (get_logging_priority (), "This is the array branch '" << bi_name << "'...");
            const std::string & propName = branch_info_.get_leaf_name ();
            DT_LOG_TRACE (get_logging_priority (), "Property name : '" << propName << "'");
            const camp::Class & parent_class = proxyParent.getClass();
            DT_LOG_TRACE (get_logging_priority (), "Parent class name is '" << parent_class.name () << "'.");

            unsigned int array_size = 0;
            if (branch_info_.is_array_fixed_size ())
              {
                array_size = branch_info_.get_array_fixed_size ();
              }
            else
              {
                const std::string & size_prop_name = branch_info_.get_array_size_name ();
                std::ostringstream getter_func_oss;
                getter_func_oss << branch_parent_name << "@get";
                std::string getter_func_name = getter_func_oss.str ();
                DT_THROW_IF (! topology_class.hasProperty (size_prop_name), std::logic_error,
                             "Cannot find size leaf named '" << size_prop_name << "' for branch '" << bi_name
                             << "' as a property of class '" << topology_class.name () << "' !");
                camp::Value arraySizeVal = topology_class.property(size_prop_name).get (proxyET);
                DT_LOG_TRACE (get_logging_priority (), "Array size '" << arraySizeVal << "'.");
                array_size = arraySizeVal.to<unsigned int> ();
                for (size_t i = 0; i < array_size; i++)
                  {
                    DT_THROW_IF (! topology_class.hasFunction (getter_func_name), std::logic_error,
                                 "Cannot find getter function named '" << getter_func_name << "' for branch '" << bi_name
                                 << "' as a function of class '" << topology_class.name () << "' !");
                    const camp::Function & getterFunc = topology_class.function (getter_func_name);
                    camp::Value objVal =  getterFunc.call (proxyET, camp::Args (i));
                    camp::UserObject obj = objVal.to<camp::UserObject>();
                    camp::Value leafVal = parent_class.property(propName).get (obj);
                    DT_LOG_TRACE (get_logging_priority (),
                                  "Branch '" << bi_name << "' : setting array [" << i << "] value ("
                                  << leafVal << ")");
                    branch_info_.set_branch_value (leafVal, i);
                  }
              }
            DT_LOG_TRACE (get_logging_priority (), "Array size is : '" << array_size << "'.");
          }
        else
          {
            // Non-array data :
            DT_LOG_TRACE (get_logging_priority (), "Not an array branch...");
            const std::string & propName = branch_info_.get_leaf_name ();
            DT_LOG_TRACE (get_logging_priority (), "Property name : '" << propName << "'");
            const camp::Class & parent_class = proxyParent.getClass();
            DT_THROW_IF (! parent_class.hasProperty (propName), std::logic_error,
                         "Cannot find leaf named '" << propName << "' for branch '" << bi_name
                         << "' as a property of class '" << parent_class.name () << "' !");;
            DT_LOG_TRACE (get_logging_priority (), "Found property '" << propName << "' in class '" << parent_class.name () << "'.");
            camp::Value leafVal = parent_class.property(propName).get (proxyParent);
            DT_LOG_TRACE (get_logging_priority (), "Branch '" << bi_name << "' : setting scalar value ("
                          << leafVal << ")");
            branch_info_.set_branch_value (leafVal);
          }

        DT_LOG_TRACE (get_logging_priority (), "Exiting.");
       return;
      }

      void export_root_topology::fill_memory ()
      {

        const export_topology & ET = static_cast<const export_topology &>(*this);
        camp::UserObject proxyET (ET);

        // Loop on branch infos:
        for (branch_manager::bi_col_type::iterator bi_iter
               = _branch_manager_.grab_branch_infos ().begin ();
             bi_iter != _branch_manager_.grab_branch_infos ().end ();
             bi_iter++)
          {
            branch_entry_type & bi = **bi_iter;
            DT_LOG_TRACE (get_logging_priority (), "Branch name = " << bi.get_name ());
            // Check if this branch is stored :
            if (! (bi.get_store_bit () & _store_bits_))
              {
                DT_LOG_TRACE (get_logging_priority (), "Branch '" << bi.get_name () << "' is not stored !");
                continue;
              }
            fill_branch_memory (bi);
          }
        return;
      }

    }  // end of namespace exports

}  // end of namespace snemo

/* end of export_root_topology.cc */
