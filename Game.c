#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


/*

CheckList:
- Game ends when "respect" is 0 or below, or above 80
- Look: View room and creature details
- Clean/Dirty: Alter room state
- Direct NPCs/Animals to Clean/Dirty
- Make a creature leave in a chosen direction
- Tunnel Out if there are too many Creatures(10)

*/


void StartFunction()
{
    printf("\n----------------------------------------------------\n\n\n");
}

void EndFunction()
{
    printf("\n\n\nend\n----------------------------------------------------\n\n");
}

void BreakLine()
{
    printf("\n----------------------------------------------------\n\n");
}

typedef struct
{
    int ID;
    int Type;
    int CurrentRoom;
} Creature;

typedef struct
{
    int roomNum;
    int cleanliness;
    int rNorth;
    int rSouth;
    int rEast;
    int rWest;
    int numCreatures;
    int numPC;
    int numNPC;
    int numAnimals;

    Creature *RoomCrsArray[10];
} Room;

typedef struct
{
    int x;
    int y;
    int roomNum;
    Room *roomPtr;
}Cord;


Room *RoomPointerArray = NULL;
Creature *CreaturePointerArray = NULL;
int Respect = 40;


void NewPrintBox(int roomNum, char Row1[], char Row2[], char Row3[], char Row4[], char Row5[], int i, Cord *cordArr)
{
    
    int spacer = 9;
    bool roomNumOverTen = false;
    char roomNumString[3]; 

    if(roomNum > 9)
    {
        roomNumOverTen = true;
        

        sprintf(roomNumString, "%d", roomNum);
    }
    else
    {
        roomNumOverTen = false;
    }

    //North
    if(cordArr[roomNum].roomPtr->rNorth != -1)
    {
        //There is a Room
        Row1[(i * spacer) + 0] = ' ';
        Row1[(i * spacer) + 1] = ' ';
        Row1[(i * spacer) + 2] = '_';
        Row1[(i * spacer) + 3] = '|';
        Row1[(i * spacer) + 4] = ' ';
        Row1[(i * spacer) + 5] = '|';
        Row1[(i * spacer) + 6] = '_';
        Row1[(i * spacer) + 7] = ' ';
        Row1[(i * spacer) + 8] = ' ';
    }
    else
    {
        //No Room
        Row1[(i * spacer) + 0] = ' ';
        Row1[(i * spacer) + 1] = ' ';
        Row1[(i * spacer) + 2] = '_';
        Row1[(i * spacer) + 3] = '_';
        Row1[(i * spacer) + 4] = '_';
        Row1[(i * spacer) + 5] = '_';
        Row1[(i * spacer) + 6] = '_';
        Row1[(i * spacer) + 7] = ' ';
        Row1[(i * spacer) + 8] = ' ';
    }


    char Right1 = '_';
    char Left1 = '_';


        //East
    if(cordArr[roomNum].roomPtr->rWest != -1)
    {
        //There is a room
        Left1 = '_';

    }
    else
    {
        //No Room
        Left1 = ' ';
    }


    char PlayerSymbol = ' ';

    if(cordArr[roomNum].roomPtr->numPC > 0)
    {
        PlayerSymbol = '*';
    }
    //East
    if(cordArr[roomNum].roomPtr->rEast != -1)
    {
        //There is a room

        Right1 = '_';
        Row3[(i * spacer) + 0] = Left1;
        Row3[(i * spacer) + 1] = '|';
        Row3[(i * spacer) + 2] = ' ';
        Row3[(i * spacer) + 3] = PlayerSymbol;
        Row3[(i * spacer) + 6] = ' ';
        Row3[(i * spacer) + 7] = ' ';
        Row3[(i * spacer) + 8] = '_';

        if(roomNumOverTen)
        {
            Row3[(i * spacer) + 4] = roomNumString[0];
            Row3[(i * spacer) + 5] = roomNumString[1];
        }
        else
        {
            Row3[(i * spacer) + 4] = roomNum + '0';
            Row3[(i * spacer) + 5] = ' ';
        }

    }
    else
    {
        //No Room

        Right1 = ' ';
        Row3[(i * spacer) + 0] = Left1;
        Row3[(i * spacer) + 1] = '|';
        Row3[(i * spacer) + 2] = ' ';
        Row3[(i * spacer) + 3] = PlayerSymbol;
        Row3[(i * spacer) + 4] = roomNum + '0';
        Row3[(i * spacer) + 5] = ' ';
        Row3[(i * spacer) + 6] = ' ';
        Row3[(i * spacer) + 7] = '|';
        Row3[(i * spacer) + 8] = ' ';
    }

    //South
    if(cordArr[roomNum].roomPtr->rSouth != -1)
    {
        //There is a Room
        Row4[(i * spacer) + 0] = ' ';
        Row4[(i * spacer) + 1] = '|';
        Row4[(i * spacer) + 2] = '_';
        Row4[(i * spacer) + 3] = ' ';
        Row4[(i * spacer) + 4] = ' ';
        Row4[(i * spacer) + 5] = ' ';
        Row4[(i * spacer) + 6] = '_';
        Row4[(i * spacer) + 7] = '|';
        Row4[(i * spacer) + 8] = ' ';


        Row5[(i * spacer) + 3] = '|';
        Row5[(i * spacer) + 5] = '|';
    }
    else
    {
        //No Room
        Row4[(i * spacer) + 0] = ' ';
        Row4[(i * spacer) + 1] = '|';
        Row4[(i * spacer) + 2] = '_';
        Row4[(i * spacer) + 3] = '_';
        Row4[(i * spacer) + 4] = '_';
        Row4[(i * spacer) + 5] = '_';
        Row4[(i * spacer) + 6] = '_';
        Row4[(i * spacer) + 7] = '|';
        Row4[(i * spacer) + 8] = ' ';
    }


    Row2[(i * spacer) + 0] = Left1;
    Row2[(i * spacer) + 1] = '|';
    Row2[(i * spacer) + 2] = ' ';
    Row2[(i * spacer) + 3] = ' ';
    Row2[(i * spacer) + 4] = ' ';
    Row2[(i * spacer) + 5] = ' ';
    Row2[(i * spacer) + 6] = ' ';
    Row2[(i * spacer) + 7] = '|';
    Row2[(i * spacer) + 8] = Right1;


}

