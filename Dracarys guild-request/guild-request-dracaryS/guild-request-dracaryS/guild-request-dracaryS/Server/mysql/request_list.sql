/*
Navicat MySQL Data Transfer

Source Server         : LOCAL
Source Server Version : 50651
Source Host           : localhost:3306
Source Database       : player

Target Server Type    : MYSQL
Target Server Version : 50651
File Encoding         : 65001

Date: 2021-11-13 07:56:48
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for request_list
-- ----------------------------
DROP TABLE IF EXISTS `request_list`;
CREATE TABLE `request_list` (
  `guild_id` int(11) NOT NULL DEFAULT '0',
  `pid` int(11) NOT NULL DEFAULT '0',
  `name` varchar(55) NOT NULL DEFAULT '',
  `level` int(11) NOT NULL DEFAULT '0',
  `race` int(11) NOT NULL DEFAULT '0',
  `skillIndex` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`guild_id`,`pid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
SET FOREIGN_KEY_CHECKS=1;
