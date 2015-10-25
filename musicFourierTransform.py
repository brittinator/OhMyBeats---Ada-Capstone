"""
This file is meant to feed an Arduino Blend Micro with data.
A fast fourier transform is performed on an imcoming music file,
and then subsequentely averaged and normalized to the number of LEDs attached to the Arduino.
I have 60 (-1, I broke one pixel) neopixels attached and have 6 buckets, so 10 LEDs/bucket.
I normalize my data from 0-10.
"""
# Dependencies/libraries to import
from scipy import fft, arange
from scipy.io import wavfile # for chunking sounds into time slices
import pyaudio # to play audio
import wave # for opening wavefiles
import serial # for serial communication
import time # for timing things/time delays on python side
# -------------------------------------------------
def returnSpectrum(y,Fs):
    """
    Plots a Single-Sided Amplitude Spectrum of y(t)
    y = wavefile in array form
    Fs = sample frequency, sometimes called sampling rate; likely 44100
    """

    n = len(y) # length of the signal
    k = arange(n) # array from [0, 1, 2, ... n-1]
    T = n/float(Fs) # need to make Fs a float so T can be 0.xx decimal

    if y.ndim > 1: # stereo music has more than one dimension for stereo sound
        y = y[:,0] # taking 1st dimension, slice of matrix

    frq = k/T # two sides frequency range
    # take array, divide by num secs
    frq = frq[range(n/2)] # one side frequency range

    Y = fft(y)/n # fft computing and normalization
    Y = Y[range(n/2)]

    zipped =  zip(frq, abs(Y)) # takes 2 arrays of same size & combines

    frequencies = dict(zipped)
    return frequencies

# -------------------------------------------------
def averaging(min, max, spectrum):
    """normalizing a bucket, returns a number from 0-1"""
    length = 0
    sum = 0

    for key in spectrum:
        if key > min and key <= max:
            length += 1
            sum += spectrum[key]

    average = sum/length
    return average

# -------------------------------------------------
def formatData(array):
    """takes an array and adds a leading zero
    then joins all into a string of length 12
    so we'll consistentely send a chunk of data of length 12 to the Arduino"""

    stringArray = []
    for n in array:
        # convert number into a string
        numAsString = str(n)
        if len(numAsString) < 2:
            # add leading zeros to numbers
            numAsString = '0' + numAsString
        stringArray.append(numAsString)

    # join array items into a string of length 12
    return ''.join(stringArray)

# -------------------------------------------------
def buckets(spectrumHash):
    """Mundges data from a huge list of frequency data into 6 distinct buckets"""
    equalizer = []
    normalized = []

    LEDS = 10 # number of leds in each 'frequency bucket'
    SUBBASS =       [20, 60]            # Sub Bass: 20 to 60 Hz
    BASS1 =         [60, 150]           # Bass1: 60 to 150 Hz
    BASS2 =         [150, 250]          # Bass2: 150 to 250 Hz
    LOWMIDRANGE =   [250, 375]          # Low Midrange: 250 to 375 Hz
    MIDRANGE =      [375, 500]           # Midrange: 275 to 500 Hz
    TREBLE =        [500, 2000]        # Treble: 500 Hz to 2 kHz

    subBass =       averaging(SUBBASS[0], SUBBASS[1], spectrumHash)
    bass1 =         averaging(BASS1[0], BASS1[1], spectrumHash)
    bass2 =         averaging(BASS2[0], BASS2[1], spectrumHash)
    lowMidrange =   averaging(LOWMIDRANGE[0], LOWMIDRANGE[1], spectrumHash)
    midrange =      averaging(MIDRANGE[0], MIDRANGE[1], spectrumHash)
    treble =        averaging(TREBLE[0], TREBLE[1], spectrumHash)

    # normalizing buckets - 0 is no leds lit, 10 is all 10 leds in a strip lit
    beforeNormalization = [subBass, bass1, bass2, lowMidrange, midrange, treble]
    hi = max(beforeNormalization)
    lo = min(beforeNormalization)

    for n in beforeNormalization:
        norms = int((((n-lo)/(hi-lo)))*LEDS)
        normalized.append(norms)
    return normalized

# -------------------------------------------------
# test files to play
baseFolder = './AudioFiles/'
rock = baseFolder +'rockinthefreeworld.wav'
piano = baseFolder +'piano2.wav'
boom = baseFolder +'01 Boom Boom Pow.wav'
bassNectar = baseFolder +'05 - Lights (Bassnectar Remix).wav'
sweep = baseFolder +'sweep20-20k.wav'
hz40 = baseFolder +'40hz.wav'
hz60 = baseFolder +'60hz.wav'
hz125 = baseFolder +'125hz.wav'
hz200 = baseFolder +'200hz.wav'
hz300 = baseFolder +'300hz.wav' # questionable that this is 300hz
hz400 = baseFolder +'400hz.wav'
hz1000 = baseFolder +'1000hz.wav'
hz3000 = baseFolder +'3000hz.wav'
drum = baseFolder +'drum.wav'
light30 = baseFolder + 'light-30s.wav'
light60 = baseFolder + 'light-1m.wav'
# -------------------------------------------------
""" Below is where we execute the code to run the fft
and send the arrays of LEDs to light to the Arduino"""

sampFreq, snd = wavfile.read(light60)

second = sampFreq # sampling frequency is = second of data
window_size = second/40 # want 40 frames per second (fps), so want 40 windows/second

connection = '/dev/cu.usbmodem1411'

ser = serial.Serial(connection, 115200, timeout=1)

#open a wav format music
f = wave.open(light60,"rb") #rb - read binary

#instantiate PyAudio
p = pyaudio.PyAudio()

# define callback
def callback(in_data, frame_count, time_info, status):
    data = f.readframes(frame_count)
    return (data, pyaudio.paContinue)

#open stream
stream = p.open(format = p.get_format_from_width(f.getsampwidth()),
                channels = f.getnchannels(),
                rate = f.getframerate(),
                output = True,
                stream_callback=callback)

stream.start_stream()

numSlices = 0
for i in range(0, len(snd)-window_size, (window_size)): # range makes an array auto
    numSlices += 1
    spectrum = returnSpectrum(snd[i:i+window_size], sampFreq)
    array = buckets(spectrum)
    data = formatData(array)
    ser.write(data)
    time.sleep(0.020) # delay of 1/40fps = 0.020

# print numSlices
# wait for stream to finish (5)
while stream.is_active():
    time.sleep(0.1)

ser.write("000000000000") # turn LEDs off
#stop stream
stream.stop_stream()
stream.close()
f.close()

#close PyAudio
p.terminate()
