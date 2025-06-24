////////////////////////////////////////////
// Plots baseline histogram from a file 
// with baselines branch
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
#include <string>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void Base_plot_histo(){
	
	gROOT->Reset();
	
	TFile *f = new TFile("file_out_threshold_copy.root");
	TTree *fTree = (TTree*)f->Get("tree");
	Int_t nentries = fTree->GetEntries();
	printf("%d\n", nentries);
	
	gStyle->SetOptStat("nemr");
	gStyle->SetOptTitle(0);
	gROOT->SetStyle("Plain");
	
	Float_t base1;
	Float_t base2;
	Float_t base3;
	Float_t base4;
	Float_t base5;
	Float_t base6;
	Float_t base7;
	Float_t base8;
	Float_t base9;
	Float_t base10;
	
	Int_t IsUUB;	
	
	fTree->SetBranchAddress("Baseline1",&base1);
	fTree->SetBranchAddress("Baseline2",&base2);
	fTree->SetBranchAddress("Baseline3",&base3);
	fTree->SetBranchAddress("Baseline4",&base4);
	fTree->SetBranchAddress("Baseline5",&base5);
	fTree->SetBranchAddress("Baseline6",&base6);
	fTree->SetBranchAddress("Baseline7",&base7);
	fTree->SetBranchAddress("Baseline8",&base8);
	fTree->SetBranchAddress("Baseline9",&base9);
	fTree->SetBranchAddress("Baseline10",&base10);
	fTree->SetBranchAddress("UUB",&IsUUB);
	
	TH1D* base1_UUB_histo = new TH1D("ADC1 HG UUB","ADC1 HG",50,100,400);
	TH1D* base1_UB_histo = new TH1D("ADC1 HG UB","ADC1 HG",50,0,100);

	TH1D* base2_UUB_histo = new TH1D("ADC1 UUB","ADC1 LG",50,100,400);
	TH1D* base2_UB_histo = new TH1D("ADC1 UB","ADC1 LG",50,0,100);

	TH1D* base3_UUB_histo = new TH1D("ADC2 HG UUB","ADC2 HG",50,100,400);
	TH1D* base3_UB_histo = new TH1D("ADC2 HG UB","ADC2 HG",50,0,100);

	TH1D* base4_UUB_histo = new TH1D("ADC2 UUB","ADC2 LG",50,100,400);
	TH1D* base4_UB_histo = new TH1D("ADC2 UB","ADC2 LG",50,0,100);

	TH1D* base5_UUB_histo = new TH1D("ADC3 HG UUB","ADC3 HG",50,100,400);
	TH1D* base5_UB_histo = new TH1D("ADC3 HG UB","ADC3 HG",50,0,100);

	TH1D* base6_UUB_histo = new TH1D("ADC3 UUB","ADC3 LG",50,100,400);
	TH1D* base6_UB_histo = new TH1D("ADC3 UB","ADC3 LG",50,0,100);

	TH1D* base7_UUB_histo = new TH1D("SSD HG UUB","SSD HG",50,100,400);
	TH1D* base8_UUB_histo = new TH1D("SSD UUB","SSD LG",50,100,400);
	TH1D* base9_UUB_histo = new TH1D("Small PMT UUB","Small",50,100,400);
	
	for (int i=0;i<nentries;i++){
		fTree->GetEntry(i);
		if(IsUUB){
			base1_UUB_histo->Fill(base1);
			base2_UUB_histo->Fill(base2);
	       	base3_UUB_histo->Fill(base3);
	       	base4_UUB_histo->Fill(base4);
	       	base5_UUB_histo->Fill(base5);
	       	base6_UUB_histo->Fill(base6);
	       	base7_UUB_histo->Fill(base7);
	       	base8_UUB_histo->Fill(base8);
	      		base9_UUB_histo->Fill(base9);
		} else {
			base1_UB_histo->Fill(base1);
			base2_UB_histo->Fill(base2);
	       	base3_UB_histo->Fill(base3);
	       	base4_UB_histo->Fill(base4);
	       	base5_UB_histo->Fill(base5);
	       	base6_UB_histo->Fill(base6);
	       }
	}
	
	int fill_style = 3002;

	TList* listUUB = new TList();
	listUUB->Add(base1_UUB_histo);
	listUUB->Add(base2_UUB_histo);
	listUUB->Add(base3_UUB_histo);
	listUUB->Add(base4_UUB_histo);
	listUUB->Add(base5_UUB_histo);
	listUUB->Add(base6_UUB_histo);
	listUUB->Add(base7_UUB_histo);
	listUUB->Add(base8_UUB_histo);
	listUUB->Add(base9_UUB_histo);

	TH1D* base_all_UUB = (TH1D*) base1_UUB_histo->Clone("All UUB");
	base_all_UUB->Reset();
	base_all_UUB->Merge(listUUB);

	TList* listUB = new TList();
	listUB->Add(base1_UB_histo);
	listUB->Add(base2_UB_histo);
	listUB->Add(base3_UB_histo);
	listUB->Add(base4_UB_histo);
	listUB->Add(base5_UB_histo);
	listUB->Add(base6_UB_histo);

	TH1D* base_all_UB = (TH1D*) base1_UB_histo->Clone("All UB");
	base_all_UB->Reset();
	base_all_UB->Merge(listUB);
	
	base_all_UUB->SetFillStyle(fill_style);
	base_all_UB->SetFillStyle(fill_style);
	base_all_UUB->SetFillColor(920);
	base_all_UB->SetFillColor(920);


	base1_UUB_histo->SetFillStyle(fill_style);
	base1_UB_histo->SetFillStyle(fill_style);
	base1_UUB_histo->SetFillColor(616+2);
	base1_UB_histo->SetFillColor(616+2);

	base2_UUB_histo->SetFillStyle(fill_style);
	base2_UB_histo->SetFillStyle(fill_style);
	base2_UUB_histo->SetFillColor(600+2);
	base2_UB_histo->SetFillColor(600+2);

	base3_UUB_histo->SetFillStyle(fill_style);
	base3_UB_histo->SetFillStyle(fill_style);
	base3_UUB_histo->SetFillColor(432+2);
	base3_UB_histo->SetFillColor(432+2);

	base4_UUB_histo->SetFillStyle(fill_style);
	base4_UB_histo->SetFillStyle(fill_style);
	base4_UUB_histo->SetFillColor(416+2);
	base4_UB_histo->SetFillColor(416+2);

	base5_UUB_histo->SetFillStyle(fill_style);
	base5_UB_histo->SetFillStyle(fill_style);
	base5_UUB_histo->SetFillColor(400-4);
	base5_UB_histo->SetFillColor(400-4);

	base6_UUB_histo->SetFillStyle(fill_style);
	base6_UB_histo->SetFillStyle(fill_style);
	base6_UUB_histo->SetFillColor(632+2);
	base6_UB_histo->SetFillColor(632+2);

	base7_UUB_histo->SetFillStyle(fill_style);
	base7_UUB_histo->SetFillColor(800+6);
	base8_UUB_histo->SetFillStyle(fill_style);
	base8_UUB_histo->SetFillColor(860+1);
	base9_UUB_histo->SetFillStyle(fill_style);
	base9_UUB_histo->SetFillColor(820-3);

	TCanvas* canvas1 = new TCanvas("canvas1","Baselines UB",800,600);
	TCanvas* canvas2 = new TCanvas("canvas2","Baselines UUB",800,600);

	canvas2->cd();
	
	base_all_UUB->SetMaximum(7000);
	base_all_UUB->Draw();
	base1_UUB_histo->Draw("same");
	base2_UUB_histo->Draw("same");
	base3_UUB_histo->Draw("same");
	base4_UUB_histo->Draw("same");
	base5_UUB_histo->Draw("same");
	base6_UUB_histo->Draw("same");
	base7_UUB_histo->Draw("same");
	base8_UUB_histo->Draw("same");
	base9_UUB_histo->Draw("same");

	Double_t MeanUUB = base_all_UUB->GetMean();
	Double_t StdUUB = base_all_UUB->GetStdDev();
	
	TLine* meanlineUUB = new TLine(MeanUUB,0,MeanUUB,7000);
	meanlineUUB->SetLineColor(kRed);
	meanlineUUB->Draw("same");
	
	TLine* stdlinepUUB = new TLine(MeanUUB+StdUUB,0,MeanUUB+StdUUB,7000);
	stdlinepUUB->SetLineColor(kCyan);
	stdlinepUUB->Draw("same");
	
	TLine* stdlinemUUB = new TLine(MeanUUB-StdUUB,0,MeanUUB-StdUUB,7000);
	stdlinemUUB->SetLineColor(kCyan);
	stdlinemUUB->Draw("same");
	canvas2->Print();
	
//	canvas2->BuildLegend();
	canvas1->cd();
	
	base_all_UB->SetMaximum(16000);
	base_all_UB->Draw();
	base1_UB_histo->Draw("same");
	base2_UB_histo->Draw("same");
	base3_UB_histo->Draw("same");
	base4_UB_histo->Draw("same");
	base5_UB_histo->Draw("same");
	base6_UB_histo->Draw("same");

	Double_t MeanUB = base_all_UB->GetMean();
	Double_t StdUB = base_all_UB->GetStdDev();
	
	TLine* meanlineUB = new TLine(MeanUB,0,MeanUB,16000);
	meanlineUB->SetLineColor(kRed);
	meanlineUB->Draw("same");
	
	TLine* stdlinepUB = new TLine(MeanUB+StdUB,0,MeanUB+StdUB,16000);
	stdlinepUB->SetLineColor(kCyan);
	stdlinepUB->Draw("same");
	
	TLine* stdlinemUB = new TLine(MeanUB-StdUB,0,MeanUB-StdUB,16000);
	stdlinemUB->SetLineColor(kCyan);
	stdlinemUB->Draw("same");
	
//	canvas1->BuildLegend();
	canvas1->Print();
	
}
