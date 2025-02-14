import uiScriptLocale

ROOT_PATH = "d:/ymir work/ui/game/windows/"
ROOT = "d:/ymir work/ui/game/"
SUPPORT_DIRECTORY = "d:/ymir work/ui/support/"
SMALL_VALUE_FILE = "d:/ymir work/ui/public/Parameter_Slot_00.sub"
MIDDLE_VALUE_FILE = "d:/ymir work/ui/public/Parameter_Slot_01.sub"
LARGE_VALUE_FILE = "d:/ymir work/ui/public/Parameter_Slot_03.sub"
XLARGE_BUTTON_FILE = "d:/ymir work/ui/public/xlarge_button_03.sub"
BASE_SLOT_FILE = "d:/ymir work/ui/public/Slot_Base.sub"

SUPPORT_BG_WIDTH		= 352
SUPPORT_BG_HEIGHT	= 143

LONG_LABEL_WIDTH	= 266
LONG_LABEL_HEIGHT	= 19

SHORT_LABLE_WIDTH	= 90
SHORT_LABLE_HEIGHT	= 20

MIDDLE_LABLE_WIDTH	= 168
MIDDLE_LABLE_HEIGHT	= 20

EXP_GAGUE_INTERVAL	= 2
EXP_IMG_WIDTH		= 16
EXP_IMG_HEIGHT		= 16

GOLD_COLOR	= 0xFFFEE3AE
WHITE_COLOR = 0xFFFFFFFF
ORANGE_COLOR = 0xFFF2A505
	
