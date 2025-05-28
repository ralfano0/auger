'''
Seleziona gli eventi se la frequenza
più intensa trovata per mezzo di Fourier
è in un certo range.

Crea anche un file con gli eventi
non selezionati.

Necessita di un file in cui siano già
state selezionate le tracce con segnale
al di sotto della baseline.
(vedi under.cpp)

Da migliorare.

'''

import ROOT
import numpy as np
import matplotlib.pyplot as plt
#import pandas as pd
import matplotlib
import array
import sys
#import scipy.stats
#import scipy.signal as sps
#import plotter
from scipy.fft import fft, fftfreq

def smooth(y, box_pts):
    box = np.ones(box_pts)/box_pts
    y_smooth = np.convolve(y, box, mode='same')
    return y_smooth

################################################### Importo il tree generato precedentemente dal file Add_Base_Branch.cpp
Root_file = ROOT.TFile.Open("data_2022_02_03_09h04_sel_tr.root","READ")
#Root_file = ROOT.TFile.Open("data_2022_07_23_09h22_sel_tr.root","READ")

fTree = Root_file.Get("tree")

###################################################
ROOT.gROOT.Reset()
ROOT.gStyle.SetOptStat("nemr")
#ROOT.gStyle.SetOptTitle(0)
ROOT.gROOT.SetStyle("Plain")
ROOT.gROOT.SetBatch(ROOT.kFALSE)
###################################################

Ntree = fTree.GetEntries()
NUUB = 2048
TUUB = 1./(120)
xfUUB = fftfreq(NUUB,TUUB)[:NUUB//2]
NUB = 750
TUB = 1./(40)
xfUB = fftfreq(NUB,TUB)[:NUB//2]

yf1UUB = np.zeros((NUUB,Ntree))
yf2UUB = np.zeros((NUUB,Ntree))
yf3UUB = np.zeros((NUUB,Ntree))
yf1UB = np.zeros((NUB,Ntree))
yf2UB = np.zeros((NUB,Ntree))
yf3UB = np.zeros((NUB,Ntree))


num_UUB=0
num_UB=0

i=0

sel_events = []
sel_tanks = []

out_file = ROOT.TFile.Open("data_2022_02_03_09h04_fousel.root","RECREATE")
#out_file = ROOT.TFile.Open("data_2022_07_23_09h22_fousel.root","RECREATE")

out_tree = fTree.CloneTree(0)

unsel_file = ROOT.TFile.Open("data_2022_02_03_09h04_fouUNsel.root","RECREATE")
#unsel_file = ROOT.TFile.Open("data_2022_07_23_09h22_fouUNsel.root","RECREATE")

unsel_tree = fTree.CloneTree(0)

# Attenzione alla funzione smooth. Può risultare utile tenerla in alcuni casi.

for event in fTree:
	if(event.UUB==1):
		temp_adc1 = np.asarray(event.ADC1)
		yf1UUB[:,i] = fft(temp_adc1)
		max1 = np.argmax(smooth(yf1UUB[60:NUUB//2,i],10))
		
		temp_adc3 = np.asarray(event.ADC3)
		yf2UUB[:,i] = fft(temp_adc3)
		max2 = np.argmax(smooth(yf2UUB[60:NUUB//2,i],10))
		
		temp_adc5 = np.asarray(event.ADC5)
		yf3UUB[:,i] = fft(temp_adc5)
		max3 = np.argmax(smooth(yf3UUB[60:NUUB//2,i],10))
		
		if( (xfUUB[max1]>3 and xfUUB[max1]<18) or \
		(xfUUB[max2]>3 and xfUUB[max2]<18) or \
		(xfUUB[max3]>3 and xfUUB[max3]<18)): 
			sel_events.append(event.Nevent)
			sel_tanks.append(event.Tank)
			out_tree.Fill()
		else: unsel_tree.Fill()
		
	elif(event.UUB==0):
		temp_adc2 = np.asarray(event.ADC2)[:NUB]
		yf1UB[:,i] = fft(temp_adc2)
		max1 = np.argmax(smooth(yf1UB[60:NUB//2,i],10))
		
		temp_adc4 = np.asarray(event.ADC4)[:NUB]
		yf2UB[:,i] = fft(temp_adc4)
		max2 = np.argmax(smooth(yf2UB[60:NUB//2,i],10))
		
		temp_adc6 = np.asarray(event.ADC6)[:NUB]
		yf3UB[:,i] = fft(temp_adc6)
		max3 = np.argmax(smooth(yf3UB[60:NUB//2,i],10))
		
		if((xfUB[max1]>3 and xfUB[max1]<18) or \
		(xfUB[max2]>3 and xfUB[max2]<18) or \
		(xfUB[max3]>3 and xfUB[max3]<18)): 
			sel_events.append(event.Nevent)
			sel_tanks.append(event.Tank)
			out_tree.Fill()
		else: unsel_tree.Fill()
	
	
	i+=1
	
out_file.Write()
unsel_file.Write()


print("Total: ", fTree.GetEntries())
print("Selected: ", out_tree.GetEntries())
print("Discarded: ", unsel_tree.GetEntries())
#Root_file.Close()
#out_file.Close()

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
