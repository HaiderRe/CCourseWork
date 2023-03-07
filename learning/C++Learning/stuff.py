with open("C:/Users/haide/Documents/GitHub/HaiderRe.github.io/learning/HaiderRe.github.io/learning/rim.bmp",'rb') as f:
    data = bytearray(f.read())
total1 = 0 
flag = False
current = "vah"
for i in range(0, 377, 20):
    if (data == 255, 255, 255):
        total1 = total1 + 1
        flag = True
        current = "w"
    if(flag): 
        print(str(total1) + current)
            