void PrintBox(Cord *cordArr, int size)
{
    

    //654321
    for(int RowCount = size - 1; RowCount >= (-size + 1); RowCount--)
    {
        bool emptyRow = true;
        //printf("\nNew Row\n");
        /*
        Iterates Through Rows(num is the row where looking at)
        */

        int maxRowSize = 9 * (size + 1);
        char Row1[maxRowSize];
        char Row2[maxRowSize];
        char Row3[maxRowSize];
        char Row4[maxRowSize];
        char Row5[maxRowSize];

        memset(Row1, ' ', maxRowSize); // Initialize arrays to empty
        memset(Row2, ' ', maxRowSize);
        memset(Row3, ' ', maxRowSize);
        memset(Row4, ' ', maxRowSize);
        memset(Row5, ' ', maxRowSize);

        // End the strings
        Row1[maxRowSize-1] = '\0';
        Row2[maxRowSize-1] = '\0';
        Row3[maxRowSize-1] = '\0';
        Row4[maxRowSize-1] = '\0';
        Row5[maxRowSize-1] = '\0';
        


        for(int cordAtInex = size - 1; cordAtInex >= 0; cordAtInex--)
        {
            
            /*
            Iterates through X Cords: 
            (0,0)
            (0,1)
            (0,2)
            (1,3)
            */
            //printf("CordArr.y: %d == %d\n", cordArr[cordAtInex].y, RowCount);

            if(cordArr[cordAtInex].y == RowCount)
            {

                //Iterates Through the X Values
                for(int i = 0; i < size; i++)
                {
                    if(cordArr[cordAtInex].x == i)
                    {
                        emptyRow = false;
                        //printf("\nCordArr.x: %d == %d\n", cordArr[cordAtInex].x, i);
                        NewPrintBox(cordArr[cordAtInex].roomNum, Row1, Row2, Row3, Row4, Row5, i, cordArr);
                    }
                }
            }
        }
        //Prints Box

        if(!emptyRow)
        {
            printf("\n%s\n", Row1);
            printf("%s\n", Row2);
            printf("%s\n", Row3);
            printf("%s\n", Row4);
            printf("%s", Row5);
        }
    }
}

