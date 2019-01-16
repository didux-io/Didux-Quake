#include "../../src/client/gamedetails.h"

void CL_Smilo_Connected(char* contractAddress, char* buffer, int buffersize);
int CL_Smilo_GetBalance(char* publickey);
int CL_Smilo_BetConfirmed();
int CL_Smilo_GetPublicKey(char* buffer, int buffersize);
int CL_Smilo_RequestToken(char* gametoken);
int CL_Smilo_RequestMoreFunds();
int CL_Smilo_CheckTokenFunds(char* contractAddress);
gameDetails_t CL_Smilo_Get_Game_Details(char* contractaddress);

extern char current_player_publickey[1024];
