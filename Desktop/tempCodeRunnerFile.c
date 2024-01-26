#include "information.h"

#define Find_a_Repository 100


void create_hidden_dir() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Error getting current working directory");
        return;
    }
    int found = 0; 
    char path[1024];
    strcpy(path, cwd);
    while (1) {
        strcat(path, "/.sgit");
        if (dir_exists(path)) { 
            printf("\nError : Already a repository exists in %s\n\n", path);
            found = 1;
            break;
        }
        path[strlen(path) - 6] = '\0';
        if (strcmp(path, "/") == 0) {
            break;
        }
        strcpy(path, dirname(path));
    }
    if (!found) {
        strcpy(path, cwd);
        strcat(path, "/.sgit");
        mkdir(path, 0777);
        char path_of_commits[1024];
        strcpy(path_of_commits, cwd);
        strcat(path_of_commits, "/.sgit/.commits");
        mkdir(path_of_commits, 0777);
        FILE *fp = fopen(".sgit/.commits/hash_commit.txt", "w");
        if(fp == NULL){
            exit(1);
        }
        fprintf(fp, "%d", 100);
        fclose(fp);
        fp = fopen(".sgit/.commits/log.txt", "w");
        if(fp == NULL){
            exit(1);
        }
        fclose(fp);
        printf("Created a local repository in %s\n", path);
    }
    else printf("error!!");
}


void add(char *name){
     char input[1024];
    if (realpath(name, input) == NULL) {
        printf("\nError resolving input path\n");
        return;
    }
      if (access(input, F_OK) != 0) {
        perror("Error accessing input path");
        return;
    }
     char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Error getting current working directory");
        return;
    }
    char dest[100];
    strcpy(dest, cwd);
    strcat(dest, "/.sgit/.staging");
     if (access(dest, F_OK) != 0) {
        mkdir(dest, 0777);
    }
    copy(input, dest);
    printf("\nAdd with success\n");
}

void check_with_staging_area(){
  char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Error getting current working directory");
        return;
    }
    char base[2048];
    sprintf(base, "%s/.sgit/.staging", cwd);
        DIR *dir = opendir(cwd);
    if (dir == NULL) {
        perror("Error opening current directory");
        exit(1);
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char temp[2048];
        sprintf(temp,"%s/%s",base, entry->d_name);
        if(!access(temp,F_OK)){
            printf("\n*** %s is in staging area ***\n", entry->d_name);
        }
        else{
            printf("\n%s is not staged\n",entry->d_name);
        }
    } 
}

void reset(char *path){
      char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Error getting current working directory");
        return;
    }
    char full_path[1024];
    sprintf(full_path,"%s/.sgit/.staging/%s",cwd,path);
    char buffer[1024];
    sprintf(buffer, "rm -r %s ", full_path);
    if(system(buffer) == 0){
        printf("\nreset is done\n");
    }
    else {
        perror("\ncaan not reset this\n");
    }
}

void config_alias(char **argv){
    if (!strcmp(argv[2], "-global")){
        FILE *alias = fopen("/alias.txt", "a");
        char *name_of_alias = strtok(argv[3], ".");
        memmove(name_of_alias, name_of_alias + 1 , strlen(name_of_alias));
        char alias_command[100];
        strcpy(alias_command, argv[4]);
        if(!isvalid_command(alias_command)){
            perror("\nInvalid command \n");
            exit(1);
        }
        else{
            char buffer[1000];
            strcpy(buffer, name_of_alias);
            strcat(buffer, " ");
            strcat(buffer, alias_command);
            strcat(buffer, "\n");
            fputs(buffer, alias);
        }
        fclose(alias);
    }
    else {
        FILE *alias = fopen(".sgit/alias.txt", "a");
        char *name_of_alias = strstr(argv[2], ".");
        memmove(name_of_alias, name_of_alias + 1 , strlen(name_of_alias));
        char alias_command[100];
        strcpy(alias_command, argv[3]);
        if(!isvalid_command(alias_command)){
            perror("\nInvalid command \n");
            exit(1);
        }
        else{
            char buffer[1000];
            strcpy(buffer, name_of_alias);
            strcat(buffer, " ");
            strcat(buffer, alias_command);
            strcat(buffer, "\n");
            fputs(buffer, alias);
        }
             fclose(alias);
     }
 printf("\n The alias is set\n");
}

void Set_Config(char **argv){
    FILE *config = NULL;
    if(!strcmp(argv[2], "-global")){
        if(!strcmp(argv[3], "user.name")) config = fopen("/username.txt", "w");
        else if(!strcmp(argv[3], "user.email")) config = fopen("/useremail.txt", "w");
         else {
            config_alias(argv);
            return;
        }
    }
        else if(!strcmp(argv[2], "user.name")) config = fopen(".sgit/username.txt", "w");
        else if(!strcmp(argv[2], "user.email")) config = fopen(".sgit/useremail.txt", "w");
        else {
            config_alias(argv);
            return;
        }
    if(config == NULL) {
        printf("Try again!\n");
    } else {
        if(!strcmp(argv[2], "-global")) {
            fputs(argv[4], config);
        } else {
            fputs(argv[3], config);
        }
        fclose(config);
        printf("The config is now set\n");
    }
}

