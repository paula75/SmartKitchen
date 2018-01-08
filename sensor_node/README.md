# Sensor

There are two different sensors used in this project.
Both are implementated on the Ateml SAM R21 Xplained Pro Board.
One the one hand NFC is used to detected the product and on the the other hand 
pressure sensors are used to measure the weight.
In this combination it is possible to detected the actual foodstuff of each product in the smart fridge.

## NFC

To read out and detect the NFC-tags the PN532 Board is used. 

## Pressure 

To measure the weight we measure the pressure and then calculated to a weight. 
For the measurment the FSR400 is used.

<p align="center">
  <img src="/images/fsr.png" width="350"/>
</p>
