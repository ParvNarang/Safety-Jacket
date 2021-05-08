# Safety-Jacket
Safety Jacket which gives an electric shock to the assailant when touched and sends your current location using GPS-GSM module to numbers fed in the device.

This is a safety jacket designed for women’s safety, to protect them from assaults.Once a user activates the jacket, it gives an electric 
shock to anyone who touches the jacket.The user can press the panic button on the jacket which activates the boost electric shock circuit, 
emergency buzzer and GPS-GSM module present in the jacket.Loud noise and electric shock act as a deterrent while current location of the user, 
in the form of a google-maps link, is sent to the phone numbers feeded in the device. The jacket also has an external taser to add another layer of safety.

# Initial Blueprint
![1606732375366](https://user-images.githubusercontent.com/56078295/117553592-1a5c1480-b070-11eb-89e2-f23001ce58d3.jpg)

# Prototype
![WhatsApp Image 2020-12-08 at 10 41 07](https://user-images.githubusercontent.com/56078295/117553619-3fe91e00-b070-11eb-8734-07f296873adb.jpeg)

# Components and Specifications
The jacket consists of 3 sections -
  - JacketShockModule
  - GPS-GSM Module
  - Taser
  
# Working
It is a wearable that is designed for women’s safety and has hidden electric conducting nodes which give an electric shock of around 2400V on full charge and a current of 5-6 milliampere. The shock circuit is powered using a 4V battery and whenever the jacket is touched it gives a shock to any assailant. The jacket has suitable insulation inside to prevent self shock to the user’s body.
It also activates the emergency buzzer on the jacket and sends the current location of the user to family members and police in the form of a google maps link using the GPS-GSM module.
The GPS-GSM module uses an active SIM and is programmed with a microcontroller “Arduino Nano” and is run by a 7.4 V li-ion battery. Whenever the button is pressed the module grabs the current coordinates of the person using the GPS module and generates a map link using the latitude and longitude coordinates. The GSM module then sends those coordinates and the map link to the phone numbers feeded in the module with the help of a sim. The sim needs to be active and working. All this happens quickly with just a click of a push button.
The jacket module and the GPS-GSM module are set in the pocket of the jacket cased inside the small zipper.
The taser also uses a boost converter which converts the potential difference from 3.7V/ 6V/ 9V to 400kV with a current of 0.5 A. It can be easily activated with the help of a rocker switch.
