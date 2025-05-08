# Sonar-Project
This repository includes all necessary files for the Sonar Project.

This Sonar Project uses the TM4C123GH6PM Microcontroller, HC-SR04 Ultrasonic Sensor,
and the SG-90 servo motor. Its main objective is to detect objects within a 40cm distance
from the ultrasonic sensor while the sensor sweeps back and forth with the servo motor.

The ultrasonic sensor is mounted to the servo motor via a 3D-printed arm/mount.

The current servo angle and distance of a detected object are then transmitted to
a graphic which is displayed on a computer via UART so that the user can know 
where exactly the object is in relation to the sonar system.
