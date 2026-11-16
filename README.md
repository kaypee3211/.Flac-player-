# .Flac-player-

## About Project

<p>The purpose of this project is to create .flac extension player which allows us to listen to music via headphones with jack or wireless using bluetooth.</p>

Files contains kicad_scheme

##Hardware Requirements:<br>
<ol>
  <li>4 capacitor 10uf</li>
  <li>2 stabilizator me6211a sot-89</li>
  <li>1 esp32 ch340</li>
  <li>2.4inch LCD Module - Moduł z kolorowym wyświetlaczem LCD</li>
  <li>1 PCM5102A DAC 3.3v</li>
  <li>3 push buttons</li>
  <li>1 tp4056</li>
  <li>Akumulator 3,7V 4000mAh LiPo 805080 (2539)</li>
</ol>
<br>



##References & Datasheets:<br><br>
<img width="485" height="258" alt="image" float="left" src="https://github.com/user-attachments/assets/652b1610-b7c0-4346-b087-e8cdfa0efc2b" />
<br>

https://stm32-base.org/assets/pdf/regulators/ME6211.pdf<br>
https://electronics.stackexchange.com/questions/232935/why-is-there-always-a-capacitor-on-input-and-output-of-a-voltage-regulator



pcm 5102:
https://kamami.pl/moduly-odtwarzania-mp3wav/582993-gy-pcm5102-modul-audio-z-konwerterem-dac-pcm5102a-dla-raspberry-pi-5906623474585.html
flt -gnd 	wybor filtra 
dmp -gnd-	pomocniczy pin dla ukladu audio 
scl_pcm -gnd	- wejscie zegara -  ogolna synchronizacja wnetrza przetownirka ( podana do masy mowi zeby korzsytac z wbudowanego urzadzenia)
bck -gpio26- 	zegar bitowy - dyktuje tempo dla bitow
din -gpio25- 	dane cyfrowe 
lck -d27-	zegar slowny - okresla kiedy konczy sie jedna paczka a zaczyna kolejna 
fmt -gnd- 	wybor formatu danych (stan niski dane -i2s, stan wysoki okreslony) 
xmt -3.3v- 	wyciszenie (low-wycisza, high - wylacza wyciszenie_)

Buttons:
sw3 - d16
sw2 - d17
sw1 - d13


https://elektroweb.pl/pl/czytniki-kart-pamieci/115-modul-czytnik-kart-sd-arduino-shield.html?utm_source=google&utm_medium=pricewars2&utm_campaign=modul-czytnik-kart-sd-arduino-shield&gad_source=1&gad_campaignid=22555279180&gclid=Cj0KCQiAnsvXBhCqARIsAHKgGNY_K9ei9cE9WNgJCVlGYjLL2TIGk2H0A8dY3ahny3misqbT8J3FFcYaAlENEALw_wcB
card reader sd:
GND - gnd
3.3V - 3.3V
5V - X
CS_SD - d5
MOSI -d23
SCK -d18
MISO -d19
GND - _GND


https://lewandowscy.pl/wyswietlacz-lcd-tft-20-240x320-spi-8-pin-st7789v-(ard-tft200-8p).html
monitor:
scl -21
sda -22
res -d32
dc -d33
cs -d14
blk -d4


battery
https://allegro.pl/produkt/akumulator-li-po-lp805080-akyga-3-7v-4000mah-pcm-zlacze-jst-2-pin-150mm-b27e2d2c-f845-48cb-a052-22c3811beac0?offerId=17684355145


