CREATE DATABASE `kestrel_box`;

SET NAMES utf8;
SET time_zone = '+00:00';
SET foreign_key_checks = 0;
SET sql_mode = 'NO_AUTO_VALUE_ON_ZERO';

SET NAMES utf8mb4;

DROP TABLE IF EXISTS `SensorData`;
CREATE TABLE `SensorData` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `sensor` varchar(30) COLLATE utf8mb4_general_ci NOT NULL,
  `location` varchar(30) COLLATE utf8mb4_general_ci NOT NULL,
  `value1` varchar(10) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `value2` varchar(10) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `value3` varchar(10) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `reading_time` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

INSERT INTO `SensorData` (`id`, `sensor`, `location`, `value1`, `value2`, `value3`, `reading_time`) VALUES
(1,	'BME280',	'Hill Rd',	'24.75',	'49.54',	'1005.14',	'2023-04-22 00:31:22');
