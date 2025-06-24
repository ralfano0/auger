////////////////////////////////////////////
// Adds a Branch with maximum values 
// of the trace around its minimum
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
#include "TMath.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"
#include "TMath.h"
#include "TAttFill.h"
#include "TLine.h"

void Add_Max_Branch(){


/////////////////////////////////////////////////////////////////////////////// SELEZIONE FILE:
//	TFile *f = new TFile("file_out_threshold_unsel.root","READ");    	// (Non selezionati)
	TFile *f = new TFile("file_out_threshold_sel_tr.root","READ");		// (Primo)	
//	TFile *f = new TFile("data_2022_02_03_09h04_sel_tr.root","READ");	// 3 Feb	
//	TFile *f = new TFile("data_2022_02_03_09h04_unsel.root","READ");	// 3 Feb
//	TFile *f = new TFile("data_2022_07_23_09h22_sel_tr.root","READ");	// 23 Lug
//	TFile *f = new TFile("data_2022_07_23_09h22_unsel.root","READ");	// 23 Lug
///////////////////////////////////////////////////////////////////////////////
	
	
////////////////////////////////////////////////// DICHIARAZIONE VARIABILI	
	TTree *fTree = (TTree*)f->Get("tree");
	Int_t nentries = fTree->GetEntries();
	printf("%d\n", nentries);
//     fTree->Print()

	int fill_style = 3002;
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
	
	Float_t Arr_max_1[nentries];
	Float_t Arr_max_2[nentries];
	Float_t Arr_max_3[nentries];
	
	Int_t max_1;
	Int_t max_2;
	Int_t max_3;
	
	Int_t temp1 = 0;
	Int_t temp2 = 0;
	Int_t temp3 = 0;
	Int_t temp4 = 0;
	Int_t temp5 = 0;
	Int_t temp6 = 0;

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
	
	Int_t min_index1;
	Int_t min_index2;
	Int_t min_index3;

	
	for(Int_t i=0; i<nentries; i++){
		fTree->GetEntry(i);
		if(IsUUB){
		
			min_index1 = TMath::LocMin(2048-40,ADC1);
			min_index2 = TMath::LocMin(2048-40,ADC3);
			min_index3 = TMath::LocMin(2048-40,ADC5);
			
			if(min_index1<40) min_index1=40;
			if(min_index2<40) min_index2=40;
			if(min_index3<40) min_index3=40;
			
/*			cout << "locmin1: " << min_index1 << endl;
			cout << "locmin2: " << min_index2 << endl;
			cout << "locmin3: " << min_index3 << endl;
*/			
			Int_t *temp_adc1 = ADC1 + min_index1 -40;
			Int_t *temp_adc2 = ADC3 + min_index2 -40;
			Int_t *temp_adc3 = ADC5 + min_index3 -40;
			
			Arr_max_1[i] = TMath::MaxElement(80,temp_adc1);
			Arr_max_2[i] = TMath::MaxElement(80,temp_adc2);
			Arr_max_3[i] = TMath::MaxElement(80,temp_adc3);
		} else {
			
			min_index1 = TMath::LocMin(750-13,ADC2);
			min_index2 = TMath::LocMin(750-13,ADC4);
			min_index3 = TMath::LocMin(750-13,ADC6);
			
			if(min_index1<13) min_index1=13;
			if(min_index2<13) min_index2=13;
			if(min_index3<13) min_index3=13;
			
/*			cout << "locmin1: " << min_index1 << endl;
			cout << "locmin2: " << min_index2 << endl;
			cout << "locmin3: " << min_index3 << endl;
*/			
			Int_t *temp_adc1 = ADC2 + min_index1 -13;
			Int_t *temp_adc2 = ADC4 + min_index2 -13;
			Int_t *temp_adc3 = ADC6 + min_index3 -13;
			
			Arr_max_1[i] = TMath::MaxElement(26,temp_adc1);
			Arr_max_2[i] = TMath::MaxElement(26,temp_adc2);
			Arr_max_3[i] = TMath::MaxElement(26,temp_adc3);
		}
	}
	
	
	gROOT->SetStyle("Plain");
   	gStyle->SetOptStat("nemr");
//   	gStyle->SetOptTitle(0);
//////////////////////////////////////////////////////////////////////////////////// SELEZIONE OUTPUT:
//	TFile *fn = new TFile("file_out_threshold_unsel_add.root","RECREATE");    //
	TFile *fn = new TFile("file_out_threshold_sel_add.root","RECREATE");      //
//	TFile *fn = new TFile("data_2022_02_03_09h04_sel_add.root","RECREATE");   //
//	TFile *fn = new TFile("data_2022_02_03_09h04_unsel_add.root","RECREATE"); //
//	TFile *fn = new TFile("data_2022_07_23_09h22_sel_add.root","RECREATE");   //
//	TFile *fn = new TFile("data_2022_07_23_09h22_unsel_add.root","RECREATE"); //
////////////////////////////////////////////////////////////////////////////////////

	TTree *fnTree = fTree->CloneTree();
	
	
	TBranch *Max1 = fnTree->Branch("max1",&max_1,"max_1/I");
	TBranch *Max2 = fnTree->Branch("max2",&max_2,"max_2/I");
	TBranch *Max3 = fnTree->Branch("max3",&max_3,"max_3/I");

	
	for(Int_t i=0; i<nentries; i++){
	
		max_1 = Arr_max_1[i];
		max_2 = Arr_max_2[i];
		max_3 = Arr_max_3[i];
		
		Max1->Fill();
		Max2->Fill();
		Max3->Fill();
	}
	
	fnTree->Write("",TObject::kOverwrite);
	
//	fnTree->Print();
	
	TH1D* UUB_HG = new TH1D("UUB_HG","26/01",4096,0,2);
	fnTree->Draw("max1*2/4096>>UUB_HG","UUB==1","goff");
	fnTree->Draw("max2*2/4096>>+UUB_HG","UUB==1","goff");
	fnTree->Draw("max3*2/4096>>+UUB_HG","UUB==1","goff");
	
		
	TH1D* UB_HG = new TH1D("UB_HG","26/01",1024,0,2);
	fnTree->Draw("max1*2/1024>>UB_HG","UUB==0","goff");
	fnTree->Draw("max2*2/1024>>+UB_HG","UUB==0","goff");
	fnTree->Draw("max3*2/1024>>+UB_HG","UUB==0","goff");
	
	
	UB_HG->ResetStats();
	UUB_HG->ResetStats();	
	
//	TH1D* UB_HG = (TH1D*)gDirectory->Get("UB_HG");
	cout	<< "UB Mean: " << UB_HG->GetMean()
		<< "	RMS: "<< UB_HG->GetRMS() << endl;
//	TH1D* UUB_HG = (TH1D*)gDirectory->Get("UUB_HG");
	cout	<< "UUB Mean: " << UUB_HG->GetMean()
		<< "	RMS: "<< UUB_HG->GetRMS() << endl;
	//////// DRAW OPT
	TCanvas* canvas_p1 = new TCanvas("All_Amp_2601","UUB",800,600);
	canvas_p1->cd();
	canvas_p1->SetLogy();

	UUB_HG->SetLineColorAlpha(kOrange+2,0.5);
	UUB_HG->SetLineWidth(2);
//	UUB_HG->SetFillStyle(fill_style);


	////////
//	TCanvas* canvas_p2 = new TCanvas("UB_Add","UB",800,600);
//	canvas_p2->cd();
//	canvas_p2->SetLogy();

	UB_HG->SetLineColorAlpha(kAzure-7,0.5);
	UB_HG->SetLineWidth(2);
//	UB_HG->SetFillStyle(fill_style);
	UB_HG->GetXaxis()->SetTitle("Amplitude [V]");	
	UB_HG->Scale(1./UB_HG->Integral(0,1024));
//	UB_HG->Scale(1./UB_HG->GetEntries());
	UB_HG->SetMinimum(1E-4);
	UB_HG->SetMaximum(1E-1);

	UB_HG->GetXaxis()->SetRangeUser(0,0.701);
	UUB_HG->GetXaxis()->SetRangeUser(0,0.701);
	
	
	UB_HG->Draw("HIST");
	canvas_p1->Update();
	UUB_HG->GetXaxis()->SetTitle("Amplitude [V]");	
	UUB_HG->Scale(1./UUB_HG->Integral(0,4096));
//	UUB_HG->Scale(1./UUB_HG->GetEntries());
	UUB_HG->SetMaximum(1E-1);
	UUB_HG->SetMinimum(1E-4);
	UUB_HG->Draw("HIST sames");
	
	TLegend* legend_UUB_p = new TLegend(0.55,0.85,0.7,0.9);
	legend_UUB_p->AddEntry(UUB_HG, "UUB");
	legend_UUB_p->Draw();
	TLegend* legend_UB_p = new TLegend(0.55,0.80,0.7,0.85);
	legend_UB_p->AddEntry(UB_HG, "UB");
	legend_UB_p->Draw();
	
	
	Double_t x_csbt = 0.2513;
	Double_t x_ctot = 0.1345;
	
	TLine *csbt_UUB = new TLine(x_csbt,1E-4,x_csbt,1E-1);
	TLine *ctot_UUB = new TLine(x_ctot,1E-4,x_ctot,1E-1);

	ctot_UUB->SetLineColor(kGreen+1);
	csbt_UUB->SetLineColor(kRed);
	
	csbt_UUB->SetVertical();
	ctot_UUB->SetVertical();
	

	TLegend* leg_csbt_UUB = new TLegend(0.55,0.75,0.7,0.8);
	leg_csbt_UUB->AddEntry(csbt_UUB, "SB UUB");
	leg_csbt_UUB->Draw();
	

	TLegend* leg_ctot_UUB = new TLegend(0.55,0.7,0.7,0.75);
	leg_ctot_UUB->AddEntry(ctot_UUB, "TOT UUB");
	leg_ctot_UUB->Draw();
	
	ctot_UUB->Draw();
	csbt_UUB->Draw();
	
	
	canvas_p1->Update();
//	canvas_p2->Print();
	canvas_p1->Update();
//	canvas_p1->Close();
//	canvas_p2->Close();
	canvas_p1->Print();

}
