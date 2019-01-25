// $Id: EventAction.hh 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.hh
/// \brief Definition of the EventAction class
//

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include <fstream>
#include "TFile.h"
#include "TTree.h"

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    
  private:
    TFile* file;
    TTree* tree;
    double tempEnergy;
    int    tempId;

};

#endif
