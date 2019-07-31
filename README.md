<p align="center">
<img src="https://github.com/31337H4X0R/crab-tracker/blob/master/doc/PrototypeSetup/graphics/ct-logo.png" alt="drawing" width="250"/>

## Ultrasonic telemetry to track underwater crustaceans
</p>

This repository contains hardware designs and software to create prototypes of a low-cost, customizable ultrasonic telemetry system that can be used to relocate crabs (or other things) in shallow (<30m) aquatic environments. The basic design uses a piezoelectric ceramic crystal in each emitter to send short pulses of sound. These pulses of sound are received by four hydrophones deployed from a single watercraft, and the time delay between arrival of the sound pulses at each of the different hydrophones is used to calculate the direction from the watercraft/receiver array to the animal/emitter.

This repository is intended as supplemental information for *Barnes 2019. The Crab Tracker: Ultrasonic telemetry to relocate and quantify space use of benthic estuarine crustaceans. Western Washington University.* As supplemental information, **this repository will not be updated with future work**. A link will be provided here if further work is conducted on the Crab Tracker. The thesis document contains full technical details of this project as well as further considerations for the use of telemetry technology, and is available in WWU's CEDAR archive here: https://cedar.wwu.edu/wwuet/.

## Directory Contents:
`/GUI` - contains Python code for the graphical user interface.

`/doc` - documentation: 
* how to configure Rasp Pi Model B
* how to wire all hardware components to each other
* detailed description of code contained in `/src`
* an overview of SPI communication between different hardware components
* discussion of signal collision probability and mitigation strategies

`/hardware` - contains

`/src` - all code other than GUI code, including:
* code to program emitters
* code to configure the GPX2 timing chip
* code to generate simulated arrival times from an emitter

All code is contained in the src directory.

Design files, fabrications files, parts lists, and photos of custom electronic prototypes are available in the Hardware directory




**This repository is a fork of https://github.com/cabeese/crab-tracker/. This repository adds hardware schematics and fabrication details to the original repository and removes some content not directly related to the thesis publication referenced above.**
