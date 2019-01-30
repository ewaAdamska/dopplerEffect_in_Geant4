//
// $Id: PrimaryGeneratorAction.hh 15.10.2018 A Fijalkowska, edited by E. Adamska $
//
/// \file PrimaryGeneratorAction.hh
/// \brief Definition of the PrimaryGeneratorAction class

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4GeneralParticleSource.hh"
#include "G4LorentzVector.hh"


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);

  private:
	void SetUpDefault();	
    G4ParticleGun* particleGun;
    G4ParticleTable* particleTable;
    void GenerateGammaIncident(G4Event* anEvent);
    G4ThreeVector GenerateIsotropicDirection(G4double randomPhi);
    G4double GeneratePropagationAngle();
    G4double CalculateDopplerEffect(G4double energy, G4double randomPhi, G4double beta);

    G4LorentzVector LorentzTransformation(G4ThreeVector momentum, G4double energy, G4double beta);

};


#endif 

