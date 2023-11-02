#INCLUDE <tv_matran_phim.c>
unsigned int8 kytu[]      = {0x20,0x20,0X20,0X20,0x20,0x20,0x20,0X20,0X20,0x20};         // 0x20 là khoang trang
unsigned int8 passmp[]    = {0x20,0x20,0X20,0X20,0x20,0x20,0x20,0X20,0X20,0x20};
unsigned int8 kytu_sao[]  = {0x20,0x20,0X20,0X20,0x20,0x20,0x20,0X20,0X20,0x20};
unsigned int8 mk_doi[]    = {0x20,0x20,0X20,0X20,0x20,0x20,0x20,0X20,0X20,0x20};
unsigned int8 mk_doi_ss[] = {0x20,0x20,0X20,0X20,0x20,0x20,0x20,0X20,0X20,0x20};
unsigned int8 b;
unsigned int8 lan,sl,dem;
int1 tt_doi,ss,tt_mo;
signed int8 k;         

#define  loa    pin_a1
#define  sv     pin_a0

void dong_cua()
{
   for(int k=0;k<=50;k++)     // giu trang thai goc quay 180 do
   {                
      output_high(sv);
      delay_ms(2);
      output_low(sv);
      delay_ms(18);              // 18ms
   }   
}

void mo_cua()
{
   for(k=0;k<10;k++)            // kich goc 90 do
   {
      output_high(sv);
      delay_ms(1);               //1ms
      output_low(sv);
      delay_ms(19);
   } 
}

void dem_giay()
{
   for(dem=5;dem>0;dem--)
   {
       output_high(loa);
       
       lcd_command(0x80);
       lcd_data(" VUOT LAN NHAP  "); 
       lcd_command(0xc0);
       lcd_data("THOI GIAN:   "); 
       lcd_data(dem/10+0X30); 
       lcd_data(dem%10+0X30); 
       lcd_data("s"); 
       delay_ms(1000);
   }
   output_low(loa);
   lcd_command(0x01);
}

void nhap_mk()
{
     for(b=0;b<9;b++)
     {
         kytu[b]=kytu[b+1];
     }
     kytu[9]=mp+0x30;      // 0x30 chuyen ma thap phan sang ascii
     
     for(b=0;b<9;b++)
     {
         kytu_sao[b]=kytu_sao[b+1];
     }
     kytu_sao[9]=0x2a;

    lcd_command(0xc6);   // cot 7 hang 2
    for(b=0;b<10;b++)
    {
      lcd_data(kytu_sao[b]); 
      delay_ms(30);
    }
}

void nhap_mk_doi()  // dich lan 1 pass moi
{
     for(b=0;b<9;b++)
     {
         mk_doi[b]=mk_doi[b+1];
     }
     mk_doi[9]=mp+0x30;
     
    lcd_command(0xc6);
    for(b=0;b<10;b++)
    {
      lcd_data(mk_doi[b]);
      delay_ms(30);
    }
}

void nhap_mk_doi_ss()
{
     for(b=0;b<9;b++)
     {
         mk_doi_ss[b]=mk_doi_ss[b+1]; //so sanh mat khau vua doi
     }
     mk_doi_ss[9]=mp+0x30;
     
    lcd_command(0xc6);
    for(b=0;b<10;b++)
    {
      lcd_data(mk_doi_ss[b]);
      delay_ms(30);
    }
}

void kiem_tra_mk()
{
   for(b=0;b<10;b++)
      {
         if(kytu[b]!=passmp[b])
         {
            tt_mo=0;             // bao sai 
            break;
         }
         else              tt_mo=1;       // bao dung pass
      }
      
      if(tt_mo==0)
      {
         lcd_command(0x80);
         lcd_data("  SAI MAT KHAU  ");
         lcd_command(0xc0);
         lcd_data("  MOI NHAP LAI  ");
         delay_ms(1000);
         lcd_command(0x01);
         sl++;
         if(sl>=3)
         {
            dem_giay();
         }
      }
      else   // tt=0  bao dung
      {
         sl=0;
         chay=0;
      }
      for(b=0;b<10;b++)
      {
         kytu[b]=0x20;   // xoa ky tu cu~
         kytu_sao[b]=0x20;
      }
      
}

