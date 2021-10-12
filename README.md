# Hunt The Wumpus

## Contents

- [Description](#description)
- [Technology Stack](#technology-stack)
- [Application Overview](#application-overview)


## Description
This repository is an object-oriented implementation of Hunt the Wumpus using modern C++ and design patterns.

Hunt the Wumpus is a text-based adventure game originally developed by Gregory Yob.

The game involves a player exploring a network of caves connected by tunnels. There are 20 interconnected caves, where each cave is connected to 3 other caves. There are 5 obstacles present in the cave network: 2 bottomless pits, 2 bats, and 1 Wumpus. 

The objective of the game is for the player to hunt the Wumpus. The player is equipped with 5 "crooked arrows" (arrow path can change direction during flight between caves and may loop to hit the player). Landing a hit on the Wumpus wins the game. Landing a hit on the player, falling into a bottomless pit, or being eaten by the Wumpus ends the game with a loss.

## Technology Stack
This application is developed in Visual Studio 2019 environment using C++ (C++20).

CppUnitLite unit test framework is used to provide unit test coverage for this project.

## Application Overview
### System Design
The [design specification](https://github.com/myu404/HuntTheWumpus/blob/master/HuntTheWumpusDesignSpec.pdf) illustrates a UML class diagram of the Hunt the Wumpus application. The diagram establishes the relationship between the objects involved. 

Smart pointers (unique pointers, shared pointers, and weak pointers) from C++ Standard Library (```<memory>``` header) are used extensively to emphasize the UML relationship and resource ownership between objects. 

Searching, sorting, and modifying algorithms from C++ Standard Library are implemented to facilitate object interaction between other objects and containers/collections. Functional programming paradigm, like lambda functions, is utilized in conjunction with C++ algorithms to handle data processing.

### Libraries
*Standard Library*

Various new C++20 features from C++ Standard Library and C++ Standard Template Library are used in the implementation of this project to reduce code bloat. Some of the features implemented in this project are:

- ```operator<=>``` (three-way comparison operator or operator spaceship): reduces the number of comparison function definition from 18 (C++17 and older) to 2 (C++20). C++20 standard only need to define ```operator=``` and ```operator<=>``` to provide the full suite of comparison operations. 
- Ranges library from ```<ranges>``` header: pre-C++20 ```<algorithm>``` library features that operate on containers/collections would require the ```begin()``` and ```end()``` iterators as input arguments. C++20 standard only require the container/collection object as input argument.

*User-Defined Library*

Hunt the Wumpus library is a static library that contains all the classes involved in the system and the game state monitoring to check for win/lose condition.

### Unit Testing
Unit test suite is included in this project to verify and validate the functionality of class objects and methods. Tests provide coverage to demostrate that the application will meet the system design requirements.

See [UnitTestHuntTheWumpus/](https://github.com/myu404/HuntTheWumpus/tree/master/UnitTestHuntTheWumpus) for unit tests.

### Installation
Download the repository to local machine. Assuming Visual Studio 2019 environment, open ```HuntTheWumpus.sln```, set ```HuntTheWumpus``` project as "startup project" from Visual Studio 2019 IDE, build and compile solution to create executable file, and run the executable file.
