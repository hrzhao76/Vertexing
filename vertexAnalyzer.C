/*
Simple macro showing how to access vertex information, and tracks associated to vertices.
Computes vertex reconstruction efficiencies, merging, fake and duplicate rates.
The input file needs to be produced with cards/CMS_PhaseII/testVertexing.tcl

root -l examples/vertexAnalyzer.C'("delphes_output.root")'
*/

#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "include/classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#endif

//------------------------------------------------------------------------------

void vertexAnalyzer(const char *inputFile)
{
  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();

  // Get pointers to branches used in this analysis
  TClonesArray *branchParticle = treeReader->UseBranch("Particle");
  TClonesArray *branchGenVtx = treeReader->UseBranch("AllVertices");
  
  TClonesArray *branchTrack = treeReader->UseBranch("Track");

  Vertex *bestgenvtx, *bestvtx, *vtx, *recovtx;

  Track *track;
  GenParticle *particle;

  TObject *object;


  Double_t distance;
  // Loop over all events
  for(Int_t entry = 0; entry < 1; ++entry)
  {
    //cout<<"------------- New event --------------------  "<<endl;
    //cout<<"  "<<endl;
    //cout<<" Reconstructed vertices: "<<branchGenVtx->GetEntriesFast()<<endl;

    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);


    // If event contains at least 1 genvtx
    // for(Int_t i = 0; i < branchGenVtx->GetEntriesFast(); ++i)
    for(Int_t i = 0; i < 3; ++i)

    {

      // Take vtx
      vtx = (Vertex*) branchGenVtx->At(i);
      //cout<<"gen vertex, Sumpt2: "<<vtx->SumPT2<<", Z: "<<vtx->Z<<", T:"<<vtx->T<<endl;
      cout<< "The number of Constituents of vertex " << i << ": is "  << vtx->Constituents.GetEntriesFast() << endl; 
      // Loop over gen vertex attached tracks
      for(Int_t j = 0; j < vtx->Constituents.GetEntriesFast(); ++j)
      {
        object = vtx->Constituents.At(j);
        
        // Check if the constituent is accessible
        if(object == 0) {
          cout << "nullptr" <<endl;
          continue;
        }
        
        if(object->IsA() == GenParticle::Class())
        {
          particle = (GenParticle*) object;
          cout << "    GenPart " << j << " pt: " << particle->PT << ", z: " << particle->Z << ", t: " << particle->T <<", PID: "<<particle->PID<<", Status: "<<particle->Status<<", PU: "<<particle->IsPU<<endl;

        }
        


      }


    }
  }
}

