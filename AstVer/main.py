import sensor, image, time, math,lcd
from pyb import Pin, Timer #, LED
height = 120
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
#sensor.set_windowing(320,240))
sensor.skip_frames(time = 2000)
#sensor.set_auto_gain(False) # must be turned off for color tracking
#sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()
red_block_x=1
green_block_x=2
blue_block_x=3

Light = Pin('P0',Pin.OUT_PP,Pin.PULL_UP)
Light.low()
message=000

#led_r=LED(1)
#led_g=LED(2)
#led_b=LED(3)


threshold_index = 0 # 0 for red, 1 for green, 2 for blue

# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
# The below thresholds track in general red/green/blue things. You may wish to tune them...
thresholds = [(35, 70, 27, 127, -46, 83), # generic_red_thresholdsup
              (33, 62, -42, -4, -35, 13), # generic_green_thresholds
              (8, 40, 10, 56, -128, -27),  # generic_blue_thresholds
              (35, 70, 27, 127, -46, 83), #RD
              (33, 62, -42, -4, -35, 13), #GD
              (8, 40, 10, 56, -128, -27) ] #BD



#################### Openmv数据处理 ###################
# 直接向arduino发送处理好的数据
# 红-1 绿-2 蓝-3

PP_s = "123"        # 色环顺序（固定） 逆时针方向

# 需要获取的顺序
above_order=0     # 上层物料抓取顺序
bottom_order=0  # 下层物料抓取顺序    二维码

Aorder=0          # 上层物料放置顺序
Border=0      # 下层物料放置顺序


Pos1 = "000"     # 上层放置位置
Pos2 = "000"     # 下层放置位置


def find_min(blobs):
    min_size=1000000
    for blob in blobs:
        if blob[2]*blob[3] <= min_size:
            min_blob=blob
            min_size = blob[2]*blob[3]
    return min_blob

# 输入： QRCode|任务码  Pos|物料放置位置
# 求 QRCode在Pos中的顺序
def Index_find(QRCode,Pos):   # 解算出机械臂的动作顺序
    result = 0
    for i in range(3):
        cc =  Pos.find(QRCode[i])+1
        #print(cc)
        result = result*10 + cc
    return result

#Move1 = Index_find(QRCode1,Pos1)    # 解算出机械臂抓取上层物料的动作顺序
#Move2 = Index_find(QRCode2,Pos2)	# 解算出机械臂抓取下层物料的动作顺序


#################### UART TO ARDUINO ###################
# 导入串口
from pyb import UART
# 串口3  [TX-P4, RX-P5]
uart = UART(3,9600,timeout_char = 50)   # 100 可改

# 串口收发数据
recv_data = ""     # 串口接收的数据
WL_flag = 0       # 获取上层物料放置顺序标志位


def Uart_recv():  # 串口接收数据
    global WL_flag

    if (uart.any()):   # 更新串口接收数据
        recv_data = eval(str(uart.read()))

        print(recv_data)
        #uart.write(recv_data)
        if (recv_data!="") :
            print("Openmv has recved CMD data.")
            if ("ST" in recv_data):
                WL_flag = 1
                print("Task Start!")

            if ("ED" in recv_data):
                WL_flag = 0
                print("Task End!")


