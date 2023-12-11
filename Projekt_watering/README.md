# Smart plant watering system and data logger

### Členové skupiny
 - Matěj Výlet
 - Martin Borski

## Cíl projektu
 Vytvořit systém na zalévání květin pomocí mikrokontroleru Arduino Uno, relé a senzorů teploty a vlhkosti. Dále ukládat relevantní data do paměti a následně je vypsat.
#### Řešení
 Za pomoci seznoru vlhkosti a teploty určíme bod, kdy se zapne a vypne zavlažování pomocí relé. 
Po překročení spodní hranice vlhkosti se začne zavlažovat do doby, než se dostaneme k horní hranici vlhkosti, kde se zavlažování vypne. Ovládání senzorů a relé je zajištěno mikrokontrolerem Arduino Uno s čipem ATmega328P.

## Popis hardwarového provedení
 Schéma zapojení




### Arduino Uno
Projekt byl vytvořen pro Arduino Uno s čipem ATmega328P. [Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf).

![pinout](https://docs.arduino.cc/static/2b141eb1cfe6f465a949c203e4af1b5f/A000066-pinout.png)
[Obr. - Rozložení pinů na desce](https://docs.arduino.cc/hardware/uno-rev3)




### Senzor teploty
Byl použit obvod DHT12 se zabudovaným senzorem teploty a vzdušné vlhkosti, ale v tomto projektu využíváme pouze měření teploty. [Datasheet](https://datasheetspdf.com/pdf-file/1147840/Aosong/DHT12/1).



### Kapacitní senzor vhlkosti
Pomocí senzoru se monitoruje vlhkost hlíny a na základě procenta vlhkosti se zapíná a vypíná zavlažování pomocí relé. [Datasheet senzoru](https://www.sigmaelectronica.net/wp-content/uploads/2018/04/sen0193-humedad-de-suelos.pdf).



### Relé
Spínání čerpadla na vodu(,které není součástí projektu) je zajištěno relém. [Datasheet]().



### Oled display 128x64
Zobrazuje hodnoty teploty a vlhkosti a status zalévání. [Datasheet](https://www.datasheethub.com/wp-content/uploads/2022/08/SSD1306.pdf).




### Časový modul se zabudovanou pamětí RTC DS3231
Hodiny udávající reálný čas (real time clock). Obsahují též paměť EEPROM k ukládání dat vlhkosti a teploty. [Datasheet RTC modulu](https://www.analog.com/media/en/technical-documentation/data-sheets/ds3231.pdf), 
[datasheet EEPROM paměti](https://ww1.microchip.com/downloads/en/devicedoc/doc0336.pdf).




## Popis softwaru
Pro více podrobností se podívejte na dokumentaci Doxygenu.

### gpio.h, gpio.c
- Zapisuje a čte registry pinů Arduina.
### timer.h
- Ovládá časovací moduly
- Používá se k časování přerušení
### oled.h, oled.c
- Knihovna k zapisování hodnot teploty a vlhkosti na display
### twi.h, twi.c
- Knihovna ovládající komunikaci přes sériovou sběrnici I2C
### uart.h, uart.c
- Umožňuje zápis a čtení dat ze sériové sběrnice UART, kerá slouží ke komunikaci s počítačem.

## Vývojový diagram aplikace
![vývojový diagram](https://github.com/Matej-Vylet/digital-electronics-2/assets/124773189/470273a2-88b7-4f4f-8d6e-2b0313c95bd9)


## Video

## Reference

