Overview

This project is a prototype backend system that simulates the management of a fleet of devices.
It provides a gRPC based API to register devices, track their states, and trigger mock long-running operations such as software updates.

Technologies Used
C++17
gRPC / Protocol Buffers
CMake
Python 3
Ubuntu 24.04.1 LTS (WSL2)

Architecture

The system consists of the following main components:
C++ Backend Service
gRPC server
In-memory storage for devices and actions
Worker threads for asynchronous action execution
Protocol Buffers API Layer
Defines services and message formats
Python CLI Client
Command line interface for interacting with the backend