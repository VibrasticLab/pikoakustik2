#!/usr/bin/python
# -*- coding: utf-8 -*-

##
# @file audtone.py
# @brief This program convert tone scale JSON into actual dB-SPL, dBA, or dB-HL

# Imports
import os
import sys
import json
from pathlib import Path
from PyQt5.QtWidgets import QApplication,QWidget,QPushButton
from PyQt5.QtWidgets import QLabel,QFileDialog,QMessageBox
import matplotlib.pyplot as mplt

# The Main Class
class AudiometriViewer():

# build basic gui
    def __init__(self):
        self.stt_fOpenData = "Data Open: "
        self.openCalibFName = os.getcwd() + "/calib_example.json"
        self.stt_fOpenCalib = "Calibration Open: %s" %  self.shorten_path(self.openCalibFName,3)

        self.freq = [250,500,1000,2000,4000,8000]

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
        json_file.close()
        return json_data

# Plot JSON using Matplotlib
    def json_plot_matplotlib(self,jsonDataFName):
        if self.openCalibFName == "":
            msgerr = QMessageBox()
            msgerr.setIcon(QMessageBox.Critical)
            msgerr.setText("Calibration File is not set")
            msgerr.setWindowTitle("No Calibration File")
            msgerr.setStandardButtons(QMessageBox.Ok)
            msgerr.exec()
        else:
            jsonData = self.json_load(jsonDataFName)
            jsonCalib = self.json_load(self.openCalibFName)

            dBL = [
                    jsonCalib["250Hz"][int(jsonData["audiogram"]["ch_0"]["freq_0"]["ampl"])],
                    jsonCalib["500Hz"][int(jsonData["audiogram"]["ch_0"]["freq_1"]["ampl"])],
                    jsonCalib["1000Hz"][int(jsonData["audiogram"]["ch_0"]["freq_2"]["ampl"])],
                    jsonCalib["2000Hz"][int(jsonData["audiogram"]["ch_0"]["freq_3"]["ampl"])],
                    jsonCalib["4000Hz"][int(jsonData["audiogram"]["ch_0"]["freq_4"]["ampl"])],
                    jsonCalib["8000Hz"][int(jsonData["audiogram"]["ch_0"]["freq_5"]["ampl"])]
                    ]
            dBR = [
                    jsonCalib["250Hz"][int(jsonData["audiogram"]["ch_1"]["freq_0"]["ampl"])],
                    jsonCalib["500Hz"][int(jsonData["audiogram"]["ch_1"]["freq_1"]["ampl"])],
                    jsonCalib["1000Hz"][int(jsonData["audiogram"]["ch_1"]["freq_2"]["ampl"])],
                    jsonCalib["2000Hz"][int(jsonData["audiogram"]["ch_1"]["freq_3"]["ampl"])],
                    jsonCalib["4000Hz"][int(jsonData["audiogram"]["ch_1"]["freq_4"]["ampl"])],
                    jsonCalib["8000Hz"][int(jsonData["audiogram"]["ch_1"]["freq_5"]["ampl"])]
                    ]

            mplt.close()

            mplt.plot(self.freq,dBL,'X-',color='r',label='Left Ear')
            for ix,iy in zip(self.freq,dBL):
                mplt.text(ix,iy,'({},{})'.format(ix,iy),fontsize='x-small')

            mplt.plot(self.freq,dBR,'X-',color='b',label='Right Ear')
            for ix,iy in zip(self.freq,dBR):
                mplt.text(ix,iy,'({},{})'.format(ix,iy),fontsize='x-small')

            mplt.grid(axis='y')
            mplt.semilogx()
            mplt.ylim(0,90)

            outLabel = "Tone Output (%s)" % jsonCalib["audio_unit"]
            mplt.ylabel(outLabel)
            mplt.xlabel("Frequency Hz")
            mplt.xticks([])

            calibText = "CALIBRATION: %s by %s at %s" % (jsonCalib["headphone"],jsonCalib["author"],jsonCalib["tanggal"])
            mplt.title(calibText, fontsize=8)

            mplt.legend(loc='best')

            mplt.show()


# Shorten File Path for label only
    def shorten_path(self,file_path,length):
        return Path(*Path(file_path).parts[-length:])

# Open Data
    def data_open(self):
        opts = QFileDialog.Options()
        opts |= QFileDialog.DontUseNativeDialog
        fName,_ = QFileDialog.getOpenFileName(None,"Audiometri Data Record","","All Files (*)",options=opts)
        if fName:
            self.stt_fOpenData = "Data Open: %s" % (self.shorten_path(fName,3))
            self.lbl_openData.setText(self.stt_fOpenData)
            self.lbl_openData.adjustSize()

            self.json_plot_matplotlib(fName)

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
