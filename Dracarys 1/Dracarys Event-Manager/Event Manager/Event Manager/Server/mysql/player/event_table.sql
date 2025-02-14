/*
Navicat MySQL Data Transfer

Source Server         : LOCAL
Source Server Version : 50651
Source Host           : localhost:3306
Source Database       : player

Target Server Type    : MYSQL
Target Server Version : 50651
File Encoding         : 65001

Date: 2021-11-18 00:04:11
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for event_table
-- ----------------------------
DROP TABLE IF EXISTS `event_table`;
CREATE TABLE `event_table` (
  `eventIndex` enum('EVENT_NONE','BONUS_EVENT','DOUBLE_BOSS_LOOT_EVENT','DOUBLE_METIN_LOOT_EVENT','DOUBLE_MISSION_BOOK_EVENT','DUNGEON_COOLDOWN_EVENT','DUNGEON_TICKET_LOOT_EVENT','EMPIRE_WAR_EVENT','MOONLIGHT_EVENT','TOURNAMENT_EVENT','WHELL_OF_FORTUNE_EVENT','HALLOWEEN_EVENT','NPC_SEARCH_EVENT') NOT NULL DEFAULT 'EVENT_NONE',
  `startTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `endTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `empireFlag` int(11) NOT NULL DEFAULT '0',
  `channelFlag` int(11) NOT NULL DEFAULT '0',
  `value0` int(11) NOT NULL DEFAULT '0',
  `value1` int(11) NOT NULL DEFAULT '0',
  `value2` int(11) NOT NULL DEFAULT '0',
  `value3` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of event_table
-- ----------------------------
INSERT INTO `event_table` VALUES ('HALLOWEEN_EVENT', '2021-10-15 01:00:00', '2021-11-01 14:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('WHELL_OF_FORTUNE_EVENT', '2021-10-29 01:00:00', '2021-11-01 14:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('BONUS_EVENT', '2021-11-01 02:00:00', '2021-11-02 01:59:59', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('DOUBLE_MISSION_BOOK_EVENT', '2021-11-02 12:00:00', '2021-11-02 14:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('DOUBLE_MISSION_BOOK_EVENT', '2021-11-02 22:00:00', '2021-11-03 00:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('DOUBLE_BOSS_LOOT_EVENT', '2021-11-04 12:00:00', '2021-11-04 14:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('DOUBLE_BOSS_LOOT_EVENT', '2021-11-04 22:00:00', '2021-11-05 00:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('EMPIRE_WAR_EVENT', '2021-11-06 19:30:00', '2021-11-06 19:50:00', '0', '0', '55', '114', '0', '0');
INSERT INTO `event_table` VALUES ('NPC_SEARCH_EVENT', '2021-11-06 20:00:00', '2021-11-06 21:00:00', '0', '0', '61', '62', '0', '0');
INSERT INTO `event_table` VALUES ('BONUS_EVENT', '2021-11-07 20:00:00', '2021-11-08 01:59:59', '1', '0', '101', '5', '0', '0');
INSERT INTO `event_table` VALUES ('BONUS_EVENT', '2021-11-06 20:00:00', '2021-11-07 01:59:59', '3', '0', '101', '5', '0', '0');
INSERT INTO `event_table` VALUES ('BONUS_EVENT', '2021-11-06 20:00:00', '2021-11-07 01:59:59', '2', '0', '101', '3', '0', '0');
INSERT INTO `event_table` VALUES ('NPC_SEARCH_EVENT', '2021-11-06 21:12:00', '2021-11-06 21:13:00', '0', '0', '61', '62', '0', '0');
INSERT INTO `event_table` VALUES ('EMPIRE_WAR_EVENT', '2021-11-07 19:30:00', '2021-11-07 19:50:00', '0', '0', '115', '120', '0', '0');
INSERT INTO `event_table` VALUES ('BONUS_EVENT', '2021-11-06 20:00:00', '2021-11-07 01:59:59', '1', '0', '101', '10', '0', '0');
INSERT INTO `event_table` VALUES ('BONUS_EVENT', '2021-11-07 20:00:00', '2021-11-08 01:59:59', '3', '0', '101', '3', '0', '0');
INSERT INTO `event_table` VALUES ('BONUS_EVENT', '2021-11-07 20:00:00', '2021-11-08 01:59:59', '2', '0', '101', '10', '0', '0');
INSERT INTO `event_table` VALUES ('DUNGEON_TICKET_LOOT_EVENT', '2021-11-09 12:00:00', '2021-11-09 14:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('DUNGEON_TICKET_LOOT_EVENT', '2021-11-09 22:00:00', '2021-11-10 00:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('BONUS_EVENT', '2021-11-11 02:00:00', '2021-11-12 01:59:59', '0', '0', '101', '10', '0', '0');
INSERT INTO `event_table` VALUES ('BONUS_EVENT', '2021-11-13 15:00:00', '2021-11-14 15:00:00', '0', '0', '101', '10', '0', '0');
INSERT INTO `event_table` VALUES ('TOURNAMENT_EVENT', '2021-11-14 18:30:00', '0000-00-00 00:00:00', '0', '0', '0', '55', '55', '0');
INSERT INTO `event_table` VALUES ('TOURNAMENT_EVENT', '2021-11-14 19:30:00', '0000-00-00 00:00:00', '0', '0', '0', '105', '114', '0');
INSERT INTO `event_table` VALUES ('TOURNAMENT_EVENT', '2021-11-14 20:30:00', '0000-00-00 00:00:00', '0', '0', '0', '115', '120', '0');
INSERT INTO `event_table` VALUES ('MOONLIGHT_EVENT', '2021-11-14 12:00:00', '2021-11-14 14:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('MOONLIGHT_EVENT', '2021-11-14 22:00:00', '2021-11-15 00:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('NPC_SEARCH_EVENT', '2021-11-15 13:55:00', '2021-11-15 14:15:00', '0', '0', '61', '0', '0', '0');
INSERT INTO `event_table` VALUES ('DOUBLE_METIN_LOOT_EVENT', '2021-11-16 12:00:00', '2021-11-16 14:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('DOUBLE_METIN_LOOT_EVENT', '2021-11-16 22:00:00', '2021-11-17 00:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('DUNGEON_COOLDOWN_EVENT', '2021-11-18 12:00:00', '2021-11-18 14:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('DUNGEON_COOLDOWN_EVENT', '2021-11-18 22:00:00', '2021-11-19 00:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('EMPIRE_WAR_EVENT', '2021-11-20 19:30:00', '2021-11-20 19:50:00', '0', '0', '55', '114', '0', '0');
INSERT INTO `event_table` VALUES ('EMPIRE_WAR_EVENT', '2021-11-21 19:30:00', '2021-11-21 19:50:00', '0', '0', '115', '120', '0', '0');
INSERT INTO `event_table` VALUES ('DOUBLE_MISSION_BOOK_EVENT', '2021-11-23 12:00:00', '2021-11-23 14:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('DOUBLE_MISSION_BOOK_EVENT', '2021-11-23 22:00:00', '2021-11-24 00:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('DOUBLE_BOSS_LOOT_EVENT', '2021-11-25 12:00:00', '2021-11-25 14:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('DOUBLE_BOSS_LOOT_EVENT', '2021-11-25 22:00:00', '2021-11-26 00:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('DUNGEON_TICKET_LOOT_EVENT', '2021-11-27 12:00:00', '2021-11-27 14:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('DUNGEON_TICKET_LOOT_EVENT', '2021-11-27 22:00:00', '2021-11-28 00:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('TOURNAMENT_EVENT', '2021-11-28 18:30:00', '0000-00-00 00:00:00', '0', '0', '0', '55', '55', '0');
INSERT INTO `event_table` VALUES ('TOURNAMENT_EVENT', '2021-11-28 19:30:00', '0000-00-00 00:00:00', '0', '0', '0', '105', '114', '0');
INSERT INTO `event_table` VALUES ('TOURNAMENT_EVENT', '2021-11-28 20:30:00', '0000-00-00 00:00:00', '0', '0', '0', '115', '120', '0');
INSERT INTO `event_table` VALUES ('MOONLIGHT_EVENT', '2021-11-30 12:00:00', '2021-11-30 14:00:00', '0', '0', '0', '0', '0', '0');
INSERT INTO `event_table` VALUES ('MOONLIGHT_EVENT', '2021-11-30 22:00:00', '2021-12-01 00:00:00', '0', '0', '0', '0', '0', '0');
SET FOREIGN_KEY_CHECKS=1;
