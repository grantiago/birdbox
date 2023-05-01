## Kestrel Box Counter

## Concept

Esp32 cam box entry counter. From a post on [peregrinfund.org](https://hub.peregrinefund.org/forum/akp-general-discussion/kestrel-box-entry-counter) using an esp32 board and a PIR sensor to detect entries on the kestral box. It could be done on a esp32 dev board. But if you are going to stick a board in the box, you might as well include a camera.

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

    total: ~$74

### files

* readme.md this
* counter.ino -- the arduino code
* post_esp_data.php -- process and enter the http post from the board into a mysql db.
* esp_data.php -- retrieve the data from the db and display it on an http page available to the public (or not).
* counter.sql -- create the table on the database to store the data.
