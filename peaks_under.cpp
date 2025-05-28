////////////////////////////////////////////
// Essenzialmente uguale a peaks_triple.cpp
// utilizzato per controllo con i file in
// output da Under.cpp
// Seleziona eventi con anomalie contando
// il numero di volte che il segnale
// passa attraverso la baseline (almeno Nzero) 
// entro un certo numero di bins
// (RANGE_UB, RANGE_UUB).
//
// Questa verifica viene effettuata solo
// se il segnale scende al di sotto di
// Nstd deviazioni standard (della
// distribuzione degli ADC nei primi
// 100 bins) rispetto alla baseline.
//
// La traccia viene selezionata se
// le condizioni sono verificate su 3 PMT.
//
// Il file deve contenere una Branch con le 
// baselines.
// 
// Plotta una distribuzione dei massimi
// come in Add_Max_Branch.cpp ma è
// più sicuro utilizzare quello
// per le distribuzioni dei massimi
// con il file fornito da questo codice.
//
// Crea anche un file con gli eventi non selezionati.
//
// DA ESEGUIRE CON I FILE OUTPUTTATI DA Under.cpp
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
#include <string>
#include <sstream>
#include <vector>


void peaks_under(){
//////////////////////////////////////////////////////////////////////// SELEZIONE FILE:
//	TFile *f = new TFile("file_out_threshold_sel_under.root");	// (Primo)	
//	TFile *f = new TFile("data_2022_02_03_09h04_sel_under.root");	// 3 Feb
	TFile *f = new TFile("data_2022_07_23_09h22_sel_under.root");	// 23 Lug
///////////////////////////////////////////////////////////////////////

	TTree *fTree = (TTree*)f->Get("tree");
	Int_t nentries = fTree->GetEntries();
	printf("%d\n", nentries);
	
	int Nstd = 3;
	int RANGE_UUB = 60;
	int RANGE_UB = 20;
	int Nzero = 6;
	
	gROOT->Reset();
	gStyle->SetOptStat("nemr");
	gStyle->SetOptTitle(0);
	gROOT->SetStyle("Plain");
	gROOT->SetBatch(kFALSE);
	
	int fill_style = 3001;
	
	/////////////////////////////////////////// UUB
	/////////////////////////////////////////// Istogramma di tutti gli ADC nei primi 100 time bins
	///////////////////////////////////////////
	
	TH1D* HGUUB = new TH1D("HGUUB","24/07",100,-0.4,1);
	
	fTree->Draw("(ADC1-Baseline1)*2/4096 >> HGUUB","UUB==1 && Time<100","goff");
	fTree->Draw("(ADC3-Baseline3)*2/4096 >>+ HGUUB","UUB==1 && Time<100","goff");
	fTree->Draw("(ADC5-Baseline5)*2/4096 >>+ HGUUB","UUB==1 && Time<100","goff");
	
	///// DRAW OPT
	TCanvas* canvas1 = new TCanvas("All_ADC_0724","All ADC",800,600);
	canvas1->cd();
	canvas1->SetLogy();

//	HGUUB->SetFillStyle(fill_style);
	HGUUB->SetLineColorAlpha(kOrange+2, 0.35);
	HGUUB->SetLineWidth(2);
	HGUUB->GetXaxis()->SetTitle("ADC [V]");
//	HGUUB->Draw();

	
 //	canvas1->Print();
	/////

	/////////////////////////////////////////// UB
	/////////////////////////////////////////// Istogramma di tutti gli ADC nei primi 100 time bins
	///////////////////////////////////////////

	TH1D* HGUB = new TH1D("HGUB","24/07",100,-0.4,1);
	
	fTree->Draw("(ADC2-Baseline2)*2/1024 >> HGUB","UUB==0 && Time<100","goff");
	fTree->Draw("(ADC4-Baseline4)*2/1024 >>+ HGUB","UUB==0 && Time<100","goff");
	fTree->Draw("(ADC6-Baseline6)*2/1024 >>+ HGUB","UUB==0 && Time<100","goff");
	
	///// DRAW OPT
//	TCanvas* canvas2 = new TCanvas("UB_ADC_p6","UB ADC",800,600);
//	canvas2->cd();
//	canvas2->SetLogy();

//	HGUB->SetFillStyle(fill_style);
	HGUB->SetLineColorAlpha(kAzure-7, 0.35);
	HGUB->SetLineWidth(2);
	HGUB->GetXaxis()->SetTitle("ADC [V]");
	HGUB->Scale(1./HGUB->Integral(0,100));
	HGUB->SetMaximum(10);
	HGUB->SetMinimum(1E-8);
	HGUB->Draw("HIST");

	HGUUB->Scale(1./HGUUB->Integral(0,100));
	HGUUB->SetMaximum(10);
	HGUUB->SetMinimum(1E-8);
	HGUUB->Draw("HIST SAMES");
	TLegend* legend_UB = new TLegend(0.55,0.80,0.75,0.85);
	legend_UB->AddEntry(HGUB, "UB");
	legend_UB->Draw();
 //	canvas2->Print();
 	TLegend* legend_UUB = new TLegend(0.55,0.85,0.75,0.9);
	legend_UUB->AddEntry(HGUUB, "UUB");
	legend_UUB->Draw();
	/////
	canvas1->Print();
//	canvas1->Close();
//	canvas2->Close();
	
	///////////////////////////////////////////
	/////////////////////////////////////////// 
	///////////////////////////////////////////
	Float_t std_UUB = HGUUB->GetStdDev();
	TH1D* peak_histo_UUB_HG = new TH1D("UUB High Gain","UUB peaks",100,0,2);

	Float_t std_UB = HGUB->GetStdDev();
	TH1D* peak_histo_UB_HG = new TH1D("UB High Gain","UB peaks",100,0,2);
	
	//////////// Variabili per conteggi
	int countUUB = 0;
	int countHGUUB = 0;
	int TtotcountUUB = 0;
	int TcountUUB = 0;
	int TflagUUB = 0;

	int countUB = 0;
	int countHGUB = 0;
	int TtotcountUB = 0;
	int TcountUB = 0;
	int TflagUB = 0;

	int totEVcount = 0;
	int EVcount = 0;
	
	///////////////////// NEL CASO SI VOLESSE INSERIRE LA STD A MANO
	//std_UUB = 0.00726;
	//std_UB = 0;
	/////////////////////
	
	int zero = 0;
	
	std::vector< Int_t > sel_events;
	std::vector< Int_t > sel_tanks;
	////////////
	
	Int_t nevent;
	Int_t tank;
	
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
	
	Int_t Time[2048];
	
	Int_t IsUUB;
	
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
	fTree->SetBranchAddress("Time",Time);

	Int_t max1;
	Int_t max2;
	Int_t max3;
	Int_t max4;
	Int_t max5;
	Int_t max6;	
	
	Int_t newmax1;
	Int_t newmax2;
	Int_t newmax3;
	Int_t newmax4;
	Int_t newmax5;
	Int_t newmax6;	
	
	Int_t FFlag1 = 0;
	Int_t FFlag2 = 0;
	Int_t FFlag3 = 0;

	Int_t min1;
	Int_t min2;
	Int_t min3;
	Int_t min4;
	Int_t min5;
	Int_t min6;
	
	Int_t min_index1;
	Int_t min_index2;
	Int_t min_index3;

	
	Float_t scale_fact;
	
	Int_t prev_temp = 0;
	Int_t prev_ev = 0;
	
	
	
	
	for(int i=0; i<nentries; i++){
		
		fTree->GetEntry(i);
		if(tank!=1438 and tank!=29){ //Queste tank non vengono considerate perché malfunzionanti
		
		TflagUB=0;
		TflagUUB=0;
		zero = 0;
		FFlag1 = 0;
		FFlag2 = 0;
		FFlag3 = 0;
		
		if(IsUUB){
		
			scale_fact = 2./4096;
			
			countUUB+=3;
			TtotcountUUB++;
			zero = 0;
			FFlag1 = 0;
			FFlag2 = 0;
			FFlag3 = 0;
			
			max1 = TMath::MaxElement(2048,ADC1);
			max3 = TMath::MaxElement(2048,ADC3);
			max5 = TMath::MaxElement(2048,ADC5);
			
			min1 = TMath::MinElement(2048,ADC1);
			min3 = TMath::MinElement(2048,ADC3);
			min5 = TMath::MinElement(2048,ADC5);

			
			if( ((min1*scale_fact)<(base1*scale_fact - Nstd*std_UUB)) and (max1<4094) ){			/////////////////////// Se il minimo della traccia è più di "Nstd"
				for(int i=0; i<(2048-RANGE_UUB); i++){						/////////////////////// (definito all'inizio) deviazioni standard
					if(ADC1[i]*scale_fact<(base1*scale_fact - Nstd*std_UUB)){			/////////////////////// sotto la baseline, ogni volta che si scende
															/////////////////////// sotto questo valore, nella traccia, vengono
						prev_temp = ADC1[i];							/////////////////////// contati i passaggi dalla baseline
															/////////////////////// nei "RANGE_UUB" bin successivi.
															/////////////////////// Se entro questi viene oltrepassata la
						for(int j=0; j<RANGE_UUB; j++){					/////////////////////// baseline più di Nzero volte, viene segnalato:
															/////////////////////// Da TFlagUUB che è stata individuata una traccia UUB
							if( ((ADC1[i+j]-base1)>=0 and (prev_temp-base1)<=0) or 	/////////////////////// Da FFlag1,2,3 che è stata individuata la traccia  
							  ((ADC1[i+j]-base1)<=0 and (prev_temp-base1)>=0) ) zero++;	/////////////////////// 	di questo PMT
							  								/////////////////////// Viene incrementato countHGUUB per tenere conto del numero
							prev_temp = ADC1[i+j];						/////////////////////// 	di tracce individuate
						}									/////////////////////// All'inizio viene controllato anche che la traccia
					}										/////////////////////// sia < 4094 per evitare gli undershoot
					if(zero>Nzero and zero<16){									///////////////////////
						FFlag1 = 1;								///////////////////////
						TflagUUB = 1;								///////////////////////
						break;									///////////////////////
					}zero=0;										///////////////////////
				}											///////////////////////
			}												///////////////////////
			
			zero = 0;
			
			if( ((min3*scale_fact)<(base3*scale_fact - Nstd*std_UUB)) and (max3<4094) ){
				
				for(int i=0; i<(2048-RANGE_UUB); i++){
					
					if(ADC3[i]*scale_fact<(base3*scale_fact - Nstd*std_UUB)){
						
						prev_temp = ADC3[i];
						
						for(int j=0; j<RANGE_UUB; j++){
						
							if( ((ADC3[i+j]-base3)>=0 and (prev_temp-base3)<=0) or 
							  ((ADC3[i+j]-base3)<=0 and (prev_temp-base3)>=0) ) zero++;
							
							prev_temp = ADC3[i+j];
						}
						
					}
					
					if(zero>Nzero and zero<16){
						FFlag2 = 1;
						TflagUUB = 1;
						break;
					}zero=0;
				}
			}
			
			zero = 0;
			
			if( ((min5*scale_fact)<(base5*scale_fact - Nstd*std_UUB)) and (max5<4094) ){
				
				for(int i=0; i<(2048-RANGE_UUB); i++){
					
					if(ADC5[i]*scale_fact<(base5*scale_fact - Nstd*std_UUB)){
						
						prev_temp = ADC5[i];
						
						for(int j=0; j<RANGE_UUB; j++){
						
							if( ((ADC5[i+j]-base5)>=0 and (prev_temp-base5)<=0) or 
							  ((ADC5[i+j]-base5)<=0 and (prev_temp-base5)>=0) ) zero++;
							
							prev_temp = ADC5[i+j];
						}
					}
					
					if(zero>Nzero and zero<16){
						FFlag3 = 1;
						TflagUUB = 1;
						break;
					}zero=0;
				}
			}
			
			
					
				
		} else {
			
			scale_fact = 2./1024;
			
			countUB+=3;
			TtotcountUB++;
			zero = 0;
			FFlag1 = 0;
			FFlag2 = 0;
			FFlag3 = 0;
			
			max2 = TMath::MaxElement(750,ADC2);
			max4 = TMath::MaxElement(750,ADC4);
			max6 = TMath::MaxElement(750,ADC6);
			
			min2 = TMath::MinElement(750,ADC2);
			min4 = TMath::MinElement(750,ADC4);
			min6 = TMath::MinElement(750,ADC6);
			
			if( ((min2*scale_fact)<(base2*scale_fact - Nstd*std_UB)) and (max2<1022) ){
				
				for(int i=0; i<(750-RANGE_UB); i++){
					
					if(ADC2[i]*scale_fact<(base2*scale_fact - Nstd*std_UB)){
						
						prev_temp = ADC2[i];
						
						for(int j=0; j<RANGE_UB; j++){
						
							if( ((ADC2[i+j]-base2)>=0 and (prev_temp-base2)<=0) or 
							  ((ADC2[i+j]-base2)<=0 and (prev_temp-base2)>=0) ) zero++;
							
							prev_temp = ADC2[i+j];
							
						}
					}
					
					if(zero>Nzero and zero<16){
						FFlag1 = 1;
						TflagUB = 1;
						break;
					}zero=0;
				}
			}
			
			zero = 0;
			
			if( ((min4*scale_fact)<(base4*scale_fact - Nstd*std_UB)) and (max4<1022) ){
				
				for(int i=0; i<(750-RANGE_UB); i++){
					
					if(ADC4[i]*scale_fact<(base4*scale_fact - Nstd*std_UB)){
						
						prev_temp = ADC4[i];
						
						for(int j=0; j<RANGE_UB; j++){
						
							if( ((ADC4[i+j]-base4)>=0 and (prev_temp-base4)<=0) or 
							  ((ADC4[i+j]-base4)<=0 and (prev_temp-base4)>=0) ) zero++;
							
							prev_temp = ADC4[i+j];
						}
					}
					
					if(zero>Nzero and zero<16){
						FFlag2 = 1;
						TflagUB = 1;
						break;
					}zero=0;
				}
			}
			
			zero = 0;
			
			if( ((min6*scale_fact)<(base6*scale_fact - Nstd*std_UB)) and (max6<1022) ){
				
				for(int i=0; i<(750-RANGE_UB); i++){
					
					if(ADC6[i]*scale_fact<(base6*scale_fact - Nstd*std_UB)){
						
						prev_temp = ADC6[i];
						
						for(int j=0; j<RANGE_UB; j++){
						
							if( ((ADC6[i+j]-base6)>=0 and (prev_temp-base6)<=0) or 
							  ((ADC6[i+j]-base6)<=0 and (prev_temp-base6)>=0) ) zero++;
							
							prev_temp = ADC6[i+j];
						}
					}
					
					if(zero>Nzero and zero<16){
						FFlag3 = 1;
						TflagUB = 1;
						break;
					}zero=0;
				}
			}
		}
		
		if((TflagUUB)and(FFlag1 and FFlag2 and FFlag3)){					
					TcountUUB++;		
					countHGUUB+=3;
					
					min_index1 = TMath::LocMin(2048-40,ADC1);
					min_index2 = TMath::LocMin(2048-40,ADC3);
					min_index3 = TMath::LocMin(2048-40,ADC5);
					
					if(min_index1<40) min_index1=40;
					if(min_index2<40) min_index2=40;
					if(min_index3<40) min_index3=40;
								
					Int_t *temp_adc1 = ADC1 + min_index1 -40;
					Int_t *temp_adc2 = ADC3 + min_index2 -40;
					Int_t *temp_adc3 = ADC5 + min_index3 -40;
					
					newmax1 = TMath::MaxElement(80,temp_adc1);
					newmax3 = TMath::MaxElement(80,temp_adc2);
					newmax5 = TMath::MaxElement(80,temp_adc3);			////////////////////////// Se le tracce di tutti e tre i PMT sono state
													////////////////////////// individuate, viene incrementato il conteggio delle
													////////////////////////// entries (tank per ogni evento) e viene riempito l'istogramma
					peak_histo_UUB_HG->Fill(newmax1*scale_fact);			////////////////////////// con i massimi di ogni traccia (presi 40 bins prima e 40 bins
					peak_histo_UUB_HG->Fill(newmax3*scale_fact);			////////////////////////// dopo il minimo).
					peak_histo_UUB_HG->Fill(newmax5*scale_fact);			////////////////////////// QUESTA STESSA OPERAZIONE VIENE ESEGUITA DAL CODICE
													////////////////////////// ADD_MAX_BRANCH CHE È PIÙ SICURO DA USARE.
		}
			
		if((TflagUB)and(FFlag1 and FFlag2 and FFlag3)){					////////////////////////// Uguale ma per le UB (con il max 13 bins prima e 13 bins dopo il minimo)
					TcountUB++;
					countHGUB+=3;
					
					min_index1 = TMath::LocMin(750-13,ADC2);
					min_index2 = TMath::LocMin(750-13,ADC4);
					min_index3 = TMath::LocMin(750-13,ADC6);
					
					if(min_index1<13) min_index1=13;
					if(min_index2<13) min_index2=13;
					if(min_index3<13) min_index3=13;
					
					Int_t *temp_adc1 = ADC2 + min_index1 -13;
					Int_t *temp_adc2 = ADC4 + min_index2 -13;
					Int_t *temp_adc3 = ADC6 + min_index3 -13;
					
					newmax2 = TMath::MaxElement(26,temp_adc1);
					newmax4 = TMath::MaxElement(26,temp_adc2);
					newmax6 = TMath::MaxElement(26,temp_adc3);
					
					peak_histo_UB_HG->Fill(newmax2*scale_fact);
					peak_histo_UB_HG->Fill(newmax4*scale_fact);
					peak_histo_UB_HG->Fill(newmax6*scale_fact);
		}
			
		if(nevent != prev_ev){									////////////////////////// Se l'evento non è lo stesso della entry precedente,
			totEVcount++;									////////////////////////// ovvero se sono finite le tank per questo evento e siamo
			if((TflagUUB || TflagUB) and (FFlag1 and FFlag2 and FFlag3)){		////////////////////////// passati a quello successivo, incrementa il numero totale di Eventi.
				EVcount++;								////////////////////////// Se una tank (sia UB che UUB) ha individuato una traccia,
			}										////////////////////////// e se l'ha individuata su tutti e tre i PMT, incrementa il numero
		}											////////////////////////// di eventi individuati.
				
		if((TflagUUB || TflagUB) and (FFlag1 and FFlag2 and FFlag3)){			////////////////////////// Per ogni entry, indipendentemente che sia lo stesso evento o meno,
			sel_events.push_back(nevent);							////////////////////////// se sono rispettate le condizioni di cui sopra, salva in un vettore
			sel_tanks.push_back(tank);							////////////////////////// numero di evento e tank
		}
		
		prev_ev = nevent;		
	}	////////////////////////// Per chiudere l'if che stringe la selezione 
	}	
	cout << "\nUUB  " << "HG traces found: " << (Float_t)countHGUUB/countUUB << endl
	     << "tot: " << countUUB << "	found: " << countHGUUB << endl
	     << "\nentries found: " << (Float_t)TcountUUB/TtotcountUUB << endl
	     << "tot: " << TtotcountUUB << "	found: " << TcountUUB << endl;
	     
	cout << "\n" << endl;
	
	cout << "\nUB	" << "HG traces found: " << (Float_t)countHGUB/countUB << endl
	     << "tot: " << countUB << "	found: " << countHGUB << endl
	     << "\nentries found: " << (Float_t)TcountUB/TtotcountUB << endl
	     << "tot: " << TtotcountUB << "	found: " << TcountUB << endl;
	
	cout << "\n" << endl;
	
	cout << "\nEvents found: " << (Float_t)EVcount/totEVcount << endl
	     << "tot: " << totEVcount << "	found: " << EVcount << endl;

	//////// DRAW OPT
	TCanvas* canvas_p1 = new TCanvas("UUB_p6","UUB",800,600);
	canvas_p1->cd();
	canvas_p1->SetLogy();

	peak_histo_UUB_HG->SetFillColor(kRed);
	peak_histo_UUB_HG->Draw();
	peak_histo_UUB_HG->GetXaxis()->SetTitle("ADC [V]");

/*	TLegend* legend_UUB_p = new TLegend(0.55,0.85,0.75,0.9);
	legend_UUB_p->AddEntry(peak_histo_UUB_HG, "High Gain");
	legend_UUB_p->Draw();
*/
	canvas_p1->Update();
	canvas_p1->Print();
	////////
	TCanvas* canvas_p2 = new TCanvas("UB_p6","UB",800,600);
	canvas_p2->cd();
	canvas_p2->SetLogy();

	peak_histo_UB_HG->SetFillColor(kRed);
	peak_histo_UB_HG->Draw();
	peak_histo_UB_HG->GetXaxis()->SetTitle("ADC [V]");

/*	TLegend* legend_UB_p = new TLegend(0.55,0.85,0.75,0.9);
	legend_UB_p->AddEntry(peak_histo_UB_HG, "High Gain");
	legend_UB_p->Draw();
*/
	canvas_p2->Update();
	canvas_p2->Print();

	canvas_p1->Close();
	canvas_p2->Close();
///////////////////////////////////////////////////////////////////////////////////////// SELEZIONE OUTPUT:	
//	TFile *small_file = new TFile("file_out_threshold_sel_selunder.root","RECREATE");     //
//	TFile *small_file = new TFile("data_2022_02_03_09h04_sel_selunder.root","RECREATE");  //
	TFile *small_file = new TFile("data_2022_07_23_09h22_sel_selunder.root","RECREATE");  //
/////////////////////////////////////////////////////////////////////////////////////////

	TTree *small_tree = fTree->CloneTree(0);		/////////////////////////// Su un TTree clonato salvo solo le entries con
								/////////////////////////// nevent e tank corrispondenti a quelli salvati 
	int j=0;						/////////////////////////// precedentemente nei vettori
								/////////////////////////// Ci sono sicuramente modi più eleganti, da modificare
	
	for(int i=0;i<nentries;i++){
	
		fTree->GetEntry(i);
		if(nevent==sel_events[j] && tank==sel_tanks[j]){
			small_tree->Fill();
			if(j>sel_tanks.size()) break;
			j++;
		}
	}
	
	small_file->Write();
/**************************************************************************************/
///////////////////////////////////////////////////////////// PER CREARE UN TTREE CON GLI EVENTI NON SELEZIONATI
/////////////////////////////////////////////////////////////////////////////////////// SELEZIONE OUTPUT BIG:	
//	TFile *big_file = new TFile("file_out_threshold_unsel_selunder.root","RECREATE");     //
//	TFile *big_file = new TFile("data_2022_02_03_09h04_unsel_selunder.root","RECREATE");  //
	TFile *big_file = new TFile("data_2022_07_23_09h22_unsel_selunder.root","RECREATE");  //
///////////////////////////////////////////////////////////////////////////////////////
	TTree *big_tree = fTree->CloneTree(0);
	
	j=0;
	
	for(int i=0;i<nentries;i++){
	
		fTree->GetEntry(i);
		if(nevent==sel_events[j] && tank==sel_tanks[j]) {j++; continue;}
		big_tree->Fill();
//		if(j>(nentries-sel_tanks.size())) break;
		
		
	}
	
	big_file->Write();
	cout<< "big " << big_tree->GetEntries() << endl;
	cout<< "tot " << nentries << endl;
/**************************************************************************************/	
	sel_events.clear();
	sel_tanks.clear();	
}
