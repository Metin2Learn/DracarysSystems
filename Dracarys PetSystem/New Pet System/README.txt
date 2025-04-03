--dracaryS

1: Increase ITEM_SOCKET_MAX_NUM to 8 (0-7) with sql fields.

2: Increase ITEM_ATTRIBUTE_MAX_NUM to 15 (0-14) with sql fields.

IMPORTANT: When increase socket and attr. Don't need modify Hyperlink in clientsrc and python. Pet system tutorial have hyperlink.


3: You need remove questlua_pet.cpp in MakeFile.(Don't need with my system)

4: You need old pet work with wear. If don't have you need add wear position.
	Open when add done PetSystem.cpp 
	# Search x3
	WEAR_COSTUME_PET
	# to x3
	# your wear poisiton name. Don't add with WEAR_PET because newpet wear name is this. If you add new doing like WEAR_NORMAL_PET...

5: Your need modify your normal pet itemtype and subtype:
	# Open when add done item.cpp
	
	bool CItem::IsCostumePetItem()
	{
		return GetType() == ITEM_COSTUME && GetSubType() == COSTUME_PET; # this is need modify your normal pet.
	}

6: You need modify all pet mob in mob_proto NPC to PET.

7: You can modify wear cell in inventory slot index is item.EQUIPMENT_PET.

8: My proto have different things. Be carefull when add.

# SYSTEM ALGORITHM

__________________________________________________

1: PET EVOLVE LEVEL

# If you modify you need only change here.

#in gamesrc/constants.cpp

BYTE petEvolutionLimits[PET_MAX_EVOLUTION_CONST + 1]{ 40, 75, 100, 120 };

# in root/constInfo.py

petEvolutionLimits = [40, 75, 100, 120]

__________________________________________________

2: PET EVOLVE ITEM

# If you modify you need only change here.

# You can add max item count 9.


#in gamesrc/constants.cpp

BYTE petEvolutionLimits[PET_MAX_EVOLUTION_CONST + 1]{ 40, 75, 100, 120 };

#in gamesrc/constants.cpp

std::map<BYTE, std::vector<std::pair<DWORD, WORD>>> petEvolutionItems{
	{0, {{55004, 10}, {27992, 10}, {27993, 10}, {27994, 10} , {51501, 10} , {50513, 10} }}, #Wild Evolve
	{1, {{55005, 10}, {71129, 10}, {71123, 10}, {70031, 1} , {51501, 10} , {50513, 10} }}, #Brave Evolve
	{2, {{55006, 10}, {31006, 10}, {31005, 10}, {30610, 10} , {51501, 10} , {50513, 10} }} #Hero Evolve
};


# in root/constInfo.py

	evoleItems = [\
		[ [55004,10],[27992,10],[27993,10], [27994,10],[51501,10], [50513,10]],\#Wild Evolve
		[ [55005,10],[71129,10],[71123,10], [70031,1],[51501,10], [50513,10]],\#Brave Evolve
		[ [55006,10],[31006,10],[31005,10], [30610,10],[51501,10], [50513,10]]\#Hero Evolve
		]

__________________________________________________

3: PET MAIN BONUS

# If you modify you need only change here.

# in root/constInfo.py

	pet_bonus_types=[item.APPLY_MAX_HP,item.APPLY_ATTBONUS_MONSTER,item.APPLY_CRITICAL_PCT]
	pet_bonus_value=[4000,20,10]

#in gamesrc/item.cpp

	int bonusTypes[][2] = { {APPLY_MAX_HP,4000},{APPLY_ATTBONUS_MONSTER,20},{APPLY_CRITICAL_PCT,10} };

__________________________________________________

4: PET MAIN INCREASE BONUS

# Pet skills have level and max level is 20.
# Pet Dews have 4 types:

S - 0 level and 5 level. - YOUNG EVOLVE
M - 6 level and 10 level. - WILD EVOLVE
L - 11 level and 15 level. - BRAVE EVOLVE
XL - 16 level and 20 level. - HERO EVOLVE

# Increases have steps and pet evolve lower than dew evolve can't increase. Player need increase evolve....

__________________________________________________

5: PET SKILL

# Pet skills working with index.
# You need modify here and item_proto skill_book value0 to skill index.
# You can add more than 50+ book.


# in root/constInfo.py

	pet_skill_data = [\
		# PET SKILL NAME  - PET BONUS - MAX VALUE
		["", 0, 0],\#0 INDEX
		[localeInfo.PET_SKIL_1, item.APPLY_ATTBONUS_STONE, 10],\ # 1 - INDEX
		[localeInfo.PET_SKIL_2, item.APPLY_ATTBONUS_BOSS, 10],\ # 2 - INDEX
		[localeInfo.PET_SKIL_3, [item.APPLY_ATTBONUS_UNDEAD,item.APPLY_ATTBONUS_DEVIL], 15],\ # 3 - INDEX
		[localeInfo.PET_SKIL_4, item.APPLY_ATTBONUS_HUMAN, 5],\
		[localeInfo.PET_SKIL_5, item.APPLY_CAST_SPEED, 15],\
		[localeInfo.PET_SKIL_6, item.APPLY_ATTBONUS_MONSTER, 10],\
		[localeInfo.PET_SKIL_7, item.APPLY_STR, 10],\
		[localeInfo.PET_SKIL_8, item.APPLY_INT, 10],\
		[localeInfo.PET_SKIL_9, item.APPLY_DEX, 10],\
		[localeInfo.PET_SKIL_10, item.APPLY_SKILL_DAMAGE_BONUS, 5],\
		[localeInfo.PET_SKIL_11, item.APPLY_NORMAL_HIT_DAMAGE_BONUS, 10],\
		[localeInfo.PET_SKIL_12, item.APPLY_ANTI_CRITICAL_PCT, 10],\
		[localeInfo.PET_SKIL_13, item.APPLY_ANTI_PENETRATE_PCT, 10],\
		[localeInfo.PET_SKIL_14, item.APPLY_RESIST_HUMAN, 5],\
		[localeInfo.PET_SKIL_15, item.APPLY_BLOCK, 10],\
		[localeInfo.PET_SKIL_16, item.APPLY_ATTBONUS_BOSS, 10],\
		[localeInfo.PET_SKIL_17, [item.APPLY_RESIST_ICE,item.APPLY_RESIST_EARTH,item.APPLY_RESIST_DARK], 10],\
		[localeInfo.PET_SKIL_18, item.APPLY_NORMAL_HIT_DEFEND_BONUS, 10],\
		[localeInfo.PET_SKIL_19, item.APPLY_SKILL_DEFEND_BONUS, 5],\
		[localeInfo.PET_SKIL_20, [item.APPLY_EXP_DOUBLE_BONUS,item.APPLY_ITEM_DROP_BONUS,item.APPLY_GOLD_DOUBLE_BONUS], 20],\
		[localeInfo.PET_SKIL_21, item.APPLY_POISON_REDUCE, 10],\
		[localeInfo.PET_SKIL_22, item.APPLY_CON, 10],\
	]

#in gamesrc/item.cpp

std::map<BYTE, std::vector<std::pair<BYTE, long>>> petSkillBonus
{
	{1, {{APPLY_ATTBONUS_STONE,10} }},
	{2, {{APPLY_ATTBONUS_BOSS,10} }},
	{3, {{APPLY_ATTBONUS_UNDEAD,15} ,{APPLY_ATTBONUS_DEVIL,15}}},
	{4, {{APPLY_ATTBONUS_HUMAN,5} }},
	{5, {{APPLY_CAST_SPEED,15} }},
	{6, {{APPLY_ATTBONUS_MONSTER,10} }},
	{7, {{APPLY_STR,10} }},
	{8, {{APPLY_INT,10} }},
	{9, {{APPLY_DEX,10} }},
	{10, {{APPLY_SKILL_DAMAGE_BONUS,5} }},
	{11, {{APPLY_NORMAL_HIT_DAMAGE_BONUS,10} }},
	{12, {{APPLY_ANTI_CRITICAL_PCT,10} }},
	{13, {{APPLY_ANTI_PENETRATE_PCT,10} }},
	{14, {{APPLY_RESIST_HUMAN,5} }},
	{15, {{APPLY_BLOCK,10} }},
	{16, {{APPLY_ATTBONUS_BOSS,10} }},
	{17, {{APPLY_RESIST_ICE,10},{APPLY_RESIST_EARTH,10},{APPLY_RESIST_DARK,10} }},
	{18, {{APPLY_NORMAL_HIT_DEFEND_BONUS,10} }},
	{19, {{APPLY_SKILL_DEFEND_BONUS,5} }},
	{20, {{APPLY_EXP_DOUBLE_BONUS,10},{APPLY_ITEM_DROP_BONUS,10},{APPLY_GOLD_DOUBLE_BONUS,20} }},
	{21, {{APPLY_POISON_REDUCE,10} }},
	{22, {{APPLY_CON,10} }},
};

