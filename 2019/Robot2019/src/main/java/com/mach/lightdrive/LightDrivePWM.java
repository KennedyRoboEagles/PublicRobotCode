/*     */ package com.mach.lightdrive;
/*     */ 
/*     */ import edu.wpi.first.wpilibj.DigitalOutput;
/*     */ import edu.wpi.first.wpilibj.Servo;
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ public final class LightDrivePWM
/*     */ {
/*     */   private DigitalOutput m_pwm_select;
/*     */   private DigitalOutput m_pwm_value;
/*     */   private Servo m_servo_bank1;
/*     */   private Servo m_servo_bank2;
/*     */   private int[] m_matrix;
/*     */   private boolean m_type_servo;
/*     */   
/*     */   public LightDrivePWM(Servo bank1, Servo bank2)
/*     */   {
/*  30 */     this.m_servo_bank1 = bank1;
/*  31 */     this.m_servo_bank2 = bank2;
/*     */     
/*  33 */     this.m_matrix = new int[12];
/*     */     
/*  35 */     this.m_type_servo = true;
/*     */   }
/*     */   
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */   public void Update()
/*     */   {
/*  60 */     double newduty = 0.0D;
/*     */     
/*     */ 
/*     */ 
/*  64 */     int channels = (this.m_matrix[0] > 0 ? 16 : 0) | (this.m_matrix[1] > 0 ? 32 : 0) | 
/*  65 */       (this.m_matrix[2] > 0 ? 64 : 0) | (this.m_matrix[3] > 0 ? 128 : 0) | 
/*  66 */       (this.m_matrix[4] > 0 ? 256 : 0) | (this.m_matrix[5] > 0 ? 512 : 0);
/*     */     
/*     */ 
/*  69 */     newduty = channels / 1023.0D;
/*     */     
/*  71 */     if (this.m_type_servo)
/*     */     {
/*  73 */       this.m_servo_bank1.set(newduty);
/*     */     }
/*     */     else
/*     */     {
/*  77 */       this.m_pwm_select.updateDutyCycle(newduty);
/*     */     }
/*     */     
/*  80 */     channels = (this.m_matrix[6] > 0 ? 16 : 0) | (this.m_matrix[7] > 0 ? 32 : 0) | 
/*  81 */       (this.m_matrix[8] > 0 ? 64 : 0) | (this.m_matrix[9] > 0 ? 128 : 0) | 
/*  82 */       (this.m_matrix[10] > 0 ? 256 : 0) | (this.m_matrix[11] > 0 ? 512 : 0);
/*     */     
/*  84 */     newduty = channels / 1023.0D;
/*     */     
/*  86 */     if (this.m_type_servo)
/*     */     {
/*  88 */       this.m_servo_bank2.set(newduty);
/*     */     }
/*     */     else
/*     */     {
/*  92 */       this.m_pwm_select.updateDutyCycle(newduty);
/*     */     }
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
/* 104 */     if ((ch < 1) || (ch > 4))
/*     */     {
/* 106 */       return;
/*     */     }
/*     */     
/* 109 */     ch--;
/* 110 */     ch *= 3;
/*     */     
/* 112 */     this.m_matrix[ch] = color.green;
/* 113 */     this.m_matrix[(ch + 1)] = color.red;
/* 114 */     this.m_matrix[(ch + 2)] = color.blue;
/*     */   }
/*     */   
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */   public void SetLevel(int ch, int level)
/*     */   {
/* 124 */     if ((ch < 1) || (ch > 12) || (level < 0) || (level > 255)) {
/* 125 */       return;
/*     */     }
/* 127 */     this.m_matrix[ch] = level;
/*     */   }
/*     */ }


/* Location:              C:\Users\Robotics\Downloads\LDRV-12_Examples\java\LightDrive.jar!\com\mach\LightDrive\LightDrivePWM.class
 * Java compiler version: 8 (52.0)
 * JD-Core Version:       0.7.1
 */