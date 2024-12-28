
#include <TError.h>
#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TGraph.h"


#include <iomanip>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctype.h>
#include <stdio.h>

#include <list>
#include <vector>
#include <map>
using namespace std;








  //--------------------------------- ROOT histogram stuff
  //gErrorIgnoreLevel = kFatal;
  //TFile* hfile = new TFile("process_data.root","RECREATE","histogram file");
  //   TH1F* h = new TH1F("","", , , );
  //TCanvas* canvas1 = new TCanvas("canvas1","sub data",200,10,700,500);
  //gStyle->SetOptStat(110000);    //ksiourmen  // supress leftmost 0s
  //----------------------------------- ROOT histogram stuff



/*
to run, install the CERN ROOT package, then:


kwd1:code20$  root stm.C
   ------------------------------------------------------------------
  | Welcome to ROOT 6.30/08                        https://root.cern |
  | (c) 1995-2024, The ROOT Team; conception: R. Brun, F. Rademakers |
  | Built for linuxx8664gcc on Jul 14 2024, 22:53:16                 |
  | From tags/v6-30-08@v6-30-08                                      |
  | With c++ (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0                   |
  | Try '.help'/'.?', '.demo', '.license', '.credits', '.quit'/'.q'  |
   ------------------------------------------------------------------

root [0] 
Processing stm.C...

 */





class Node{

public:

  string   symbol;                        

  int      input_level;                         // current input level
  int      threshold;                           // threshold to fire

  list< pair<int, Node*> >   branches;

  int      last_cycle;
  
  int touch(int weight, Node* touched_by, int cycle, string* output);

  Node(){last_cycle=-1;threshold=40;input_level=0;}
  
};

int
Node::touch(int input, Node* touched_by, int cycle, string* output){

  
 
  input_level += input;
  
  if (input_level >= threshold){

    //cout<<symbol<<"  "<<cycle<<" "<<last_cycle<<endl;

      if (cycle == last_cycle) return 1;
      last_cycle = cycle;

    // node fires

    *output = *output + symbol;

    //cout<<"here"<<endl;

    input_level = 35;
    
    list< pair<int, Node*> >::iterator b = branches.begin();

    for(;b!=branches.end(); b++){

      if (b->second != touched_by)
	b->second->touch(b->first, this, cycle, output);
    }

    
  }

  return 1;
};



  



