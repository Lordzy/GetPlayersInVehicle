#tryinclude <a_samp>

enum e_VehicleSeatData {

	e_VehiclePlayers[7],
};


static
			g_VehicleSeatData[MAX_VEHICLES][e_VehicleSeatData],
	bool:	g_VehInit = false,
			g_PlayerVehicleID[MAX_PLAYERS];
	

VehicleSeat_Init() {

	for(new i = 0; i< MAX_VEHICLES; i++) {
	
		for(new j = 0; j< 7; j++) {
		
		    g_VehicleSeatData[i][e_VehiclePlayers][j] = INVALID_PLAYER_ID;
		}
	}
	for(new i = 0; i< MAX_PLAYERS; i++)
	    g_PlayerVehicleID[i] = INVALID_VEHICLE_ID;
	    
	return 1;
}

public OnFilterScriptInit() {

	if(!g_VehInit) {
	
		VehicleSeat_Init();
		g_VehInit = true;
	}
	return 1;
}
	
	
public OnGameModeInit() {

	if(!g_VehInit) {
	
	    VehicleSeat_Init();
	    g_VehInit = true;
	}
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate) {

	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER) {
	
	    new
	        temp_VehicleID = GetPlayerVehicleID(playerid);

//		g_VehicleSeatData[temp_VehicleID][e_VehiclePlayers][g_VehicleSeatData[temp_VehicleID][e_VehicleFreeSeatID]++] = playerid;

		for(new i = 0; i< 7; i++)
			if(g_VehicleSeatData[temp_VehicleID][e_VehiclePlayers][i] == INVALID_PLAYER_ID)
			    g_VehicleSeatData[temp_VehicleID][e_VehiclePlayers][i] = playerid;

		g_PlayerVehicleID[playerid] = temp_VehicleID;
	}
	else if((oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) && !IsPlayerInAnyVehicle(playerid)) {

		if(g_PlayerVehicleID[playerid] == INVALID_VEHICLE_ID) return 0;
		for(new i = 0; i< 7; i++) {
		
		    if(g_VehicleSeatData[g_PlayerVehicleID[playerid]][e_VehiclePlayers][i] == playerid) {
		    
		        g_VehicleSeatData[g_PlayerVehicleID[playerid]][e_VehiclePlayers][i] = INVALID_PLAYER_ID;
			}
		}
	}
	return 1;
}


stock GetPlayersInVehicle(vehicleid, players[7]) {

	for(new i = 0; i< 7; i++) {
	
	    players[i] = g_VehicleSeatData[vehicleid][e_VehiclePlayers][i];
	}
	return players;
}

