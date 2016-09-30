# ant-tsp

Ant TSP is an implementation of ant colony optimisation to find efficient approximate solutions to the Traveling Salesman
Problem. It includes a visualiser written in Python 2 with Pygame. It uses self defined protocols to communicate between the
visualiser and the actual algorithm written in C++14.

This was written in 4 hours for the hackathon conducted in NITH for Udbhava 2016 on the 30th of September, 2016 by 

* [Sarv Shakti Singh](http://github.com/hackboxlive)
* [Param Singh](http://github.com/paramsingh)
* [Abhishek Rastogi](http://github.com/Princu7)


## How to build and run

Install all dependencies

    sudo apt-get install build-essential
  
    sudo apt-get install python-pygame
 

Compile ant.cpp and then run gui.py
  
    g++ ant.cpp -std=c++14
  
    python gui.py

