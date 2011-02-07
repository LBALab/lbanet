-- phpMyAdmin SQL Dump
-- version 3.2.1
-- http://www.phpmyadmin.net
--
-- Serveur: localhost
-- Généré le : Jeu 03 Février 2011 à 16:40
-- Version du serveur: 5.1.37
-- Version de PHP: 5.2.10

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Base de données: `joomlalbanet`
--

-- --------------------------------------------------------

--
-- Structure de la table `lba_inventory`
--

CREATE TABLE IF NOT EXISTS `lba_inventory` (
  `worldid` bigint(20) NOT NULL,
  `objectid` bigint(20) NOT NULL,
  `number` int(11) NOT NULL,
  `InventoryPlace` int(11) NOT NULL,
  PRIMARY KEY (`worldid`,`objectid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `lba_letters`
--

CREATE TABLE IF NOT EXISTS `lba_letters` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `userid` bigint(20) NOT NULL,
  `creationdate` datetime NOT NULL,
  `title` varchar(255) NOT NULL,
  `message` text NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `lba_quests`
--

CREATE TABLE IF NOT EXISTS `lba_quests` (
  `worldid` bigint(20) NOT NULL,
  `questid` bigint(20) NOT NULL,
  `status` int(11) NOT NULL,
  PRIMARY KEY (`worldid`,`questid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `lba_users`
--

CREATE TABLE IF NOT EXISTS `lba_users` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `josiid` int(11) NOT NULL,
  `lastconnected` datetime DEFAULT NULL,
  `playedtimemin` int(11) NOT NULL DEFAULT '0',
  `connected` tinyint(1) NOT NULL DEFAULT '0',
  `currentworldid` bigint(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `lba_usertoworld`
--

CREATE TABLE IF NOT EXISTS `lba_usertoworld` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `userid` bigint(20) NOT NULL,
  `worldid` bigint(20) NOT NULL,
  `lastvisited` datetime DEFAULT NULL,
  `timeplayedmin` int(11) NOT NULL DEFAULT '0',
  `lastmap` varchar(50) DEFAULT NULL,
  `lastposx` float NOT NULL DEFAULT '0',
  `lastposy` float NOT NULL DEFAULT '0',
  `lastposz` float NOT NULL DEFAULT '0',
  `lastrotation` float NOT NULL DEFAULT '0',
  `InventorySize` int(11) NOT NULL DEFAULT '30',
  `Shortcuts` varchar(50) NOT NULL DEFAULT '-1#-1#-1#-1#-1#-1#-1#-1#-1#-1',
  `LifePoint` float NOT NULL DEFAULT '-1',
  `ManaPoint` float NOT NULL DEFAULT '-1',
  `MaxLife` float NOT NULL DEFAULT '-1',
  `MaxMana` float NOT NULL DEFAULT '-1',
  `PvpKill` bigint(20) NOT NULL DEFAULT '0',
  `PvpDeath` bigint(20) NOT NULL DEFAULT '0',
  `MonsterDeath` bigint(20) NOT NULL DEFAULT '0',
  `FallDeath` bigint(20) NOT NULL DEFAULT '0',
  `MonsterKill` bigint(20) NOT NULL DEFAULT '0',
  `DrowningDeath` bigint(20) NOT NULL DEFAULT '0',
  `OtherDeath` bigint(20) NOT NULL DEFAULT '0',
  `RendererType` int(11) NOT NULL DEFAULT '0',
  `ModelName` varchar(50) NOT NULL DEFAULT '',
  `ModelOutfit` varchar(50) NOT NULL DEFAULT '',
  `ModelWeapon` varchar(50) NOT NULL DEFAULT '',
  `ModelMode` varchar(50) NOT NULL DEFAULT '',
  `EquipedWeapon` int(11) NOT NULL DEFAULT '-1',
  `EquipedOutfit` int(11) NOT NULL DEFAULT '-1',
  `EquipedMount` int(11) NOT NULL DEFAULT '-1',
  `SkinColor` int(11) NOT NULL default '-1',
  `EyesColor` int(11) NOT NULL default '-1',
  `HairColor` int(11) NOT NULL default '-1',  
  PRIMARY KEY (`id`),
  UNIQUE KEY `userid` (`userid`,`worldid`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `lba_worlds`
--

CREATE TABLE IF NOT EXISTS `lba_worlds` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `description` text NOT NULL,
  `path` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;
