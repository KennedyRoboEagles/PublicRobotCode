/*    */ package com.mach.lightdrive;
/*    */ 
/*    */ 
/*    */ public final class Color
/*    */ {
/*    */   public short red;
/*    */   
/*    */   public short green;
/*    */   
/*    */   public short blue;
/*    */   
/* 12 */   public static final Color RED = new Color(255, 0, 0);
/* 13 */   public static final Color GREEN = new Color(0, 255, 0);
/* 14 */   public static final Color BLUE = new Color(0, 0, 255);
/* 15 */   public static final Color TEAL = new Color(0, 255, 255);
/* 16 */   public static final Color YELLOW = new Color(255, 255, 0);
/* 17 */   public static final Color PURPLE = new Color(255, 0, 255);
/* 18 */   public static final Color WHITE = new Color(255, 255, 255);
/* 19 */   public static final Color OFF = new Color(0, 0, 0);
/*    */   
/*    */ 
/*    */ 
/*    */ 
/*    */   public Color()
/*    */   {
/* 26 */     this.red = 0;
/* 27 */     this.green = 0;
/* 28 */     this.blue = 0;
/*    */   }
/*    */   
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */   public Color(short r, short g, short b)
/*    */   {
/* 39 */     this.red = r;
/* 40 */     this.green = g;
/* 41 */     this.blue = b;
/*    */   }
/*    */   
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */ 
/*    */   public Color(int r, int g, int b)
/*    */   {
/* 52 */     this.red = ((short)r);
/* 53 */     this.green = ((short)g);
/* 54 */     this.blue = ((short)b);
/*    */   }
/*    */ }


/* Location:              C:\Users\Robotics\Downloads\LDRV-12_Examples\java\LightDrive.jar!\com\mach\LightDrive\Color.class
 * Java compiler version: 8 (52.0)
 * JD-Core Version:       0.7.1
 */