# 🔍 cscan – A Simple Port Scanner in C

A simple lightweight port scanner made in C, inspired by Nmap. A project made by a C and ethical hacking enthusiast!

## 🚀 Features
- Simple CLI usage
- Written from scratch in C
- Lightweight and fast
- A TCP Scan

## 📅 Future plans
- **UDP Scan** - Adds support for scanning UDP ports
- **SYN Scan** - Implements SYN scan which is more **stealthy** than TCP scan!
- **Better error handling** - Improve the error handling

## 🎯 Commands
``bash

    Usage: ./cscan <type> <ports> <target ip>
    Example: ./cscan -t tcp -p 80 -ip 127.0.0.1
    Types of scan:
     - tcp: Performs a full TCP connection and is fast but not stealthy at all.
    Port types:
     - 80: It will only scan the one port you listed.
     - 21,80,443: It will scan the multiple ports you listed.
     - 1-1024: It will scan all the ports from 1 to 1024.

## 📦 Download instructions
### 🧰 Dependencies
- **CMake** and **GCC**:
- ```bash
  sudo apt update
  sudo apt install cmake gcc
### 📜Steps
- ```bash
  git clone https://github.com/kristus310/cscan-portscanner.git
  cd cscan-portscanner
  mkdir build
  cd build
  cmake ..
  make
