// SPDX-FileCopyrightText: 2023 CERN
// SPDX-License-Identifier: Apache-2.0
//
#ifndef PARTICLEGUN_HH
#define PARTICLEGUN_HH

#include "G4ParticleGun.hh"
#include "G4VPrimaryGenerator.hh"
#include "G4Event.hh"

class ParticleGunMessenger;

class ParticleGun : public G4ParticleGun {
public:
  ParticleGun();
  ~ParticleGun();
  virtual void GeneratePrimaries(G4Event *) final;
  void GenerateRandomPrimaryVertex(G4Event *aEvent, G4double aMinPhi, G4double aMaxPhi, G4double aMinTheta,
                                   G4double aMaxTheta, std::vector<G4ParticleDefinition *> *aParticleList,
                                   std::vector<float> *aParticleWeights, std::vector<float> *aParticleEnergies);
  void Print();
  void PrintPrimaries(G4Event *aEvent) const;
  void SetHepMC() { fUseHepMC = true; }
  void SetDefaultKinematic();
  void SetRandomizeGun(G4bool val) { fRandomizeGun = val; }
  void AddParticle(G4ParticleDefinition *val, float weight = -1, double energy = -1);
  void SetMinPhi(G4double val) { fMinPhi = val; }
  void SetMaxPhi(G4double val) { fMaxPhi = val; }
  void SetMinTheta(G4double val) { fMinTheta = val; }
  void SetMaxTheta(G4double val) { fMaxTheta = val; }
  void SetPrintGun(G4double val) { fPrintGun = val; }
  /** @brief Checks that the user-provided weights sum to 1 or less, distributes the remaining weight
   * among the particles with undefined weight.
   */
  void ReWeight();

private:
  G4double fPrintGun;
  // Gun randomization
  bool fRandomizeGun;
  std::vector<G4ParticleDefinition *> *fParticleList;
  std::vector<float> *fParticleWeights;
  std::vector<float> *fParticleEnergies;
  bool fInitializationDone;
  G4double fMinPhi;
  G4double fMaxPhi;
  G4double fMinTheta;
  G4double fMaxTheta;

  // HepMC3 reader
  G4VPrimaryGenerator *fHepmcAscii;
  G4bool fUseHepMC;

  ParticleGunMessenger *fMessenger;
};

#endif /* PARTICLEGUN_HH */