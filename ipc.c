a.c

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <fcntl.h>
 #include <sys/stat.h>
 #include <sys/types.h>
 void main(){
 char *fifo1 = "fifo1";
 char *fifo2 = "fifo2";
 int d1,d2;
 char buff[100];
 char ch;
 char buff2[100];
 int i=0;
 mkfifo("fifo1", 0666);
 d1 = open("fifo1" , O_WRONLY);
 printf("Enter Data ->>> ");
 ch = getchar();
 while(ch!='#')
 {
           buff[i]=ch;
           i++;
           ch = getchar();
        }
        buff[i]='#';
        write(d1 , buff , sizeof(buff));
        close(d1);
        d2 = open("fifo2",O_RDONLY);
        read(d2,buff2,sizeof(buff2));
        FILE* fp = fopen(buff2,"r");
 do{
    ch = fgetc(fp);
    printf("%c",ch);
 }while(ch!=EOF);
 fclose(fp);
 }

b.c

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <fcntl.h>
 #include <sys/stat.h>
 #include <sys/types.h>
 void main(){
 char* fifo1 = "fifo1";
 char* fifo2 = "fifo2";
 int d1,d2;
 char buff[100];
 char ch;
 char buff2[100];
 int i=0;
 int word = 0,chcount = 0,linecount = 0;
 mkfifo("fifo1" , 0666);
 d1 = open("fifo1" , O_RDONLY);
 read(d1,buff,sizeof(buff));
 close(d1);
while(buff[i]!='#')
 {
  if(buff[i]==' ')
     word++;
  else if(buff[i]=='\n')
  {
    linecount++;
    word++;
  }
  else 
      chcount++;
  i++;
 }
 FILE* fp = fopen("abc.txt","w+");
 fprintf(fp , "count of Lines = %d \n",linecount);
 fprintf(fp , "count of Words = %d \n",word);
 fprintf(fp , "count of Characters = %d \n",chcount);
 fclose(fp);
 mkfifo("fifo2" , 0666);
 d2 = open("fifo2" , O_WRONLY);
 write(d2 , "abc.txt" , 7);
 close(d2);
 }

//gcc a.c -o a.out
//gcc b.c -o b.out
//./a.out
//./b.out
