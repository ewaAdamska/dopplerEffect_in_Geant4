//
// $Id: DetectorConstruction.cc 12.16.2016 A. Fijalkowska $
//
/// \file DetectorConstruction.cc
/// \brief DetectorConstruction class
//
//
#include "DetectorConstruction.hh"
#include "G4PVPlacement.hh" //tworzenie physical volume
#include "G4SystemOfUnits.hh" //jednostki
#include "G4VisAttributes.hh" //sposob wyświetlania, kolory itp
#include "G4Material.hh" //materiały
#include "G4Box.hh" //prostopadłościan
#include "G4Tubs.hh" //walec
#include "G4ThreeVector.hh" //trzyelementowy wektor wbudowany w geant
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4UnitsTable.hh"

DetectorConstruction::DetectorConstruction()
{
    worldLogic = 0L;
    LaBrLogic = 0L;
    man = G4NistManager::Instance();

}



DetectorConstruction::~DetectorConstruction() {}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    ConstructLaBrDetector();

    return worldPhys;
}


G4VPhysicalVolume* DetectorConstruction::ConstructWorld()
{

    G4double worldX = 0.5*m;
    G4double worldY = 0.5*m;
    G4double worldZ = 0.5*m;
    G4Material* vaccum = new G4Material("GalacticVacuum", 1., 1.01*g/mole,
                           CLHEP::universe_mean_density, 
                           kStateGas, 3.e-18*pascal, 2.73*kelvin);
  
    G4Box* worldSolid = new G4Box("worldSolid",worldX,worldY,worldZ);
    worldLogic = new G4LogicalVolume(worldSolid, vaccum,"worldLogic", 0,0,0);
                                             
    //worldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "world", 0, false, 0);
    return worldPhys;

}


void DetectorConstruction::ConstructLaBrDetector() {
    G4String name, symbol;
    G4double a, density;
    G4int z, ncomponents;
    G4UnitDefinition::BuildUnitsTable();

    a=139.*g/mole;
    G4Element* lanthanum = new G4Element(name="Lanthanum", symbol="La", z=57,  a);
    a=79.*g/mole;
    G4Element* boromine  = new G4Element(name="Boromine", symbol="Br", z=35,  a);

    G4int natoms;
    G4Material* LaBrMixture = new G4Material("LaBrMixture", density=5.06*g/cm3, ncomponents=2);


    //G4Material *testMaterial = man->FindOrBuildMaterial("G4_SODIUM_IODIDE"); // well known material for first tests

    LaBrMixture -> AddElement(lanthanum,  natoms=1);
    LaBrMixture -> AddElement(boromine,  natoms=3);

    //geometry parameters
    G4double rMin = 0;
    G4double rMax = 2 * cm;
    G4double height = 6 * cm;
    G4double phiMin = 0 * deg;
    G4double phiMax = 360 * deg;

    G4Tubs *LaBrShape = new G4Tubs("LaBrColid", rMin, rMax, height / 2., phiMin, phiMax);

    LaBrLogic = new G4LogicalVolume(LaBrShape, LaBrMixture, "LaBrLogic");

    G4VisAttributes *LaBrVisAtt = new G4VisAttributes(G4Colour(0.117, 0.564, 1));
    LaBrVisAtt->SetForceAuxEdgeVisible(true);
    LaBrVisAtt->SetForceSolid(true);
    LaBrLogic->SetVisAttributes(LaBrVisAtt);


    G4double radius = 10. * cm;
    int nrOfDets = 10;
    for(int i = 0; i!= nrOfDets; ++i)
    {
        G4double theta = i * 360.*deg/nrOfDets;
        G4ThreeVector pos(radius*sin(theta), radius*cos(theta), 0);
        G4RotationMatrix* rot = new G4RotationMatrix();
        rot->rotateZ(theta);
        rot->rotateX(90*deg);
        new G4PVPlacement(rot, pos, LaBrLogic, "LaBrPhys", worldLogic, 0, i);

    }//

//    G4RotationMatrix* rotation = new G4RotationMatrix;
//    G4RotationMatrix* rotation2 = new G4RotationMatrix;
//    rotation -> rotateX(90*deg);
//    new G4PVPlacement(rotation, placeFirst, LaBrLogic, "LaBrPhys", worldLogic, 0, 0);

}


	
void DetectorConstruction::ConstructSDandField()
{
    G4MultiFunctionalDetector* detector = new G4MultiFunctionalDetector("LaBrSensitiveDet");
    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    SDmanager->AddNewDetector(detector);
    LaBrLogic->SetSensitiveDetector(detector);
    G4VPrimitiveScorer* energyDepScorer = new G4PSEnergyDeposit("eDep",0);
    detector->RegisterPrimitive(energyDepScorer);

}



