# ROS Robot Simulation 
=======================
Reaserch Track1, 2nd assignment
Professor: Carmine Recchiuto
Student: Shima Amiri Fard

## Installing & Running:
------------------------
to build the program, run the following commands:

```
$ mkdir -p catkin_ws/src

$ cd catkin_ws/src

$ git clone https://github.com/shimaamiri/ResearchTrack_assignment2.git

$ cd ..

$ source /opt/ros/<distro>/setup.bash

$ catkin_make
```
To run the programm, open 4 terminals and run one of the following commands in each of them:

```
$ roscore

$ rosrun stage_ros stageros $(rospack find second_assignment)/world/my_world.world

$ rosrun second_assignment controller

$ rosrun second_assignment UI

```

## Problem & Solution:
----------------------
 The robot endowed with laser scanners, should move inside a circuit with the possibility to increase/decrease the velocity or reset the position by user. This program consists of the following components:

- Stageros node from the world folder, which consists of the simulation environment (robot and robot circuit). 
- User interface (UI) node, which interacts with the user (increase / decrease the speed or reset the robot’s position).
- Controller node, for controlling the robot.
- A Service, which takes as the request the user command and gives as the responce the velocity.

* For obtaining the distance from the wall, the ranges vector of laser scanner should be considered (we divide the ranges vector into 3 subsections; left, front, and right. Then, we consider the minimum value of each subsection, which provides information about the closest wall).

The program rosgraph is shown in the following image:
![rosgraph](https://github.com/shimaamiri/rt_assignment2/blob/master/rosgraph_RT1_2.png)

### Controller node
Subscribes to command and base_scan topics and publishes the robot control signal with respect to detected obstacles to cmd_vel topic. 

### User Interface (UI) node
Recieves as input the increasing/decreasing speed command or reset position request from the user and publishes them on command topic.

## Flowchart
------------
The program flowchart is shown in the following image:
![Flowchart](https://github.com/shimaamiri/rt_assignment2/blob/master/Flowchart_RT1_2.jpeg)


