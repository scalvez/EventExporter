// -*- : c++ ; -*-
/* base_export_data_bank.cc */

#include <falaise/snemo/exports/base_export_data_bank.h>
#include <falaise/snemo/exports/base_data_bank_exporter.h>

#include <sstream>
#include <limits>

namespace snemo {

  namespace exports {

    const int32_t constants::INVALID_ID        = -1;
    const int16_t constants::INVALID_INTEGER16 = -1;
    const int32_t constants::INVALID_INTEGER   = -1;
    const int64_t constants::INVALID_INTEGER64 = -1;
    const double  constants::INVALID_DOUBLE    = std::numeric_limits<double>::quiet_NaN ();


    /***********************************************/

    base_export_data_bank::base_export_data_bank ()
    {
      // static bool activated = false;
      // if (! activated)
      //   {
      //     implement_introspection ();
      //     activated = true;
      //   }
      return;
    }

    base_export_data_bank::~base_export_data_bank ()
    {
      return;
    }

  }  // end of namespace exports

}  // end of namespace snemo

/* end of export_event.cc */
