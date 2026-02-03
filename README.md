# Sonar System (TM4C123GH6PM)

## Introduction
This repository contains all the relevant files for the sonar system project. These include source code files (.c), header files (.h), and all the required hardware is listed. All programming was done through the Keil uVision IDE. The aim of this project was to build and implement a system that detects nearby objects using ultrasonic waves. The information from all the peripherals (i.e. distance and angle) is then transmitted via UART from a microcontroller to a graphic that displays the real-time position of an object in relation to the system - given that an object is inside the operating range of 40 centimeters.

## Results and Video Demonstration
- Demo Video: https://www.youtube.com/shorts/GWr8HmAAaNE

## Background and Methodology
The main embedded systems concepts covered in this project are:
- UART
- PWM
- Timers
- GPIO
- SysTick Timer
- Polling
- Interfacing with hardware
- Interfacing with peripherals
- Hardware - Software Integration

Our project goals were achieved by using the HC-SR04 ultrasonic sensor mounted on a 3D-printed servo arm, a SG90 servo motor, the TM4c123GH6PM microcontroller by Texas Instruments, an external 5V power supply, Keil uVision IDE for programming the microcontroller, and Processing IDE to create the graphic UI for the visuals of the radar.

## Functional Block Diagram
<img width="856" height="444" alt="image" src="https://github.com/user-attachments/assets/1e265844-ef95-4f73-80c0-8b85b3156cd7" />

## Hardware Used
<img width="922" height="417" alt="image" src="https://github.com/user-attachments/assets/3f14c039-6789-49d0-868f-362e352a1107" />


## Pinouts Used
<img width="967" height="573" alt="image" src="https://github.com/user-attachments/assets/47142542-3819-4bc1-afa2-37c12af1ce33" />

### HC-SR04 Pinout
<img width="1319" height="648" alt="image" src="https://github.com/user-attachments/assets/cbc91345-aea3-4d2b-8194-5734a81a7021" />

### HC-SR04 Timing Diagram
<img width="884" height="599" alt="image" src="https://github.com/user-attachments/assets/9d5369a0-0c94-4513-bf3e-2549f59a3416" />


### SG90 Servo Pinout
<img width="1016" height="463" alt="image" src="https://github.com/user-attachments/assets/0641ddaf-408c-44fe-a38e-f8096a2f459d" />

### SG90 Servo PWM Requirements
The following image shows the position that the servo will rotate to given a specific pulse width.
- 0° - 2ms pulse (2000us)
- 90° - 1.5ms pulse (1500us)
- 180° - 1ms pulse (1000us)
<img width="569" height="411" alt="image" src="https://github.com/user-attachments/assets/b837cb3f-4c31-495e-9284-818d2a1f49ae" />

### TM4C123GH6PM Pinout
<img width="878" height="747" alt="image" src="https://github.com/user-attachments/assets/f539def0-6f7e-46b1-a285-0a89261d8b21" />

### Sonar Graphic
<img width="3417" height="1236" alt="image" src="https://github.com/user-attachments/assets/d0487fb9-75c0-4df4-b783-5bfbdacffad2" />
