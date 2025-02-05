// SPDX-FileCopyrightText: 2021 CERN
// SPDX-License-Identifier: Apache-2.0

#ifndef EXAMPLE16_H
#define EXAMPLE16_H

struct G4HepEmState;

// Data structures for scoring. The accessors must make sure to use atomic operations if needed.
struct GlobalScoring {
  double energyDeposit;
  // Not int to avoid overflows for more than 100,000 events; unsigned long long
  // is the only other data type available for atomicAdd().
  unsigned long long chargedSteps;
  unsigned long long neutralSteps;
  unsigned long long hits;
  unsigned long long numGammas;
  unsigned long long numElectrons;
  unsigned long long numPositrons;
  // Not used on the device, filled in by the host.
  unsigned long long numKilled;
};

struct ScoringPerVolume {
  double *energyDeposit;
  double *chargedTrackLength;
};

// Interface between C++ and CUDA.
void example16(int numParticles, double energy, int batch, const int *MCCindex, ScoringPerVolume *scoringPerVolume,
               GlobalScoring *globalScoring, int numVolumes, int numPlaced, G4HepEmState *state, bool rotatingParticleGun);

#endif
