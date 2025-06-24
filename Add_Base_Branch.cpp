////////////////////////////////////////////
// Adds a Branch with baselines 
// calculated as average of first
// 100 bins
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
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"

void Add_Base_Branch(){
//////////////////////////////////////////////////////////////// SELEZIONE FILE:
//	TFile *f = new TFile("file_out_threshold.root");	// (Primo)	
//	TFile *f = new TFile("data_2022_02_03_09h04.root");	// 3 Feb
	TFile *f = new TFile("data_2022_07_23_09h22.root");	// 23 Lug
////////////////////////////////////////////////////////////////
	
	TTree *fTree = (TTree*)f->Get("tree");
	Int_t nentries = fTree->GetEntries();
	printf("%d\n", nentries);
//     fTree->Print()

	Int_t Nevent;
	Int_t Tank;
	Int_t Trigger;
	Int_t IsUUB;
	Int_t Time[2048];

	Int_t ADC1[2048];
	Int_t ADC2[2048];
	Int_t ADC3[2048];
	Int_t ADC4[2048];
	Int_t ADC5[2048];
	Int_t ADC6[2048];
	Int_t ADC7[2048];
	Int_t ADC8[2048];
	Int_t ADC9[2048];
	Int_t ADC10[2048];
	
	Float_t Arr_baseline_1[nentries];
	Float_t Arr_baseline_2[nentries];
	Float_t Arr_baseline_3[nentries];
	Float_t Arr_baseline_4[nentries];
	Float_t Arr_baseline_5[nentries];
	Float_t Arr_baseline_6[nentries];
	Float_t Arr_baseline_7[nentries];
	Float_t Arr_baseline_8[nentries];
	Float_t Arr_baseline_9[nentries];
	Float_t Arr_baseline_10[nentries];
	
	Float_t baseline_1;
	Float_t baseline_2;
	Float_t baseline_3;
	Float_t baseline_4;
	Float_t baseline_5;
	Float_t baseline_6;
	Float_t baseline_7;
	Float_t baseline_8;
	Float_t baseline_9;
	Float_t baseline_10;
	
	Int_t temp1 = 0;
	Int_t temp2 = 0;
	Int_t temp3 = 0;
	Int_t temp4 = 0;
	Int_t temp5 = 0;
	Int_t temp6 = 0;
	Int_t temp7 = 0;
	Int_t temp8 = 0;
	Int_t temp9 = 0;
	Int_t temp10 = 0;

	fTree->SetBranchAddress("Time",Time);
	fTree->SetBranchAddress("Nevent",&Nevent);
	fTree->SetBranchAddress("trigger",&Trigger);
	fTree->SetBranchAddress("UUB",&IsUUB);
	fTree->SetBranchAddress("Tank",&Tank);
	fTree->SetBranchAddress("ADC1",ADC1);
	fTree->SetBranchAddress("ADC2",ADC2);
	fTree->SetBranchAddress("ADC3",ADC3);
	fTree->SetBranchAddress("ADC4",ADC4);
	fTree->SetBranchAddress("ADC5",ADC5);
	fTree->SetBranchAddress("ADC6",ADC6);
	fTree->SetBranchAddress("ADC7",ADC7);
	fTree->SetBranchAddress("ADC8",ADC8);
	fTree->SetBranchAddress("ADC9",ADC9);
	fTree->SetBranchAddress("ADC10",ADC10);
	
	
	for(Int_t i=0; i<nentries; i++){
		fTree->GetEntry(i);
		
		for(Int_t j=0; j<100; j++){
			temp1 += ADC1[j];
			temp2 += ADC2[j];
			temp3 += ADC3[j];
			temp4 += ADC4[j];
			temp5 += ADC5[j];
			temp6 += ADC6[j];
			temp7 += ADC7[j];
			temp8 += ADC8[j];
			temp9 += ADC9[j];
			temp10 += ADC10[j];
		}
		
		Arr_baseline_1[i]=(float)temp1/100;
		Arr_baseline_2[i]=(float)temp2/100;
		Arr_baseline_3[i]=(float)temp3/100;
		Arr_baseline_4[i]=(float)temp4/100;
		Arr_baseline_5[i]=(float)temp5/100;
		Arr_baseline_6[i]=(float)temp6/100;
		Arr_baseline_7[i]=(float)temp7/100;
		Arr_baseline_8[i]=(float)temp8/100;
		Arr_baseline_9[i]=(float)temp9/100;
		Arr_baseline_10[i]=(float)temp10/100;
		
		temp1=0;
		temp2=0;
		temp3=0;
		temp4=0;
		temp5=0;
		temp6=0;
		temp7=0;
		temp8=0;
		temp9=0;
		temp10=0;
	}
	
//////////////////////////////////////////////////////////////////////////////// SELEZIONE OUTPUT:	
//	TFile *fn = new TFile("file_out_threshold_copy.root","RECREATE");     //
	TFile *fn = new TFile("data_2022_02_03_09h04_copy.root","RECREATE");  //
//	TFile *fn = new TFile("data_2022_07_23_09h22_copy.root","RECREATE");  //
////////////////////////////////////////////////////////////////////////////////

	TTree *fnTree = fTree->CloneTree();
	
	
	TBranch *Base1 = fnTree->Branch("Baseline1",&baseline_1,"baseline_1/F");
	TBranch *Base2 = fnTree->Branch("Baseline2",&baseline_2,"baseline_2/F");
	TBranch *Base3 = fnTree->Branch("Baseline3",&baseline_3,"baseline_3/F");
	TBranch *Base4 = fnTree->Branch("Baseline4",&baseline_4,"baseline_4/F");
	TBranch *Base5 = fnTree->Branch("Baseline5",&baseline_5,"baseline_5/F");
	TBranch *Base6 = fnTree->Branch("Baseline6",&baseline_6,"baseline_6/F");
	TBranch *Base7 = fnTree->Branch("Baseline7",&baseline_7,"baseline_7/F");
	TBranch *Base8 = fnTree->Branch("Baseline8",&baseline_8,"baseline_8/F");
	TBranch *Base9 = fnTree->Branch("Baseline9",&baseline_9,"baseline_9/F");
	TBranch *Base10 = fnTree->Branch("Baseline10",&baseline_10,"baseline_10/F");

	
	for(Int_t i=0; i<nentries; i++){
	
		baseline_1=Arr_baseline_1[i];
		baseline_2=Arr_baseline_2[i];
		baseline_3=Arr_baseline_3[i];
		baseline_4=Arr_baseline_4[i];
		baseline_5=Arr_baseline_5[i];
		baseline_6=Arr_baseline_6[i];
		baseline_7=Arr_baseline_7[i];
		baseline_8=Arr_baseline_8[i];
		baseline_9=Arr_baseline_9[i];
		baseline_10=Arr_baseline_10[i];
					
		Base1->Fill();
		Base2->Fill();
		Base3->Fill();
		Base4->Fill();
		Base5->Fill();
		Base6->Fill();
		Base7->Fill();
		Base8->Fill();
		Base9->Fill();
		Base10->Fill();
	}
	fnTree->Write("",TObject::kOverwrite);
	
	fnTree->Print();
	
	f->Close();
	fn->Close();
}
