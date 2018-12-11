# Design Skills Project (Variable Light Intensity)

## For Dr. Palmeri + TAs: 
This is a link to the demo of my LED light project:

https://photos.app.goo.gl/saTWxsfEm9hphPUx9

## Background

Hello, welcome to my repo for my LED light project for my BME590 Fundamentals of Engineering Design class. 
I have created a basic device that shines an LED light with 5 modes: 
  1. `Off`
  1. `Brightest`
  1. `Intermediate Brightness`
  1. `Least Bright`
  1. `Flashing @ 2 Hz`
 
The device is actually a Christmas ornament, where the red LED is the nose of the reindeer. The device also sings "Rudolph the Red-Nosed Reindeer."

An Arduino Uno is the software/electronics backbone of this device. The Uno handles all the logic. The circuitry is mounted on top of the Arduino Uno through a PCB that I created in Altium Designer, printed, and soldered myself. The hardware case was designed on Solidworks and printed on 3D printers. 

## What's in this repo:

There are several folders in this repo:
 * `Docs` contains the datasheets for various components that I used. 
 * `Electronics` contains the schematics of my circuitry and the Altium files I used to print my PCB
 * `Mechanical` contains the Solidworks files of my hardware case
 * `Software` contains the Arduino code I wrote to run the software logic
 * `Testing` contains links to videos demonstrating various versions of the project
 * `.gitignore` is used to set up my github pushing from my local machine
 * `Readme` is this.
 
 
# Original Assignment Document Attached Below

## Functional Specifications
* LED light that is button-activated to switch between the following operating modes:
  1. `Off`
  1. `Brightest`
  1. `Intermediate Brightness`
  1. `Least Bright`
  1. `Flashing @ 2 Hz`
* Self-contained device with LED and button exposed.
* Extra credit possibilities:
  + Battery life indicator
  + Waterproof enclosure
  + You tell us!

## Constraints
* Run on single battery up to 9 V
* Electronics connected to a single PCB (can be single- or double-sided)
* Cannot weight more than 1 lb
* Cannot have a single dimension > 6 in
* Cannot cost more than $50 to duplicate unit
* Battery must be easily replaceable

## Evaluation
* Minimize weight
* Minimize size
* Maximize `Brightest` mode
* Minimize power draw / maximize battery life
* Survive 3 foot drop with battery installed

* Create-and-maintain a GitHub project repository to maintain version history of:
  + Mechanical CAD (PDFs + more)
  + Electronic CAD (PDFs + more)
  + Software
  + Testing data
  + Design history / notes
  + Specification sheets
  + Usage notes (`README.md`)
  + Kanban board / Issues / Milestones
