from tkinter import *

root = Tk()  #create Tk root widget
a= Label(root,text="Label widget used to display text") #create label widget: child to root
a.pack()  #resize label to fit text; making it more visible
root.mainloop()  #enter Tkinter event loop 
