#include <project_vxl_nhom_04.h>

#define RS  PIN_C0
#define RW  PIN_C1
#define E   PIN_C2
void lcd_command(unsigned int8 cm)
{
   output_low(RW);
   output_low(RS);
   delay_ms(5);
   output_d(cm);
   output_low(E);
   output_high(E);
   delay_ms(1);
}
void lcd_data(unsigned int8 dt)
{
   output_low(RW);
   output_high(RS);
   delay_ms(5);
   output_d(dt);
   output_low(E);
   output_high(E);
   delay_ms(1);
}
void lcd_setup()
  {
   delay_ms(5);
   lcd_command(0x38);
   delay_ms(5);
   lcd_command(0x0c);
   lcd_command(0x06);
   lcd_command(0x01);
   delay_ms(2);
  }
signed int8 chay,i;
#include<tv_key_phim_4x3.c>


void main()
{
   set_tris_a(0x00);
   set_tris_d(0x00);
   set_tris_c(0x00);
   set_tris_b(0xf0);
   lcd_setup();
   lcd_command(0x80);
   lcd_data(" NHAP MAT KHAU  ");
   output_bit(loa,0);
   tt_doi=0;     // cho phep doi pass
   lan=0;        // so lan doi pass
   sl=0;
   dong_cua();
   chay=0;
   tt_mo=0; // cua dong

   for(i=0;i<10;i++)          // luu gia tri pass moi vao eeprom
   {
      write_eeprom(i,mk_doi[i]);
   }
   WHILE(TRUE)
   {
      kiem_tra_key_phim();
      for(b=0;b<10;b++)
      {
         passmp[b]=read_eeprom(b);  // DOC MAT KHAU DUC LUU TRONG EEPROM
      }
      if(tt_mo==1)       // nhan dung mat khau cua mo
      {
         if((tt_doi==0))       // chua nhan # de doi mat khau 
         {
            chay++;
            lcd_command(0x80);
            lcd_data(" DUNG MAT KHAU  ");
            lcd_command(0xc0);
            lcd_data("CUA MO - MOI VAO");
         }
         if(chay<30)
         {
            if(tt_doi==0)        mo_cua();
         }
         else 
         {
            tt_mo=0;
            tt_doi=0;
            dong_cua();
            lcd_command(0x01);
         }
      }
      else
      {
         lcd_command(0x80);
         lcd_data(" NHAP MAT KHAU  ");  
      }   
   }
}

