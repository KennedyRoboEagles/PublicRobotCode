/*    */ package com.mach.lightdrive;
/*    */ 
/*    */ final class RxPacket
/*    */ {
/*    */   byte I1;
/*    */   byte I2;
/*    */   byte I3;
/*    */   byte I4;
/*    */   byte VIN;
/*    */   Status status;
/*    */   byte PWMVals;
/*    */   byte FW;
/*    */   
/*    */   RxPacket() {
/* 15 */     this.status = new Status();
/* 16 */     this.I1 = 0;
/* 17 */     this.I2 = 0;
/* 18 */     this.I3 = 0;
/* 19 */     this.I4 = 0;
/* 20 */     this.VIN = 0;
/* 21 */     this.PWMVals = 0;
/* 22 */     this.FW = 0;
/*    */   }
/*    */   
/*    */   byte[] GetBytes() {
/* 26 */     byte[] tempdata = new byte[8];
/*    */     
/* 28 */     tempdata[0] = this.I1;
/* 29 */     tempdata[1] = this.I2;
/* 30 */     tempdata[2] = this.I3;
/* 31 */     tempdata[3] = this.I4;
/* 32 */     tempdata[4] = this.VIN;
/* 33 */     tempdata[5] = this.status.GetRaw().byteValue();
/* 34 */     tempdata[6] = this.PWMVals;
/* 35 */     tempdata[7] = this.FW;
/*    */     
/* 37 */     return tempdata;
/*    */   }
/*    */   
/*    */   void SetBytes(byte[] data) {
/* 41 */     this.I1 = data[0];
/* 42 */     this.I2 = data[1];
/* 43 */     this.I3 = data[2];
/* 44 */     this.I4 = data[3];
/* 45 */     this.VIN = data[4];
/* 46 */     this.status.SetRaw(data[5]);
/* 47 */     this.PWMVals = data[6];
/* 48 */     this.FW = data[7];
/*    */   }
/*    */ }


/* Location:              C:\Users\Robotics\Downloads\LDRV-12_Examples\java\LightDrive.jar!\com\mach\LightDrive\RxPacket.class
 * Java compiler version: 8 (52.0)
 * JD-Core Version:       0.7.1
 */