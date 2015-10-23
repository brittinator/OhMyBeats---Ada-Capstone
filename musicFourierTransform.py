from scipy import fft, arange
from scipy.io import wavfile # for chunking sounds into time slices
import pyaudio # to play audio
import wave # for opening wavefiles
import serial # for serial communication
import time # for timing things/time delays on python side
# import sys
# -------------------------------------------------
def returnSpectrum(y,Fs):
    """
    Plots a Single-Sided Amplitude Spectrum of y(t)
    y = wavefile in array form
    Fs = sample rate, probably 44100
    """

    n = len(y) # length of the signal
    k = arange(n) # array from [0, 1, 2, ... n-1]
    T = n/float(Fs) # need to make Fs a float so T can be 0.xx decimal

    if y.ndim > 1:
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
    """normalizing buckets - 0 is no leds lit, 10 is all 10 leds in a strip lit"""
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
    formatted = ""
    stringArray = []
    for n in array:
        # convert array into a string
        numAsString = str(n)
        if len(numAsString) < 2:
            # add leading zeros to numbers
            numAsString = '0' + numAsString
        stringArray.append(numAsString)

    return ''.join(stringArray)

# -------------------------------------------------
def buckets(spectrumHash):
    """Mundges data from a huge list of frequency data into 6 distinct buckets"""

    # Sub Bass: 20 to 60 Hz
    # Bass1: 60 to 150 Hz
    # Bass2: 150 to 250 Hz
    # Low Midrange: 250 to 375 Hz
    # Midrange: 275 to 500 Hz
    # Treble: 500 Hz to 2 kHz

    subBass = averaging(20, 60, spectrumHash)
    bass1 = averaging(60, 150, spectrumHash)
    bass2 = averaging(150, 250, spectrumHash)
    lowMidrange = averaging(250, 375, spectrumHash)
    midrange = averaging(385, 500, spectrumHash)
    treble = averaging(500, 2000, spectrumHash)

    equalizer = []

    # normalizing buckets - 0 is no leds lit, 10 is all 10 leds in a strip lit
    beforeNormalization = [subBass, bass1, bass2, lowMidrange, midrange, treble]
    hi = max(beforeNormalization)
    lo = min(beforeNormalization)

    normalized = []

    for n in beforeNormalization:
        norms = int((((n-lo)/(hi-lo)))*10)
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
# -------------------------------------------------
""" Below is where we execute the code to run the fft
and send the arrays of LEDs to light to the Arduino"""

sampFreq, snd = wavfile.read(drum)

duration = len(snd)/sampFreq # in seconds
second = len(snd)/duration # second translation into file size
window_size = second/20 # break up snd into chunks
connection = '/dev/cu.usbmodem1411'

print duration
print window_size

ser = serial.Serial(connection, 115200, timeout=1)

#open a wav format music
f = wave.open(piano,"rb") #rb - read binary
#instantiate PyAudio
p = pyaudio.PyAudio()

# define callback (2)
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
time.sleep(.5)
for i in range(0, len(snd)-(window_size*2), (window_size*2)): # range makes an array auto
    numSlices += 1
    spectrum = returnSpectrum(snd[i:i+window_size], sampFreq)
    array = buckets(spectrum)
    data = formatData(array)
    print data
    ser.write(data)
    # time.sleep(1)

# wait for stream to finish (5)
while stream.is_active():
    time.sleep(0.1)

ser.write("000000000000") # turning LEDs off
#stop stream
stream.stop_stream()
stream.close()
f.close()

#close PyAudio
p.terminate()