;******************************************************************************
;*                                                                            *
;*       Source title: bowplus.spec                                           *
;*                                                                            *
;*         Written by: Xina Fu                                                *
;*                                                                            *
;*        Description: SPEC initialization file                               *
;*                                                                            *
;******************************************************************************

; parameters common to all device versions
;*****************************************
[NU1682]
PT_PROG		    = 1682

VRECT			= 5.5V
V5V			    = 5  V
ENB			    = 5  V

Num_VoltageTable    = 3
;temperature characterization values
;[Voltage_Tempchar]
V5V_CHAR	= 0:3.3  V,
			  1:5    V,
			  2:5.5  V,

VRECT_CHAR	= 0:5.2    V,
			  1:6.2    V,
			  2:7      V,

ENB_CHAR	= 0:1.8    V,
			  1:3.3    V,
			  2:5      V,

Num_Temperature_Table   = 7
;temperature characterization values
;[Temperature_Tempchar]
Temperature 	= 0:-40  C,
			      1:-20  C,
				  2: 0   C,
				  3: 25  C
				  4: 85  C
				  5: 100 C
				  6: 125 C


[NU1685]
PT_PROG		    = 1685

VRECT			= 5.5V
V5V			    = 5  V
ENB			    = 5  V

Num_VoltageTable    = 3
;temperature characterization values
;[Voltage_Tempchar]
V5V_CHAR	= 0:3.3  V,
			  1:5    V,
			  2:5.5  V,

VRECT_CHAR	= 0:5.2    V,
			  1:6.2    V,
			  2:7      V,

ENB_CHAR	= 0:1.8    V,
			  1:3.3    V,
			  2:5      V,

Num_Temperature_Table   = 7
;temperature characterization values
;[Temperature_Tempchar]
Temperature 	= 0:-40  C,
			      1:-20  C,
				  2: 0   C,
				  3: 25  C
				  4: 85  C
				  5: 100 C
				  6: 125 C


[NU1687]
PT_PROG		    = 1687

VRECT			= 5.5V
V5V			    = 5  V
ENB			    = 5  V

Num_VoltageTable    = 3
;temperature characterization values
;[Voltage_Tempchar]
V5V_CHAR	= 0:3.3  V,
			  1:5    V,
			  2:5.5  V,

VRECT_CHAR	= 0:5.2    V,
			  1:6.2    V,
			  2:7      V,

ENB_CHAR	= 0:1.8    V,
			  1:3.3    V,
			  2:5      V,

Num_Temperature_Table   = 7
;temperature characterization values
;[Temperature_Tempchar]
Temperature 	= 0:-40  C,
			      1:-20  C,
				  2: 0   C,
				  3: 25  C
				  4: 85  C
				  5: 100 C
				  6: 125 C


[NU1682A]
PT_PROG		    = 16821

VRECT			= 5.5V
V5V			    = 5  V
ENB			    = 5  V

Num_VoltageTable    = 3
;temperature characterization values
;[Voltage_Tempchar]
V5V_CHAR	= 0:3.3  V,
			  1:5    V,
			  2:5.5  V,

VRECT_CHAR	= 0:5.2    V,
			  1:6.2    V,
			  2:7      V,

ENB_CHAR	= 0:1.8    V,
			  1:3.3    V,
			  2:5      V,

Num_Temperature_Table   = 7
;temperature characterization values
;[Temperature_Tempchar]
Temperature 	= 0:-40  C,
			      1:-20  C,
				  2: 0   C,
				  3: 25  C
				  4: 85  C
				  5: 100 C
				  6: 125 C