int load_alias(char *alias_name) {
    char line[300];
    FILE *alias;

    if ((alias = fopen(".sgit/alias.txt", "r")) != NULL) {
        while (fgets(line, 300, alias) != NULL) {
            char *aliases = strtok(line, " ");
            char *command = strtok(NULL, "\n");
            if (!strcmp(aliases, alias_name)) {
                system(command);
                fclose(alias);
                return 0;
            }
        }
        fclose(alias);
    }

    if ((alias = fopen("/alias.txt", "r")) != NULL) {
        while (fgets(line, 300, alias) != NULL) {
            char *aliases = strtok(line, " ");
            char *command = strtok(NULL, "\n");
            if (!strcmp(aliases, alias_name)) {
                system(command);
                fclose(alias);
                return 0;
            }
        }
        fclose(alias);
    }

    return -1;
}


void status(){
      FILE *fp;
  char buffer[256];
  char cwd[256];
  getcwd(cwd, sizeof(cwd));
  strcat(cwd, "/.sgit/.staging");
  char command[512];
  sprintf(command, "diff -srq  %s . ", cwd);
  fp = popen(command, "r");
  if (fp == NULL) {
    fprintf(stderr, "Error opening pipe\n");
    exit(1);
  }
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    char temp[1024];
    sscanf(buffer, "%s ", temp);
    //The file is in both directories but Deleted or OK ?
    if(strcmp(temp, "Only")){
      sscanf(buffer + 6, "%s ", temp);
      char *name = strrchr(temp, '/');
      if(*name == '.') continue;
    char *situation = strrchr(buffer , ' ');
    situation++;
    //Modified
     if(!strcmp(situation, "differ\n")){
        printf("%s : +M \n", name+1);
     }
     //As the same
     else if(!strcmp(situation, "identical\n")){
        printf("%s : ++ \n", name+1);
     }
    }
    //Only in one directory
    else{
        char name[256];
        sscanf(buffer, "%*s %*s %*s %s ", name);
        //ignore  . and .. and hidden directories
        if(*name == '.') continue;
        //A or D ?
        if (buffer[8] == '.') {
          printf("%s : -A \n", name);
        }
        else if(buffer[8] == '/') {
          printf("%s : +D \n", name);
        }
    }
  }
  pclose(fp);  
}


