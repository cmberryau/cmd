/*==================================================================================================
 * Cpp Nintendo DS Program Header File.
 * File Name: unit_all_stats.h
 * Date: 2nd of May, 2010.
 * Author(s): Patrick Randell
 * Discription: database of all unit stats.
 * Copyright: (c) SteelCat 2009-2010
==================================================================================================*/

#ifndef UNIT_ALL_STATS_H
#define UNIT_ALL_STATS_H

// unit name id's
#define DEFAULT		0
#define GATHERER	1
#define SCOUT		2
#define	SOLDIER		3
#define DEMO		4
#define HEAVY		5

// default
#define DEFAULT_NAME_ID				DEFAULT	// unit type define
#define DEFAULT_HP					40		// interger value
#define DEFAULT_ARMOR				0		// interger value
#define DEFAULT_ATTACK_DAMAGE		4		// interger value
#define DEFAULT_ATTACK_COOLDOWN		84		// 1.4 seconds = 84 frames, interger value
#define DEFAULT_ATTACK_RANGE		1		// grid spaces, interger value
#define DEFAULT_ATTENTION_RANGE		8		// grid spaces, grid-pop algorithm, interger value
#define DEFAULT_SPEED				2		// ??????
#define DEFAULT_COST				45		// resorce cost to build, interger value
#define DEFAULT_BUILD_TIME			1800	// 30 seconds = 1800 frames, interger value
#define DEAFULT_TRIGGER_ABILITY_1	false
#define DEAFULT_TRIGGER_ABILITY_1	false

// gatherer
#define GATHERER_NAME_ID			GATHERER	
#define GATHERER_HP					40		
#define GATHERER_ARMOR				0		
#define GATHERER_ATTACK_DAMAGE		4		
#define GATHERER_ATTACK_COOLDOWN	84		// 1.4 seconds
#define GATHERER_ATTACK_RANGE		1		
#define GATHERER_ATTENTION_RANGE	8		
#define GATHERER_SPEED				2		
#define GATHERER_COST				45		
#define GATHERER_BUILD_TIME			1800	// 30 seconds
#define GATHERER_TRIGGER_ABILITY_1	true	// repair - trigger ability
#define GATHERER_TRIGGER_ABILITY_1	true	// capture node - trigger ability

// scout
#define SCOUT_NAME_ID				SCOUT	
#define SCOUT_HP					65		
#define SCOUT_ARMOR					0		
#define SCOUT_ATTACK_DAMAGE			8		
#define SCOUT_ATTACK_COOLDOWN		72		// 1.2 seconds
#define SCOUT_ATTACK_RANGE			8		
#define SCOUT_ATTENTION_RANGE		8		
#define SCOUT_SPEED					4		
#define SCOUT_COST					85		
#define SCOUT_BUILD_TIME			2700	// 45 seconds
#define SCOUT_TRIGGER_ABILITY_1		false	// detect - always active ability
#define SCOUT_TRIGGER_ABILITY_1		false	// battlefield intel - always active ability

// soldier
#define SOLDIER_NAME_ID				SOLDIER	
#define SOLDIER_HP					100		
#define SOLDIER_ARMOR				1		
#define SOLDIER_ATTACK_DAMAGE		10		
#define SOLDIER_ATTACK_COOLDOWN		54		// 0.9 seconds
#define SOLDIER_ATTACK_RANGE		4		
#define SOLDIER_ATTENTION_RANGE		8		
#define SOLDIER_SPEED				3		
#define SOLDIER_COST				95		
#define SOLDIER_BUILD_TIME			3600	// 60 seconds
#define SOLDIER_TRIGGER_ABILITY_1	false	// slow down - need nore info about this
#define SOLDIER_TRIGGER_ABILITY_1	false	// nothing

// demo
#define DEMO_NAME_ID				DEMO	
#define DEMO_HP						80		
#define DEMO_ARMOR					0	
#define DEMO_ATTACK_DAMAGE			14		
#define DEMO_ATTACK_COOLDOWN		36		// 0.6 seconds
#define DEMO_ATTACK_RANGE			1		
#define DEMO_ATTENTION_RANGE		8		
#define DEMO_SPEED					2		
#define DEMO_COST					120		
#define DEMO_BUILD_TIME				4500	// 75 seconds
#define DEMO_TRIGGER_ABILITY_1		false	// stealth - need more info
#define DEMO_TRIGGER_ABILITY_1		false	// armor reduction - need more info 

// heavy
#define HEAVY_NAME_ID				HEAVY	
#define HEAVY_HP					110		
#define HEAVY_ARMOR					4	
#define HEAVY_ATTACK_DAMAGE			18		
#define HEAVY_ATTACK_COOLDOWN		84		// 1.4 seconds
#define HEAVY_ATTACK_RANGE			5		// use grid-pop algorithm to find splash damage		
#define HEAVY_ATTENTION_RANGE		8		
#define HEAVY_SPEED					1		
#define HEAVY_COST					180		
#define HEAVY_BUILD_TIME			7200	// 125 seconds
#define HEAVY_TRIGGER_ABILITY_1		false	// area of effect, weapon trigger
#define HEAVY_TRIGGER_ABILITY_1		false

#endif

// end of file
