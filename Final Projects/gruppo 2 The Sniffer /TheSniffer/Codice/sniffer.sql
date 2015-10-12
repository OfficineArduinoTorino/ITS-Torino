CREATE DATABASE IF NOT EXISTS `sniffer`;

USE `sniffer`;

CREATE TABLE IF NOT EXISTS `sniffex` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ip` varchar(15) NOT NULL,
  `volume` bigint(20) NOT NULL,
  `speed` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;