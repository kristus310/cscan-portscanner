# 🔍 cscan – A Simple Port Scanner in C
## Version: 1.0

A simple lightweight port scanner made in **C**, inspired by **Nmap**. A project made by a C and ethical hacking enthusiast!
This project is a work in progress and has a **long journey** ahead before it reaches completion.
**WARNING:**
    - This tool was made for ethical use only. Don't scan anyone/anything if you don't have their consent to do so!
    - This is the first version of the tool and bugs are expected - if you encounter any, please contact me about them, thank you!
    
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
- ```bash
    Usage: ./cscan <type> <ports> <target ip>
    Example: ./cscan -t tcp -p 80 -ip 127.0.0.1
    Types of scan:
     - tcp: Performs a full TCP connection and is fast but not stealthy at all.
    Port types:
     - 80: It will only scan the one port you listed.
     - 21,80,443: It will scan the multiple ports you listed.
     - 1-1024: It will scan all the ports from 1 to 1024.

## 📦 Download instructions
### 🧰 Dependencies:
- **CMake** and **GCC**:
- ```bash
  sudo apt update
  sudo apt install cmake gcc
### 📜 Steps:
- ```bash
  git clone https://github.com/kristus310/cscan-portscanner.git
  cd cscan-portscanner
  mkdir build
  cd build
  cmake ..
  make

## 🏅 Credits
Inspiration: This project was inspired by the powerful port scanning tool, Nmap.
Contributors:
    Kristián "kristus310" Botek – Creator and Maintainer
    
Special thanks to the open-source community for the inspiration and libraries that made this possible!
