#!/bin/bash

# stacked plots
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/data.mu.2_selected.root
do
	./stackedPlots.exe $filename;
done
