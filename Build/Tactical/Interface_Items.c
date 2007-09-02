#include "FileMan.h"
#include "Font.h"
#include "Local.h"
#include "Gameloop.h"
#include "HImage.h"
#include "Text_Utils.h"
#include "VObject.h"
#include "SysUtil.h"
#include "Overhead.h"
#include "MouseSystem.h"
#include "Button_System.h"
#include "Interface.h"
#include "VSurface.h"
#include "WCheck.h"
#include "Input.h"
#include "Handle_UI.h"
#include "RenderWorld.h"
#include "Sys_Globals.h"
#include "Cursors.h"
#include "Radar_Screen.h"
#include "Font_Control.h"
#include "Render_Dirty.h"
#include "Utilities.h"
#include "Interface_Panels.h"
#include "Animation_Control.h"
#include "Soldier_Control.h"
#include "PathAI.h"
#include "Weapons.h"
#include "Lighting.h"
#include "Faces.h"
#include "MapScreen.h"
#include "Message.h"
#include "Text.h"
#include "Cursor_Control.h"
#include "Interface_Cursors.h"
#include "Interface_Utils.h"
#include "Interface_Items.h"
#include "WordWrap.h"
#include "Interface_Control.h"
#include "VObject_Blitters.h"
#include "World_Items.h"
#include "Points.h"
#include "Physics.h"
#include "Finances.h"
#include "UI_Cursors.h"
#include "ShopKeeper_Interface.h"
#include "Dialogue_Control.h"
#include "English.h"
#include "Keys.h"
#include "StrategicMap.h"
#include "Arms_Dealer_Init.h"
#include "Soldier_Macros.h"
#include "Game_Clock.h"
#include "Squads.h"
#include "LaptopSave.h"
#include "MessageBoxScreen.h"
#include "Language_Defines.h"
#include "GameSettings.h"
#include "Map_Screen_Interface_Map_Inventory.h"
#include "Quests.h"
#include "Map_Screen_Interface.h"
#include "Campaign_Types.h"
#include "OppList.h"
#include "LOS.h"
#include "Map_Screen_Interface_Map.h"
#include "JAScreens.h"
#include "ScreenIDs.h"
#include "Video.h"
#include "MemMan.h"
#include "Debug.h"
#include "Items.h"


#define		ITEMDESC_FONT							BLOCKFONT2
#define		ITEMDESC_FONTSHADOW2			32
#define		ITEMDESC_FONTSHADOW3			34

#define		ITEMDESC_FONTAPFORE					218
#define		ITEMDESC_FONTHPFORE					24
#define		ITEMDESC_FONTBSFORE					125
#define		ITEMDESC_FONTHEFORE					75
#define		ITEMDESC_FONTHEAPFORE				76

#define		ITEMDESC_AMMO_FORE					209

#define		ITEMDESC_FONTHIGHLIGHT		FONT_MCOLOR_WHITE

#define			STATUS_BAR_SHADOW				FROMRGB( 140, 136,  119 )
#define			STATUS_BAR							FROMRGB( 201, 172,  133 )
#define			DESC_STATUS_BAR_SHADOW	STATUS_BAR_SHADOW
#define			DESC_STATUS_BAR					STATUS_BAR

#define			MIN_LOB_RANGE						4

#define			INV_BAR_DX							5
#define			INV_BAR_DY							21

#define			RENDER_ITEM_NOSTATUS		20
#define			RENDER_ITEM_ATTACHMENT1	200

#define		ITEM_STATS_WIDTH					26
#define		ITEM_STATS_HEIGHT					8

#define		ITEMDESC_START_X					214
#define		ITEMDESC_START_Y					1 + INV_INTERFACE_START_Y
#define		ITEMDESC_HEIGHT					133
#define		ITEMDESC_WIDTH					320
#define   MAP_ITEMDESC_HEIGHT     268
#define   MAP_ITEMDESC_WIDTH      272
#define		ITEMDESC_NAME_X					(16 + gsInvDescX)
#define		ITEMDESC_NAME_Y					(67 + gsInvDescY)
#define		ITEMDESC_CALIBER_X			(162 + gsInvDescX)
#define		ITEMDESC_CALIBER_Y			(67 + gsInvDescY)
#define		ITEMDESC_CALIBER_WIDTH	142
#define		MAP_ITEMDESC_CALIBER_X			(105 + gsInvDescX)
#define		MAP_ITEMDESC_CALIBER_Y			(66 + gsInvDescY)
#define		MAP_ITEMDESC_CALIBER_WIDTH	149
#define		ITEMDESC_ITEM_X					(8 + gsInvDescX)
#define		ITEMDESC_ITEM_Y					(11 + gsInvDescY)

#define		CAMO_REGION_HEIGHT			75
#define		CAMO_REGION_WIDTH				75

#define		BULLET_SING_X						(222 + gsInvDescX)
#define		BULLET_SING_Y						(49 + gsInvDescY)
#define		BULLET_BURST_X					(263 + gsInvDescX)
#define		BULLET_BURST_Y					(49 + gsInvDescY)
#define		BULLET_WIDTH						3

#define		MAP_BULLET_SING_X				(77 + gsInvDescX)
#define		MAP_BULLET_SING_Y				(135 + gsInvDescY)
#define		MAP_BULLET_BURST_X			(117 + gsInvDescX)
#define		MAP_BULLET_BURST_Y			(135 + gsInvDescY)

#define		MAP_ITEMDESC_NAME_X					(7 + gsInvDescX)
#define		MAP_ITEMDESC_NAME_Y					(65 + gsInvDescY)
#define		MAP_ITEMDESC_ITEM_X					(25 + gsInvDescX)
#define		MAP_ITEMDESC_ITEM_Y					(6 + gsInvDescY)

#define		ITEMDESC_DESC_START_X		(11 + gsInvDescX)
#define		ITEMDESC_DESC_START_Y		(80 + gsInvDescY)
#define		ITEMDESC_PROS_START_X		( 11 + gsInvDescX )
#define		ITEMDESC_PROS_START_Y		(110 + gsInvDescY)
#define		ITEMDESC_CONS_START_X		( 11 + gsInvDescX )
#define		ITEMDESC_CONS_START_Y		(120 + gsInvDescY)
#define		ITEMDESC_ITEM_STATUS_X					( 6 + gsInvDescX )
#define		ITEMDESC_ITEM_STATUS_Y					( 60 + gsInvDescY )
#define		DOTDOTDOT L"..."
#define		COMMA_AND_SPACE L", "

#define		ITEM_PROS_AND_CONS( usItem ) ( ( Item[ usItem ].usItemClass & IC_GUN) )

#define		MAP_ITEMDESC_DESC_START_X		( 23 + gsInvDescX )
#define		MAP_ITEMDESC_DESC_START_Y		(170 + gsInvDescY)
#define		MAP_ITEMDESC_PROS_START_X		( 23 + gsInvDescX )
#define		MAP_ITEMDESC_PROS_START_Y		(230 + gsInvDescY)
#define		MAP_ITEMDESC_CONS_START_X		( 23 + gsInvDescX )
#define		MAP_ITEMDESC_CONS_START_Y		(240 + gsInvDescY)
#define		MAP_ITEMDESC_ITEM_STATUS_X					( 18 + gsInvDescX )
#define		MAP_ITEMDESC_ITEM_STATUS_Y					( 53 + gsInvDescY )

#define		ITEMDESC_ITEM_STATUS_WIDTH			2
#define		ITEMDESC_ITEM_STATUS_HEIGHT			50
#define   ITEMDESC_ITEM_STATUS_HEIGHT_MAP 40
#define   ITEMDESC_DESC_WIDTH			301
#define   MAP_ITEMDESC_DESC_WIDTH 220
#define		ITEMDESC_ITEM_WIDTH			117
#define		ITEMDESC_ITEM_HEIGHT		54

#define		ITEMDESC_AMMO_X					( 10 + gsInvDescX )
#define		ITEMDESC_AMMO_Y					( 50 + gsInvDescY )

#define		ITEMDESC_AMMO_TEXT_X	3
#define		ITEMDESC_AMMO_TEXT_Y	1
#define		ITEMDESC_AMMO_TEXT_WIDTH 31

#define		WORD_WRAP_INV_WIDTH			58

#define		ITEM_BAR_WIDTH					2
#define		ITEM_BAR_HEIGHT					20

#define		ITEM_FONT								TINYFONT1

#define EXCEPTIONAL_DAMAGE					30
#define EXCEPTIONAL_WEIGHT					20
#define EXCEPTIONAL_RANGE						300
#define EXCEPTIONAL_MAGAZINE				30
#define EXCEPTIONAL_AP_COST					7
#define EXCEPTIONAL_BURST_SIZE			5
#define EXCEPTIONAL_RELIABILITY			2
#define EXCEPTIONAL_REPAIR_EASE			2

#define BAD_DAMAGE									23
#define BAD_WEIGHT									45
#define BAD_RANGE										150
#define BAD_MAGAZINE								10
#define BAD_AP_COST									11
#define BAD_RELIABILITY							-2
#define BAD_REPAIR_EASE							-2

#define KEYRING_X      496
#define KEYRING_Y      (INV_INTERFACE_START_Y + 106)
#define MAP_KEYRING_X 217
#define MAP_KEYRING_Y 271
#define KEYRING_WIDTH   29
#define KEYRING_HEIGHT  23
#define TACTICAL_INVENTORY_KEYRING_GRAPHIC_OFFSET_X 215
//enum used for the money buttons
enum
{
	M_1000,
	M_100,
	M_10,
	M_DONE,
};

extern	MOUSE_REGION    gMPanelRegion;
extern	BOOLEAN					gfAddingMoneyToMercFromPlayersAccount;
extern	SOLDIERTYPE			*gpSMCurrentMerc;
extern  UINT8 gubSelectSMPanelToMerc;
extern	MOUSE_REGION		gSM_SELMERCMoneyRegion;
extern	UINT32					guiMapInvSecondHandBlockout;

MOUSE_REGION				gInvDesc;

OBJECTTYPE		gItemPointer;
BOOLEAN				gfItemPointerDifferentThanDefault = FALSE;
SOLDIERTYPE		*gpItemPointerSoldier;
INT8					gbItemPointerSrcSlot;
static UINT16 gusItemPointer = 255;
static UINT32 guiNewlyPlacedItemTimer = 0;
static BOOLEAN gfBadThrowItemCTGH;
BOOLEAN				gfDontChargeAPsToPickup = FALSE;
static BOOLEAN gbItemPointerLocateGood = FALSE;

// ITEM DESCRIPTION BOX STUFF
static UINT32 guiItemDescBox;
static UINT32 guiMapItemDescBox;
static UINT32 guiItemGraphic;
static UINT32 guiMoneyGraphicsForDescBox;
static UINT32 guiBullet;
BOOLEAN			gfInItemDescBox = FALSE;
static UINT32 guiCurrentItemDescriptionScreen=0;
OBJECTTYPE	*gpItemDescObject = NULL;
static BOOLEAN gfItemDescObjectIsAttachment = FALSE;
static const wchar_t* gzItemName;
static wchar_t gzItemDesc[SIZE_ITEM_INFO];
static wchar_t gzItemPros[SIZE_ITEM_PROS];
static wchar_t gzItemCons[SIZE_ITEM_CONS];
static wchar_t gzFullItemPros[SIZE_ITEM_PROS];
static wchar_t gzFullItemCons[SIZE_ITEM_PROS];
static INT16 gsInvDescX;
static INT16 gsInvDescY;
static UINT8 gubItemDescStatusIndex;
static INT32 giItemDescAmmoButtonImages;
static INT32 giItemDescAmmoButton;
static SOLDIERTYPE* gpItemDescSoldier;
static BOOLEAN fItemDescDelete = FALSE;
MOUSE_REGION		gItemDescAttachmentRegions[4];
static MOUSE_REGION gProsAndConsRegions[2];

static UINT32 guiMoneyButtonBtn[MAX_ATTACHMENTS];
static INT32 guiMoneyButtonImage;
static INT32 guiMoneyDoneButtonImage;

static UINT16 gusOriginalAttachItem[MAX_ATTACHMENTS];
static UINT8 gbOriginalAttachStatus[MAX_ATTACHMENTS];
static SOLDIERTYPE* gpAttachSoldier;
extern BOOLEAN	gfSMDisableForItems;

typedef struct
{
	UINT16 x;
	UINT16 y;
} MoneyLoc;

static const MoneyLoc gMoneyButtonLoc = { 343, 351 };
static const MoneyLoc gMoneyButtonOffsets[] = { { 0, 0 }, { 34, 0 }, { 0, 32 }, { 34, 32 }, { 8, 22 } };
static const MoneyLoc gMapMoneyButtonLoc = { 174, 115 };

// show the description
extern BOOLEAN fShowDescriptionFlag;
extern BOOLEAN fShowInventoryFlag;


// number of keys on keyring, temp for now
#define			NUMBER_KEYS_ON_KEYRING 28
#define			KEY_RING_ROW_WIDTH 7
#define			MAP_KEY_RING_ROW_WIDTH 4

// ITEM STACK POPUP STUFF
static BOOLEAN gfInItemStackPopup = FALSE;
static UINT32 guiItemPopupBoxes;
static OBJECTTYPE* gpItemPopupObject;
static INT16 gsItemPopupX;
static INT16 gsItemPopupY;
static MOUSE_REGION gItemPopupRegions[8];
static MOUSE_REGION gKeyRingRegions[NUMBER_KEYS_ON_KEYRING];
BOOLEAN							gfInKeyRingPopup = FALSE;
static UINT8 gubNumItemPopups = 0;
static MOUSE_REGION gItemPopupRegion;
static INT16 gsItemPopupInvX;
static INT16 gsItemPopupInvY;
static INT16 gsItemPopupInvWidth;
static INT16 gsItemPopupInvHeight;

static INT16 gsKeyRingPopupInvX;
static INT16 gsKeyRingPopupInvY;
static INT16 gsKeyRingPopupInvWidth;
static INT16 gsKeyRingPopupInvHeight;


SOLDIERTYPE *gpItemPopupSoldier;
extern BOOLEAN fMapScreenBottomDirty;

// inventory description done button for mapscreen
INT32 giMapInvDescButton = -1;


static BOOLEAN gfItemPopupRegionCallbackEndFix = FALSE;
extern void InternalMAPBeginItemPointer( SOLDIERTYPE *pSoldier );


extern BOOLEAN MAPInternalInitItemDescriptionBox( OBJECTTYPE *pObject, UINT8 ubStatusIndex, SOLDIERTYPE *pSoldier );
extern void	StartSKIDescriptionBox( void );

void UpdateItemHatches();


static const UINT8 ubRGBItemCyclePlacedItemColors[] =
{
	25,		25,		25,
	50,		50,		50,
	75,   75,   75,
	100,	100,	100,
	125,	125,	125,
	150,	150,	150,
	175,	175,	175,
	200,	200,	200,
	225,	225,	225,
	250,	250,	250,

	250,	250,	250,
	225,	225,	225,
	200,	200,	200,
	175,	175,	175,
	150,	150,	150,
	125,	125,	125,
	100,	100,	100,
	75,   75,   75,
	50,		50,		50,
	25,		25,		25

};


typedef struct
{
	INT16 sX;
	INT16 sY;
	INT16 sValDx;
} INV_DESC_STATS;

typedef struct
{
	INT16 sX;
	INT16 sY;
	INT16 sHeight;
	INT16 sWidth;
	INT16 sBarDx;
	INT16 sBarDy;
} INV_ATTACHXY;


static const INV_DESC_STATS gWeaponStats[] =
{
	{ 202, 25, 83 },
	{ 202, 15, 83 },
	{ 202, 15, 83 },
	{ 265, 40, 20 },
	{ 202, 40, 32 },
	{ 202, 50, 32 },
	{ 265, 50, 20 },
	{ 234, 50,  0 },
	{ 290, 50,  0 }
};


// displayed AFTER the mass/weight/"Kg" line
static const INV_DESC_STATS gMoneyStats[] =
{
	{ 202, 14, 78 },
	{ 212, 25, 78 },
	{ 202, 40, 78 },
	{ 212, 51, 78 }
};

// displayed AFTER the mass/weight/"Kg" line
static const INV_DESC_STATS gMapMoneyStats[] =
{
	{ 51,  97, 45 },
	{ 61, 107, 75 },
	{ 51, 125, 45 },
	{ 61, 135, 70 }
};


static const INV_DESC_STATS gMapWeaponStats[] =
{
	{  72 - 20,      20 + 80 + 8, 80 },
	{  72 - 20,      20 + 80 - 2, 80 },
	{  72 - 20,      20 + 80 - 2, 80 },
	{  72 - 20 + 65, 40 + 80 + 4, 21 },
	{  72 - 20,      40 + 80 + 4, 30 },
	{  72 - 20,      53 + 80 + 2, 30 },
	{  72 - 20 + 65, 53 + 80 + 2, 25 },
	{  86,           53 + 80 + 2,  0 },
	{ 145,           53 + 80 + 2,  0 }
};


static const INV_ATTACHXY gItemDescAttachmentsXY[] =
{
	{ 129, 12, SM_INV_SLOT_HEIGHT, SM_INV_SLOT_WIDTH, INV_BAR_DX - 1, INV_BAR_DY + 1 },
	{ 163, 12, SM_INV_SLOT_HEIGHT, SM_INV_SLOT_WIDTH, INV_BAR_DX - 1, INV_BAR_DY + 1 },
	{ 129, 39, SM_INV_SLOT_HEIGHT, SM_INV_SLOT_WIDTH, INV_BAR_DX - 1, INV_BAR_DY + 1 },
	{ 163, 39, SM_INV_SLOT_HEIGHT, SM_INV_SLOT_WIDTH, INV_BAR_DX - 1, INV_BAR_DY + 1 }
};

static const INV_ATTACHXY gMapItemDescAttachmentsXY[] =
{
	{ 173, 10, SM_INV_SLOT_HEIGHT, 26, INV_BAR_DX + 2, INV_BAR_DY },
	{ 211, 10, SM_INV_SLOT_HEIGHT, 26, INV_BAR_DX + 2, INV_BAR_DY },
	{ 173, 36, SM_INV_SLOT_HEIGHT, 26, INV_BAR_DX + 2, INV_BAR_DY },
	{ 211, 36, SM_INV_SLOT_HEIGHT, 26, INV_BAR_DX + 2, INV_BAR_DY }
};

static const SGPRect gItemDescProsConsRects[] =
{// NB the left value is calculated based on the width of the 'pros' and 'cons' labels
	{ 0, 111, 313, 118 },
	{ 0, 119, 313, 126 }
};

static const SGPRect gMapItemDescProsConsRects[] =
{
	{ 0, 231, 313, 238 },
	{ 0, 239, 313, 246 },
};


static BOOLEAN gfItemDescHelpTextOffset = FALSE;


// A STRUCT USED INTERNALLY FOR INV SLOT REGIONS
typedef struct
{
	const BOOLEAN fBigPocket;
	const INT16   sBarDx;
	const INT16   sBarDy;
	const INT16   sWidth;
	const INT16   sHeight;
	INT16         sX; // starts at 0, gets set via InitInvSlotInterface()
	INT16         sY; // starts at 0, gets set via InitInvSlotInterface()
} INV_REGIONS;

#define M(big, w, h) { big, INV_BAR_DX, INV_BAR_DY, w, h, 0, 0 }

// ARRAY FOR INV PANEL INTERFACE ITEM POSITIONS (sX,sY get set via InitInvSlotInterface() )
static INV_REGIONS gSMInvData[] =
{
	M(FALSE, HEAD_INV_SLOT_WIDTH, HEAD_INV_SLOT_HEIGHT), // HELMETPOS
	M(FALSE, VEST_INV_SLOT_WIDTH, VEST_INV_SLOT_HEIGHT), // VESTPOS
	M(FALSE, LEGS_INV_SLOT_WIDTH, LEGS_INV_SLOT_HEIGHT), // LEGPOS,
	M(FALSE, SM_INV_SLOT_WIDTH,   SM_INV_SLOT_HEIGHT  ), // HEAD1POS
	M(FALSE, SM_INV_SLOT_WIDTH,   SM_INV_SLOT_HEIGHT  ), // HEAD2POS
	M(TRUE,  BIG_INV_SLOT_WIDTH,  BIG_INV_SLOT_HEIGHT ), // HANDPOS,
	M(TRUE,  BIG_INV_SLOT_WIDTH,  BIG_INV_SLOT_HEIGHT ), // SECONDHANDPOS
	M(TRUE,  BIG_INV_SLOT_WIDTH,  BIG_INV_SLOT_HEIGHT ), // BIGPOCK1
	M(TRUE,  BIG_INV_SLOT_WIDTH,  BIG_INV_SLOT_HEIGHT ), // BIGPOCK2
	M(TRUE,  BIG_INV_SLOT_WIDTH,  BIG_INV_SLOT_HEIGHT ), // BIGPOCK3
	M(TRUE,  BIG_INV_SLOT_WIDTH,  BIG_INV_SLOT_HEIGHT ), // BIGPOCK4
	M(FALSE, SM_INV_SLOT_WIDTH,   SM_INV_SLOT_HEIGHT  ), // SMALLPOCK1
	M(FALSE, SM_INV_SLOT_WIDTH,   SM_INV_SLOT_HEIGHT  ), // SMALLPOCK2
	M(FALSE, SM_INV_SLOT_WIDTH,   SM_INV_SLOT_HEIGHT  ), // SMALLPOCK3
	M(FALSE, SM_INV_SLOT_WIDTH,   SM_INV_SLOT_HEIGHT  ), // SMALLPOCK4
	M(FALSE, SM_INV_SLOT_WIDTH,   SM_INV_SLOT_HEIGHT  ), // SMALLPOCK5
	M(FALSE, SM_INV_SLOT_WIDTH,   SM_INV_SLOT_HEIGHT  ), // SMALLPOCK6
	M(FALSE, SM_INV_SLOT_WIDTH,   SM_INV_SLOT_HEIGHT  ), // SMALLPOCK7
	M(FALSE, SM_INV_SLOT_WIDTH,   SM_INV_SLOT_HEIGHT  )  // SMALLPOCK8
};

#undef M


typedef struct
{
	UINT32	uiTotalAmount;
	UINT32	uiMoneyRemaining;
	UINT32	uiMoneyRemoving;

} REMOVE_MONEY;
static REMOVE_MONEY gRemoveMoney;

static MOUSE_REGION gSMInvRegion[NUM_INV_SLOTS];
static MOUSE_REGION gKeyRingPanel;
static MOUSE_REGION gSMInvCamoRegion;
static INT8 gbCompatibleAmmo[NUM_INV_SLOTS];
INT8						gbInvalidPlacementSlot[ NUM_INV_SLOTS ];
static UINT16 us16BPPItemCyclePlacedItemColors[20];
static UINT32 guiBodyInvVO[4][2];
static UINT32 guiGoldKeyVO;
INT8						gbCompatibleApplyItem = FALSE;


static BOOLEAN AttemptToAddSubstring(STR16 zDest, const wchar_t* zTemp, UINT32* puiStringLength, UINT32 uiPixLimit)
{
	UINT32 uiRequiredStringLength, uiTempStringLength;

	uiTempStringLength = StringPixLength( zTemp, ITEMDESC_FONT );
	uiRequiredStringLength = *puiStringLength + uiTempStringLength;
	if (zDest[0] != 0)
	{
		uiRequiredStringLength += StringPixLength( COMMA_AND_SPACE, ITEMDESC_FONT );
	}
	if (uiRequiredStringLength < uiPixLimit)
	{
		if (zDest[0] != 0)
		{
			wcscat( zDest, COMMA_AND_SPACE );
		}
		wcscat( zDest, zTemp );
		*puiStringLength = uiRequiredStringLength;
		return( TRUE );
	}
	else
	{
		wcscat( zDest, DOTDOTDOT );
		return( FALSE );
	}
}