window = {
	"name" : "SupportInformationWindow",
	"style" : ("movable", "float",),
	
	"x" : SCREEN_WIDTH - 176 -200 -146 -145,
	"y" : SCREEN_HEIGHT - 37 - 565,

	"width" : SUPPORT_BG_WIDTH,
	"height" : SUPPORT_BG_HEIGHT,

	"children" :
	(
		{
			"name" : "board",
			"type" : "window",

			"x" : 0,
			"y" : 0,

			"width" : SUPPORT_BG_WIDTH,
			"height" : SUPPORT_BG_HEIGHT,
			
			"children" :
			(
				## Support UI BG
				{ "name" : "PetUIBG", "type" : "expanded_image", "style" : ("attach",), "x" : 0, "y" : 0, "image" : "d:/ymir work/ui/support/support_bg.tga" },
				{
					"name" : "SlotSupportImage",
					"type" : "slot",
					"x" : 25,
					"y" : 100,
					"width" : 32,
					"height" : 32,
					"slot" : ({"index":0, "x":0, "y":0, "width":32, "height":32},),
				},
				## Support Information Title
				{ 
					"name" : "TitleWindow", "type" : "window", "x" : 10, "y" : 7, "width" : SUPPORT_BG_WIDTH-10-15, "height" : 15, "style" : ("attach",),
					"children" :
					(
						{"name":"TitleName", "type":"text", "x":0, "y":0, "text":uiScriptLocale.SUPPORTWND_TITLE, "all_align" : "center"},
					),
				},
				
				## Close Button
				{ 
					"name" : "CloseButton", 
					"type" : "button", 
					"x" : SUPPORT_BG_WIDTH -10-15, 
					"y" : 7, 
					"tooltip_text" : "Pencereyi Kapat", 
					"default_image" : "d:/ymir work/ui/public/close_button_01.sub",	
					"over_image" : "d:/ymir work/ui/public/close_button_02.sub",
					"down_image" : "d:/ymir work/ui/public/close_button_03.sub",
				},

				## Level Title
				{ 
					"name" : "LevelWindow", "type" : "window", "x" : 20, "y" : 30, "width" : SHORT_LABLE_WIDTH, "height" : SHORT_LABLE_HEIGHT, "style" : ("attach",),
					"children" :
					(
						{"name":"LevelTitle", "type":"text", "x":0, "y":0, "text": uiScriptLocale.SUPPORTWND_LEVEL, "color":GOLD_COLOR, "all_align" : "center"},
					),	
				},
				## Level Value
				{ 
					"name" : "LevelValueWindow", "type" : "window", "x" : 20, "y" : 50, "width" : SHORT_LABLE_WIDTH, "height" : SHORT_LABLE_HEIGHT, "style" : ("attach",),
					"children" :
					(
						{"name":"LevelValue", "type":"text", "x":0, "y":0, "text": "", "color":WHITE_COLOR, "all_align" : "center"},
					),	
				},
				## Specialita Title
				{ 
					"name" : "SpecialityWindow", "type" : "window", "x" : 120, "y" : 30, "width" : SHORT_LABLE_WIDTH, "height" : SHORT_LABLE_HEIGHT, "style" : ("attach",),
					"children" :
					(
						{"name":"SpecialityTitle", "type":"text", "x":0, "y":0, "text": uiScriptLocale.SUPPORTWND_CBEC, "color":GOLD_COLOR, "all_align" : "center"},
					),	
				},
				## Speciality Value
				{ 
					"name" : "SpecialityValueWindow", "type" : "window", "x" : 120, "y" : 50, "width" : SHORT_LABLE_WIDTH, "height" : SHORT_LABLE_HEIGHT, "style" : ("attach",),
					"children" :
					(
						{"name":"SpecialityValue", "type":"text", "x":0, "y":0, "text": "", "color":WHITE_COLOR, "all_align" : "center"},
					),
				},
				## EXP Title
				{ 
					"name" : "ExpWindow", "type" : "window", "x" : 220, "y" : 30, "width" : SHORT_LABLE_WIDTH, "height" : SHORT_LABLE_HEIGHT, "style" : ("attach",),
					"children" :
					(
						{"name":"ExpTitle", "type":"text", "x":0, "y":0, "text": uiScriptLocale.SUPPORTWND_CTECRUBE, "color":GOLD_COLOR, "all_align" : "center"},
					),	
				},
				## EXP Gauge
				{
					"name" : "UpBringing_Support_EXP_Gauge_Board",
					"type" : "window",
					"style": ("ltr",),

					"x" : 232,
					"y" : 54,
				
					"width"		: 72,
					"height"	: 13,

					"children" :
					(
						{
							"name" : "UpBringing_Support_EXPGauge_0",
							"type" : "expanded_image",

							"x" : 0,
							"y" : 0,

							"image" : SUPPORT_DIRECTORY + "exp_gauge/exp_on.sub",
						},
						{
							"name" : "UpBringing_Support_EXPGauge_1",
							"type" : "expanded_image",

							"x" : EXP_IMG_WIDTH + EXP_GAGUE_INTERVAL + 1,
							"y" : 0,

							"image" : SUPPORT_DIRECTORY + "exp_gauge/exp_on.sub",
						},
						{
							"name" : "UpBringing_Support_EXPGauge_2",
							"type" : "expanded_image",

							"x" : EXP_IMG_WIDTH * 2 + EXP_GAGUE_INTERVAL * 2 + 3,
							"y" : 0,

							"image" : SUPPORT_DIRECTORY + "exp_gauge/exp_on.sub",
						},
						{
							"name" : "UpBringing_Support_EXPGauge_3",
							"type" : "expanded_image",

							"x" : EXP_IMG_WIDTH * 3 + EXP_GAGUE_INTERVAL * 3 + 4,
							"y" : 0,

							"image" : SUPPORT_DIRECTORY + "exp_gauge/exp_on.sub",
						},
					),
				}, 
				#End of EXP
				{ 
					"name" : "AbilitiesWindow", "type" : "window", "x" : 60, "y" : 75, "width" : LONG_LABEL_WIDTH, "height" : LONG_LABEL_HEIGHT, "style" : ("attach",),
					"children" :
					(
						{"name":"AbilitiesName", "type":"text", "x":0, "y":0, "text": uiScriptLocale.SUPPORTWND_BONUS, "color":ORANGE_COLOR, "all_align" : "center"},
					),	
				},
	
				## Int Title
				{ 
					"name" : "IntWindow", "type" : "window", "x" : 40, "y" : 105, "width" : MIDDLE_LABLE_WIDTH, "height" : MIDDLE_LABLE_HEIGHT, "style" : ("attach",),
					"children" :
					(
						{"name":"IntTitle", "type":"text", "x":0, "y":0, "text": uiScriptLocale.SUPPORTWND_BECINT, "color":GOLD_COLOR, "all_align" : "center"},
					),
				},
				## Int Value
				{ 
					"name" : "IntValueWindow", "type" : "window", "x" : 150, "y" : 105, "width" : MIDDLE_LABLE_WIDTH, "height" : MIDDLE_LABLE_HEIGHT, "style" : ("attach",),
					"children" :
					(
						{"name":"SupportIntValue", "type":"text", "x":0, "y":0, "text": "", "color":WHITE_COLOR, "all_align" : "center"},
					),	
				},
			),			
		},
	),
}