int commit(char *mess, char *swith){
    char cwd[1024];
    char path_of_staging[1024];
    char path_of_commits[1024];
    char buffer[2048];
    char saving_file[2048];
    char new_file[2048];

    if(!strcmp(swith, "-s")){
        Find_shortcut_message(mess);
    }

    getcwd(cwd, sizeof(cwd));
    strcpy(path_of_staging, cwd);
    strcat(path_of_staging, "/.sgit/.staging");
   if(!dir_exists(path_of_staging)){
    perror("Please add something\n");
    return -1;
   }
   if(strlen(mess) > 72){
    perror("the message is too long\n");
    return -1;
   }
   int commit_ID = 0;;
   FILE *hash = fopen(".sgit/.commits/hash_commit.txt", "r");
   if(hash == NULL){
    perror("Try again later\n");
    return -1;
   }
   fscanf(hash, "%d", &commit_ID);
   fclose(hash);
   hash = fopen(".sgit/.commits/hash_commit.txt", "w");
   commit_ID++;
   fprintf(hash, "%d", commit_ID);
   fclose(hash);
   sprintf(path_of_commits, ".sgit/.commits/number%d", commit_ID);

    FILE *original_file = fopen(".sgit/.commits/log.txt", "r");
    FILE *temp_file = fopen(".sgit/.commits/temp.txt", "w");
     char *name = find_name();
     char *email = find_email();
     //char *branch = find_branch();
     char *branch = find_name();
     fprintf(temp_file,"number%d\n%s\n%s\n%s\n%s\n", commit_ID, branch, mess, name, email);
    free(name);
    free(branch);
     time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(temp_file,"%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    
     char *dir = ".sgit/.staging";
    char *command = "find ";
    char *options = "-type f -printf \"%p\\n\"";
    char *full_command = malloc(strlen(command) + strlen(dir) + strlen(options) + 1);
    sprintf(full_command, "%s%s %s", command, dir, options);
    FILE *fp;
    char path[1035];
    fp = popen(full_command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        char *tok = strchr(path, '/');
        tok++;
        tok  = strchr(tok, '/');
        tok++;
        fputs(tok, temp_file);
    }
    fprintf(temp_file, "\n");
    
    char bufffer[1024];
    while (fgets(bufffer, sizeof(bufffer), original_file)) {
        fprintf(temp_file, "%s", bufffer);
    }
    fclose(temp_file);

     remove(".sgit/.commits/log.txt");
     rename(".sgit/.commits/temp.txt", ".sgit/.commits/log.txt");

    pclose(fp);
    free(full_command);
    sprintf(buffer, "sudo mv %s* %s ", path_of_staging, path_of_commits);
    system(buffer);
    return 0;
}


void LOG(int argc,char **argv){
    int count_of_commits = 0;
    FILE *log = fopen(".sgit/.commits/log.txt", "r");
    if (!log) {
        perror("Error opening log file.");
        exit(1);
     }
     char line[1024];
     char line_branch[1024];
     char line_message[1024];
     char line_name[1024];
     char line_email[1024]; 
     char line_time[1024];
     while ((fgets(line, sizeof(line), log)) != NULL){
       if(!strncmp(line, "number", 6)){
        count_of_commits++;
        static bool flag = false;
        fgets(line_branch, sizeof(line), log);
        fgets(line_message, sizeof(line), log);
        fgets(line_name, sizeof(line), log);
        fgets(line_email, sizeof(line), log);
        fgets(line_time, sizeof(line), log);

        int count_of_files = 0;
        char temp_line[1024];
        do{
          fgets(temp_line, sizeof(line), log);
          count_of_files++;
        } while(strcmp(temp_line, "\n"));
        count_of_files--;
        
        static struct tm date1 = {0};
        static struct tm date2 = {0};
        char date_of_commit[128];
        strncpy(date_of_commit, line_time, 10);
        strptime(date_of_commit, "%Y-%m-%d", &date1);
        strptime(argv[3], "%Y-%m-%d", &date2);
        double diff = difftime(mktime(&date2), mktime(&date1));

        if(argc == 2){
            flag =true;
        }
        else if(!strcmp(argv[2], "-n") && (count_of_commits <= atoi(argv[3]))){
            flag = true;
        }
        else if(!strcmp(argv[2], "-branch") && strstr(line_branch, argv[3])){
            flag = true;
        }
        else if(!strcmp(argv[2], "-author") && strstr(line_name, argv[3])){
            flag = true;
        }
        else if(!strcmp(argv[2], "-search") && strstr(line_message, argv[3])){
            flag = true;
        }
        else if(!strcmp(argv[2], "-before") && (diff>=0)){
            flag = true;
        }
        else if(!strcmp(argv[2], "-since") && (diff<=0)){
            flag = true;
        }

        if(flag){
        printf("\n********************\n");
        printf("Commit with Id %s ", line);
        printf("Commit message : %s ", line_message);
        printf("Author name : %s ", line_name);
        printf("Author email : %s ", line_email);
        printf("DATE and Time of Commit : %s ", line_time);
        printf("In branch : %s ", line_branch);
        printf("number of files in this commit : %d \n", count_of_files);
        printf("\n********************\n");
        printf("\n\n");
        }
       }
     }
        

    fclose(log);
}

int main(int argc, char **argv){
     char main_command[100]; strcpy(main_command, argv[1]);
     //Find_a_Repository
     if(strcmp(main_command, "init")){
        while(!dir_exists(".sgit")){
            chdir("..");
        }
     }
    //init>>
    if(!strcmp(main_command, "init")) {
        create_hidden_dir();
     return 0;
     }
     //config>>
     if(!strcmp(main_command, "config")){
       Set_Config(argv);
     }
      //add>>
      else if(!strcmp(main_command, "add")){
          if(!strcmp(argv[2],"-f")) {
            for (int i = 3 ;i < argc;i++)
            add(argv[i]);
         }
         else if(!strcmp(argv[2], "-n")){
           check_with_staging_area();
         }
         else add(argv[2]);
      }
     //reset>>
     else if(!strcmp(main_command, "reset")) {
        reset(argv[2]);
     }
     //status>>
     else if(!strcmp(main_command, "status")){
        status();
     }
     //commit>>
     else if(!strcmp(main_command, "commit")){
        if(argc < 4){
            printf("Commit message please!\n");
            return 0;
        }
        if(commit(argv[3], argv[2]) == 0){
            printf("Commit successfully\n");
        }
     }
     //About shortcut messages>>
          //set_shortcut
          else if(!strcmp(main_command, "set")){
            set_shortcut(argv);
          }
          //replace_shortcut
          else if(!strcmp(main_command, "replace")){
            replace_shortcut(argv);
          }
          //remove_shortcut
          else if (!strcmp(main_command,"remove")){
            remove_shortcut(argv);
          }
     //Log>>
     else if(!strcmp(main_command, "log")){
        LOG(argc,argv);
     }
     //maybe it is an alias>>
     else if(!load_alias(argv[1])) {
        printf("\n Yes this was an alias\n");
     }
    // ??? Invalid ???
     else{
        printf("\nInvalid\n");
         exit(1);
     }
   return 0;
 }