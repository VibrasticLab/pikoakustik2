#!/usr/bin/python3
# -*- coding: utf-8 -*-

##
# @file audtone.py
# @brief This program convert tone scale JSON into actual dB-SPL, dBA, or dB-HL

# Imports
import sys
import json
from pathlib import Path
from PyQt5.QtWidgets import QApplication,QWidget,QPushButton
from PyQt5.QtWidgets import QLabel,QFileDialog,QMessageBox

# The Main Class
class AudiometriViewer():
    def __init__(self):
        self.stt_fOpenData = "Data Open: "
        self.openDataFName = ""
        self.stt_fOpenCalib = "Calibration Open: "
        self.openCalibFName = ""

        self.app = QApplication(sys.argv)

        self.win = QWidget()
        self.win.resize(300,100)
        self.win.setWindowTitle("Audiometri Data Viewer")

        self.btn_loadData = QPushButton("Load Data",self.win)
        self.btn_loadData.setToolTip("Load the HT*.TXT data record")
        self.btn_loadData.move(10,10)
        self.btn_loadData.clicked.connect(self.data_open)

        self.btn_loadCalib = QPushButton("Load Calibration",self.win)
        self.btn_loadCalib.setToolTip("Load the Calibration data")
        self.btn_loadCalib.move(100,10)
        self.btn_loadCalib.clicked.connect(self.calib_open)

        self.btn_about = QPushButton("About",self.win)
        self.btn_about.setToolTip("Show Some Info")
        self.btn_about.move(205,10)
        self.btn_about.clicked.connect(self.about_dlg)

        self.lbl_openData = QLabel(self.win)
        self.lbl_openData.setText(self.stt_fOpenData)
        self.lbl_openData.move(10,60)

        self.lbl_openCalib = QLabel(self.win)
        self.lbl_openCalib.setText(self.stt_fOpenCalib)
        self.lbl_openCalib.move(10,80)

# JSON loading
    def json_load(self,fName):
        with open(fName) as json_file:
            json_data = json.load(json_file)
        return json_data

# Shorten File Path for label only
    def shorten_path(self,file_path,length):
        return Path(*Path(file_path).parts[-length:])

# Open Data
    def data_open(self):
        opts = QFileDialog.Options()
        opts |= QFileDialog.DontUseNativeDialog
        fName,_ = QFileDialog.getOpenFileName(None,"Audiometri Data Record","","All Files (*)",options=opts)
        if fName:
            self.openDataFName = fName
            self.stt_fOpenData = "Data Open: %s" % (self.shorten_path(fName,3))
            self.lbl_openData.setText(self.stt_fOpenData)
            self.lbl_openData.adjustSize()

            self.jsonOpenData = self.json_load(self.openDataFName)
            print(self.jsonOpenData['audiogram']['ch_0']['freq_0'])


# Open Calibration
    def calib_open(self):
        opts = QFileDialog.Options()
        opts |= QFileDialog.DontUseNativeDialog
        fName,_ = QFileDialog.getOpenFileName(None,"Audiometri Calibration","","All Files (*)",options=opts)
        if fName:
            self.openCalibFName = fName
            self.stt_fOpenCalib = "Calibration Open: %s" % (self.shorten_path(fName,3))
            self.lbl_openCalib.setText(self.stt_fOpenCalib)
            self.lbl_openCalib.adjustSize()

# About Dialog
    def about_dlg(self):
        msginfo = QMessageBox()
        msginfo.setIcon(QMessageBox.Information)
        msginfo.setText("Audiometri Data Viewer")
        msginfo.setWindowTitle("About this program")
        msginfo.setStandardButtons(QMessageBox.Ok)
        msginfo.exec()

# Build the GUI
    def gui_run(self):
        self.win.show()
        sys.exit(self.app.exec_())

if __name__ == "__main__":
    aud = AudiometriViewer()
    aud.gui_run()
