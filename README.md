picGrabber
==========

Simple program for acquiring pairs of images for the purpose of stereo calibration.

It was developed for my master thesis to test and compare all stereo algorithms available in OpenCV.

This program servs only one purpose: to collect specified ammount of picture pairs valid for stereo calibration performed by other program.

This program is a part of a tools bundle (and a master CMake project); Other tools being:
 - sample program from OpenCV for stereo calibration (not included);
 - program performing stereo algorithm on two live cameras feed or pair of static images (in separate project);
