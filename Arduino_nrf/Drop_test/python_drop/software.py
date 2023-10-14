import serial
from tkinter import *
from PIL import ImageTk,Image
import csv
import time

ser = serial.Serial('com6')

root=Tk()
root.title('babyshake')
root.geometry("800x450")


font = "C:/Users/Alex/Documents/myproject/Call of Ops Duty.otf"


canvas = Canvas(root, width = 700, height = 350)  
canvas.place(x=400,y=80)

img = ImageTk.PhotoImage(Image.open("picka.png"))  
canvas.create_image(-100, -40, anchor=NW, image=img) 

fieldnames = ["  ", "x_value", "y_value" , "z_value"]

with open("test_data.csv","a") as f:
    writer = csv.DictWriter(f,fieldnames=fieldnames)
    writer.writeheader()
                    

class you:
    def __init__(self,master):
        self.led=Button(master,text="Click me",bg="yellow",width=15,height=5,command=self.clickerme)
        self.led.place(x=85,y=150)
        self.data=Button(master,text="Click me",bg="yellow",width=15,height=5,command=self.clicker)
        self.data.place(x=85,y=260)
        self.label=Label(master,text="WELCOME TO DROP TEST", fg="#0F9D58", font=(font, 15))
        self.label.place(x=250,y=25)
        self.first=Label(master,text="First:").place(x=30,y=140)
        self.second=Label(master,text="Second:").place(x=17,y=250)
    def clickerme(self):
        pass
    
    def clicker(self):
        me=True
        
        while me == True:
            try:
                allitems=ser.readline().decode("utf-8")
                separateditems=allitems.split();
                print(separateditems[0], separateditems[1],separateditems[2])
                with open("test_data.csv","a") as f:
                    writer = csv.writer(f,delimiter=",")
                    writer.writerow([time.time(),separateditems[0],separateditems[1],separateditems[2]])
            except:
                print("Keyboard Interrupt")
                break
       
            
            

a=you(root)
root.mainloop()

