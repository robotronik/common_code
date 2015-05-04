#include "s2a.h"

char *s2a_keys[S2A_SIZE] = {
    [S2A_KEY_X]            = "x=",
    [S2A_KEY_Y]            = "y=",
    [S2A_KEY_ALPHA]        = "alpha=",
    [S2A_KEY_DELTA]        = "delta=",
    [S2A_KEY_THETA]        = "theta=",
    [S2A_KEY_KP_DELTA]     = "KPd=",
    [S2A_KEY_KD_DELTA]     = "KDd=",
    [S2A_KEY_KP_ALPHA]     = "KPa=",
    [S2A_KEY_KD_ALPHA]     = "KDa=",

    [S2A_CMD_QUIT]         = "q",
    [S2A_CMD_HELP]         = "?",
    [S2A_CMD_GET_POS]      = "get_pos()",
    [S2A_CMD_EMERGENCY_STOP] = "estop",
    [S2A_CMD_STOP]         = "stop",

    [S2A_FCT_ALPHA_DELTA]  = "alpha_delta()",
    [S2A_FCT_XY_RELATIF]   = "xy_relatif()",
    [S2A_FCT_XY_ABSOLU]    = "xy_absolu()",
    [S2A_FCT_THETA]        = "theta()",
    [S2A_FCT_ADD]          = "add()",
    [S2A_FCT_CHEMIN]       = "chemin()",
    [S2A_FCT_CLEAR]        = "clear()",
    [S2A_FCT_UPDATE]       = "update()",
    [S2A_FCT_MODE_TENDU]   = "mode(tendu)",
    [S2A_FCT_MODE_COURBE]  = "mode(courbe)",
    [S2A_FCT_SET_POS]      = "set_pos()",
    [S2A_FCT_SET_PID]      = "change_pid()",
};