#!/usr/bin/python
# -*- coding: utf-8 -*-

##
# @file audtone.py
# @brief This program convert tone scale JSON into actual dB-SPL, dBA, or dB-HL

# Imports
import os
import sys
import json
import numpy as np
from pathlib import Path
from PyQt5.QtWidgets import QApplication,QWidget,QPushButton
from PyQt5.QtWidgets import QLabel,QFileDialog,QMessageBox
from matplotlib.offsetbox import AnchoredText as antext
import matplotlib.pyplot as mplt

# The Main Class
class AudiometriViewer():

# build basic gui
    def __init__(self):
        self.stt_fOpenData = "Data Open: "
        self.openCalibFName = os.getcwd() + "/calib_example.json"
        self.stt_fOpenCalib = "Calibration Open: %s" %  self.shorten_path(self.openCalibFName,3)

        self.freq = [250,500,1000,2000,4000,8000]
        self.strfreq = ["250","500","1000","2000","4000","8000"]

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

# PTA calculation
    def pta_calc(self,l500,l1000,l2000,l4000,r500,r1000,r2000,r4000):
        pta_L = (l500+l1000+l2000+l4000)/4
        strPTA_L = r'$\frac{%i + %i + %i + %i}{4} = %i$' % (l500,l1000,l2000,l4000,pta_L)

        pta_R = (r500+r1000+r2000+r4000)/4
        strPTA_R = r'$\frac{%i + %i + %i + %i}{4} = %i$' % (r500,r1000,r2000,r4000,pta_R)

        return "PTA L: " + strPTA_L + "\n" + "PTA R: " + strPTA_R

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
            mplt.figure(figsize=(4, 6))

            mplt.plot(self.freq,dBL,'-',color='r',marker=r'$O$',label='Left Ear')
            for ix,iy in zip(self.freq,dBL):
                mplt.text(ix,iy,'({},{})'.format(ix,iy),fontsize='x-small')

            mplt.plot(self.freq,dBR,'--',color='b',marker=r'$X$',label='Right Ear')
            for ix,iy in zip(self.freq,dBR):
                mplt.text(ix,iy,'({},{})'.format(ix,iy),fontsize='x-small')

            mplt.grid(axis='both')
            mplt.semilogx()
            mplt.yticks(np.arange(0,160,10))

            if jsonCalib["audio_unit"]=="dBHL":
                mplt.gca().invert_yaxis()

            outLabel = "Tone Output (%s)" % jsonCalib["audio_unit"]
            mplt.ylabel(outLabel)
            mplt.xlabel("Frequency Hz")
            mplt.xticks(self.freq,labels=self.strfreq)

            calibText = "CALIBRATION: %s by %s at %s" % (jsonCalib["headphone"],jsonCalib["author"],jsonCalib["tanggal"])
            mplt.title(calibText, fontsize=8)

            mplt.legend(loc='best')

            strPTA = self.pta_calc(
                jsonCalib["500Hz"][int(jsonData["audiogram"]["ch_0"]["freq_1"]["ampl"])],
                jsonCalib["1000Hz"][int(jsonData["audiogram"]["ch_0"]["freq_2"]["ampl"])],
                jsonCalib["2000Hz"][int(jsonData["audiogram"]["ch_0"]["freq_3"]["ampl"])],
                jsonCalib["4000Hz"][int(jsonData["audiogram"]["ch_0"]["freq_4"]["ampl"])],
                jsonCalib["500Hz"][int(jsonData["audiogram"]["ch_1"]["freq_1"]["ampl"])],
                jsonCalib["1000Hz"][int(jsonData["audiogram"]["ch_1"]["freq_2"]["ampl"])],
                jsonCalib["2000Hz"][int(jsonData["audiogram"]["ch_1"]["freq_3"]["ampl"])],
                jsonCalib["4000Hz"][int(jsonData["audiogram"]["ch_1"]["freq_4"]["ampl"])]
            )

            pta_info = antext(strPTA,loc=8)
            mplt.gca().add_artist(pta_info)

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
