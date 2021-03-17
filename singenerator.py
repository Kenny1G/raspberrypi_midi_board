import matplotlib.pyplot as plt
import numpy as np
import math

#Python script to generate array of sine wave
#Do this for B0 C1 CS1 D1 DS1 E1 F1 FS1 G1 GS1 A1 AS1
#adjust  sampling rate until it ends as close to where it started as possible
sampling_rate = 14000
freq = 55
sample = 256
x = np.arange(sample)
y = (    np.sin(2 * np.pi * freq * x / sampling_rate)    + 1)  * 128
#y = ((np.sin(2 * np.pi * freq * x / sampling_rate)))
output = []
for i in y:
    output.append(hex (int(i)))
print(repr(np.array(output)))

plt.plot(x, y)
plt.xlabel('sample(n)')
plt.ylabel('voltage(V)')
plt.show()
