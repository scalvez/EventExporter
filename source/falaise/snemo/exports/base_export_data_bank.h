// -*- mode: c++ ; -*-
/* base_export_data_bank.h
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

#ifndef EXPORTS_BASE_EXPORT_DATA_BANK_H
#define EXPORTS_BASE_EXPORT_DATA_BANK_H 1

#include <string>
#include <vector>
#include <iostream>

#include <boost/cstdint.hpp>
#include <camp/camptype.hpp>
#include <camp/class.hpp>

namespace snemo {

  namespace exports {

    template<class Type>
    void bank_export_version (int32_t & bank_version_)
    {
      bank_version_ = Type::EXPORT_VERSION;
      return;
    }

    template<class Type>
    bool bank_check_export_version (int32_t bank_version_)
    {
      return bank_version_ >= 0 && bank_version_ <= Type::EXPORT_VERSION;
    }

    // template<class Type>
    // const std::string & describe_class ();

    struct constants
    {
      static const int32_t INVALID_ID;
      static const int16_t INVALID_INTEGER16;
      static const int32_t INVALID_INTEGER;
      static const int64_t INVALID_INTEGER64;
      static const double  INVALID_DOUBLE;
      enum calo_block_type
        {
          CALO_TYPE  = 0, // GID has: module/side/column/row
          XCALO_TYPE = 1, // GID has: module/side/wall/column/row
          GVETO_TYPE = 2  // GID has: module/side/wall/column
        };
    };

    // template <class Type>
    // void audit_vector (const std::vector< Type > & v_, int i_)
    // {
    //   // std::clog << "**** AUDIT VECTOR " << typeid(Type).name () << " : \n";
    //   // std::clog << "     Size     : " << v_.size () << "\n";
    //   // std::clog << "     Capacity : " << v_.capacity () << "\n";
    //   // std::clog << "     Index    : " << i_ << "\n";
    //   return;
    // }

    struct base_export_data_bank
    {
    public:
      static const int32_t EXPORT_VERSION = 0;
      base_export_data_bank ();
      virtual ~base_export_data_bank ();
      virtual void reset () = 0;
      virtual void clear_data () = 0;

      virtual void implement_introspection () = 0;
      struct introspection_activator
      {
        introspection_activator ();
      };

      virtual void print (std::ostream & out_ = std::clog,
                  const std::string & title_ = "",
                  const std::string & indent_ = "") const = 0;
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

} // end of namespace snemo

#endif // EXPORTS_EXPORT_DATA_BANK_H

// end of base_export_data_bank.h
