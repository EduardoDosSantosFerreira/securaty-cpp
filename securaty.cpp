// Importar bibliotecas
#include <EEPROM.h> // Memória não volátil
#include <Keypad.h> // Biblioteca de teclado
#include <LiquidCrystal.h> Biblioteca de display LCD
#include <Servo.h> Biblioteca de servomotor

// Definir protótipos de funções
void playTone(const byte piezoPin, int frequency, int delayTime);
void setLocked(bool locked);
void loadCode();
void saveCode();
void getNewCode(char *password);

// Definir pinos
const byte redLed = 12, greenLed = 13, piezo = 11, servo = A1;
const byte rs = 9, en = 10, db4 = A2, db5 = A3, db6 = A4, db7 = A5;

// Instânciar objetos
LiquidCrystal lcd(rs, en, db4,db5,db6,db7);
Servo servomotor;

// Teclado
const byte rows = 4;
const byte cols= 4;
char keys[rows][cols]=
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[rows] = {8,7,6,5};
byte colPins[cols] = {4,3,2,1};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols); // Mapear teclas e criar objeto teclado

// Definir Variáveis
char *password = "123456"; // Senha que libera o acesso
byte totalKeys = strlen(password); // Quantidade de digítos da senha
byte tries = 0; // Quantidade de digítos digitados
byte hits = 0; // Quantidade de digítos digitados e corretos
bool locked = true;

void setup()
{
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(servo, OUTPUT);
  lcd.begin(16,2);
  servomotor.attach(servo);
  loadCode();
  setLocked(locked);
}

void loop()
{
  char key = keypad.getKey(); // Receber tecla do usuário
  
  // Se alguma tecla foi digitada
  if (key){
    
    if (key == '#' || key == '*'){
      
      lcd.clear();
      hits = 0;
      tries = 0;
      
      if (key == '*'){
        if (!locked){
            getNewCode(password);
        }
      }
      delay(200);
      locked = true;
      setLocked(locked);
      playTone(piezo,128,50);
    }
    
    else{
      tries ++;
      playTone(piezo,10,20);
      lcd.print(key);
      
      // Se digíto estiver correto
      
      if (key == password[hits]){
        hits ++;
      }

      // Se tentativas se esgotaram
      if (tries == totalKeys){
        tries = 0;

        // Se senha estiver correta
        if (hits == totalKeys){
          hits = 0;
          locked = false;
          setLocked(locked);
        }

        else {
          locked = true;
          setLocked(locked);
          playTone(piezo,128,50);
        }

        delay(100);
        lcd.clear();
      }
    }
  }
}

void playTone(const byte piezoPin, int frequency, int delayTime)
// Tocar um som por um determinado período de tempo
{
  	tone(piezoPin, frequency);
    delay(delayTime);
  	noTone(piezoPin);
}

void setLocked(bool locked)
// Ligar ou desligar leds e porta
{
  if (locked){
  	Serial.println("Porta travada");
    digitalWrite(redLed,HIGH);
    digitalWrite(greenLed,LOW);
    servomotor.write(0);
  }
  
  else {
    Serial.println("Porta destravada");
    digitalWrite(redLed,LOW);
    digitalWrite(greenLed,HIGH);
    playTone(piezo,512,50);
    servomotor.write(90);
  }
}

void loadCode()
// Carregar senha da EEPROM    
{
  if (EEPROM.read(0) == 1){
    password[0] = EEPROM.read(1);
    password[1] = EEPROM.read(2);
    password[2] = EEPROM.read(3);
    password[3] = EEPROM.read(4);
    password[4] = EEPROM.read(5);
    password[5] = EEPROM.read(6);
    
    Serial.println("Senha " + (String) password + " carregada da EEPROM");
    return;
  }
                 
    Serial.println("Não há dados armazenados na EEPROM");
}

void saveCode()
// Salvar senha na EEPROM  
{
  EEPROM.write(1,password[0]);               
  EEPROM.write(2,password[1]); 
  EEPROM.write(3,password[2]);                       
  EEPROM.write(4,password[3]);            
  EEPROM.write(5,password[4]);           
  EEPROM.write(6,password[5]);            
  EEPROM.write(0,1);
  Serial.println("Senha " + (String) password + " salva na EEPROM");
}

void getNewCode(char *password)
// Redefenir senha
{
  // Ligar leds
  digitalWrite(redLed,HIGH);
  digitalWrite(greenLed,HIGH);
  playTone(piezo,240,50);
  
  Serial.println("Insira a nova senha...");
  
  // Definir variáveis locais
  char *oldPassword;
  oldPassword = strcpy(oldPassword, password);
  byte i = 0;
  
  // Obter dígito enquanto menor do que 6
  while (i < 6){
    char key = keypad.getKey();

    if (key){
      
      if (key == '#' || key == '*'){
      	// Cancelar redefinição de senha
        playTone(piezo,30,20);
        password = strcpy(password, oldPassword);
        lcd.clear();
        Serial.println("Redefinição de senha cancelada");
        return; 	
      }
    
      else {
        // Obter dígito
        playTone(piezo,10,20);
        lcd.print(key);
        password[i] = key;
        i++; 
      }
    }
  }
  
  delay(100);
  lcd.clear();
  saveCode();
  playTone(piezo,512,50);
}
