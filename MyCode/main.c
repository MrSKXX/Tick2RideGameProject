#define JSMN_STATIC  
#include "../tickettorideapi/jsmn.h"
#include "../tickettorideapi/codingGameServer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tickettorideapi/ticketToRide.h"

int main() {
    const char* serverAddress = "82.64.1.174";  // professor's server address
    unsigned int serverPort = 15001;          // port number
    const char* playerName = "Georges";     
    
    printf("Attempting to connect to server at %s:%d\n", serverAddress, serverPort);
    
    // Connect to the server
    ResultCode result = connectToCGS(serverAddress, serverPort);
    if (result != ALL_GOOD) {
        printf("Failed to connect to server. Error code: 0x%x\n", result);
        return 1;
    }
    printf("Successfully connected to server!\n");
    
    // Send player name
    result = sendName(playerName);
    if (result != ALL_GOOD) {
        printf("Failed to send name to server. Error code: 0x%x\n", result);
        return 1;
    }
    printf("Successfully sent player name: %s\n", playerName);
    
    // Configure game settings
    // Configure game settings - try with the most basic/default values
    GameSettings gameSettings = GameSettingsDefaults;

    //essai avec des valeurs precises
    //gameSettings.gameType = 1; // Direct value instead of enum
    //gameSettings.botId = 1;    // Try a different bot
    //gameSettings.timeout = 15; // Use default timeout
    //gameSettings.starter = 1;  // Explicitly set you as starter
    //gameSettings.seed = 123;   // Use a specific seed
    //gameSettings.reconnect = 0;


    // Prepare to receive game data
    GameData gameData = GameDataDefaults;
    
    // Send game settings and get game data
    result = sendGameSettings(gameSettings, &gameData);
    if (result != ALL_GOOD) {
        printf("Failed to send game settings. Error code: 0x%x\n", result);
        return 1;
    }
    
    printf("Successfully started game: %s\n", gameData.gameName);
    printf("Game seed: %d\n", gameData.gameSeed);
    printf("Starter: %d (1 = you, 2 = opponent)\n", gameData.starter);


    result = printBoard();
    if (result != ALL_GOOD) {
        printf("Failed to print board. Error code: 0x%x\n", result);
        return 1;
    }
    



    
    // Clean up allocated memory
    if (gameData.gameName) {
        free(gameData.gameName);
    }
    if (gameData.trackData) {
        free(gameData.trackData);
    }
    


    
    // Quit the game
    quitGame();
    
    return 0;
}