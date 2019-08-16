#include "../../src/client/gamedetails.h"

void CL_Smilo_Connected(char* contractAddress, char* buffer, int buffersize);
void CL_Smilo_SetPublicKey();
int CL_Smilo_GetBalance();
int CL_Smilo_BetConfirmed(char* contractaddress);
// int CL_Smilo_GetPublicKey(char* buffer, int buffersize);
int CL_Smilo_RequestToken(char* gametoken);
int CL_Smilo_RequestMoreFunds();
int CL_Smilo_CheckTokenFunds(char* contractAddress);
gameDetails_t CL_Smilo_Get_Game_Details(char* contractaddress);

// extern char current_player_publickey[1024];
