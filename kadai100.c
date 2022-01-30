#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void read_dict_files(char *filename, char dict[][256]){
    FILE *fp = fopen(filename, "r");
    while(fscanf(fp,"%s",dict) != EOF){
        dict++;
    }
    fclose(fp);
}

void add_words(char* word, char* translation){
    FILE *en,*ja;
    en = fopen("english.txt","a");
    ja = fopen("japanese.txt","a");

    char* englishWord,japaneseWord;
    if(isascii(word[0])){//word is english,translation is japanese
        fprintf(en,"%s\n",word);
        fprintf(ja,"%s\n",translation);
    }
    else{
        fprintf(ja,"%s\n",word);
        fprintf(en,"%s\n",translation);
    };

    printf("Added %s to the dictionary\n",word);
    fclose(en);
    fclose(ja);
}
void look_up(char *word){
    //load dictionary
    char* englishDictionaryPath = "english.txt";
    char* japaneseDictionaryPath = "japanese.txt";
    char englishDict[1000][256];
    char japaneseDict[1000][256];

    read_dict_files(englishDictionaryPath, englishDict);
    read_dict_files(japaneseDictionaryPath, japaneseDict);

    //search for word
    if(isascii(word[0])){
        for(int i = 0; i < 1000; i++){
            if(strcmp(word,englishDict[i]) == 0){
                printf("The transration of %s is %s.\n",word,japaneseDict[i]);
                return;
            }
        }
        printf("%s is not in the dictionary.\n",word);
    }
    else{
        for(int i = 0; i < 1000; i++){
            if(strcmp(word,japaneseDict[i]) == 0){
                printf("The transration of %s is %s.\n",word,englishDict[i]);
                return;
            }
        }
        printf("%s is not in the dictionary.\n",word);
    }
}
int mygetline(char s[], int size)
{
    int         c, i;

    for ( i = 0;  (c = getchar()) != EOF && c != '\n' && i < size - 1; i++ ) {
        s[i] = c;
    }

    s[i] = '\0';

    if ( c == EOF && i == 0 ){
        return -1;
    }

    return i;
}
int main(void){
    //show menu
    printf("Welcome to the Japanese-English/English-Japanese Dictionary.\n");
    printf("usage: add <word> <translation>\n");
    printf("       lookup <word>\n");
    printf("       quit\n");
    printf("Please enter a command.\n");

    //command and arguments
	char sentence[256];
	char doublesentence[256];
    char command[256];
    char word[256];
    char translation[256];
    
    while(1){
        mygetline(sentence, 100);
		for(int j=0;j<100;++j){
        doublesentence[j] = sentence[j];
        }

		char *ptr;
        ptr = strtok(sentence, " ");
        sprintf(command,"%s", ptr);
        if(strcmp(command,"add") == 0){
             char *tp;
             tp = strtok(doublesentence, " ");
             sprintf(command,"%s", tp);

             tp = strtok(NULL, " ");
             sprintf(word,"%s", tp);

             tp = strtok(NULL, " ");
             sprintf(translation,"%s", tp);
              
			 
            add_words(word,translation);
        }
        else if(strcmp(command,"lookup") == 0){
            ptr = strtok(NULL, " ");
            if(ptr != NULL) {
            sprintf(word,"%s", ptr);
			}
            look_up(word);
        }
        else if(strcmp(command,"quit") == 0){
            break;
        }
        else{
            printf("Invalid command.\n");
        }
    }
    
    
}