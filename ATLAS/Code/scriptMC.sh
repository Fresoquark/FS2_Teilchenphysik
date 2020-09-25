#!/bin/bash

for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/E4/Final/samples/ttbar.el.root
do
	./runSelection.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/E4/Final/samples/ttbar.mu.root
do
	./runSelection.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/E4/Final/samples/singletop.el.root
do
	./runSelection.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/E4/Final/samples/singletop.mu.root
do
	./runSelection.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/E4/Final/samples/diboson.el.root
do
	./runSelection.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/E4/Final/samples/diboson.mu.root
do
	./runSelection.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/E4/Final/samples/wjets.el.root
do
	./runSelection.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/E4/Final/samples/wjets.mu.root
do
	./runSelection.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/E4/Final/samples/zjets.el.root
do
	./runSelection.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/E4/Final/samples/zjets.mu.root
do
	./runSelection.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/E4/Final/samples/zprime*.el.root
do
	./runSelection.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/E4/Final/samples/zprime*.mu.root
do
	./runSelection.exe $filename;
done

# plotDistribution
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/ttbar.el*.root
do
	./plotDistribution.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/ttbar.mu*.root
do
	./plotDistribution.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/singletop.el*.root
do
	./plotDistribution.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/singletop.mu*.root
do
	./plotDistribution.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/diboson.el*.root
do
	./plotDistribution.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/diboson.mu*.root
do
	./plotDistribution.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/wjets.el*.root
do
	./plotDistribution.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/wjets.mu*.root
do
	./plotDistribution.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/zjets.el*.root
do
	./plotDistribution.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/zjets.mu*.root
do
	./plotDistribution.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/zprime*.el_selected.root
do
	./plotDistribution.exe $filename;
done
for filename in /net/e4-nfs-home.e4.physik.tu-dortmund.de/home/zprime/koch_breer_schulte/output_runSelection/zprime*.mu_selected.root
do
	./plotDistribution.exe $filename;
done
