/*
Simple macro showing how to access vertex information, and tracks associated to vertices.
Computes vertex reconstruction efficiencies, merging, fake and duplicate rates.
The input file needs to be produced with cards/CMS_PhaseII/testVertexing.tcl
root -l examples/vertexAnalyzer.C'("delphes_output.root")'
*/

#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#endif

//------------------------------------------------------------------------------

void dumpVertex(const char *inputFile)
{
  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  std::cout << "number Of Entries  " << numberOfEntries << std::endl;

  // Get pointers to branches used in this analysis

  TClonesArray *branchVtx = treeReader->UseBranch("Vertex");
  TClonesArray *branchParticle = treeReader->UseBranch("Particle");
  Vertex *vtx;
  GenParticle *particle;
  TObject *object;

  // Loop over all events
  // for (Int_t entry = 0; entry < numberOfEntries; ++entry)
  for (Int_t entry = 0; entry < 1; ++entry)
  {
    treeReader->ReadEntry(entry);
    cout << "------------- Event " << entry << "--------------------  " << endl;
    cout << "Number of primary vertices: " << branchVtx->GetEntriesFast() << endl;
    cout << "Number of stable particles: " << branchParticle->GetEntriesFast() << endl;

    cout << "  " << endl;

    // Loop over all particles

    cout << "Event " << entry << " Particles info " << endl;
    cout << fixed << setprecision(5) << setw(15)
         << "Index" << "\t" << "PID" << "\t" << "Status" << "\t" << "IsPU" << "\t"
         << "M1" << "\t" << "M2" << "\t" << "D1" << "\t" << "D2" << "\t"
         << "Charge" << "\t" << "Mass" << "\t" << "E" << "\t"
         << "Px" << "\t" << "Py" << "\t" << "Pz" << "\t"
         << "Vtx" << "\t" << "Vty" << "\t" << "Vtz" << "\t" << "Vtt" << "\t"
         << endl;

    // for (Int_t i = 0; i < branchParticle->GetEntriesFast(); ++i)
    for (Int_t i = 0; i < 50; ++i)

    {
      particle = (GenParticle*) branchParticle->At(i);
      cout << fixed << setprecision(5) << setw(10)
           << i << "\t" << particle->PID << "\t" << particle->Status << "\t" << particle->IsPU << "\t"
           << particle->M1 << "\t" << particle->M2 << "\t" << particle->D1 << "\t" << particle->D2 << "\t"
           << particle->Charge << "\t" << particle->Mass << "\t" << particle->E << "\t"
           << particle->Px << "\t" << particle->Py << "\t" << particle->Pz << "\t"
           << particle->X << "\t" << particle->Y << "\t" << particle->Z << "\t" << particle->T << "\t"
           << endl;

    }

    // Loop over all vertices
    // for (Int_t i = 0; i < branchVtx->GetEntriesFast(); ++i)
    // for (Int_t i = branchVtx->GetEntriesFast() - 1 ; i < branchVtx->GetEntriesFast(); ++i)
    for (Int_t i = 0; i < 5;  ++i)
    {
      vtx = (Vertex*) branchVtx->At(i);

      cout << "Event " << entry << " Vertex " << i << endl;
      cout << fixed << setprecision(5) << setw(5)
           << "Index" << "\t" << "vtx_t" << "\t" << "vtx_x" << "\t" << "vtx_y" << "\t" << "vtx_z" << "\t"
           << endl;

      cout << fixed << setprecision(5) << setw(5)
           <<     i    << "\t" << vtx->T << "\t" << vtx->X << "\t" << vtx->Y << "\t" << vtx->Z
           << endl;
    }

    //   // Loop over gen vertex attached tracks
    //   for (Int_t j = 0; j < vtx->Constituents.GetEntriesFast(); ++j)
    //   {
    //     // cout << "Number of Constituents" << vtx->Constituents.GetEntriesFast() << endl;
    //     // cout << vtx->Constituents.At(j)->IsA() << endl;
    //     // object = vtx->Constituents.At(j);
    //     cout << vtx->Constituents.At(j) << endl;
    //     // // Check if the constituent is accessible
    //     // if (object == 0) continue;

    //     // if (object->IsA() == GenParticle::Class())
    //     // {
    //     //   particle = (GenParticle*) object;
    //     //   cout << "    GenPart pt: " << particle->PT << ", z: " << particle->Z << ", t: " << particle->T << ", PID: " << particle->PID << ", Status: " << particle->Status << ", PU: " << particle->IsPU << endl;

    //     //   if (particle->IsPU == 0)
    //     //     cout << particle->IsPU;
    //     // }

    //   }




  } // end event loop

}
