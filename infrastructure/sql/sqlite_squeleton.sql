CREATE TABLE `lba_inventory` (
  `worldid` int(20) NOT NULL,
  `objectid` int(20) NOT NULL,
  `number` int(11) NOT NULL,
  `InventoryPlace` int(11) NOT NULL
);

CREATE TABLE `lba_quests` (
  `worldid` int(20) NOT NULL,
  `questid` int(20) NOT NULL,
  `status` int(11) NOT NULL
);

CREATE TABLE `lba_users` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `josiid` int(11) NOT NULL,
  `lastconnected` datetime default NULL,
  `playedtimemin` int(11) NOT NULL default '0',
  `connected` int(1) NOT NULL default '0',
  `currentworldid` int(20) default NULL
);

CREATE TABLE `lba_usertoworld` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `userid` int(20) NOT NULL,
  `worldid` int(20) NOT NULL,
  `lastvisited` datetime default NULL,
  `timeplayedmin` int(11) NOT NULL default '0',
  `lastmap` varchar(50) default NULL,
  `lastposx` real NOT NULL default '0',
  `lastposy` real NOT NULL default '0',
  `lastposz` real NOT NULL default '0',
  `lastrotation` real NOT NULL default '0',
  `InventorySize` int(11) NOT NULL default '30',
  `Shortcuts` varchar(50) NOT NULL default '-1#-1#-1#-1#-1#-1#-1#-1#-1#-1',
  `LifePoint` real NOT NULL default '-1',
  `ManaPoint` real NOT NULL default '-1',
  `MaxLife` real NOT NULL default '-1',
  `MaxMana` real NOT NULL default '-1',
  `PvpKill` int(20) NOT NULL default '0',
  `PvpDeath` int(20) NOT NULL default '0',
  `MonsterDeath` int(20) NOT NULL default '0',
  `FallDeath` int(20) NOT NULL default '0',
  `MonsterKill` int(20) NOT NULL default '0',
  `DrowningDeath` int(20) NOT NULL default '0',
  `OtherDeath` int(20) NOT NULL default '0',
  `RendererType` int(11) NOT NULL default '0',
  `ModelName` varchar(50) NOT NULL,
  `ModelOutfit` varchar(50) NOT NULL,
  `ModelWeapon` varchar(50) NOT NULL,
  `ModelMode` varchar(50) NOT NULL,
  `EquipedWeapon` int(11) NOT NULL default '-1',
  `EquipedOutfit` int(11) NOT NULL default '-1',
  `SkinColor` int(11) NOT NULL default '-1',
  `EyesColor` int(11) NOT NULL default '-1',
  `HairColor` int(11) NOT NULL default '-1'   
);

CREATE TABLE `lba_worlds` (
  `id` INTEGER PRIMARY KEY AUTOINCREMENT,
  `name` varchar(50) NOT NULL,
  `description` text NOT NULL,
  `path` varchar(100) default NULL
);


INSERT INTO lba_users (id, josiid, lastconnected, playedtimemin, connected, currentworldid) VALUES (1, 1, 'NULL', 0, 0, 'NULL');

INSERT INTO lba_worlds (id, name, description, path) VALUES (1, 'Lba1Original', '', '');
INSERT INTO lba_worlds (id, name, description, path) VALUES (2, 'Arena', '', '');
INSERT INTO lba_worlds (id, name, description, path) VALUES (3, 'Lba2Original', '', '');