void kiemtra_mk_doi()
{
   lan=1;
   for(b=0;b<10;b++)
   {
      if(mk_doi[b]!=mk_doi_ss[b])
      {
         ss=1;             // bao sai 
         break;
      }
      else           ss=0;
   }
   if(ss==0)  // doi mat khau thanh cong
   {
      lcd_command(0x80);
      lcd_data("  DOI MAT KHAU  ");
      lcd_command(0xc0);
      lcd_data(" DOI THANH CONG ");
      for(b=0;b<10;b++)          // luu gia tri pass moi vao eeprom
      {
         write_eeprom(b,mk_doi[b]);
      }
   }
   else        // ss=1 doi mat khau that bai
   {
      lcd_command(0x80);
      lcd_data("  DOI MAT KHAU  ");
      lcd_command(0xc0);
      lcd_data("  DOI THAT BAI  ");
   }
   delay_ms(1000);
   tt_doi=0;
   tt_mo=0;
   dong_cua();
   for(b=0;b<10;b++)
   {
      mk_doi[b]=0x20;   // xoa ky tu cu~
      mk_doi_ss[b]=0x20;   // xoa ky tu cu~
   }
   lcd_command(0x80);
   lcd_data("                  ");
   lcd_command(0xc0);
   lcd_data("                  ");
}

void kiem_tra_key_phim()
{
   mp=quetphim_4x3(); 
   if(mp!=12)    // kiem tra co nhan phim khong
   {        // co nhan phim
      if((tt_doi==0))    // nhap pass mo cua
      {
         if(tt_mo==0)
         {
            if(mp<10)        // co phep nhap tu 0 den 9
            {
               nhap_mk();
            }
            else if(mp==10)    
            {
               kiem_tra_mk();
            }   
         }
         
         if(mp==11)            // cho phep doi pass
         {
            if(tt_mo==1)      // cua dang mo
            {
                for(b=0;b<10;b++)
                {
                  kytu[b]=0x20;   // xoa ky tu cu~
                  kytu_sao[b]=0x20;
                  mk_doi[b]=0X20;   // xoa ky tu cu~
                  mk_doi_ss[b]=0X20;   // xoa ky tu cu~
                }
               tt_doi=1;
               lan=1;
               lcd_command(0x80);
               lcd_data("  DOI MAT KHAU  ");
               lcd_command(0xc0);
               lcd_data("LAN 1:          ");
            }
         }
      }
      else if(tt_doi==1)       // doi pass   tt_doi=1;
      {
         if(lan==1)      // nhap pass moi lan 1
         {
            if(mp<10)
            {
               nhap_mk_doi();
            }
            else if(mp==10) // nhan *
            {
               lan=2;
               lcd_command(0xc0);
               lcd_data("LAN 2:          ");
            }
         }
         else if(lan==2)
         {
            lcd_command(0xc0);
            lcd_data("LAN 2:");
            
            if(mp<10)
            {
               nhap_mk_doi_ss();
            }
            else if(mp==10)
            {
              kiemtra_mk_doi();
            }
         }
         if(mp==11)     // huy qua trinh doi pass, quay ve man hinh chinh
         {
            tt_doi=0;        // cho nhap pass
            tt_mo=0;         // khong cho doi pass
            lan=0;
            for(b=0;b<10;b++)
            {
               mk_doi[b]=0x20;   // xoa ky tu cu~
               mk_doi_ss[b]=0x20;   // xoa ky tu cu~
               kytu[b]=0x20;   // xoa ky tu cu~
               kytu_sao[b]=0x20;
            }
            lcd_command(0x01);
            dong_cua();
         }
      }   
   }
}

