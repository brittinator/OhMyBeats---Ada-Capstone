# Oh My Beats Product Plan - Brittany L. Walentin

## Overview
Oh My Beats is a wearable technology that will compliment any person who wants to share their music with people in a novel way.  Oh My Beats aims to be a gender neutral accessory so as to be an inclusive as possible.

This project is a top hat that will display a live-view of your music using LEDs. The LEDs will show up as equalizer bars, and will have the ability to change color.

## Market Research
LED Dress: A fashion designer Zac Posen partnered with Made With Code for a spring 2016 collection at New York Fashion Week. They made a dress that can change the leds using programming. Thus far it is set patterns and not based on musical input.
http://www.adweek.com/adfreak/zac-posen-debuts-led-dress-made-and-female-coders-166801

## Technique
A fourier transform will be used to deconvolute the audio signals into individual frequency sinusoidal waves, representing frequncies.
![visual representation](http://www.revisemri.com/images/ft.gif)

## Frequency Buckets
Sub-bass > Bass > Low midrange > Midrange > Upper midrange > Presence and Brilliance

Sub Bass: 20 to 60 Hz
Bass: 60 to 250 Hz
Low Midrange: 250 to 500 Hz
Midrange: 500 Hz to 2 kHz
Upper Midrange: 2 to 4 kHz
Presence: 4 kHz to 6 kHz
Brilliance: 6 kHz to 20 kHz

## Target Audience
- Primarily, myself.  I love music, costuming, and programming and want to combine them all.

This hat could be desirable to individuals who enjoy going to festivals, raves, or people who want a novel costume.

- Unmet Need: A costume with a light component
- Unmet Need: A interactive wearable piece of hardware that will respond to input

## Specifications
- Version 1.0 will be gender neutral in the form of a hat to have the largest user base.
- Top Hat with bars of RGB LEDs lining the front of the hat.
- Input will be transfered via bluetooth to the hat's microcontroller, and the hat's LEDs will be turned into a visual equalizer.
- Version 1.1 (stretch goal) will include more inputs from other sources: weather, moon phase, using APIs already out there.
- Version 2.0 could be an LED skirt/kilt - now with more LEDs!

### Features
**Proof of Concept (POC)**
Will display dots on a computer monitor when music is played. These dots will each represent a single LED position.

These features will address the user's needs
- wearable item of clothing that when hooked up to a microcontroller, will light up
- these lights will correspond to a music input from an external website
- stretch goal: incorporate weather.com API to include data munging for weather forecast (display sun for sunny, cloud for cloudy, rain for rainy)

### Learning Goals
There are two main camps the learning goals land in: hardware and software.

* Hardware Goals  
  * Understanding power requirements for various parts
  * Incorporating limitations of computational power and space on a microcontroller so as to offload complex programming onto another device (laptop for now)
  * Working with bluetooth technology

* Software Goals  
  * Low level programming in C
  * Mathematical modeling of audio input (i.e. fourier transform)
  * working with ruby wrappers for C libraries
  * sending small packet of data through bluetooth

I will also have to learn how to test my hardware and software individually, and as a unit.

## Links
* [Trello Board](https://trello.com/b/vTjSs1My/oh-my-beats-don-t-you-look-wonderful)
* [FFTW3 C Library Home Page](http://www.fftw.org)
