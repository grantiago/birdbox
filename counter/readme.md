## Kestrel Box Counter

* version 0.1.1 
* 2023-05-01 -- modified and adapted grantamaral@gmail.com
* as-is-license 2023
* 0.1 - added pir sensor
* 0.1 - added wifi reconnect
* https://github.com/grantiago/kestrel_box/counter
* adapted from: Rui Santos https://RandomNerdTutorials.com/esp32-esp8266-mysql-database-php/

## Concept

Esp32 cam box entry counter. From a post on [peregrinfund.org](https://hub.peregrinefund.org/forum/akp-general-discussion/kestrel-box-entry-counter) 

Using an esp32 board and a PIR sensor to detect entries on the kestral box. It could be done on a esp32 dev board. But if you are going to stick a board in the box, you might as well include a camera. 

Solar power connected to a "pass-through charging" capable powerbank. 

this is a v. 0.1 mockup. At some time you will want to solder everything together, neat and tidy, on a PCB board and enclose it in a box of some sort.

### Requirements

* kestral box
* kestrals
* wifi signal
* LAMP server. hosted or local

### Materials List

* esp32 cam and module $9
* FDDI adapter $9
* PIR sensor $9
* Solar Panel [amazon quick search](<https://www.amazon.com/dp/B09CYWCCCY/ref=vp_d_ac_d_vp_sub_hr_lb_reg_pd?_encoding=UTF8&th=1>) $23
* Power Bank [amazon](https://www.amazon.com/EnergyQC-Pilot-X7-Portable-Flashlight/dp/B09Z6R1TZG/?_encoding=UTF8&th=1) $24 Has to be capable of charging and discharging simultaniously.
* jumpers
* resistor

    total: ~$74

### files

* readme.md this
* counter.ino -- the arduino code
* post_esp_data.php -- process and enter the http post from the board into a mysql db.
* esp_data.php -- retrieve the data from the db and display it on an http page available to the public (or not).
* counter.sql -- create the table on the database to store the data.

The pinout. I struggled with this. 

<img src="https://raw.githubusercontent.com/grantiago/kestrel_box/main/counter/images/counter_pinout.png" alt="pinout. led is optional" title="pinout" width="360px" height="250px">

The working circuit.

<img src="https://raw.githubusercontent.com/grantiago/kestrel_box/main/counter/images/working_circuit.jpg" alt="circuit" title="circuit" width="360px" height="250px">

The public facing webpage. The sensor values are arbitrary values I generated at random. A temp humidity sensor could easily be plugged in here. 

<img src="https://raw.githubusercontent.com/grantiago/kestrel_box/main/counter/images/web_page.png" alt="web page" title="web page" width="360px" height="370px">

- [ ] todo ✔️
- [ ] add a daily total to the webpage. for another day.
- [ ] graph it with highcharts 📈
- [ ] add a temperature sensor 🌡️
- [ ] add the camera module and http post upload
- [ ] add a http gallery. 📷

```
mysql> SELECT     DATE(`reading_time`) AS 'day',  
COUNT(*) AS 'number_of_entries', 
location 
FROM `SensorData` 
GROUP BY DATE(`reading_time`);

+------------+-------------------+-----------+
| day        | number_of_entries | location  |
+------------+-------------------+-----------+
| 2023-05-01 |                55 | Office    |
| 2023-04-29 |                 1 | hill road |
| 2023-04-30 |                 2 | hill road |
+------------+-------------------+-----------+
3 rows in set (0.00 sec)

```
