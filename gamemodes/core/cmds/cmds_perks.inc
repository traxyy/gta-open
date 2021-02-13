#define DIALOG_PERKS 69
#define DIALOG_PERKS_TP 6970

enum
    E_PERKS_DATA
    {
        E_NAME[32],     E_PURPOSE[64],
        E_COST
    }
;

static
    gPerkData[][E_PERKS_DATA] =
    {
        {"Repair Vehicle", "Restores a vehicle's health to 1000", 5000},
        {"Flip Vehicle", "Flips a vehicle back to wheels if it's backflipped", 1000},
        {"Add NOS", "Adds a NOS to vehicle", 4000},
        {"Teleportation", "You can teleport to any player", 1000}
    }
;

CMD:perks(playerid, params[])
{
    new 
        perksStr[256]
    ;

    inline perks(pid, dialogid, response, listitem, string:inputtext[]) {
        #pragma unused pid, dialogid, inputtext
        if(!response) return 1;
        new 
            vehicleid = GetPlayerVehicleID(playerid)
        ;

        switch (listitem)
        {
            case 0: // Repair vehicle
            {
                if(!IsPlayerInAnyVehicle(playerid)) // Somehow left vehicle?
                    return SendErrorMsg(playerid, "You must be in a vehicle to use this feature.");

                RepairVehicle(vehicleid);

                SendMsgF(playerid, -1, "[VEH-FIX] You have fixed your vehicle for {FFDC2E}$%d", gPerkData[listitem][E_COST]);
            }
            case 1: // Flip vehicle
            {
                if(!IsPlayerInAnyVehicle(playerid)) // Somehow left vehicle?
                    return SendErrorMsg(playerid, "You must be in a vehicle to use this feature.");

                new
                    Float:VehZAngle
                ;

                GetVehicleZAngle(vehicleid, VehZAngle);
                SetVehicleZAngle(vehicleid, VehZAngle);

                SendMsgF(playerid, -1,  "[VEH-FLIP] You have flipped your vehicle for {FFDC2E}$%d", gPerkData[listitem][E_COST]);
            }
            case 2: // Add NOS
            {
                if(!IsPlayerInAnyVehicle(playerid)) // Somehow left vehicle?
                    return SendErrorMsg(playerid, "You must be in a vehicle to use this feature.");

                AddVehicleComponent(vehicleid, 1010);

                SendMsgF(playerid, -1, "[VEH-NOS] You have installed NOS your vehicle for {FFDC2E}$%d", gPerkData[listitem][E_COST]);
            }
            case 3: // Teleport
            {
                inline teleportInline(pid2, did, resp, li, string:it[]) {
                    #pragma unused pid2, did, li
                    new
                        id
                    ;

                    if(!resp) return Dialog_ShowCallback(playerid, using inline teleportInline, DIALOG_STYLE_INPUT, "{FFFFFF}Teleport To A Player", "Input a valid player name/id", "Select", "Cancel");

                    if(sscanf(it, "u", id)) {
                        return Dialog_ShowCallback(playerid, using inline teleportInline, DIALOG_STYLE_INPUT, "{FFFFFF}Teleport To A Player", "Input a valid player name/id", "Select", "Cancel");
                    }

                    else if(!IsPlayerConnected(id)) {
                    return SendErrorMsg(playerid, "Invalid Player ID");
                    }

                    else if(GetPlayerWantedLevel(playerid) != 0) {
                        return SendErrorMsg(playerid, "You mustn't be a wanted player to use this perk.");
                    }

                    new Float:x, Float:y, Float:z;
                    new interior = GetPlayerInterior(playerid), vm = GetPlayerVirtualWorld(playerid);
                    GetPlayerPos(id, x, y, z);
                    SetPlayerPos(playerid, x, y, z);
                    SetPlayerInterior(playerid, interior);
                    SetPlayerVirtualWorld(playerid, vm);
                                
                    SendMsgF(playerid, -1, "[PERK-TP] You have successfully teleported to %s", id);
                }
                Dialog_ShowCallback(playerid, using inline teleportInline, DIALOG_STYLE_INPUT, "{FFFFFF}Teleport To A Player", "Input a valid player name/id", "Select", "Cancel");
            }
        }
    }

    for(new i = 0; i < sizeof(gPerkData); i++)
        format(perksStr, sizeof perksStr, "%s%s\t%s\t{FFDC2E}$%d\n", perksStr, gPerkData[i][E_NAME], gPerkData[i][E_PURPOSE], gPerkData[i][E_COST]);

    format(perksStr, sizeof perksStr, "{FFFFFF}Perk\t{FFFFFF}Purpose\t{FFFFFF}Cost\n%s", perksStr);

    Dialog_ShowCallback(playerid, using inline perks, DIALOG_STYLE_TABLIST_HEADERS, "Player Perks", perksStr, "Choose", "Close");
    return 1;    
}