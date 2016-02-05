/*
 * Author (s) :
 Francois Mauger <mauger@lpccaen.in2p3.fr>
 Xavier Garrido  <garrido@lal.in2p3.fr>
 Steven Calvez   <calvez@lal.in2p3.fr>
 * Creation date: 2016-02-04
 * Last modified: 2016-02-04
 */

#ifndef EXPORTS_LOGGABLE_SUPPORT_H_
#define EXPORTS_LOGGABLE_SUPPORT_H_ 1

#include <datatools/logger.h>

namespace datatools {
  class properties;
}

namespace snemo {

    namespace exports {

      class loggable_support {

      public:

        loggable_support();

        explicit loggable_support(datatools::logger::priority);

        datatools::logger::priority get_logging_priority() const;

        void set_logging_priority(const std::string & priority_label_);

        void set_logging_priority(datatools::logger::priority);

        bool is_debug () const;

        void set_debug (bool);

        bool is_verbose () const;

        void set_verbose (bool);

      protected:

        void _initialize_logging_support(const datatools::properties &);

      protected:

        datatools::logger::priority _logging_priority; //!< Logging priority threshold

      };

    } // end of namespace exports

} // end of namespace snemo

#endif //EXPORTS_LOGGABLE_SUPPORT_H_

// end of track_history.h
/*
** Local Variables: --
** mode: c++ --
** c-file-style: "gnu" --
** End: --
*/
