#!/bin/bash

# data
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/E4/Final/samples/data.mu.2.root
do
	./runSelection.exe $filename;
done

for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/data.mu.2_selected.root
do
	./plotDistribution.exe $filename;
done

# background
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/ttbar*.root
do
	./plotDistribution.exe $filename;
done

for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/singletop*.root
do
	./plotDistribution.exe $filename;
done

for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/diboson*.root
do
	./plotDistribution.exe $filename;
done

for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/wjets*.root
do
	./plotDistribution.exe $filename;
done

for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/zjets*.root
do
	./plotDistribution.exe $filename;
done

# stacked plots
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/data.mu.2_selected.root
do
	./stackedPlots.exe $filename;
done
