////////////////////////////////////////////
// Plots simple threshold 
// histogram from a file 
//
// 
// Author: Roberto Alfano
////////////////////////////////////////////

#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TH1.h"
#include "TList.h"
#include "TLine.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"
#include "TMath.h"
#include <string>
#include <stdio.h>
#include <iostream>

void csbt(){
	
//////////////////////////////////////////////////////////////////////// SELEZIONE FILE:
//	TFile *f = new TFile("file_out_threshold_sel_add.root");	// (Primo)	
	TFile *f = new TFile("data_2022_02_03_09h04_sel_add.root");	// 3 Feb
///////////////////////////////////////////////////////////////////////

	TTree *fTree = (TTree*)f->Get("tree");
	Int_t nentries = fTree->GetEntries();
	printf("%d\n", nentries);
	
	TH1D* ST = new TH1D("ST","03/02",4096,0.,2);
	
	fTree->Draw("(csbt_threshold1)*2/4096>>ST","UUB==1");
	fTree->Draw("(csbt_threshold2)*2/4096>>+ST","UUB==1");
	fTree->Draw("(csbt_threshold3)*2/4096>>+ST","UUB==1");
	
	TCanvas* trigLight = new TCanvas("trigLightSB0302","Lightning trigger simple threshold");
	ST->SetLineWidth(2);
	ST->SetLineColor(kOrange+2);
	
	trigLight->cd();
	
	ST->ResetStats();
	
	ST->Draw("HIST");
	trigLight->SetLogy();
	
	ST->GetXaxis()->SetTitle("ADC [V]");	
	ST->Scale(1./ST->Integral(0,4096));
	ST->SetMaximum(1E-1);
	ST->SetMinimum(1E-4);
	
	ST->GetXaxis()->SetRangeUser(0.1,0.4);
	
	TLegend* legend_UUB_p = new TLegend(0.55,0.85,0.7,0.9);
	legend_UUB_p->AddEntry(ST, "UUB");
	legend_UUB_p->Draw();
	
	trigLight->Update();
	trigLight->Print();
}