void PrintRespect()
{
    printf("\nYour Respect is now %d\n", Respect);
}

void Help()
{
    printf("\nWrite a Command as IDCommand, EX. 2clean 0north\n");
    printf("The Commands Are:\n");
    printf("clean - Cleans the room your in\n");
    printf("dirty - Dirtys the room your in\n");
    printf("look - Gives you facts about the current room your in\n");
    printf("north - Attemps to move you north\n");
    printf("south - Attemps to move you south\n");
    printf("east - Attemps to move you east\n");
    printf("west - Attemps to move you west\n");
    printf("help - Brings up this message\n");
    printf("openMap - Brings up the map");
    printf("exit - Quits the program\n");
}

void AddCreature(int NewRoom, int OldRoom, int CraetureIndex)
{
    
    Room* newRoom = &RoomPointerArray[NewRoom];

    Room* oldRoom = &RoomPointerArray[OldRoom];

    //Sets Creature To The Next Spot In Array

    newRoom->RoomCrsArray[newRoom->numCreatures] = oldRoom->RoomCrsArray[CraetureIndex];

    newRoom->numCreatures++;

    

}

void RemoveCreature(int CurrentRoom,int numIndex)
{
    Room* currentRoom = &RoomPointerArray[CurrentRoom];

    //0 1 2 3 4 5
    //a b c d e f

    for(int i = numIndex; i < currentRoom->numCreatures - 1; i++)
    {
        currentRoom->RoomCrsArray[i] = currentRoom->RoomCrsArray[i + 1];
    }

    currentRoom->numCreatures--;
}

void CreatureLeaveRoom(int PlayerCurrentRoom, int creatureIndex)
{
    //NPC Has to leave Room

    Room* currentRoom = &RoomPointerArray[PlayerCurrentRoom];
    bool newRoomFound = false;
    int tries = 0;
    while(newRoomFound == false)
    {
        //int num = rand() % 4;
        if(tries == 4)
        {
            printf("There Was No SuitableRoom, The Creature leaves the house");
        }
        int num = 0;
        if(num == 0)
        {
            if(currentRoom->rNorth != -1)
            {
                Room* roomNorth = &RoomPointerArray[currentRoom->rNorth];
                if(roomNorth->numCreatures < 10)
                {

                    newRoomFound = true;
                    AddCreature(currentRoom->rNorth, PlayerCurrentRoom, creatureIndex);

                    RemoveCreature(PlayerCurrentRoom, creatureIndex);
                    
                }
                else
                {
                    tries++;
                }
            }
            else
            {
                tries++;
            }
        }
        else if(num == 1)
        {
            if(currentRoom->rSouth != -1)
            {
                Room* roomSouth = &RoomPointerArray[currentRoom->rSouth];
                if(roomSouth->numCreatures < 10)
                {
                    newRoomFound = true;
                    AddCreature(currentRoom->rSouth, PlayerCurrentRoom, creatureIndex);
                    RemoveCreature(PlayerCurrentRoom, creatureIndex);

                }
                else
                {
                    tries++;
                }
            }
            else
            {
                tries++;
            }
        }
        else if(num == 2)
        {
            if(currentRoom->rEast != -1)
            {

                
                Room* roomEast = &RoomPointerArray[currentRoom->rEast];
                if(roomEast->numCreatures < 10)
                {

                    newRoomFound = true;
                    AddCreature(currentRoom->rEast, PlayerCurrentRoom, creatureIndex);
                    RemoveCreature(PlayerCurrentRoom, creatureIndex);
                    
                }
                else
                {
                    tries++;
                }
            }
            else
            {
                tries++;
            }
        }
        else if(num == 3)
        {
            if(currentRoom->rWest != -1)
            {

                
                Room* roomWest = &RoomPointerArray[currentRoom->rWest];
                if(roomWest->numCreatures < 10)
                {

                    newRoomFound = true;
                    AddCreature(currentRoom->rWest, PlayerCurrentRoom, creatureIndex);
                    RemoveCreature(PlayerCurrentRoom, creatureIndex);
                    
                }
                else
                {
                    tries++;
                }
            }
            else
            {
                tries++;
            }
        }
                        
    }
}

