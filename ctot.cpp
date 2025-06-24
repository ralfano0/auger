////////////////////////////////////////////
// Plots time over threshold 
// histogram from a file 
//
// 
// Author: Roberto Alfano
////////////////////////////////////////////
/*
 * Copyright (c) 2025, Roberto Alfano
 * Licensed under the Creative Commons Attribution-NonCommercial 4.0 International License.
 * See: https://creativecommons.org/licenses/by-nc/4.0/
 */
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

void ctot(){
	
//////////////////////////////////////////////////////////////////////// SELEZIONE FILE:
//	TFile *f = new TFile("file_out_threshold_sel_add.root");	// (Primo)	
	TFile *f = new TFile("data_2022_02_03_09h04_sel_add.root");	// 3 Feb
///////////////////////////////////////////////////////////////////////

	TTree *fTree = (TTree*)f->Get("tree");
	Int_t nentries = fTree->GetEntries();
	printf("%d\n", nentries);
	
	TH1D* TOT = new TH1D("TOT","03/02",4096,0,2);
	
	fTree->Draw("(ctot_threshold1)*2/4096>>TOT","UUB==1");
	fTree->Draw("(ctot_threshold2)*2/4096>>+TOT","UUB==1");
	fTree->Draw("(ctot_threshold3)*2/4096>>+TOT","UUB==1");
	
	TCanvas* trigLight = new TCanvas("trigLightTOT0302","Lightning trigger time over threshold");
	TOT->SetLineWidth(2);
	TOT->SetLineColor(kOrange+2);
	
	trigLight->cd();
	
	TOT->ResetStats();
	
	TOT->Draw("HIST");
	trigLight->SetLogy();
	
	TOT->GetXaxis()->SetTitle("ADC [V]");	
	TOT->Scale(1./TOT->Integral(0,4096));
	TOT->SetMaximum(1E-1);
	TOT->SetMinimum(1E-4);

	TOT->GetXaxis()->SetRangeUser(0.1,0.18);
	
	TLegend* legend_UUB_p = new TLegend(0.55,0.85,0.7,0.9);
	legend_UUB_p->AddEntry(TOT, "UUB");
	legend_UUB_p->Draw();
	
	trigLight->Update();
	trigLight->Print();
}
