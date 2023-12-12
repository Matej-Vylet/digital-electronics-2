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
### Schéma zapojení
![schema](https://github.com/Matej-Vylet/digital-electronics-2/assets/124773189/29c24e20-eb0a-469f-86a1-0b721720bd9e)




### Arduino Uno
Projekt byl vytvořen pro Arduino Uno s čipem ATmega328P.

![pinout](https://docs.arduino.cc/static/2b141eb1cfe6f465a949c203e4af1b5f/A000066-pinout.png)
[Obr. - Rozložení pinů na desce](https://docs.arduino.cc/hardware/uno-rev3)




### Senzor teploty
Byl použit obvod DHT12 se zabudovaným senzorem teploty a vzdušné vlhkosti, ale v tomto projektu využíváme pouze měření teploty. 
![DHT12](https://github.com/Matej-Vylet/digital-electronics-2/assets/124773189/8d7d2df3-afcf-4010-a112-27c3d926d82d)




### Kapacitní senzor vhlkosti
Pomocí senzoru se monitoruje vlhkost hlíny a na základě procenta vlhkosti se zapíná a vypíná zavlažování pomocí relé.
![Senzor vlhkosti](https://github.com/Matej-Vylet/digital-electronics-2/assets/124773189/53a7a830-1072-40e3-a36a-d71ce7ea70e7)


### Relé
Spínání čerpadla na vodu(,které není součástí projektu) je zajištěno relém. 
![Relé](https://github.com/Matej-Vylet/digital-electronics-2/assets/124773189/acbff0cf-3f77-4832-a41a-3b04d55694f8)


### Oled display 128x64
Zobrazuje hodnoty teploty a vlhkosti a status zalévání. 
![Display](https://github.com/Matej-Vylet/digital-electronics-2/assets/124773189/3a8ec688-a55e-483b-97d3-d78d2285eaf7)









## Popis softwaru
Pro více podrobností se podívejte na dokumentaci Doxygenu.

## Ukládání dat
Data ukládáme pomocí UARTu a programu PuTTY. Ten čte sériový port a data zapisuje do .csv souboru, který následně lze otevřít v Excelu. Po opětovném zapnutí desky se data ukládají do téhož souboru pod data již existující.

#### Nastavení programu PuTTY
![session](https://github.com/Matej-Vylet/digital-electronics-2/assets/124773189/36b0be4a-0fbe-4d14-8bdb-0db85694d950)
![logging](https://github.com/Matej-Vylet/digital-electronics-2/assets/124773189/d7193cca-7fed-4e6f-8c59-5745243bb8db)


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
[Video](https://www.youtube.com/watch?v=iqaxpEFCBaQ)

## Reference
1. [Arduino datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
2. [Senzor teploty DHT12 datasheet](https://datasheetspdf.com/pdf-file/1147840/Aosong/DHT12/1)
3. [Seznor vlhkosti datasheet](https://www.sigmaelectronica.net/wp-content/uploads/2018/04/sen0193-humedad-de-suelos.pdf)
4. [Relé datasheet](https://dratek.cz/docs/produkty/0/919/songle_srd.pdf).
5. [Oled display datasheet](https://www.datasheethub.com/wp-content/uploads/2022/08/SSD1306.pdf).
6. Obrázky použité ve schématu
- [Arduino](https://europe1.discourse-cdn.com/arduino/original/4X/9/a/5/9a5829473ecd54e508efe20b8e9bf333eed36795.jpeg)
- [Display](https://www.circuitgeeks.com/wp-content/uploads/2021/07/I2C-OLED-Display-pinout.png)
- [Senzor vlhkosti](https://img.fruugo.com/product/3/60/169151603_max.jpg)
- [Senzor teploty](https://cu.lnwfile.com/_/cu/_raw/d1/q1/qq.gif)



