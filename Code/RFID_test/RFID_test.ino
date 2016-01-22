#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);       // объект MFRC522
unsigned long uidDec, uidDecTemp; // для отображения номера карточки в десятичном формате
byte bCounter, readBit;
unsigned long ticketNumber;


void setup() {
        Serial.begin(9600);     
        SPI.begin();            // инициализация SPI
        mfrc522.PCD_Init();     // инициализация MFRC522
        Serial.println("Waiting for card...");
}

void loop() {
        // Поиск новой карточки
        if ( ! mfrc522.PICC_IsNewCardPresent()) {
                return;
        }

        // Выбор карточки
        if ( ! mfrc522.PICC_ReadCardSerial()) {
                return;
        }

        uidDec = 0;

        // Выдача серийного номера карточки
        Serial.print("Card UID: ");
        for (byte i = 0; i < mfrc522.uid.size; i++) {
                // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                // Serial.print(mfrc522.uid.uidByte[i], HEX);
                uidDecTemp=mfrc522.uid.uidByte[i];
                uidDec=uidDec*256+uidDecTemp;
        } 
        Serial.println(uidDec);
        Serial.println();

        // Выдача типа карты
        byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak); // запрос типа
        Serial.print("Card type: ");
        Serial.println(mfrc522.PICC_GetTypeName(piccType)); // трансляция типа в читаемый вид
        if (piccType != MFRC522::PICC_TYPE_MIFARE_UL) { // если не билетная карта
                Serial.print("Not a valid card: "); // так и говорим
                Serial.println(piccType);                               
                // Halt PICC
                mfrc522.PICC_HaltA();                   // остановка чипа
                return;
        }

// сюда мы приедем, если чип правильный

        byte status;
        byte byteCount;
        byte buffer[18]; // длина массива (16 байт + 2 байта контрольная сумма) 
        byte pages[2]={4, 8}; // страницы с данными
        byte pageByte; // счетчик байтов страницы
        
        byteCount = sizeof(buffer);
        byte bCount=0;
                

        for (byte i=0; i<2; i++) { // начинаем читать страницы
        status = mfrc522.MIFARE_Read(pages[i], buffer, &byteCount);
        
        if (status != MFRC522::STATUS_OK) {
                Serial.print("Read error: ");}
            //    Serial.println(mfrc522.GetStatusCodeName(status));}
                else {
                      if (pages[i] == 4) {
                                bCounter = 0; // 32-битный счетчик для номера
                                
                                // биты 0-3
                                for (bCount=0; bCount<4; bCount++) {
                                        readBit = bitRead(buffer[6], (bCount+4));
                                        setBitsForGood(readBit);
                                }

                                // биты 4 - 27
                                for (pageByte=5; pageByte > 2; pageByte--) {
                                        for (bCount=0; bCount<8; bCount++) {
                                                readBit = bitRead(buffer[pageByte], bCount);
                                                setBitsForGood(readBit);
                                        }
                                }

                                // биты 28-31
                                for (bCount=0; bCount<4; bCount++) {
                                        readBit = bitRead(buffer[2], bCount);
                                        setBitsForGood(readBit);
                                }

                                Serial.print("Ticket number: ");
                                Serial.println(ticketNumber, DEC);
                         }
                        
                          if (pages[i] == 8) { // читаем дату выдачи

                                Serial.print("Issued: ");
                                unsigned int issueDate = buffer[0] * 256 + buffer[1]; // количество дней с 01.01.1992 в десятичном формате, 256 - сдвиг на 8 бит
                                printIssueDate(issueDate);

                                Serial.print("Good for (days): "); // срок действия
                                Serial.print(buffer[2], DEC);                                                           
                                Serial.println();                               
                        
                                Serial.print("Trip reminder: "); // количество оставшихся поездок
                                Serial.print(buffer[5], DEC);                                                           
                                Serial.println();       
                        }
                        
                        
                }
        }

                
                
        // Halt PICC
    mfrc522.PICC_HaltA();                       
        
}

void printIssueDate(unsigned int incoming) {

boolean isLeap = true; // признак високосного года
int days[]={0,31,59,90,120,151,181,212,243,273,304,334}; // последний по порядку день месяца для обычного года
byte dayOfMonth, monthCounter;
unsigned int yearCount;

incoming = incoming+1; // подогнал под ответ, но возможно это как раз необходимая коррекция, потому что начало отсчета - 01.01.1992, а не 00.01.1992

for (yearCount = 1992; incoming >366; yearCount++) { // считаем год и количество дней, прошедших с выдачи билета

        if ((yearCount % 4 == 0 && yearCount % 100 != 0) ||  yearCount % 400 == 0) {
                incoming = incoming - 366;
                isLeap = true;
          } else {
                incoming = incoming - 365;
                isLeap = false;
                }
        }

for (monthCounter = 0; incoming > days[monthCounter]; monthCounter++) { // узнаем номер месяца
}

// считаем день месяца

if (isLeap == true) { // если високосный год
  if (days[monthCounter-1]>31) { // если не первый месяц, то добавляем к последнему дню месяца единицы
  dayOfMonth = incoming - (days[monthCounter-1]+ 1);
  } else {
    dayOfMonth = incoming - (days[monthCounter-1]); // если первый - ничего не добавляем, потому что сдвиг начинается с февраля
  }
} else {
  dayOfMonth = incoming - (days[monthCounter-1]); // если не високосный год
}

Serial.print(dayOfMonth);
Serial.print(".");
Serial.print(monthCounter);
Serial.print(".");
Serial.print(yearCount);
Serial.println();

        

}




void setBitsForGood(byte daBeat) {


  
        if (daBeat == 1) {
                bitSet(ticketNumber, bCounter);
                bCounter=bCounter+1;
                }
        else {
                bitClear(ticketNumber, bCounter);
                bCounter=bCounter+1;
        }
}
