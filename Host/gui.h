//*******************
// Color Definition 
#define R_FOND 0
#define V_FOND 0
#define B_FOND 0

#define R_TEXT 128
#define V_TEXT 90
#define B_TEXT 200

#define R_ONGLET 0
#define V_ONGLET 0
#define B_ONGLET 128

#define R_CHECK 0
#define V_CHECK 0
#define B_CHECK 128

#define R_CHECK_CROSS 0
#define V_CHECK_CROSS 100
#define B_CHECK_CROSS 50

#define R_INTERNAL 160
#define V_INTERNAL 100
#define B_INTERNAL 200

#define R_JOG 150
#define V_JOG 100
#define B_JOG 150

#define R_TEXT_BOX 70
#define V_TEXT_BOX 70
#define B_TEXT_BOX 130


#define R_BUTTON 80
#define V_BUTTON 90
#define B_BUTTON 80

#define R_TEXT_BUTTON 128
#define V_TEXT_BUTTON 90
#define B_TEXT_BUTTON 210

//*******************
// Tab definition 
#define TAB_JOG 0
#define TAB_TEMP 1
#define TAB_GCODE 2

#define X_START_JOG 0 
#define Y_START_JOG 0 
#define X_END_JOG 3*8+3
#define Y_END_JOG 16

#define X_START_TEMP 3*8+3
#define Y_START_TEMP 0 
#define X_END_TEMP 3*8+3+4*8+3
#define Y_END_TEMP 16

#define X_START_GCODE 3+3*8+3+4*8
#define Y_START_GCODE 0
#define X_END_GCODE 3*8+3+4*8+3+5*8+3
#define Y_END_GCODE 16

//*******************
// Jog definition Y
#define X_START_JOG_YP100 70
#define Y_START_JOG_YP100 30
#define X_END_JOG_YP100 150
#define Y_END_JOG_YP100 66

#define X_START_JOG_YP10 82
#define Y_START_JOG_YP10 70
#define X_END_JOG_YP10 140
#define Y_END_JOG_YP10 95

#define X_START_JOG_YP1 95
#define Y_START_JOG_YP1 94
#define X_END_JOG_YP1 129
#define Y_END_JOG_YP1 106

#define X_START_JOG_YM1 98
#define Y_START_JOG_YM1 144
#define X_END_JOG_YM1 126
#define Y_END_JOG_YM1 161

#define X_START_JOG_YM10 82
#define Y_START_JOG_YM10 Y_END_JOG_YM1
#define X_END_JOG_YM10 140
#define Y_END_JOG_YM10 184

#define X_START_JOG_YM100 78
#define Y_START_JOG_YM100 Y_END_JOG_YM10
#define X_END_JOG_YM100 162
#define Y_END_JOG_YM100 224

//*******************
// Jog definition X
#define X_START_JOG_XP100 175
#define Y_START_JOG_XP100 84
#define X_END_JOG_XP100 200
#define Y_END_JOG_XP100 180

#define X_START_JOG_XP10 143
#define Y_START_JOG_XP10 100
#define X_END_JOG_XP10  X_START_JOG_XP100
#define Y_END_JOG_XP10 164

#define X_START_JOG_XP1 122
#define Y_START_JOG_XP1 111
#define X_END_JOG_XP1  140
#define Y_END_JOG_XP1 145

#define X_START_JOG_XM1 80
#define Y_START_JOG_XM1 107
#define X_END_JOG_XM1  102
#define Y_END_JOG_XM1 145

#define X_START_JOG_XM10 52
#define Y_START_JOG_XM10 99
#define X_END_JOG_XM10  80
#define Y_END_JOG_XM10 155

#define X_START_JOG_XM100 19
#define Y_START_JOG_XM100 83
#define X_END_JOG_XM100  47
#define Y_END_JOG_XM100 170

//*******************
// Jog definition Z
#define X_START_JOG_ZP10 212
#define Y_START_JOG_ZP10 36
#define X_END_JOG_ZP10 265
#define Y_END_JOG_ZP10 67

#define X_START_JOG_ZP1 212
#define Y_START_JOG_ZP1 67
#define X_END_JOG_ZP1 265
#define Y_END_JOG_ZP1 95

#define X_START_JOG_ZM1 212
#define Y_START_JOG_ZM1 161
#define X_END_JOG_ZM1 265
#define Y_END_JOG_ZM1 192

#define X_START_JOG_ZM10 212
#define Y_START_JOG_ZM10 192
#define X_END_JOG_ZM10 265
#define Y_END_JOG_ZM10 222

//*******************
// Home definition
#define X_START_HOME_Y 16
#define Y_START_HOME_Y 38
#define X_END_HOME_Y X_START_HOME_Y+22
#define Y_END_HOME_Y Y_START_HOME_Y+19

#define X_START_HOME_Z 163
#define Y_START_HOME_Z 38
#define X_END_HOME_Z X_START_HOME_Z+22
#define Y_END_HOME_Z Y_START_HOME_Z+19

#define X_START_HOME_X 16
#define Y_START_HOME_X 196
#define X_END_HOME_X X_START_HOME_X+22
#define Y_END_HOME_X Y_START_HOME_X+19

#define X_START_HOME_ALL 173
#define Y_START_HOME_ALL 196
#define X_END_HOME_ALL X_START_HOME_ALL+22
#define Y_END_HOME_ALL Y_START_HOME_ALL+19