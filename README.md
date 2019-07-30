# crab-tracker

This repository contains hardware designs and software to create prototypes of a low-cost, customizable ultrasonic telemetry system that can be used to relocate crabs (or other things) in shallow (<30m) aquatic environments. The basic design uses a piezoelectric ceramic crystal in each emitter to send short pulses of sound. These pulses of sound are received by four hydrophones deployed from a single watercraft, and the time delay between arrival of the sound pulses at each of the different hydrophones is used to calculate the direction from the watercraft/receiver array to the animal/emitter.

Orginally a fork of https://github.com/cabeese/crab-tracker/, this repository is intended as supplemental information for Barnes 2019. *The Crab Tracker: Ultrasonic telemetry to relocate and quantify space use of benthic estuarine crustaceans*. Western Washington University. This document contains full technical details of this project and is available in WWU's CEDAR archive here: https://cedar.wwu.edu/wwuet/.


Directory list:
/GUI - contains Python code for graphical user interface.

All code is contained in the src directory.

Design files, fabrications files, parts lists, and photos of custom electronic prototypes are available in the Hardware directory




**This repository adds hardware schematics, fabrication details, and mathematical treatment to the original repository and removes some content not directly related to the thesis publication referenced above. This repository will not be updated to maintain consistancy with the published thesis - if any additional work is conducted, a link will be provided here in this description box.**
