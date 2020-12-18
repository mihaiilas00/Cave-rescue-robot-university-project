# Cave-rescue-robot-university-project

This repository contains my contributions in a university project whose goal was designing and building a robot entering a narrow tunnel into a 2mx2m cave, identifying colourful 3cmx3cmx4m "victims" and returning them to the base, in a time span of 2 minutes.

I worked in a team of 2 on the software part. The project consisted in using a camera placed above the table to identify the robot, surroundings and victims at a fixed number of frames using colour masks and OpenCV built-in functions, then pass these coordinates via Wi-Fi connection to the Arduino board of the robot.
The decision making was performed on the Arduino board, which was then activating the motors to produce the motion.

My contributions came in designing the overall flow described above and in writing the .ino files describing different types of movement (all present in this repository). The repo also contains the Documentation of the project, explaining the algorithms in larger detail. 
