This project was done in association with the IEEE Student Branch on the UCLA campus.
This is the second iteration of the project. Due to the 2020 global pandemic, this
project was cut short for the 2019-2020 academic year and will resume in the 2020-
2021 academic year.

The goal of the project was to: 1. Design and assemble a custom PCB for a drone,
2. Write a program to hover the drone, then fly the drone. Because of the nature
of the project, the PCB was required to be small and compact (meaning SMD soldering
was needed) and the program needed to be quick and responsive.

Hardware Selection Choices:

MCU: The main chip is the model STM32F405. This was chosen for its ideal balance
between size and functionality. It is able to support all the needed sensors and
motor drivers for our drone and can be powered by a 3.3v supply which closely
matches the 3.7v of standard drone batteries (3.7v is stepped down to 3.3 using
a voltage regulator). Additionally, this chip was more ideal than other chips of
similar style because it handles floating point calculations better which allows
for simplicity and efficiency when writing the program.

Voltage Regulator: The voltage regulator used is the LTC3246MPMSE from Linear 
Technology. This component was chosen since it is a buck boost regulator with
the ability to step down or step up voltage as we need in this application. This
component is larger, more expensive, and more complex than the regulator used in
the first iteration but it accomplishes the same purpose while being much easier
to solder onto the board.

Wireless Module: The wireless module used is the nrf24l01 which is standard, easy
to use, and familiar so we used it in this application since it fits well with the
acclerometer module.

Accelerometer/Gyroscope: The module used is the mpu6050 which is standard, easy to
use, and familiar so we used it in this application since it fits well with the
wireless module.


Passive Components: For the resistors, capacitors, and inductors, we primarily
used parts with the package size 0603 which would fit the board without being
overly difficult to solder. Each piece was checked for its operating voltages as 
well as the operating temperatures to make sure no issues would arise.

Hardware Design Choices:



Bottlenecks: There are some moderate bottlenecks in this design and also places where
the polygons have rather indirect routes. For example, some components rely on power
that comes gaps in the MCU which signficantly bottlenecks the polygons. The 3.3v 
needed by the wireless module comes from a couple vias and a route used as a bridge
rather than having a direct connection as it is cut off from the 3.3v polygon.

Voltage Regulator: The voltage regulator was small and simple but due to the exposed
pad design and its small size, was a pain to solder. This ended up being by far the
biggest hiccup in the assembly of the board and required backup components.

Decoupling Capacitors: The decoupling capacitors are not optimally placed in every
case but rather are placed to prevent bottlenecks. Capacitors for certain components
are placed near the MCU rather than the component itself.



