/////////////////////////////////////////////////
// Utilizzato per scorrere fra le tracce
// di un tree root. Il file deve avere
// una branch con baseline e una con i massimi
////////////////////////////////////////////////

#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TH1.h"
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

void Trace_next(){

	gROOT->Reset();
	gStyle->SetOptStat(0);
	
///////////////////////////////////////////////////////////////////////////////	SELEZIONE FILE:
//	TFile *f = new TFile("file_out_threshold_unsel_add.root","READ");    //	(primo non sel)
//	TFile *f = new TFile("file_out_threshold_sel_add.root","READ");	//	(Primo)	
	TFile *f = new TFile("data_2022_02_03_09h04_sel_under.root","READ");	//	3 Feb	
//	TFile *f = new TFile("data_2022_02_03_09h04_unsel_under.root","READ");	//	3 Feb non sel
//	TFile *f = new TFile("data_2022_07_23_09h22_sel_add.root","READ");	//	23 Lug
//	TFile *f = new TFile("data_2022_07_23_09h22_unsel_add.root","READ");	//	23 Lug non sel
///////////////////////////////////////////////////////////////////////////////
	
	
////////////////////////////////////////////////// DICHIARAZIONE VARIABILI	
	TTree *fTree = (TTree*)f->Get("tree");
	Int_t nentries = fTree->GetEntries();
	printf("%d\n", nentries);

	Int_t nevent;
	Int_t tank;
	
	Float_t base1;
	Float_t temp_base1;
	
	Float_t base2;
	Float_t temp_base2;
	
	Float_t base3;
	Float_t temp_base3;
	
	Float_t base4;
	Float_t temp_base4;
	
	Float_t base5;
	Float_t temp_base5;
	
	Float_t base6;
	Float_t temp_base6;
	
	Float_t base7;
	Float_t temp_base7;
	
	Float_t base8;
	Float_t temp_base8;
	
	Float_t base9;
	Float_t temp_base9;
	
	Float_t base10;
	Float_t temp_base10;
	
	Int_t IsUUB;
	Int_t UUB_flag;
	
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
	
	Int_t max1 = 0;  
	Int_t max2 = 0;
	Int_t max3 = 0;
	
	fTree->SetBranchAddress("Nevent",&nevent);
	fTree->SetBranchAddress("Tank",&tank);
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
	fTree->SetBranchAddress("max1",&max1);
	fTree->SetBranchAddress("max2",&max2);
	fTree->SetBranchAddress("max3",&max3);
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
	
	string sel_ev_str;
	Int_t sel_ev;
	
	string sel_tank_str;
	Int_t sel_tank;
	
	string cut;
	int count = 0;
	int an = 0;
/////////////////////////////////////////////////////////////////// CANVAS
	TCanvas* canvas = new TCanvas("canvas","canvas",900,700);
	canvas->Divide(2,5,0.005,0.005);
///////////////////////////////////////////////////////////////////
	
////////////////////////////////////////////////////////////////////////// INDICE PER ITERARE IN ORDINE DI MASSIMO
	Int_t MX[nentries];						   // PRENDE IL MASSIMO DI TUTTE LE TRACCE
									   // E ORDINA IN BASE AL PIÙ GRANDE DEI TRE
	Float_t scale_fact;

	for(Int_t i = 0; i<nentries; i++){
	
		fTree->GetEntry(i);
		
		if(IsUUB) scale_fact = 2./4096; 
		else scale_fact = 2./1024;
		
		if (max1*scale_fact >= max2*scale_fact) {
		
			if (max1 >= max3) MX[i] = max1*scale_fact;
			else MX[i] = max3*scale_fact;  
				
	   	} else {
	   	
			if (max2*scale_fact*scale_fact >= max3) MX[i] = max2*scale_fact;
			else MX[i] = max3*scale_fact;
			
		}
	
			
	}
	
	Int_t *index = new Int_t[nentries];
	TMath::Sort(nentries,MX,index, kTRUE);			   // CAMBIARE kTRUE IN kFALSE PER SELEZIONARE 
////////////////////////////////////////////////////////////////////////// L'ORDINE CRESCENTE O DECRESCENTE


	for(Int_t i = 0; i<nentries; i++){

////////////////////////////////////////////////// SELEZIONE INDICE:
	//	fTree->GetEntry(index[i]);	  // ORDINA PER MASSIMO
		fTree->GetEntry(i);		  // ORDINA PER N_EVENTO
//////////////////////////////////////////////////

		
		if(IsUUB) scale_fact = 2./4096;
		else scale_fact = 2./1024;
////////////////////////////////////////////////// SELEZIONE		
		sel_ev_str = to_string(nevent);
		sel_tank_str = to_string(tank);
		
		string ev_cut = "Nevent==" + sel_ev_str;
		
		string tank_cut = "Tank==" + sel_tank_str;
		
		cut = ev_cut + "&&" + tank_cut;
		
		cout << cut << endl;
		cout << "ev: " << nevent << "   tank: " << tank << endl;
		cout << "max1: " << max1 << endl;
		cout << "max2: " << max2 << endl;
		cout << "max3: " << max3 << endl;
		
////////////////////////////////////////////////// DRAW CON IL CUT DELL'ENTRATA SELEZIONATA		
		Int_t n = fTree->Draw("ADC1:ADC2:ADC3:ADC4:ADC5:ADC6:ADC7:ADC8:ADC9:ADC10:Time",cut.c_str(),"gOff");
		Double_t *adc1 = fTree->GetVal(0);
		Double_t *adc2 = fTree->GetVal(1);
		Double_t *adc3 = fTree->GetVal(2);
		Double_t *adc4 = fTree->GetVal(3);
		Double_t *adc5 = fTree->GetVal(4);
		Double_t *adc6 = fTree->GetVal(5);
		Double_t *adc7 = fTree->GetVal(6);
		Double_t *adc8 = fTree->GetVal(7);
		Double_t *adc9 = fTree->GetVal(8);
		Double_t *adc10 = fTree->GetVal(9);
		Double_t *time = fTree->GetVal(10);
		
		temp_base1 = base1;
		temp_base2 = base2;
		temp_base3 = base3;
		temp_base4 = base4;
		temp_base5 = base5;
		temp_base6 = base6;
		temp_base7 = base7;
		temp_base8 = base8;
		temp_base9 = base9;
		temp_base10 = base10;
		
		UUB_flag = IsUUB;
//////////////////////////////////////////////////

////////////////////////////////////////////////// PLOT GRAFICI
		if(UUB_flag){
			////////////////////////////////////////// I NUMERI SONO INVERTITI PERCHÉ HG E LG SONO INVERTITI TRA UB E UUB
			canvas->cd(2);
			TGraph *g1 = new TGraph(n, time, adc1);
			g1->Draw("AL");
			g1->GetYaxis()->SetLabelSize(0.07);
			g1->GetXaxis()->SetLabelSize(0.07);
			g1->GetYaxis()->SetTitle("ADC");
			g1->GetXaxis()->SetTitle("Time");
			g1->GetXaxis()->SetRangeUser(0,2048);
			g1->SetTitle("High Gain");
			TLine* baseline1 = new TLine(0,temp_base1,2048,temp_base1);
			baseline1->SetLineColor(kRed);
			baseline1->Draw();
			TLine* maxline1 = new TLine(0,max1,2048,max1);
			maxline1->SetLineColor(kBlue);
			maxline1->Draw();
			
			canvas->cd(1);
			TGraph *g2 = new TGraph(n, time, adc2);
			g2->Draw("AL");
			g2->GetYaxis()->SetLabelSize(0.07);
			g2->GetXaxis()->SetLabelSize(0.07);
			g2->GetYaxis()->SetTitle("ADC");
			g2->GetXaxis()->SetTitle("Time");
			g2->GetXaxis()->SetRangeUser(0,2048);
			g2->SetTitle("Low Gain");
			TLine* baseline2 = new TLine(0,temp_base2,2048,temp_base2);
			baseline2->SetLineColor(kRed);
			baseline2->Draw();
			
			canvas->cd(4);
			TGraph *g3 = new TGraph(n, time, adc3);
			g3->Draw("AL");
			g3->GetYaxis()->SetLabelSize(0.07);
			g3->GetXaxis()->SetLabelSize(0.07);
			g3->GetYaxis()->SetTitle("ADC");
			g3->GetXaxis()->SetTitle("Time");
			g3->GetXaxis()->SetRangeUser(0,2048);
			TLine* baseline3 = new TLine(0,temp_base3,2048,temp_base3);
			baseline3->SetLineColor(kRed);
			baseline3->Draw();
			TLine* maxline2 = new TLine(0,max2,2048,max2);
			maxline2->SetLineColor(kBlue);
			maxline2->Draw();
			
			canvas->cd(3);
			TGraph *g4 = new TGraph(n, time, adc4);
			g4->Draw("AL");
			g4->GetYaxis()->SetLabelSize(0.07);
			g4->GetXaxis()->SetLabelSize(0.07);
			g4->GetYaxis()->SetTitle("ADC");
			g4->GetXaxis()->SetTitle("Time");
			g4->GetXaxis()->SetRangeUser(0,2048);
			TLine* baseline4 = new TLine(0,temp_base4,2048,temp_base4);
			baseline4->SetLineColor(kRed);
			baseline4->Draw();
			
			canvas->cd(6);
			TGraph *g5 = new TGraph(n, time, adc5);
			g5->Draw("AL");
			g5->GetYaxis()->SetLabelSize(0.07);
			g5->GetXaxis()->SetLabelSize(0.07);
			g5->GetYaxis()->SetTitle("ADC");
			g5->GetXaxis()->SetTitle("Time");
			g5->GetXaxis()->SetRangeUser(0,2048);
			TLine* baseline5 = new TLine(0,temp_base5,2048,temp_base5);
			baseline5->SetLineColor(kRed);
			baseline5->Draw();
			TLine* maxline3 = new TLine(0,max3,2048,max3);
			maxline3->SetLineColor(kBlue);
			maxline3->Draw();
			
			canvas->cd(5);
			TGraph *g6 = new TGraph(n, time, adc6);
			g6->Draw("AL");
			g6->GetYaxis()->SetLabelSize(0.07);
			g6->GetXaxis()->SetLabelSize(0.07);
			g6->GetYaxis()->SetTitle("ADC");
			g6->GetXaxis()->SetTitle("Time");
			g6->GetXaxis()->SetRangeUser(0,2048);
			TLine* baseline6 = new TLine(0,temp_base6,2048,temp_base6);
			baseline6->SetLineColor(kRed);
			baseline6->Draw();
			
			canvas->cd(8);
			TGraph *g7 = new TGraph(n, time, adc7);
			g7->Draw("AL");
			g7->GetYaxis()->SetLabelSize(0.07);
			g7->GetXaxis()->SetLabelSize(0.07);
			g7->GetYaxis()->SetTitle("ADC");
			g7->GetXaxis()->SetTitle("Time");
			g7->GetXaxis()->SetRangeUser(0,2048);
			TLine* baseline7 = new TLine(0,temp_base7,2048,temp_base7);
			baseline7->SetLineColor(kRed);
			baseline7->Draw();
			
			canvas->cd(7);
			TGraph *g8 = new TGraph(n, time, adc8);
			g8->Draw("AL");
			g8->GetYaxis()->SetLabelSize(0.07);
			g8->GetXaxis()->SetLabelSize(0.07);
			g8->GetYaxis()->SetTitle("ADC");
			g8->GetXaxis()->SetTitle("Time");
			g8->GetXaxis()->SetRangeUser(0,2048);
			TLine* baseline8 = new TLine(0,temp_base8,2048,temp_base8);
			baseline8->SetLineColor(kRed);
			baseline8->Draw();
			
			canvas->cd(10);
			TGraph *g9 = new TGraph(n, time, adc9);
			g9->Draw("AL");
			g9->GetYaxis()->SetLabelSize(0.07);
			g9->GetXaxis()->SetLabelSize(0.07);
			g9->GetYaxis()->SetTitle("ADC");
			g9->GetXaxis()->SetTitle("Time");
			g9->GetXaxis()->SetRangeUser(0,2048);
			TLine* baseline9 = new TLine(0,temp_base9,2048,temp_base9);
			baseline9->SetLineColor(kRed);
			baseline9->Draw();
			
			canvas->cd(9);
			TGraph *g10 = new TGraph(n, time, adc10);
			g10->Draw("AL");
			g10->GetYaxis()->SetLabelSize(0.07);
			g10->GetXaxis()->SetLabelSize(0.07);
			g10->GetYaxis()->SetTitle("ADC");
			g10->GetXaxis()->SetTitle("Time");
			g10->GetXaxis()->SetRangeUser(0,2048);
			TLine* baseline10 = new TLine(0,temp_base10,2048,temp_base10);
			baseline10->SetLineColor(kRed);
			baseline10->Draw();
		
		} else {
			canvas->cd(1);
			TGraph *g1 = new TGraph(n, time,  adc1);
			g1->Draw("AL");
			g1->GetYaxis()->SetLabelSize(0.07);
			g1->GetXaxis()->SetLabelSize(0.07);
			g1->GetYaxis()->SetTitle("ADC");
			g1->GetXaxis()->SetTitle("Time");
			g1->GetXaxis()->SetRangeUser(0,750);
			g1->SetTitle("Low Gain");
			TLine* baseline1 = new TLine(0,temp_base1,750,temp_base1);
			baseline1->SetLineColor(kRed);
			baseline1->Draw();
			
			canvas->cd(2);
			TGraph *g2 = new TGraph(n, time,  adc2);
			g2->Draw("AL");
			g2->GetYaxis()->SetLabelSize(0.07);
			g2->GetXaxis()->SetLabelSize(0.07);
			g2->GetYaxis()->SetTitle("ADC");
			g2->GetXaxis()->SetTitle("Time");
			g2->GetXaxis()->SetRangeUser(0,750);
			g2->SetTitle("High Gain");
			TLine* baseline2 = new TLine(0,temp_base2,750,temp_base2);
			baseline2->SetLineColor(kRed);
			baseline2->Draw();
			TLine* maxline1 = new TLine(0,max1,750,max1);
			maxline1->SetLineColor(kBlue);
			maxline1->Draw();
			
			canvas->cd(3);
			TGraph *g3 = new TGraph(n, time,  adc3);
			g3->Draw("AL");
			g3->GetYaxis()->SetLabelSize(0.07);
			g3->GetXaxis()->SetLabelSize(0.07);
			g3->GetYaxis()->SetTitle("ADC");
			g3->GetXaxis()->SetTitle("Time");
			g3->GetXaxis()->SetRangeUser(0,750);
			TLine* baseline3 = new TLine(0,temp_base3,750,temp_base3);
			baseline3->SetLineColor(kRed);
			baseline3->Draw();
			
			canvas->cd(4);
			TGraph *g4 = new TGraph(n, time,  adc4);
			g4->Draw("AL");
			g4->GetYaxis()->SetLabelSize(0.07);
			g4->GetXaxis()->SetLabelSize(0.07);
			g4->GetYaxis()->SetTitle("ADC");
			g4->GetXaxis()->SetTitle("Time");
			g4->GetXaxis()->SetRangeUser(0,750);
			TLine* baseline4 = new TLine(0,temp_base4,750,temp_base4);
			baseline4->SetLineColor(kRed);
			baseline4->Draw();
			TLine* maxline2 = new TLine(0,max2,750,max2);
			maxline2->SetLineColor(kBlue);
			maxline2->Draw();
			
			canvas->cd(5);
			TGraph *g5 = new TGraph(n, time,  adc5);
			g5->Draw("AL");
			g5->GetYaxis()->SetLabelSize(0.07);
			g5->GetXaxis()->SetLabelSize(0.07);
			g5->GetYaxis()->SetTitle("ADC");
			g5->GetXaxis()->SetTitle("Time");
			g5->GetXaxis()->SetRangeUser(0,750);
			TLine* baseline5 = new TLine(0,temp_base5,750,temp_base5);
			baseline5->SetLineColor(kRed);
			baseline5->Draw();
			
			canvas->cd(6);
			TGraph *g6 = new TGraph(n, time,  adc6);
			g6->Draw("AL");
			g6->GetYaxis()->SetLabelSize(0.07);
			g6->GetXaxis()->SetLabelSize(0.07);
			g6->GetYaxis()->SetTitle("ADC");
			g6->GetXaxis()->SetTitle("Time");
			g6->GetXaxis()->SetRangeUser(0,750);
			TLine* baseline6 = new TLine(0,temp_base6,750,temp_base6);
			baseline6->SetLineColor(kRed);
			baseline6->Draw();
			TLine* maxline3 = new TLine(0,max3,750,max3);
			maxline3->SetLineColor(kBlue);
			maxline3->Draw();
			
			canvas->cd(7);
			TGraph *g7 = new TGraph(n, time, adc7);
			g7->Draw("AL");
			g7->GetYaxis()->SetLabelSize(0.07);
			g7->GetXaxis()->SetLabelSize(0.07);
			g7->GetYaxis()->SetTitle("ADC");
			g7->GetXaxis()->SetTitle("Time");
			g7->GetXaxis()->SetRangeUser(0,2048);
			TLine* baseline7 = new TLine(0,temp_base7,2048,temp_base7);
			baseline7->SetLineColor(kRed);
			baseline7->Draw();
			
			canvas->cd(8);
			TGraph *g8 = new TGraph(n, time, adc8);
			g8->Draw("AL");
			g8->GetYaxis()->SetLabelSize(0.07);
			g8->GetXaxis()->SetLabelSize(0.07);
			g8->GetYaxis()->SetTitle("ADC");
			g8->GetXaxis()->SetTitle("Time");
			g8->GetXaxis()->SetRangeUser(0,2048);
			TLine* baseline8 = new TLine(0,temp_base8,2048,temp_base8);
			baseline8->SetLineColor(kRed);
			baseline8->Draw();
			
			canvas->cd(9);
			TGraph *g9 = new TGraph(n, time, adc9);
			g9->Draw("AL");
			g9->GetYaxis()->SetLabelSize(0.07);
			g9->GetXaxis()->SetLabelSize(0.07);
			g9->GetYaxis()->SetTitle("ADC");
			g9->GetXaxis()->SetTitle("Time");
			g9->GetXaxis()->SetRangeUser(0,2048);
			TLine* baseline9 = new TLine(0,temp_base9,2048,temp_base9);
			baseline9->SetLineColor(kRed);
			baseline9->Draw();
			
			canvas->cd(10);
			TGraph *g10 = new TGraph(n, time, adc10);
			g10->Draw("AL");
			g10->GetYaxis()->SetLabelSize(0.07);
			g10->GetXaxis()->SetLabelSize(0.07);
			g10->GetYaxis()->SetTitle("ADC");
			g10->GetXaxis()->SetTitle("Time");
			g10->GetXaxis()->SetRangeUser(0,2048);
			TLine* baseline10 = new TLine(0,temp_base10,2048,temp_base10);
			baseline10->SetLineColor(kRed);
			baseline10->Draw();
		}
////////////////////////////////////////////////// SCOMMENTARE IL PRINT PER STAMPARE
//		canvas->Print();		  // I GRAFICI MAN MANO CHE VENGONO MOSTRATI
		canvas->Update();		  // ATTENZIONE, SOVRASCRIVONO TUTTI LA STESSA IMMAGINE
//////////////////////////////////////////////////		
		cout << "Press Enter to go next, 'c' to stop, 'p' to go to the previous one..." << endl;
		
		auto ch = cin.get();
		count+=1;
		if(ch=='c') break;
		else if(ch=='p') {
			i -= 3;	// A quanto pare serve diminuire di 3 per tornare indietro
			count -= 1;
		}
		else if(ch=='n'){
			an += 1;
		}
	}
	cout << count << endl;
}
