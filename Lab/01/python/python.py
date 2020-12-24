import json
import requests
from tkinter import *

#цвета
color1="#f5f5dc"
color2="#ffc31f"

#на /raw  json с данными о погоде
def Reloading(event=None):
	r = requests.get('http://localhost:3000/raw').content.decode("UTF8")
	data = json.loads(r)
	description.config(text=str(data["description"]))
	temperature.config(text=str(data["temperature"]) + "°C")

root = Tk()
root.title("Погода в Симферополе")
root.bind("<Button-1>", Reloading)
root.geometry("250x300")

top = Frame(root, bg=color2)
middle = Frame(root, bg=color1)
bottom = Frame(root, bg=color2, height=60)

top.pack(side=TOP, fill=X)
middle.pack(expand=True, fill=BOTH)
bottom.pack(side=BOTTOM, fill=X)

town = Label(top, font=("Times New Roman", 14), text="Симферополь", bg=color2)
description = Label(top, font=("Arial", 14), bg=color2)
temperature = Label(middle, font=("Arial", 70), bg=color1)

town.pack()
description.pack()
temperature.pack(expand=True)

Reloading()
root.mainloop()