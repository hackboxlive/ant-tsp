# ant-tsp

Ant TSP is an implementation of ant colony optimisation to find efficient approximate solutions to the Traveling Salesman
Problem. It includes a visualiser written in Python 2 with Pygame. It uses self defined protocols to communicate between the
visualiser and the actual algorithm written in C++14.


## How to build

* Install all dependencies

  sudo apt-get install build-essential
  sudo apt-get install python-pygame
  

## How to run

  g++ ant.cpp -std=c++14
  python gui.py