#WL_flag = 1
# 主循环
while(True):
    clock.tick()
    img = sensor.snapshot().replace(vflip=True,       #水平翻转
                                    hmirror=True,     #镜像翻转
                                    transpose=False)

    Uart_recv() # 串口接收（接收arduino发送的指令）



    while(WL_flag): # 识别物料    WL_flag
        #uart.write("WL_"+Pos1+Pos2+"\r\n")
        #led_r.on()
        #led_g.on()
        #led_b.on()
        Light.high()
        clock.tick()
        #light = Timer(2, freq=50000).channel(1, Timer.PWM, pin=Pin("P6"))
        #light.pulse_width_percent(100) # 控制亮度 0~100
        img = sensor.snapshot().replace(vflip=True,       #水平翻转
                                    hmirror=True,     #镜像翻转
                                    transpose=False)
        for r in img.find_blobs([thresholds[0]],roi=[0,55,320,70],pixels_threshold=200, area_threshold=200, merge=True):
            # These values depend on the blob not being circular - otherwise they will be shaky.

            # These values are stable all the time.
            img.draw_rectangle(r.rect())
            img.draw_cross(r.cx(), r.cy())
            # Note - the blob rotation is unique to 0-180 only.
            img.draw_keypoints([(r.cx(), r.cy(), int(math.degrees(r.rotation())))], size=20)
        #print(clock.fps())
            red_block_x = r.cx()
        for g in img.find_blobs([thresholds[1]],roi=[0,55,320,70], pixels_threshold=200, area_threshold=200, merge=True):
            # These values depend on the blob not being circular - otherwise they will be shaky.

            # These values are stable all the time.
            img.draw_rectangle(g.rect())
            img.draw_cross(g.cx(), g.cy())
            # Note - the blob rotation is unique to 0-180 only.
            img.draw_keypoints([(g.cx(), g.cy(), int(math.degrees(g.rotation())))], size=20)
        #print(clock.fps())
            green_block_x = g.cx()

        for b in img.find_blobs([thresholds[2]],roi=[0,55,320,70], pixels_threshold=200, area_threshold=200, merge=True):
            # These values depend on the blob not being circular - otherwise they will be shaky.

            # These values are stable all the time.
            img.draw_rectangle(b.rect())
            img.draw_cross(b.cx(), b.cy())
            # Note - the blob rotation is unique to 0-180 only.
            img.draw_keypoints([(b.cx(), b.cy(), int(math.degrees(b.rotation())))], size=20)
            blue_block_x = b.cx()
            #if g.cx()==None:
             #   print(1)
            #elif g.cx()!=None：
            if int(red_block_x)<int(green_block_x) and int(green_block_x)<int(blue_block_x):
                if Border!=123:
                        #print("上层物料顺序为：红绿蓝")
                        #print(red_block_x,green_block_x,blue_block_x)
                        #print(blob.h(),blob.w() )
                        Border=123
            elif int(blue_block_x)<int(green_block_x) and int(green_block_x)<int(red_block_x):
                if Border!=321:
                        #print("上层物料顺序为：蓝绿红")
                        #print(red_block_x,green_block_x,blue_block_x)
                        #print(blob.h(),blob.w() )
                        Border=321
            elif int(red_block_x)<int(blue_block_x) and int(blue_block_x)<int(green_block_x):
                if Border!=132:
                        #print("上层物料顺序为：红蓝绿")
                        #print(red_block_x,green_block_x,blue_block_x)
                        #print(blob.h(),blob.w() )
                        Border=132
            elif int(green_block_x)<int(blue_block_x) and int(blue_block_x)<int(red_block_x):
                if Border!=231:
                        #print("上层物料顺序为：绿蓝红")
                        # print(red_block_x,green_block_x,blue_block_x)
                        #print(blob.h(),blob.w() )
                        Border=231
            elif int(blue_block_x)<int(red_block_x) and int(red_block_x)<int(green_block_x):
                if Border!=312:
                        #print("上层物料顺序为：蓝红绿")
                        #print(red_block_x,green_block_x,blue_block_x)
                        #print(blob.h(),blob.w() )
                        Border=312
            elif int(green_block_x)<int(red_block_x) and int(red_block_x)<int(blue_block_x):
                if Border!=213:
                        #print("上层物料顺序为：绿红蓝")
                        #print(red_block_x,green_block_x,blue_block_x)
                        #print(blob.h(),blob.w() )
                        Border=213
            #print(Aorder)########################################得到下层物料
                #if int(red_block_x)>int(blue_block_x):
                 #   print(1)

                #a = int(green_block_x) - int(red_block_x)
                #b = int(red_block_x) - int(blue_block_x)
                #c = int(green_block_x) - int(blue_block_x)
                #print("%d,%d,%d,%d,%d,%d"%(int(red_block_x),int(green_block_x),int(blue_block_x),a,b,c))
                #print(Aorder)
            if (Border==123) or (Border==132) or (Border==213) or (Border==231) or (Border==312) or (Border==321):
                for r in img.find_blobs([thresholds[3]],roi=[0,110,320,80],pixels_threshold=200, area_threshold=200, merge=True):
                    # These values depend on the blob not being circular - otherwise they will be shaky.

                    # These values are stable all the time.
                    img.draw_rectangle(r.rect())
                    img.draw_cross(r.cx(), r.cy())
                    # Note - the blob rotation is unique to 0-180 only.
                    img.draw_keypoints([(r.cx(), r.cy(), int(math.degrees(r.rotation())))], size=20)
                    #print(clock.fps())
                    red_block_x = r.cx()

                for g in img.find_blobs([thresholds[4]],roi=[0,110,320,80], pixels_threshold=200, area_threshold=200, merge=True):
                    # These values depend on the blob not being circular - otherwise they will be shaky.

                    # These values are stable all the time.
                    img.draw_rectangle(g.rect())
                    img.draw_cross(g.cx(), g.cy())
                    # Note - the blob rotation is unique to 0-180 only.
                    img.draw_keypoints([(g.cx(), g.cy(), int(math.degrees(g.rotation())))], size=20)
                    #print(clock.fps())
                    green_block_x = g.cx()

                for b in img.find_blobs([thresholds[5]],roi=[0,110,320,80], pixels_threshold=200, area_threshold=200, merge=True):
                    # These values depend on the blob not being circular - otherwise they will be shaky.

                    # These values are stable all the time.
                    img.draw_rectangle(b.rect())
                    img.draw_cross(b.cx(), b.cy())
                    # Note - the blob rotation is unique to 0-180 only.
                    img.draw_keypoints([(b.cx(), b.cy(), int(math.degrees(b.rotation())))], size=20)
                    blue_block_x = b.cx()

                    if int(red_block_x)<int(green_block_x) and int(green_block_x)<int(blue_block_x):
                        if Aorder!=123:
                                #print("上层物料顺序为：红绿蓝")
                                #print(red_block_x,green_block_x,blue_block_x)
                                #print(blob.h(),blob.w() )
                                Aorder=123
                    elif int(blue_block_x)<int(green_block_x) and int(green_block_x)<int(red_block_x):
                        if Aorder!=321:
                                #print("上层物料顺序为：蓝绿红")
                                #print(red_block_x,green_block_x,blue_block_x)
                                #print(blob.h(),blob.w() )
                                Aorder=321
                    elif int(red_block_x)<int(blue_block_x) and int(blue_block_x)<int(green_block_x):
                        if Aorder!=132:
                                #print("上层物料顺序为：红蓝绿")
                                #print(red_block_x,green_block_x,blue_block_x)
                                #print(blob.h(),blob.w() )
                                Aorder=132
                    elif int(green_block_x)<int(blue_block_x) and int(blue_block_x)<int(red_block_x):
                        if Aorder!=231:
                                #print("上层物料顺序为：绿蓝红")
                                # print(red_block_x,green_block_x,blue_block_x)
                                #print(blob.h(),blob.w() )
                                Aorder=231
                    elif int(blue_block_x)<int(red_block_x) and int(red_block_x)<int(green_block_x):
                        if Aorder!=312:
                                #print("上层物料顺序为：蓝红绿")
                                #print(red_block_x,green_block_x,blue_block_x)
                                #print(blob.h(),blob.w() )
                                Aorder=312
                    elif int(green_block_x)<int(red_block_x) and int(red_block_x)<int(blue_block_x):
                        if Aorder!=213:
                                #print("上层物料顺序为：绿红蓝")
                                #print(red_block_x,green_block_x,blue_block_x)
                                #print(blob.h(),blob.w() )
                                Aorder=213

                #if int(Aorder)!=int(Border):
                    ##print("%dand%d"%(int(Aorder),int(Border)))
                    #Above=Aorder
                    #Below=Border

                print("%dand%d"%(int(Aorder),int(Border)))
                if int(Aorder)!= 0 and int(Border)!=0 :
                    print("OK!")

                    Pos1 = str(Border)
                    Pos2 = str(Aorder)

                    # 2）当物料识别成功后 【处理数据，发送数据】
                    print("WL_"+Pos1+Pos2)
                    uart.write("W"+Pos1+Pos2+"b\r\n")
                    WL_flag = 0;
                    #led_r.off()
                    #led_g.off()
                    #led_b.off()
                    Light.low()
                    print("Done! ")









