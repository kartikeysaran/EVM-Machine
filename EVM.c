#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *file;
FILE *voterFile;
FILE *fp;
FILE *resultFile;



void printError();
void loginAsVoter(); 
void loginAsAdmin();
void introMenu();
void getData();
void printCandidateAndID();
char candidateName[20][50];
int candidateID[20];
int votes[20];
char voterID[20][50];

void printError(){
    printf("\nError ! Please try again..");
    introMenu();
}
void loginAsVoter(){
    int voterId,votedCandidate;
    
    printf("Enter Voting id: ");
    scanf("%d",&voterId);
    voterFile = fopen("evmVoterData.csv","a+");
    if(!voterFile){
       printf("Voters File not found ! Please try again..");
       introMenu();
    }
    else{
        //TODO:Check whether the voter has voted before or not
        printCandidateAndID();
        printf("\nEnter Candidate ID to vote: ");
        scanf("%d",&votedCandidate);
        fprintf(voterFile, "%d, %d \n", voterId, votedCandidate);
        fclose(voterFile);    
    }
    fp = fopen("evmData.csv","r");
    if(!fp){
       
       introMenu(); 
    }
    else{
        
       
            char buffer[1024]; 
            int row = 0; 
            int column = 0;

        while (fgets(buffer, 1024, fp)) { 
            column = 0; 
            row++;
            
            // To avoid printing of column 
            // names in file can be changed 
            // according to need 
            if (row == 1) 
                continue; 
  
            // Splitting the data 
            char* value = strtok(buffer, ", "); 
  
            while (value) { 
                
                // Column 2 
                if (column == 1) { 
                    candidateID[row-1] = atoi(value);
                    
                } 
                // Column 3 
                if (column == 2) { 
                    if(value!=NULL){
                    votes[row-1] = atoi(value);
                    
                    }    
                }  
                value = strtok(NULL, ", "); 
                column++; 
            } 
        } 
        // Close the file 
        fclose(fp); 
        }

        resultFile = fopen("evmResults.csv","w");
        if(!resultFile){
           printf("Result File Not Found \n");
           introMenu();
        }else{
            
            for(int i = 0;i<20;i++){
                if(candidateID[i]==votedCandidate){
                    votes[i] = votes[i]+1;
                }
            }
            
            for(int i = 0; i<20;i++){  
              fprintf(resultFile, "%d, %d\n", candidateID[i], votes[i]);
              
            }
            fclose(resultFile);        
        }
        printf("\nResponse Recorded successfully ! Thankyou for your vote each vote Counts\n"); 
        introMenu();    
    }
    
void printCandidateAndID(){
    file = fopen("evmData.csv","r");
        if(!file){
              printf("Candidate File not found ! Please try again..");
              introMenu();
            }
        else{
            char buffer[1024]; 
            int row = 0; 
            int column = 0;
            
  
        while (fgets(buffer, 1024, file)) { 
            column = 0; 
            row++; 
  
            // To avoid printing of column 
            // names in file can be changed 
            // according to need 
            if (row == 1) 
                continue; 
  
            // Splitting the data 
            char* value = strtok(buffer, ", "); 
  
            while (value) { 
                // Column 1 
                if (column == 0) { 
                    printf("Candidate Name :"); 
                } 
  
                // Column 2 
                if (column == 1) { 
                    printf("\tCandidate ID :"); 
                } 
                printf("%s", value); 
                value = strtok(NULL, ", "); 
                column++; 
            } 
            printf("\n"); 
        } 
  
        // Close the file 
        fclose(file); 
        }
}      

void loginAsAdmin(){
    int adminLogin,updateCandidate,addCandidate,cId,deleteCId;
    char cName[100];
    int initialVotes = 0;
    
    printf("\nChoose one of the options below :\n1.Update Candidates\n2.View Election Result\n");
    scanf("%d",&adminLogin);
    if(adminLogin == 1){
        printf("\nChoose one\n1.Add Candidate\n2.Remove Candidate\n");
        scanf("%d",&updateCandidate);
        if(updateCandidate == 1){
            file = fopen("evmData.csv","a+");
            if(!file){
              printf("\nFile not found ! Please try again..");
              introMenu();
            }
            else{
              printf("\nEnter Candidate Name : ");
              scanf("%s",cName);
              printf("\nEnter Candidate Id : ");
              scanf("%d",&cId);
              fprintf(file, "%s, %d, %d\n", cName, cId, initialVotes);
              printf("\nSuccessfully added new candidate"); 
              fclose(file);
              introMenu();
            }
            
        }else if(updateCandidate == 2){
            int candidateIDtoRemove;
            printf("\nEnter Candidate Id to remove : ");
            scanf("%d",&candidateIDtoRemove);
            file = fopen("evmData.csv","a+");
            if(!file){
                printf("\nFile not found ! Please try again..");
                introMenu();
            }
            else{

            }
            
            introMenu();
                
        }else{
            printError();
        }
    }else if(adminLogin == 2){
        file = fopen("evmData.csv","r");
        if(!file){
              printf("File not found ! Please try again..");
              introMenu();
            }
        else{
            char buffer[1024]; 
            int row = 0; 
            int column = 0;
            
  
        while (fgets(buffer, 1024, file)) { 
            column = 0; 
            row++; 
  
            // To avoid printing of column 
            // names in file can be changed 
            // according to need 
            if (row == 1) 
                continue; 
  
            // Splitting the data 
            char* value = strtok(buffer, ", "); 
  
            while (value) { 
                int candidateId;
                // Column 1 
                if (column == 0) { 
                    printf("Candidate Name :"); 
                } 
  
                // Column 2 
                if (column == 1) { 
                    printf("\tCandidate ID :");
                     
                } 
  
                // Column 3 
                if (column == 2) { 
                    printf("\tVotes :");
                    
                } 
  
                printf("%s", value); 
                value = strtok(NULL, ", "); 
                column++; 
            } 
            printf("\n");
        } 
  
        // Close the file 
        fclose(file); 
        }
        printf("\nc has won the election");
        introMenu();

    }
    else{
        printError();
    }
}



void introMenu(){
    int loginmenu;
    printf("\nSomeone struggled for your right to vote. Use it.\nLogin as :\n1.Admin\n2.Voter\nPress any other key to exit\n");
    scanf("%d",&loginmenu);
    if(loginmenu == 1){
       loginAsAdmin();
    }else if(loginmenu == 2){
       loginAsVoter(); 
    }else{
       exit(0);
    }
    

}

int main(){
    introMenu();
    return 0;
}
