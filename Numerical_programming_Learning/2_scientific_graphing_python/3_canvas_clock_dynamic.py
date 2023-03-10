from tkinter import *

root = Tk()  
root.title("Canvas")

Nx=300
Ny=300   #canvas size
a=Canvas(root, width=Nx,height=Ny, bg = "white")
a.pack()

a.create_line(150,150,100,100,fill="black",arrow=LAST, width=3)
a.create_line(150,150,150,250,fill="red",arrow=LAST)
a.create_rectangle(50, 50, 250, 250, width=2)
a.create_oval(50,50,250,250)
a.create_text(150,75,text = "10:30")

root.mainloop()  #enter tkinter event loop
