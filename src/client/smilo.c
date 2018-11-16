#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdlib.h>
#include "../../inc/common/http.h"
#include "../../inc/client/smilo.h"

int clientPort = 8090;

void CL_Smilo_Connected(char* id, char* contractAddress, int playfee) {
    printf("Client connected! Notifying Smilo Client Agent...\n");

    printf("Playfee: %d \n", playfee);

    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/client/participate?contractaddress=%s&playfee=%d";
    sprintf(url, urlTemplate, contractAddress, playfee);

    printf("URL: %s \n", url);

    char response[4096];
    if(HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response))) {
        printf("  Agent response: %s\n", response);
    }
    else {
        printf("Failed to do HTTP call...\n");
    }
}

int CL_Smilo_GetBalance(char* publickey) {
    printf("Get client balance!\n");

    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/client/balance?publickey=%s";
    sprintf(url, urlTemplate, publickey);

    char response[4096];
    if(HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response))) {
        printf("  Agent response: %s\n", response);
        return atoi(response);
    }
    else {
        printf("Failed to do HTTP call...\n");
        return 0;
    }
}

int CL_Smilo_GetPublicKey(char* buffer, int bufferSize) {
    printf("Get client publickey!\n");

    // Notify Smilo server agent
    char response[4096];
    if(HTTP_Get("127.0.0.1", "v1/client/publickey", clientPort, response, sizeof(response))) {
        printf("  Agent response: %s\n", response);
        
        // Copy response in buffer
        strncpy(buffer, response, bufferSize);

        return 1;
    }
    else {
        printf("Failed to do HTTP call...\n");
        return 0;
    }
}

int CL_Smilo_BetConfirmed(char* publickey, char* contractaddress) {
    printf("Checking if bet is confirmed for publickey: %s\n", publickey);

    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/client/betconfirmed?publickey=%s&contractaddress=%s";
    sprintf(url, urlTemplate, publickey, contractaddress);

    printf("Checking URL: %s \n", url);

    // Notify Smilo server agent
    char response[4096];
    if(HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response))) {
        printf("  Agent response: %s\n", response);
        if (!strcmp(response, "true")) {
            printf("  BET CONFIRMED: 1! \n");
            return 1;
        } else {
            printf("  BET CONFIRMED: 0! \n");
            return 0;
        }
    }
    else {
        printf("Failed to do HTTP call...\n");
        return 0;
    }
}

int CL_Smilo_Get_Validated_Player_Count(char* contractaddress) {
    printf("Get player count!\n");

    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/client/validatedPlayersCount?contractaddress=%s";
    sprintf(url, urlTemplate, contractaddress);

    printf("Validated URL: %s \n", url);

    char response[4096];
    if(HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response))) {
        printf("  Agent response: %s\n", response);
        return atoi(response);
    }
    else {
        printf("Failed to do HTTP call...\n");
        return 0;
    }
}

int CL_Smilo_GameInfo(smilo_game_info* output) {
    printf("Retrieving game info...\n");

    char response[4096];
    if(HTTP_Get("127.0.0.1", "v1/client/gamedetails", 8090, response, sizeof(response))) {
        printf("  Agent response: %s\n", response);

        // Line formatting
        // line 1: input amount
        // line 2: validated contract ('true' or 'false')
        // line 3, 4 and 5: first, second and third place rewards
        int index = 0;
        for(char* p = strtok(response, ","); p != NULL; p = strtok(NULL, ",")) {
            printf("Read line: %s\n", p);
            switch(index) {
                case(0):
                    output->input_amount = strtol(p, (char **)NULL, 10);
                    break;
                case(1):
                    output->valid_smart_contract = strcmp(p, "true") ? 0 : 1;
                    break;
                case(2):
                    output->payout_amounts[0] = strtol(p, (char **)NULL, 10);
                    break;
                case(3):
                    output->payout_amounts[1] = strtol(p, (char **)NULL, 10);
                    break;
                case(4):
                    output->payout_amounts[2] = strtol(p, (char **)NULL, 10);
                    break;
            }

            if(index == 5)
                break;

            index++;
        }

        // Incomplete response
        if(index < 5)
            return 0;

        return 1;
    }
    else {
        printf("Failed to do HTTP call...\n");
        return 0;
    }
}
