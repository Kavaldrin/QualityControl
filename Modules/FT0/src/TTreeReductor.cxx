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
/// \file   TTreeReductor.cxx
/// \author Piotr Konopka
///

#include <TH1.h>
#include <TTree.h>
#include "FT0/TTreeReductor.h"
#include "FT0/Utilities.h"
#include "QualityControl/QcInfoLogger.h"

namespace o2::quality_control_modules::ft0
{

void* TTreeReductor::getBranchAddress()
{
  return &mStats;
}

const char* TTreeReductor::getBranchLeafList()
{
  return "chargeMean/D:chargeStddev:timestampMean:timestampStddev:chargeEntries:timestampEntries";
}

void TTreeReductor::update(TObject* obj)
{

  auto tree = dynamic_cast<TTree*>(obj);
  if(tree)
  {
    EventWithChannelData event, *pEvent = &event;

    tree->SetBranchAddress("EventWithChannelData", &pEvent);
    auto chargeHisto = std::make_unique<TH1F>("chargeHistogram", "chargeHistogram", 200, 0, 200);
    auto timestampHisto = std::make_unique<TH1F>("timestampHistogram", "timestampHistogram", 200, 0, 200);
    
    for(unsigned int i = 0; i < tree->GetEntries(); ++i){
        
        tree->GetEntry(i);
        for(auto& channel : event.getChannels()){
          chargeHisto->Fill(channel.QTCAmpl);
        }
        timestampHisto->Fill(event.getTimestamp());
    }


    mStats.chargeMean = chargeHisto->GetMean();
    mStats.chargeStddev = chargeHisto->GetStdDev();
    mStats.timestampMean = timestampHisto->GetMean();
    mStats.timestampStddev = timestampHisto->GetStdDev();
    mStats.chargeEntries = chargeHisto->GetEntries();
    mStats.timestampEntries = timestampHisto->GetEntries();



  }

  
}

} // namespace o2::quality_control_modules::common
