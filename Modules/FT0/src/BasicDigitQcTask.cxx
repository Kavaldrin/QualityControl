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
/// \file   BasicDigitQcTask.cxx
/// \author Milosz Filus
///

#include "TCanvas.h"
#include "TH1.h"
#include "TFile.h"
#include "TGraph.h"

#include "QualityControl/QcInfoLogger.h"
#include "FT0/BasicDigitQcTask.h"
#include "FT0/Utilities.h"
#include "DataFormatsFT0/Digit.h"
#include "DataFormatsFT0/ChannelData.h"
#include <Framework/InputRecord.h>

namespace o2::quality_control_modules::ft0
{

BasicDigitQcTask::~BasicDigitQcTask()
{
}

void BasicDigitQcTask::initialize(o2::framework::InitContext& /*ctx*/)
{
  ILOG(Info, Support) << "initialize BasicDigitQcTask" << ENDM; // QcInfoLogger is used. FairMQ logs will go to there as well.

  mChargeHistogram = std::make_unique<TH1F>("Charge", "Charge", 200, 0, 200);
  getObjectsManager()->startPublishing(mChargeHistogram.get());
}

void BasicDigitQcTask::startOfActivity(Activity& activity)
{
  ILOG(Info, Support) << "startOfActivity" << activity.mId << ENDM;
  mChargeHistogram->Reset();
}

void BasicDigitQcTask::startOfCycle()
{
  mChargeHistogram->Reset();
  ILOG(Info, Support) << "startOfCycle" << ENDM;
}

void BasicDigitQcTask::monitorData(o2::framework::ProcessingContext& ctx)
{

//  mChargeHistogram->Reset();
  auto channels = ctx.inputs().get<gsl::span<o2::ft0::ChannelData>>("channels");
  auto digits = ctx.inputs().get<gsl::span<o2::ft0::Digit>>("digits");

  std::vector<o2::ft0::ChannelData> channelDataCopy(channels.begin(), channels.end());
  std::vector<o2::ft0::Digit> digitDataCopy(digits.begin(), digits.end());

  for (auto& digit : digits) {
    auto currentChannels = digit.getBunchChannelData(channels);

    for (auto& channel : currentChannels) {
      mChargeHistogram->Fill(channel.QTCAmpl);
    }
  }
}

void BasicDigitQcTask::endOfCycle()
{
  ILOG(Info, Support) << "endOfCycle" << ENDM;
}

void BasicDigitQcTask::endOfActivity(Activity& /*activity*/)
{
  ILOG(Info, Support) << "endOfActivity" << ENDM;
}

void BasicDigitQcTask::reset()
{
  // clean all the monitor objects here

  mChargeHistogram->Reset();
}

} // namespace o2::quality_control_modules::ft0
