import pyaudio
import numpy                                         
import matplotlib.pyplot as plt

CHUNK = 1024                                                                                 
FORMAT = pyaudio.paInt16                                                                     
CHANNELS = 1
RATE = 44100
RECORD_SECONDS = 1
WAVE_OUTPUT_FILENAME = "output.wav"

frames=[]

def rec():
    global frames                                                                   
    p = pyaudio.PyAudio()
    stream = p.open(format=FORMAT,
             channels=CHANNELS,                  
             rate=RATE,    
             input=True,
             frames_per_buffer=CHUNK)                                                    
    print("* recording")                                                                     
            
    frames = []
                      
    for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
        data = stream.read(CHUNK)
        frames.append(data)
    frames = b''.join(frames)
                            
    print("* done recording")     

def pl(a=0,b=-1): 
    fig = plt.figure()
    s = fig.add_subplot(111)
    amplitude = numpy.fromstring(frames, numpy.int16)
    s.plot(amplitude[a:b])
    plt.show()
    return amplitude

