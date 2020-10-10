# Aircopter Project

This project was done in association with the IEEE Student Branch on the UCLA campus.
This is the second iteration of the project. Due to the 2020 global pandemic, this
project was cut short for the 2019-2020 academic year and will resume in the 2020-
2021 academic year.

The goal of the project was to: 1. Design and assemble a custom PCB for a drone,
2. Write a program to hover the drone, then fly the drone. Because of the nature
of the project, the PCB was required to be small and compact (meaning SMD soldering
was needed) and the program needed to be quick and responsive.

#### Note: 

This version of the project was cut short due to the 2020 pandemic. The code was still
written and the board was still designed and printed but we were not able to assemble
and solder the final product because we were then living off-campus and all campus
activities we're mandated to be put on hold.

### Hardware Selection Choices:

**MCU**: The main chip is the model STM32F405. This was chosen for its ideal balance
between size and functionality. It is able to support all the needed sensors and
motor drivers for our drone and can be powered by a 3.3v supply which closely
matches the 3.7v of standard drone batteries (3.7v is stepped down to 3.3 using
a voltage regulator). Additionally, this chip was more ideal than other chips of
similar style because it handles floating point calculations better which allows
for simplicity and efficiency when writing the program.

**Voltage Regulator**: The voltage regulator used is the LTC3246MPMSE from Linear 
Technology. This component was chosen since it is a buck boost regulator with
the ability to step down or step up voltage as we need in this application. This
component is larger, more expensive, and more complex than the regulator used in
the first iteration but it accomplishes the same purpose while being much easier
to solder onto the board (no heat guns required).

**Wireless Module**: The wireless module used is the nrf24l01 which is standard, easy
to use, and familiar so we used it in this application since it fits well with the
acclerometer module.

**Accelerometer/Gyroscope**: The module used is the mpu6050 which is standard, easy to
use, and familiar so we used it in this application since it fits well with the
wireless module.

**Oscillator**: We opted for an abracon 25mhz crystal oscillator. The frequency fits 
the range of our operation and takes up a relatively small amount of space on
the PCB. In this iteration, a through-hole component was chosen because it could
be added more compactly without needing large pads on the PCB outside the area of
the oscillator.

**Passive Components**: For the resistors, capacitors, and inductors, we primarily
used parts with the package size 0603 which would fit the board without being
overly difficult to solder. Each piece was checked for its operating voltages as 
well as the operating temperatures to make sure no issues would arise. Additonally,
we tried to get components that were less dependent on external passive components
so we could make the PCB more compact/efficient.

### Hardware Design Choices:

**Motors**: In this design, we opted to place the 4 motor JST connectors along the left
side of the board because this would reduce the amount of "prime-real-estate" occupied
by the motor drivers. Also, we saved a significant amount of space on the PCB by
moving the motor drivers to the backside, under the JST rather than having the drivers
being on the same side (which means we cannot overlap the area occupied by the JSTs).

**Battery**: The JST of the battery is placed directly right of the motors. This is
important since its a central component and that position allows it easy access to
the motors and the rest of the PCB.

**Voltage Regulator**: The voltage regulator is placed below the battery JST, also in a
central position. This is key because we are able to define the 3.7V and 3.3V polygons
without complexity, and therefore reduing bottlenecks. Because the voltage regulator
is dependent on several passive components, it is placed in an open space with the
passive components compactly fit around it, without creating any major bottlenecks.

**Polygons**: Because of the location of the voltage divider, we are able to make an easy
distinction between the 3.3v, 3.7v, motor ground, and general ground planes. Everything
left of the voltage regulator is either the 3.7v or motor ground planes while everything
right is either 3.3v or general ground.

**MCU**: We chose to turn the MCU 45 degrees for a few reasons:
  1. Having the MCU turned actually signficantly reduced the bottlenecks as key 
  components had more direct access to the 3.3v plane and we had less "dead-ends" in 
  the plane. This gave extra space to work in that would not present a threat of 
  bottlenecking.
  2. The traces coming out of the MCU can be shorter and more optimized for the key
  components.
  3. We thought it looked neat!

**Oscillator**: The oscillator is placed as physically close to the MCU as possible with
relatively thick traces in order to prevent that signal from being overly distorted.

**Wireless Module/Accelerometer**: Because these two modules are not raised to the same
level, they can be overlapping on the PCB and not cause any issues. The wireless
module is placed along the right side while the accelerometer is placed along the
bottom because this allows for easy access to the respective connections on the MCU.

**Other items**: This includes the programmer and the reset switch. Since neither of them
are crucial in the operation of the drone, they are place along the top with less
direct connections (meaning the traces and planes for key components are better
optimized). Additionally, this iteration includes a tx and rx connection which will
be useful for debugging.

**Bottlenecks**: For this version, we were able to get away with no major bottlenecks
in the planes thanks to the reduction of passive components, better placements,
and the 45 degree MCU.

**Decoupling Capacitors**: The decoupling capacitors are placed in such a way that they
are close to the components they stabalize. This also helped in reducing bottlenecks
as passive components were not cutting up the planes

### Possible Improvements:

Some components are not optimally placed meaning the traces are not direct. This can
be solved by either tweaking the placement or choosing different compatible pins on
the MCU. Also the placement of the motors and battery mean that the lower motors are
further away from the power source, meaning potentially higher noise. Furthermore,
adding some LEDs would be useful for debugging (we have the room to do so).
