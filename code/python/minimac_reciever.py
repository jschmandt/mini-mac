import serial
from struct import *
import csv
import numpy as np

class MSPCommunications:
    def __init__(self, comportnum, baudrate=28800,header="****"):
        self.comportnum = comportnum
        self.baudrate = baudrate
        self.header = header
        
    def __del__(self):
        self.disconnectSerialDevice()

    def connectSerialDevice(self):
        print "Attempting to connect to:", self.comportnum
        self.ser = serial.Serial(self.comportnum-1,self.baudrate,timeout=None)
        self.ser.flushInput()
        print "Connected to ", self.ser.name     
        
    def eatthrough(self, searchStr=None):
        if searchStr is None:
            searchStr = self.header  
            
        #print "eating through, searchStr=", searchStr 
        
        readString = "" 
        for itr in range(0,len(searchStr)):
            readString = readString + self.ser.read()
            #for i in readString:
                #print ord(i)
        while readString != searchStr:
            readString = readString[1:] + self.ser.read()
            #print "len(readString)=", len(readString)
            #for i in readString:
                #print ord(i)
            
        
    def disconnectSerialDevice(self):
        if self.ser.isOpen():
            self.ser.close()
            print "Serial Device", self.ser.name, "closed"
            return True
        else:
            print "Serial Device", self.ser.name, "was not open"
            return False
            
    def read(self,numValues):
        data = np.zeros(numValues)
        readString = self.ser.read(numValues*2)
        for itr in range(numValues):
            data[itr] = ord(readString[itr*2]) + ord(readString[itr*2+1])*256
        return data
            
    def readInt16LittleEndian(self,numValues):
        data = np.zeros(numValues)
        readString = self.ser.read(numValues*2)
        #print "readString=",
        #for i in readString:
            #print ord(i)
        for itr in range(numValues):
            #print "itr=", itr
            data[itr] = ord(readString[itr*2]) + ord(readString[itr*2+1])*256;
        return data
        
    def readInt16BigEndian(self, numValues):
        data = np.zeros(numValues)
        readString = self.ser.read(numValues*2)
        for itr in range(numValues):
            data[itr] = ord(readString[itr*2+1]) + ord(readString[itr*2])*256;
        return data

def main():
    COMPORT = 5
    BAUDRATE = 28800
    comm = MSPCommunications(COMPORT,BAUDRATE,"****")    
    comm.connectSerialDevice()
    
    data = np.zeros(1000)
    for itr in range(1000):
        comm.eatthrough()
        data[itr] = comm.readInt16BigEndian(1)
        
    np.savetxt('minimac_log.txt', data)
        
    avg = np.mean(data)
    avg_t = avg/ float(32000)
    print "average (cyc)=", avg
    print "average (ms,approx)=", avg_t*1000
    
    max = np.max(data)
    max_t = max/ float(32000)    
    print "max (cyc)=", max
    print "max (ms, approx)=", max_t*1000
    
    min = np.min(data)
    min_t = min/ float(32000)
    print "min (cyc)=", min
    print "min (ms, approx)=", min_t*1000
    
if __name__ == "__main__":
    main()