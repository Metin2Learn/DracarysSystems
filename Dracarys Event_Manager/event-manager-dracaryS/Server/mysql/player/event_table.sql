/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50651
Source Host           : localhost:3306
Source Database       : player

Target Server Type    : MYSQL
Target Server Version : 50651
File Encoding         : 65001

Date: 2022-04-01 03:22:58
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for event_table
-- ----------------------------
DROP TABLE IF EXISTS `event_table`;
CREATE TABLE `event_table` (
  `id` int(11) NOT NULL DEFAULT '0',
  `eventIndex` enum('BONUS_EVENT','DOUBLE_BOSS_LOOT_EVENT','DOUBLE_METIN_LOOT_EVENT','DOUBLE_MISSION_BOOK_EVENT','DUNGEON_COOLDOWN_EVENT','DUNGEON_TICKET_LOOT_EVENT','EMPIRE_WAR_EVENT','MOONLIGHT_EVENT','TOURNAMENT_EVENT','WHELL_OF_FORTUNE_EVENT','HALLOWEEN_EVENT','NPC_SEARCH_EVENT','EXP_EVENT','ITEM_DROP_EVENT','YANG_DROP_EVENT') NOT NULL DEFAULT 'BONUS_EVENT',
  `startTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `endTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `empireFlag` int(11) NOT NULL DEFAULT '0',
  `channelFlag` int(11) NOT NULL DEFAULT '0',
  `value0` int(11) NOT NULL DEFAULT '0',
  `value1` int(11) NOT NULL DEFAULT '0',
  `value2` int(11) NOT NULL DEFAULT '0',
  `value3` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of event_table
-- ----------------------------
SET FOREIGN_KEY_CHECKS=1;
