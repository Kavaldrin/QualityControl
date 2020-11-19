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
/// \file   TTreeReductor.h
/// \author Piotr Konopka
///
#ifndef QUALITYCONTROL_TTreeReductor_H
#define QUALITYCONTROL_TTreeReductor_H

#include "QualityControl/Reductor.h"

namespace o2::quality_control_modules::ft0
{

/// \brief A Reductor which obtains the most popular characteristics of TH1.
///
/// A Reductor which obtains the most popular characteristics of TH1.
/// It produces a branch in the format: "mean/D:stddev:entries"
class TTreeReductor : public quality_control::postprocessing::Reductor
{
 public:
  TTreeReductor() = default;
  ~TTreeReductor() = default;

  void* getBranchAddress() override;
  const char* getBranchLeafList() override;
  void update(TObject* obj) override;

 private:
  struct {
    Double_t chargeMean;
    Double_t chargeStddev;
    Double_t timestampMean;
    Double_t timestampStddev;
    Double_t chargeEntries;
    Double_t timestampEntries;
  } mStats;
};

} // namespace o2::quality_control_modules::common

#endif //QUALITYCONTROL_TTreeReductor_H
