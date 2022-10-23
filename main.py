import time
from neopixel import Neopixel
from machine import Timer
import random

numpix = 576
pixels = Neopixel(numpix, 0, 28, "GRB")

 
green = (0, 255, 0)
blue = (0, 0, 255)
red = (255, 0, 0)
black=(0,0,0)
white=(255,255,255)
dropColor=(255,255,255)
pixels.brightness(100)
pixels.fill(black)

timer=Timer(-1)
timer2=Timer(-1)
timer3=Timer(-1)
timer4=Timer(-1)

def SetStrip(_Start,_End,Color1,Color2):
    pixels.set_pixel_line(_Start,_End,black) 
    for x in range(12):
        start=(_Start)+(x*12)
        end=(_Start+12)+(x*12)
        if(end>_End):
            end=_End
        if x%2==0:   
            pixels.set_pixel_line(start,end,Color1)
        else:
            pixels.set_pixel_line(start,end,Color2)

def SetStripModulo(_Start,_End,Color1,Color2,Modulo):
    pixels.set_pixel_line(_Start,_End,black) 
    for x in range(_Start,_End):
        if x%Modulo==0:   
            pixels.set_pixel(x,Color1)
        else:
            pixels.set_pixel(x,Color2)
 
SetStrip(0,143,dropColor,black)
SetStrip(144,287,red,green)
SetStrip(288,431,red,blue)
SetStrip(432,575,dropColor,black)

Toggle=False
def Pattern1(t):
    Color1=(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255));
    Color2=(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255));
    SetStrip(144,287,Color1,Color2)
    SetStrip(288,431,Color1,Color2)
 
def Pattern2(t):
    Color1=(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255));
    SetStrip(144,287,Color1,black)
    SetStrip(288,431,Color1,black)
 
def Pattern3(t):
    global Toggle
    Toggle=not Toggle;

def Pattern4(t):
    Color1=(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255));
    Color2=(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255));
    mod=random.randint(1,8) 
    SetStripModulo(144,287,Color1,Color2,mod)
    SetStripModulo(288,431,Color1,Color2,mod)
   
timer.init(period=4000, mode=Timer.PERIODIC, callback=Pattern1)
timer2.init(period=8100, mode=Timer.PERIODIC, callback=Pattern2)
timer3.init(period=10000, mode=Timer.PERIODIC, callback=Pattern3)
timer4.init(period=15100, mode=Timer.PERIODIC, callback=Pattern4)

while True: 
    pixels.ShiftLeft(0,144,6)    
    pixels.ShiftRight(432,575,6)
    if(Toggle):
        pixels.ShiftLeft(144,287,3)
        pixels.ShiftRight(288,431,3)
    else:
        pixels.ShiftRight(144,287,3)
        pixels.ShiftLeft(288,431,3)
        
    time.sleep(.1)
    pixels.show() 