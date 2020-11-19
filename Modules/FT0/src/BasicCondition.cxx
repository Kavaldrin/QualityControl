// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

///
/// \file   BasicCondition.cxx
/// \author Milosz Filus
///

#include "FT0/BasicCondition.h"
#include <boost/property_tree/ptree.hpp>
#include "DataFormatsFT0/Digit.h"
#include "Headers/DataHeader.h"

namespace o2::quality_control_modules::ft0
{

void BasicCondition::configure(const boost::property_tree::ptree& config)
{
  m_minEvents = config.get<uint16_t>("minEvents");
}

bool BasicCondition::decide(const o2::framework::DataRef& dataRef)
{
  // const auto* header = o2::header::get<o2::header::DataHeader*>(dataRef.header);
  
  // ILOG(Info, Support) << "[data description: ]" << header->dataDescription << ENDM; 



  ILOG(Info, Support) << "[decide]" << ENDM;
  return true;
}

} // namespace o2::quality_control_modules::example