void stm()
{


  TCanvas* canvas1 = new TCanvas("canvas1","stm memory demo",200,10,1100,600);
  gStyle->SetOptStat(0000);    //ksiourmen  // supress leftmost 0s

  //TText *t = new TText(.0,.95,"Hello World !");
  TFile* hfile = new TFile("process_data.root","RECREATE","histogram file");

 
  TH2F* htest1  = new TH2F("test1" ,"pass:  a b| a b " ,22 , 5 ,110, 21,0.05,1.15 );
 TH2F* htest1f  = new TH2F("test1f" ,"fail:  a b| a b c  " ,22 , 5 ,110, 21,0.05,1.15 );
 TH2F* htest1fs  = new TH2F("test1fs" ," pass - fail  " ,22 , 5 ,110, 21,0.05,1.15 );


  
    float prob_stm = .40;

    int num_stm=95;

    for(num_stm=10;num_stm<101; num_stm+=10)
      {

	
      
    
	for (prob_stm=.05; prob_stm<1.01; prob_stm+=.1)
      {


  for (int t=0;t!=100;t++){           // 100 tests

    string output;


 

    list<Node*> symbols;
  
    Node a;   a.symbol="a";  symbols.push_back(&a);
    Node b;   b.symbol="b";  symbols.push_back(&b);
    Node c;   c.symbol="c";  symbols.push_back(&c);
    Node c1;   c1.symbol="c";  symbols.push_back(&c1);

     Node c2;   c.symbol="c";  symbols.push_back(&c2);
     Node c3;   c.symbol="c";  symbols.push_back(&c3);
     Node c4;   c.symbol="c";  symbols.push_back(&c4);
     Node c5;   c.symbol="c";  symbols.push_back(&c5);
     Node c6;   c.symbol="c";  symbols.push_back(&c6);
     Node c7;   c.symbol="c";  symbols.push_back(&c7);
     Node c8;   c.symbol="c";  symbols.push_back(&c8);
     Node c9;   c.symbol="c";  symbols.push_back(&c9);



    
    list<Node> stm_nodes;
  
    for (int i = 0; i!= num_stm; i++){

      Node stm; //stm.symbol="s";

      stm_nodes.push_back(stm);

    }

    list<Node*>::iterator l = symbols.begin();

    for (;l!=symbols.end();l++){
  

      list<Node>::iterator s = stm_nodes.begin();

      for (;s!=stm_nodes.end();s++){

	//cout<<(float) rand()/(float)RAND_MAX<<endl;

	if ((float)rand()/(float)RAND_MAX < prob_stm){

	  //cout<<(*l)->symbol <<endl;
	
	  s->branches.push_back(pair<int,Node*>(1, *l));

	  (*l)->branches.push_back(pair<int,Node*>(20, &(*s)));
	}
   
      }

    }
    


  
    /*
    a.touch(50, NULL, 0, &output );
    b.touch(50, NULL, 0, &output );
    a.touch(50, NULL, 1, &output );
    */
    
    a.touch(50, NULL, 0, &output );
    b.touch(50, NULL, 0, &output );
    a.touch(50, NULL, 2, &output );

    cout<<output<<endl;


    int fail =0;
    int pass =0;
      
    if (output.find("c",3)!=string::npos) fail=1;//cout<<"fail"<<endl;

    //if (output.find("b",3)==string::npos) fail=1;//cout<<"fail"<<endl;

    if (output.find("b",3)!=string::npos) pass=1;//cout<<"pass"<<endl;

    if (pass) htest1 ->Fill(num_stm, prob_stm, 1);
    if (fail) htest1f->Fill(num_stm, prob_stm, 1);

    

  }   //test number


      }
      }

    gStyle->SetTitleFontSize(.065);
    htest1->GetXaxis()->SetTitleSize(.045);
    htest1->GetYaxis()->SetTitleSize(.045);
 
  htest1->SetMarkerSize(2);
  htest1->GetXaxis()->SetTitle("# STM nodes"); 
  htest1->GetYaxis()->SetTitle("Prob. of symbol to (stm) connection"); 
 htest1->Draw("text"); canvas1->Update();  canvas1->Print("bica1.pdf(","pdf");  canvas1->Clear();
htest1->UseCurrentStyle();

  htest1f->SetMarkerSize(2);
  htest1f->GetXaxis()->SetTitle("# STM nodes"); 
  htest1f->GetYaxis()->SetTitle("Prob. of symbol to (stm) connection"); 
    htest1f->GetXaxis()->SetTitleSize(.045);
    htest1f->GetYaxis()->SetTitleSize(.045);
 
 htest1f->Draw("text"); canvas1->Update();  canvas1->Print("bica1.pdf(","pdf");  canvas1->Clear();
htest1f->UseCurrentStyle();
 
   htest1fs->GetXaxis()->SetTitleSize(.045);
    htest1fs->GetYaxis()->SetTitleSize(.045);
 
   htest1fs->SetMarkerSize(2);
  htest1fs->GetXaxis()->SetTitle("# STM nodes"); 
  htest1fs->GetYaxis()->SetTitle("Prob. of symbol to (stm) connection"); 
 htest1fs->Add(htest1,1);
 htest1fs->Add(htest1f,-1);
  htest1fs->Draw("text"); canvas1->Update();  canvas1->Print("bica1.pdf(","pdf");  canvas1->Clear();
htest1f->UseCurrentStyle();
 
  //----------------
  canvas1->Print("bica1.pdf)","pdf");  canvas1->Clear();
  //hfile->Write();   // write histogram file
  //----------------




}



 




