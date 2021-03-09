#######################################
# Order of execution of various modules
#######################################

set ExecutionPath {
  PileUpMerger
  ParticlePropagator

  TrackMerger
  TreeWriter
}


###############
# PileUp Merger
###############

module PileUpMerger PileUpMerger {
  set InputArray Delphes/stableParticles

  set ParticleOutputArray stableParticles
  set VertexOutputArray vertices

  # pre-generated minbias input file
  set PileUpFile MinBias.pileup

  # average expected pile up
  set MeanPileUp 50

   # maximum spread in the beam direction in m
  set ZVertexSpread 0.25

  # maximum spread in time in s
  set TVertexSpread 800E-12

  # vertex smearing formula f(z,t) (z,t need to be respectively given in m,s)
  set VertexDistributionFormula {exp(-(t^2/160e-12^2/2))*exp(-(z^2/0.053^2/2))}


}

#################################
# Propagate particles in cylinder
#################################

module ParticlePropagator ParticlePropagator {
  set InputArray PileUpMerger/stableParticles

  set OutputArray stableParticles
  set ChargedHadronOutputArray chargedHadrons
  set ElectronOutputArray electrons
  set MuonOutputArray muons

  # radius of the magnetic field coverage, in m
  set Radius 1.29
  # half-length of the magnetic field coverage, in m
  set HalfLength 3.0

  # magnetic field
  set Bz 3.8
}


##############
# Track merger
##############

module Merger TrackMerger {
# add InputArray InputArray

  add InputArray ParticlePropagator/chargedHadrons
  add InputArray ParticlePropagator/electrons
  add InputArray ParticlePropagator/muons
  set OutputArray tracks
}


##################
# ROOT tree writer
##################

module TreeWriter TreeWriter {
#  add Branch InputArray BranchName BranchClass
  add Branch Delphes/allParticles Delphes_AllParticles GenParticle
  add Branch Delphes/stableParticles Delphes_StableParticles GenParticle

  add Branch PileUpMerger/vertices PU_Vertex Vertex
  add Branch PileUpMerger/stableParticles PU_StableParticles GenParticle
  add Branch TrackMerger/tracks Tracks Track
  #add Branch Delphes/ Tracks Track
}

