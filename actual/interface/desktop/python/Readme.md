# Audiometri Data Viewer

## Description

This small Python program can be used to convert from our Audiometri tone scale into more acceptable graph known as 'Audiogram'

This program should be easy to learn and modify since its written in known Python language and reading only simple JSON for input array or calibration

## Requirements

List of Requirements
- Python 3 (preferably 3.8 or above)
- PyQT5 (only need basic Widgets)
- JSON parser (already part of Python 3)
- Matplotlib for plotting

You will also need calibration JSON file.
You can use one example provided here.

## Installation

For convinient, here some installtion tutorial.
Only GNU/Linux and Windows available for now.


### Python3 for GNU/Linux

For most GNU/Linux, the Python 3 interpreter already part of operating system distribution.
No need for any installation.

But if you need, here some install commands:

#### ArchLinux/Manjaro/Endeavor

```sh
sudo pacman -Syu
sudo pacman -S python python-pip python-setuptools python-wheel
```

#### Debian/Ubuntu/LinuxMint

```sh
sudo apt-get update
sudo apt-get install python3 python3-pip python3-setuptools python3-wheel
```

**NOTES:** In most GNU/Linux distribution, the python interpreter already refers to Python version 3. 
But for Debian, Ubuntu, and its derivate, its still stuck as version 2 and for version 3 has to specificly call python3 program.
For convinient accross operating system, its advised to use python3 everytime call Python interpreters

To check installed version, type this command on your terminal emulator:

```sh
python3 -V
```

### Python3 for Windows

#### Windows 7 Important

If you use earlier Windows 7 (before SP1), you may install KB3063858 update patch:

Here you can download:
- For [64bit](https://www.microsoft.com/en-us/download/details.aspx?id=47442)
- For [32bit](https://www.microsoft.com/en-us/download/details.aspx?id=47409)

If you use Windows 7 SP1 onward, or even Windows 8 after, you can ignore this step.

#### Python Installer

Next, you need download Python installer from [here](https://www.python.org/downloads/release/python-3106/).

Choose **Windows installer (64-bit)** for 64 version of Windows and vice-versa.

![images](images/python_win_installer.png?raw=true)