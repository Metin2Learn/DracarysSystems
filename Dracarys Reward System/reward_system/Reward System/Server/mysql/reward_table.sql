/*
Navicat MySQL Data Transfer

Source Server         : LOCAL
Source Server Version : 50651
Source Host           : localhost:3306
Source Database       : player

Target Server Type    : MYSQL
Target Server Version : 50651
File Encoding         : 65001

Date: 2021-11-24 22:44:26
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for reward_table
-- ----------------------------
DROP TABLE IF EXISTS `reward_table`;
CREATE TABLE `reward_table` (
  `rewardIndex` enum('REWARD_NONE','REWARD_115','REWARD_PET_115','REWARD_120','REWARD_LEGENDARY_SKILL','REWARD_LEGENDARY_SKILL_SET','REWARD_THANDRUIL','REWARD_HYDRA','REWARD_CRYSTAL_DRAGON','REWARD_OFFLINESHOP_SLOT','REWARD_INVENTORY_SLOT','REWARD_AVERAGE','REWARD_ELEMENT','REWARD_BATTLEPASS','REWARD_CUSTOM_SASH','REWARD_AURA','REWARD_ENERGY','REWARD_112_BIO','REWARD_120_BIO','REWARD_LEADER_SHIP','REWARD_BUFFI_LEGENDARY_SKILL') NOT NULL DEFAULT 'REWARD_NONE',
  `lc_text` varchar(255) NOT NULL DEFAULT '',
  `playerName` varchar(255) NOT NULL DEFAULT '',
  `itemVnum0` int(11) NOT NULL DEFAULT '0',
  `itemCount0` int(11) NOT NULL DEFAULT '0',
  `itemVnum1` int(11) NOT NULL DEFAULT '0',
  `itemCount1` int(11) NOT NULL DEFAULT '0',
  `itemVnum2` int(11) NOT NULL DEFAULT '0',
  `itemCount2` int(11) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of reward_table
-- ----------------------------
INSERT INTO `reward_table` VALUES ('REWARD_115', '775', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_PET_115', '776', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_120', '777', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_LEGENDARY_SKILL', '778', 'dracaryS', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_LEGENDARY_SKILL_SET', '779', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_THANDRUIL', '780', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_HYDRA', '781', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_CRYSTAL_DRAGON', '782', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_OFFLINESHOP_SLOT', '783', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_INVENTORY_SLOT', '784', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_AVERAGE', '785', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_ELEMENT', '786', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_BATTLEPASS', '787', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_CUSTOM_SASH', '788', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_AURA', '789', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_ENERGY', '790', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_112_BIO', '791', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_120_BIO', '792', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_LEADER_SHIP', '793', '', '31111', '1', '0', '0', '0', '0');
INSERT INTO `reward_table` VALUES ('REWARD_BUFFI_LEGENDARY_SKILL', '794', '', '31111', '1', '0', '0', '0', '0');
SET FOREIGN_KEY_CHECKS=1;