static void GenerateProsString(wchar_t* zItemPros, OBJECTTYPE* pObject, UINT32 uiPixLimit)
{
	UINT32			uiStringLength = 0;
	const wchar_t *zTemp;
	UINT16			usItem = pObject->usItem;
	UINT8				ubWeight;

	zItemPros[0] = 0;

	ubWeight = Item[ usItem ].ubWeight;
	if (Item[ usItem ].usItemClass == IC_GUN)
	{
		ubWeight += Item[ pObject->usGunAmmoItem ].ubWeight;
	}

	if (Item[usItem].ubWeight <= EXCEPTIONAL_WEIGHT)
	{
		zTemp = Message[STR_LIGHT];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (Item[usItem].ubPerPocket >= 1) // fits in a small pocket
	{
		zTemp = Message[STR_SMALL];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( GunRange( pObject ) >= EXCEPTIONAL_RANGE )
	{
		zTemp = Message[STR_LONG_RANGE];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (Weapon[usItem].ubImpact >= EXCEPTIONAL_DAMAGE)
	{
		zTemp = Message[STR_HIGH_DAMAGE];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (BaseAPsToShootOrStab( DEFAULT_APS, DEFAULT_AIMSKILL, gpItemDescObject ) <= EXCEPTIONAL_AP_COST)
	{
		zTemp = Message[STR_QUICK_FIRING];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (Weapon[usItem].ubShotsPerBurst >= EXCEPTIONAL_BURST_SIZE || usItem == G11)
	{
		zTemp = Message[STR_FAST_BURST];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (Weapon[usItem].ubMagSize > EXCEPTIONAL_MAGAZINE)
	{
		zTemp = Message[STR_LARGE_AMMO_CAPACITY];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( Item[usItem].bReliability >= EXCEPTIONAL_RELIABILITY )
	{
		zTemp = Message[STR_RELIABLE];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( Item[usItem].bRepairEase >= EXCEPTIONAL_REPAIR_EASE )
	{
		zTemp = Message[STR_EASY_TO_REPAIR];
		if ( ! AttemptToAddSubstring( zItemPros, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( zItemPros[0] == 0 )
	{
		// empty string, so display "None"
		if ( ! AttemptToAddSubstring( zItemPros, Message[ STR_NONE ], &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}
}


static void GenerateConsString(wchar_t* zItemCons, OBJECTTYPE* pObject, UINT32 uiPixLimit)
{
	UINT32			uiStringLength = 0;
	const wchar_t *zTemp;
	UINT8				ubWeight;
	UINT16			usItem = pObject->usItem;

	zItemCons[0] = 0;

	// calculate the weight of the item plus ammunition but not including any attachments
	ubWeight = Item[ usItem ].ubWeight;
	if (Item[ usItem ].usItemClass == IC_GUN)
	{
		ubWeight += Item[ pObject->usGunAmmoItem ].ubWeight;
	}

	if (ubWeight >= BAD_WEIGHT)
	{
		zTemp = Message[STR_HEAVY];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( GunRange( pObject ) <= BAD_RANGE)
	{
		zTemp = Message[STR_SHORT_RANGE];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (Weapon[usItem].ubImpact <= BAD_DAMAGE)
	{
		zTemp = Message[STR_LOW_DAMAGE];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (BaseAPsToShootOrStab( DEFAULT_APS, DEFAULT_AIMSKILL, gpItemDescObject ) >= BAD_AP_COST)
	{
		zTemp = Message[STR_SLOW_FIRING];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (Weapon[usItem].ubShotsPerBurst == 0)
	{
		zTemp = Message[STR_NO_BURST];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if (Weapon[usItem].ubMagSize < BAD_MAGAZINE)
	{
		zTemp = Message[STR_SMALL_AMMO_CAPACITY];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( Item[usItem].bReliability <= BAD_RELIABILITY )
	{
		zTemp = Message[STR_UNRELIABLE];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}

	if ( Item[usItem].bRepairEase <= BAD_REPAIR_EASE )
	{
		zTemp = Message[STR_HARD_TO_REPAIR];
		if ( ! AttemptToAddSubstring( zItemCons, zTemp, &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}


	if ( zItemCons[0] == 0 )
	{
		// empty string, so display "None"
		if ( ! AttemptToAddSubstring( zItemCons, Message[ STR_NONE ], &uiStringLength, uiPixLimit ) )
		{
			return;
		}
	}
}


BOOLEAN InitInvSlotInterface(const INV_REGION_DESC* pRegionDesc, const INV_REGION_DESC* pCamoRegion, MOUSE_CALLBACK INVMoveCallback, MOUSE_CALLBACK INVClickCallback, MOUSE_CALLBACK INVMoveCammoCallback, MOUSE_CALLBACK INVClickCammoCallback, BOOLEAN fSetHighestPrioity)
{
	INT32 cnt;

	// Load all four body type images
	guiBodyInvVO[1][0] = AddVideoObjectFromFile("INTERFACE/inventory_figure_large_male.sti");
	CHECKF(guiBodyInvVO[1][0] != NO_VOBJECT);
	guiBodyInvVO[1][1] = AddVideoObjectFromFile("INTERFACE/inventory_figure_large_male_H.sti");
	CHECKF(guiBodyInvVO[1][1] != NO_VOBJECT);

	guiBodyInvVO[0][0] = AddVideoObjectFromFile("INTERFACE/inventory_normal_male.sti");
	CHECKF(guiBodyInvVO[0][0] != NO_VOBJECT);
	guiBodyInvVO[0][1] = AddVideoObjectFromFile("INTERFACE/inventory_normal_male_H.sti");
	CHECKF(guiBodyInvVO[0][1] != NO_VOBJECT);

	guiBodyInvVO[2][0] = AddVideoObjectFromFile("INTERFACE/inventory_normal_male.sti");
	CHECKF(guiBodyInvVO[2][0] != NO_VOBJECT);
	guiBodyInvVO[2][1] = AddVideoObjectFromFile("INTERFACE/inventory_normal_male.sti");
	CHECKF(guiBodyInvVO[2][1] != NO_VOBJECT);

	guiBodyInvVO[3][0] = AddVideoObjectFromFile("INTERFACE/inventory_figure_female.sti");
	CHECKF(guiBodyInvVO[3][0] != NO_VOBJECT);
	guiBodyInvVO[3][1] = AddVideoObjectFromFile("INTERFACE/inventory_figure_female_H.sti");
	CHECKF(guiBodyInvVO[3][1] != NO_VOBJECT);

	// add gold key graphic
	guiGoldKeyVO = AddVideoObjectFromFile("INTERFACE/gold_key_button.sti");
	CHECKF(guiGoldKeyVO != NO_VOBJECT);

	// Add cammo region
	MSYS_DefineRegion(&gSMInvCamoRegion, pCamoRegion->sX, pCamoRegion->sY, pCamoRegion->sX + CAMO_REGION_WIDTH, pCamoRegion->sY + CAMO_REGION_HEIGHT, MSYS_PRIORITY_HIGH, MSYS_NO_CURSOR, INVMoveCammoCallback, INVClickCammoCallback);

	// Add regions for inventory slots
	for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
	{
		// set inventory pocket coordinates from the table passed in
		gSMInvData[ cnt ].sX = pRegionDesc[ cnt ].sX;
		gSMInvData[ cnt ].sY = pRegionDesc[ cnt ].sY;

		MSYS_DefineRegion(&gSMInvRegion[cnt], gSMInvData[cnt].sX, gSMInvData[cnt].sY, gSMInvData[cnt].sX + gSMInvData[cnt].sWidth, gSMInvData[cnt].sY + gSMInvData[cnt].sHeight, fSetHighestPrioity ? MSYS_PRIORITY_HIGHEST : MSYS_PRIORITY_HIGH, MSYS_NO_CURSOR, INVMoveCallback, INVClickCallback);
		MSYS_SetRegionUserData( &gSMInvRegion[ cnt ], 0, cnt );
	}

	memset( gbCompatibleAmmo, 0, sizeof( gbCompatibleAmmo ) );

	return( TRUE );
}


void InitKeyRingInterface(MOUSE_CALLBACK KeyRingClickCallback)
{
	MSYS_DefineRegion(&gKeyRingPanel, KEYRING_X, KEYRING_Y, KEYRING_X + KEYRING_WIDTH, KEYRING_Y + KEYRING_HEIGHT, MSYS_PRIORITY_HIGH, MSYS_NO_CURSOR, MSYS_NO_CALLBACK, KeyRingClickCallback);
	SetRegionFastHelpText(&gKeyRingPanel, TacticalStr[KEYRING_HELP_TEXT]);
}


void InitMapKeyRingInterface( MOUSE_CALLBACK KeyRingClickCallback )
{
	MSYS_DefineRegion(&gKeyRingPanel, MAP_KEYRING_X, MAP_KEYRING_Y, MAP_KEYRING_X + KEYRING_WIDTH, MAP_KEYRING_Y + KEYRING_HEIGHT, MSYS_PRIORITY_HIGH, MSYS_NO_CURSOR, MSYS_NO_CALLBACK, KeyRingClickCallback);
	SetRegionFastHelpText(&gKeyRingPanel, TacticalStr[KEYRING_HELP_TEXT]);
}


static void EnableKeyRing(BOOLEAN fEnable)
{
	if ( fEnable )
	{
		MSYS_EnableRegion( &gKeyRingPanel );
	}
	else
	{
		MSYS_DisableRegion( &gKeyRingPanel );
	}
}


void ShutdownKeyRingInterface( void )
{
	MSYS_RemoveRegion( &gKeyRingPanel );
}

void DisableInvRegions( BOOLEAN fDisable )
{
	INT32 cnt;

	for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
	{
		if ( fDisable )
		{
			MSYS_DisableRegion( &gSMInvRegion[ cnt ] );
		}
		else
		{
			MSYS_EnableRegion( &gSMInvRegion[ cnt ] );
		}
	}

	if ( fDisable )
	{
		MSYS_DisableRegion( &gSMInvCamoRegion );

		MSYS_DisableRegion( &gSM_SELMERCMoneyRegion );
		EnableKeyRing( FALSE );
	}
	else
	{
		MSYS_EnableRegion( &gSMInvCamoRegion );

		MSYS_EnableRegion( &gSM_SELMERCMoneyRegion );
		EnableKeyRing( TRUE );
	}

}

void ShutdownInvSlotInterface( )
{
	UINT32		cnt;

	// Remove all body type panels
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 0 ][ 0 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 2 ][ 0 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 1 ][ 0 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 3 ][ 0 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 0 ][ 1 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 2 ][ 1 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 1 ][ 1 ] );
	DeleteVideoObjectFromIndex( guiBodyInvVO[ 3 ][ 1 ] );

	DeleteVideoObjectFromIndex( guiGoldKeyVO );

	// Remove regions
	// Add regions for inventory slots
	for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
	{
		// Remove region
		MSYS_RemoveRegion( &gSMInvRegion[ cnt ] );
	}

	// Remove cammo
	MSYS_RemoveRegion( &gSMInvCamoRegion );

}


void RenderInvBodyPanel(const SOLDIERTYPE* pSoldier, INT16 sX, INT16 sY)
{
	// Blit body inv, based on body type
	INT8 bSubImageIndex = gbCompatibleApplyItem;

	BltVideoObjectFromIndex( guiSAVEBUFFER, guiBodyInvVO[ pSoldier->ubBodyType ][ bSubImageIndex ], 0, sX, sY);
}


static void INVRenderINVPanelItem(const SOLDIERTYPE* pSoldier, INT16 sPocket, UINT8 fDirtyLevel);


void HandleRenderInvSlots(const SOLDIERTYPE* pSoldier, UINT8 fDirtyLevel)
{
	INT32									cnt;
	static wchar_t					pStr[ 150 ];

	if ( InItemDescriptionBox( ) || InItemStackPopup( ) || InKeyRingPopup( ) )
	{

	}
	else
	{
		for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
		{
			if ( fDirtyLevel == DIRTYLEVEL2 )
			{
				GetHelpTextForItem( pStr, lengthof(pStr), &( pSoldier->inv[ cnt ] ), pSoldier );

				SetRegionFastHelpText( &(gSMInvRegion[ cnt ]), pStr );
			}

			INVRenderINVPanelItem( pSoldier, (INT16)cnt, fDirtyLevel );
		}

		if ( KeyExistsInKeyRing( pSoldier, ANYKEY, NULL ) )
		{
			// blit gold key here?
			INT32 x;
			INT32 y;
			if (guiCurrentItemDescriptionScreen == MAP_SCREEN)
			{
				x = MAP_KEYRING_X;
				y = MAP_KEYRING_Y;
			}
			else
			{
				x = KEYRING_X;
				y = KEYRING_Y;
			}
			BltVideoObjectFromIndex(guiSAVEBUFFER, guiGoldKeyVO, 0, x, y);
			RestoreExternBackgroundRect(x, y, KEYRING_WIDTH, KEYRING_HEIGHT);
		}
	}
}


static void INVRenderINVPanelItem(const SOLDIERTYPE* pSoldier, INT16 sPocket, UINT8 fDirtyLevel)
{
	INT16 sX, sY;
	INT16	sBarX, sBarY;
	BOOLEAN	fOutline = FALSE;
	INT16		sOutlineColor = 0;
	UINT8		fRenderDirtyLevel;
	BOOLEAN fHatchItOut = FALSE;


	//Assign the screen
	guiCurrentItemDescriptionScreen = guiCurrentScreen;

	const OBJECTTYPE* pObject = &pSoldier->inv[sPocket];

	sX = gSMInvData[ sPocket ].sX;
	sY = gSMInvData[ sPocket ].sY;

	if ( fDirtyLevel == DIRTYLEVEL2 )
	{
		// CHECK FOR COMPATIBILITY WITH MAGAZINES

/*	OLD VERSION OF GUN/AMMO MATCH HIGHLIGHTING
		UINT32	uiDestPitchBYTES;
		UINT8		*pDestBuf;
		UINT16	usLineColor;

		if ( ( Item [ pSoldier->inv[ HANDPOS ].usItem ].usItemClass & IC_GUN )  && ( Item[ pObject->usItem ].usItemClass & IC_AMMO ) )
		{
			// CHECK
			if (Weapon[pSoldier->inv[ HANDPOS ].usItem].ubCalibre == Magazine[Item[pObject->usItem].ubClassIndex].ubCalibre )
			{
				// IT's an OK calibre ammo, do something!
				// Render Item with specific color
				//fOutline = TRUE;
				//sOutlineColor = Get16BPPColor( FROMRGB( 96, 104, 128 ) );
				//sOutlineColor = Get16BPPColor( FROMRGB( 20, 20, 120 ) );

				// Draw rectangle!
				pDestBuf = LockVideoSurface( guiSAVEBUFFER, &uiDestPitchBYTES );
				SetClippingRegionAndImageWidth(uiDestPitchBYTES, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

				//usLineColor = Get16BPPColor( FROMRGB( 255, 255, 0 ) );
				usLineColor = Get16BPPColor( FROMRGB( 230, 215, 196 ) );
				RectangleDraw( TRUE, (sX+1), (sY+1), (sX + gSMInvData[ sPocket ].sWidth - 2 ),( sY + gSMInvData[ sPocket ].sHeight - 2 ), usLineColor, pDestBuf );

				SetClippingRegionAndImageWidth(uiDestPitchBYTES, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

				UnLockVideoSurface( guiSAVEBUFFER );
			}
		}
*/

		if ( gbCompatibleAmmo[ sPocket ] )
		{
			fOutline = TRUE;
			sOutlineColor = Get16BPPColor( FROMRGB( 255, 255, 255 ) );
		}

		// IF it's the second hand and this hand cannot contain anything, remove the second hand position graphic
		if (sPocket == SECONDHANDPOS && Item[pSoldier->inv[HANDPOS].usItem].fFlags & ITEM_TWO_HANDED)
		{
//			if( guiCurrentScreen != MAP_SCREEN )
			if( guiCurrentItemDescriptionScreen != MAP_SCREEN )
			{
				BltVideoObjectFromIndex( guiSAVEBUFFER, guiSecItemHiddenVO, 0, 217, 448);
				RestoreExternBackgroundRect( 217, 448, 72, 28 );
			}
			else
			{
				BltVideoObjectFromIndex( guiSAVEBUFFER, guiMapInvSecondHandBlockout, 0, 14, 218);
				RestoreExternBackgroundRect( 14, 218, 102, 24 );
			}
		}
	}

	// If we have a new item and we are in the right panel...
	if ( pSoldier->bNewItemCount[ sPocket ] > 0 && gsCurInterfacePanel == SM_PANEL && fInterfacePanelDirty != DIRTYLEVEL2 )
	{
		fRenderDirtyLevel = DIRTYLEVEL0;
		//fRenderDirtyLevel = fDirtyLevel;
	}
	else
	{
		fRenderDirtyLevel = fDirtyLevel;
	}

	//Now render as normal
	//INVRenderItem( guiSAVEBUFFER, pObject, (INT16)(sX + gSMInvData[ sPocket ].sSubX), (INT16)(sY + gSMInvData[ sPocket ].sSubY), gSMInvData[ sPocket ].sWidth, gSMInvData[ sPocket ].sHeight, fDirtyLevel, &(gfSM_HandInvDispText[ sPocket ] ) );
	INVRenderItem( guiSAVEBUFFER, pSoldier, pObject, sX, sY, gSMInvData[ sPocket ].sWidth, gSMInvData[ sPocket ].sHeight, fRenderDirtyLevel, NULL, 0, fOutline, sOutlineColor );

	if ( gbInvalidPlacementSlot[ sPocket ] )
	{
		if ( sPocket != SECONDHANDPOS )
		{
			// If we are in inv panel and our guy is not = cursor guy...
			if ( !gfSMDisableForItems )
			{
				fHatchItOut = TRUE;
			}
		}
	}

	//if we are in the shop keeper interface
	if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
	{
		if( ShouldSoldierDisplayHatchOnItem( pSoldier->ubProfile, sPocket ) && !gbInvalidPlacementSlot[ sPocket ] )
		{
			fHatchItOut = TRUE;
		}
	}

	if ( fHatchItOut )
	{
		UINT32 uiWhichBuffer = (guiCurrentItemDescriptionScreen == MAP_SCREEN ? guiSAVEBUFFER : FRAME_BUFFER);
		DrawHatchOnInventory( uiWhichBuffer, sX, sY, (UINT16)(gSMInvData[ sPocket ].sWidth-1), (UINT16)(gSMInvData[ sPocket ].sHeight-1) );
	}

	// if there's an item in there
	if ( pObject->usItem != NOTHING )
	{
		// Add item status bar
		sBarX = sX - gSMInvData[ sPocket ].sBarDx;
		sBarY = sY + gSMInvData[ sPocket ].sBarDy;
		DrawItemUIBarEx( pObject, 0, sBarX, sBarY, ITEM_BAR_WIDTH, ITEM_BAR_HEIGHT,	Get16BPPColor( STATUS_BAR ), Get16BPPColor( STATUS_BAR_SHADOW ), TRUE , guiSAVEBUFFER);
	}

}


static BOOLEAN CompatibleAmmoForGun(const OBJECTTYPE* pTryObject, const OBJECTTYPE* pTestObject)
{
	if ( ( Item[ pTryObject->usItem ].usItemClass & IC_AMMO ) )
	{
		// CHECK
		if (Weapon[ pTestObject->usItem ].ubCalibre == Magazine[Item[pTryObject->usItem].ubClassIndex].ubCalibre )
		{
			return( TRUE );
		}
	}
	return( FALSE );
}


static BOOLEAN CompatibleGunForAmmo(const OBJECTTYPE* pTryObject, const OBJECTTYPE* pTestObject)
{
	if ( ( Item[ pTryObject->usItem ].usItemClass & IC_GUN ) )
	{
		// CHECK
		if (Weapon[ pTryObject->usItem ].ubCalibre == Magazine[Item[pTestObject->usItem].ubClassIndex].ubCalibre )
		{
			return( TRUE );
		}
	}
	return( FALSE );
}


static BOOLEAN CompatibleItemForApplyingOnMerc(const OBJECTTYPE* pTestObject)
{
	UINT16 usItem = pTestObject->usItem;

  // ATE: If in mapscreen, return false always....
	if( guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN )
  {
     return( FALSE );
  }

	// ATE: Would be nice to have flag here to check for these types....
	if ( usItem == CAMOUFLAGEKIT || usItem == ADRENALINE_BOOSTER || usItem == REGEN_BOOSTER ||
			 usItem == SYRINGE_3		 || usItem == SYRINGE_4 || usItem == SYRINGE_5 ||
			 usItem == ALCOHOL			 || usItem == WINE			|| usItem == BEER			 || usItem == CANTEEN || usItem == JAR_ELIXIR )
	{
		return( TRUE );
	}
	else
	{
		return( FALSE );
	}
}


static BOOLEAN SoldierContainsAnyCompatibleStuff(SOLDIERTYPE* pSoldier, OBJECTTYPE* pTestObject)
{
	INT32				cnt;
	OBJECTTYPE  *pObject;

	if( ( Item [ pTestObject->usItem ].usItemClass & IC_GUN ) )
	{
		for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
		{
			pObject = &(pSoldier->inv[ cnt ]);

			if ( CompatibleAmmoForGun( pObject, pTestObject ) )
			{
				return( TRUE );
			}
		}
	}

	if( ( Item [ pTestObject->usItem ].usItemClass & IC_AMMO ) )
	{
		for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
		{
			pObject = &(pSoldier->inv[ cnt ]);

			if ( CompatibleGunForAmmo( pObject, pTestObject ) )
			{
				return( TRUE );
			}
		}
	}

	// ATE: Put attachment checking here.....

	return( FALSE );
}


void HandleAnyMercInSquadHasCompatibleStuff( UINT8 ubSquad, OBJECTTYPE *pObject, BOOLEAN fReset )
{
	INT32 iCounter = 0;

	if ( ubSquad == NUMBER_OF_SQUADS )
	{
		return;
	}

	for( iCounter = 0; iCounter < NUMBER_OF_SOLDIERS_PER_SQUAD; iCounter++ )
	{
		if(  Squad[ iCurrentTacticalSquad ][ iCounter ] != NULL )
		{
			if ( !fReset )
			{
				if ( SoldierContainsAnyCompatibleStuff( Squad[ iCurrentTacticalSquad ][ iCounter ], pObject )	)
				{
					// Get face and set value....
					gFacesData[ Squad[ iCurrentTacticalSquad ][ iCounter ]->iFaceIndex ].fCompatibleItems = TRUE;
				}
			}
			else
			{
				gFacesData[ Squad[ iCurrentTacticalSquad ][ iCounter ]->iFaceIndex ].fCompatibleItems = FALSE;
			}
		}
	}

}


BOOLEAN HandleCompatibleAmmoUIForMapScreen(const SOLDIERTYPE* pSoldier, INT32 bInvPos, BOOLEAN fOn, BOOLEAN fFromMerc)
{
	BOOLEAN			fFound = FALSE;
	INT32				cnt;

	const OBJECTTYPE* pTestObject;
	if( fFromMerc == FALSE )
	{
		pTestObject = &( pInventoryPoolList[ bInvPos ].o );
	}
	else
	{
		if ( bInvPos == NO_SLOT )
		{
			pTestObject = NULL;
		}
		else
		{
			pTestObject = &(pSoldier->inv[ bInvPos ]);
		}
	}

	// ATE: If pTest object is NULL, test only for existence of syringes, etc...
	if ( pTestObject == NULL )
	{
		for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
		{
			const OBJECTTYPE* pObject = &pSoldier->inv[cnt];
			if ( CompatibleItemForApplyingOnMerc( pObject ) )
			{
				if ( fOn != gbCompatibleAmmo[ cnt ] )
				{
					fFound = TRUE;
				}

				// IT's an OK calibere ammo, do something!
				// Render Item with specific color
				gbCompatibleAmmo[ cnt ] = fOn;

			}
		}


		if ( gpItemPointer != NULL )
		{
			if ( CompatibleItemForApplyingOnMerc( gpItemPointer ) )
			{
				// OK, Light up portrait as well.....
				if ( fOn )
				{
					gbCompatibleApplyItem = TRUE;
				}
				else
				{
					gbCompatibleApplyItem = FALSE;
				}

				fFound = TRUE;
			}
		}

		if ( fFound )
		{
			fInterfacePanelDirty = DIRTYLEVEL2;
			//HandleRenderInvSlots( pSoldier, DIRTYLEVEL2 );
		}

		return( fFound );
	}

	if ( (! Item[ pTestObject->usItem ].fFlags & ITEM_HIDDEN_ADDON) )
	{
		// First test attachments, which almost any type of item can have....
		for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
		{
			const OBJECTTYPE* pObject = &pSoldier->inv[cnt];

			if ( Item[ pObject->usItem ].fFlags & ITEM_HIDDEN_ADDON )
			{
				// don't consider for UI purposes
				continue;
			}

			if ( ValidAttachment( pObject->usItem, pTestObject->usItem ) ||
					 ValidAttachment( pTestObject->usItem, pObject->usItem ) ||
					 ValidLaunchable( pTestObject->usItem, pObject->usItem ) ||
					 ValidLaunchable( pObject->usItem, pTestObject->usItem ) )
			{
				if ( fOn != gbCompatibleAmmo[ cnt ] )
				{
					fFound = TRUE;
				}

				// IT's an OK calibere ammo, do something!
				// Render Item with specific color
				gbCompatibleAmmo[ cnt ] = fOn;
			}
		}
	}


	if ( ( Item [ pTestObject->usItem ].usItemClass & IC_GUN ) )
	{
		for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
		{
			const OBJECTTYPE* pObject = &pSoldier->inv[cnt];
			if ( CompatibleAmmoForGun( pObject, pTestObject ) )
			{
				if ( fOn != gbCompatibleAmmo[ cnt ] )
				{
					fFound = TRUE;
				}

				// IT's an OK calibere ammo, do something!
				// Render Item with specific color
				gbCompatibleAmmo[ cnt ] = fOn;
			}
		}
	}
	else if( ( Item [ pTestObject->usItem ].usItemClass & IC_AMMO ) )
	{
		for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
		{
			const OBJECTTYPE* pObject = &pSoldier->inv[cnt];
			if ( CompatibleGunForAmmo( pObject, pTestObject ) )
			{
				if ( fOn != gbCompatibleAmmo[ cnt ] )
				{
					fFound = TRUE;
				}

				// IT's an OK calibere ammo, do something!
				// Render Item with specific color
				gbCompatibleAmmo[ cnt ] = fOn;

			}
		}
	}


	return( fFound );
}

BOOLEAN HandleCompatibleAmmoUIForMapInventory( SOLDIERTYPE *pSoldier, INT32 bInvPos, INT32 iStartSlotNumber, BOOLEAN fOn, BOOLEAN fFromMerc   )
{
	// CJC: ATE, needs fixing here!

	BOOLEAN			fFound = FALSE;
	INT32				cnt;
	OBJECTTYPE  *pObject, *pTestObject ;

	if( fFromMerc == FALSE )
	{
		pTestObject = &( pInventoryPoolList[ iStartSlotNumber + bInvPos ].o);
	}
	else
	{
		if ( bInvPos == NO_SLOT )
		{
			pTestObject = NULL;
		}
		else
		{
			pTestObject = &(pSoldier->inv[ bInvPos ]);
		}
	}

	// First test attachments, which almost any type of item can have....
	for ( cnt = 0; cnt < MAP_INVENTORY_POOL_SLOT_COUNT; cnt++ )
	{
		pObject = &( pInventoryPoolList[ iStartSlotNumber + cnt ].o );

		if ( Item[ pObject->usItem ].fFlags & ITEM_HIDDEN_ADDON )
		{
			// don't consider for UI purposes
			continue;
		}

		if ( ValidAttachment( pObject->usItem, pTestObject->usItem ) ||
				 ValidAttachment( pTestObject->usItem, pObject->usItem ) ||
				 ValidLaunchable( pTestObject->usItem, pObject->usItem ) ||
				 ValidLaunchable( pObject->usItem, pTestObject->usItem ) )
		{
			if ( fOn != fMapInventoryItemCompatable[ cnt ] )
			{
				fFound = TRUE;
			}

			// IT's an OK calibere ammo, do something!
			// Render Item with specific color
			fMapInventoryItemCompatable[ cnt ] = fOn;
		}
	}


	if( ( Item [ pTestObject->usItem ].usItemClass & IC_GUN ) )
	{
		for ( cnt = 0; cnt < MAP_INVENTORY_POOL_SLOT_COUNT; cnt++ )
		{
			pObject = &( pInventoryPoolList[ iStartSlotNumber + cnt ].o );

			if ( CompatibleAmmoForGun( pObject, pTestObject ) )
			{
				if ( fOn != fMapInventoryItemCompatable[ cnt ] )
				{
					fFound = TRUE;
				}

				// IT's an OK calibere ammo, do something!
				// Render Item with specific color
				fMapInventoryItemCompatable[ cnt ] = fOn;
			}
		}
	}
	else if( ( Item [ pTestObject->usItem ].usItemClass & IC_AMMO ) )
	{
		for ( cnt = 0; cnt < MAP_INVENTORY_POOL_SLOT_COUNT; cnt++ )
		{
			pObject = &( pInventoryPoolList[ iStartSlotNumber + cnt ].o );

			if ( CompatibleGunForAmmo( pObject, pTestObject ) )
			{
				if ( fOn != fMapInventoryItemCompatable[ cnt ] )
				{
					fFound = TRUE;
				}

				// IT's an OK calibere ammo, do something!
				// Render Item with specific color
				fMapInventoryItemCompatable[ cnt ] = fOn;

			}
		}
	}


	return( fFound );
}


BOOLEAN InternalHandleCompatibleAmmoUI(const SOLDIERTYPE* pSoldier, const OBJECTTYPE* pTestObject, BOOLEAN fOn)
{
	BOOLEAN			fFound = FALSE;
	INT32				cnt;
	BOOLEAN			fFoundAttachment = FALSE;

	// ATE: If pTest object is NULL, test only for existence of syringes, etc...
	if ( pTestObject == NULL )
	{
		for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
		{
			const OBJECTTYPE* pObject = &pSoldier->inv[cnt];
			if ( CompatibleItemForApplyingOnMerc( pObject ) )
			{
				if ( fOn != gbCompatibleAmmo[ cnt ] )
				{
					fFound = TRUE;
				}

				// IT's an OK calibere ammo, do something!
				// Render Item with specific color
				gbCompatibleAmmo[ cnt ] = fOn;

			}
		}


		if ( gpItemPointer != NULL )
		{
			if ( CompatibleItemForApplyingOnMerc( gpItemPointer ) )
			{
				// OK, Light up portrait as well.....
				if ( fOn )
				{
					gbCompatibleApplyItem = TRUE;
				}
				else
				{
					gbCompatibleApplyItem = FALSE;
				}

				fFound = TRUE;
			}
		}

		if ( fFound )
		{
			fInterfacePanelDirty = DIRTYLEVEL2;
			//HandleRenderInvSlots( pSoldier, DIRTYLEVEL2 );
		}

		return( fFound );
	}

	// First test attachments, which almost any type of item can have....
	for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
	{
		const OBJECTTYPE* pObject = &pSoldier->inv[cnt];

		if ( Item[ pObject->usItem ].fFlags & ITEM_HIDDEN_ADDON )
		{
			// don't consider for UI purposes
			continue;
		}

		if ( ValidAttachment( pObject->usItem, pTestObject->usItem ) ||
				 ValidAttachment( pTestObject->usItem, pObject->usItem ) ||
				 ValidLaunchable( pTestObject->usItem, pObject->usItem ) ||
				 ValidLaunchable( pObject->usItem, pTestObject->usItem ) )
		{
			fFoundAttachment = TRUE;

			if ( fOn != gbCompatibleAmmo[ cnt ] )
			{
				fFound = TRUE;
			}

			// IT's an OK calibere ammo, do something!
			// Render Item with specific color
			gbCompatibleAmmo[ cnt ] = fOn;
		}
	}

	//if ( !fFoundAttachment )
	//{
		if( ( Item [ pTestObject->usItem ].usItemClass & IC_GUN ) )
		{
			for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
			{
				const OBJECTTYPE* pObject = &pSoldier->inv[cnt];
				if ( CompatibleAmmoForGun( pObject, pTestObject ) )
				{
					if ( fOn != gbCompatibleAmmo[ cnt ] )
					{
						fFound = TRUE;
					}

					// IT's an OK calibere ammo, do something!
					// Render Item with specific color
					gbCompatibleAmmo[ cnt ] = fOn;
				}
			}
		}

		else if( ( Item [ pTestObject->usItem ].usItemClass & IC_AMMO ) )
		{
			for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
			{
				const OBJECTTYPE* pObject = &pSoldier->inv[cnt];
				if ( CompatibleGunForAmmo( pObject, pTestObject ) )
				{
					if ( fOn != gbCompatibleAmmo[ cnt ] )
					{
						fFound = TRUE;
					}

					// IT's an OK calibere ammo, do something!
					// Render Item with specific color
					gbCompatibleAmmo[ cnt ] = fOn;

				}
			}
		}
		else if ( CompatibleItemForApplyingOnMerc( pTestObject ) )
		{
			//If we are currently NOT in the Shopkeeper interface
			if( !( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE ) )
			{
				fFound = TRUE;
				gbCompatibleApplyItem = fOn;
			}
		}
	//}


	if ( !fFound )
	{
		for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
		{
			if ( gbCompatibleAmmo[ cnt ] )
			{
				fFound = TRUE;
				gbCompatibleAmmo[ cnt ] = FALSE;
			}

			if ( gbCompatibleApplyItem )
			{
				fFound = TRUE;
				gbCompatibleApplyItem = FALSE;
			}
		}
	}

	if ( fFound )
	{
		fInterfacePanelDirty = DIRTYLEVEL2;
		//HandleRenderInvSlots( pSoldier, DIRTYLEVEL2 );
	}

	return( fFound );

}

void ResetCompatibleItemArray( )
{
	INT32 cnt = 0;

	for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
	{
		if ( gbCompatibleAmmo[ cnt ] )
		{
			gbCompatibleAmmo[ cnt ] = FALSE;
		}
	}
}


BOOLEAN HandleCompatibleAmmoUI(const SOLDIERTYPE* pSoldier, INT8 bInvPos, BOOLEAN fOn)
{
	INT32 cnt;

	//if we are in the shopkeeper interface
	const OBJECTTYPE* pTestObject;
	if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
	{
		// if the inventory position is -1, this is a flag from the Shopkeeper interface screen
		//indicating that we are to use a different object to do the search
		if( bInvPos == -1 )
		{
			if( fOn )
			{
				if( gpHighLightedItemObject )
				{
					pTestObject = gpHighLightedItemObject;
//					gubSkiDirtyLevel = SKI_DIRTY_LEVEL2;
				}
				else
					return( FALSE );
			}
			else
			{
				gpHighLightedItemObject = NULL;

				for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
				{
					if ( gbCompatibleAmmo[ cnt ] )
					{
						gbCompatibleAmmo[ cnt ] = FALSE;
					}
				}

				gubSkiDirtyLevel = SKI_DIRTY_LEVEL1;
				return( TRUE );
			}
		}
		else
		{
			if( fOn )
			{
				pTestObject = &(pSoldier->inv[ bInvPos ]);
				gpHighLightedItemObject = pTestObject;
			}
			else
			{
				pTestObject = &(pSoldier->inv[ bInvPos ]);
				gpHighLightedItemObject = NULL;
				gubSkiDirtyLevel = SKI_DIRTY_LEVEL1;
			}
		}
	}
	else
	{
//		if( fOn )

		if ( bInvPos == NO_SLOT )
		{
			pTestObject = NULL;
		}
		else
		{
			pTestObject = &(pSoldier->inv[ bInvPos ]);
		}

	}

	return( InternalHandleCompatibleAmmoUI( pSoldier, pTestObject, fOn ) );

}


void HandleNewlyAddedItems( SOLDIERTYPE *pSoldier, BOOLEAN *fDirtyLevel )
{
	UINT32 cnt;
	INT16  sX, sY;
	OBJECTTYPE		*pObject;


	// If item description up.... stop
	if ( gfInItemDescBox )
	{
		return;
	}

	for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
	{
		if ( pSoldier->bNewItemCount[ cnt ] == -2 )
		{
			// Stop
			*fDirtyLevel = DIRTYLEVEL2;
			pSoldier->bNewItemCount[ cnt ] = 0;
		}

		if ( pSoldier->bNewItemCount[ cnt ] > 0 )
		{

			sX = gSMInvData[ cnt ].sX;
			sY = gSMInvData[ cnt ].sY;

			pObject = &(pSoldier->inv[ cnt ]);

			if ( pObject->usItem == NOTHING )
			{
				continue;
			}

			INVRenderItem( guiSAVEBUFFER, pSoldier, pObject, sX, sY, gSMInvData[ cnt ].sWidth, gSMInvData[ cnt ].sHeight, DIRTYLEVEL2, NULL, 0, TRUE, us16BPPItemCyclePlacedItemColors[ pSoldier->bNewItemCycleCount[ cnt ] ] );

		}

	}
}

void CheckForAnyNewlyAddedItems( SOLDIERTYPE *pSoldier )
{
	UINT32 cnt;

	// OK, l0ok for any new...
	for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
	{
		if ( pSoldier->bNewItemCount[ cnt ] == -1 )
		{
			pSoldier->bNewItemCount[ cnt ]	= NEW_ITEM_CYCLES - 1;
		}
	}

}

void DegradeNewlyAddedItems( )
{
	UINT32 uiTime;
	UINT32 cnt, cnt2;
	SOLDIERTYPE		*pSoldier;

	// If time done
	uiTime = GetJA2Clock();

	if ( ( uiTime - guiNewlyPlacedItemTimer ) > 100 )
	{
		guiNewlyPlacedItemTimer = uiTime;

		for ( cnt2 = 0; cnt2 < NUM_TEAM_SLOTS; cnt2++ )
		{
			// GET SOLDIER
			if ( gTeamPanel[ cnt2 ].fOccupied )
			{
				pSoldier = MercPtrs[ gTeamPanel[ cnt2 ].ubID ];

				for ( cnt = 0; cnt < NUM_INV_SLOTS; cnt++ )
				{
					if ( pSoldier->bNewItemCount[ cnt ] > 0 )
					{
						// Decrement all the time!
						pSoldier->bNewItemCycleCount[ cnt ]--;

						if ( pSoldier->bNewItemCycleCount[ cnt ] == 0 )
						{
							// OK, cycle down....
							pSoldier->bNewItemCount[ cnt ]--;

							if ( pSoldier->bNewItemCount[ cnt ] == 0 )
							{
								// Stop...
								pSoldier->bNewItemCount[ cnt ] = -2;
							}
							else
							{
								// Reset!
								pSoldier->bNewItemCycleCount[ cnt ]	= NEW_ITEM_CYCLE_COUNT;
								continue;
							}
						}
					}
				}
			}
		}
	}
}


void InitItemInterface( )
{
	UINT32 cnt, cnt2;

	for ( cnt = 0, cnt2 = 0; cnt2 < 20; cnt+=3, cnt2++ )
	{
		us16BPPItemCyclePlacedItemColors[ cnt2 ] = Get16BPPColor( FROMRGB( ubRGBItemCyclePlacedItemColors[ cnt ], ubRGBItemCyclePlacedItemColors[ cnt + 1 ], ubRGBItemCyclePlacedItemColors[ cnt + 2] ) );
	}

}


void INVRenderItem(UINT32 uiBuffer, const SOLDIERTYPE* pSoldier, const OBJECTTYPE* pObject, INT16 sX, INT16 sY, INT16 sWidth, INT16 sHeight, UINT8 fDirtyLevel, UINT8* pubHighlightCounter, UINT8 ubStatusIndex, BOOLEAN fOutline, INT16 sOutlineColor)
{
	UINT16								uiStringLength;
	INVTYPE								*pItem;
	INT16									sNewY, sNewX;
	BOOLEAN								fLineSplit = FALSE;
	INT16									sFontX2, sFontY2;
	INT16									sFontX, sFontY;

	static wchar_t				pStr[ 100 ], pStr2[ 100 ];

	if ( pObject->usItem == NOTHING )
	{
		return;
	}

	if ( ubStatusIndex < RENDER_ITEM_ATTACHMENT1 )
	{
		pItem = &Item[ pObject->usItem ];
	}
	else
	{
		pItem = &Item[ pObject->usAttachItem[ ubStatusIndex - RENDER_ITEM_ATTACHMENT1 ] ];
	}

	if ( fDirtyLevel == DIRTYLEVEL2 )
	{
		// TAKE A LOOK AT THE VIDEO OBJECT SIZE ( ONE OF TWO SIZES ) AND CENTER!
		UINT32 ItemVOIdx = GetInterfaceGraphicForItem(pItem);
		const ETRLEObject* pTrav = GetVideoObjectETRLESubregionProperties(ItemVOIdx, pItem->ubGraphicNum);
		UINT32 usHeight = pTrav->usHeight;
		UINT32 usWidth  = pTrav->usWidth;

		// CENTER IN SLOT!
		// CANCEL OFFSETS!
		INT16 sCenX = sX + abs(sWidth  - usWidth)  / 2 - pTrav->sOffsetX;
		INT16 sCenY = sY + abs(sHeight - usHeight) / 2 - pTrav->sOffsetY;

		// Shadow area
		BltVideoObjectOutlineShadowFromIndex(uiBuffer, ItemVOIdx, pItem->ubGraphicNum, sCenX - 2, sCenY + 2);
		BltVideoObjectOutlineFromIndex(      uiBuffer, ItemVOIdx, pItem->ubGraphicNum, sCenX,     sCenY, sOutlineColor, fOutline);


		if ( uiBuffer == FRAME_BUFFER )
		{
			InvalidateRegion( sX, sY, (INT16)(sX + sWidth), (INT16)(sY + sHeight ) );
		}
		else
		{
			RestoreExternBackgroundRect( sX, sY, sWidth, sHeight );
		}

	}

	SetFont( ITEM_FONT );

	if ( fDirtyLevel != DIRTYLEVEL0 )
	{

		if ( ubStatusIndex < RENDER_ITEM_ATTACHMENT1 )
		{

			SetFontBackground( FONT_MCOLOR_BLACK );
			SetFontForeground( FONT_MCOLOR_DKGRAY );

			// FIRST DISPLAY FREE ROUNDS REMIANING
			if ( pItem->usItemClass == IC_GUN && pObject->usItem != ROCKET_LAUNCHER )
			{
				sNewY = sY + sHeight - 10;
				sNewX = sX + 1;

				switch (pObject->ubGunAmmoType)
				{
					case AMMO_AP:
					case AMMO_SUPER_AP:
						SetFontForeground( ITEMDESC_FONTAPFORE );
						break;
					case AMMO_HP:
						SetFontForeground( ITEMDESC_FONTHPFORE );
						break;
					case AMMO_BUCKSHOT:
						SetFontForeground( ITEMDESC_FONTBSFORE );
						break;
					case AMMO_HE:
						SetFontForeground( ITEMDESC_FONTHEFORE );
						break;
					case AMMO_HEAT:
						SetFontForeground( ITEMDESC_FONTHEAPFORE );
						break;
					default:
						SetFontForeground( FONT_MCOLOR_DKGRAY );
						break;
				}


				swprintf( pStr, lengthof(pStr), L"%d", pObject->ubGunShotsLeft );
				if ( uiBuffer == guiSAVEBUFFER )
				{
					RestoreExternBackgroundRect( sNewX, sNewY, 20, 15 );
				}
				mprintf( sNewX, sNewY, pStr );
				gprintfinvalidate( sNewX, sNewY, pStr );

				SetFontForeground( FONT_MCOLOR_DKGRAY );

				// Display 'JAMMED' if we are jammed
				if ( pObject->bGunAmmoStatus < 0 )
				{
					SetFontForeground( FONT_MCOLOR_RED );

					const wchar_t* Jammed;
					if ( sWidth >= ( BIG_INV_SLOT_WIDTH - 10 )  )
					{
						Jammed = TacticalStr[JAMMED_ITEM_STR];
					}
					else
					{
						Jammed = TacticalStr[SHORT_JAMMED_GUN];
					}

					FindFontCenterCoordinates(sX, sY, sWidth, sHeight, Jammed, ITEM_FONT, &sNewX, &sNewY);
					mprintf(sNewX, sNewY, Jammed);
					gprintfinvalidate(sNewX, sNewY, Jammed);
				}
			}
			else
			{
				if ( ubStatusIndex != RENDER_ITEM_NOSTATUS )
				{
					// Now display # of items
					if ( pObject->ubNumberOfObjects > 1 )
					{
						SetFontForeground( FONT_GRAY4 );

						sNewY = sY + sHeight - 10;
						swprintf( pStr, lengthof(pStr), L"%d", pObject->ubNumberOfObjects );

						// Get length of string
						uiStringLength=StringPixLength(pStr, ITEM_FONT );

						sNewX = sX + sWidth - uiStringLength - 4;

						if ( uiBuffer == guiSAVEBUFFER )
						{
							RestoreExternBackgroundRect( sNewX, sNewY, 15, 15 );
						}
						mprintf( sNewX, sNewY, pStr );
						gprintfinvalidate( sNewX, sNewY, pStr );
					}

				}
			}

			if ( ItemHasAttachments( pObject ) )
			{
				if ( FindAttachment( pObject, UNDER_GLAUNCHER ) == NO_SLOT )
				{
					SetFontForeground( FONT_GREEN );
				}
				else
				{
					SetFontForeground( FONT_YELLOW );
				}

				sNewY = sY;
				const wchar_t* AttachMarker = L"*";

				// Get length of string
				uiStringLength = StringPixLength(AttachMarker, ITEM_FONT);

				sNewX = sX + sWidth - uiStringLength - 4;

				if ( uiBuffer == guiSAVEBUFFER )
				{
					RestoreExternBackgroundRect( sNewX, sNewY, 15, 15 );
				}
				mprintf(sNewX, sNewY, AttachMarker);
				gprintfinvalidate(sNewX, sNewY, AttachMarker);
			}

			if ( pSoldier && pObject == &(pSoldier->inv[HANDPOS] ) && ( Item[ pSoldier->inv[ HANDPOS ].usItem ].usItemClass == IC_GUN ) && pSoldier->bWeaponMode != WM_NORMAL )
			{
				SetFontForeground( FONT_DKRED );

				sNewY = sY + 13; // rather arbitrary
				const wchar_t* ModeMarker;
				if ( pSoldier->bWeaponMode == WM_BURST )
				{
					ModeMarker = L"*";
				}
				else
				{
					ModeMarker = L"+";
				}

				// Get length of string
				uiStringLength = StringPixLength(ModeMarker, ITEM_FONT);

				sNewX = sX + sWidth - uiStringLength - 4;

				if ( uiBuffer == guiSAVEBUFFER )
				{
					RestoreExternBackgroundRect( sNewX, sNewY, 15, 15 );
				}
				mprintf(sNewX, sNewY, ModeMarker);
				gprintfinvalidate(sNewX, sNewY, ModeMarker);
			}
		}
	}

	if ( pubHighlightCounter != NULL )
	{
		SetFontBackground( FONT_MCOLOR_BLACK );
		SetFontForeground( FONT_MCOLOR_LTGRAY );

		// DO HIGHLIGHT
		if ( *pubHighlightCounter )
		{
			// Set string
			const wchar_t* ItemName;
			if ( ubStatusIndex < RENDER_ITEM_ATTACHMENT1 )
			{
				ItemName = ShortItemNames[pObject->usItem];
			}
			else
			{
				ItemName = ShortItemNames[pObject->usAttachItem[ubStatusIndex - RENDER_ITEM_ATTACHMENT1]];
			}
			wcslcpy(pStr, ItemName, lengthof(pStr));

			fLineSplit = WrapString( pStr, pStr2, lengthof(pStr2), WORD_WRAP_INV_WIDTH, ITEM_FONT );

			FindFontCenterCoordinates(sX, sY, sWidth, sHeight, pStr, ITEM_FONT, &sFontX, &sFontY);
			sFontY = sY + 1;
			gprintfinvalidate( sFontX, sFontY, pStr );

			if ( fLineSplit )
			{
				FindFontCenterCoordinates(sX, sY, sWidth, sHeight, pStr2, ITEM_FONT, &sFontX2, &sFontY2);
				sFontY2 = sY + 13;
				gprintfinvalidate( sFontX2, sFontY2, pStr2 );
			}

		}

		if ( *pubHighlightCounter == 2 )
		{
			mprintf( sFontX, sFontY, pStr );

			if ( fLineSplit )
			{
				mprintf( sFontX2, sFontY2, pStr2 );
			}
		}
		else if ( *pubHighlightCounter == 1 )
		{
			*pubHighlightCounter = 0;
			gprintfRestore( sFontX, sFontY, pStr );

			if ( fLineSplit )
			{
				gprintfRestore( sFontX2, sFontY2, pStr2 );
			}
		}
	}
}


BOOLEAN InItemDescriptionBox( )
{
	return( gfInItemDescBox );
}

void CycleItemDescriptionItem( )
{
	INT16 usOldItem;

	// Delete old box...
	DeleteItemDescriptionBox( );

	// Make new item....
	usOldItem = gpItemDescSoldier->inv[ HANDPOS ].usItem;

	if ( _KeyDown( SHIFT ) )
	{
		usOldItem--;

		if ( usOldItem < 0 )
		{
			usOldItem = MAXITEMS-1;
		}
	}
	else
	{
		usOldItem++;

		if ( usOldItem > MAXITEMS )
		{
			usOldItem = 0;
		}
	}

	CreateItem( (UINT16)usOldItem, 100, &( gpItemDescSoldier->inv[ HANDPOS ] ) );

	InternalInitItemDescriptionBox( &( gpItemDescSoldier->inv[ HANDPOS ] ), 214, (INT16)(INV_INTERFACE_START_Y + 1 ), gubItemDescStatusIndex, gpItemDescSoldier );
}

BOOLEAN InitItemDescriptionBox( SOLDIERTYPE *pSoldier, UINT8 ubPosition, INT16 sX, INT16 sY, UINT8 ubStatusIndex )
{
	OBJECTTYPE *pObject;

//DEF:
	//if we are in the shopkeeper screen, and we are to use the
	if( guiCurrentScreen == SHOPKEEPER_SCREEN && ubPosition == 255 )
	{
		pObject = pShopKeeperItemDescObject;
	}

	//else use item from the hand position
	else
	{
		pObject = &(pSoldier->inv[ ubPosition ] );
	}

	return( InternalInitItemDescriptionBox( pObject, sX, sY, ubStatusIndex, pSoldier ) );
}

BOOLEAN InitKeyItemDescriptionBox( SOLDIERTYPE *pSoldier, UINT8 ubPosition, INT16 sX, INT16 sY, UINT8 ubStatusIndex )
{
	OBJECTTYPE *pObject;

	AllocateObject( &pObject );
	CreateKeyObject( pObject, pSoldier->pKeyRing[ ubPosition ].ubNumber ,pSoldier->pKeyRing[ ubPosition ].ubKeyID );

	return( InternalInitItemDescriptionBox( pObject, sX, sY, ubStatusIndex, pSoldier ) );
}


static void BtnMoneyButtonCallback(GUI_BUTTON* btn, INT32 reason);
static void ItemDescAmmoCallback(GUI_BUTTON* btn, INT32 reason);
static void ItemDescAttachmentsCallback(MOUSE_REGION* pRegion, INT32 iReason);
static void ItemDescCallback(MOUSE_REGION* pRegion, INT32 iReason);
static void ItemDescDoneButtonCallback(GUI_BUTTON* btn, INT32 reason);
static BOOLEAN ReloadItemDesc(void);


BOOLEAN InternalInitItemDescriptionBox( OBJECTTYPE *pObject, INT16 sX, INT16 sY, UINT8 ubStatusIndex, SOLDIERTYPE *pSoldier )
{
	INT32		cnt;
	wchar_t	pStr[10];
	UINT16	usX, usY;
	INT16		sForeColour;
	INT16 sProsConsIndent;

	//Set the current screen
	guiCurrentItemDescriptionScreen = guiCurrentScreen;

	// Set X, Y
	gsInvDescX = sX;
	gsInvDescY = sY;

	gpItemDescObject = pObject;
	gubItemDescStatusIndex = ubStatusIndex;
	gpItemDescSoldier = pSoldier;
	fItemDescDelete		= FALSE;

	// Build a mouse region here that is over any others.....
	if (guiCurrentItemDescriptionScreen ==  MAP_SCREEN )
	{

		//return( FALSE );

		MSYS_DefineRegion(&gInvDesc, gsInvDescX, gsInvDescY, gsInvDescX + MAP_ITEMDESC_WIDTH, gsInvDescY + MAP_ITEMDESC_HEIGHT, MSYS_PRIORITY_HIGHEST - 2, CURSOR_NORMAL, MSYS_NO_CALLBACK, ItemDescCallback);

		giMapInvDescButton = QuickCreateButtonImg("INTERFACE/itemdescdonebutton.sti", -1, 0, -1, 1, -1, gsInvDescX + 204, gsInvDescY + 107, MSYS_PRIORITY_HIGHEST, ItemDescDoneButtonCallback);

			fShowDescriptionFlag = TRUE;
	}
	else
	{
		MSYS_DefineRegion(&gInvDesc, gsInvDescX, gsInvDescY, gsInvDescX + ITEMDESC_WIDTH, gsInvDescY + ITEMDESC_HEIGHT, MSYS_PRIORITY_HIGHEST, MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemDescCallback);
	}
  // Add region
	if ( (Item[ pObject->usItem ].usItemClass & IC_GUN) && pObject->usItem != ROCKET_LAUNCHER )
	{
		// Add button
//    if( guiCurrentScreen != MAP_SCREEN )
		//if( guiCurrentItemDescriptionScreen != MAP_SCREEN )
		 swprintf( pStr, lengthof(pStr), L"%d/%d", gpItemDescObject->ubGunShotsLeft, Weapon[ gpItemDescObject->usItem ].ubMagSize );
		 sForeColour = ITEMDESC_AMMO_FORE;

		const char* Filename = "INTERFACE/infobox.sti";
		switch( pObject->ubGunAmmoType )
		{
			case AMMO_AP:
			case AMMO_SUPER_AP:
			 //sForeColour = ITEMDESC_FONTAPFORE;
				giItemDescAmmoButtonImages = LoadButtonImage(Filename, 8, 5, -1, 7, -1);
			 break;
			case AMMO_HP:
			 //sForeColour = ITEMDESC_FONTHPFORE;

				giItemDescAmmoButtonImages = LoadButtonImage(Filename, 12, 9, -1, 11, -1);
			 break;
			default:
			 //sForeColour = FONT_MCOLOR_WHITE;
				giItemDescAmmoButtonImages = LoadButtonImage(Filename, 4, 1, -1, 3, -1);
			 break;

		}

		if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
		{
			// in mapscreen, move over a bit
			giItemDescAmmoButton = CreateIconAndTextButton( giItemDescAmmoButtonImages, pStr, TINYFONT1,
															 sForeColour, FONT_MCOLOR_BLACK,
															 sForeColour, FONT_MCOLOR_BLACK,
															 TEXT_CJUSTIFIED,
															 (INT16)(ITEMDESC_AMMO_X + 18), (INT16)(ITEMDESC_AMMO_Y - 5), BUTTON_TOGGLE ,MSYS_PRIORITY_HIGHEST,
															 ItemDescAmmoCallback );

		}
		else
		{

			// not in mapscreen
		 giItemDescAmmoButton = CreateIconAndTextButton( giItemDescAmmoButtonImages, pStr, TINYFONT1,
															 sForeColour, FONT_MCOLOR_BLACK,
															 sForeColour, FONT_MCOLOR_BLACK,
															 TEXT_CJUSTIFIED,
															 (INT16)(ITEMDESC_AMMO_X), (INT16)(ITEMDESC_AMMO_Y), BUTTON_TOGGLE ,MSYS_PRIORITY_HIGHEST,
															 ItemDescAmmoCallback );

		 //if we are being called from the
		}
		//if we are being init from the shop keeper screen and this is a dealer item we are getting info from
		if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE && pShopKeeperItemDescObject != NULL )
		{
			//disable the eject button
			SpecifyDisabledButtonStyle( giItemDescAmmoButton, DISABLED_STYLE_HATCHED );

			DisableButton( giItemDescAmmoButton );
			SetButtonFastHelpText( giItemDescAmmoButton, L"\0" );
		}
		else
			SetButtonFastHelpText( giItemDescAmmoButton, Message[ STR_EJECT_AMMO ] );

		FindFontCenterCoordinates(ITEMDESC_AMMO_TEXT_X, ITEMDESC_AMMO_TEXT_Y, ITEMDESC_AMMO_TEXT_WIDTH, GetFontHeight(TINYFONT1), pStr, TINYFONT1, &usX, &usY);
		SpecifyButtonTextOffsets(giItemDescAmmoButton,  usX, usY, TRUE);
	}

	if ( ITEM_PROS_AND_CONS( gpItemDescObject->usItem ) )
	{
		if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
		{
			sProsConsIndent = __max( StringPixLength( gzProsLabel, ITEMDESC_FONT ), StringPixLength( gzConsLabel, ITEMDESC_FONT ) ) + 10;
			for ( cnt = 0; cnt < 2; cnt++ )
			{
				// Add region for pros/cons help text
				MSYS_DefineRegion( &gProsAndConsRegions[ cnt ],
					ITEMDESC_PROS_START_X + sProsConsIndent,
					gsInvDescY + gMapItemDescProsConsRects[cnt].iTop,
					gsInvDescX + gMapItemDescProsConsRects[cnt].iRight,
					gsInvDescY + gMapItemDescProsConsRects[cnt].iBottom,
					MSYS_PRIORITY_HIGHEST, MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemDescCallback );

				if (cnt == 0)
				{
					wcscpy( gzFullItemPros, gzProsLabel );
					wcscat( gzFullItemPros, L" " );
					// use temp variable to prevent an initial comma from being displayed
					wchar_t FullItemTemp[SIZE_ITEM_PROS];
					GenerateProsString(FullItemTemp, gpItemDescObject, 1000);
					wcscat(gzFullItemPros, FullItemTemp);
					SetRegionFastHelpText( &(gProsAndConsRegions[ cnt ]), gzFullItemPros );
				}
				else
				{
					wcscpy( gzFullItemCons, gzConsLabel );
					wcscat( gzFullItemCons, L" " );
					// use temp variable to prevent an initial comma from being displayed
					wchar_t FullItemTemp[SIZE_ITEM_PROS];
					GenerateConsString(FullItemTemp, gpItemDescObject, 1000);
					wcscat(gzFullItemCons, FullItemTemp);
					SetRegionFastHelpText( &(gProsAndConsRegions[ cnt ]), gzFullItemCons );
				}
			}

		}
		else
		{
			sProsConsIndent = __max( StringPixLength( gzProsLabel, ITEMDESC_FONT ), StringPixLength( gzConsLabel, ITEMDESC_FONT ) ) + 10;
			for ( cnt = 0; cnt < 2; cnt++ )
			{
				// Add region for pros/cons help text
				MSYS_DefineRegion( &gProsAndConsRegions[ cnt ],
					ITEMDESC_PROS_START_X + sProsConsIndent,
					gsInvDescY + gItemDescProsConsRects[cnt].iTop,
					gsInvDescX + gItemDescProsConsRects[cnt].iRight,
					gsInvDescY + gItemDescProsConsRects[cnt].iBottom,
					MSYS_PRIORITY_HIGHEST, MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemDescCallback );

				if (cnt == 0)
				{
					wcscpy( gzFullItemPros, gzProsLabel );
					wcscat( gzFullItemPros, L" " );
					// use temp variable to prevent an initial comma from being displayed
					wchar_t FullItemTemp[SIZE_ITEM_PROS];
					GenerateProsString(FullItemTemp, gpItemDescObject, 1000);
					wcscat(gzFullItemPros, FullItemTemp);
					SetRegionFastHelpText( &(gProsAndConsRegions[ cnt ]), gzFullItemPros );
				}
				else
				{
					wcscpy( gzFullItemCons, gzConsLabel );
					wcscat( gzFullItemCons, L" " );
					// use temp variable to prevent an initial comma from being displayed
					wchar_t FullItemTemp[SIZE_ITEM_PROS];
					GenerateConsString(FullItemTemp, gpItemDescObject, 1000);
					wcscat(gzFullItemCons, FullItemTemp);
					SetRegionFastHelpText( &(gProsAndConsRegions[ cnt ]), gzFullItemCons );
				}
			}
		}
	}

	// Load graphic
	guiItemDescBox = AddVideoObjectFromFile("INTERFACE/infobox.sti");
	CHECKF(guiItemDescBox != NO_VOBJECT);
	guiMapItemDescBox = AddVideoObjectFromFile("INTERFACE/iteminfoc.STI");
	CHECKF(guiMapItemDescBox != NO_VOBJECT);
	guiBullet = AddVideoObjectFromFile("INTERFACE/bullet.STI");
	CHECKF(guiBullet != NO_VOBJECT);

	if ( gpItemDescObject->usItem != MONEY  )
	{
		for ( cnt = 0; cnt < MAX_ATTACHMENTS; cnt++ )
		{
			// Build a mouse region here that is over any others.....
//			if (guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN )
			const INV_ATTACHXY* xy;
			INT16 dx;
			if (guiCurrentItemDescriptionScreen == MAP_SCREEN)
			{
				xy = &gMapItemDescAttachmentsXY[cnt];
				dx = 0;
			}
			else
			{
				 xy = &gItemDescAttachmentsXY[cnt];
				 dx = xy->sBarDx;
			}
			MSYS_DefineRegion(&gItemDescAttachmentRegions[cnt], gsInvDescX + xy->sX, gsInvDescY + xy->sY, gsInvDescX + xy->sX + dx + xy->sWidth, gsInvDescY + xy->sY + xy->sHeight, MSYS_PRIORITY_HIGHEST, MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemDescAttachmentsCallback);
			MSYS_SetRegionUserData( &gItemDescAttachmentRegions[cnt], 0, cnt );

			if ( gpItemDescObject->usAttachItem[ cnt ] != NOTHING )
			{
				SetRegionFastHelpText( &(gItemDescAttachmentRegions[ cnt ]), ItemNames[ gpItemDescObject->usAttachItem[ cnt ] ] );
			}
			else
			{
				SetRegionFastHelpText( &(gItemDescAttachmentRegions[ cnt ]), Message[ STR_ATTACHMENTS ] );
			}
		}
	}
	else
	{
		memset( &gRemoveMoney, 0, sizeof( REMOVE_MONEY ) );
		gRemoveMoney.uiTotalAmount = gpItemDescObject->uiMoneyAmount;
		gRemoveMoney.uiMoneyRemaining = gpItemDescObject->uiMoneyAmount;
		gRemoveMoney.uiMoneyRemoving = 0;

		// Load graphic
		guiMoneyGraphicsForDescBox = AddVideoObjectFromFile("INTERFACE/info_bil.sti");
		CHECKF(guiMoneyGraphicsForDescBox != NO_VOBJECT);

		//Create buttons for the money
//		if (guiCurrentScreen ==  MAP_SCREEN )
		guiMoneyButtonImage = LoadButtonImage("INTERFACE/Info_bil.sti", -1, 1, -1, 2, -1);
		const MoneyLoc* Loc = (guiCurrentItemDescriptionScreen == MAP_SCREEN ? &gMapMoneyButtonLoc : &gMoneyButtonLoc);
		for (cnt = 0; cnt < MAX_ATTACHMENTS - 1; cnt++)
		{
			guiMoneyButtonBtn[cnt] = CreateIconAndTextButton(
				guiMoneyButtonImage, gzMoneyAmounts[cnt], BLOCKFONT2,
				5, DEFAULT_SHADOW,
				5, DEFAULT_SHADOW,
				TEXT_CJUSTIFIED,
				(UINT16)(Loc->x + gMoneyButtonOffsets[cnt].x), (UINT16)(Loc->y + gMoneyButtonOffsets[cnt].y), BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
				BtnMoneyButtonCallback
			);
			MSYS_SetBtnUserData(guiMoneyButtonBtn[cnt], cnt);
		}
		if (gRemoveMoney.uiTotalAmount < 1000) DisableButton(guiMoneyButtonBtn[M_1000]);
		if (gRemoveMoney.uiTotalAmount <  100) DisableButton(guiMoneyButtonBtn[M_100]);
		if (gRemoveMoney.uiTotalAmount <   10) DisableButton(guiMoneyButtonBtn[M_10]);

		//Create the Done button
		guiMoneyDoneButtonImage = UseLoadedButtonImage(guiMoneyButtonImage, -1, 3, -1, 4, -1);
		guiMoneyButtonBtn[cnt] = CreateIconAndTextButton(
			guiMoneyDoneButtonImage, gzMoneyAmounts[cnt], BLOCKFONT2,
			5, DEFAULT_SHADOW,
			5, DEFAULT_SHADOW,
			TEXT_CJUSTIFIED,
			(UINT16)(Loc->x + gMoneyButtonOffsets[cnt].x), (UINT16)(Loc->y + gMoneyButtonOffsets[cnt].y), BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST,
			BtnMoneyButtonCallback
		);
		MSYS_SetBtnUserData(guiMoneyButtonBtn[cnt], cnt);
	}


	fInterfacePanelDirty = DIRTYLEVEL2;


	gfInItemDescBox = TRUE;

	CHECKF( ReloadItemDesc( ) );

	if ( gpItemPointer )
	{
		gpAttachSoldier = gpItemPointerSoldier;
	}
	else
	{
		gpAttachSoldier = pSoldier;
	}
	// store attachments that item originally had
	for ( cnt = 0; cnt < MAX_ATTACHMENTS; cnt++ )
	{
		gusOriginalAttachItem[ cnt ] = pObject->usAttachItem[ cnt ];
		gbOriginalAttachStatus[ cnt ] = pObject->bAttachStatus[ cnt ];
	}

	if (gpItemPointer != NULL && !gfItemDescHelpTextOffset && !CheckFact(FACT_ATTACHED_ITEM_BEFORE, 0))
	{
		const wchar_t* text;
		if (!(Item[pObject->usItem].fFlags & ITEM_HIDDEN_ADDON) && (
					ValidAttachment(gpItemPointer->usItem, pObject->usItem) ||
					ValidLaunchable(gpItemPointer->usItem, pObject->usItem) ||
					ValidMerge(gpItemPointer->usItem, pObject->usItem)
				))
		{
			text = Message[STR_ATTACHMENT_HELP];
		}
		else
		{
			text = Message[STR_ATTACHMENT_INVALID_HELP];
		}
		SetUpFastHelpRegion(69 + gsInvDescX, 12 + gsInvDescY, 170, text);

		StartShowingInterfaceFastHelpText();

		SetFactTrue( FACT_ATTACHED_ITEM_BEFORE );
		gfItemDescHelpTextOffset = TRUE;
	}



	return( TRUE );
}


static BOOLEAN ReloadItemDesc(void)
{
	guiItemGraphic = LoadTileGraphicForItem(&Item[gpItemDescObject->usItem]);
	if (guiItemGraphic == NO_VOBJECT) return FALSE;

	//
	// Load name, desc
	//

	//if the player is extracting money from the players account, use a different item name and description
	UINT16 Item = gpItemDescObject->usItem;
	if (Item == MONEY && gfAddingMoneyToMercFromPlayersAccount)
	{
		Item = MONEY_FOR_PLAYERS_ACCOUNT;
	}
	gzItemName = ItemNames[Item];
	return LoadItemInfo(Item, gzItemDesc);
}


static void ItemDescAmmoCallback(GUI_BUTTON*  btn, INT32 reason)
{
	if (reason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
		{
			if ( gpItemPointer == NULL && EmptyWeaponMagazine( gpItemDescObject, &gItemPointer ) )
			{
				// OK, END the description box
				//fItemDescDelete = TRUE;
				fInterfacePanelDirty = DIRTYLEVEL2;
				gpItemPointer = &gItemPointer;
				gpItemPointerSoldier = gpItemDescSoldier;

				SpecifyButtonText(giItemDescAmmoButton, L"0");

				// Set mouse
				guiExternVo = GetInterfaceGraphicForItem( &(Item[ gpItemPointer->usItem ]) );
				gusExternVoSubIndex = Item[ gpItemPointer->usItem ].ubGraphicNum;

				MSYS_ChangeRegionCursor( &gMPanelRegion , EXTERN_CURSOR );
				MSYS_SetCurrentCursor( EXTERN_CURSOR );
				fMapInventoryItem=TRUE;
				fTeamPanelDirty=TRUE;
			}
		}
		else
		{
			// Set pointer to item
			if ( gpItemPointer == NULL && EmptyWeaponMagazine( gpItemDescObject, &gItemPointer ) )
			{
				gpItemPointer = &gItemPointer;
				gpItemPointerSoldier = gpItemDescSoldier;

				// if in SKI, load item into SKI's item pointer
				if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
				{
					// pick up bullets from weapon into cursor (don't try to sell)
					BeginSkiItemPointer( PLAYERS_INVENTORY, -1, FALSE );
				}

				// OK, END the description box
				//fItemDescDelete = TRUE;
				fInterfacePanelDirty = DIRTYLEVEL2;

				SpecifyButtonText(giItemDescAmmoButton, L"0");

				fItemDescDelete = TRUE;
			}
		}
	}
}


static void DoAttachment(void)
{
	if ( AttachObject( gpItemDescSoldier, gpItemDescObject, gpItemPointer ) )
	{
		if (gpItemPointer->usItem == NOTHING)
		{
			// attachment attached, merge item consumed, etc

    	if ( guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN )
      {
        MAPEndItemPointer( );
      }
      else
      {
				// End Item pickup
				gpItemPointer = NULL;
				EnableSMPanelButtons( TRUE , TRUE );

				MSYS_ChangeRegionCursor( &gSMPanelRegion , CURSOR_NORMAL );
				SetCurrentCursorFromDatabase( CURSOR_NORMAL );

				//if we are currently in the shopkeeper interface
				if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
				{
					//Clear out the moving cursor
					memset( &gMoveingItem, 0, sizeof( INVENTORY_IN_SLOT ) );

					//change the curosr back to the normal one
					SetSkiCursor( CURSOR_NORMAL );
				}
			}
		}

		if ( gpItemDescObject->usItem == NOTHING )
		{
			// close desc panel panel
			DeleteItemDescriptionBox();
		}
		//Dirty interface
		fInterfacePanelDirty = DIRTYLEVEL2;

		ReloadItemDesc( );
	}

	// re-evaluate repairs
	gfReEvaluateEveryonesNothingToDo = TRUE;
}


static void PermanantAttachmentMessageBoxCallBack(UINT8 ubExitValue)
{
	if ( ubExitValue == MSG_BOX_RETURN_YES )
	{
		DoAttachment();
	}
	// else do nothing
}


static void ItemDescAttachmentsCallback(MOUSE_REGION* pRegion, INT32 iReason)
{
	UINT32					uiItemPos;
	static BOOLEAN	fRightDown = FALSE;

	if ( gfItemDescObjectIsAttachment )
	{
		// screen out completely
		return;
	}

	uiItemPos = MSYS_GetRegionUserData( pRegion, 0 );

	if (iReason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		// if the item being described belongs to a shopkeeper, ignore attempts to pick it up / replace it
		if( ( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE ) && ( pShopKeeperItemDescObject != NULL ) )
		{
			return;
		}

		// Try to place attachment if something is in our hand
		// require as many APs as to reload
		if ( gpItemPointer != NULL )
		{
			// nb pointer could be NULL because of inventory manipulation in mapscreen from sector inv
			if ( !gpItemPointerSoldier || EnoughPoints( gpItemPointerSoldier, AP_RELOAD_GUN, 0, TRUE ) )
			{
				if ( (Item[ gpItemPointer->usItem ].fFlags & ITEM_INSEPARABLE) && ValidAttachment( gpItemPointer->usItem, gpItemDescObject->usItem ) )
				{
					DoScreenIndependantMessageBox( Message[ STR_PERMANENT_ATTACHMENT ], ( UINT8 )MSG_BOX_FLAG_YESNO, PermanantAttachmentMessageBoxCallBack );
					return;
				}

				DoAttachment();
			}
		}
		else
		{
      // ATE: Make sure we have enough AP's to drop it if we pick it up!
			if ( EnoughPoints( gpItemDescSoldier, ( AP_RELOAD_GUN + AP_PICKUP_ITEM ), 0, TRUE ) )
			{
				// Get attachment if there is one
				// The follwing function will handle if no attachment is here
				if ( RemoveAttachment( gpItemDescObject, (UINT8)uiItemPos, &gItemPointer ) )
				{
					gpItemPointer = &gItemPointer;
					gpItemPointerSoldier = gpItemDescSoldier;

	//				if( guiCurrentScreen == MAP_SCREEN )
					if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
					{
						// Set mouse
						guiExternVo = GetInterfaceGraphicForItem( &(Item[ gpItemPointer->usItem ]) );
						gusExternVoSubIndex = Item[ gpItemPointer->usItem ].ubGraphicNum;

						MSYS_ChangeRegionCursor( &gMPanelRegion , EXTERN_CURSOR );
						MSYS_SetCurrentCursor( EXTERN_CURSOR );
						fMapInventoryItem=TRUE;
						fTeamPanelDirty=TRUE;
					}

					//if we are currently in the shopkeeper interface
					else if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
					{
						// pick up attachment from item into cursor (don't try to sell)
						BeginSkiItemPointer( PLAYERS_INVENTORY, -1, FALSE );
					}

					//Dirty interface
					fInterfacePanelDirty = DIRTYLEVEL2;

					// re-evaluate repairs
					gfReEvaluateEveryonesNothingToDo = TRUE;

					UpdateItemHatches();
				}
			}
		}
	}
	else if (iReason & MSYS_CALLBACK_REASON_RBUTTON_DWN )
	{
		fRightDown = TRUE;
	}
	else if (iReason & MSYS_CALLBACK_REASON_RBUTTON_UP && fRightDown )
	{
		static OBJECTTYPE Object2;

		fRightDown = FALSE;

		if ( gpItemDescObject->usAttachItem[ uiItemPos ] != NOTHING )
		{
			BOOLEAN fShopkeeperItem = FALSE;

			// remember if this is a shopkeeper's item we're viewing ( pShopKeeperItemDescObject will get nuked on deletion )
			if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE && pShopKeeperItemDescObject != NULL )
			{
				fShopkeeperItem = TRUE;
			}

			DeleteItemDescriptionBox( );

			if ( CreateItem( gpItemDescObject->usAttachItem[ uiItemPos ], gpItemDescObject->bAttachStatus[ uiItemPos ], &Object2 ) )
			{
				gfItemDescObjectIsAttachment = TRUE;
				InternalInitItemDescriptionBox( &Object2, gsInvDescX, gsInvDescY, 0, gpItemDescSoldier );

				if ( fShopkeeperItem )
				{
					pShopKeeperItemDescObject = &Object2;
					StartSKIDescriptionBox( );
				}
			}
		}
	}
}

void RenderItemDescriptionBox( )
{
	INT16									sStrX;
	UINT16								uiStringLength, uiRightLength;
	static wchar_t				pStr[ 100 ];
	INT32									cnt;
	FLOAT									fWeight;
	UINT16								usX, usY;
	UINT8									ubAttackAPs;
	BOOLEAN								fHatchOutAttachments = gfItemDescObjectIsAttachment; // if examining attachment, always hatch out attachment slots
	INT16									sProsConsIndent;

  if( ( guiCurrentItemDescriptionScreen == MAP_SCREEN ) &&(gfInItemDescBox ) )
	{
    	// TAKE A LOOK AT THE VIDEO OBJECT SIZE ( ONE OF TWO SIZES ) AND CENTER!
		const ETRLEObject* pTrav = GetVideoObjectETRLESubregionProperties(guiItemGraphic, 0);
		UINT32 usHeight = pTrav->usHeight;
		UINT32 usWidth  = pTrav->usWidth;

		// CENTER IN SLOT!
		// REMOVE OFFSETS!
		INT16 sCenX = MAP_ITEMDESC_ITEM_X + abs(ITEMDESC_ITEM_WIDTH  - usWidth)  / 2 - pTrav->sOffsetX;
		INT16 sCenY = MAP_ITEMDESC_ITEM_Y + abs(ITEMDESC_ITEM_HEIGHT - usHeight) / 2 - pTrav->sOffsetY;

		BltVideoObjectFromIndex( guiSAVEBUFFER, guiMapItemDescBox, 0, gsInvDescX, gsInvDescY);

		//Display the money 'seperating' border
		if ( gpItemDescObject->usItem == MONEY )
		{
			//Render the money Boxes
			BltVideoObjectFromIndex( guiSAVEBUFFER, guiMoneyGraphicsForDescBox, 0, (UINT16)(gMapMoneyButtonLoc.x + gMoneyButtonOffsets[0].x), (UINT16)(gMapMoneyButtonLoc.y + gMoneyButtonOffsets[0].y));
		}


		// Display item
		BltVideoObjectOutlineShadowFromIndex( guiSAVEBUFFER, guiItemGraphic, 0, sCenX - 2, sCenY + 2  );

		BltVideoObjectFromIndex( guiSAVEBUFFER, guiItemGraphic, 0, sCenX, sCenY);


		// Display ststus
		DrawItemUIBarEx( gpItemDescObject, gubItemDescStatusIndex, (INT16)MAP_ITEMDESC_ITEM_STATUS_X, (INT16)MAP_ITEMDESC_ITEM_STATUS_Y, ITEMDESC_ITEM_STATUS_WIDTH, ITEMDESC_ITEM_STATUS_HEIGHT_MAP, 	Get16BPPColor( DESC_STATUS_BAR ), Get16BPPColor( DESC_STATUS_BAR_SHADOW ), TRUE, guiSAVEBUFFER );

		if (gpItemPointer)
		{
			if ( ( Item[ gpItemPointer->usItem ].fFlags & ITEM_HIDDEN_ADDON ) ||

			 ( !ValidItemAttachment( gpItemDescObject, gpItemPointer->usItem, FALSE ) &&
				 !ValidMerge( gpItemPointer->usItem, gpItemDescObject->usItem ) && !ValidLaunchable( gpItemPointer->usItem, gpItemDescObject->usItem ) ) )
			{
				// hatch out the attachment panels
				fHatchOutAttachments = TRUE;
			}
		}

		// Display attachments
		for ( cnt = 0; cnt < MAX_ATTACHMENTS; cnt++ )
		{
			if ( gpItemDescObject->usAttachItem[ cnt ] != NOTHING )
			{

//        if (guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN )
				if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
				{
         sCenX = (INT16)( gsInvDescX + gMapItemDescAttachmentsXY[cnt].sX + 5 );
				 sCenY = (INT16)( gsInvDescY + gMapItemDescAttachmentsXY[cnt].sY - 1 );

				 INVRenderItem( guiSAVEBUFFER, NULL, gpItemDescObject, sCenX, sCenY, gMapItemDescAttachmentsXY[cnt].sWidth, gMapItemDescAttachmentsXY[cnt].sHeight, DIRTYLEVEL2, NULL, (UINT8)(RENDER_ITEM_ATTACHMENT1 + cnt), FALSE, 0 );

				 sCenX = sCenX - gMapItemDescAttachmentsXY[cnt].sBarDx;
				 sCenY = sCenY + gMapItemDescAttachmentsXY[cnt].sBarDy;
				 DrawItemUIBarEx( gpItemDescObject, (UINT8)(DRAW_ITEM_STATUS_ATTACHMENT1 + cnt), sCenX, sCenY, ITEM_BAR_WIDTH, ITEM_BAR_HEIGHT, Get16BPPColor( STATUS_BAR ), Get16BPPColor( STATUS_BAR_SHADOW ), TRUE , guiSAVEBUFFER );

				}
				else
				{
				 sCenX = (INT16)( gsInvDescX + gMapItemDescAttachmentsXY[cnt].sX + 5 );
				 sCenY = (INT16)( gsInvDescY + gMapItemDescAttachmentsXY[cnt].sY - 1 );

				 INVRenderItem( guiSAVEBUFFER, NULL, gpItemDescObject, sCenX, sCenY, gMapItemDescAttachmentsXY[cnt].sWidth, gMapItemDescAttachmentsXY[cnt].sHeight, DIRTYLEVEL2, NULL, (UINT8)(RENDER_ITEM_ATTACHMENT1 + cnt), FALSE, 0 );

				 sCenX = sCenX - gItemDescAttachmentsXY[cnt].sBarDx;
				 sCenY = sCenY + gItemDescAttachmentsXY[cnt].sBarDy;
				 DrawItemUIBarEx( gpItemDescObject, (UINT8)(DRAW_ITEM_STATUS_ATTACHMENT1 + cnt), sCenX, sCenY, ITEM_BAR_WIDTH, ITEM_BAR_HEIGHT, Get16BPPColor( STATUS_BAR ), Get16BPPColor( STATUS_BAR_SHADOW ), TRUE , guiSAVEBUFFER );


				}
			}

			if (fHatchOutAttachments )
			{
				DrawHatchOnInventory( guiSAVEBUFFER, (INT16) (gsInvDescX + gMapItemDescAttachmentsXY[ cnt ].sX), (INT16) (gsInvDescY + gMapItemDescAttachmentsXY[ cnt ].sY - 2), (INT16)(gMapItemDescAttachmentsXY[ cnt ].sWidth + gMapItemDescAttachmentsXY[ cnt ].sBarDx), (INT16) (gMapItemDescAttachmentsXY[ cnt ].sHeight + 2) );
			}

		}

		if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_GUN )
		{
			// display bullets for ROF
			BltVideoObjectFromIndex( guiSAVEBUFFER, guiBullet, 0, MAP_BULLET_SING_X, MAP_BULLET_SING_Y);

			if (Weapon[ gpItemDescObject->usItem ].ubShotsPerBurst > 0)
			{
				for ( cnt = 0; cnt < Weapon[ gpItemDescObject->usItem ].ubShotsPerBurst; cnt++ )
				{
					BltVideoObjectFromIndex( guiSAVEBUFFER, guiBullet, 0, MAP_BULLET_BURST_X + cnt * (BULLET_WIDTH + 1), MAP_BULLET_BURST_Y);
				}
			}

		}

		RestoreExternBackgroundRect( gsInvDescX, gsInvDescY, MAP_ITEMDESC_WIDTH, MAP_ITEMDESC_HEIGHT );

		// Render font desc
		SetFont( ITEMDESC_FONT );
		SetFontBackground( FONT_MCOLOR_BLACK );
		SetFontForeground( FONT_FCOLOR_WHITE );
		SetFontShadow( ITEMDESC_FONTSHADOW3 );

		// Render name
		#ifdef JA2TESTVERSION
			mprintf( MAP_ITEMDESC_NAME_X, MAP_ITEMDESC_NAME_Y, L"%ls (%d)", gzItemName, gpItemDescObject->usItem );
		#else
			mprintf( MAP_ITEMDESC_NAME_X, MAP_ITEMDESC_NAME_Y, L"%ls", gzItemName );
		#endif

		SetFontForeground( FONT_BLACK );
		SetFontShadow( ITEMDESC_FONTSHADOW2 );

		DisplayWrappedString(MAP_ITEMDESC_DESC_START_X, MAP_ITEMDESC_DESC_START_Y, MAP_ITEMDESC_DESC_WIDTH, 2, ITEMDESC_FONT, FONT_BLACK, gzItemDesc, FONT_MCOLOR_BLACK, LEFT_JUSTIFIED);

		if ( ITEM_PROS_AND_CONS( gpItemDescObject->usItem ) )
		{
			if ( (gpItemDescObject->usItem == ROCKET_RIFLE || gpItemDescObject->usItem == AUTO_ROCKET_RIFLE) && gpItemDescObject->ubImprintID < NO_PROFILE )
			{
				// add name noting imprint
				swprintf( pStr, lengthof(pStr), L"%ls %ls (%ls)", AmmoCaliber[ Weapon[ gpItemDescObject->usItem ].ubCalibre ], WeaponType[ Weapon[ gpItemDescObject->usItem ].ubWeaponType ], gMercProfiles[ gpItemDescObject->ubImprintID ].zNickname );
			}
			else
			{
				swprintf( pStr, lengthof(pStr), L"%ls %ls", AmmoCaliber[ Weapon[ gpItemDescObject->usItem ].ubCalibre ], WeaponType[ Weapon[ gpItemDescObject->usItem ].ubWeaponType ] );
			}

			FindFontRightCoordinates(MAP_ITEMDESC_CALIBER_X, MAP_ITEMDESC_CALIBER_Y, MAP_ITEMDESC_CALIBER_WIDTH, ITEM_STATS_HEIGHT, pStr, ITEMDESC_FONT, &usX, &usY);
			mprintf( usX, usY, pStr );

			SetFontForeground( FONT_MCOLOR_DKWHITE2 );
			SetFontShadow( ITEMDESC_FONTSHADOW3 );
			mprintf( (INT16)MAP_ITEMDESC_PROS_START_X, (INT16)MAP_ITEMDESC_PROS_START_Y, gzProsLabel );

			sProsConsIndent = __max( StringPixLength( gzProsLabel, ITEMDESC_FONT ), StringPixLength( gzConsLabel, ITEMDESC_FONT ) ) + 10;

			GenerateProsString( gzItemPros, gpItemDescObject, MAP_ITEMDESC_DESC_WIDTH - sProsConsIndent - StringPixLength( DOTDOTDOT, ITEMDESC_FONT ) );
			if (gzItemPros[0] != 0)
			{
				SetFontForeground( FONT_BLACK );
				SetFontShadow( ITEMDESC_FONTSHADOW2 );
				DisplayWrappedString(MAP_ITEMDESC_PROS_START_X + sProsConsIndent, MAP_ITEMDESC_PROS_START_Y, ITEMDESC_DESC_WIDTH - sProsConsIndent, 2, ITEMDESC_FONT, FONT_BLACK, gzItemPros, FONT_MCOLOR_BLACK, LEFT_JUSTIFIED);
			}

			SetFontForeground( FONT_MCOLOR_DKWHITE2 );
			SetFontShadow( ITEMDESC_FONTSHADOW3 );
			mprintf( (INT16)MAP_ITEMDESC_CONS_START_X, (INT16)MAP_ITEMDESC_CONS_START_Y, gzConsLabel );

			GenerateConsString( gzItemCons, gpItemDescObject, MAP_ITEMDESC_DESC_WIDTH - sProsConsIndent - StringPixLength( DOTDOTDOT, ITEMDESC_FONT ) );
			if (gzItemCons[0] != 0)
			{
				SetFontForeground( FONT_BLACK );
				SetFontShadow( ITEMDESC_FONTSHADOW2 );
				DisplayWrappedString(MAP_ITEMDESC_CONS_START_X + sProsConsIndent, MAP_ITEMDESC_CONS_START_Y, ITEMDESC_DESC_WIDTH - sProsConsIndent, 2, ITEMDESC_FONT, FONT_BLACK, gzItemCons, FONT_MCOLOR_BLACK, LEFT_JUSTIFIED);
			}
		}

/*
		DisplayWrappedString(MAP_ITEMDESC_PROS_START_X, MAP_ITEMDESC_PROS_START_Y, MAP_ITEMDESC_DESC_WIDTH, 2, ITEMDESC_FONT, FONT_BLACK, gzProsLabel, FONT_MCOLOR_BLACK, LEFT_JUSTIFIED);
		if (gzItemPros[0] != 0)
		{
			DisplayWrappedString(MAP_ITEMDESC_PROS_START_X, MAP_ITEMDESC_PROS_START_Y, MAP_ITEMDESC_DESC_WIDTH, 2, ITEMDESC_FONT, FONT_BLACK, gzItemPros, FONT_MCOLOR_BLACK, LEFT_JUSTIFIED);
		}

		DisplayWrappedString(MAP_ITEMDESC_CONS_START_X, MAP_ITEMDESC_CONS_START_Y, MAP_ITEMDESC_DESC_WIDTH, 2, ITEMDESC_FONT, FONT_BLACK, gzConsLabel, FONT_MCOLOR_BLACK, LEFT_JUSTIFIED);
		if (gzItemCons[0] != 0)
		{
			DisplayWrappedString(MAP_ITEMDESC_CONS_START_X, MAP_ITEMDESC_CONS_START_Y, MAP_ITEMDESC_DESC_WIDTH, 2, ITEMDESC_FONT, FONT_BLACK, gzItemCons, FONT_MCOLOR_BLACK, LEFT_JUSTIFIED);
		}
*/

		// Get length of string
		uiRightLength=35;


		fWeight = (float)(CalculateObjectWeight( gpItemDescObject )) / 10;
		if ( !gGameSettings.fOptions[ TOPTION_USE_METRIC_SYSTEM ] ) // metric units not enabled
		{
			fWeight = fWeight * 2.2f;
		}

		// Add weight of attachments here !

		if ( fWeight < 0.1 )
		{
			fWeight = 0.1f;
		}

		// Render, stat  name
		if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_WEAPON )
		{
			SetFont( BLOCKFONT2 );
			SetFontForeground( 6 );
			SetFontShadow( DEFAULT_SHADOW );

			//LABELS
			mprintf(gMapWeaponStats[0].sX + gsInvDescX, gMapWeaponStats[0].sY + gsInvDescY, gWeaponStatsDesc[0], GetWeightUnitString());
			if ( Item[ gpItemDescObject->usItem ].usItemClass & (IC_GUN | IC_LAUNCHER ) )
			{
				mprintf( gMapWeaponStats[ 3 ].sX + gsInvDescX, gMapWeaponStats[ 3 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 3 ] );
			}
			if ( !(Item[ gpItemDescObject->usItem ].usItemClass & IC_LAUNCHER) && gpItemDescObject->usItem != ROCKET_LAUNCHER )
			{
				mprintf( gMapWeaponStats[ 4 ].sX + gsInvDescX, gMapWeaponStats[ 4 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 4 ] );
			}
			mprintf( gMapWeaponStats[ 5 ].sX + gsInvDescX, gMapWeaponStats[ 5 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 5 ] );
			if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_GUN )
			{
				// equals sign
				mprintf( gMapWeaponStats[ 7 ].sX + gsInvDescX, gMapWeaponStats[ 7 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 7 ] );
			}
			mprintf( gMapWeaponStats[ 1 ].sX + gsInvDescX, gMapWeaponStats[ 1 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 1 ] );


			if (Weapon[ gpItemDescObject->usItem ].ubShotsPerBurst > 0)
			{
				mprintf( gMapWeaponStats[ 8 ].sX + gsInvDescX, gMapWeaponStats[ 8 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 8 ] );
			}

			SetFontForeground( 5 );
			//Status
			swprintf( pStr, lengthof(pStr), L"%2d%%", gpItemDescObject->bStatus[ gubItemDescStatusIndex ] );
			FindFontRightCoordinates(gMapWeaponStats[1].sX + gsInvDescX + gMapWeaponStats[1].sValDx + 6, gMapWeaponStats[1].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
			mprintf(usX, usY, L"%ls", pStr);

			// Values
			if (fWeight <= (EXCEPTIONAL_WEIGHT / 10))
			{
				SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
			}
			else
			{
				SetFontForeground( 5 );
			}
			//Weight
			swprintf( pStr, lengthof(pStr), L"%1.1f", fWeight );
			FindFontRightCoordinates(gMapWeaponStats[0].sX + gsInvDescX + gMapWeaponStats[0].sValDx + 6, gMapWeaponStats[0].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
			mprintf( usX, usY, pStr );

			if ( Item[ gpItemDescObject->usItem ].usItemClass & (IC_GUN | IC_LAUNCHER) )
			{

				if ( GunRange( gpItemDescObject ) >= EXCEPTIONAL_RANGE)
				{
					SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
				}
				else
				{
					SetFontForeground( 5 );
				}

				//Range
				 swprintf( pStr, lengthof(pStr), L"%2d", ( GunRange( gpItemDescObject ) ) / 10 );
				 FindFontRightCoordinates(gMapWeaponStats[3].sX + gsInvDescX + gMapWeaponStats[3].sValDx, gMapWeaponStats[3].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
				 mprintf( usX, usY, pStr );
			}

			if ( !(Item[ gpItemDescObject->usItem ].usItemClass & IC_LAUNCHER) && gpItemDescObject->usItem != ROCKET_LAUNCHER )
			{

				if (Weapon[ gpItemDescObject->usItem ].ubImpact  >= EXCEPTIONAL_DAMAGE)
				{
					SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
				}
				else
				{
					SetFontForeground( 5 );
				}

				//Damage
			 swprintf( pStr, lengthof(pStr), L"%2d", Weapon[ gpItemDescObject->usItem ].ubImpact );
			 FindFontRightCoordinates(gMapWeaponStats[4].sX + gsInvDescX + gMapWeaponStats[4].sValDx, gMapWeaponStats[4].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
			 mprintf( usX, usY, pStr );
		  }

			 ubAttackAPs = BaseAPsToShootOrStab( DEFAULT_APS, DEFAULT_AIMSKILL, gpItemDescObject );

				if (ubAttackAPs <= EXCEPTIONAL_AP_COST)
				{
					SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
				}
				else
				{
					SetFontForeground( 5 );
				}

			 //Ap's
			 swprintf( pStr, lengthof(pStr), L"%2d", ubAttackAPs );
			 FindFontRightCoordinates(gMapWeaponStats[5].sX + gsInvDescX + gMapWeaponStats[5].sValDx, gMapWeaponStats[5].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
			 mprintf( usX, usY, pStr );

			 if (Weapon[ gpItemDescObject->usItem ].ubShotsPerBurst > 0)
			 {

				if (Weapon[ gpItemDescObject->usItem ].ubShotsPerBurst >= EXCEPTIONAL_BURST_SIZE || gpItemDescObject->usItem == G11)
				{
					SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
				}
				else
				{
					SetFontForeground( 5 );
				}

			  swprintf( pStr, lengthof(pStr), L"%2d", ubAttackAPs + CalcAPsToBurst( DEFAULT_APS, gpItemDescObject ) );
			  FindFontRightCoordinates(gMapWeaponStats[6].sX + gsInvDescX + gMapWeaponStats[6].sValDx, gMapWeaponStats[6].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
			  mprintf( usX, usY, pStr );
			 }

		}
		else if ( gpItemDescObject->usItem == MONEY )
		{

			SetFontForeground( FONT_FCOLOR_WHITE );
			SetFontShadow( DEFAULT_SHADOW );

			//
			// Display the total amount of money
			//

			// if the player is taking money from their account
			SPrintMoney(pStr, gfAddingMoneyToMercFromPlayersAccount ? LaptopSaveInfo.iCurrentBalance : gRemoveMoney.uiTotalAmount);
			uiStringLength=StringPixLength(pStr, ITEMDESC_FONT );
			sStrX =  MAP_ITEMDESC_NAME_X + ( 245 - uiStringLength );
			mprintf( sStrX, MAP_ITEMDESC_NAME_Y, pStr );

			SetFont( BLOCKFONT2 );

			SetFontForeground( 6 );
			SetFontShadow( DEFAULT_SHADOW );

			//Display the 'Removing'
			mprintf( gMapMoneyStats[ 0 ].sX + gsInvDescX, gMapMoneyStats[ 0 ].sY + gsInvDescY, L"%ls", gMoneyStatsDesc[ MONEY_DESC_AMOUNT ] );
			//Display the 'REmaining'
			mprintf( gMapMoneyStats[ 2 ].sX + gsInvDescX, gMapMoneyStats[ 2 ].sY + gsInvDescY, L"%ls", gMoneyStatsDesc[ MONEY_DESC_AMOUNT_2_SPLIT ] );

			//Display the 'Amt removing'
			mprintf( gMapMoneyStats[ 1 ].sX + gsInvDescX, gMapMoneyStats[ 1 ].sY + gsInvDescY, L"%ls", gMoneyStatsDesc[ MONEY_DESC_REMAINING ] );
			//Display the 'REmaining amount'
			mprintf( gMapMoneyStats[ 3 ].sX + gsInvDescX, gMapMoneyStats[ 3 ].sY + gsInvDescY, L"%ls", gMoneyStatsDesc[ MONEY_DESC_TO_SPLIT ] );

			SetFontForeground( 5 );

			//Display the 'Seperate text'
			mprintf( (UINT16)(gMapMoneyButtonLoc.x + gMoneyButtonOffsets[cnt].x), (UINT16)(gMapMoneyButtonLoc.y + gMoneyButtonOffsets[cnt].y ), gzMoneyAmounts[4] );

			// The Money Remaining
			SPrintMoney(pStr, gRemoveMoney.uiMoneyRemaining);
			uiStringLength=StringPixLength(pStr, ITEMDESC_FONT );
			sStrX =  gMapMoneyStats[ 1 ].sX + gsInvDescX + gMapMoneyStats[ 1 ].sValDx + ( uiRightLength - uiStringLength );
			mprintf( sStrX, gMapMoneyStats[ 1 ].sY + gsInvDescY, pStr );


			// The money removing
			SetFontForeground( 5 );
			SPrintMoney(pStr, gRemoveMoney.uiMoneyRemoving);
			uiStringLength=StringPixLength(pStr, ITEMDESC_FONT );
			sStrX =  gMapMoneyStats[ 3 ].sX + gsInvDescX + gMapMoneyStats[ 3 ].sValDx + ( uiRightLength - uiStringLength );
			mprintf( sStrX, gMapMoneyStats[ 3 ].sY + gsInvDescY, pStr );
		}
		else if ( Item[ gpItemDescObject->usItem ].usItemClass == IC_MONEY )
		{
			SetFontForeground( FONT_FCOLOR_WHITE );
			SetFontShadow( DEFAULT_SHADOW );
			SPrintMoney(pStr, gpItemDescObject->uiMoneyAmount);
			uiStringLength=StringPixLength(pStr, ITEMDESC_FONT );
			sStrX =  MAP_ITEMDESC_NAME_X + ( 245 - uiStringLength );
			mprintf( sStrX, MAP_ITEMDESC_NAME_Y, pStr );
		}
		else
		{
			//Labels
			SetFont( BLOCKFONT2 );

			SetFontForeground( 6 );
			SetFontShadow( DEFAULT_SHADOW );

			if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_AMMO )
			{
				mprintf( gMapWeaponStats[ 2 ].sX + gsInvDescX, gMapWeaponStats[ 2 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 2 ] );
			}
			else
			{
				mprintf( gMapWeaponStats[ 1 ].sX + gsInvDescX, gMapWeaponStats[ 1 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 1 ] );
			}
			mprintf(gMapWeaponStats[0].sX + gsInvDescX, gMapWeaponStats[0].sY + gsInvDescY, gWeaponStatsDesc[0], GetWeightUnitString());

			// Values
			SetFontForeground( 5 );


			if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_AMMO )
			{
				// Ammo
					swprintf( pStr, lengthof(pStr), L"%d/%d", gpItemDescObject->ubShotsLeft[0], Magazine[ Item[ gpItemDescObject->usItem ].ubClassIndex ].ubMagSize );
					uiStringLength=StringPixLength(pStr, ITEMDESC_FONT );
		//			sStrX =  gMapWeaponStats[ 0 ].sX + gsInvDescX + gMapWeaponStats[ 0 ].sValDx + ( uiRightLength - uiStringLength );
					FindFontRightCoordinates(gMapWeaponStats[2].sX + gsInvDescX + gMapWeaponStats[2].sValDx + 6, gMapWeaponStats[2].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &sStrX, &usY);
					mprintf( sStrX, gMapWeaponStats[ 2 ].sY + gsInvDescY, pStr );
			}
			else
			{
				//Status
				swprintf( pStr, lengthof(pStr), L"%2d%%", gpItemDescObject->bStatus[ gubItemDescStatusIndex ] );
				uiStringLength=StringPixLength(pStr, ITEMDESC_FONT );
	//			sStrX =  gMapWeaponStats[ 1 ].sX + gsInvDescX + gMapWeaponStats[ 1 ].sValDx + ( uiRightLength - uiStringLength );
				FindFontRightCoordinates(gMapWeaponStats[1].sX + gsInvDescX + gMapWeaponStats[1].sValDx + 6, gMapWeaponStats[1].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &sStrX, &usY);
				mprintf(sStrX, gMapWeaponStats[1].sY + gsInvDescY, L"%ls", pStr);
			}

			//Weight
			swprintf( pStr, lengthof(pStr), L"%1.1f", fWeight );
			uiStringLength=StringPixLength(pStr, ITEMDESC_FONT );
//			sStrX =  gMapWeaponStats[ 0 ].sX + gsInvDescX + gMapWeaponStats[ 0 ].sValDx + ( uiRightLength - uiStringLength );
			FindFontRightCoordinates(gMapWeaponStats[0].sX + gsInvDescX + gMapWeaponStats[0].sValDx + 6, gMapWeaponStats[0].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &sStrX, &usY);
			mprintf( sStrX, gMapWeaponStats[ 0 ].sY + gsInvDescY, pStr );

			if ( ( InKeyRingPopup() == TRUE ) || ( Item[ gpItemDescObject->usItem ].usItemClass & IC_KEY ) )
			{
				SetFontForeground( 6 );

				// build description for keys .. the sector found
				mprintf(gMapWeaponStats[4].sX + gsInvDescX, gMapWeaponStats[4].sY + gsInvDescY, sKeyDescriptionStrings[0]);
				mprintf(gMapWeaponStats[4].sX + gsInvDescX, gMapWeaponStats[4].sY + gsInvDescY + GetFontHeight(BLOCKFONT) + 2 , sKeyDescriptionStrings[1]);


				SetFontForeground( 5 );
				wchar_t sTempString[128];
				GetShortSectorString( ( INT16 ) SECTORX( KeyTable[ gpItemDescObject->ubKeyID ].usSectorFound ), ( INT16 ) SECTORY( KeyTable[ gpItemDescObject->ubKeyID ].usSectorFound ), sTempString, lengthof(sTempString));
				FindFontRightCoordinates(gMapWeaponStats[4].sX + gsInvDescX, gMapWeaponStats[4].sY + gsInvDescY, 110, ITEM_STATS_HEIGHT, sTempString, BLOCKFONT2, &usX, &usY);
				mprintf(usX, usY, sTempString);

				swprintf( pStr, lengthof(pStr), L"%d", KeyTable[ gpItemDescObject->ubKeyID ].usDateFound );
				FindFontRightCoordinates(gMapWeaponStats[4].sX + gsInvDescX, gMapWeaponStats[4].sY + gsInvDescY + GetFontHeight(BLOCKFONT) + 2, 110, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
				mprintf( usX, usY, pStr );
			}

		}

		SetFontShadow( DEFAULT_SHADOW );
	}
	else if ( gfInItemDescBox )
	{
		// TAKE A LOOK AT THE VIDEO OBJECT SIZE ( ONE OF TWO SIZES ) AND CENTER!
		const ETRLEObject* pTrav = GetVideoObjectETRLESubregionProperties(guiItemGraphic, 0);
		UINT32 usHeight = pTrav->usHeight;
		UINT32 usWidth  = pTrav->usWidth;

		// CENTER IN SLOT!
		INT16 sCenX = ITEMDESC_ITEM_X + abs(ITEMDESC_ITEM_WIDTH  - usWidth)  / 2 - pTrav->sOffsetX;
		INT16 sCenY = ITEMDESC_ITEM_Y + abs(ITEMDESC_ITEM_HEIGHT - usHeight) / 2 - pTrav->sOffsetY;

		BltVideoObjectFromIndex( guiSAVEBUFFER, guiItemDescBox, 0, gsInvDescX, gsInvDescY);

		if ( gpItemDescObject->usItem == MONEY )
		{
			//Render the money Boxes
			BltVideoObjectFromIndex( guiSAVEBUFFER, guiMoneyGraphicsForDescBox, 0, (UINT16)(gsInvDescX+gItemDescAttachmentsXY[0].sX-1), (UINT16)(gsInvDescY+gItemDescAttachmentsXY[0].sY-2));
		}


		// Display item
		BltVideoObjectOutlineShadowFromIndex( guiSAVEBUFFER, guiItemGraphic, 0, sCenX - 2, sCenY + 2  );
		BltVideoObjectFromIndex( guiSAVEBUFFER, guiItemGraphic, 0, sCenX, sCenY);

		// Display status
		DrawItemUIBarEx( gpItemDescObject, gubItemDescStatusIndex, (INT16)ITEMDESC_ITEM_STATUS_X, (INT16)ITEMDESC_ITEM_STATUS_Y, ITEMDESC_ITEM_STATUS_WIDTH, ITEMDESC_ITEM_STATUS_HEIGHT, 	Get16BPPColor( DESC_STATUS_BAR ), Get16BPPColor( DESC_STATUS_BAR_SHADOW ), TRUE, guiSAVEBUFFER );

		if (gpItemPointer)
		{
			if ( ( Item[ gpItemPointer->usItem ].fFlags & ITEM_HIDDEN_ADDON ) ||

			 ( !ValidItemAttachment( gpItemDescObject, gpItemPointer->usItem, FALSE ) &&
				 !ValidMerge( gpItemPointer->usItem, gpItemDescObject->usItem ) && !ValidLaunchable( gpItemPointer->usItem, gpItemDescObject->usItem ) ) )
			{
				// hatch out the attachment panels
				fHatchOutAttachments = TRUE;
			}
		}

		// Display attachments
		for ( cnt = 0; cnt < MAX_ATTACHMENTS; cnt++ )
		{
			if ( gpItemDescObject->usAttachItem[ cnt ] != NOTHING )
			{
        sCenX = (INT16)( gsInvDescX + gItemDescAttachmentsXY[cnt].sX + 5 );
				sCenY = (INT16)( gsInvDescY + gItemDescAttachmentsXY[cnt].sY - 1 );

				INVRenderItem( guiSAVEBUFFER, NULL, gpItemDescObject, sCenX, sCenY, gItemDescAttachmentsXY[cnt].sWidth, gItemDescAttachmentsXY[cnt].sHeight, DIRTYLEVEL2, NULL, (UINT8)(RENDER_ITEM_ATTACHMENT1 + cnt), FALSE, 0 );

				sCenX = sCenX - gItemDescAttachmentsXY[cnt].sBarDx;
				sCenY = sCenY + gItemDescAttachmentsXY[cnt].sBarDy;
				DrawItemUIBarEx( gpItemDescObject, (UINT8)(DRAW_ITEM_STATUS_ATTACHMENT1 + cnt), sCenX, sCenY, ITEM_BAR_WIDTH, ITEM_BAR_HEIGHT, Get16BPPColor( STATUS_BAR ), Get16BPPColor( STATUS_BAR_SHADOW ), TRUE , guiSAVEBUFFER );

			  SetRegionFastHelpText( &(gItemDescAttachmentRegions[ cnt ]), ItemNames[ gpItemDescObject->usAttachItem[ cnt ] ] );
			}
			else
			{
				 SetRegionFastHelpText( &(gItemDescAttachmentRegions[ cnt ]), Message[ STR_ATTACHMENTS ] );
			}
			if (fHatchOutAttachments)
			{
				//UINT32 uiWhichBuffer = (guiCurrentItemDescriptionScreen == MAP_SCREEN ? guiSAVEBUFFER : FRAME_BUFFER);
				DrawHatchOnInventory( guiSAVEBUFFER, (INT16) (gsInvDescX + gItemDescAttachmentsXY[ cnt ].sX), (INT16) (gsInvDescY + gItemDescAttachmentsXY[ cnt ].sY - 2), (INT16)(gItemDescAttachmentsXY[ cnt ].sWidth + gItemDescAttachmentsXY[ cnt ].sBarDx), (INT16) (gItemDescAttachmentsXY[ cnt ].sHeight + 2) );
			}
		}

		if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_GUN )
		{
			// display bullets for ROF
			BltVideoObjectFromIndex( guiSAVEBUFFER, guiBullet, 0, BULLET_SING_X, BULLET_SING_Y);

			if (Weapon[ gpItemDescObject->usItem ].ubShotsPerBurst > 0)
			{
				for ( cnt = 0; cnt < Weapon[ gpItemDescObject->usItem ].ubShotsPerBurst; cnt++ )
				{
					BltVideoObjectFromIndex( guiSAVEBUFFER, guiBullet, 0, BULLET_BURST_X + cnt * (BULLET_WIDTH + 1), BULLET_BURST_Y);
				}
			}

		}

		RestoreExternBackgroundRect( gsInvDescX, gsInvDescY, ITEMDESC_WIDTH, ITEMDESC_HEIGHT );

		// Render font desc
		SetFont( ITEMDESC_FONT );
		SetFontBackground( FONT_MCOLOR_BLACK );
		SetFontForeground( FONT_FCOLOR_WHITE );
		SetFontShadow( ITEMDESC_FONTSHADOW3 );

		// Render name
		// SET CLIPPING RECT FOR FONTS
		#ifdef JA2TESTVERSION
			mprintf( ITEMDESC_NAME_X, ITEMDESC_NAME_Y, L"%ls (%d)", gzItemName, gpItemDescObject->usItem );
		#else
			mprintf( ITEMDESC_NAME_X, ITEMDESC_NAME_Y, L"%ls", gzItemName );
		#endif

		// Render caliber and description

		SetFontForeground( FONT_BLACK );
		SetFontShadow( ITEMDESC_FONTSHADOW2 );

		DisplayWrappedString(ITEMDESC_DESC_START_X, ITEMDESC_DESC_START_Y, ITEMDESC_DESC_WIDTH, 2, ITEMDESC_FONT, FONT_BLACK, gzItemDesc, FONT_MCOLOR_BLACK, LEFT_JUSTIFIED);

		if ( ITEM_PROS_AND_CONS( gpItemDescObject->usItem ) )
		{
			if ( (gpItemDescObject->usItem == ROCKET_RIFLE || gpItemDescObject->usItem == AUTO_ROCKET_RIFLE) && gpItemDescObject->ubImprintID < NO_PROFILE )
			{
				// add name noting imprint
				swprintf( pStr, lengthof(pStr), L"%ls %ls (%ls)", AmmoCaliber[ Weapon[ gpItemDescObject->usItem ].ubCalibre ], WeaponType[ Weapon[ gpItemDescObject->usItem ].ubWeaponType ], gMercProfiles[ gpItemDescObject->ubImprintID ].zNickname );
			}
			else
			{
				swprintf( pStr, lengthof(pStr), L"%ls %ls", AmmoCaliber[ Weapon[ gpItemDescObject->usItem ].ubCalibre ], WeaponType[ Weapon[ gpItemDescObject->usItem ].ubWeaponType ] );
			}

			FindFontRightCoordinates(ITEMDESC_CALIBER_X, ITEMDESC_CALIBER_Y, ITEMDESC_CALIBER_WIDTH, ITEM_STATS_HEIGHT, pStr, ITEMDESC_FONT, &usX, &usY);
			mprintf( usX, usY, pStr );

			SetFontForeground( FONT_MCOLOR_DKWHITE2 );
			SetFontShadow( ITEMDESC_FONTSHADOW3 );
			mprintf( (INT16)ITEMDESC_PROS_START_X, (INT16)ITEMDESC_PROS_START_Y, gzProsLabel );

			sProsConsIndent = __max( StringPixLength( gzProsLabel, ITEMDESC_FONT ), StringPixLength( gzConsLabel, ITEMDESC_FONT ) ) + 10;

			gzItemPros[0] = 0;
			GenerateProsString( gzItemPros, gpItemDescObject, ITEMDESC_DESC_WIDTH - sProsConsIndent - StringPixLength( DOTDOTDOT, ITEMDESC_FONT ) );
			if (gzItemPros[0] != 0)
			{
				SetFontForeground( FONT_BLACK );
				SetFontShadow( ITEMDESC_FONTSHADOW2 );
				DisplayWrappedString(ITEMDESC_PROS_START_X + sProsConsIndent, ITEMDESC_PROS_START_Y, ITEMDESC_DESC_WIDTH - sProsConsIndent, 2, ITEMDESC_FONT, FONT_BLACK, gzItemPros, FONT_MCOLOR_BLACK, LEFT_JUSTIFIED);
			}

			SetFontForeground( FONT_MCOLOR_DKWHITE2 );
			SetFontShadow( ITEMDESC_FONTSHADOW3 );
			mprintf( (INT16)ITEMDESC_CONS_START_X, (INT16)ITEMDESC_CONS_START_Y, gzConsLabel );

			GenerateConsString( gzItemCons, gpItemDescObject, ITEMDESC_DESC_WIDTH - sProsConsIndent - StringPixLength( DOTDOTDOT, ITEMDESC_FONT ) );
			if (gzItemCons[0] != 0)
			{
				SetFontForeground( FONT_BLACK );
				SetFontShadow( ITEMDESC_FONTSHADOW2 );
				DisplayWrappedString(ITEMDESC_CONS_START_X + sProsConsIndent, ITEMDESC_CONS_START_Y, ITEMDESC_DESC_WIDTH - sProsConsIndent, 2, ITEMDESC_FONT, FONT_BLACK, gzItemCons, FONT_MCOLOR_BLACK, LEFT_JUSTIFIED);
			}


		}


		// Get length of string
		uiRightLength=35;

		// Calculate total weight of item and attachments
		fWeight = (float)(CalculateObjectWeight( gpItemDescObject )) / 10;
		if ( !gGameSettings.fOptions[ TOPTION_USE_METRIC_SYSTEM ] )
		{
			fWeight = fWeight * 2.2f;
		}

		if ( fWeight < 0.1 )
		{
			fWeight = (float)0.1;
		}

		// Render, stat  name
		if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_WEAPON )
		{

			SetFont( BLOCKFONT2 );
			SetFontForeground( 6 );
			SetFontShadow( DEFAULT_SHADOW );

			//LABELS
			mprintf(gWeaponStats[0].sX + gsInvDescX, gWeaponStats[0].sY + gsInvDescY, gWeaponStatsDesc[0], GetWeightUnitString());
			if ( Item[ gpItemDescObject->usItem ].usItemClass & (IC_GUN | IC_LAUNCHER ) )
			{
				mprintf( gWeaponStats[ 3 ].sX + gsInvDescX, gWeaponStats[ 3 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 3 ] );
			}
			if ( !(Item[ gpItemDescObject->usItem ].usItemClass & IC_LAUNCHER) && gpItemDescObject->usItem != ROCKET_LAUNCHER )
			{
				mprintf( gWeaponStats[ 4 ].sX + gsInvDescX, gWeaponStats[ 4 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 4 ] );
			}
			mprintf( gWeaponStats[ 5 ].sX + gsInvDescX, gWeaponStats[ 5 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 5 ] );
			if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_GUN )
			{
				mprintf( gWeaponStats[ 7 ].sX + gsInvDescX, gWeaponStats[ 7 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 7 ] );
			}
			mprintf( gWeaponStats[ 1 ].sX + gsInvDescX, gWeaponStats[ 1 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 1 ] );

			if (Weapon[ gpItemDescObject->usItem ].ubShotsPerBurst > 0)
			{
				mprintf( gWeaponStats[ 8 ].sX + gsInvDescX, gWeaponStats[ 8 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 8 ] );
			}

			// Values
			if (fWeight <= (EXCEPTIONAL_WEIGHT / 10))
			{
				SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
			}
			else
			{
				SetFontForeground( 5 );
			}

			//Status
			swprintf( pStr, lengthof(pStr), L"%2d%%", gpItemDescObject->bGunStatus );
			FindFontRightCoordinates(gWeaponStats[1].sX + gsInvDescX + gWeaponStats[1].sValDx, gWeaponStats[1].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
			mprintf(usX, usY, L"%ls", pStr);

			//Wieght
			swprintf( pStr, lengthof(pStr), L"%1.1f", fWeight );
			FindFontRightCoordinates(gWeaponStats[0].sX + gsInvDescX + gWeaponStats[0].sValDx, gWeaponStats[0].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
			mprintf(usX, usY, L"%ls", pStr);

			if ( Item[ gpItemDescObject->usItem ].usItemClass & (IC_GUN | IC_LAUNCHER) )
			{
				if ( GunRange( gpItemDescObject ) >= EXCEPTIONAL_RANGE)
				{
					SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
				}
				else
				{
					SetFontForeground( 5 );
				}

				swprintf( pStr, lengthof(pStr), L"%2d", ( GunRange( gpItemDescObject ) ) / 10 );
				FindFontRightCoordinates(gWeaponStats[3].sX + gsInvDescX + gWeaponStats[3].sValDx, gWeaponStats[3].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
				mprintf( usX, usY, pStr );
			}

			if ( !(Item[ gpItemDescObject->usItem ].usItemClass & IC_LAUNCHER) && gpItemDescObject->usItem != ROCKET_LAUNCHER )
			{

				if (Weapon[ gpItemDescObject->usItem ].ubImpact  >= EXCEPTIONAL_DAMAGE)
				{
					SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
				}
				else
				{
					SetFontForeground( 5 );
				}

				swprintf( pStr, lengthof(pStr), L"%2d", Weapon[ gpItemDescObject->usItem ].ubImpact );
				FindFontRightCoordinates(gWeaponStats[4].sX + gsInvDescX + gWeaponStats[4].sValDx, gWeaponStats[4].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
				mprintf( usX, usY, pStr );
			}

			ubAttackAPs = BaseAPsToShootOrStab( DEFAULT_APS, DEFAULT_AIMSKILL, gpItemDescObject );

			if (ubAttackAPs <= EXCEPTIONAL_AP_COST)
			{
				SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
			}
			else
			{
				SetFontForeground( 5 );
			}

			swprintf( pStr, lengthof(pStr), L"%2d", ubAttackAPs );
			FindFontRightCoordinates(gWeaponStats[5].sX + gsInvDescX + gWeaponStats[5].sValDx, gWeaponStats[5].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
			mprintf( usX, usY, pStr );

			if (Weapon[ gpItemDescObject->usItem ].ubShotsPerBurst > 0)
			{
				if (Weapon[ gpItemDescObject->usItem ].ubShotsPerBurst >= EXCEPTIONAL_BURST_SIZE || gpItemDescObject->usItem == G11)
				{
					SetFontForeground( ITEMDESC_FONTHIGHLIGHT );
				}
				else
				{
					SetFontForeground( 5 );
				}

				swprintf( pStr, lengthof(pStr), L"%2d", ubAttackAPs + CalcAPsToBurst( DEFAULT_APS, gpItemDescObject ) );
				FindFontRightCoordinates(gWeaponStats[6].sX + gsInvDescX + gWeaponStats[6].sValDx, gWeaponStats[6].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
				mprintf( usX, usY, pStr );
			}

		}
		else if ( gpItemDescObject->usItem == MONEY )
		{
			//Labels
			SetFont( BLOCKFONT2 );
			SetFontShadow( DEFAULT_SHADOW );

			SetFontForeground( 6 );

			//Display the 'Seperate text'

			//if the player is removing money from the players account
			if( gfAddingMoneyToMercFromPlayersAccount )
				mprintf( (UINT16)(gMoneyButtonLoc.x + gMoneyButtonOffsets[4].x), (UINT16)(gMoneyButtonLoc.y + gMoneyButtonOffsets[4].y), gzMoneyAmounts[5] );
			else
				mprintf( (UINT16)(gMoneyButtonLoc.x + gMoneyButtonOffsets[4].x), (UINT16)(gMoneyButtonLoc.y + gMoneyButtonOffsets[4].y), gzMoneyAmounts[4] );


			// if the player is taking money from their account
			if( gfAddingMoneyToMercFromPlayersAccount )
			{
				//Display the 'Removing'
				mprintf( gMoneyStats[ 0 ].sX + gsInvDescX, gMoneyStats[ 0 ].sY + gsInvDescY, L"%ls", gMoneyStatsDesc[ MONEY_DESC_PLAYERS ] );
				//Display the 'REmaining'
				mprintf( gMoneyStats[ 2 ].sX + gsInvDescX, gMoneyStats[ 2 ].sY + gsInvDescY, L"%ls", gMoneyStatsDesc[ MONEY_DESC_AMOUNT_2_WITHDRAW ] );
			}
			else
			{
				//Display the 'Removing'
				mprintf( gMoneyStats[ 0 ].sX + gsInvDescX, gMoneyStats[ 0 ].sY + gsInvDescY, L"%ls", gMoneyStatsDesc[ 0 ] );
				//Display the 'REmaining'
				mprintf( gMoneyStats[ 2 ].sX + gsInvDescX, gMoneyStats[ 2 ].sY + gsInvDescY, L"%ls", gMoneyStatsDesc[ 2 ] );
			}

			// Total Amount
			SetFontForeground( FONT_WHITE );
			SPrintMoney(pStr, gRemoveMoney.uiTotalAmount);
			FindFontRightCoordinates(ITEMDESC_NAME_X, ITEMDESC_NAME_Y, 295,ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
			mprintf( usX, usY, pStr );

			SetFontForeground( 6 );

			// if the player is taking money from their account
			if( gfAddingMoneyToMercFromPlayersAccount )
			{
				//Display the 'Amt removing'
				mprintf( gMoneyStats[ 1 ].sX + gsInvDescX, gMoneyStats[ 1 ].sY + gsInvDescY, L"%ls", gMoneyStatsDesc[ MONEY_DESC_BALANCE ] );
				//Display the 'REmaining amount'
				mprintf( gMoneyStats[ 3 ].sX + gsInvDescX, gMoneyStats[ 3 ].sY + gsInvDescY, L"%ls", gMoneyStatsDesc[ MONEY_DESC_TO_WITHDRAW ] );
			}
			else
			{
				//Display the 'Amt removing'
				mprintf( gMoneyStats[ 1 ].sX + gsInvDescX, gMoneyStats[ 1 ].sY + gsInvDescY, L"%ls", gMoneyStatsDesc[ 1 ] );
				//Display the 'REmaining amount'
				mprintf( gMoneyStats[ 3 ].sX + gsInvDescX, gMoneyStats[ 3 ].sY + gsInvDescY, L"%ls", gMoneyStatsDesc[ 3 ] );
			}



			// Values
			SetFontForeground( 5 );

			//Display the total amount of money remaining
			SPrintMoney(pStr, gRemoveMoney.uiMoneyRemaining);
			FindFontRightCoordinates(gMoneyStats[1].sX + gsInvDescX + gMoneyStats[1].sValDx, gMoneyStats[1].sY + gsInvDescY, ITEM_STATS_WIDTH - 3, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
			mprintf( usX, usY, pStr );

			//Display the total amount of money removing
			SPrintMoney(pStr, gRemoveMoney.uiMoneyRemoving);
			FindFontRightCoordinates(gMoneyStats[3].sX + gsInvDescX + gMoneyStats[3].sValDx, gMoneyStats[3].sY + gsInvDescY, ITEM_STATS_WIDTH - 3, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
			mprintf( usX, usY, pStr );

		}
		else if ( Item[ gpItemDescObject->usItem ].usItemClass == IC_MONEY )
		{
			SetFontForeground( FONT_FCOLOR_WHITE );
			SetFontShadow( DEFAULT_SHADOW );
			SPrintMoney(pStr, gpItemDescObject->uiMoneyAmount);
			FindFontRightCoordinates(ITEMDESC_NAME_X, ITEMDESC_NAME_Y, 295, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
			mprintf( usX, usY, pStr );
		}
		else
		{
			//Labels
			SetFont( BLOCKFONT2 );
			SetFontForeground( 6 );
			SetFontShadow( DEFAULT_SHADOW );


			if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_AMMO )
			{
				//Status
				mprintf( gWeaponStats[ 2 ].sX + gsInvDescX, gWeaponStats[ 2 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 2 ] );
			}
			else
			{
				mprintf( gWeaponStats[ 1 ].sX + gsInvDescX, gWeaponStats[ 1 ].sY + gsInvDescY, L"%ls", gWeaponStatsDesc[ 1 ] );
			}

			//Weight
			mprintf(gWeaponStats[0].sX + gsInvDescX, gWeaponStats[0].sY + gsInvDescY, gWeaponStatsDesc[0], GetWeightUnitString());

			// Values
			SetFontForeground( 5 );

			if ( Item[ gpItemDescObject->usItem ].usItemClass & IC_AMMO )
			{
				// Ammo - print amount
				//Status
				swprintf( pStr, lengthof(pStr), L"%d/%d", gpItemDescObject->ubShotsLeft[0], Magazine[ Item[ gpItemDescObject->usItem ].ubClassIndex ].ubMagSize );
				FindFontRightCoordinates(gWeaponStats[2].sX + gsInvDescX + gWeaponStats[2].sValDx, gWeaponStats[2].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
				mprintf(usX, usY, L"%ls", pStr);
			}
			else
			{
				//Status
				swprintf( pStr, lengthof(pStr), L"%2d%%", gpItemDescObject->bStatus[ gubItemDescStatusIndex ] );
				FindFontRightCoordinates(gWeaponStats[1].sX + gsInvDescX + gWeaponStats[1].sValDx, gWeaponStats[1].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
				mprintf(usX, usY, L"%ls", pStr);
			}

			if( ( InKeyRingPopup() == TRUE ) || ( Item[ gpItemDescObject->usItem ].usItemClass & IC_KEY ) )
			{
				SetFontForeground( 6 );

				// build description for keys .. the sector found
				mprintf(gWeaponStats[4].sX + gsInvDescX, gWeaponStats[4].sY + gsInvDescY, sKeyDescriptionStrings[0]);
				mprintf(gWeaponStats[4].sX + gsInvDescX, gWeaponStats[4].sY + gsInvDescY + GetFontHeight(BLOCKFONT) + 2 , sKeyDescriptionStrings[1]);


				SetFontForeground( 5 );
				wchar_t sTempString[128];
				GetShortSectorString(SECTORX(KeyTable[gpItemDescObject->ubKeyID].usSectorFound), SECTORY(KeyTable[gpItemDescObject->ubKeyID].usSectorFound), sTempString, lengthof(sTempString));
				FindFontRightCoordinates(gWeaponStats[4].sX + gsInvDescX, gWeaponStats[4].sY + gsInvDescY, 110, ITEM_STATS_HEIGHT, sTempString, BLOCKFONT2, &usX, &usY);
				mprintf(usX, usY, sTempString);

				swprintf( pStr, lengthof(pStr), L"%d", KeyTable[ gpItemDescObject->ubKeyID ].usDateFound );
				FindFontRightCoordinates(gWeaponStats[4].sX + gsInvDescX, gWeaponStats[4].sY + gsInvDescY + GetFontHeight(BLOCKFONT) + 2, 110, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
				mprintf( usX, usY, pStr );
			}




			//Weight
			swprintf( pStr, lengthof(pStr), L"%1.1f", fWeight );
			FindFontRightCoordinates(gWeaponStats[0].sX + gsInvDescX + gWeaponStats[0].sValDx, gWeaponStats[0].sY + gsInvDescY, ITEM_STATS_WIDTH, ITEM_STATS_HEIGHT, pStr, BLOCKFONT2, &usX, &usY);
			mprintf( usX, usY, pStr );
		}

		SetFontShadow( DEFAULT_SHADOW );

	}

}

void HandleItemDescriptionBox( BOOLEAN *pfDirty )
{
	if ( fItemDescDelete )
	{
		DeleteItemDescriptionBox( );
		fItemDescDelete = FALSE;
		*pfDirty = DIRTYLEVEL2;
	}

}


void DeleteItemDescriptionBox( )
{
	INT32 cnt, cnt2;
	BOOLEAN	fFound, fAllFound;

	if( gfInItemDescBox == FALSE )
	{
		return;
	}

//	DEF:

	//Used in the shopkeeper interface
	if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
	{
		DeleteShopKeeperItemDescBox();
	}

	// check for any AP costs
	if ( ( gTacticalStatus.uiFlags & TURNBASED ) && ( gTacticalStatus.uiFlags & INCOMBAT ) )
	{
		if (gpAttachSoldier)
		{
			// check for change in attachments, starting with removed attachments
			fAllFound = TRUE;
			for ( cnt = 0; cnt < MAX_ATTACHMENTS; cnt++ )
			{
				if ( gusOriginalAttachItem[ cnt ] != NOTHING )
				{
					fFound = FALSE;
					for ( cnt2 = 0; cnt2 < MAX_ATTACHMENTS; cnt2++ )
					{
						if ( (gusOriginalAttachItem[ cnt ] == gpItemDescObject->usAttachItem[ cnt2 ]) && (gpItemDescObject->bAttachStatus[ cnt2 ] == gbOriginalAttachStatus[ cnt ]) )
						{
							fFound = TRUE;
						}
					}
					if (!fFound)
					{
						// charge APs
						fAllFound = FALSE;
						break;
					}
				}
			}

			if (fAllFound)
			{
				// nothing was removed; search for attachment added
				for ( cnt = 0; cnt < MAX_ATTACHMENTS; cnt++ )
				{
					if ( gpItemDescObject->usAttachItem[ cnt ] != NOTHING )
					{
						fFound = FALSE;
						for ( cnt2 = 0; cnt2 < MAX_ATTACHMENTS; cnt2++ )
						{
							if ( (gpItemDescObject->usAttachItem[ cnt ] == gusOriginalAttachItem[ cnt2 ]) && (gbOriginalAttachStatus[ cnt2 ] == gpItemDescObject->bAttachStatus[ cnt ]) )
							{
								fFound = TRUE;
							}
						}
						if (!fFound)
						{
							// charge APs
							fAllFound = FALSE;
							break;
						}
					}
				}
			}

			if (!fAllFound)
			{
				DeductPoints( gpAttachSoldier, AP_RELOAD_GUN, 0 );
			}
		}
	}

	//Remove
	DeleteVideoObjectFromIndex( guiItemDescBox );
  DeleteVideoObjectFromIndex( guiMapItemDescBox );
	DeleteVideoObjectFromIndex( guiBullet );
	// Delete item graphic
	DeleteVideoObjectFromIndex( guiItemGraphic );

	gfInItemDescBox = FALSE;

//	if( guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN  )
	if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
	{
		RemoveButton( giMapInvDescButton );
	}

	// Remove region
	MSYS_RemoveRegion( &gInvDesc);


	if( gpItemDescObject->usItem != MONEY )
	{
		for ( cnt = 0; cnt < MAX_ATTACHMENTS; cnt++ )
		{
			MSYS_RemoveRegion( &gItemDescAttachmentRegions[cnt]);
		}
	}
	else
	{
		UnloadButtonImage( guiMoneyButtonImage );
		UnloadButtonImage( guiMoneyDoneButtonImage );
		for ( cnt = 0; cnt < MAX_ATTACHMENTS; cnt++ )
		{
			RemoveButton( guiMoneyButtonBtn[cnt] );
		}
	}

	if ( ITEM_PROS_AND_CONS( gpItemDescObject->usItem ) )
	{
		MSYS_RemoveRegion( &gProsAndConsRegions[0] );
		MSYS_RemoveRegion( &gProsAndConsRegions[1] );
	}

	if(( ( Item[ gpItemDescObject->usItem ].usItemClass & IC_GUN ) && gpItemDescObject->usItem != ROCKET_LAUNCHER ) )
	{
		// Remove button
		UnloadButtonImage( giItemDescAmmoButtonImages );
		RemoveButton( giItemDescAmmoButton );
	}
//	if(guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN )
	if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
	{
	 fCharacterInfoPanelDirty=TRUE;
	 fMapPanelDirty = TRUE;
	 fTeamPanelDirty = TRUE;
	 fMapScreenBottomDirty = TRUE;
	}

	if( InKeyRingPopup() == TRUE )
	{
		DeleteKeyObject(gpItemDescObject);
		gpItemDescObject = NULL;
		fShowDescriptionFlag = FALSE;
		fInterfacePanelDirty = DIRTYLEVEL2;
		return;
	}

	fShowDescriptionFlag = FALSE;
	fInterfacePanelDirty = DIRTYLEVEL2;

	if( gpItemDescObject->usItem == MONEY )
	{
		//if there is no money remaining
		if( gRemoveMoney.uiMoneyRemaining == 0 && !gfAddingMoneyToMercFromPlayersAccount )
		{
			//get rid of the money in the slot
			memset( gpItemDescObject, 0, sizeof( OBJECTTYPE ) );
			gpItemDescObject = NULL;
		}
	}

	if( gfAddingMoneyToMercFromPlayersAccount )
		gfAddingMoneyToMercFromPlayersAccount = FALSE;

	gfItemDescObjectIsAttachment = FALSE;
}


void InternalBeginItemPointer( SOLDIERTYPE *pSoldier, OBJECTTYPE *pObject, INT8 bHandPos )
{
//	BOOLEAN fOk;

	// If not null return
	if ( gpItemPointer != NULL )
	{
		return;
	}

	// Copy into cursor...
	gItemPointer = *pObject;

	// Dirty interface
	fInterfacePanelDirty = DIRTYLEVEL2;
	gpItemPointer = &gItemPointer;
	gpItemPointerSoldier = pSoldier;
	gbItemPointerSrcSlot = bHandPos;
	gbItemPointerLocateGood = TRUE;

	CheckForDisabledForGiveItem( );

	EnableSMPanelButtons( FALSE, TRUE );

	gfItemPointerDifferentThanDefault = FALSE;

	// re-evaluate repairs
	gfReEvaluateEveryonesNothingToDo = TRUE;
}

void BeginItemPointer( SOLDIERTYPE *pSoldier, UINT8 ubHandPos )
{
	BOOLEAN			fOk;
	OBJECTTYPE	pObject;

	memset( &pObject, 0, sizeof( OBJECTTYPE ) );

	if (_KeyDown( SHIFT ))
	{
		// Remove all from soldier's slot
		fOk = RemoveObjectFromSlot( pSoldier, ubHandPos, &pObject );
	}
	else
	{
		GetObjFrom( &(pSoldier->inv[ubHandPos]), 0, &pObject );
		fOk = (pObject.ubNumberOfObjects == 1);
	}
	if (fOk)
	{
		InternalBeginItemPointer( pSoldier, &pObject, ubHandPos );
	}
}


void BeginKeyRingItemPointer( SOLDIERTYPE *pSoldier, UINT8 ubKeyRingPosition )
{
	BOOLEAN fOk;

	// If not null return
	if ( gpItemPointer != NULL )
	{
		return;
	}

	if (_KeyDown( SHIFT ))
	{
		// Remove all from soldier's slot
		fOk = RemoveKeysFromSlot( pSoldier, ubKeyRingPosition, pSoldier->pKeyRing[ ubKeyRingPosition ].ubNumber, &gItemPointer );
	}
	else
	{
		RemoveKeyFromSlot( pSoldier, ubKeyRingPosition, &gItemPointer );
		fOk = (gItemPointer.ubNumberOfObjects == 1);
	}


	if (fOk)
	{
		// ATE: Look if we are a BLOODIED KNIFE, and change if so, making guy scream...

		// Dirty interface
		fInterfacePanelDirty = DIRTYLEVEL2;
		gpItemPointer = &gItemPointer;
		gpItemPointerSoldier = pSoldier;
		gbItemPointerSrcSlot = ubKeyRingPosition;

		if ( (guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
		{
			guiExternVo = GetInterfaceGraphicForItem( &(Item[ gpItemPointer->usItem ]) );
			gusExternVoSubIndex = Item[ gpItemPointer->usItem ].ubGraphicNum;

			fMapInventoryItem=TRUE;
			MSYS_ChangeRegionCursor( &gMPanelRegion , EXTERN_CURSOR );
			MSYS_SetCurrentCursor( EXTERN_CURSOR );
		}
	}
	else
	{
		//Debug mesg
	}



	gfItemPointerDifferentThanDefault = FALSE;
}

void EndItemPointer( )
{
	if ( gpItemPointer != NULL )
	{
		gpItemPointer = NULL;
		gbItemPointerSrcSlot = NO_SLOT;
		MSYS_ChangeRegionCursor( &gSMPanelRegion , CURSOR_NORMAL );
		MSYS_SetCurrentCursor( CURSOR_NORMAL );

		if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
		{
			memset( &gMoveingItem, 0, sizeof( INVENTORY_IN_SLOT ) );
			SetSkiCursor( CURSOR_NORMAL );
		}
		else
		{
			EnableSMPanelButtons( TRUE , TRUE );
		}

		gbItemPointerLocateGood = FALSE;

		// re-evaluate repairs
		gfReEvaluateEveryonesNothingToDo = TRUE;
	}
}

void DrawItemFreeCursor( )
{
	// Get usIndex and then graphic for item
	guiExternVo = GetInterfaceGraphicForItem( &(Item[ gpItemPointer->usItem ]) );
	gusExternVoSubIndex = Item[ gpItemPointer->usItem ].ubGraphicNum;

	MSYS_ChangeRegionCursor( &gSMPanelRegion , EXTERN_CURSOR );
	MSYS_SetCurrentCursor( EXTERN_CURSOR );
}


static BOOLEAN SoldierCanSeeCatchComing(SOLDIERTYPE* pSoldier, INT16 sSrcGridNo)
{
	return( TRUE );
/*-
	INT32							cnt;
	INT8							bDirection, bTargetDirection;

	bTargetDirection = (INT8)GetDirectionToGridNoFromGridNo( pSoldier->sGridNo, sSrcGridNo );

	// Look 3 directions Clockwise from what we are facing....
	bDirection = pSoldier->bDirection;

	for ( cnt = 0; cnt < 3; cnt++ )
	{
		if ( bDirection == bTargetDirection )
		{
			return( TRUE );
		}

		bDirection = gOneCDirection[ bDirection ];
	}

	// Look 3 directions CounterClockwise from what we are facing....
	bDirection = pSoldier->bDirection;

	for ( cnt = 0; cnt < 3; cnt++ )
	{
		if ( bDirection == bTargetDirection )
		{
			return( TRUE );
		}

		bDirection = gOneCCDirection[ bDirection ];
	}

	// If here, nothing good can happen!
	return( FALSE );
-*/

}

void DrawItemTileCursor( )
{
	UINT16						usMapPos;
	UINT16						usIndex;
	UINT8							ubSoldierID;
	INT16							sAPCost;
	BOOLEAN						fRecalc;
	UINT32						uiCursorFlags;
	INT16							sFinalGridNo;
	UINT32						uiCursorId = CURSOR_ITEM_GOOD_THROW;
	SOLDIERTYPE				*pSoldier;
	BOOLEAN						fGiveItem = FALSE;
	INT16							sActionGridNo;
	UINT8							ubDirection;
	static UINT32			uiOldCursorId = 0;
	static UINT16			usOldMousePos = 0;
	INT16							sEndZ = 0;
	INT16							sDist;
	INT8							bLevel;

	if (GetMouseMapPos( &usMapPos) )
	{
		if ( gfUIFullTargetFound )
		{
			// Force mouse position to guy...
			usMapPos = MercPtrs[ gusUIFullTargetID ]->sGridNo;
		}

		gusCurMousePos = usMapPos;

		if( gusCurMousePos != usOldMousePos )
		{
			gfItemPointerDifferentThanDefault = FALSE;
		}

		// Save old one..
		usOldMousePos = gusCurMousePos;

		// Default to turning adjacent area gridno off....
		gfUIHandleShowMoveGrid = FALSE;

		// If we are over a talkable guy, set flag
		if ( IsValidTalkableNPCFromMouse( &ubSoldierID, TRUE, FALSE, TRUE ) )
		{
			fGiveItem = TRUE;
		}


		// OK, if different than default, change....
		if ( gfItemPointerDifferentThanDefault )
		{
			fGiveItem = !fGiveItem;
		}


		// Get recalc and cursor flags
		fRecalc = GetMouseRecalcAndShowAPFlags( &uiCursorFlags, NULL );

		// OK, if we begin to move, reset the cursor...
		if ( uiCursorFlags & MOUSE_MOVING )
		{
			EndPhysicsTrajectoryUI( );
		}

		// Get Pyth spaces away.....
		sDist = PythSpacesAway( gpItemPointerSoldier->sGridNo, gusCurMousePos );


		// If we are here and we are not selected, select!
		// ATE Design discussion propably needed here...
		if ( gpItemPointerSoldier->ubID != gusSelectedSoldier )
		{
			SelectSoldier( gpItemPointerSoldier->ubID, FALSE, FALSE );
		}

		// ATE: if good for locate, locate to selected soldier....
		if ( gbItemPointerLocateGood )
		{
			gbItemPointerLocateGood = FALSE;
			LocateSoldier( gusSelectedSoldier, FALSE );
		}

		if ( !fGiveItem )
		{
			if ( UIHandleOnMerc( FALSE ) && usMapPos != gpItemPointerSoldier->sGridNo )
			{
				// We are on a guy.. check if they can catch or not....
				if ( gfUIFullTargetFound )
				{
					// Get soldier
					pSoldier = MercPtrs[ gusUIFullTargetID ];

					// Are they on our team?
					// ATE: Can't be an EPC
					if ( pSoldier->bTeam == gbPlayerNum && !AM_AN_EPC( pSoldier ) && !( pSoldier->uiStatusFlags & SOLDIER_VEHICLE ) )
					{
						if ( sDist <= PASSING_ITEM_DISTANCE_OKLIFE )
						{
							// OK, on a valid pass
							gfUIMouseOnValidCatcher = 4;
							gubUIValidCatcherID			= (UINT8)gusUIFullTargetID;
						}
						else
						{
							// Can they see the throw?
							if ( SoldierCanSeeCatchComing( pSoldier, gpItemPointerSoldier->sGridNo ) )
							{
								// OK, set global that this buddy can see catch...
								gfUIMouseOnValidCatcher = TRUE;
								gubUIValidCatcherID			= (UINT8)gusUIFullTargetID;
							}
						}
					}
				}
			}

			// We're going to toss it!
			if ( gTacticalStatus.uiFlags & INCOMBAT )
			{
				gfUIDisplayActionPoints = TRUE;
				gUIDisplayActionPointsOffX = 15;
				gUIDisplayActionPointsOffY = 15;
			}

			// If we are tossing...
			if (  sDist <= 1 && gfUIMouseOnValidCatcher == 0 || gfUIMouseOnValidCatcher == 4 )
			{
				gsCurrentActionPoints = AP_PICKUP_ITEM;
			}
			else
			{
				gsCurrentActionPoints = AP_TOSS_ITEM;
			}

		}
		else
		{
			if ( gfUIFullTargetFound )
			{
				UIHandleOnMerc( FALSE );

				// OK, set global that this buddy can see catch...
				gfUIMouseOnValidCatcher = 2;
				gubUIValidCatcherID			= (UINT8)gusUIFullTargetID;

				// If this is a robot, change to say 'reload'
				if ( MercPtrs[ gusUIFullTargetID ]->uiStatusFlags & SOLDIER_ROBOT )
				{
					gfUIMouseOnValidCatcher = 3;
				}

				if ( !( uiCursorFlags & MOUSE_MOVING ) )
				{
					// Find adjacent gridno...
					sActionGridNo =  FindAdjacentGridEx( gpItemPointerSoldier, gusCurMousePos, &ubDirection, NULL, FALSE, FALSE );
					if ( sActionGridNo == -1 )
					{
						sActionGridNo = gusCurMousePos;
					}

					// Display location...
					gsUIHandleShowMoveGridLocation = sActionGridNo;
					gfUIHandleShowMoveGrid = TRUE;


					// Get AP cost
					if ( MercPtrs[ gusUIFullTargetID ]->uiStatusFlags & SOLDIER_ROBOT )
					{
						sAPCost = GetAPsToReloadRobot( gpItemPointerSoldier, MercPtrs[ gusUIFullTargetID ] );
					}
					else
					{
						sAPCost = GetAPsToGiveItem( gpItemPointerSoldier, sActionGridNo );
					}

					gsCurrentActionPoints = sAPCost;
				}

				// Set value
				if ( gTacticalStatus.uiFlags & INCOMBAT )
				{
					gfUIDisplayActionPoints = TRUE;
					gUIDisplayActionPointsOffX = 15;
					gUIDisplayActionPointsOffY = 15;
				}
			}
		}


		if ( fGiveItem )
		{
			uiCursorId = CURSOR_ITEM_GIVE;
		}
		else
		{
			// How afar away are we?
			if ( sDist <= 1 && gfUIMouseOnValidCatcher == 0 )
			{
				// OK, we want to drop.....

				// Write the word 'drop' on cursor...
				SetIntTileLocationText(pMessageStrings[MSG_DROP]);
			}
			else
			{
				if ( usMapPos == gpItemPointerSoldier->sGridNo )
				{
					EndPhysicsTrajectoryUI( );
				}
        else if ( gfUIMouseOnValidCatcher == 4 )
        {
          // ATE: Don't do if we are passing....
        }
        else
				// ( sDist > PASSING_ITEM_DISTANCE_OKLIFE )
				{
					// Write the word 'drop' on cursor...
					if ( gfUIMouseOnValidCatcher == 0 )
					{
						SetIntTileLocationText(pMessageStrings[MSG_THROW]);
					}

					gfUIHandlePhysicsTrajectory = TRUE;

					if ( fRecalc && usMapPos != gpItemPointerSoldier->sGridNo )
					{
						if ( gfUIMouseOnValidCatcher )
						{
							switch( gAnimControl[ MercPtrs[ gubUIValidCatcherID ]->usAnimState ].ubHeight )
							{
								case ANIM_STAND:

									sEndZ = 150;
									break;

								case ANIM_CROUCH:

									sEndZ = 80;
									break;

								case ANIM_PRONE:

									sEndZ = 10;
									break;
							}

							if ( MercPtrs[ gubUIValidCatcherID ]->bLevel > 0 )
							{
								sEndZ = 0;
							}
						}

						// Calculate chance to throw here.....
						if ( !CalculateLaunchItemChanceToGetThrough( gpItemPointerSoldier, gpItemPointer, usMapPos, (INT8)gsInterfaceLevel, (INT16)( ( gsInterfaceLevel * 256 ) + sEndZ ), &sFinalGridNo, FALSE, &bLevel, TRUE ) )
						{
							gfBadThrowItemCTGH = TRUE;
						}
						else
						{
							gfBadThrowItemCTGH = FALSE;
						}

						BeginPhysicsTrajectoryUI( sFinalGridNo, bLevel, gfBadThrowItemCTGH );
					}
				}

				if ( gfBadThrowItemCTGH )
				{
					uiCursorId = CURSOR_ITEM_BAD_THROW;
				}
			}
		}

		//Erase any cursor in viewport
		//MSYS_ChangeRegionCursor( &gViewportRegion , VIDEO_NO_CURSOR );

		// Get tile graphic fro item
		usIndex = GetTileGraphicForItem( &(Item[ gpItemPointer->usItem ]) );

		// ONly load if different....
		if ( usIndex != gusItemPointer || uiOldCursorId != uiCursorId )
		{
			// OK, Tile database gives me subregion and video object to use...
			SetExternVOData( uiCursorId, gTileDatabase[ usIndex ].hTileSurface, gTileDatabase[ usIndex ].usRegionIndex );
			gusItemPointer = usIndex;
			uiOldCursorId = uiCursorId;
		}


		MSYS_ChangeRegionCursor( &gViewportRegion , (UINT16)uiCursorId );

	}
}


static BOOLEAN IsValidAmmoToReloadRobot(SOLDIERTYPE* pSoldier, OBJECTTYPE* pObject)
{
	if ( !CompatibleAmmoForGun( pObject, &( pSoldier->inv[ HANDPOS ] ) ) )
	{
		// Build string...
		ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[ ROBOT_NEEDS_GIVEN_CALIBER_STR ], AmmoCaliber[ Weapon[ pSoldier->inv[ HANDPOS ].usItem ].ubCalibre ] );

		return( FALSE );
	}

	return( TRUE );
}


BOOLEAN HandleItemPointerClick( UINT16 usMapPos )
{
	// Determine what to do
	UINT8 ubDirection;
	UINT8	ubSoldierID;
	UINT16	  usItem;
	INT16			sAPCost;
	SOLDIERTYPE		*pSoldier=NULL;
	UINT8			ubThrowActionCode=0;
	UINT32		uiThrowActionData=0;
	INT16			sEndZ = 0;
	BOOLEAN		fGiveItem = FALSE;
	OBJECTTYPE TempObject;
	INT16			sGridNo;
	INT16			sDist;
	INT16			sDistVisible;


	if ( SelectedGuyInBusyAnimation( ) )
	{
		return( FALSE );
	}

	if ( giUIMessageOverlay != -1 )
	{
		EndUIMessage( );
		return( FALSE );
	}

	// Don't allow if our soldier is a # of things...
	if ( AM_AN_EPC( gpItemPointerSoldier ) || gpItemPointerSoldier->bLife < OKLIFE || gpItemPointerSoldier->bOverTerrainType == DEEP_WATER )
	{
		return( FALSE );
	}

	// This implies we have no path....
	if ( gsCurrentActionPoints == 0 )
	{
		ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[ NO_PATH ] );
		return( FALSE );
	}


	if ( gfUIFullTargetFound )
	{
		// Force mouse position to guy...
		usMapPos = MercPtrs[ gusUIFullTargetID ]->sGridNo;

		if ( gAnimControl[ MercPtrs[ gusUIFullTargetID ]->usAnimState ].uiFlags & ANIM_MOVING )
		{
			return( FALSE );
		}

	}

	// Check if we have APs....
	if ( !EnoughPoints( gpItemPointerSoldier, gsCurrentActionPoints, 0, TRUE ) )
	{
		if ( gfDontChargeAPsToPickup && gsCurrentActionPoints == AP_PICKUP_ITEM )
		{

		}
		else
		{
			return( FALSE );
		}
	}

	// SEE IF WE ARE OVER A TALKABLE GUY!
	if ( IsValidTalkableNPCFromMouse( &ubSoldierID, TRUE, FALSE, TRUE ) )
	{
		fGiveItem = TRUE;
	}

	// OK, if different than default, change....
	if ( gfItemPointerDifferentThanDefault )
	{
		fGiveItem = !fGiveItem;
	}


	// Get Pyth spaces away.....
	sDist = PythSpacesAway( gpItemPointerSoldier->sGridNo, gusCurMousePos );


	if ( fGiveItem )
	{
		usItem = gpItemPointer->usItem;

		// If the target is a robot,
		if ( MercPtrs[ ubSoldierID ]->uiStatusFlags & SOLDIER_ROBOT )
		{
			// Charge APs to reload robot!
			sAPCost = GetAPsToReloadRobot( gpItemPointerSoldier,  MercPtrs[ ubSoldierID ] );
		}
		else
		{
			// Calculate action point costs!
			sAPCost = GetAPsToGiveItem( gpItemPointerSoldier, usMapPos );
		}

		// Place it back in our hands!

		TempObject = *gpItemPointer;

		if ( gbItemPointerSrcSlot != NO_SLOT )
		{
			PlaceObject( gpItemPointerSoldier, gbItemPointerSrcSlot, gpItemPointer );
			fInterfacePanelDirty = DIRTYLEVEL2;
		}
/*
		//if the user just clicked on an arms dealer
		if( IsMercADealer( MercPtrs[ ubSoldierID ]->ubProfile ) )
		{
			if ( EnoughPoints( gpItemPointerSoldier, sAPCost, 0, TRUE ) )
			{
				//Enter the shopkeeper interface
				EnterShopKeeperInterfaceScreen( MercPtrs[ ubSoldierID ]->ubProfile );

				EndItemPointer( );
			}

			return( TRUE );
		}
*/

		if ( EnoughPoints( gpItemPointerSoldier, sAPCost, 0, TRUE ) )
		{
			// If we are a robot, check if this is proper item to reload!
			if ( MercPtrs[ ubSoldierID ]->uiStatusFlags & SOLDIER_ROBOT )
			{
				// Check if we can reload robot....
				if ( IsValidAmmoToReloadRobot( MercPtrs[ ubSoldierID ], &TempObject ) )
				{
					 INT16	sActionGridNo;
					 UINT8	ubDirection;
					 INT16	sAdjustedGridNo;

					 // Walk up to him and reload!
					 // See if we can get there to stab
					 sActionGridNo =  FindAdjacentGridEx( gpItemPointerSoldier, MercPtrs[ ubSoldierID ]->sGridNo, &ubDirection, &sAdjustedGridNo, TRUE, FALSE );

					 if ( sActionGridNo != -1 && gbItemPointerSrcSlot != NO_SLOT )
					 {
							// Make a temp object for ammo...
							gpItemPointerSoldier->pTempObject	 = MemAlloc( sizeof( OBJECTTYPE ) );
							*gpItemPointerSoldier->pTempObject = TempObject;

							// Remove from soldier's inv...
							RemoveObjs( &( gpItemPointerSoldier->inv[ gbItemPointerSrcSlot ] ), 1 );

							gpItemPointerSoldier->sPendingActionData2  = sAdjustedGridNo;
							gpItemPointerSoldier->uiPendingActionData1 = gbItemPointerSrcSlot;
							gpItemPointerSoldier->bPendingActionData3  = ubDirection;
							gpItemPointerSoldier->ubPendingActionAnimCount = 0;

							// CHECK IF WE ARE AT THIS GRIDNO NOW
							if ( gpItemPointerSoldier->sGridNo != sActionGridNo )
							{
								// SEND PENDING ACTION
								gpItemPointerSoldier->ubPendingAction = MERC_RELOADROBOT;

								// WALK UP TO DEST FIRST
								EVENT_InternalGetNewSoldierPath( gpItemPointerSoldier, sActionGridNo, gpItemPointerSoldier->usUIMovementMode, FALSE, FALSE );
							}
							else
							{
								EVENT_SoldierBeginReloadRobot( gpItemPointerSoldier, sAdjustedGridNo, ubDirection, gbItemPointerSrcSlot );
							}

							// OK, set UI
							SetUIBusy( gpItemPointerSoldier->ubID );
					 }

				}

				gfDontChargeAPsToPickup = FALSE;
				EndItemPointer( );
			}
			else
			{
				//if (gbItemPointerSrcSlot != NO_SLOT )
				{
					// Give guy this item.....
					SoldierGiveItem( gpItemPointerSoldier, MercPtrs[ ubSoldierID ], &TempObject, gbItemPointerSrcSlot );

					gfDontChargeAPsToPickup = FALSE;
					EndItemPointer( );

					// If we are giving it to somebody not on our team....
					if ( MercPtrs[ ubSoldierID ]->ubProfile < FIRST_RPC || RPC_RECRUITED( MercPtrs[ ubSoldierID ] ) )
					{

					}
					else
					{
						SetEngagedInConvFromPCAction( gpItemPointerSoldier );
					}
				}
			}
		}

		return( TRUE );
	}

	// CHECK IF WE ARE NOT ON THE SAME GRIDNO
	if ( sDist <= 1 && !( gfUIFullTargetFound && gusUIFullTargetID != gpItemPointerSoldier->ubID ) )
	{
		// Check some things here....
		// 1 ) are we at the exact gridno that we stand on?
		if ( usMapPos == gpItemPointerSoldier->sGridNo )
		{
			// Drop
			if ( !gfDontChargeAPsToPickup )
			{
				// Deduct points
				DeductPoints( gpItemPointerSoldier, AP_PICKUP_ITEM, 0 );
			}

			SoldierDropItem( gpItemPointerSoldier, gpItemPointer );
		}
		else
		{
			// Try to drop in an adjacent area....
			// 1 ) is this not a good OK destination
			// this will sound strange, but this is OK......
			if ( !NewOKDestination( gpItemPointerSoldier, usMapPos, FALSE, gpItemPointerSoldier->bLevel ) || FindBestPath( gpItemPointerSoldier, usMapPos, gpItemPointerSoldier->bLevel, WALKING, NO_COPYROUTE, 0 ) == 1 )
			{
				// Drop
				if ( !gfDontChargeAPsToPickup )
				{
					// Deduct points
					DeductPoints( gpItemPointerSoldier, AP_PICKUP_ITEM, 0 );
				}

				// Play animation....
				// Don't show animation of dropping item, if we are not standing



				switch ( gAnimControl[ gpItemPointerSoldier->usAnimState ].ubHeight )
				{
					case ANIM_STAND:

						gpItemPointerSoldier->pTempObject = MemAlloc( sizeof( OBJECTTYPE ) );
						if (gpItemPointerSoldier->pTempObject != NULL)
						{
							*gpItemPointerSoldier->pTempObject = *gpItemPointer;
							gpItemPointerSoldier->sPendingActionData2 = usMapPos;

	 						// Turn towards.....gridno
							EVENT_SetSoldierDesiredDirection( gpItemPointerSoldier, (INT8)GetDirectionFromGridNo( usMapPos, gpItemPointerSoldier ) );

							EVENT_InitNewSoldierAnim( gpItemPointerSoldier, DROP_ADJACENT_OBJECT, 0 , FALSE );
						}
						break;

					case ANIM_CROUCH:
					case ANIM_PRONE:

						AddItemToPool( usMapPos, gpItemPointer, 1, gpItemPointerSoldier->bLevel, 0 , -1 );
						NotifySoldiersToLookforItems( );
						break;
				}
			}
			else
			{
				// Drop in place...
				if ( !gfDontChargeAPsToPickup )
				{
					// Deduct points
					DeductPoints( gpItemPointerSoldier, AP_PICKUP_ITEM, 0 );
				}

				SoldierDropItem( gpItemPointerSoldier, gpItemPointer );
			}
		}
	}
	else
	{
		sGridNo = usMapPos;

		if ( sDist <= PASSING_ITEM_DISTANCE_OKLIFE && gfUIFullTargetFound && MercPtrs[ gusUIFullTargetID ]->bTeam == gbPlayerNum && !AM_AN_EPC( MercPtrs[ gusUIFullTargetID ] ) && !( MercPtrs[ gusUIFullTargetID ]->uiStatusFlags & SOLDIER_VEHICLE ) )
		{
			// OK, do the transfer...
			{
				pSoldier = MercPtrs[ gusUIFullTargetID ];

				{
					// Change to inventory....
					//gfSwitchPanel = TRUE;
					//gbNewPanel = SM_PANEL;
					//gubNewPanelParam = (UINT8)pSoldier->ubID;
					if ( !EnoughPoints( pSoldier, 3, 0, TRUE ) ||
							 !EnoughPoints( gpItemPointerSoldier, 3, 0, TRUE ) )
					{
						return( FALSE );
					}

					sDistVisible = DistanceVisible( pSoldier, DIRECTION_IRRELEVANT, DIRECTION_IRRELEVANT, gpItemPointerSoldier->sGridNo, gpItemPointerSoldier->bLevel );

					// Check LOS....
					if ( !SoldierTo3DLocationLineOfSightTest( pSoldier, gpItemPointerSoldier->sGridNo,  gpItemPointerSoldier->bLevel, 3, (UINT8) sDistVisible, TRUE ) )
					{
						return( FALSE );
					}

					// Charge AP values...
					DeductPoints( pSoldier, 3, 0 );
					DeductPoints( gpItemPointerSoldier, 3, 0 );

					usItem = gpItemPointer->usItem;

					// try to auto place object....
					if ( AutoPlaceObject( pSoldier, gpItemPointer, TRUE ) )
					{
						ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[ MSG_ITEM_PASSED_TO_MERC ], ShortItemNames[ usItem ], pSoldier->name );

						// Check if it's the same now!
						if ( gpItemPointer->ubNumberOfObjects == 0 )
						{
							EndItemPointer( );
						}

	    			// OK, make guys turn towards each other and do animation...
			  		{
						  UINT8	ubFacingDirection;

						  // Get direction to face.....
						  ubFacingDirection = (UINT8)GetDirectionFromGridNo( gpItemPointerSoldier->sGridNo, pSoldier );

						  // Stop merc first....
						  EVENT_StopMerc( pSoldier, pSoldier->sGridNo, pSoldier->bDirection );

						  // If we are standing only...
						  if ( gAnimControl[ pSoldier->usAnimState ].ubEndHeight == ANIM_STAND && !MercInWater( pSoldier ) )
						  {
							  // Turn to face, then do animation....
							  EVENT_SetSoldierDesiredDirection( pSoldier, ubFacingDirection );
							  pSoldier->fTurningUntilDone	 = TRUE;
							  pSoldier->usPendingAnimation = PASS_OBJECT;
              }

						  if ( gAnimControl[ gpItemPointerSoldier->usAnimState ].ubEndHeight == ANIM_STAND && !MercInWater( gpItemPointerSoldier ) )
						  {
							  EVENT_SetSoldierDesiredDirection( gpItemPointerSoldier, gOppositeDirection[ ubFacingDirection ] );
							  gpItemPointerSoldier->fTurningUntilDone	 = TRUE;
							  gpItemPointerSoldier->usPendingAnimation = PASS_OBJECT;
						  }
					  }

						return( TRUE );
					}
					else
					{
						ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_INTERFACE, pMessageStrings[ MSG_NO_ROOM_TO_PASS_ITEM ], ShortItemNames[ usItem ], pSoldier->name );
  					return( FALSE );
					}
				}
			}
		}
		else
		{
			// CHECK FOR VALID CTGH
			if ( gfBadThrowItemCTGH )
			{
				ScreenMsg( FONT_MCOLOR_LTYELLOW, MSG_UI_FEEDBACK, TacticalStr[ CANNOT_THROW_TO_DEST_STR ] );
				return( FALSE );
			}

			// Deduct points
			//DeductPoints( gpItemPointerSoldier, AP_TOSS_ITEM, 0 );
			gpItemPointerSoldier->fDontChargeTurningAPs = TRUE;
			// Will be dome later....

			ubThrowActionCode = NO_THROW_ACTION;

			// OK, CHECK FOR VALID THROW/CATCH
			// IF OVER OUR GUY...
			if ( gfUIFullTargetFound )
			{
				pSoldier = MercPtrs[ gusUIFullTargetID ];

				if ( pSoldier->bTeam == gbPlayerNum && pSoldier->bLife >= OKLIFE && !AM_AN_EPC( pSoldier ) && !( pSoldier->uiStatusFlags & SOLDIER_VEHICLE ) )
				{
					// OK, on our team,

					// How's our direction?
					if ( SoldierCanSeeCatchComing( pSoldier, gpItemPointerSoldier->sGridNo ) )
					{
						// Setup as being the catch target
						ubThrowActionCode = THROW_TARGET_MERC_CATCH;
						uiThrowActionData = pSoldier->ubID;

						sGridNo = pSoldier->sGridNo;

						switch( gAnimControl[ pSoldier->usAnimState ].ubHeight )
						{
								case ANIM_STAND:

									sEndZ = 150;
									break;

								case ANIM_CROUCH:

									sEndZ = 80;
									break;

								case ANIM_PRONE:

									sEndZ = 10;
									break;
						}

						if ( pSoldier->bLevel > 0 )
						{
							sEndZ = 0;
						}

						// Get direction
						ubDirection = (UINT8)GetDirectionFromGridNo( gpItemPointerSoldier->sGridNo, pSoldier );

						// ATE: Goto stationary...
						SoldierGotoStationaryStance( pSoldier );

						// Set direction to turn...
						EVENT_SetSoldierDesiredDirection( pSoldier, ubDirection );

					}
				}
			}


			// CHANGE DIRECTION AT LEAST
			ubDirection = (UINT8)GetDirectionFromGridNo( sGridNo, gpItemPointerSoldier );
			EVENT_SetSoldierDesiredDirection( gpItemPointerSoldier, ubDirection );
			gpItemPointerSoldier->fTurningUntilDone = TRUE;

			// Increment attacker count...
			gTacticalStatus.ubAttackBusyCount++;
			DebugMsg( TOPIC_JA2, DBG_LEVEL_3, String("INcremtning ABC: Throw item to %d", gTacticalStatus.ubAttackBusyCount) );


			// Given our gridno, throw grenate!
			CalculateLaunchItemParamsForThrow( gpItemPointerSoldier, sGridNo, gpItemPointerSoldier->bLevel, (INT16)( ( gsInterfaceLevel * 256 ) + sEndZ ), gpItemPointer, 0, ubThrowActionCode, uiThrowActionData );

			// OK, goto throw animation
			HandleSoldierThrowItem( gpItemPointerSoldier, usMapPos );
		}
	}

	gfDontChargeAPsToPickup = FALSE;
	EndItemPointer( );


	return( TRUE );
}


static BOOLEAN ItemCursorInLobRange(UINT16 usMapPos)
{
	// Draw item depending on distance from buddy
	if ( GetRangeFromGridNoDiff( usMapPos, gpItemPointerSoldier->sGridNo ) > MIN_LOB_RANGE )
	{
		return( FALSE );
	}
	else
	{
		return( TRUE );
	}
}




BOOLEAN InItemStackPopup( )
{
	return( gfInItemStackPopup );
}


BOOLEAN InKeyRingPopup( )
{
	return( gfInKeyRingPopup );
}


static void ItemPopupFullRegionCallback(MOUSE_REGION* pRegion, INT32 iReason);
static void ItemPopupRegionCallback(MOUSE_REGION* pRegion, INT32 iReason);


BOOLEAN InitItemStackPopup( SOLDIERTYPE *pSoldier, UINT8 ubPosition, INT16 sInvX, INT16 sInvY, INT16 sInvWidth, INT16 sInvHeight )
{
	SGPRect					aRect;
	UINT8						ubLimit;
	INT32						cnt;
	UINT16				 usPopupWidth;

	// Set some globals
	gsItemPopupInvX					= sInvX;
	gsItemPopupInvY					= sInvY;
	gsItemPopupInvWidth			= sInvWidth;
	gsItemPopupInvHeight		= sInvHeight;


	gpItemPopupSoldier = pSoldier;


	// Determine # of items
	gpItemPopupObject = &(pSoldier->inv[ ubPosition ] );
	ubLimit = ItemSlotLimit( gpItemPopupObject->usItem, ubPosition );

	// Return false if #objects not >1
	if ( ubLimit <1 )
	{
		return( FALSE );
	}

	if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
	{
    if ( ubLimit > 6 )
    {
      ubLimit = 6;
    }
  }

	// Load graphics
	guiItemPopupBoxes = AddVideoObjectFromFile("INTERFACE/extra_inventory.STI");
	CHECKF(guiItemPopupBoxes != NO_VOBJECT);

	// Get size
	const ETRLEObject* pTrav = GetVideoObjectETRLESubregionProperties(guiItemPopupBoxes, 0);
	usPopupWidth = pTrav->usWidth;

	// Get Width, Height
	INT16 gsItemPopupWidth = ubLimit * usPopupWidth;
	INT16 gsItemPopupHeight = pTrav->usHeight;
	gubNumItemPopups = ubLimit;

	// Calculate X,Y, first center
	const INV_REGIONS* reg = &gSMInvData[ubPosition];
	INT16 sCenX = reg->sX - (gsItemPopupWidth / 2 + reg->sWidth / 2);
	INT16 sCenY	= reg->sY;

	// Limit it to window for item desc
	if ( sCenX < gsItemPopupInvX )
	{
		sCenX = gsItemPopupInvX;
	}
	if ( ( sCenX + gsItemPopupWidth ) > ( gsItemPopupInvX + gsItemPopupInvWidth ) )
	{
		sCenX = gsItemPopupInvX;
	}

  // Cap it at 0....
  if ( sCenX < 0 )
  {
    sCenX = 0;
  }

	// Set
	gsItemPopupX	= sCenX;
	gsItemPopupY	= sCenY;

	for ( cnt = 0; cnt < gubNumItemPopups; cnt++ )
	{
		// Build a mouse region here that is over any others.....
		MSYS_DefineRegion(&gItemPopupRegions[cnt], sCenX + cnt * usPopupWidth, sCenY, sCenX + (cnt + 1) * usPopupWidth, sCenY + gsItemPopupHeight, MSYS_PRIORITY_HIGHEST, MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemPopupRegionCallback);
		MSYS_SetRegionUserData( &gItemPopupRegions[cnt], 0, cnt );

		//OK, for each item, set dirty text if applicable!
		SetRegionFastHelpText( &(gItemPopupRegions[ cnt ]), ItemNames[ pSoldier->inv[ ubPosition ].usItem ] );
		gfItemPopupRegionCallbackEndFix = FALSE;
	}


	// Build a mouse region here that is over any others.....
	MSYS_DefineRegion(&gItemPopupRegion, gsItemPopupInvX, gsItemPopupInvY, gsItemPopupInvX + gsItemPopupInvWidth, gsItemPopupInvY + gsItemPopupInvHeight, MSYS_PRIORITY_HIGH, MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemPopupFullRegionCallback);


	//Disable all faces
	SetAllAutoFacesInactive( );


	fInterfacePanelDirty = DIRTYLEVEL2;

	//guiTacticalInterfaceFlags |= INTERFACE_NORENDERBUTTONS;


	gfInItemStackPopup = TRUE;

//	if ( !(guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
	if( guiCurrentItemDescriptionScreen != MAP_SCREEN )
	{
		EnableSMPanelButtons( FALSE, FALSE );
	}

	//Reserict mouse cursor to panel
	aRect.iTop = sInvY;
	aRect.iLeft = sInvX;
	aRect.iBottom = sInvY + sInvHeight;
	aRect.iRight = sInvX + sInvWidth;

	RestrictMouseCursor( &aRect );

	return( TRUE );
}


static void DeleteItemStackPopup(void);


static void EndItemStackPopupWithItemInHand(void)
{
	if ( gpItemPointer != NULL )
	{
		DeleteItemStackPopup( );
	}
}

void RenderItemStackPopup( BOOLEAN fFullRender )
{
	if ( gfInItemStackPopup )
	{

		//Disable all faces
		SetAllAutoFacesInactive( );

		// Shadow Area
		if ( fFullRender )
		{
			ShadowVideoSurfaceRect( FRAME_BUFFER, gsItemPopupInvX, gsItemPopupInvY, gsItemPopupInvX + gsItemPopupInvWidth , gsItemPopupInvY + gsItemPopupInvHeight  );
		}

	}
	// TAKE A LOOK AT THE VIDEO OBJECT SIZE ( ONE OF TWO SIZES ) AND CENTER!
	const ETRLEObject* pTrav = GetVideoObjectETRLESubregionProperties(guiItemPopupBoxes, 0);
	UINT32 usWidth = pTrav->usWidth;

	for (UINT32 cnt = 0; cnt < gubNumItemPopups; cnt++)
	{
		BltVideoObjectFromIndex( FRAME_BUFFER, guiItemPopupBoxes, 0, gsItemPopupX + ( cnt * usWidth ), gsItemPopupY);

		if ( cnt < gpItemPopupObject->ubNumberOfObjects )
		{
			INT16 sX = gsItemPopupX + cnt * usWidth + 11;
			INT16 sY = gsItemPopupY + 3;

			INVRenderItem( FRAME_BUFFER, NULL, gpItemPopupObject, sX, sY, 29, 23, DIRTYLEVEL2, NULL, (UINT8)RENDER_ITEM_NOSTATUS, FALSE, 0 );

			// Do status bar here...
			INT16 sNewX = gsItemPopupX + cnt * usWidth + 7;
			INT16 sNewY = gsItemPopupY + INV_BAR_DY + 3;
			DrawItemUIBarEx( gpItemPopupObject, (UINT8)cnt, sNewX, sNewY, ITEM_BAR_WIDTH, ITEM_BAR_HEIGHT, 	Get16BPPColor( STATUS_BAR ), Get16BPPColor( STATUS_BAR_SHADOW ), TRUE , FRAME_BUFFER );
		}
	}

	//RestoreExternBackgroundRect( gsItemPopupInvX, gsItemPopupInvY, gsItemPopupInvWidth, gsItemPopupInvHeight );
	InvalidateRegion( gsItemPopupInvX, gsItemPopupInvY, gsItemPopupInvX + gsItemPopupInvWidth, gsItemPopupInvY + gsItemPopupInvHeight );

}


static void DeleteItemStackPopup(void)
{
	INT32			cnt;

	//Remove
	DeleteVideoObjectFromIndex( guiItemPopupBoxes );

	MSYS_RemoveRegion( &gItemPopupRegion);


	gfInItemStackPopup = FALSE;

	for ( cnt = 0; cnt < gubNumItemPopups; cnt++ )
	{
		MSYS_RemoveRegion( &gItemPopupRegions[cnt]);
	}


	fInterfacePanelDirty = DIRTYLEVEL2;

	//guiTacticalInterfaceFlags &= (~INTERFACE_NORENDERBUTTONS);

//	if ( !(guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
	if( guiCurrentItemDescriptionScreen != MAP_SCREEN )
	{
		EnableSMPanelButtons( TRUE, FALSE );
	}

	FreeMouseCursor( );

}


BOOLEAN InitKeyRingPopup( SOLDIERTYPE *pSoldier, INT16 sInvX, INT16 sInvY, INT16 sInvWidth, INT16 sInvHeight )
{
	SGPRect			aRect;
	INT16				sKeyRingItemWidth = 0;
	INT16				sOffSetY = 0, sOffSetX = 0;

	if( guiCurrentScreen == MAP_SCREEN )
	{
		gsKeyRingPopupInvX				= 0;
		sKeyRingItemWidth						= MAP_KEY_RING_ROW_WIDTH;
		sOffSetX = 40;
		sOffSetY = 15;
	}
	else
	{
		// Set some globals
		gsKeyRingPopupInvX					= sInvX + TACTICAL_INVENTORY_KEYRING_GRAPHIC_OFFSET_X;
		sKeyRingItemWidth						= KEY_RING_ROW_WIDTH;
		sOffSetY = 8;
	}

	gsKeyRingPopupInvY					= sInvY;
	gsKeyRingPopupInvWidth			= sInvWidth;
	gsKeyRingPopupInvHeight		= sInvHeight;


	gpItemPopupSoldier = pSoldier;

	// Load graphics
	guiItemPopupBoxes = AddVideoObjectFromFile("INTERFACE/extra_inventory.STI");
	CHECKF(guiItemPopupBoxes != NO_VOBJECT);

	// Get size
	const ETRLEObject* pTrav = GetVideoObjectETRLESubregionProperties(guiItemPopupBoxes, 0);
	UINT16 usPopupWidth = pTrav->usWidth;
	UINT16 usPopupHeight = pTrav->usHeight;

	for (INT32 cnt = 0; cnt < NUMBER_KEYS_ON_KEYRING; cnt++)
	{
		// Build a mouse region here that is over any others.....
		MSYS_DefineRegion(&gKeyRingRegions[cnt],
			gsKeyRingPopupInvX + (cnt % sKeyRingItemWidth      * usPopupWidth)  + sOffSetX, // top left
			sInvY              + (cnt / sKeyRingItemWidth      * usPopupHeight) + sOffSetY, // top right
			gsKeyRingPopupInvX + (cnt % sKeyRingItemWidth + 1) * usPopupWidth   + sOffSetX, // bottom left
			sInvY              + (cnt / sKeyRingItemWidth + 1) * usPopupHeight  + sOffSetY, // bottom right
			MSYS_PRIORITY_HIGHEST,
			MSYS_NO_CURSOR, MSYS_NO_CALLBACK, KeyRingSlotInvClickCallback
		);
		MSYS_SetRegionUserData( &gKeyRingRegions[cnt], 0, cnt );
		//gfItemPopupRegionCallbackEndFix = FALSE;
	}


	// Build a mouse region here that is over any others.....
	MSYS_DefineRegion(&gItemPopupRegion, sInvX, sInvY, sInvX + sInvWidth, sInvY + sInvHeight, MSYS_PRIORITY_HIGH, MSYS_NO_CURSOR, MSYS_NO_CALLBACK, ItemPopupFullRegionCallback);


	//Disable all faces
	SetAllAutoFacesInactive( );


	fInterfacePanelDirty = DIRTYLEVEL2;

	//guiTacticalInterfaceFlags |= INTERFACE_NORENDERBUTTONS;


//	if ( !(guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
	if( guiCurrentItemDescriptionScreen != MAP_SCREEN )
	{
		EnableSMPanelButtons( FALSE , FALSE );
	}

	gfInKeyRingPopup = TRUE;

	//Reserict mouse cursor to panel
	aRect.iTop = sInvY;
	aRect.iLeft = sInvX;
	aRect.iBottom = sInvY + sInvHeight;
	aRect.iRight = sInvX + sInvWidth;

	RestrictMouseCursor( &aRect );

	return( TRUE );
}


void RenderKeyRingPopup( BOOLEAN fFullRender )
{
	UINT32								cnt;
	OBJECTTYPE						pObject;
	INT16 sKeyRingItemWidth = 0;
	INT16 sOffSetY = 0, sOffSetX = 0;

	if( guiCurrentScreen != MAP_SCREEN )
	{
		sOffSetY = 8;
	}
	else
	{
		sOffSetX = 40;
		sOffSetY = 15;
	}

	if ( gfInKeyRingPopup )
	{

		//Disable all faces
		SetAllAutoFacesInactive( );

		// Shadow Area
		if ( fFullRender )
		{
			ShadowVideoSurfaceRect( FRAME_BUFFER, 0, gsKeyRingPopupInvY, gsKeyRingPopupInvX + gsKeyRingPopupInvWidth , gsKeyRingPopupInvY + gsKeyRingPopupInvHeight );
		}

	}

	memset( &pObject, 0, sizeof( OBJECTTYPE ) );

	pObject.usItem = KEY_1;
	pObject.bStatus[ 0 ] = 100;

	// TAKE A LOOK AT THE VIDEO OBJECT SIZE ( ONE OF TWO SIZES ) AND CENTER!
	const ETRLEObject* pTrav = GetVideoObjectETRLESubregionProperties(guiItemPopupBoxes, 0);
	UINT32 usHeight = pTrav->usHeight;
	UINT32 usWidth  = pTrav->usWidth;

	if( guiCurrentScreen == MAP_SCREEN )
	{
		sKeyRingItemWidth						= MAP_KEY_RING_ROW_WIDTH;
	}
	else
	{
		// Set some globals
		sKeyRingItemWidth						= KEY_RING_ROW_WIDTH;
	}

	for ( cnt = 0; cnt < NUMBER_KEYS_ON_KEYRING; cnt++ )
	{
		BltVideoObjectFromIndex( FRAME_BUFFER, guiItemPopupBoxes, 0, (INT16)(gsKeyRingPopupInvX + ( cnt % sKeyRingItemWidth * usWidth ) + sOffSetX ), ( INT16 )( gsKeyRingPopupInvY + sOffSetY + ( cnt / sKeyRingItemWidth * usHeight ) ));

		// will want to draw key here.. if there is one
		if( ( gpItemPopupSoldier->pKeyRing[ cnt ].ubKeyID != INVALID_KEY_NUMBER ) && ( gpItemPopupSoldier->pKeyRing[ cnt ].ubNumber > 0 ) )
		{
			pObject.ubNumberOfObjects = gpItemPopupSoldier->pKeyRing[ cnt ].ubNumber;

			// show 100% status for each
			DrawItemUIBarEx( &pObject, 0, (INT16)( gsKeyRingPopupInvX + sOffSetX + ( cnt % sKeyRingItemWidth * usWidth ) + 7 ), ( INT16 )( gsKeyRingPopupInvY + sOffSetY + ( cnt / sKeyRingItemWidth * usHeight ) + 24 )
			, ITEM_BAR_WIDTH, ITEM_BAR_HEIGHT, 	Get16BPPColor( STATUS_BAR ), Get16BPPColor( STATUS_BAR_SHADOW ), TRUE , FRAME_BUFFER );

			// set item type
			pObject.usItem = FIRST_KEY + LockTable[ gpItemPopupSoldier->pKeyRing[ cnt].ubKeyID ].usKeyItem;

			// render the item
			INVRenderItem( FRAME_BUFFER, NULL, &pObject, (INT16)(gsKeyRingPopupInvX + sOffSetX +( cnt % sKeyRingItemWidth * usWidth ) + 8), ( INT16 )( gsKeyRingPopupInvY + sOffSetY + ( cnt / sKeyRingItemWidth * usHeight ) ),
				( UINT16 )( usWidth - 8 ), ( UINT16 )( usHeight - 2 ) , DIRTYLEVEL2,  NULL, 0, 0, 0 );
		}

		//BltVideoObjectFromIndex( FRAME_BUFFER, guiItemPopupBoxes, 0, (INT16)(gsKeyRingPopupInvX + ( cnt % KEY_RING_ROW_WIDTH * usWidth ) ), ( INT16 )( gsKeyRingPopupInvY + ( cnt / KEY_RING_ROW_WIDTH * usHeight ) ));


	}

	//RestoreExternBackgroundRect( gsItemPopupInvX, gsItemPopupInvY, gsItemPopupInvWidth, gsItemPopupInvHeight );
	InvalidateRegion( gsKeyRingPopupInvX, gsKeyRingPopupInvY, gsKeyRingPopupInvX + gsKeyRingPopupInvWidth, gsKeyRingPopupInvY + gsKeyRingPopupInvHeight );

}


void DeleteKeyRingPopup(void)
{
	if (!gfInKeyRingPopup) return;

	DeleteVideoObjectFromIndex(guiItemPopupBoxes);

	MSYS_RemoveRegion(&gItemPopupRegion);

	gfInKeyRingPopup = FALSE;

	for (INT32 i = 0; i < NUMBER_KEYS_ON_KEYRING; i++)
	{
		MSYS_RemoveRegion(&gKeyRingRegions[i]);
	}

	fInterfacePanelDirty = DIRTYLEVEL2;

	//guiTacticalInterfaceFlags &= (~INTERFACE_NORENDERBUTTONS);

//	if ( !(guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
	if (guiCurrentItemDescriptionScreen != MAP_SCREEN)
	{
		EnableSMPanelButtons(TRUE, FALSE);
	}

	FreeMouseCursor();
}


UINT32 GetInterfaceGraphicForItem(const INVTYPE* pItem)
{
	// CHECK SUBCLASS
	switch (pItem->ubGraphicType)
	{
		case 0:  return guiGUNSM;
		case 1:  return guiP1ITEMS;
		case 2:  return guiP2ITEMS;
		default: return guiP3ITEMS;
	}
}


UINT16 GetTileGraphicForItem(const INVTYPE* pItem)
{
	UINT32 Type;
	switch (pItem->ubGraphicType)
	{
		case 0:  Type = GUNS;    break;
		case 1:  Type = P1ITEMS; break;
		case 2:  Type = P2ITEMS; break;
		default: Type = P3ITEMS; break;
	}
	return GetTileIndexFromTypeSubIndex(Type, pItem->ubGraphicNum + 1);
}


UINT32 LoadTileGraphicForItem(const INVTYPE* pItem)
{
	const char* Prefix;
	switch (pItem->ubGraphicType)
	{
		case 0:  Prefix = "gun";    break;
		case 1:  Prefix = "p1item"; break;
		case 2:  Prefix = "p2item"; break;
		default: Prefix = "p3item"; break;
	}

	//Load item
	SGPFILENAME ImageFile;
	sprintf(ImageFile, "BIGITEMS/%s%02d.sti", Prefix, pItem->ubGraphicNum);
	return AddVideoObjectFromFile(ImageFile);
}


static void ItemDescCallback(MOUSE_REGION* pRegion, INT32 iReason)
{
	static BOOLEAN fRightDown = FALSE, fLeftDown = FALSE;

	if (iReason & MSYS_CALLBACK_REASON_LBUTTON_DWN)
	{
		fLeftDown = TRUE;
	}
	else if (iReason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		if ( fLeftDown )
		{
			fLeftDown = FALSE;

			//Only exit the screen if we are NOT in the money interface.  Only the DONE button should exit the money interface.
			if( gpItemDescObject->usItem != MONEY )
			{
				DeleteItemDescriptionBox( );
			}
		}
	}
	else if (iReason & MSYS_CALLBACK_REASON_RBUTTON_DWN)
	{
		fRightDown = TRUE;
	}
	else if (iReason & MSYS_CALLBACK_REASON_RBUTTON_UP)
	{
		if ( fRightDown )
		{
			fRightDown = FALSE;

			//Only exit the screen if we are NOT in the money interface.  Only the DONE button should exit the money interface.
//			if( gpItemDescObject->usItem != MONEY )
			{
				DeleteItemDescriptionBox( );
			}
		}
	}
}


static void RemoveMoney(void);


static void ItemDescDoneButtonCallback(GUI_BUTTON *btn, INT32 reason)
{
	if (reason & MSYS_CALLBACK_REASON_LBUTTON_UP)
  {
		if (gpItemDescObject->usItem == MONEY) RemoveMoney();
		DeleteItemDescriptionBox();
	}

	if (reason & MSYS_CALLBACK_REASON_RBUTTON_UP)
  {
		DeleteItemDescriptionBox();
	}
}


static void ItemPopupRegionCallback(MOUSE_REGION* pRegion, INT32 iReason)
{
	UINT32					uiItemPos;

	uiItemPos = MSYS_GetRegionUserData( pRegion, 0 );

	// TO ALLOW ME TO DELETE REGIONS IN CALLBACKS!
	if ( gfItemPopupRegionCallbackEndFix )
	{
		return;
	}

	if (iReason & MSYS_CALLBACK_REASON_LBUTTON_DWN)
	{

		//If one in our hand, place it
		if ( gpItemPointer != NULL )
		{
				if ( !PlaceObjectAtObjectIndex( gpItemPointer, gpItemPopupObject, (UINT8)uiItemPos ) )
				{
    		  if ( (guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
          {
            MAPEndItemPointer( );
          }
          else
          {
					  gpItemPointer = NULL;
					  MSYS_ChangeRegionCursor( &gSMPanelRegion , CURSOR_NORMAL );
					  SetCurrentCursorFromDatabase( CURSOR_NORMAL );

						if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
						{
							memset( &gMoveingItem, 0, sizeof( INVENTORY_IN_SLOT ) );
							SetSkiCursor( CURSOR_NORMAL );
						}
          }

					// re-evaluate repairs
					gfReEvaluateEveryonesNothingToDo = TRUE;
				}

				//Dirty interface
				//fInterfacePanelDirty = DIRTYLEVEL2;
				//RenderItemStackPopup( FALSE );
		}
		else
		{
			if ( uiItemPos < gpItemPopupObject->ubNumberOfObjects )
			{
				// Here, grab an item and put in cursor to swap
				//RemoveObjFrom( OBJECTTYPE * pObj, UINT8 ubRemoveIndex )
				GetObjFrom( gpItemPopupObject, (UINT8)uiItemPos, &gItemPointer );

    		if ( (guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN ) )
        {
			    // pick it up
          InternalMAPBeginItemPointer( gpItemPopupSoldier );
        }
        else
        {
				  gpItemPointer = &gItemPointer;
				  gpItemPointerSoldier = gpItemPopupSoldier;
        }

				//if we are in the shop keeper interface
				if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
				{
					// pick up stacked item into cursor and try to sell it ( unless CTRL is held down )
					BeginSkiItemPointer( PLAYERS_INVENTORY, -1, ( BOOLEAN )!gfKeyState[ CTRL ] );

					// if we've just removed the last one there
					if ( gpItemPopupObject->ubNumberOfObjects == 0 )
					{
						// we must immediately get out of item stack popup, because the item has been deleted (memset to 0), and
						// errors like a right bringing up an item description for item 0 could happen then.  ARM.
						DeleteItemStackPopup( );
					}
				}

				// re-evaluate repairs
				gfReEvaluateEveryonesNothingToDo = TRUE;

				//Dirty interface
				//RenderItemStackPopup( FALSE );
				//fInterfacePanelDirty = DIRTYLEVEL2;
			}
		}

		UpdateItemHatches();
	}
	else if (iReason & MSYS_CALLBACK_REASON_RBUTTON_UP)
	{
		// Get Description....
		// Some global stuff here - for esc, etc
		//Remove
		gfItemPopupRegionCallbackEndFix = TRUE;


		DeleteItemStackPopup( );

		if ( !InItemDescriptionBox( ) )
		{
			// RESTORE BACKGROUND
			RestoreExternBackgroundRect( gsItemPopupInvX, gsItemPopupInvY, gsItemPopupInvWidth, gsItemPopupInvHeight );
			if ( guiCurrentItemDescriptionScreen == MAP_SCREEN )
			{
				MAPInternalInitItemDescriptionBox( gpItemPopupObject, (UINT8)uiItemPos, gpItemPopupSoldier );
			}
			else
			{
				InternalInitItemDescriptionBox( gpItemPopupObject, (INT16) ITEMDESC_START_X, (INT16) ITEMDESC_START_Y, (UINT8)uiItemPos, gpItemPopupSoldier );
			}
		}


	}
}


static void ItemPopupFullRegionCallback(MOUSE_REGION* pRegion, INT32 iReason)
{
	if (iReason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		if ( InItemStackPopup( ) )
		{
			// End stack popup and retain pointer
			EndItemStackPopupWithItemInHand( );
		}
		else if( InKeyRingPopup() )
		{
			// end pop up with key in hand
			DeleteKeyRingPopup( );
			fTeamPanelDirty = TRUE;

		}
	}
	else if (iReason & MSYS_CALLBACK_REASON_RBUTTON_UP)
	{
		if ( InItemStackPopup( ) )
		{
			DeleteItemStackPopup( );
			fTeamPanelDirty = TRUE;
		}
		else
		{
			DeleteKeyRingPopup( );
			fTeamPanelDirty = TRUE;
		}
	}
}

#define NUM_PICKUP_SLOTS				6

typedef struct
{
	ITEM_POOL			*pItemPool;
	INT16					sX;
	INT16					sY;
	INT16					sWidth;
	INT16					sHeight;
	INT8					bScrollPage;
	INT32			  	ubScrollAnchor;
	INT32		  		ubTotalItems;
	INT32		  		bCurSelect;
	UINT8					bNumSlotsPerPage;
	UINT32				uiPanelVo;
	INT32					iUpButtonImages;
	INT32					iDownButtonImages;
	INT32					iAllButtonImages;
	INT32					iCancelButtonImages;
	INT32					iOKButtonImages;
	INT32					iUpButton;
	INT32					iDownButton;
	INT32					iAllButton;
	INT32					iOKButton;
	INT32					iCancelButton;
	BOOLEAN				fCanScrollUp;
	BOOLEAN				fCanScrollDown;
	BOOLEAN				fDirtyLevel;
	INT32					iDirtyRect;
	BOOLEAN				fHandled;
	INT16					sGridNo;
	INT8					bZLevel;
	INT16					sButtomPanelStartY;
	SOLDIERTYPE		*pSoldier;
	ITEM_POOL			*ItemPoolSlots[ NUM_PICKUP_SLOTS ];
	MOUSE_REGION	Regions[ NUM_PICKUP_SLOTS ];
	MOUSE_REGION	BackRegions;
	MOUSE_REGION	BackRegion;
	BOOLEAN				*pfSelectedArray;
	BOOLEAN				fAtLeastOneSelected;
	OBJECTTYPE		CompAmmoObject;
	BOOLEAN				fAllSelected;

} ITEM_PICKUP_MENU_STRUCT;

#define					ITEMPICK_UP_X				55
#define					ITEMPICK_UP_Y				5
#define					ITEMPICK_DOWN_X			111
#define					ITEMPICK_DOWN_Y			5
#define					ITEMPICK_ALL_X			79
#define					ITEMPICK_ALL_Y			6
#define					ITEMPICK_OK_X				16
#define					ITEMPICK_OK_Y				6
#define					ITEMPICK_CANCEL_X		141
#define					ITEMPICK_CANCEL_Y		6

#define					ITEMPICK_START_X_OFFSET		10

#define					ITEMPICK_GRAPHIC_X			10
#define					ITEMPICK_GRAPHIC_Y			12
#define					ITEMPICK_GRAPHIC_YSPACE	26

#define					ITEMPICK_TEXT_X					56
#define					ITEMPICK_TEXT_Y					22
#define					ITEMPICK_TEXT_YSPACE		26
#define					ITEMPICK_TEXT_WIDTH			109


static ITEM_PICKUP_MENU_STRUCT gItemPickupMenu;
BOOLEAN											gfInItemPickupMenu = FALSE;


// STUFF FOR POPUP ITEM INFO BOX
void SetItemPickupMenuDirty( BOOLEAN fDirtyLevel )
{
	gItemPickupMenu.fDirtyLevel = fDirtyLevel;
}


static void CalculateItemPickupMenuDimensions(void);
static void ItemPickMenuMouseClickCallback(MOUSE_REGION* pRegion, INT32 iReason);
static void ItemPickMenuMouseMoveCallback(MOUSE_REGION* pRegion, INT32 iReason);
static void ItemPickupAll(GUI_BUTTON* btn, INT32 reason);
static void ItemPickupCancel(GUI_BUTTON* btn, INT32 reason);
static void ItemPickupOK(GUI_BUTTON* btn, INT32 reason);
static void ItemPickupScrollDown(GUI_BUTTON* btn, INT32 reason);
static void ItemPickupScrollUp(GUI_BUTTON* btn, INT32 reason);
static void SetupPickupPage(INT8 bPage);


BOOLEAN InitializeItemPickupMenu( SOLDIERTYPE *pSoldier, INT16 sGridNo, ITEM_POOL *pItemPool, INT16 sScreenX, INT16 sScreenY, INT8 bZLevel )
{
	ITEM_POOL				*pTempItemPool;
	INT32						cnt;
	INT16						sCenX, sCenY, sX, sY, sCenterYVal;

	// Erase other menus....
	EraseInterfaceMenus( TRUE );

	// Make sure menu is located if not on screen
	LocateSoldier( pSoldier->ubID, FALSE );

	// memset values
	memset( &gItemPickupMenu, 0, sizeof( gItemPickupMenu ) );

	//Set item pool value
	gItemPickupMenu.pItemPool		= pItemPool;

	InterruptTime();
	PauseGame();
	LockPauseState( 18 );
	// Pause timers as well....
	PauseTime( TRUE );


	// Alrighty, cancel lock UI if we havn't done so already
	UnSetUIBusy( pSoldier->ubID );

	// Change to INV panel if not there already...
	gfSwitchPanel = TRUE;
	gbNewPanel = SM_PANEL;
	gubNewPanelParam = (UINT8)pSoldier->ubID;

	//Determine total #
	cnt = 0;
	pTempItemPool = pItemPool;
	while( pTempItemPool != NULL )
	{
		if ( ItemPoolOKForDisplay( pTempItemPool, bZLevel ) )
		{
			cnt++;
		}

		pTempItemPool = pTempItemPool->pNext;
	}
	gItemPickupMenu.ubTotalItems = (UINT8)cnt;

	// Determine # of slots per page
	if ( gItemPickupMenu.ubTotalItems > NUM_PICKUP_SLOTS )
	{
		gItemPickupMenu.bNumSlotsPerPage = NUM_PICKUP_SLOTS;
	}
	else
	{
		gItemPickupMenu.bNumSlotsPerPage = gItemPickupMenu.ubTotalItems;
	}

	gItemPickupMenu.uiPanelVo = AddVideoObjectFromFile("INTERFACE/itembox.sti");
	CHECKF(gItemPickupMenu.uiPanelVo != NO_VOBJECT);

	// Memalloc selection array...
	 gItemPickupMenu.pfSelectedArray = MemAlloc(( sizeof( UINT8 ) * gItemPickupMenu.ubTotalItems ) );
	// seto to 0
	memset( gItemPickupMenu.pfSelectedArray, 0, ( sizeof( UINT8 ) * gItemPickupMenu.ubTotalItems ) );

	// Calcualate dimensions
	CalculateItemPickupMenuDimensions( );

	// Get XY
	{
		// First get mouse xy screen location
		if( sGridNo != NOWHERE )
		{
			sX = gusMouseXPos;
			sY = gusMouseYPos;
		}
		else
		{
			 sX = sScreenX;
			 sY = sScreenY;
		}

		// CHECK FOR LEFT/RIGHT
		if (sX + gItemPickupMenu.sWidth > SCREEN_WIDTH)
		{
			sX = SCREEN_WIDTH - gItemPickupMenu.sWidth - ITEMPICK_START_X_OFFSET;
		}
		else
		{
			sX = sX + ITEMPICK_START_X_OFFSET;
		}

		// Now check for top
		// Center in the y
		sCenterYVal = gItemPickupMenu.sHeight / 2;

		sY -= sCenterYVal;

		if ( sY < gsVIEWPORT_WINDOW_START_Y )
		{
			sY = gsVIEWPORT_WINDOW_START_Y;
		}

		// Check for bottom
		if ( ( sY + gItemPickupMenu.sHeight ) > 340 )
		{
			sY = 340 - gItemPickupMenu.sHeight;
		}

	}

	// Set some values
	gItemPickupMenu.sX					= sX;
	gItemPickupMenu.sY					= sY;
	gItemPickupMenu.bCurSelect	= 0;
	gItemPickupMenu.pSoldier		= pSoldier;
	gItemPickupMenu.fHandled		= FALSE;
	gItemPickupMenu.sGridNo			= sGridNo;
	gItemPickupMenu.bZLevel			= bZLevel;
	gItemPickupMenu.fAtLeastOneSelected = FALSE;
	gItemPickupMenu.fAllSelected	= FALSE;

	//Load images for buttons
	gItemPickupMenu.iUpButtonImages     = LoadButtonImage("INTERFACE/itembox.sti", -1, 5, -1, 10, -1);
	gItemPickupMenu.iDownButtonImages		=	UseLoadedButtonImage( gItemPickupMenu.iUpButtonImages, -1, 7, -1, 12, -1 );
	gItemPickupMenu.iAllButtonImages		=	UseLoadedButtonImage( gItemPickupMenu.iUpButtonImages, -1, 6, -1,11, -1 );
	gItemPickupMenu.iCancelButtonImages	=	UseLoadedButtonImage( gItemPickupMenu.iUpButtonImages, -1, 8, -1, 13, -1 );
	gItemPickupMenu.iOKButtonImages			=	UseLoadedButtonImage( gItemPickupMenu.iUpButtonImages, -1, 4, -1, 9, -1 );


	// Build a mouse region here that is over any others.....
	MSYS_DefineRegion(&gItemPickupMenu.BackRegion, 532, 367, SCREEN_WIDTH, SCREEN_HEIGHT, MSYS_PRIORITY_HIGHEST, CURSOR_NORMAL, MSYS_NO_CALLBACK, MSYS_NO_CALLBACK);

	// Build a mouse region here that is over any others.....
	MSYS_DefineRegion(&gItemPickupMenu.BackRegions, gItemPickupMenu.sX, gItemPickupMenu.sY, gItemPickupMenu.sX + gItemPickupMenu.sWidth, gItemPickupMenu.sY + gItemPickupMenu.sHeight, MSYS_PRIORITY_HIGHEST, CURSOR_NORMAL, MSYS_NO_CALLBACK, MSYS_NO_CALLBACK);


	// Create buttons
	if ( gItemPickupMenu.bNumSlotsPerPage == NUM_PICKUP_SLOTS && gItemPickupMenu.ubTotalItems > NUM_PICKUP_SLOTS )
	{
		gItemPickupMenu.iUpButton	= QuickCreateButton(gItemPickupMenu.iUpButtonImages, sX + ITEMPICK_UP_X, sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_UP_Y, BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST, DEFAULT_MOVE_CALLBACK, ItemPickupScrollUp);

		SetButtonFastHelpText( gItemPickupMenu.iUpButton, ItemPickupHelpPopup[ 1 ] );


		gItemPickupMenu.iDownButton	= QuickCreateButton(gItemPickupMenu.iDownButtonImages, sX + ITEMPICK_DOWN_X, sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_DOWN_Y, BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST, DEFAULT_MOVE_CALLBACK, ItemPickupScrollDown);

		SetButtonFastHelpText( gItemPickupMenu.iDownButton, ItemPickupHelpPopup[ 3 ] );

	}


	gItemPickupMenu.iOKButton = QuickCreateButton(gItemPickupMenu.iOKButtonImages, sX + ITEMPICK_OK_X, sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_OK_Y, BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST, DEFAULT_MOVE_CALLBACK, ItemPickupOK);
	SetButtonFastHelpText( gItemPickupMenu.iOKButton, ItemPickupHelpPopup[ 0 ] );


	gItemPickupMenu.iAllButton = QuickCreateButton(gItemPickupMenu.iAllButtonImages, sX + ITEMPICK_ALL_X, sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_ALL_Y, BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST, DEFAULT_MOVE_CALLBACK, ItemPickupAll);
	SetButtonFastHelpText( gItemPickupMenu.iAllButton, ItemPickupHelpPopup[ 2 ] );

	gItemPickupMenu.iCancelButton = QuickCreateButton(gItemPickupMenu.iCancelButtonImages, sX + ITEMPICK_CANCEL_X, sY + gItemPickupMenu.sButtomPanelStartY + ITEMPICK_CANCEL_Y, BUTTON_TOGGLE, MSYS_PRIORITY_HIGHEST, DEFAULT_MOVE_CALLBACK, ItemPickupCancel);
	SetButtonFastHelpText( gItemPickupMenu.iCancelButton, ItemPickupHelpPopup[ 4 ] );


	DisableButton( gItemPickupMenu.iOKButton );



	// Create regions...
	sCenX = gItemPickupMenu.sX;
	sCenY = gItemPickupMenu.sY + ITEMPICK_GRAPHIC_Y;

	for ( cnt = 0; cnt < gItemPickupMenu.bNumSlotsPerPage; cnt++ )
	{
		// Build a mouse region here that is over any others.....
		MSYS_DefineRegion(&gItemPickupMenu.Regions[cnt], sCenX, sCenY + 1, sCenX + gItemPickupMenu.sWidth, sCenY + ITEMPICK_GRAPHIC_YSPACE, MSYS_PRIORITY_HIGHEST, CURSOR_NORMAL, ItemPickMenuMouseMoveCallback, ItemPickMenuMouseClickCallback);
		MSYS_SetRegionUserData( &(gItemPickupMenu.Regions[cnt]), 0, cnt );

		sCenY += ITEMPICK_GRAPHIC_YSPACE;
	}

	//Save dirty rect
	//gItemPickupMenu.iDirtyRect = RegisterBackgroundRect(BGND_FLAG_PERMANENT | BGND_FLAG_SAVERECT, gItemPickupMenu.sX, gItemPickupMenu.sY, gItemPickupMenu.sX + gItemPickupMenu.sWidth, gItemPickupMenu.sY + gItemPickupMenu.sHeight);

	SetupPickupPage( 0 );

	gfInItemPickupMenu = TRUE;

	// Ignore scrolling
	gfIgnoreScrolling = TRUE;

	HandleAnyMercInSquadHasCompatibleStuff( (INT8) CurrentSquad( ), NULL, TRUE );
	gubSelectSMPanelToMerc = pSoldier->ubID;
	ReEvaluateDisabledINVPanelButtons( );
	DisableTacticalTeamPanelButtons( TRUE );

	//gfSMDisableForItems = TRUE;
	return( TRUE );
}


static void SetupPickupPage(INT8 bPage)
{
	INT32 cnt, iStart, iEnd;
	ITEM_POOL				*pTempItemPool;
  INT16           sValue;
	OBJECTTYPE  *pObject;
	static wchar_t pStr[ 200 ];


	// Zero out page slots
	memset( gItemPickupMenu.ItemPoolSlots, 0, sizeof( gItemPickupMenu.ItemPoolSlots )  );

	// Zero page flags
	gItemPickupMenu.fCanScrollUp		= FALSE;
	gItemPickupMenu.fCanScrollDown  = FALSE;

	// Get lower bound
	iStart = bPage * NUM_PICKUP_SLOTS;
	if ( iStart > gItemPickupMenu.ubTotalItems )
	{
		return;
	}

	if ( bPage > 0 )
	{
		gItemPickupMenu.fCanScrollUp = TRUE;
	}


	iEnd   = iStart + NUM_PICKUP_SLOTS;
	if ( iEnd >= gItemPickupMenu.ubTotalItems )
	{
		iEnd = gItemPickupMenu.ubTotalItems;
	}
	else
	{
		// We can go for more!
		gItemPickupMenu.fCanScrollDown = TRUE;
	}

	// Setup slots!
	// These slots contain an inventory pool pointer for each slot...
	pTempItemPool = gItemPickupMenu.pItemPool;

  // ATE: Patch fix here for crash :(
  // Clear help text!
	for ( cnt = 0; cnt < NUM_PICKUP_SLOTS; cnt++ )
	{
  	SetRegionFastHelpText( &(gItemPickupMenu.Regions[cnt]), L"" );
  }

	for ( cnt = 0; cnt < iEnd; )
	{
		// Move to the closest one that can be displayed....
		while( !ItemPoolOKForDisplay( pTempItemPool, gItemPickupMenu.bZLevel ) )
		{
			pTempItemPool = pTempItemPool->pNext;
		}

		if ( cnt >= iStart )
		{
			gItemPickupMenu.ItemPoolSlots[ cnt - iStart ] = pTempItemPool;

			pObject = &(gWorldItems[ pTempItemPool->iItemIndex ].o );

		  sValue = pObject->bStatus[ 0 ];

	    // Adjust for ammo, other thingys..
	    if( Item[ pObject->usItem ].usItemClass & IC_AMMO || Item[ pObject->usItem ].usItemClass & IC_KEY )
	    {
        swprintf( pStr, lengthof(pStr), L"" );
	    }
      else
      {
        swprintf( pStr, lengthof(pStr), L"%d%%", sValue );
      }

    	SetRegionFastHelpText( &(gItemPickupMenu.Regions[ cnt - iStart ]), pStr );
		}

		cnt++;

		pTempItemPool = pTempItemPool->pNext;
	}

	gItemPickupMenu.bScrollPage		= bPage;
	gItemPickupMenu.ubScrollAnchor	= (UINT8)iStart;

	if ( gItemPickupMenu.bNumSlotsPerPage == NUM_PICKUP_SLOTS && gItemPickupMenu.ubTotalItems > NUM_PICKUP_SLOTS )
	{
		// Setup enabled/disabled buttons
		if ( gItemPickupMenu.fCanScrollUp )
		{
			EnableButton( gItemPickupMenu.iUpButton );
		}
		else
		{
			DisableButton( gItemPickupMenu.iUpButton );
		}

		// Setup enabled/disabled buttons
		if ( gItemPickupMenu.fCanScrollDown )
		{
			EnableButton( gItemPickupMenu.iDownButton );
		}
		else
		{
			DisableButton( gItemPickupMenu.iDownButton );
		}
	}
	SetItemPickupMenuDirty( DIRTYLEVEL2 );

}


static void CalculateItemPickupMenuDimensions(void)
{
	// Build background
	INT16 sY = 0;

	for (INT32 cnt = 0; cnt < gItemPickupMenu.bNumSlotsPerPage; cnt++)
	{
		// Add height of object
		UINT16 usSubRegion = (cnt == 0 ? 0 : 1);
		const ETRLEObject* ETRLEProps = GetVideoObjectETRLESubregionProperties(gItemPickupMenu.uiPanelVo, usSubRegion);
		sY += ETRLEProps->usHeight;
	}
	gItemPickupMenu.sButtomPanelStartY = sY;

	// Do end
	const ETRLEObject* ETRLEProps = GetVideoObjectETRLESubregionProperties(gItemPickupMenu.uiPanelVo, 2);
	sY += ETRLEProps->usHeight;

	// Set height, width
	gItemPickupMenu.sHeight = sY;
	gItemPickupMenu.sWidth  = ETRLEProps->usWidth;
}


// set pick up menu dirty level
void SetPickUpMenuDirtyLevel( BOOLEAN fDirtyLevel )
{
	gItemPickupMenu.fDirtyLevel = fDirtyLevel;
}


void RenderItemPickupMenu( )
{
	INT32			cnt;
	UINT16		usItemTileIndex;
	INT16			sX, sY, sCenX, sCenY, sFontX, sFontY, sNewX, sNewY;
	wchar_t			pStr[ 100 ];
	INVTYPE   *pItem;
	OBJECTTYPE  *pObject;
	UINT16			uiStringLength;


	if ( !gfInItemPickupMenu )
	{
		return;
	}


	// Do everything!
	if ( gItemPickupMenu.fDirtyLevel == DIRTYLEVEL2 )
	{
		MarkButtonsDirty( );

		// Build background
		sX = gItemPickupMenu.sX;
		sY = gItemPickupMenu.sY;

		for ( cnt = 0; cnt < gItemPickupMenu.bNumSlotsPerPage; cnt++ )
		{
			UINT16 usSubRegion = (cnt == 0 ? 0 : 1);

			BltVideoObjectFromIndex( FRAME_BUFFER, gItemPickupMenu.uiPanelVo, usSubRegion, sX, sY);

			// Add height of object
			const ETRLEObject* ETRLEProps = GetVideoObjectETRLESubregionProperties(gItemPickupMenu.uiPanelVo, usSubRegion);
			sY += ETRLEProps->usHeight;
		}

		// Do end
		if ( gItemPickupMenu.bNumSlotsPerPage == NUM_PICKUP_SLOTS && gItemPickupMenu.ubTotalItems > NUM_PICKUP_SLOTS )
		{
			BltVideoObjectFromIndex( FRAME_BUFFER, gItemPickupMenu.uiPanelVo, 2, sX, sY);
		}
		else
		{
			BltVideoObjectFromIndex( FRAME_BUFFER, gItemPickupMenu.uiPanelVo, 3, sX, sY);
		}

		// Render items....
		sX = ITEMPICK_GRAPHIC_X + gItemPickupMenu.sX;
		sY = ITEMPICK_GRAPHIC_Y + gItemPickupMenu.sY;

		UINT32 uiDestPitchBYTES;
		UINT16* pDestBuf = (UINT16*)LockVideoSurface(FRAME_BUFFER, &uiDestPitchBYTES);

		SetFont( ITEMDESC_FONT );
		SetFontBackground( FONT_MCOLOR_BLACK );
		SetFontShadow( ITEMDESC_FONTSHADOW2 );

		for ( cnt = 0; cnt < gItemPickupMenu.bNumSlotsPerPage; cnt++ )
		{
			if ( gItemPickupMenu.ItemPoolSlots[ cnt ] != NULL )
			{
				// Get item to render
				pObject = &(gWorldItems[ gItemPickupMenu.ItemPoolSlots[ cnt ]->iItemIndex ].o );
				pItem = &( Item[ pObject->usItem ] );

				usItemTileIndex = GetTileGraphicForItem( pItem );

				// Render
				sX = ITEMPICK_GRAPHIC_X + gItemPickupMenu.sX;

				sCenX = sX;
				sCenY = sY;

        // ATE: Adjust to basic shade.....
    		gTileDatabase[ usItemTileIndex ].hTileSurface->pShadeCurrent=gTileDatabase[ usItemTileIndex ].hTileSurface->pShades[4];

				//else
				{
					if ( gItemPickupMenu.pfSelectedArray[  cnt + gItemPickupMenu.ubScrollAnchor ] )
					{
						//SetFontForeground( FONT_MCOLOR_LTYELLOW );
						//SetFontShadow( ITEMDESC_FONTSHADOW2 );
						Blt8BPPDataTo16BPPBufferOutline(pDestBuf, uiDestPitchBYTES, gTileDatabase[usItemTileIndex].hTileSurface, sCenX, sCenY, gTileDatabase[usItemTileIndex].usRegionIndex, Get16BPPColor(FROMRGB(255, 255, 0)), TRUE);
					}
					else
					{
						//SetFontForeground( FONT_BLACK );
						//SetFontShadow( ITEMDESC_FONTSHADOW2 );
						Blt8BPPDataTo16BPPBufferOutline(pDestBuf, uiDestPitchBYTES, gTileDatabase[usItemTileIndex].hTileSurface, sCenX, sCenY, gTileDatabase[usItemTileIndex].usRegionIndex, 0, FALSE);
					}
        }

        // Draw text.....
      	SetFont( ITEM_FONT );
				if ( pObject->ubNumberOfObjects > 1 )
				{
					SetFontForeground( FONT_GRAY4 );
					SetFontShadow( DEFAULT_SHADOW );

				  sCenX = sX - 4;
				  sCenY = sY + 14;

				  swprintf( pStr, lengthof(pStr), L"%d", pObject->ubNumberOfObjects );

				  FindFontRightCoordinates(sCenX, sCenY, 42, 1, pStr, ITEM_FONT, &sFontX, &sFontY);
				  mprintf_buffer(pDestBuf, uiDestPitchBYTES, sFontX, sFontY, pStr);
				}
      	SetFont( ITEMDESC_FONT );


        // Render attachment symbols
			  if ( ItemHasAttachments( pObject ) )
			  {
				  SetFontForeground( FONT_GREEN );
					SetFontShadow( DEFAULT_SHADOW );

				  sNewY = sCenY + 2;
					const wchar_t* AttachMarker = L"*";

				  // Get length of string
				  uiStringLength = StringPixLength(AttachMarker, ITEM_FONT);

				  sNewX = sCenX + 43 - uiStringLength - 4;

  				mprintf_buffer(pDestBuf, uiDestPitchBYTES, sNewX, sNewY, AttachMarker);
			  }

				if ( gItemPickupMenu.bCurSelect == ( cnt + gItemPickupMenu.ubScrollAnchor ) )
				{
					//SetFontForeground( ITEMDESC_FONTSHADOW2 );
					//if ( gItemPickupMenu.pfSelectedArray[  cnt + gItemPickupMenu.ubScrollAnchor ] )
					//{
					//	SetFontForeground( FONT_MCOLOR_LTYELLOW );
					//	SetFontShadow( ITEMDESC_FONTSHADOW2 );
					//}
					//else
					//{
						SetFontForeground( FONT_WHITE );
						SetFontShadow( DEFAULT_SHADOW );
					//}
					// Blt8BPPDataTo16BPPBufferOutline(pDestBuf, uiDestPitchBYTES, gTileDatabase[usItemTileIndex].hTileSurface, sCenX, sCenY, gTileDatabase[usItemTileIndex].usRegionIndex, Get16BPPColor(FROMRGB(255, 0, 0)), TRUE);
					// Blt8BPPDataTo16BPPBufferOutline(pDestBuf, uiDestPitchBYTES, gTileDatabase[usItemTileIndex].hTileSurface, sCenX, sCenY, gTileDatabase[usItemTileIndex].usRegionIndex, Get16BPPColor(FROMRGB(255, 0, 0)), TRUE);
				}
				else
				{
					SetFontForeground( FONT_BLACK );
					SetFontShadow( ITEMDESC_FONTSHADOW2 );
				}

				// Render name
				sCenX = ITEMPICK_TEXT_X + gItemPickupMenu.sX;
				sCenY = ITEMPICK_TEXT_Y + gItemPickupMenu.sY + ( ITEMPICK_TEXT_YSPACE * (INT16)cnt );

				// If we are money...
				if ( Item[ pObject->usItem ].usItemClass == IC_MONEY )
				{
					wchar_t pStr2[20];
					SPrintMoney(pStr2, pObject->uiMoneyAmount);
					swprintf( pStr, lengthof(pStr), L"%ls (%ls)", ItemNames[ pObject->usItem ], pStr2 );
				}
				else
				{
					wcslcpy(pStr, ShortItemNames[pObject->usItem], lengthof(pStr));
				}
				FindFontCenterCoordinates(sCenX, sCenY, ITEMPICK_TEXT_WIDTH, 1, pStr, ITEMDESC_FONT, &sFontX, &sFontY);
				mprintf_buffer(pDestBuf, uiDestPitchBYTES, sFontX, sFontY, pStr);

				sY += ITEMPICK_GRAPHIC_YSPACE;
			}
		}

		SetFontShadow( DEFAULT_SHADOW );


		UnLockVideoSurface( FRAME_BUFFER );

		InvalidateRegion( gItemPickupMenu.sX, gItemPickupMenu.sY, gItemPickupMenu.sX + gItemPickupMenu.sWidth, gItemPickupMenu.sY + gItemPickupMenu.sHeight );

		gItemPickupMenu.fDirtyLevel = 0;

	}
}


void RemoveItemPickupMenu( )
{
	INT32 cnt;

	if ( gfInItemPickupMenu )
	{
		gfSMDisableForItems = FALSE;

		HandleAnyMercInSquadHasCompatibleStuff( (INT8) CurrentSquad( ), NULL, TRUE );

		UnLockPauseState();
		UnPauseGame();
		// UnPause timers as well....
		PauseTime( FALSE );

		// Unfreese guy!
		gItemPickupMenu.pSoldier->fPauseAllAnimation = FALSE;

		// Remove graphics!
		DeleteVideoObjectFromIndex( gItemPickupMenu.uiPanelVo );

		// Remove buttons
		if ( gItemPickupMenu.bNumSlotsPerPage == NUM_PICKUP_SLOTS && gItemPickupMenu.ubTotalItems > NUM_PICKUP_SLOTS )
		{
			RemoveButton( gItemPickupMenu.iUpButton );
			RemoveButton( gItemPickupMenu.iDownButton );
		}
		RemoveButton( gItemPickupMenu.iAllButton );
		RemoveButton( gItemPickupMenu.iOKButton );
		RemoveButton( gItemPickupMenu.iCancelButton );

		// Remove button images
		UnloadButtonImage( gItemPickupMenu.iUpButtonImages );
		UnloadButtonImage( gItemPickupMenu.iDownButtonImages );
		UnloadButtonImage( gItemPickupMenu.iAllButtonImages );
		UnloadButtonImage( gItemPickupMenu.iCancelButtonImages );
		UnloadButtonImage( gItemPickupMenu.iOKButtonImages );

		MSYS_RemoveRegion( &(gItemPickupMenu.BackRegions ) );
		MSYS_RemoveRegion( &(gItemPickupMenu.BackRegion ) );

		// Remove regions
		for ( cnt = 0; cnt < gItemPickupMenu.bNumSlotsPerPage; cnt++ )
		{
			MSYS_RemoveRegion( &(gItemPickupMenu.Regions[cnt]));
		}

		// Remove register rect
		if ( gItemPickupMenu.iDirtyRect != -1 )
		{
			//FreeBackgroundRect( gItemPickupMenu.iDirtyRect );
		}

		// Free selection list...
		MemFree( gItemPickupMenu.pfSelectedArray );
		gItemPickupMenu.pfSelectedArray = NULL;


		// Set cursor back to normal mode...
		guiPendingOverrideEvent = A_CHANGE_TO_MOVE;

		// Rerender world
		SetRenderFlags( RENDER_FLAG_FULL );

		gfInItemPickupMenu = FALSE;

		//gfSMDisableForItems = FALSE;
		//EnableButtonsForInItemBox( TRUE );
		EnableSMPanelButtons( TRUE , TRUE );
		gfSMDisableForItems = FALSE;

		fInterfacePanelDirty = DIRTYLEVEL2;

		// Turn off Ignore scrolling
		gfIgnoreScrolling = FALSE;
			DisableTacticalTeamPanelButtons( FALSE );
		gubSelectSMPanelToMerc = gpSMCurrentMerc->ubID;

	}
}


static void ItemPickupScrollUp(GUI_BUTTON* btn, INT32 reason)
{
	if (reason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		SetupPickupPage( (UINT8)( gItemPickupMenu.bScrollPage - 1 ) );
	}
}


static void ItemPickupScrollDown(GUI_BUTTON* btn, INT32 reason)
{
	if (reason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		SetupPickupPage( (UINT8)( gItemPickupMenu.bScrollPage + 1 ) );
	}
}


static void ItemPickupAll(GUI_BUTTON* btn, INT32 reason)
{
	INT32 cnt;

	if (reason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		gItemPickupMenu.fAllSelected = !gItemPickupMenu.fAllSelected;


		// OK, pickup item....
		//gItemPickupMenu.fHandled = TRUE;
		// Tell our soldier to pickup this item!
		//SoldierGetItemFromWorld( gItemPickupMenu.pSoldier, ITEM_PICKUP_ACTION_ALL, gItemPickupMenu.sGridNo, gItemPickupMenu.bZLevel, NULL );
		for ( cnt = 0; cnt < gItemPickupMenu.ubTotalItems; cnt++ )
		{
			gItemPickupMenu.pfSelectedArray[ cnt ] = gItemPickupMenu.fAllSelected;
		}

		if ( gItemPickupMenu.fAllSelected )
		{
			EnableButton( gItemPickupMenu.iOKButton );
		}
		else
		{
			DisableButton( gItemPickupMenu.iOKButton );
		}

	}
}


static void ItemPickupOK(GUI_BUTTON* btn, INT32 reason)
{
	if (reason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		// OK, pickup item....
		gItemPickupMenu.fHandled = TRUE;

		// Tell our soldier to pickup this item!
		SoldierGetItemFromWorld( gItemPickupMenu.pSoldier, ITEM_PICKUP_SELECTION, gItemPickupMenu.sGridNo, gItemPickupMenu.bZLevel, gItemPickupMenu.pfSelectedArray );
	}
}


static void ItemPickupCancel(GUI_BUTTON* btn, INT32 reason)
{
	if (reason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		// OK, pickup item....
		gItemPickupMenu.fHandled = TRUE;
	}
}


static void ItemPickMenuMouseMoveCallback(MOUSE_REGION* pRegion, INT32 iReason)
{
	UINT32					uiItemPos;
	ITEM_POOL				*pTempItemPool;
	INT32						bPos;
	static					BOOLEAN	bChecked = FALSE;

	uiItemPos = MSYS_GetRegionUserData( pRegion, 0 );


	if (iReason & MSYS_CALLBACK_REASON_MOVE)
	{
		bPos = ( uiItemPos + gItemPickupMenu.ubScrollAnchor );

		if ( bPos < gItemPickupMenu.ubTotalItems )
		{
			// Set current selected guy....
			gItemPickupMenu.bCurSelect = bPos;

			if ( !bChecked )
			{
				// Show compatible ammo...
				pTempItemPool = gItemPickupMenu.ItemPoolSlots[ gItemPickupMenu.bCurSelect - gItemPickupMenu.ubScrollAnchor ];

				gItemPickupMenu.CompAmmoObject = gWorldItems[pTempItemPool->iItemIndex].o;

				// Turn off first...
				HandleAnyMercInSquadHasCompatibleStuff( (INT8) CurrentSquad( ), NULL, TRUE );
				InternalHandleCompatibleAmmoUI( gpSMCurrentMerc, &( gItemPickupMenu.CompAmmoObject ), TRUE );

				HandleAnyMercInSquadHasCompatibleStuff( (INT8)CurrentSquad( ), &(gWorldItems[ pTempItemPool->iItemIndex ].o ), FALSE );

				SetItemPickupMenuDirty( DIRTYLEVEL2 );

				bChecked = TRUE;
			}
		}
	}
	else if( iReason & MSYS_CALLBACK_REASON_LOST_MOUSE )
	{
		gItemPickupMenu.bCurSelect = 255;

		InternalHandleCompatibleAmmoUI( gpSMCurrentMerc, &( gItemPickupMenu.CompAmmoObject ), FALSE );
		HandleAnyMercInSquadHasCompatibleStuff( (INT8) CurrentSquad( ), NULL, TRUE );

		SetItemPickupMenuDirty( DIRTYLEVEL2 );

		bChecked = FALSE;
	}


}


static void ItemPickupBackgroundClick(MOUSE_REGION* pRegion, INT32 iReason)
{
	if (iReason & MSYS_CALLBACK_REASON_RBUTTON_UP)
	{
		// OK, goto team panel....
		ToggleTacticalPanels();
	}
}


static void ItemPickMenuMouseClickCallback(MOUSE_REGION* pRegion, INT32 iReason)
{
	INT32				  	uiItemPos;
	UINT8						cnt;
	BOOLEAN					fEnable = FALSE;

	uiItemPos = MSYS_GetRegionUserData( pRegion, 0 );


	if (iReason & MSYS_CALLBACK_REASON_LBUTTON_UP)
	{
		if ( uiItemPos + gItemPickupMenu.ubScrollAnchor < gItemPickupMenu.ubTotalItems )
		{
			// Toggle selection... ONLY IF LEGAL!!
			gItemPickupMenu.pfSelectedArray[ uiItemPos + gItemPickupMenu.ubScrollAnchor ] = !gItemPickupMenu.pfSelectedArray[  uiItemPos + gItemPickupMenu.ubScrollAnchor ];

			// OK, pickup item....
			//gItemPickupMenu.fHandled = TRUE;

			//pTempItemPool = gItemPickupMenu.ItemPoolSlots[ gItemPickupMenu.bCurSelect - gItemPickupMenu.ubScrollAnchor ];

			// Tell our soldier to pickup this item!
			//SoldierGetItemFromWorld( gItemPickupMenu.pSoldier, pTempItemPool->iItemIndex, gItemPickupMenu.sGridNo, gItemPickupMenu.bZLevel );
		}

		// Loop through all and set /unset OK
		for ( cnt = 0; cnt < gItemPickupMenu.ubTotalItems; cnt++ )
		{
			if ( gItemPickupMenu.pfSelectedArray[ cnt ] )
			{
				fEnable = TRUE;
				break;
			}
		}

		if ( fEnable )
		{
			EnableButton( gItemPickupMenu.iOKButton );
		}
		else
		{
			DisableButton( gItemPickupMenu.iOKButton );
		}
	}
}

BOOLEAN HandleItemPickupMenu( )
{

	if ( !gfInItemPickupMenu )
	{
		return( FALSE );
	}

	if ( gItemPickupMenu.fHandled )
	{
		RemoveItemPickupMenu( );
	}

	return( gItemPickupMenu.fHandled );
}


static void BtnMoneyButtonCallback(GUI_BUTTON* btn, INT32 reason)
{
	INT8	i;
	if(reason & MSYS_CALLBACK_REASON_RBUTTON_DWN )
	{
		btn->uiFlags |= BUTTON_CLICKED_ON;
	}
	if(reason & MSYS_CALLBACK_REASON_LBUTTON_UP )
	{
		UINT8	ubButton = MSYS_GetBtnUserData(btn);

		switch( ubButton )
		{
			case M_1000:
				if( gRemoveMoney.uiMoneyRemaining >= 1000 )
				{
					//if the player is removing money from their account, and they are removing more then $20,000
					if( gfAddingMoneyToMercFromPlayersAccount &&  ( gRemoveMoney.uiMoneyRemoving + 1000 ) > MAX_MONEY_PER_SLOT )
					{
						if( guiCurrentScreen == SHOPKEEPER_SCREEN )
							DoMessageBox( MSG_BOX_BASIC_STYLE, gzMoneyWithdrawMessageText[ MONEY_TEXT_WITHDRAW_MORE_THEN_MAXIMUM ], SHOPKEEPER_SCREEN, ( UINT8 )MSG_BOX_FLAG_OK, NULL, NULL );
						else
							DoMessageBox( MSG_BOX_BASIC_STYLE, gzMoneyWithdrawMessageText[ MONEY_TEXT_WITHDRAW_MORE_THEN_MAXIMUM ], GAME_SCREEN, ( UINT8 )MSG_BOX_FLAG_OK, NULL, NULL );
						return;
					}

					gRemoveMoney.uiMoneyRemaining -= 1000;
					gRemoveMoney.uiMoneyRemoving += 1000;
				}
				break;
			case M_100:
				if( gRemoveMoney.uiMoneyRemaining >= 100 )
				{
					//if the player is removing money from their account, and they are removing more then $20,000
					if( gfAddingMoneyToMercFromPlayersAccount &&  ( gRemoveMoney.uiMoneyRemoving + 100 ) > MAX_MONEY_PER_SLOT )
					{
						DoMessageBox( MSG_BOX_BASIC_STYLE, gzMoneyWithdrawMessageText[ MONEY_TEXT_WITHDRAW_MORE_THEN_MAXIMUM ], GAME_SCREEN, ( UINT8 )MSG_BOX_FLAG_OK, NULL, NULL );
						return;
					}

					gRemoveMoney.uiMoneyRemaining -= 100;
					gRemoveMoney.uiMoneyRemoving += 100;
				}
				break;
			case M_10:
				if( gRemoveMoney.uiMoneyRemaining >= 10 )
				{
					//if the player is removing money from their account, and they are removing more then $20,000
					if( gfAddingMoneyToMercFromPlayersAccount &&  ( gRemoveMoney.uiMoneyRemoving + 10 ) > MAX_MONEY_PER_SLOT )
					{
						DoMessageBox( MSG_BOX_BASIC_STYLE, gzMoneyWithdrawMessageText[ MONEY_TEXT_WITHDRAW_MORE_THEN_MAXIMUM ], GAME_SCREEN, ( UINT8 )MSG_BOX_FLAG_OK, NULL, NULL );
						return;
					}

					gRemoveMoney.uiMoneyRemaining -= 10;
					gRemoveMoney.uiMoneyRemoving += 10;
				}
				break;
			case M_DONE:
			{
				RemoveMoney();

				DeleteItemDescriptionBox( );
			}
			break;
		}
		if( ubButton != M_DONE )
		{
			RenderItemDescriptionBox( );
			for( i=0; i<MAX_ATTACHMENTS; i++ )
			{
				MarkAButtonDirty( guiMoneyButtonBtn[ i ] );
			}
		}
	}


	if(reason & MSYS_CALLBACK_REASON_RBUTTON_UP )
	{
		UINT8	ubButton = MSYS_GetBtnUserData(btn);

		btn->uiFlags &= (~BUTTON_CLICKED_ON );


		switch( ubButton )
		{
			case M_1000:
				if( gRemoveMoney.uiMoneyRemoving >= 1000 )
				{
					gRemoveMoney.uiMoneyRemaining += 1000;
					gRemoveMoney.uiMoneyRemoving -= 1000;
				}
				break;
			case M_100:
				if( gRemoveMoney.uiMoneyRemoving >= 100 )
				{
					gRemoveMoney.uiMoneyRemaining += 100;
					gRemoveMoney.uiMoneyRemoving -= 100;
				}
				break;
			case M_10:
				if( gRemoveMoney.uiMoneyRemoving >= 10 )
				{
					gRemoveMoney.uiMoneyRemaining += 10;
					gRemoveMoney.uiMoneyRemoving -= 10;
				}
				break;
		}

		RenderItemDescriptionBox( );
		for( i=0; i<MAX_ATTACHMENTS; i++ )
		{
			MarkAButtonDirty( guiMoneyButtonBtn[ i ] );
		}
	}
}


static void RemoveMoney(void)
{
	if( gRemoveMoney.uiMoneyRemoving != 0 )
	{
		//if we are in the shop keeper interface
		if( guiTacticalInterfaceFlags & INTERFACE_SHOPKEEP_INTERFACE )
		{
			INVENTORY_IN_SLOT InvSlot;

			memset( &InvSlot, 0, sizeof(INVENTORY_IN_SLOT) );

			InvSlot.fActive = TRUE;
			InvSlot.sItemIndex = MONEY;
			InvSlot.bSlotIdInOtherLocation = -1;

			//Remove the money from the money in the pocket
			gpItemDescObject->uiMoneyAmount = gRemoveMoney.uiMoneyRemaining;

				//Create an item to get the money that is being removed
			CreateItem( MONEY, 0, &InvSlot.ItemObject );

			//Set the amount thast is being removed
			InvSlot.ItemObject.uiMoneyAmount = gRemoveMoney.uiMoneyRemoving;
			InvSlot.ubIdOfMercWhoOwnsTheItem = gpItemDescSoldier->ubProfile;

			//if we are removing money from the players account
			if( gfAddingMoneyToMercFromPlayersAccount )
			{
				gpItemDescObject->uiMoneyAmount = gRemoveMoney.uiMoneyRemoving;

				//take the money from the player
				AddTransactionToPlayersBook ( TRANSFER_FUNDS_TO_MERC, gpSMCurrentMerc->ubProfile, GetWorldTotalMin() , -(INT32)( gpItemDescObject->uiMoneyAmount ) );
			}

			gMoveingItem = InvSlot;

			gItemPointer = InvSlot.ItemObject;
			gpItemPointer = &gItemPointer;
			gpItemPointerSoldier = gpSMCurrentMerc;

			// Set mouse
			SetSkiCursor( EXTERN_CURSOR );

			//Restrict the cursor to the proper area
			RestrictSkiMouseCursor();
		}
		else
		{
			CreateMoney( gRemoveMoney.uiMoneyRemoving, &gItemPointer );
			gpItemPointer = &gItemPointer;
			//Asign the soldier to be the currently selected soldier
			gpItemPointerSoldier = gpItemDescSoldier;

			//Remove the money from the money in the pocket
			//if we are removing money from the players account
			if( gfAddingMoneyToMercFromPlayersAccount )
			{
				gpItemDescObject->uiMoneyAmount = gRemoveMoney.uiMoneyRemoving;

				//take the money from the player
				AddTransactionToPlayersBook ( TRANSFER_FUNDS_TO_MERC, gpSMCurrentMerc->ubProfile, GetWorldTotalMin() , -(INT32)( gpItemDescObject->uiMoneyAmount ) );
			}
			else
				gpItemDescObject->uiMoneyAmount = gRemoveMoney.uiMoneyRemaining;



			if( guiCurrentItemDescriptionScreen == MAP_SCREEN )
			{
				// Set mouse
				guiExternVo = GetInterfaceGraphicForItem( &(Item[ gpItemPointer->usItem ]) );
				gusExternVoSubIndex = Item[ gpItemPointer->usItem ].ubGraphicNum;

				MSYS_ChangeRegionCursor( &gMPanelRegion , EXTERN_CURSOR );
				MSYS_SetCurrentCursor( EXTERN_CURSOR );
				fMapInventoryItem=TRUE;
				fTeamPanelDirty=TRUE;
			}

		}
	}

//	if( gfAddingMoneyToMercFromPlayersAccount )
//		gfAddingMoneyToMercFromPlayersAccount = FALSE;
}


void GetHelpTextForItem(wchar_t* pzStr, size_t Length, const OBJECTTYPE* pObject, const SOLDIERTYPE* pSoldier)
{
	wchar_t								pStr[ 250 ];
	UINT16								usItem = pObject->usItem;
	INT32									cnt = 0;
	INT32									iNumAttachments = 0;

	if( pSoldier != NULL )
	{
		if ( pSoldier->uiStatusFlags & SOLDIER_DEAD )
		{
			wcslcpy(pzStr, L"", Length);
			return;
		}
	}

	if ( usItem == MONEY )
	{
		SPrintMoney(pStr, pObject->uiMoneyAmount);
	}
	else if ( Item[ usItem ].usItemClass == IC_MONEY )
	{ // alternate money like silver or gold
		wchar_t pStr2[20];
		SPrintMoney(pStr2, pObject->uiMoneyAmount);
		swprintf( pStr, lengthof(pStr), L"%ls (%ls)", ItemNames[ usItem ], pStr2 );
	}
	else if ( usItem != NOTHING )
	{
		if ( !gGameOptions.fGunNut && Item[ usItem ].usItemClass == IC_GUN && usItem != ROCKET_LAUNCHER && usItem != ROCKET_RIFLE )
		{
			swprintf( pStr, lengthof(pStr), L"%ls (%ls)", ItemNames[ usItem ], AmmoCaliber[ Weapon[ usItem ].ubCalibre ] );
		}
		else
		{
			wcslcpy(pStr, ItemNames[usItem], lengthof(pStr));
		}

		if ( ( pObject->usItem == ROCKET_RIFLE || pObject->usItem == AUTO_ROCKET_RIFLE ) && pObject->ubImprintID < NO_PROFILE )
		{
			wchar_t pStr2[20];
			swprintf( pStr2, lengthof(pStr2), L" [%ls]", gMercProfiles[ pObject->ubImprintID ].zNickname );
			wcscat( pStr, pStr2 );
		}

		// Add attachment string....
		for ( cnt = 0; cnt < MAX_ATTACHMENTS; cnt++ )
		{
			if ( pObject->usAttachItem[ cnt ] != NOTHING )
			{
				iNumAttachments++;

				if ( iNumAttachments == 1 )
				{
					wcscat( pStr, L" ( " );
				}
				else
				{
					wcscat( pStr, L", \n" );
				}

				wcscat( pStr, ItemNames[ pObject->usAttachItem[ cnt ] ] );
			}
		}

		if ( iNumAttachments > 0 )
		{
			wcscat( pStr, pMessageStrings[ MSG_END_ATTACHMENT_LIST ] );
		}
	}
	else
	{
		wcslcpy(pStr, L"", lengthof(pStr));
	}

	// Copy over...
	wcslcpy(pzStr, pStr, Length);
}


static UINT8 GetPrefferedItemSlotGraphicNum(UINT16 usItem)
{
	// Check for small item...
	if ( Item[usItem].ubPerPocket >= 1 )
	{
		// Small
		return( 2 );
	}

	// Now it could be large or armour, check class...
	if ( Item[ usItem ].usItemClass == IC_ARMOUR )
	{
		return( 1 );
	}

	// OK, it's a big one...
	return( 0 );
}


void CancelItemPointer( )
{
	// ATE: If we have an item pointer end it!
	if ( gpItemPointer != NULL )
	{
		if ( gbItemPointerSrcSlot != NO_SLOT )
		{
			// Place it back in our hands!
			PlaceObject( gpItemPointerSoldier, gbItemPointerSrcSlot, gpItemPointer );

      // ATE: This could potnetially swap!
      // Make sure # of items is 0, if not, auto place somewhere else...
      if ( gpItemPointer->ubNumberOfObjects > 0 )
      {
				if ( !AutoPlaceObject( gpItemPointerSoldier, gpItemPointer, FALSE ) )
        {
          // Alright, place of the friggen ground!
			    AddItemToPool( gpItemPointerSoldier->sGridNo, gpItemPointer, 1, gpItemPointerSoldier->bLevel, 0 , -1 );
			    NotifySoldiersToLookforItems( );
        }
      }
		}
		else
		{
			// We drop it here.....
			AddItemToPool( gpItemPointerSoldier->sGridNo, gpItemPointer, 1, gpItemPointerSoldier->bLevel, 0 , -1 );
			NotifySoldiersToLookforItems( );
		}
		EndItemPointer( );
	}
}


typedef struct
{
	OBJECTTYPE	ItemPointerInfo;
	UINT8				ubSoldierID;
	UINT8				ubInvSlot;
	BOOLEAN			fCursorActive;
	INT8				bPadding[5];

} ITEM_CURSOR_SAVE_INFO;


BOOLEAN LoadItemCursorFromSavedGame( HWFILE hFile )
{
	UINT32	uiLoadSize=0;
	ITEM_CURSOR_SAVE_INFO		SaveStruct;

	// Load structure
	uiLoadSize = sizeof( ITEM_CURSOR_SAVE_INFO );
	if (!FileRead(hFile, &SaveStruct, uiLoadSize)) return FALSE;

	// Now set things up.....
	// Copy object
	gItemPointer = SaveStruct.ItemPointerInfo;

	// Copy soldier ID
	if ( SaveStruct.ubSoldierID == NOBODY )
	{
		gpItemPointerSoldier = NULL;
	}
	else
	{
		gpItemPointerSoldier = MercPtrs[ SaveStruct.ubSoldierID ];
	}

	// Inv slot
	gbItemPointerSrcSlot = SaveStruct.ubInvSlot;

	// Boolean
	if ( SaveStruct.fCursorActive )
	{
		gpItemPointer = &( gItemPointer );
		ReEvaluateDisabledINVPanelButtons( );
	}
	else
	{
		gpItemPointer = NULL;
	}

	return( TRUE );
}

BOOLEAN SaveItemCursorToSavedGame( HWFILE hFile )
{
	UINT32	uiSaveSize=0;

	ITEM_CURSOR_SAVE_INFO		SaveStruct;

	// Setup structure;
	memset( &SaveStruct, 0, sizeof( ITEM_CURSOR_SAVE_INFO ) );
	SaveStruct.ItemPointerInfo = gItemPointer;

	// Soldier
	if ( gpItemPointerSoldier != NULL )
	{
		SaveStruct.ubSoldierID = gpItemPointerSoldier->ubID;
	}
	else
	{
		SaveStruct.ubSoldierID = NOBODY;
	}

	// INv slot
	SaveStruct.ubInvSlot = gbItemPointerSrcSlot;

	// Boolean
	if ( gpItemPointer != NULL )
	{
		SaveStruct.fCursorActive = TRUE;
	}
	else
	{
		SaveStruct.fCursorActive = FALSE;
	}

	// save locations of watched points
	uiSaveSize = sizeof( ITEM_CURSOR_SAVE_INFO );
	if (!FileWrite(hFile, &SaveStruct, uiSaveSize)) return FALSE;

	// All done...

	return( TRUE );
}



void UpdateItemHatches()
{
	SOLDIERTYPE *pSoldier = NULL;

  if ( guiTacticalInterfaceFlags & INTERFACE_MAPSCREEN )
  {
		if ( fShowInventoryFlag && bSelectedInfoChar >= 0 )
		{
			pSoldier = MercPtrs[ gCharactersList[ bSelectedInfoChar ].usSolID ];
		}
	}
	else
	{
		pSoldier = gpSMCurrentMerc;
	}

	if ( pSoldier != NULL )
	{
		ReevaluateItemHatches( pSoldier, ( BOOLEAN ) ( gpItemPointer == NULL ) );
	}
}
