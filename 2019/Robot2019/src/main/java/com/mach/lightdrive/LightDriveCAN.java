/*     */ package com.mach.lightdrive;
/*     */ 
/*     */ import java.nio.ByteBuffer;
/*     */ import java.nio.ByteOrder;

import edu.wpi.first.hal.can.CANJNI;
import edu.wpi.first.hal.can.CANMessageNotFoundException;
import edu.wpi.first.hal.util.UncleanStatusException;
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ public final class LightDriveCAN
/*     */ {
/*     */   public LightDriveCAN()
/*     */   {
/*  20 */     this.m_matrix = ByteBuffer.allocate(16);
/*  21 */     this.m_init = false;
/*  22 */     this.m_rx = new RxPacket();
/*  23 */     timestamp = ByteBuffer.allocateDirect(4);
/*  24 */     timestamp.order(ByteOrder.LITTLE_ENDIAN);
/*  25 */     rxid = ByteBuffer.allocateDirect(4);
/*  26 */     rxid.order(ByteOrder.LITTLE_ENDIAN);
/*     */   }
/*     */   
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */   public LightDriveCAN(int addr) {}
/*     */   
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */   public void Update()
/*     */   {
/*  44 */     byte[] txdata = new byte[8];
/*     */     
/*     */ 
/*     */ 
/*     */ 
/*  49 */     rxid.putInt(LD_ADDR + 4);
/*  50 */     rxid.rewind();
/*     */     try
/*     */     {
/*  53 */       this.m_matrix.get(txdata, 0, 8);
/*  54 */       CANJNI.FRCNetCommCANSessionMuxSendMessage(LD_ADDR, txdata, 100);
/*  55 */       this.m_matrix.get(txdata, 0, 8);
/*  56 */       CANJNI.FRCNetCommCANSessionMuxSendMessage(LD_ADDR + 1, txdata, 100);
/*     */     }
/*     */     catch (UncleanStatusException localUncleanStatusException) {}
/*     */     
/*     */ 
/*  61 */     this.m_matrix.rewind();
/*     */     try
/*     */     {
/*  64 */       this.rxdata = CANJNI.FRCNetCommCANSessionMuxReceiveMessage(rxid.asIntBuffer(), 536870911, timestamp);
/*     */       
/*     */ 
/*  67 */       if (this.rxdata.length > 7) {
/*  68 */         this.m_rx.SetBytes(this.rxdata);
/*     */       }
/*     */     }
/*     */     catch (CANMessageNotFoundException localCANMessageNotFoundException) {}
/*     */   }
/*     */   
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */   public float GetCurrent(int ch)
/*     */   {
/*  83 */     float current = 0.0F;
/*     */     
/*  85 */     switch (ch)
/*     */     {
/*     */     case 1: 
/*  88 */       current = this.m_rx.I1;
/*  89 */       break;
/*     */     case 2: 
/*  91 */       current = this.m_rx.I2;
/*  92 */       break;
/*     */     case 3: 
/*  94 */       current = this.m_rx.I3;
/*  95 */       break;
/*     */     case 4: 
/*  97 */       current = this.m_rx.I4;
/*  98 */       break;
/*     */     default: 
/* 100 */       current = -10.0F;
/*     */     }
/*     */     
/*     */     
/* 104 */     return current / 10.0F;
/*     */   }
/*     */   
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */   public float GetTotalCurrent()
/*     */   {
/* 113 */     return (this.m_rx.I1 + this.m_rx.I2 + this.m_rx.I3 + this.m_rx.I4) / 10.0F;
/*     */   }
/*     */   
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */   public float GetVoltage()
/*     */   {
/* 122 */     return this.m_rx.VIN / 10.0F;
/*     */   }
/*     */   
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */   public int GetFWVersion()
/*     */   {
/* 131 */     return this.m_rx.FW;
/*     */   }
/*     */   
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */   public Status GetStatus()
/*     */   {
/* 140 */     return this.m_rx.status;
/*     */   }
/*     */   
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */   public int GetPWMs(int ch)
/*     */   {
/* 151 */     if ((ch > 2) || (ch < 1))
/*     */     {
/* 153 */       return -1;
/*     */     }
/*     */     
/* 156 */     return ch > 1 ? this.m_rx.PWMVals >> 8 : this.m_rx.PWMVals & 0xFF;
/*     */   }
/*     */   
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */   public void SetColor(int ch, Color color)
/*     */   {
/* 167 */     if ((ch < 1) || (ch > 4)) {
/* 168 */       return;
/*     */     }
/* 170 */     ch--;
/* 171 */     ch *= 3;
/*     */     
/*     */ 
/* 174 */     this.m_matrix.array()[ch] = ((byte)color.green);
/* 175 */     this.m_matrix.array()[(ch + 1)] = ((byte)color.red);
/* 176 */     this.m_matrix.array()[(ch + 2)] = ((byte)color.blue);
/*     */   }
/*     */   
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */   public void SetColor(int ch, Color color, double brightness)
/*     */   {
/* 187 */     if ((ch < 1) || (ch > 4)) {
/*     */       return;
/*     */     }
/* 190 */     Color tmp12_11 = color;tmp12_11.red = ((short)(int)(tmp12_11.red * brightness)); Color 
/* 191 */       tmp25_24 = color;tmp25_24.green = ((short)(int)(tmp25_24.green * brightness)); Color 
/* 192 */       tmp38_37 = color;tmp38_37.blue = ((short)(int)(tmp38_37.blue * brightness));
/*     */     
/* 194 */     ch--;
/* 195 */     ch *= 3;
/*     */     
/* 197 */     this.m_matrix.array()[ch] = ((byte)color.green);
/* 198 */     this.m_matrix.array()[(ch + 1)] = ((byte)color.red);
/* 199 */     this.m_matrix.array()[(ch + 2)] = ((byte)color.blue);
/*     */   }
/*     */   
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */   public void SetLevel(int ch, byte level)
/*     */   {
/* 209 */     if ((ch < 1) || (ch > 12) || (level < 0) || (level > 255)) {
/* 210 */       return;
/*     */     }
/* 212 */     this.m_matrix.array()[ch] = level;
/*     */   }
/*     */   
/* 215 */   private static int LD_ADDR = 33882112;
/*     */   private ByteBuffer m_matrix;
/*     */   private RxPacket m_rx;
/*     */   private boolean m_init;
/*     */   private byte[] rxdata;
/*     */   private static ByteBuffer timestamp;
/*     */   private static ByteBuffer rxid;
/*     */ }


/* Location:              C:\Users\Robotics\Downloads\LDRV-12_Examples\java\LightDrive.jar!\com\mach\LightDrive\LightDriveCAN.class
 * Java compiler version: 8 (52.0)
 * JD-Core Version:       0.7.1
 */