void AnimalCleanCheck(int PlayerCurrentRoom)
{
    Room* currentRoom = &RoomPointerArray[PlayerCurrentRoom];

    for(int b = 0; b < currentRoom->numCreatures; b++)
    {
        //Room Found, Iterates Through Creates
        int Type = currentRoom->RoomCrsArray[b]->Type;
        if(Type == 1)
        {
            //Animal
            //2 is dirty

            if(currentRoom->cleanliness == 0)
            {
                //Animal Has to leave Room
                printf("Animal %d Licks Your Face", currentRoom->RoomCrsArray[b]->ID);
                Respect--;
                PrintRespect();
               
            }
        }
        else if(Type == 2)
        {
            if(currentRoom->cleanliness == 0)
            {
                //NPC is happy

                printf("NPC %d Leaves the Room and Spits At Your", currentRoom->RoomCrsArray[b]->ID);
                CreatureLeaveRoom(currentRoom->roomNum, b);
                Respect++;
                PrintRespect();
            }
        }
    }
}

void AnimalDirtyCheck(int PlayerCurrentRoom)
{
    Room* currentRoom = &RoomPointerArray[PlayerCurrentRoom];

    for(int b = 0; b < currentRoom->numCreatures; b++)
    {
        //Room Found, Iterates Through Creates
        int Type = currentRoom->RoomCrsArray[b]->Type;
        if(Type == 1)
        {
            //Animal
            //2 is dirty

            if(currentRoom->cleanliness == 2)
            {
                //Animal Has to leave Room
                printf("Animal %d Leaves the Room and Growls", currentRoom->RoomCrsArray[b]->ID);
                Respect--;
                PrintRespect();
                CreatureLeaveRoom(currentRoom->roomNum, b);

            }
        }
        else if(Type == 2)
        {
            if(currentRoom->cleanliness == 2)
            {
                //NPC is happy

                printf("NPC %d Gives You A High Five", currentRoom->RoomCrsArray[b]->ID);
                Respect++;
                PrintRespect();
            }
        }
    }
}

int MoveNorth(int CurrentRoomNum, int CreatureID)
{
    Room* currentRoom = &RoomPointerArray[CurrentRoomNum];
    
    if(currentRoom->rNorth != -1)
    {
        printf("\nThe Creature Attempts to Head North To Room %d\n", currentRoom->rNorth);
        Room* roomNorth = &RoomPointerArray[currentRoom->rNorth];
        if(roomNorth->numCreatures < 10)
        {
            for(int i = 0; i < currentRoom->numCreatures; i++)
            {
                //Finds Creature with ID To Move
                if(currentRoom->RoomCrsArray[i]->ID == CreatureID)
                {
                    //Adds Creature To New Room
                    AddCreature(currentRoom->rNorth, CurrentRoomNum, i);

                    //Removes Creature from old room
                    RemoveCreature(CurrentRoomNum, i);



                    
                    //sets the players current room
                    //printf("\nCreature Type %d == 0\n", currentRoom->RoomCrsArray[i]->Type);
                    if(currentRoom->RoomCrsArray[i]->Type == 0)
                    {
                        printf("\nYour Player Heads North\n");
                        CurrentRoomNum = currentRoom->rNorth;
                        
                    }
                }
            }
        }
        else
        {
            printf("\nCant Move Room Full\n");
        }
    }
    else
    {
        printf("\nNo Room There\n");
    }

    return CurrentRoomNum;
}

int MoveSouth(int CurrentRoom, int CreatureID)
{
    Room* currentRoom = &RoomPointerArray[CurrentRoom];

    
    if(currentRoom->rSouth != -1)
    {
        Room* roomSouth = &RoomPointerArray[currentRoom->rSouth];
        if(roomSouth->numCreatures < 10)
        {
            for(int i = 0; i < currentRoom->numCreatures; i++)
            {
                //Finds Creature with ID

                if(currentRoom->RoomCrsArray[i]->ID == CreatureID)
                {
                    AddCreature(currentRoom->rSouth, CurrentRoom, i);
                    RemoveCreature(CurrentRoom, i);
                    if(currentRoom->RoomCrsArray[i]->Type == 0)
                    {
                        printf("You Head South");
                    
                        CurrentRoom = roomSouth->roomNum;
                    }
                }
            }
        }
        else
        {
            printf("Cant Move Room Full");
        }
    }
    else
    {
        printf("No Room There");
    }

    return CurrentRoom;
}

