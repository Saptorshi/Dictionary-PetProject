//Dictionary Project
#include <stdio.h>
#include <string.h>
void createDict(char *);
int getOffset(char *);

struct book
{
	char word[30];
	char meaning[170];
	char example[500];
};

void createDict(char *fileName)
{
	FILE *fp;int i;
	struct book temp;

	strcpy(temp.word," ");
	strcpy(temp.meaning," ");
	strcpy(temp.example," ");

	fp=fopen(fileName, "wb");

	for(i=0; i<4999;i++)
		fwrite(&temp,sizeof(struct book),1,fp);

	fclose(fp);
}

int getOffset(char *p)//Hash Function
{
	int c=0;int prod=1;int i;
	//puts(p);
	while(*p!='\0')
	{
		if(c==3)
			break;
		prod=prod**p;
		c++;
		p++;
	}
	return (prod%5000);//Returns offset value
}

void searchWord(int hv, char *word, char *fileName)//this function searches for the word
{
    FILE *fp; struct book temp;char ch;
    fp=fopen(fileName, "rb+");
    fseek(fp,hv*sizeof(struct book),SEEK_SET);
    fread(&temp,sizeof(struct book),1,fp);
    fseek(fp,-sizeof(struct book),SEEK_CUR);
    if(strcmp(temp.word," ")==0)//if the file has nothing in the hv location..
    {
        printf("Word not FOUND\n\nDo you want to add the WORD? (Y/N)\n");
        ch=getch();fflush(stdin);
        if(ch=='Y'|| ch=='y')
        {
            updateDict(word, fileName);//this function will write the new word into the file
        }
        else
            exit(0);
    }
    else
    {
        while(!feof(fp))//if there is a collision then it will search till the end of the file
        {
            if(strcasecmp(word, temp.word)==0)
            {
                printf("\nSearch Succesfull!!!! Word Found\n\n");
                printf("Word:-%s\n\nMeaning:-%s\n\nExample:-%s\n",temp.word, temp.meaning, temp.example);//<--------for now use this..will make the display function later
                exit(0);//<-----------------------------------------------------------------------------------------------------------------------also this
            }
            fread(&temp,sizeof(struct book),1,fp);
        }
        printf("\nWord not Found\n\nDo you want to add the WORD? (Y/N)\n");
        ch=getch();fflush(stdin);
        if(ch=='Y'|| ch=='y')
        {
             updateDict(word, fileName);//this function will write the new word into the file
        }
    }
}


void updateDict(char *word, char *fileName)
{
    FILE *fp;
    int off; struct book twrite;struct book tread;
    strcpy(twrite.word, word);

    printf("\nEnter the meaning of the WORD\n");
    gets(twrite.meaning);fflush(stdin);

    printf("\nEnter the example of the WORD\n");
    gets(twrite.example);fflush(stdin);

    off=getOffset(word);
    fp=fopen(fileName,"rb+");
    fseek(fp,off*sizeof(struct book),SEEK_SET);
    fread(&tread,sizeof(struct book),1,fp);
    if(strcmp(tread.word, " ")==0)
    {
        fseek(fp,-sizeof(struct book),SEEK_CUR);
        fwrite(&twrite,sizeof(struct book),1,fp);
    }
    else
    {
        while(!feof(fp))
        {
            if(strcmp(tread.word, " ")==0)
            {
                fseek(fp,-sizeof(struct book),SEEK_CUR);
                break;
            }
            fread(&tread,sizeof(struct book),1,fp);
        }
        fwrite(&twrite,sizeof(struct book),1,fp);
    }
    fclose(fp);
    displayDict(fileName);
}

void displayDict(char *fileName)
{
    FILE *fp;struct book temp;int i=0;
    fp=fopen(fileName, "rb+");
    while(!feof(fp))
    {
        fread(&temp, sizeof(struct book),1,fp);
        if(i%100==0)
           getchar(); //return;
        printf("%s %s %s %d",temp.word, temp.meaning, temp.example,i);
        printf("\n");
        i++;
    }
    fclose(fp);
}

int main()
{
    int j;
    printf("\t\t");
    for(j=0;j<41;j++)
        printf("-");
    printf("\n\t\tTHE DICTIONARY PROJECT-Sarang & Saptorshi\n\t\t");
    for(j=0;j<41;j++)
        printf("-");
    printf("\n\n");
	char fileName[30], word[30];int hv,hv1,hv2;char ch;
	printf("1.Do you want to create a new file?\n\n2.Do you want to open an pre-existing FILE?\n");
	ch=getch();fflush(stdin);
    if(ch=='1')
    {
        printf("\nEnter the FILE NAME to create the file\n");
        gets(fileName);fflush(stdin);
        createDict(fileName);//creates the blank file
        printf("\nTo update the Dictionary enter the WORD\n");
        gets(word);fflush(stdin);
        updateDict(word, fileName);//its adds new word to the file
    }
    else
    {
        printf("\nEnter the pre-existing FILE NAME\n");
        gets(fileName);fflush(stdin);
        printf("\nEnter the WORD you want to search\n");
        gets(word);fflush(stdin);
        hv=getOffset(word);

        searchWord(hv, word, fileName);//searches for a word in the file
    }
//    printf("Enter the FILE NAME to create the file\n");
//	gets(fileName);fflush(stdin);
//	createDict(fileName);//creates the blank file
//
//	FILE *fp;
//	struct book temp;
//	strcpy(temp.word,"bat");
//	strcpy(temp.meaning,"used for playing cricket");
//	strcpy(temp.example,"Batsman needs a bat to bat");
//    hv1=getOffset(temp.word);
//
//	fp=fopen(fileName, "rb+");
//	fseek(fp,hv1*sizeof(struct book),SEEK_SET);
//    fwrite(&temp,sizeof(struct book),1,fp);
//    fclose(fp);
//
//
//	struct book temp1;
//	strcpy(temp1.word,"cat");
//	strcpy(temp1.meaning,"a domestic animal");
//	strcpy(temp1.example,"Cat loves to eat fish.");
//    hv2=getOffset(temp1.word);
//
//	fp=fopen(fileName, "rb+");
//	fseek(fp,hv2*sizeof(struct book),SEEK_SET);
//    fwrite(&temp1,sizeof(struct book),1,fp);
//    fclose(fp);
//
//	printf("Enter the word to be SEARCHED\n");
//	gets(word);
//	fflush(stdin);
//    hv=getOffset(word);
//
//    searchWord(hv, word, fileName);
   displayDict(fileName);
	return 0;
}

