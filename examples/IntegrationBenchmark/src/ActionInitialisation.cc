// SPDX-FileCopyrightText: 2022 CERN
// SPDX-License-Identifier: Apache-2.0
//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
#include "ActionInitialisation.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include "TrackingAction.hh"
#include "SteppingAction.hh"
#include <AdePT/benchmarking/TestManager.h>

ActionInitialisation::ActionInitialisation(G4String aOutputDirectory, G4String aOutputFilename, bool aDoBenchmark,
                                           bool aDoValidation)
    : G4VUserActionInitialization(), fOutputDirectory(aOutputDirectory), fOutputFilename(aOutputFilename),
      fDoBenchmark(aDoBenchmark), fDoValidation(aDoValidation)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialisation::~ActionInitialisation() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialisation::BuildForMaster() const
{
  new PrimaryGeneratorAction();
  SetUserAction(new RunAction(fOutputDirectory, fOutputFilename, fDoBenchmark, fDoValidation));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialisation::Build() const
{
  SetUserAction(new PrimaryGeneratorAction());
  SetUserAction(new EventAction());
  RunAction *aRunAction = new RunAction(fOutputDirectory, fOutputFilename, fDoBenchmark, fDoValidation);
  SetUserAction(aRunAction);
  TrackingAction *aTrackingAction = new TrackingAction();
  SetUserAction(aTrackingAction);

  SteppingAction *aSteppingAction = new SteppingAction(aTrackingAction, fDoBenchmark);
  SetUserAction(aSteppingAction);
  aTrackingAction->setSteppingAction(aSteppingAction);
}