int MoveEast(int CurrentRoom, int CreatureID)
{
    Room* currentRoom = &RoomPointerArray[CurrentRoom];


    if(currentRoom->rEast != -1)
    {
        Room* roomEast = &RoomPointerArray[currentRoom->rEast];
        if(roomEast->numCreatures < 10)
        {
            for(int i = 0; i < currentRoom->numCreatures; i++)
            {
                //Finds Creature with ID

                if(currentRoom->RoomCrsArray[i]->ID == CreatureID)
                {
                    AddCreature(currentRoom->rEast, CurrentRoom, i);
                    RemoveCreature(CurrentRoom, i);

                    if(currentRoom->RoomCrsArray[i]->Type == 2)
                    {
                        printf("You Head East");

                        CurrentRoom = currentRoom->rEast;
                    }
                }
            }
        }
        else
        {
            printf("Cant Move Room Full");
        }
    }
    else
    {
        printf("No Room There");
    }
    return CurrentRoom;
}

int MoveWest(int CurrentRoom, int CreatureID)
{
    Room* currentRoom = &RoomPointerArray[CurrentRoom];

    
    if(currentRoom->rWest != -1)
    {
        Room* roomWest = &RoomPointerArray[currentRoom->rWest];
        if(roomWest->numCreatures < 10)
        {
            for(int i = 0; i < currentRoom->numCreatures; i++)
            {
                //Finds Creature with ID

                if(currentRoom->RoomCrsArray[i]->ID == CreatureID)
                {
                    AddCreature(currentRoom->rWest, CurrentRoom, i);
                    RemoveCreature(CurrentRoom, i);
                    if(currentRoom->RoomCrsArray[i]->Type == 0)
                    {
                        printf("You Head West");

                        CurrentRoom = roomWest->roomNum;
                    }
                }
            }
        }
        else
        {
            printf("Cant Move Room Full");
        }
    }
    else
    {
        printf("No Room There");
    }

    return CurrentRoom;
}

void Clean(int CurrentRoom)
{
    Room* currentRoom = &RoomPointerArray[CurrentRoom];
    if(currentRoom->cleanliness != 0)
    {
        currentRoom->cleanliness--;
        printf("\nRoom Cleaned\n");
    }
    else
    {
        printf("\nThis Room Is Already Clean\n");
    }
    AnimalCleanCheck(CurrentRoom);
}

void LookFunction(int PlayerCurrentRoom)
{
    Room* currentRoom = &RoomPointerArray[PlayerCurrentRoom];

    int roomNum = currentRoom->roomNum;
    int cleanliness = currentRoom->cleanliness;
    int rNorth = currentRoom->rNorth;
    int rSouth = currentRoom->rSouth;
    int rEast = currentRoom->rEast;
    int rWest = currentRoom->rWest;


    BreakLine();
    printf("\nRoom%d\n", roomNum);

    //Cleanliness
    printf("\nSTATUS:");
    if(cleanliness == 0)
    {
        printf("Clean\n");
    }
    else if(cleanliness == 1)
    {
         printf("Half-Dirty\n");
    }
    else
    {
         printf("Dirty\n");
    }


    //Room Neighbors
    printf("\nNeighbors: \n");
    if(rNorth != -1)
    {
        printf("\nRoom %d is to the North", rNorth);
    }
    if(rSouth != -1)
    {
        printf("\nRoom %d is to the South", rSouth);
    }
    if(rEast != -1)
    {
        printf("\nRoom %d is to the East", rEast);
    }
    if(rWest != -1)
    {
        printf("\nRoom %d is to the West", rWest);
    }

    int numPC = 0;
    int numNPC = 0;
    int numAnimals = 0;

    printf("\n\nContains: \n");
    for(int num = 0; num < currentRoom->numCreatures; num++)
    {
        int Type = currentRoom->RoomCrsArray[num]->Type;
        int ID =currentRoom->RoomCrsArray[num]->ID;
        if(Type == 0)
        {
            //Player
            numPC++;
            printf("\nType: PC  ID: %d\n", ID);
        }
        else if(Type == 1)
        {
            //NPC
            numNPC++;
            printf("\nType: NPC  ID: %d\n", ID);
        }
        else if(Type == 2)
        {
            //Animal
            numAnimals++;
            printf("\nType: Animal  ID: %d\n\n", ID);
        }
    }
}

