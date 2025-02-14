import uiScriptLocale
SUPPORT_DIRECTORY = "d:/ymir work/ui/support/"

MINI_WINDOW_WIDTH	= 130
MINI_WINDOW_HEIGHT	= 44

## EXP Gague interval
EXP_GAGUE_INTERVAL	= 2
EXP_GAGUE_SCALE		= 0.8
EXP_IMG_WIDTH		= 16 * EXP_GAGUE_SCALE
EXP_IMG_HEIGHT		= 16 * EXP_GAGUE_SCALE

window = {
	"name" : "SupportMiniInformationWindow",
	"style" : ("movable", "float",),
	
	"x" : 10,
	"y" : SCREEN_HEIGHT - 225,

	"width" : MINI_WINDOW_WIDTH,
	"height" : MINI_WINDOW_HEIGHT,
	
	"children" :
	(
		## Pet Mini Information Window Back Ground
		{
			"name" : "main_bg",
			"type" : "expanded_image",
			"style" : ("attach",),

			"x" : 0,
			"y" : 0,
			
			"image" : "d:/ymir work/ui/pet/mini_window/pet_mini_info_back.sub",

			"width" : MINI_WINDOW_WIDTH,
			"height" : MINI_WINDOW_HEIGHT,
		},
		{
			"name" : "main_bg2",
			"type" : "image",
			"style" : ("attach",),
			"x" : 36,
			"y" : 0,
			"image" : SUPPORT_DIRECTORY+"exp.tga",
		},
		{
			"name" : "job_name",
			"type" : "text",
			"x" : 55,
			"y" : 2,
			"fontname": "Tahoma:17",
			"text":"",
		},
		## Icon Slot
		{
			"name" : "icon_base",
			"type" : "window",
			"style" : ("attach",),
			
			"x" : 0,
			"y" : 0,
			
			"width" : 32 + 3,
			"height" : MINI_WINDOW_HEIGHT,
			
			"children" :
			(
				## Main Slot
				{
					"name" : "pet_icon_slot",
					"type" : "slot",
					#"style" : ("attach",),

					"x" : 3,
					"y" : 6,
					"width"	: 35,
					"height" : MINI_WINDOW_HEIGHT,
					"slot" : ({"index":0, "x":0, "y":0, "width":32, "height":32,},),
				},
				
				## Main Slot Effect
				{
					"name" : "pet_icon_slot_ani_img",
					"type" : "ani_image",
					"style" : ("attach",),
					
					"x" : 3,
					"y" : 3,
					
					"delay" : 6,

					"images" :
					(
						"D:/Ymir Work/UI/pet/mini_window/main_slot_effect/main_slot_effect1.sub",
						"D:/Ymir Work/UI/pet/mini_window/main_slot_effect/main_slot_effect2.sub",
						"D:/Ymir Work/UI/pet/mini_window/main_slot_effect/main_slot_effect3.sub",
						"D:/Ymir Work/UI/pet/mini_window/main_slot_effect/main_slot_effect4.sub",
						"D:/Ymir Work/UI/pet/mini_window/main_slot_effect/main_slot_effect5.sub",
						"D:/Ymir Work/UI/pet/mini_window/main_slot_effect/main_slot_effect6.sub",
						"D:/Ymir Work/UI/pet/mini_window/main_slot_effect/main_slot_effect6.sub",
						"D:/Ymir Work/UI/pet/mini_window/main_slot_effect/main_slot_effect6.sub",
						"D:/Ymir Work/UI/pet/mini_window/main_slot_effect/main_slot_effect5.sub",
						"D:/Ymir Work/UI/pet/mini_window/main_slot_effect/main_slot_effect4.sub",
						"D:/Ymir Work/UI/pet/mini_window/main_slot_effect/main_slot_effect3.sub",
						"D:/Ymir Work/UI/pet/mini_window/main_slot_effect/main_slot_effect2.sub",
						"D:/Ymir Work/UI/pet/mini_window/main_slot_effect/main_slot_effect1.sub",
					),
				},
			),
		},
		{
			"name" : "UpBringing_Support_EXP_Gauge_Board",
			"type" : "window",
			"style": ("ltr",),

			"x" : 45,
			"y" : 23,

			"width"		: EXP_IMG_WIDTH * 5 + EXP_GAGUE_INTERVAL * 4,
			"height"	: EXP_IMG_HEIGHT,

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

					"x" : (18*1),
					"y" : 0,

					"image" : SUPPORT_DIRECTORY + "exp_gauge/exp_on.sub",
				},
				{
					"name" : "UpBringing_Support_EXPGauge_2",
					"type" : "expanded_image",

					"x" : (18*2)+2,
					"y" : 0,

					"image" : SUPPORT_DIRECTORY + "exp_gauge/exp_on.sub",
				},
				{
					"name" : "UpBringing_Support_EXPGauge_3",
					"type" : "expanded_image",

					"x" : (18*3)+4,
					"y" : 0,

					"image" : SUPPORT_DIRECTORY + "exp_gauge/exp_on.sub",
				},
			),
		}, 
	),
}
