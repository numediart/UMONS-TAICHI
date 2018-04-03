# UMONS-TAICHI
[![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-nc-sa/4.0/)
## Presentation
UMONS-TAICHI is a large 3D motion capture dataset of Taijiquan martial art gestures (n = 2200 samples) that includes 13 classes (relative to Taijiquan techniques) executed by 12 participants of various skill levels. Participants levels were ranked by three experts on a scale of [0-10]. The dataset was captured using two motion capture systems simultaneously: 1) Qualisys system, a sophisticated motion capture system of 11 Oqus cameras that tracked 68 retroreflective markers at 179 Hz, and 2) Microsoft Kinect V2, a low-cost markerless sensor that tracked 25 locations of a person’s skeleton at 30 Hz. Data from both systems were synchronized manually. Qualisys data were manually corrected, and then processed to complete any missing data. Data were also manually annotated for segmentation. Both segmented and unsegmented data are provided in this database. This article details the recording protocol as well as the processing and annotation procedures. The data were initially recorded for gesture recognition and skill evaluation, but they are also suited for research on synthesis, segmentation, multi-sensor data comparison and fusion, sports science or more general research on human science or motion capture. A preliminary analysis has been conducted by Tits et al. (2017) [1] on a part of the dataset to extract morphology-independent motion features for gesture skill evaluation. Results of this analysis are presented in their communication: “Morphology Independent Feature Engineering in Motion Capture Database for Gesture Evaluation” (https://doi.org/10.1145/3077981.3078037) [1].

## Processing
### Qualisys
Qualisys data were processed manually with [Qualisys Track Manager](http://www.qualisys.com/software/qualisys-track-manager/).

Missing data (occluded markers) were then recovered with an automatic recovery method: [MocapRecovery](https://github.com/titsitits/MocapRecovery).

Data were annotated for gesture segmentation, using the [MotionMachine](https://github.com/numediart/ofxMotionMachine) framework (C++ [openFrameworks](http://openframeworks.cc/) addon). The code for annotation can be found [here](https://github.com/numediart/ofxMotionMachine/tree/master/mmTutorial_4_Annotation). Annotations were saved as ".lab" files (see Download section).

Data were then segmented (output files: TSV) using the Matlab code provided in this repository (see folder "Segmentation"). This code requires the [MoCap Toolbox for Matlab](https://www.jyu.fi/hytk/fi/laitokset/mutku/en/research/materials/mocaptoolbox/), and optionally the [MoCap Toolbox Extension](https://github.com/titsitits/MocapRecovery/tree/master/MoCapToolboxExtension) for data visualization.

### Kinect

The Kinect data were recorded with [Kinect Studio](https://msdn.microsoft.com/en-us/library/hh855389.aspx). Skeleton data were then extracted with [Kinect SDK](https://www.microsoft.com/en-us/download/details.aspx?id=44561) and saved into “.txt” files which contain several lines corresponding to each captured frame. Each line contains one integer number (ms), relative to the moment when the frame was captured, followed by 3 x 25 float numbers corresponding to the 3-dimentional locations of the 25 body joints.

Kinect data were then manually synchronized with Qualisys data, using the code provided in this repository (see folder "Synchronization"). This code requires the [MotionMachine](https://github.com/numediart/ofxMotionMachine) framework.

## Download

Qualisys data (.c3d): http://tcts.fpms.ac.be/~tits/C3D.zip

Segmented Qualisys data (.tsv): http://tcts.fpms.ac.be/~tits/Segmented_TSV.zip

Kinect data (.txt): http://tcts.fpms.ac.be/~tits/Kinect.zip

Labels (.lab):  http://tcts.fpms.ac.be/~tits/Labels.zip


All files (except TSV for now) can be used with the [MotionMachine](https://github.com/numediart/ofxMotionMachine) framework.

## References
Dataset submitted to the Journal Data in Brief, reference will be added upon publication acceptance.

[1]	M. Tits, J. Tilmanne, T. Dutoit, Morphology Independent Feature Engineering in Motion Capture Database for Gesture Evaluation, Proc. 4th Int. Conf. Mov. Comput.  - MOCO ’17. (2017) 1–8. https://doi.org/10.1145/3077981.3078037 
