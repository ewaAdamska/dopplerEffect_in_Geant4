
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska, edited by E. Adamska  $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"



EventAction::EventAction()
{
    file = new TFile("output.root", "recreate");
    tree = new TTree("tree", "tree");
    tree->Branch("energy",&tempEnergy);
    tree->Branch("id",&tempId);

}
 
EventAction::~EventAction()
{
    file->Write();
    file->Close();
    delete file;
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
    //trzyma wszystkie kolekcje hitów
    G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
    if(!hitsCollOfThisEvent)
        return;

    int eventId = anEvent-> GetEventID();
    //
    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    G4int LaBrCollId = SDmanager->GetCollectionID("LaBrSensitiveDet/eDep");

    //wyciągamy mapę depozytów energii
    G4THitsMap<G4double>* LaBrEnDep = dynamic_cast <G4THitsMap<G4double>* >
    (hitsCollOfThisEvent->GetHC(LaBrCollId));

    G4double energyDeposit(0);

    for (int i=0; i<=7; i++)
    {
        //std::cout<<"test"<<i<<std::endl;
        if((*LaBrEnDep)[i] != 0L)
        {
            tempEnergy =*((*LaBrEnDep)[i])/keV;
            tempId = i;

            tree->Fill();
        }
    }




}



