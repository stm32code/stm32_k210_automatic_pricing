import sensor, image, time, lcd, gc, cmath
from maix import KPU
from maix import GPIO
from fpioa_manager import fm
from machine import UART,Timer


lcd.init()                          # Init lcd display
lcd.clear(lcd.RED)                  # Clear lcd screen.

#注册IO和构建LED对象
fm.register(35, fm.fpioa.GPIO0)
LED_B = GPIO(GPIO.GPIO0, GPIO.OUT)
#计数变量
Counter=0
fruits=0

 
 


while(True):
    gc.collect()

    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.

    img256240 = img.copy((32, 0, 256, 240))
    a = img256256.draw_image(img256240,0,8)
    del img256240

    img128128 = img256256.resize(128,128)
    img128128.pix_to_ai()

    result = kpu.run_with_output(img128128, getlist=True)
    del img128128
    #print(result)

    fps = clock.fps()

    result = kpu.softmax(result)
    #print(result)

    _max_val = max(result)
    _max_idx = result.index(_max_val)

    # print(labels[_max_idx], _max_val)

    img.draw_string(32, 0, labels[_max_idx] + " %.3f"%_max_val,0xFFFF,2.0)
    if(labels[_max_idx]) == "apple":
        fruits = 1
    if(labels[_max_idx]) == "banana":
        fruits = 2
    if(labels[_max_idx]) == "orange":
        fruits = 3

    img.draw_rectangle(32,0,256,240)
    # a = img.draw_string(0, 240 - 32, "%2.1ffps" %(fps),color=(0,60,255),scale=2.0)

    lcd.display(img)
