# Procedure

## Materials
* 1 M x Adafruit NeoPixel Digital RGB LED Strip - Black 60 LED (BLACK) [ID:1461] (http://www.adafruit.com/products/1461) - $24.95 USD
* RedBearLab Blend Micro (http://store.redbearlab.com/products/blendmicro) - $26.90 USD

NeoPixels are Adafruit's house brand of Red Green Blue (RGB) LEDs (Light Emitting Diodes) that are also addressable.  This means the pixels know their location, which makes programming what you want to display a little easier.

The Blend Micro is an Arduino microcontroller that also houses an on-board bluetooth chip.  The micro utilizes bluetooth 4.0 Low Energy, (BLE) which makes this board not as power hungry as some other arduino shields or raspberry pi dongles. The micro-controller unit (MCU) is Atmel ATmega32U4 and the BLE chip is Nordic nRF8001.

## Software/Gems
* ruby-audio gem - ruby-audio wraps around libsndfile to provide simplified sound reading and writing support to ruby programs
* fftw-3.3.4 - download this from:
* NArray : https://github.com/masa16/narray
* ruby-fftw3 - This is a ruby gem that is a wrapper to the Fastest Fourier Transfor in the West, a collection of C routines  https://rubygems.org/gems/fftw3/versions/0.3

to install ruby-audio
`gem install ruby-audio`

libsndfile
`brew install libsndfile`

to install FFTW v 3.3.4 C library
```
cd into the folder
$ cd ~/Downloads/fftw-3.3.4
$ gem install ruby-fftw3
$ less INSTALL
$ ./configure
$ make
$ make install
```

in Gemfile:
```
source 'https://rubygems.org'

gem 'fftw3'
gem 'ruby-audio', '~> 1.6.1'
gem 'narray', '~> 0.6.1.1'
```
in terminal
`install bundler`
`bundle`

* Nu Wav
NuWav is a pure ruby audio WAV file parser and writer. It supports Broadcast Wave Format (BWF), inclluding MPEG audio data, and the public radio standard cart chunk.
https://rubygems.org/gems/nu_wav/versions/0.5.1
 ` gem install nu_wav `

* Minim
https://github.com/ddf/Minim/releases/tag/v2.2.1
https://github.com/O-I/music_visualizer_intro
procedure:
https://github.com/jashkenas/ruby-processing/wiki/Installing-ruby-processing-on-the-mac
brew install wget
`gem install ruby-processing`
`rp5 setup install`
rp5 setup unpack_samples
`rp5 create visualizer `




* jruby
`rvm install jruby`
