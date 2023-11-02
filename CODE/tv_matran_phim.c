#define     c0       pin_b0
#define     c1       pin_b1
#define     c2       pin_b2
#define     c3       pin_b3

#define     h0       pin_b4
#define     h1       pin_b5
#define     h2       pin_b6


unsigned int8 mp;
unsigned int8 quetphim_4x3()
{
   output_low(c0);   // cap muc 0 cho hang 1
   output_high(c1);
   output_high(c2);
   output_high(c3);
   
   if(input(h0)==0)        // kiem tra co xuong 0 
   {
      delay_ms(20);        // chong doi phim
      if(input(h0)==0)     // con muc 0
      {
         while(input(h0)==0);       // cho nha phim
         return 1;                    //1
      }
   }
   if(input(h1)==0)
   {
      delay_ms(20);
      if(input(h1)==0)
      {
         while(input(h1)==0);
         return 2;                     //2
      }
   }
   if(input(h2)==0)
   {
      delay_ms(20);
      if(input(h2)==0)
      {
         while(input(h2)==0);
         return 3;                    //3
      }
   }
   output_low(c1);    // cap muc 0 cho hang 2
   output_high(c0);
   output_high(c2);
   output_high(c3);
   if(input(h0)==0)
   {
      delay_ms(20);
      if(input(h0)==0)
      {
         while(input(h0)==0);
         return 4;               //4
      }
   }
   if(input(h1)==0)
   {
      delay_ms(20);
      if(input(h1)==0)
      {
         while(input(h1)==0);
         return 5;                  //5
      }
   }
   if(input(h2)==0)
   {
      delay_ms(20);
      if(input(h2)==0)
      {
         while(input(h2)==0);
         return 6;               //6
      }
   }

   output_low(c2);  // cap muc 0 cho hang 3
   output_high(c0);
   output_high(c1);
   output_high(c3);
   if(input(h0)==0)
   {
      delay_ms(20);
      if(input(h0)==0)
      {
         while(input(h0)==0);
         return 7;                  //7
      }
   }
   if(input(h1)==0)
   {
      delay_ms(20);
      if(input(h1)==0)
      {
         while(input(h1)==0);
         return 8;                  //8
      }
   }
   if(input(h2)==0)
   {
      delay_ms(20);
      if(input(h2)==0)
      {
         while(input(h2)==0);
         return 9;                  //9
      }
   }
   
   output_low(c3);// cap muc 0 cho hang 4
   output_high(c0);
   output_high(c1);
   output_high(c2);
   if(input(h0)==0)
   {
      delay_ms(20);
      if(input(h0)==0)
      {
         while(input(h0)==0);
         return 10;         //10
      }
   }
   if(input(h1)==0)
   {
      delay_ms(20);
      if(input(h1)==0)
      {
         while(input(h1)==0);
         return 0;         //0
      }
   }
   if(input(h2)==0)
   {
      delay_ms(20);
      if(input(h2)==0)
      {
         while(input(h2)==0);
         return 11;            //11
      }
   }
   
   return 12;
}
