#!/usr/bin/env python3

from keras.models import load_model
from keras import backend as K
from tkinter import *
#from PIL.ImageGrab import grab
from pyscreenshot import grab
#from PIL import Image, ImageOps
import numpy as np
import tensorflow as tf
K.set_image_data_format('channels_last')

# loading model
clf = load_model('cnn_model.h5')
print('Model loaded')

# init'ing tkinter stuff
root = Tk()
root.title('Draw')
canv = Canvas(root, width=400, height=400, bg='black')
canv.pack()
lbl = Label(root, text='', font='Arial 100')
lbl.pack()
PS = 7 # pen size
dots = []

## TODO: adjust pen's width based on bbox size

def draw(event):
    x, y = event.x, event.y
    if dots:
        xprev, yprev = dots.pop()
        canv.create_line(xprev, yprev, x, y, fill='white', width=2*PS+1)
    canv.create_oval(x-PS, y-PS, x+PS, y+PS, outline='white', fill='white')
    dots.append((x, y))

def clear(event):
    dots.clear()

def redraw(event):
    canv.delete('all')
    lbl.config(text='')

def predict(event):
    sample = preprocess(root).reshape((1, 28, 28, 1)) / 255
    prediction = np.argmax(clf.predict(sample))
    lbl.config(text=str(prediction))

def preprocess(root):
    x, y = root.winfo_rootx(), root.winfo_rooty()
    im = grab(bbox=(x+2, y+2, x+398, y+398)).convert('L')
    # im = ImageOps.invert(Image.open('six.jpg').convert('L'))
    im.show()
    bbox = list(im.getbbox())
    w, h = bbox[2]-bbox[0], bbox[3]-bbox[1]
    if w > h:
        bbox[1] -= (w-h)//2
        bbox[3] += (w-h)//2
    else:
        bbox[0] -= (h-w)//2
        bbox[2] += (h-w)//2
    im = im.crop(bbox).resize((400, 400))
    pix = np.asarray(im)
    pix = [[pix[i*20: i*20+20, j*20: j*20+20]
            for j in range(20)] for i in range(20)]
    gs = np.zeros((20, 20))
    mass = np.zeros(2)
    for i in range(20):
        for j in range(20):
            gs[i][j] = min(255, np.sum(pix[i][j])/350)
            mass += np.array([i, j])*gs[i][j]
    mass = (mass/np.sum(gs)).astype('uint8')
    sample = np.zeros((28, 28), dtype='float32')
    for i in range(20):
        for j in range(20):
            k = i + 14 - mass[0]
            l = j + 14 - mass[1]
            sample[k][l] = gs[i][j]
    return sample


root.bind('<B1-Motion>', draw)
root.bind('<ButtonRelease-1>', clear)
root.bind('<space>', redraw)
root.bind('<Return>', predict)
root.mainloop()
