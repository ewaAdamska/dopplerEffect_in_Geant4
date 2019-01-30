
// $Id: PrimaryGeneratorAction.cc 15.10.2018 A Fijalkowska, edited by E. Adamska $
//
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "Randomize.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4LorentzVector.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
    particleGun = new G4ParticleGun();
    particleTable = G4ParticleTable::GetParticleTable();

    SetUpDefault();
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::SetUpDefault()
{

	G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
	particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
	particleGun->SetParticleEnergy(500.0*keV);

}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    GenerateGammaIncident(anEvent);
}	

void PrimaryGeneratorAction::GenerateGammaIncident(G4Event* anEvent)
{
    //1. wybieranie kwantu gamma
	G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
	particleGun->SetParticleDefinition(particle);
    //2. wysyłanie ze środka
    particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));

    //3. energia i efekt Dopplera
    G4double randomPhi = GeneratePropagationAngle();
    G4double beta = 0.02;
    G4double gammaEnergy = 3000*keV;

    // otrzymuję czterowektor lorentza po transofrmacji
    G4LorentzVector SecondaryVector = LorentzTransformation(GenerateIsotropicDirection(randomPhi), gammaEnergy, beta);



    G4double energyFromDetectorPointOfRefrence = SecondaryVector.e();

    particleGun->SetParticleEnergy(energyFromDetectorPointOfRefrence);

    //4. izotropowo

    G4ThreeVector secondaryDirection = G4ThreeVector(SecondaryVector.x(), SecondaryVector.y(), SecondaryVector.z());
    particleGun->SetParticleMomentumDirection(secondaryDirection);

    //5. wyślij tą cząstkę
    particleGun->GeneratePrimaryVertex(anEvent);
}


G4double PrimaryGeneratorAction::GeneratePropagationAngle()
{
    //kąt pommiędzy kierunkiem ruchu jonu a propagacją gammy
    return  G4UniformRand()*2.*M_PI;

}

G4double PrimaryGeneratorAction::CalculateDopplerEffect(G4double energy, G4double phi, G4double beta)
{   //implementacja efektu dopplera
    G4double energyInDetector;

    energyInDetector = energy*(sqrt(1-beta*beta)/(1-beta*cos(phi)));
//    std::cout<<energyInDetector<<std::endl; //test

    return  energyInDetector;

}

G4ThreeVector PrimaryGeneratorAction::GenerateIsotropicDirection(G4double randomPhi)
{
   //G4double randomPhi = G4UniformRand()*2.*M_PI;
   G4double randomCosTheta = G4UniformRand()*2. - 1.;
   G4double randomTheta = acos(randomCosTheta);

//  // test
//   randomPhi=30*deg;

   G4double x = sin(randomTheta)*sin(randomPhi);
   G4double y = sin(randomTheta)*cos(randomPhi);
   G4double z = cos(randomTheta);


    return G4ThreeVector(x, y,z);
}

G4LorentzVector PrimaryGeneratorAction::LorentzTransformation(G4ThreeVector momentum, G4double energy, G4double beta)
{
    G4LorentzVector PrimaryVector = G4LorentzVector();

    PrimaryVector.setPx(energy*momentum.getX());
    PrimaryVector.setPy(energy*momentum.getY());
    PrimaryVector.setPx(energy*momentum.getZ());
    PrimaryVector.setE(energy);

    G4LorentzVector SecondaryVector = PrimaryVector.boostY(beta);

    return PrimaryVector;

}



