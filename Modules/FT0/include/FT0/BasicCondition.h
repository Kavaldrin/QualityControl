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
/// \file   BasicCondition.h
/// \author Milosz Filus
///

#ifndef QC_MODULE_FT0_BasicCondition_H
#define QC_MODULE_FT0_BasicCondition_H

#include "QualityControl/TaskInterface.h"
#include <DataSampling/DataSamplingCondition.h>

namespace o2::quality_control_modules::ft0
{

/// \brief Example of custom Data Sampling Condition for FT0 detector
/// \author Milosz Filus

/// \brief Just to present how to define custom condition to data dispatcher
class BasicCondition : public o2::utilities::DataSamplingCondition
{
 public:
  /// \brief Constructor.
  BasicCondition() = default;
  /// \brief Default destructor
  ~BasicCondition() override = default;

  void configure(const boost::property_tree::ptree& config) override;
  bool decide(const o2::framework::DataRef& dataRef) override;

 private:
  uint16_t m_minEvents = 0;
};

} // namespace o2::quality_control_modules::ft0

#endif //QC_MODULE_FT0_BasicCondition_H
