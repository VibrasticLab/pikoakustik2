# Audiometri Data Viewer

## Description

This small Python program can be used to convert from our Audiometri tone scale into more acceptable graph known as 'Audiogram'

This program should be easy to learn and modify since its written in known Python language and reading only simple JSON for input array or calibration

![images](images/audtone.png?raw=true)

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

**NOTES:** Most recent Python for Windows cannot be installed on Windows 7 or ealier version of Windows.
At the time this tutorial written, the last version available for Windows 7 is Python version 3.8.10.
You can visit [here](https://www.python.org/downloads/release/python-3810/).

Check **Add Python to PATH**, then click **Install Now**

![images](images/python_win_install.png?raw=true)

Wait until success

![images](images/python_win_install_success.png?raw=true)

Close the installer, then open command prompt using Win+R, type **cmd**, then Enter.
Then type this to check version:

```sh
python -V
```

![images](images/python_win_chkver.png?raw=true)

### Module Installation

The PyQt5 and Matplotlib can be install using tutorials below

#### ArchLinux/Manjaro/Endeavor

```sh
sudo pacman -Syu
sudo pacman -S python-pyqt5 python-matplotlib
```

#### Debian/Ubuntu/LinuxMint

```sh
sudo apt-get update
sudo apt-get install python3-pyqt5 python3-matplotlib
```

#### Windows

For Windows, module installation can be done through PIP

PIP (short for Package Installer for Python) is Python's internal package management system.
Written in Python and designed to be operating system independent so it can be used same way across major operating system like Windows and GNU/Linux.

For module installation in Windows, first open **cmd** window like previous, then type command:

```sh
pip install PyQt5
pip install matplotlib
```

## Run Program

Assume all installation done, you can run a virtual terminal emulator (e.g Mate-Terminal, Xfce-Terminal) in your GNU/Linux computer, or open **cmd** window in your Windows computer

Then go to where this project folder path and type command:

```sh
python audtone.py
```

It will run main program like this:

![images](images/main.png?raw=true)

From here, if you load valid JSON data input, it will plot the conversion like this:

![images](images/plot.png?raw=true)

You can also change your JSON calibration from here.
By default, the main program will use 'calib_example.json' file (provided here) every program start.

## Valid JSON

Here example of valid calibration JSON:

```json
{
"author" : "mbak Lela",
"headphone" : "JBL",
"tanggal" : "23-08-2022",
"audio_unit" : "dBA",
"250Hz" : [0, 4.3, 4.5, 6.4, 11.6, 18.6, 24.3, 30.5, 36.5, 42.48, 48.6, 54.7],
"500Hz" : [0, 6.2, 6.6, 10.8, 15.5, 22.6, 29.3, 35.4, 41.5, 47.5, 53.4, 59.6],
"1000Hz" : [0, 11.1, 11.8, 17.8, 24.4, 31.5, 37.9, 44.6, 50.1, 56.2, 62.3, 68.3],
"2000Hz" : [0, 14.6, 14.5, 16.8, 21.3, 27.7, 34.2, 40.4, 46.6, 52.7, 58.7, 64.8],
"4000Hz" : [0, 18.5, 18.1, 27.7, 35.2, 42.8, 49.5, 55.9, 61.9, 68.0, 74.1, 80.1],
"8000Hz" : [0, 18.4, 18.6, 21.5, 26.6, 32.6, 38.9, 45.1, 51.2, 57.2, 63.3, 69.4]
}
```

Here example of valid data input JSON:

```json
{"audiogram":{

"ch_0":{
"freq_0":{"freq": 0.625,"ampl":8,"record":[11,11,11,11,10,9,8,7,8,7,8,7,8,7,8,7,8,8,8,8,8,8,8,8]},
"freq_1":{"freq": 1.250,"ampl":8,"record":[11,10,9,8,7,6,5,6,7,6,7,8,7,8,7,8,9,8,7,8,7,6,7,8]},
"freq_2":{"freq": 2.500,"ampl":5,"record":[11,10,9,8,7,6,5,4,5,6,5,6,5,6,5,6,5,4,5,4,5,5,5,5]},
"freq_3":{"freq": 5.000,"ampl":5,"record":[11,10,9,8,7,6,5,4,5,4,5,4,5,4,5,4,5,5,5,5,5,5,5,5]},
"freq_4":{"freq":10.000,"ampl":3,"record":[11,10,9,8,7,6,5,4,3,2,3,4,3,4,3,2,1,2,3,2,3,4,3,2]},
"freq_5":{"freq":20.000,"ampl":4,"record":[11,10,9,8,7,6,5,4,3,2,1,2,3,4,3,4,3,4,3,2,3,4,5,4]}},
"ch_1":{
"freq_0":{"freq": 0.625,"ampl":7,"record":[11,10,9,8,7,8,7,8,9,10,9,8,7,6,7,6,7,8,9,8,7,6,7,6]},
"freq_1":{"freq": 1.250,"ampl":9,"record":[11,10,9,8,7,6,5,6,7,6,7,6,7,6,7,8,7,6,7,8,9,8,9,9]},
"freq_2":{"freq": 2.500,"ampl":6,"record":[11,10,9,8,7,6,5,6,5,6,7,8,7,6,5,6,7,6,5,4,5,6,5,6]},
"freq_3":{"freq": 5.000,"ampl":6,"record":[11,10,9,8,7,8,7,8,7,8,7,8,7,6,7,8,7,6,5,6,7,8,7,6]},
"freq_4":{"freq":10.000,"ampl":5,"record":[11,10,9,8,9,8,7,6,5,6,5,6,7,6,5,4,3,4,5,4,5,5,5,5]},
"freq_5":{"freq":20.000,"ampl":9,"record":[11,10,9,8,7,6,7,8,9,8,7,6,7,6,5,6,5,6,7,8,9,8,9,9]}}
}
}
```