void AutoSetUp()
{
    RoomPointerArray[0].roomNum = 0;
    RoomPointerArray[0].numCreatures = 0;
    RoomPointerArray[0].cleanliness = 0;
    RoomPointerArray[0].rNorth = -1;
    RoomPointerArray[0].rSouth = 1;
    RoomPointerArray[0].rEast = -1;
    RoomPointerArray[0].rWest = 2;

    RoomPointerArray[1].roomNum = 1;
    RoomPointerArray[1].numCreatures = 0;
    RoomPointerArray[1].cleanliness = 2;
    RoomPointerArray[1].rNorth = 0;
    RoomPointerArray[1].rSouth = -1;
    RoomPointerArray[1].rEast = -1;
    RoomPointerArray[1].rWest = -1;

    RoomPointerArray[2].roomNum = 2;
    RoomPointerArray[2].numCreatures = 0;
    RoomPointerArray[2].cleanliness = 2;
    RoomPointerArray[2].rNorth = 1;
    RoomPointerArray[2].rSouth = -1;
    RoomPointerArray[2].rEast = 0;
    RoomPointerArray[2].rWest = -1;
}

int main()
{
    StartFunction();
    Help();


    //Setting Up Rooms

    int roomCount = 0;

    //Gets Number of rooms

    printf("Input room specs: ");
    scanf("%d", &roomCount);

    //Make RoomArray an Array of Pointers

    RoomPointerArray = malloc(roomCount * sizeof(Room));

    //AutoSetUp();


    Cord *cordList = malloc(roomCount * sizeof(Cord));
    int currentLocX = 0;
    int currentLocY = 0;

    for(int i = 0; i < roomCount - 1; i++)
    {
        //Emptys Rid of cordsList
        cordList[i].x = 0;
        cordList[i].y = 0;
    }


    for (int digit = 0; digit < roomCount; ++digit)
    {
       RoomPointerArray[digit].roomNum = digit;
       RoomPointerArray[digit].numCreatures = 0;
       scanf("%d %d %d %d %d", &RoomPointerArray[digit].cleanliness, &RoomPointerArray[digit].rNorth, &RoomPointerArray[digit].rSouth, &RoomPointerArray[digit].rEast, &RoomPointerArray[digit].rWest);
       //printf("\nRoomNum: %d cleanliness: %d roomNorth: %d roomSouth: %d roomEast: %d roomWest: %d\n", RoomPointerArray[digit].roomNum, RoomPointerArray[digit].cleanliness, RoomPointerArray[digit].rNorth, RoomPointerArray[digit].rSouth, RoomPointerArray[digit].rEast, RoomPointerArray[digit].rWest);

        cordList[digit].roomNum = digit;
        cordList[digit].roomPtr = &RoomPointerArray[digit];

        if(digit != 0)
        {
            if(RoomPointerArray[digit - 1].rNorth == digit)
            {
                //North
                currentLocY += 1;

                //Adds cordinate to the Cord list
                cordList[digit].x = currentLocX;
                cordList[digit].y = currentLocY;
            }
            else if(RoomPointerArray[digit - 1].rSouth == digit)
            {
                //South
                currentLocY -= 1;

                //Adds cordinate to the Cord list
                cordList[digit].x = currentLocX;
                cordList[digit].y = currentLocY;
            }
            else if(RoomPointerArray[digit - 1].rEast == digit)
            {
                //Checks if you moved one unit north
                currentLocX += 1;
                //Adds cordinate to the Cord list
                cordList[digit].x = currentLocX;
                cordList[digit].y = currentLocY;
            }
            else if(RoomPointerArray[digit - 1].rWest == digit)
            {
                //Checks if you moved one unit north
                currentLocX -= 1;

                //Adds cordinate to the Cord list
                cordList[digit].x = currentLocX;
                cordList[digit].y = currentLocY;
            }
        }
        else
        {
            cordList[digit].x = 0;
            cordList[digit].y = 0;
        }
    }

    //Gets Creature Count


    int creatureCount = 0;
    printf("\nInput creature number: ");
    scanf("%d", &creatureCount);

    
    //Makes Creature Pointer Array


    int PlayerCurrentRoom = 2;

    CreaturePointerArray = malloc(creatureCount * sizeof(Creature));

    for (int creatureDigit = 0; creatureDigit < creatureCount; ++creatureDigit)
    {
       CreaturePointerArray[creatureDigit].ID = creatureDigit;

       scanf("%d %d", &CreaturePointerArray[creatureDigit].Type, &CreaturePointerArray[creatureDigit].CurrentRoom);
       //printf("CreatureNum: %d Type: %d CurrentRoom: %d\n", CreaturePointerArray[creatureDigit].ID, CreaturePointerArray[creatureDigit].Type, CreaturePointerArray[creatureDigit].CurrentRoom);

       //Adds Creatures to CRS;

       Room* currentRoom = &RoomPointerArray[CreaturePointerArray[creatureDigit].CurrentRoom];
       Creature* currentCreature = &CreaturePointerArray[creatureDigit];
       currentRoom->RoomCrsArray[currentRoom->numCreatures] = currentCreature;

       
       if(CreaturePointerArray[creatureDigit].Type == 0)
       {
           PlayerCurrentRoom = CreaturePointerArray[creatureDigit].CurrentRoom;
           currentRoom->numPC++;
       }
       else if(CreaturePointerArray[creatureDigit].Type == 1)
       {
           currentRoom->numNPC++;
       }
       else if(CreaturePointerArray[creatureDigit].Type == 2)
       {
           currentRoom->numAnimals++;
       }

       currentRoom->numCreatures++;

    }

    //Commands

    LookFunction(PlayerCurrentRoom);
    int run = 0;
    while(run == 0)
    {

        if(Respect < 0)
        {
            //Win Condition

            printf("You Lost");
            run = 1;
        }

        int ID = 0;
        char FullCommand[10];
        printf("\nEnter the Creatures ID: \n");
        scanf("%d", &ID);

        printf("\nEnter A Command: ");
        scanf("%s", FullCommand);


        //Command List

        if(strcmp(FullCommand, "look") == 0)
        {
            LookFunction(PlayerCurrentRoom);
        }
        if(strcmp(FullCommand, "clean") == 0)
        {
            Clean(PlayerCurrentRoom);
        }
        if(strcmp(FullCommand, "exit") == 0)
        {
            run = 1;
            printf("Goodbye");
        }
        if(strcmp(FullCommand, "north") == 0)
        {
            int temp = MoveNorth(PlayerCurrentRoom, ID);
            printf("\nPlayerCurrentRoom**** %d\n", temp);
            PlayerCurrentRoom = temp;
        }
        if(strcmp(FullCommand, "south") == 0)
        {
            PlayerCurrentRoom = MoveSouth(PlayerCurrentRoom, ID);
        }
        if(strcmp(FullCommand, "east") == 0)
        {
            PlayerCurrentRoom = MoveEast(PlayerCurrentRoom, ID);
        }
        if(strcmp(FullCommand, "west") == 0)
        {
            PlayerCurrentRoom = MoveWest(PlayerCurrentRoom, ID);
        }
        if(strcmp(FullCommand, "openMap") == 0)
        {
            PrintBox(cordList, roomCount);
        }
        if(strcmp(FullCommand, "help") == 0)
        {
            Help();
        }
    }


    // Free dynamically allocated memory
    if (cordList != NULL) {
        free(cordList);
        cordList = NULL;
    }

    if (RoomPointerArray != NULL) {
        free(RoomPointerArray);
        RoomPointerArray = NULL;
    }

    if (CreaturePointerArray != NULL) {
        free(CreaturePointerArray);
        CreaturePointerArray = NULL;
    }

    EndFunction();
    return 0;
}
