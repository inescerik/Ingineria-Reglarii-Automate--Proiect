float c[3]={0,0,0};
float e[3]={1,1,1}; 
float in() 
{
  union u_tag {
  byte b[4]; 
  float fvalue; 
  } in; 
  in.fvalue=0;
  for (int i=0 ; i<4 ; i++) { 
    while (!Serial.available());
    in.b[i]=Serial.read(); 
  }
  return in.fvalue; 
}
void out(float c) {
  union u_tag {
    byte b[4]; 
    float fvalue; 
  }out;
  out.fvalue=c; 
  Serial.write(out.b[0]); 
  Serial.write(out.b[1]); 
  Serial.write(out.b[2]); 
  Serial.write(out.b[3]); 
}
void setup(){
  Serial.begin(9600);
  delay(1000); 
  out(0); 
}
void loop() {
  e[0]=in(); //insert below the calculated discrete control function 
   c[0] =4.612*e[1] - 4.387*e[2] + 1.607*c[1] - 0.6065*c[2];
  out(c[0]); 
  for(int i=1;i>0;i--) {
    c[i]=c[i-1]; 
    e[i]=e[i-1]; 
  }
}
