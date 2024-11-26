#include <Adafruit_LiquidCrystal.h>
#define BotaoProx 2
#define BotaoConf 3
int pos = 0, l = 0;
unsigned long tempoProx = 0, tempoConf = 0;
char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .<";
char nome[15] = "";
bool nomeConcluido = false;
Adafruit_LiquidCrystal lcd_1(0);

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  lcd_1.print("Introd. o nome");
}

void loop() {
  if (nomeConcluido) {
    return;
  }

  lcd_1.setCursor(pos, 1);
  lcd_1.print(caracteres[l]);

  if (digitalRead(BotaoProx) == LOW) {
    tempoProx = millis();
    while (digitalRead(BotaoProx) == LOW) {
      if (millis() - tempoProx > 2000) {
        pos = 0;
        l = 0;
        memset(nome, 0, sizeof(nome));
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Introd. o nome");
        return;
      }
    }
    if (l < 54) {
      l++;
    } else {
      l = 0;
    }
    lcd_1.setCursor(pos, 1);
    lcd_1.print(caracteres[l]);
  }

  if (digitalRead(BotaoConf) == LOW) {
    tempoConf = millis();
    while (digitalRead(BotaoConf) == LOW) {
      if (millis() - tempoConf > 2000) {
        nomeConcluido = true;
        nome[pos] = '\0';
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Hello:");
        lcd_1.setCursor(0, 1);
        lcd_1.print(nome);
        Serial.print("Nome inserido: ");
        Serial.println(nome);
        return;
      }
    }
    if (caracteres[l] == '<') {
      if (pos > 0) {
        pos--;
        nome[pos] = '\0';
        lcd_1.setCursor(pos, 1);
        lcd_1.print(" ");
      }
    } else if (pos < 14) {
      nome[pos] = caracteres[l];
      pos++;
    }
    lcd_1.setCursor(pos, 1);
    lcd_1.print(" ");
  }
}
