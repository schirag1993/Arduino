# Gyro Code

This folder contains the files required for the MPU6050 sensor to work with Arduino. We use the Kalman filter to obtain usable data from the sensor and then pass it on to the other Arduino that controls the motor.

# Motor Code

This folder contains the code for the motor. Data is recieved via nRF24L01+ and parsed. Code for stepper motor as well as DC motor control is present. The stepper motor maps the angle of the MPU while the DC motor turns, reverses or moves forward based on the angle.
