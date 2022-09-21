#include <EEPROMex.h>
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(3,4); // RX, TX
int luu_pass_eeprom = 30; // vị trí lưu biến Int
int khoa =5;
int coi =4 ;
int doi_pass=2;
float data1;
float data2=0;
double time_cho=0;
double passeeprom=0;
double pass=0;
int input;
int i=2;

void setup() 
{
    Serial.begin(9600);
    //mySerial.begin(9600);
    pinMode(khoa, OUTPUT);
    pinMode(coi, OUTPUT);
    pinMode(doi_pass,INPUT);
    digitalWrite(coi,HIGH);
    digitalWrite(khoa,HIGH);
    digitalWrite(khoa,LOW);
    EEPROM.setMemPool(0, 1024); //vị tri dau tien và dung luong cua eeprom
    EEPROM.setMaxAllowedWrites(1024); // số byte cho phép lưu
    passeeprom=EEPROM.readInt(luu_pass_eeprom);
    pass=passeeprom;
    Serial.println(pass);
}
void loop() 
{   // đóng khóa sau 2s
     if (digitalRead(doi_pass) == 0){
    if(millis()-time_cho>=1200){
      digitalWrite(khoa,LOW);
    digitalWrite(coi,LOW);}
    
    
    //khi có data gửi đến
    if (Serial.available()) 
    {
        delay(11);
        data1 = Serial.readString().toInt();
        //mySerial.write(data1);
        //Serial.println(data1);
        if(data1 == pass) 
        {   Serial.println("Đã mở két.");
            time_cho=millis();
            digitalWrite(khoa, HIGH);
            digitalWrite(coi,HIGH);
            data1=0;
        }
        else
        {Serial.println("Mật khẩu sai.");
        digitalWrite(coi,HIGH);
        delay(3000);}
    }////hết
     }
   
    /// đỏi mật khẩu
  //if (digitalRead(doi_pass) == 1)
    else
  {     
    if(i==2)
    {
        Serial.println("Nhập Mật Khẩu Mới.");
        i=3;
        data1=0;
        digitalWrite(khoa,LOW);
    digitalWrite(coi,LOW);
    }
    ///chờ nhập mật khẩu mới
    while (i==3)   
    {      
    if (Serial.available()) 
    {
        delay(11);
        //data1 = Serial.read();
        data1 = Serial.readString().toInt();
        Serial.print("Mật khẩu mới là: ");
        Serial.println(data1);
        Serial.print("Nhập lại mật khẩu mới để lưu.");
        while (i==3)
        {
            if (Serial.available()) 
            {
                delay(11);
                data2 = Serial.readString().toInt();
                if(data2==data1)
                {
                    Serial.print("Mật khẩu mới là: ");
                    Serial.println(data1);
                    EEPROM.writeInt(luu_pass_eeprom,data2); // lưu input vào eeprom
                    data2=0;
                    data1=0;
                    i=2;
                    passeeprom=EEPROM.readInt(luu_pass_eeprom);
                    pass=passeeprom;
                    Serial.println("----------------------------------------------");
                }
            }
                      
                     
        }
    }

  }
  } 
}
//output = EEPROM.readInt(luu_pass_eeprom); // đọc int từ eeprom tại địa chỉ luu_pass_eeprom, lưu vào output
