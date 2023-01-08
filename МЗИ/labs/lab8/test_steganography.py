from steganography import *
import matplotlib.pyplot as pyplot

encode('initial.jpg', 'encoded.jpg', '12345', 'message')
decode('initial.jpg', 'encoded.jpg', '12345')
