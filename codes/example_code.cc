//The header file provides access to FastJet functions
#include "fastjet/ClusterSequence.hh" 
#include <iostream>

//All FastJet objects exist in the following namespace
using namespace fastjet;
using namespace std;

int main () {
    vector<PseudoJet> particles;|\label{line:A}|
    //a particle event with three particles:
    //                                  px    py   pz     E
    particles.push_back( PseudoJet(   99.0,  0.1,  0, 100.0) );
    particles.push_back( PseudoJet(    4.0, -0.1,  0,   5.0) );
    particles.push_back( PseudoJet(  -99.0,    0,  0,  99.0) );
    // all of which are stored in a vector as pseudojets|\label{line:B}|

    // choose a jet definition|\label{line:C}|
    double R = 0.7;
    JetDefinition jet_def(antikt_algorithm, R);

    // run the clustering, extract the jets
    ClusterSequence cs(particles, jet_def);
    // The result of the clustering is stored again in a vector of Pseudojet 
    //after some filtering to get rid of very low energy paricles takes place
    vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());|\label{line:D}|
}