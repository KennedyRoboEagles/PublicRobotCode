/*    */ package com.mach.lightdrive;
/*    */ 
/*    */ 
/*    */ 
/*    */ public class Status
/*    */ {
/*    */   private byte m_raw;
/*    */   
/*    */   private mode m_mode;
/*    */   
/*    */ 
/*    */   public static enum mode
/*    */   {
/* 14 */     NONE, 
/* 15 */     IDLE, 
/* 16 */     PWM, 
/* 17 */     CAN, 
/* 18 */     SERIAL;
/*    */   }
/*    */   
/*    */ 
/*    */ 
/*    */ 
/*    */   public Status()
/*    */   {
/* 26 */     this.m_raw = 0;
/* 27 */     this.m_mode = mode.NONE;
/*    */   }
/*    */   
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */   public byte GetTripped()
/*    */   {
/* 36 */     return (byte)((this.m_raw & 0xF0) >> 4);
/*    */   }
/*    */   
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */   public Boolean IsEnabled()
/*    */   {
/* 45 */     if ((this.m_raw & 0x1) > 0) return Boolean.valueOf(true); return Boolean.valueOf(false);
/*    */   }
/*    */   
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */   public mode GetMode()
/*    */   {
/* 54 */     return this.m_mode;
/*    */   }
/*    */   
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */   public Byte GetRaw()
/*    */   {
/* 63 */     return Byte.valueOf(this.m_raw);
/*    */   }
/*    */   
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */   public void SetRaw(byte raw)
/*    */   {
/* 72 */     this.m_raw = raw;
/*    */   }
/*    */ }


/* Location:              C:\Users\Robotics\Downloads\LDRV-12_Examples\java\LightDrive.jar!\com\mach\LightDrive\Status.class
 * Java compiler version: 8 (52.0)
 * JD-Core Version:       0.7.1
 */