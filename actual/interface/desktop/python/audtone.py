#!/usr/bin/python3
# -*- coding: utf-8 -*-

##
# @file audtone.py
# @brief This program convert tone scale JSON into actual dB-SPL, dBA, or dB-HL

# Imports
import sys
from PyQt5.QtWidgets import QApplication,QWidget,QPushButton
from PyQt5.QtWidgets import QLabel,QFileDialog

# The Main Class
class AudiometriViewer():
    def __init__(self):
        self.stt_fName = "Data Open: "
        self.openDataFName = ""

        self.app = QApplication(sys.argv)

        self.win = QWidget()
        self.win.resize(300,100)
        self.win.setWindowTitle("Audiometri Data Viewer")

        self.btn_loadData = QPushButton("Load Data",self.win)
        self.btn_loadData.setToolTip("Load teh HT*.TXT data record")
        self.btn_loadData.move(10,10)
        self.btn_loadData.clicked.connect(self.data_open)

        self.lbl_openData = QLabel(self.win)
        self.lbl_openData.setText(self.stt_fName)
        self.lbl_openData.move(10,60)

        self.lbl_openCalib = QLabel("Data Calibration: ",self.win)
        self.lbl_openCalib.move(10,80)

# Open Data
    def data_open(self):
        opts = QFileDialog.Options()
        opts |= QFileDialog.DontUseNativeDialog
        fName,_ = QFileDialog.getOpenFileName(None,"Audiometri Data Record","","All Files (*)",options=opts)
        if fName:
            self.openDataFName = fName
            self.stt_fName = "Data Open: " + fName
            self.lbl_openData.setText(self.stt_fName)

# Build the GUI
    def gui_run(self):
        self.win.show()
        sys.exit(self.app.exec_())

if __name__ == "__main__":
    aud = AudiometriViewer()
    aud.gui_run()
