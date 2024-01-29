/* Include libraries */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libgen.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define Find_a_Repository           \
  if (strcmp(main_command, "init")) \
                                    \
  {                                 \
    while (!dir_exists(".sgit"))    \
      \                           
                                                                                                                                                                                                                                                                   \
      {                             \
        chdir("..");                \
      }                             \
  }

// tree --sort ctime -I "*time*|-a"

/* Function Declaration */

int dir_exists(char *path)
{
  struct stat st;
  if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void print_word_in_another_colour(char *word, char *str)
{
  char *pos = strstr(str, word);
  int index = pos - str;

  printf("%.*s\033[1;31m%s\033[0m%s\n", index, str, word, pos + strlen(word));
}

int min(int a, int b)
{
  return (a < b) ? a : b;
}

int is_null_space(char *str)
{
  while (*str)
  {
    if (!isspace(*str))
    {
      return 0;
    }
    str++;
  }
  return 1;
}

int strcmp_ignore_spaces(char *s1, char *s2)
{
  s1[strcspn(s1, "\n")] = '\0';
  s2[strcspn(s2, "\n")] = '\0';
  while (*s1 && *s2)
  {
    if (isspace(*s1))
    {
      s1++;
      continue;
    }
    if (isspace(*s2))
    {
      s2++;
      continue;
    }
    if (*s1 != *s2)
    {
      return *s1 - *s2;
    }
    s1++;
    s2++;
  }
  return *s1 - *s2;
}

int isvalid_command(const char *command)
{
  char buffer[128];
  snprintf(buffer, sizeof(buffer), "type %s >/dev/null 2>&1", command);
  return system(buffer) == 0;
}

void copy(char *path, char *dest)
{
  char command[1024];
  sprintf(command, "cp -ur %s %s", path, dest);
  system(command);
}

char *find_email()
{
  FILE *fp = NULL;
  char *email = malloc(128 * sizeof(char));
  int file1Exists = access("/mnt/c/Users/hadij/useremail.txt", F_OK) != -1;
  int file2Exists = access(".sgit/useremail.txt", F_OK) != -1;

  if (!file1Exists && !file2Exists)
  {
    perror("please set your email\n");
    exit(1);
  }

  if (file1Exists && file2Exists)
  {
    struct stat file1Stat, file2Stat;
    int err = stat("/mnt/c/Users/hadij/useremail.txt", &file1Stat);
    if (err != 0)
    {
      perror("Error: ");
      exit(1);
    }
    err = stat(".sgit/useremail.txt", &file2Stat);
    if (err != 0)
    {
      perror("Error: ");
      exit(1);
    }
    if (file1Stat.st_mtime > file2Stat.st_mtime)
    {
      printf("Opening file1.\n");
      fp = fopen("/mnt/c/Users/hadij/useremail.txt", "r");
      if (fp == NULL)
      {
        perror("Error: ");
        exit(1);
      }
    }
    else
    {
      printf("Opening file2.\n");
      fp = fopen(".sgit/useremail.txt", "r");
      if (fp == NULL)
      {
        perror("Error: ");
        exit(1);
      }
    }
  }

  else if (file1Exists)
  {
    printf("Opening file1.\n");
    fp = fopen("/mnt/c/Users/hadij/useremail.txt", "r");
    if (fp == NULL)
    {
      perror("Error\n");
      exit(1);
    }
  }

  else
  {
    printf("Opening file2.\n");
    fp = fopen(".sgit/useremail.txt", "r");
    if (fp == NULL)
    {
      perror("Error\n");
      exit(1);
    }
  }
  fscanf(fp, "%[^\\n]s", email);
  fclose(fp);

  return email;
}

char *find_name()
{
  FILE *fp = NULL;
  char *name = malloc(128 * sizeof(char));
  int file1Exists = access("/mnt/c/Users/hadij/username.txt", F_OK) != -1;
  int file2Exists = access(".sgit/username.txt", F_OK) != -1;

  if (!file1Exists && !file2Exists)
  {
    perror("please set your name\n");
    exit(1);
  }

  if (file1Exists && file2Exists)
  {
    struct stat file1Stat, file2Stat;
    int err = stat("/mnt/c/Users/hadij/username.txt", &file1Stat);
    if (err != 0)
    {
      perror("Error: ");
      exit(1);
    }
    err = stat(".sgit/username.txt", &file2Stat);
    if (err != 0)
    {
      perror("Error: ");
      exit(1);
    }
    if (file1Stat.st_mtime > file2Stat.st_mtime)
    {
      printf("Opening file1.\n");
      fp = fopen("/mnt/c/Users/hadij/username.txt", "r");
      if (fp == NULL)
      {
        perror("Error: ");
        exit(1);
      }
    }
    else
    {
      printf("Opening file2.\n");
      fp = fopen(".sgit/username.txt", "r");
      if (fp == NULL)
      {
        perror("Error: ");
        exit(1);
      }
    }
  }

  else if (file1Exists)
  {
    printf("Opening file1.\n");
    fp = fopen("/mnt/c/Users/hadij/username.txt", "r");
    if (fp == NULL)
    {
      perror("Error\n");
      exit(1);
    }
  }

  else
  {
    printf("Opening file2.\n");
    fp = fopen(".sgit/username.txt", "r");
    if (fp == NULL)
    {
      perror("Error\n");
      exit(1);
    }
  }
  fscanf(fp, "%[^\\n]s", name);
  fclose(fp);

  return name;
}

void set_shortcut(char **argv)
{
  FILE *fp = fopen(".sgit/shortcut.txt", "a");
  fputs(argv[3], fp);
  fprintf(fp, "|");
  fputs(argv[5], fp);
  fprintf(fp, "\n");
  fclose(fp);
}

void remove_shortcut(char **argv)
{
  bool flag = false;
  FILE *fp = fopen(".sgit/shortcut.txt", "r");
  FILE *temp_file = fopen(".sgit/temp.txt", "w");
  char buffer[1024];

  while (fgets(buffer, sizeof(buffer), fp))
  {
    char *temp = strchr(buffer, '|');
    temp++;
    temp[strcspn(temp, "\n")] = '\0';
    if (!strcmp(temp, argv[3]))
    {
      flag = true;
      continue;
    }
    fputs(buffer, temp_file);
  }

  fclose(temp_file);
  fclose(fp);

  remove(".sgit/shortcut.txt");
  rename(".sgit/temp.txt", ".sgit/shortcut.txt");

  if (flag)
  {
    printf("The shortcut removed\n");
  }
  else
  {
    printf("Ther is not any shortcut with name %s\n", argv[3]);
  }
}

void replace_shortcut(char **argv)
{
  bool flag = false;
  FILE *fp = fopen(".sgit/shortcut.txt", "r");
  FILE *temp_file = fopen(".sgit/temp.txt", "w");
  char buffer[1024];

  while (fgets(buffer, sizeof(buffer), fp))
  {
    char *temp = strchr(buffer, '|');
    temp++;
    temp[strcspn(temp, "\n")] = '\0';
    if (!strcmp(temp, argv[5]))
    {
      fprintf(temp_file, "%s|%s\n", argv[3], argv[5]);
      flag = true;
    }
    else
    {
      fputs(buffer, temp_file);
    }
  }

  fclose(temp_file);
  fclose(fp);

  remove(".sgit/shortcut.txt");
  rename(".sgit/temp.txt", ".sgit/shortcut.txt");

  if (flag)
  {
    printf("The shortcut replaced\n");
  }
  else
  {
    printf("Ther is not any shortcut with name %s\n", argv[5]);
  }
}

void Find_shortcut_message(char *name)
{
  char copy[512];
  strcpy(copy, name);
  bool flag = false;
  FILE *fp = fopen(".sgit/shortcut.txt", "r");
  if (fp == NULL)
  {
    printf("Try again\n");
    exit(1);
  }
  char buffer[1024];
  while (fgets(buffer, sizeof(buffer), fp))
  {
    char *temp = strchr(buffer, '|');
    temp++;
    temp[strcspn(temp, "\n")] = '\0';
    if (!strcmp(temp, copy))
    {
      int len = temp - buffer;
      char substr[len];
      strncpy(substr, buffer, len);
      substr[len - 1] = '\0';
      flag = true;
      strcpy(name, substr);
      break;
    }
  }

  fclose(fp);

  if (!flag)
  {
    printf("Ther is not any shortcut with name %s\n", copy);
    exit(1);
  }
}

char *find_current_branch()
{
  char *branch = (char *)calloc(128, sizeof(char));
  FILE *fp = fopen(".sgit/.branches/current_branch.txt", "r");
  if (fp == NULL)
  {
    exit(1);
  }
  fgets(branch, sizeof(branch), fp);
  fclose(fp);
  return branch;
}

int find_current_commitID()
{
  FILE *fp = fopen(".sgit/.branches/CurrentCommitID.txt", "r");
  if (fp == NULL)
  {
    exit(1);
  }
  unsigned int ID = 100;
  fscanf(fp, "%u", &ID);
  fclose(fp);
  return ID;
}

int count_of_master_commits_upto_now()
{
  FILE *fp = fopen(".sgit/.commits/log.txt", "r");
  if (!fp)
  {
    exit(1);
  }
  int count = 0;
  char buffer[512];
  while (fgets(buffer, sizeof(buffer), fp))
  {
    if (!strncmp(buffer, "number", 6))
    {
      count++;
    }
  }
  fclose(fp);
  return count;
}

void show_branches_list()
{
  FILE *fp = fopen(".sgit/.branches/BranchesList.txt", "r");
  if (!fp)
  {
    exit(1);
  }
  char buffer[512];
  while (fgets(buffer, sizeof(buffer), fp))
  {
    char *name = strchr(buffer, '|');
    puts(name);
  }

  fclose(fp);
}

int isnumber(char *string)
{
  uid_t i = 0;
  while (string[i])
  {
    if (!isdigit(string[i]))
    {
      return 0;
    }
    i++;
  }
  return 1;
}

int HEAD_of_branch(char *branch_name)
{
  FILE *fp = fopen(".sgit/.commits/log.txt", "r");
  if (fp == NULL)
  {
    exit(1);
  }
  int ID;
  char buffer1[1024];
  char buffer2[1024];

  while (fgets(buffer1, sizeof(buffer1), fp))
  {
    if (!strncmp(buffer1, "number", 6))
    {
      fgets(buffer2, sizeof(buffer2), fp);
      if (!strncmp(buffer2, branch_name, strlen(branch_name)))
      {
        sscanf(buffer1, "number%d\n", &ID);
      }
    }
  }

  fclose(fp);
  return ID;
}

void push_stash(int argc, char **argv)
{
  char command[1024] = "rsync -a --exclude=\".*\" . .sgit/.stash/ ";
  system(command);

  FILE *fp = fopen(".sgit/stash.txt", "w");
  if (fp == NULL)
  {
    exit(1);
  }
  fprintf(fp, "Entry0|");
  char *branch = find_current_branch();
  fprintf(fp, " In branch : %s ", branch);
  free(branch);
  if (argc == 5)
  {
    fprintf(fp, " with message : %s ", argv[4]);
  }
  fprintf(fp, "\n");
  int commit_ID;
  FILE *current_commit = fopen(".sgit/.branches/CurrentCommitID.txt", "r");
  fscanf(current_commit, "%d", &commit_ID);
  fclose(current_commit);
  fprintf(fp, "On Commit:%d", commit_ID);
  fclose(fp);
  printf("Push seccessfully\n");
}

void push_list()
{
  FILE *fp = fopen(".sgit/stash.txt", "r");
  if (fp == NULL)
  {
    exit(1);
  }

  char buffer[256];
  fgets(buffer, sizeof(buffer) - 1, fp);
  char *temp = strchr(buffer, '|');
  temp++;
  printf("Entry 0 :\n");
  puts(temp);

  fclose(fp);
}

void clear_stash()
{
  system("rm -r  .sgit/.stash");
  system("rm .sgit/stash.txt");
  printf("Stashed changes are cleared.\n");
}

void diff(char *file1, char *file2, char *lines1, char *lines2)
{
  bool diffrent = false;
  char path1[512], path2[512];
  realpath(file1, path1);
  realpath(file2, path2);
  uid_t start_line1, start_line2;
  uid_t end_line1, end_line2;
  sscanf(lines1, "%d-%d", &start_line1, &end_line1);
  sscanf(lines2, "%d-%d", &start_line2, &end_line2);
  int len1 = end_line1 - start_line1 + 1;
  int len2 = end_line2 - start_line2 + 1;
  FILE *f1 = fopen(path1, "r"), *f2 = fopen(path2, "r");
  char buffer1[512], buffer2[512];
  for (int i = 1; i < start_line1; i++)
  {
    fgets(buffer1, sizeof(buffer1), f1);
  }
  for (int j = 1; j < start_line2; j++)
  {
    fgets(buffer2, sizeof(buffer2), f2);
  }
  int min_len = min(len1, len2);
  for (int i = 0, j = 0; i < min_len && j < min_len;)
  {
    while (i < min_len && fgets(buffer1, sizeof(buffer1), f1) && is_null_space(buffer1))
    {
      i++;
    }
    while (j < min_len && fgets(buffer2, sizeof(buffer2), f2) && is_null_space(buffer2))
    {
      j++;
    }

    if (feof(f1) || feof(f2))
    {
      break;
    }
    if (strcmp_ignore_spaces(buffer1, buffer2))
    {
      diffrent = true;

      printf("File : %s-> Line : %d\n", file1, start_line1 + i);
      printf("%s%s%s", ANSI_COLOR_RED, buffer1, ANSI_COLOR_RESET);
      printf("\n");

      printf("File : %s-> Line : %d\n", file2, start_line2 + j);
      printf("%s%s%s", ANSI_COLOR_BLUE, buffer2, ANSI_COLOR_RESET);
      printf("\n");
    }
  }
  if (diffrent)
  {
    if (len1 == len2)
    {
      printf("The end of files\n");
    }
    else if (len1 > len2)
    {
      printf("The end of file 2 \n");
    }
    else if (len2 > len1)
    {
      printf("The end of file1 \n");
    }
    printf("**********\n");
  }
}

void diff_directories(char *dir1, char *dir2)
{
  char cmd[128], buffer[512];
  sprintf(cmd, "diff -qr %s %s ", dir1, dir2);
  printf("%s\n", dir1);
  printf("%s\n", dir2);
  printf("%s\n", cmd);
  FILE *fp = popen(cmd, "r");
  if (fp == NULL)
  {
    printf("try again\n");
    exit(1);
  }
  while (fgets(buffer, sizeof(buffer), fp))
  {
    if (!strncmp(buffer, "Only", strlen("Only")))
    {
      char *temp = strrchr(buffer, ':');
      temp += 2;
      printf("\nThe file : %s is only in one of them\n\n", temp);
    }
    else
    {
      char *file1 = strtok(buffer, " ");
      file1 = strtok(NULL, " ");
      char *file2 = strtok(NULL, " ");
      file2 = strtok(NULL, " ");
      diff(file1, file2, "1-10000", "1-10000");
    }
  }
  pclose(fp);
}

void show_stash_diff()
{
  char cwd[128];
  getcwd(cwd, 128);
  FILE *fp = fopen(".sgit/stash.txt", "r");
  if (fp == NULL)
  {
    printf("Try again!\n");
    exit(1);
  }
  char line[128];

  // Ignore first line
  fgets(line, sizeof(line), fp);

  fgets(line, sizeof(line), fp);
  char *ID = strchr(line, ':');
  ID++;
  ID[strcspn(ID, "\n")] = '\0';
  char path_to_commit[128];
  char path_to_stash[128];
  sprintf(path_to_commit, "%s/.sgit/.commits/number%s", cwd, ID);
  sprintf(path_to_stash, "%s/.sgit/.stash", cwd);
  diff_directories(path_to_commit, path_to_stash);
}

int revert_to_backup(const char *backup_path, const char *current_path)
{
  DIR *dir;
  struct dirent *entry;

  dir = opendir(backup_path);
  if (dir == NULL)
  {
    perror("Unable to open stash\n");
    return 1;
  }

  while ((entry = readdir(dir)) != NULL)
  {
    if (entry->d_name[0] == '.')
    {
      continue;
    }

    char source_path[1024];
    snprintf(source_path, sizeof(source_path), "%s/%s", backup_path, entry->d_name);

    char dest_path[1024];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", current_path, entry->d_name);

    if (entry->d_type == DT_DIR)
    {
      mkdir(dest_path, 0700);
      revert_to_backup(source_path, dest_path);
    }
    else
    {
      if (rename(source_path, dest_path))
      {
        perror("Error moving file");
        closedir(dir);
        return 1;
      }
    }
  }

  closedir(dir);
  return 0;
}

void append_tag(char *tag_name, char *message, int commit_ID, bool can_owerwrite)
{
  FILE *fp = fopen(".sgit/tags.txt", "r+");
  if (fp == NULL)
  {
    fp = fopen(".sgit/tags.txt", "w");
    fclose(fp);
  }

  char *name = find_name();
  char *email = find_email();
  char line[256];
  while (fgets(line, sizeof(line), fp))
  {
    char *temp = strchr(line, ':');
    if (temp == NULL)
      continue;
    temp++;
    temp[strcspn(temp, "\n")] = '\0';
    if (!strcmp(temp, tag_name))
    {
      if (!can_owerwrite)
      {
        printf("The tag is already exists\n");
        exit(0);
      }

      fprintf(fp, "%s\n%d\n%s\n%s\n", message, commit_ID, name, email);
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      fprintf(fp, "%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
      fprintf(fp, "\n");
      printf("***The tag OwerWrited successfully***\n");
      fclose(fp);
      return;
    }
  }

  fprintf(fp, "tag:%s\n%s\n%d\n%s\n%s\n", tag_name, message, commit_ID, name, email);

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  fprintf(fp, "%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  fprintf(fp, "\n");
  fclose(fp);
  printf("***The tag Appended successfuly***\n");
}

int pstrcmp(const void *a, const void *b)
{
  return strcmp(*(const char **)a, *(const char **)b);
}

void tag_list()
{
  FILE *fp = fopen(".sgit/tags.txt", "r");
  if (fp == NULL)
  {
    printf("Error: could not open file\n");
    return 1;
  }

  char **lines = malloc(128 * sizeof(char *));
  for (int i = 0; i < 128; i++)
  {
    lines[i] = malloc(1024 * sizeof(char));
  }
  size_t n = 0;
  char temp[1024];
  while (fgets(temp, 1000, fp))
  {
    if (!strncmp(temp, "tag:", 4))
    {
      strcpy(lines[n], temp);
      n++;
    }
  }

  qsort(lines, n, sizeof(char *), pstrcmp);

  printf("\n<< Sorting Alphabetically >>\n\n");
  for (int i = 0; i < n; i++)
  {
    printf("number : %d -->  ", (i + 1));
    printf("%s\n", lines[i]);
  }

  for (int i = 0; i < 128; i++)
  {
    free(lines[i]);
  }
  free(lines);
  fclose(fp);
}

void show_tag(const char *tag_name)
{
  FILE *fp = fopen(".sgit/tags.txt", "r");
  if (fp == NULL)
  {
    printf("Error: could not open file\n");
    exit(1);
  }
  char buffer[512];
  char **lines = malloc(128 * sizeof(char *));
  while (fgets(buffer, 500, fp))
  {
    char *temp = strchr(buffer, ':');
    if (temp == NULL)
      continue;
    temp++;
    temp[strcspn(temp, "\n")] = '\0';
    if (!strcmp(temp, tag_name))
    {
      printf("*****\n");
      printf("tag with Name : %s\n", tag_name);
      fgets(buffer, 500, fp);
      printf("wit message : %s", buffer);
      fgets(buffer, 500, fp);
      printf("with commit ID : %s", buffer);
      fgets(buffer, 500, fp);
      printf("Author name : %s", buffer);
      fgets(buffer, 500, fp);
      printf("Author email : %s", buffer);
      fgets(buffer, 500, fp);
      printf("Date and Time of tag : %s", buffer);
      printf("*****\n");

      fclose(fp);
      return;
    }
  }

  fclose(fp);
  printf("The tag with name \"%s\" not found!!\n", tag_name);
}




#include "information.h"

void create_hidden_dir()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("Error getting current working directory");
        return;
    }
    int found = 0;
    char path[1024];
    strcpy(path, cwd);
    while (1)
    {
        strcat(path, "/.sgit");
        if (dir_exists(path))
        {
            printf("\nError : Already a repository exists in %s\n\n", path);
            found = 1;
            break;
        }
        path[strlen(path) - 6] = '\0';
        if (strcmp(path, "/") == 0)
        {
            break;
        }
        strcpy(path, dirname(path));
    }
    if (!found)
    {

        strcpy(path, cwd);
        strcat(path, "/.sgit");
        mkdir(path, 0777);

        char path_of_commits[1024];
        char path_of_branches[1024];

        strcpy(path_of_commits, cwd);
        strcat(path_of_commits, "/.sgit/.commits");
        mkdir(path_of_commits, 0777);

        strcpy(path_of_branches, cwd);
        strcat(path_of_branches, "/.sgit/.branches");
        mkdir(path_of_branches, 0777);

        FILE *fp = fopen(".sgit/.commits/hash_commit.txt", "w");
        if (fp == NULL)
        {
            exit(1);
        }
        fprintf(fp, "%d", 100);
        fclose(fp);
        fp = fopen(".sgit/.commits/log.txt", "w");
        if (fp == NULL)
        {
            exit(1);
        }
        fclose(fp);

        fp = fopen(".sgit/.branches/current_branch.txt", "w");
        if (fp == NULL)
        {
            exit(1);
        }
        fprintf(fp, "Master");
        fclose(fp);

        fp = fopen(".sgit/.branches/BranchesList.txt", "w");
        if (fp == NULL)
        {
            exit(1);
        }
        fprintf(fp, "0|Master\n");
        fclose(fp);

        fp = fopen(".sgit/.precommit/hooks.txt", "w");
        if (fp == NULL)
        {
            exit(1);
        }
        fprintf(fp, "0 ck-size-f\n0 character-limit\n0 balance-braces\n0 eof-blank-space\n0 static-error-check\n0 indentation-check\n");
        fclose(fp);

         fp = fopen(".sgit/.precommit/situation.txt", "w");
        if (fp == NULL)
        {
            exit(1);
        }
        fprintf(fp, "TRUE");
        fclose(fp);

        printf("Created a local repository in %s\n", path);
    }
    else
        printf("error!!\n");
}

void add(char *name)
{
    char input[1024];
    if (realpath(name, input) == NULL)
    {
        printf("\nError resolving input path\n");
        return;
    }
    if (access(input, F_OK) != 0)
    {
        perror("Error accessing input path");
        return;
    }
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("Error getting current working directory");
        return;
    }
    char dest[100];
    strcpy(dest, cwd);
    strcat(dest, "/.sgit/.staging");
    if (access(dest, F_OK) != 0)
    {
        mkdir(dest, 0777);
    }
    copy(input, dest);
    printf("\nAdd with success\n");
}

void check_with_staging_area()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("Error getting current working directory");
        return;
    }
    char base[2048];
    sprintf(base, "%s/.sgit/.staging", cwd);
    DIR *dir = opendir(cwd);
    if (dir == NULL)
    {
        perror("Error opening current directory");
        exit(1);
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        char temp[2048];
        sprintf(temp, "%s/%s", base, entry->d_name);
        if (!access(temp, F_OK))
        {
            printf("\n*** %s is in staging area ***\n", entry->d_name);
        }
        else
        {
            printf("\n%s is not staged\n", entry->d_name);
        }
    }
}

void reset(char *path)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("Error getting current working directory");
        return;
    }
    char full_path[1024];
    sprintf(full_path, "%s/.sgit/.staging/%s", cwd, path);
    char buffer[1024];
    sprintf(buffer, "rm -r %s ", full_path);
    if (system(buffer) == 0)
    {
        printf("\nreset is done\n");
    }
    else
    {
        perror("\ncaan not reset this\n");
    }
}

void config_alias(char **argv)
{
    if (!strcmp(argv[2], "-global"))
    {
        FILE *alias = fopen("/mnt/c/Users/hadij/alias.txt", "a");
        char *name_of_alias = strtok(argv[3], ".");
        memmove(name_of_alias, name_of_alias + 1, strlen(name_of_alias));
        char alias_command[100];
        strcpy(alias_command, argv[4]);
        if (!isvalid_command(alias_command))
        {
            perror("\nInvalid command \n");
            exit(1);
        }
        else
        {
            char buffer[1000];
            strcpy(buffer, name_of_alias);
            strcat(buffer, " ");
            strcat(buffer, alias_command);
            strcat(buffer, "\n");
            fputs(buffer, alias);
        }
        fclose(alias);
    }
    else
    {
        FILE *alias = fopen(".sgit/alias.txt", "a");
        char *name_of_alias = strstr(argv[2], ".");
        memmove(name_of_alias, name_of_alias + 1, strlen(name_of_alias));
        char alias_command[100];
        strcpy(alias_command, argv[3]);
        if (!isvalid_command(alias_command))
        {
            perror("\nInvalid command \n");
            exit(1);
        }
        else
        {
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

void Set_Config(char **argv)
{
    char cwd[1024];
    getcwd(cwd, 1000);
    puts(cwd);
    FILE *config = NULL;
    if (!strcmp(argv[2], "-global"))
    {
        if (!strcmp(argv[3], "user.name"))
            config = fopen("/mnt/c/Users/hadij/username.txt", "w");
        else if (!strcmp(argv[3], "user.email"))
            config = fopen("/mnt/c/Users/hadij/useremail.txt", "w");
        else
        {
            config_alias(argv);
            return;
        }
    }
    else if (!strcmp(argv[2], "user.name"))
        config = fopen(".sgit/username.txt", "w");
    else if (!strcmp(argv[2], "user.email"))
        config = fopen(".sgit/useremail.txt", "w");
    else
    {
        config_alias(argv);
        return;
    }
    if (config == NULL)
    {
        printf("Try again!\n");
        exit(1);
    }
    else
    {
        if (!strcmp(argv[2], "-global"))
        {
            fputs(argv[4], config);
        }
        else
        {
            fputs(argv[3], config);
        }
        fclose(config);
        printf("The config is now set\n");
    }
}

int load_alias(char *alias_name)
{
    char line[300];
    FILE *alias;

    if ((alias = fopen(".sgit/alias.txt", "r")) != NULL)
    {
        while (fgets(line, 300, alias) != NULL)
        {
            char *aliases = strtok(line, " ");
            char *command = strtok(NULL, "\n");
            if (!strcmp(aliases, alias_name))
            {
                system(command);
                fclose(alias);
                return 0;
            }
        }
        fclose(alias);
    }

    if ((alias = fopen("/mnt/c/Users/hadij/alias.txt", "r")) != NULL)
    {
        while (fgets(line, 300, alias) != NULL)
        {
            char *aliases = strtok(line, " ");
            char *command = strtok(NULL, "\n");
            if (!strcmp(aliases, alias_name))
            {
                system(command);
                fclose(alias);
                return 0;
            }
        }
        fclose(alias);
    }

    return -1;
}

void status()
{
    FILE *fp;
    char buffer[256];
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/.sgit/.staging");
    if (!dir_exists(cwd))
    {
        printf("Ther is not anything in staging area!!\nSo we compare with current commit\n\n");
        int commit_ID;
        FILE *current_commit = fopen(".sgit/.branches/CurrentCommitID.txt", "r");
        if (current_commit == NULL)
        {
            printf("Try again!\n");
            exit(1);
        }
        fscanf(current_commit, "%d", &commit_ID);
        fclose(current_commit);
        char cwd2[256];
        getcwd(cwd2, sizeof(cwd2));
        sprintf(cwd, "%s/.sgit/.commits/number%d", cwd2, commit_ID);
    }
    char command[512];
    sprintf(command, "diff -srq  %s . ", cwd);
    fp = popen(command, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error opening pipe\n");
        exit(1);
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        char temp[1024];
        sscanf(buffer, "%s ", temp);
        // The FILE is in both directories but Deleted or OK ?
        if (strcmp(temp, "Only"))
        {
            sscanf(buffer + 6, "%s ", temp);
            char *name = strrchr(temp, '/');
            if (*name == '.')
                continue;
            char *situation = strrchr(buffer, ' ');
            situation++;
            // Modified
            if (!strcmp(situation, "differ\n"))
            {
                printf("%s : +M \n", name + 1);
            }
            // As the same
            else if (!strcmp(situation, "identical\n"))
            {
                printf("%s : +A \n", name + 1);
            }
        }
        // Only in one directory
        else
        {
            char name[256];
            sscanf(buffer, "%*s %*s %*s %s ", name);
            // ignore  . and .. and hidden directories
            if (*name == '.')
                continue;
            // A or D ?
            if (buffer[8] == '.')
            {
                printf("%s : -A \n", name);
            }
            else if (buffer[8] == '/')
            {
                printf("%s : +D \n", name);
            }
        }
    }
    pclose(fp);
}

int commit(char *mess, char *swith)
{
    char cwd[1024];
    char path_of_staging[1024];
    char path_of_commits[1024];
    char buffer[2048];

    if (!strcmp(swith, "-s"))
    {
        Find_shortcut_message(mess);
    }

    getcwd(cwd, sizeof(cwd));
    strcpy(path_of_staging, cwd);
    strcat(path_of_staging, "/.sgit/.staging");
    if (!dir_exists(path_of_staging))
    {
        perror("Please add something\n");
        return -1;
    }
    if (strlen(mess) > 72)
    {
        perror("the message is too long\n");
        return -1;
    }
    if(!precommit_situation())
    {
        perror("\n!!Warning!!\nYou have some failed hooks!\n\n");
        exit(1);
    }
    int commit_ID = 0;
    FILE *hash = fopen(".sgit/.commits/hash_commit.txt", "r");
    if (hash == NULL)
    {
        perror("Try again later\n");
        return -1;
    }
    fscanf(hash, "%d", &commit_ID);
    fclose(hash);
    hash = fopen(".sgit/.commits/hash_commit.txt", "w");
    commit_ID++;
    fprintf(hash, "%d", commit_ID);
    fclose(hash);
    FILE *current_commit = fopen(".sgit/.branches/CurrentCommitID.txt", "w");
    fprintf(current_commit, "%d", commit_ID);
    fclose(current_commit);

    sprintf(path_of_commits, ".sgit/.commits/number%d", commit_ID);

    FILE *original_FILE = fopen(".sgit/.commits/log.txt", "r");
    FILE *temp_FILE = fopen(".sgit/.commits/temp.txt", "w");
    char *name = find_name();
    char *email = find_email();
    char *branch = find_current_branch();
    fprintf(temp_FILE, "number%d\n%s\n%s\n%s\n%s\n", commit_ID, branch, mess, name, email);
    free(name);
    free(branch);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(temp_FILE, "%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    char *dir = ".sgit/.staging";
    char *command = "find ";
    char *options = "-type f -printf \"%p\\n\"";
    char *full_command = malloc(strlen(command) + strlen(dir) + strlen(options) + 1);
    sprintf(full_command, "%s%s %s", command, dir, options);
    FILE *fp;
    char path[1035];
    fp = popen(full_command, "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n");
        exit(1);
    }
    while (fgets(path, sizeof(path) - 1, fp))
    {
        char *tok = strchr(path, '/');
        tok++;
        tok = strchr(tok, '/');
        tok++;
        fputs(tok, temp_FILE);
    }
    fprintf(temp_FILE, "\n");

    char bufffer[1024];
    while (fgets(bufffer, sizeof(bufffer), original_FILE))
    {
        fprintf(temp_FILE, "%s", bufffer);
    }
    fclose(temp_FILE);

    remove(".sgit/.commits/log.txt");
    rename(".sgit/.commits/temp.txt", ".sgit/.commits/log.txt");

    pclose(fp);
    free(full_command);
    sprintf(buffer, "sudo mv %s* %s ", path_of_staging, path_of_commits);
    system(buffer);
    return 0;
}

void LOG(int argc, char **argv)
{
    size_t count_of_commits = 1;
    FILE *log = fopen(".sgit/.commits/log.txt", "r");
    if (!log)
    {
        perror("Error opening log FILE.");
        exit(1);
    }
    char line[1024];
    char line_branch[1024];
    char line_message[1024];
    char line_name[1024];
    char line_email[1024];
    char line_time[1024];
    bool flag = false;
    while ((fgets(line, sizeof(line), log)) != NULL)
    {
        if (!strncmp(line, "number", 6))
        {
            flag = false;
            fgets(line_branch, sizeof(line), log);
            fgets(line_message, sizeof(line), log);
            fgets(line_name, sizeof(line), log);
            fgets(line_email, sizeof(line), log);
            fgets(line_time, sizeof(line), log);

            int count_of_FILEs = 0;
            char temp_line[1024];
            do
            {
                fgets(temp_line, sizeof(line), log);
                count_of_FILEs++;
            } while (strcmp(temp_line, "\n"));
            count_of_FILEs--;

            static struct tm date1 = {0};
            static struct tm date2 = {0};
            char date_of_commit[128];
            strncpy(date_of_commit, line_time, 10);
            strptime(date_of_commit, "%Y-%m-%d", &date1);
            strptime(argv[3], "%Y-%m-%d", &date2);
            double diff = difftime(mktime(&date2), mktime(&date1));

            if (argc == 2)
            {
                flag = true;
            }
            else if (!strcmp(argv[2], "-n") && (count_of_commits <= atoi(argv[3])))
            {
                flag = true;
                count_of_commits++;
            }
            else if (!strcmp(argv[2], "-branch") && strstr(line_branch, argv[3]))
            {
                flag = true;
            }
            else if (!strcmp(argv[2], "-author") && strstr(line_name, argv[3]))
            {
                flag = true;
            }
            else if (!strcmp(argv[2], "-search") && strstr(line_message, argv[3]))
            {
                flag = true;
            }
            else if (!strcmp(argv[2], "-before") && (diff >= 0))
            {
                flag = true;
            }
            else if (!strcmp(argv[2], "-since") && (diff <= 0))
            {
                flag = true;
            }

            if (flag)
            {
                printf("\n********************\n");
                printf("Commit with Id %s ", line);
                printf("Commit message : %s ", line_message);
                printf("Author name : %s ", line_name);
                printf("Author email : %s ", line_email);
                printf("DATE and Time of Commit : %s ", line_time);
                printf("In branch : %s ", line_branch);
                printf("number of FILEs in this commit : %d \n", count_of_FILEs);
                printf("\n********************\n");
                printf("\n\n");
            }
        }
    }

    fclose(log);
}

void Run_branch_command(int argc, char **argv)
{
    if (argc == 2)
    {
        show_branches_list();
    }
    else
    {
        bool flag = false;
        FILE *fp = fopen(".sgit/.branches/BranchesList.txt", "a+");
        if (fp == NULL)
        {
            exit(1);
        }

        rewind(fp);
        char line[1024];
        char name_of_branch[128];
        strcpy(name_of_branch, argv[2]);

        while (fgets(line, sizeof(line), fp))
        {
            char *name = strchr(line, '|');
            name++;
            if (!strncmp(name, name_of_branch, strlen(name_of_branch)))
            {
                flag = true;
            }
        }

        if (flag)
        {
            printf("Ther is already a branch with this name!\n");
            exit(0);
        }

        int number = count_of_master_commits_upto_now();
        fprintf(fp, "%d|%s\n", number, name_of_branch);

        fclose(fp);
    }
}

void grep(int argc, char **argv)
{
    bool flag_n = false;
    if ((argc == 7 || argc == 9) && (!strcmp(argv[argc - 1], "-n")))
    {
        flag_n = true;
    }

    char file_path[512];
    if ((argc > 6) && (!strcmp(argv[6], "-c")))
    {
        sprintf(file_path, ".sgit/.commits/number%d/%s", atoi(argv[7]), argv[3]);
    }
    else
    {
        strcpy(file_path, argv[3]);
    }

    size_t count = 0;
    char line[1024];
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL)
    {
        exit(1);
    }

    char *word = argv[5];
    while (fgets(line, sizeof(line), fp))
    {
        count++;
        if (strstr(line, word))
        {
            if (flag_n)
            {
                printf("In line : %lu", count);
            }
            printf("--> ");
            print_word_in_another_colour(word, line);
            printf("\n");
        }
    }
}

void check_out(char *dest)
{

    // If this is HEAD
    if (!strcmp(dest, "HEAD"))
    {
        check_out("Master");
    }

    // If this is a commit ID>>
    else if (isnumber(dest))
    {
        char cwd[512];
        getcwd(cwd, sizeof(cwd));
        FILE *fp = fopen(".sgit/.commits/log.txt", "r");
        if (fp == NULL)
        {
            exit(1);
        }
        char number100[256] = "number";
        strcat(number100, dest);
        strcat(number100, "\n");
        char buffer[512];
        while (fgets(buffer, sizeof(buffer), fp))
        {
            if (!strcmp(buffer, number100))
            {
                fgets(buffer, sizeof(buffer), fp);
                fgets(buffer, sizeof(buffer), fp);
                fgets(buffer, sizeof(buffer), fp);
                fgets(buffer, sizeof(buffer), fp);
                fgets(buffer, sizeof(buffer), fp);

                while (1)
                {
                    fgets(buffer, sizeof(buffer), fp);
                    if (!strcmp(buffer, "\n"))
                    {
                        break;
                    }
                    buffer[strcspn(buffer, "\n")] = '\0';
                    number100[strcspn(number100, "\n")] = '\0';
                    char command[512];
                    sprintf(command, "rm %s ", buffer);
                    system(command);
                    sprintf(command, "cp -ur .sgit/.commits/%s/. %s ", number100, cwd);
                    system(command);
                }
                break;
            }
        }
        fclose(fp);
        FILE *current_commit = fopen(".sgit/.branches/CurrentCommitID.txt", "w");
        fprintf(current_commit, "%d", atoi(dest));
        fclose(current_commit);
    }

    // If this is a Branch name>>
    else
    {
        int ID_of_head_branch = HEAD_of_branch(dest);
        char temp[256];
        sprintf(temp, "%d", ID_of_head_branch);
        check_out(temp);
        FILE *fp = fopen(".sgit/.branches/current_branch.txt", "w");
        if (fp == NULL)
        {
            exit(1);
        }
        fputs(dest, fp);
        fclose(fp);
    }
}

void stash_command(int argc, char **argv)
{
    if (!strcmp(argv[2], "push"))
    {
        push_stash(argc, argv);
    }
    else if (!strcmp(argv[2], "list"))
    {
        push_list();
    }
    else if (!strcmp(argv[2], "show"))
    {
        show_stash_diff();
    }
    else if (!strcmp(argv[2], "pop"))
    {
        if (revert_to_backup("/mnt/c/Users/hadij/b/.sgit/.stash", ".") == 0)
        {
            printf("Pop was successful\nAnd\n");
            clear_stash();
        }
    }
    else if (!strcmp(argv[2], "clear"))
    {
        clear_stash();
    }
}

void Run_tag(int argc, char **argv)
{
    if (argc == 2)
    {
        tag_list();
    }
    else if (!strcmp(argv[2], "show"))
    {
        show_tag(argv[3]);
    }
    else
    {
        bool owerwrite = false;
        if (!strcmp(argv[argc - 1], "-f"))
            owerwrite = true;
        int commit_ID = find_current_commitID();
        if ((argc > 4) && !strcmp(argv[4], "-c"))
            commit_ID = atoi(argv[5]);
        else if ((argc > 6) && !strcmp(argv[6], "-c"))
            commit_ID = atoi(argv[7]);
        if ((argc > 4) && !strcmp(argv[4], "-m"))
        {
            append_tag(argv[3], argv[5], commit_ID, owerwrite);
            return;
        }
        append_tag(argv[3], "", commit_ID, owerwrite);
    }
}

void hook(int argc, char **argv)
{
    if (argc == 4)
    {
        bool all_or_applied = false;
        if (!strcmp(argv[3], "list"))
        {
            all_or_applied = true;
        }
        show_hooks(all_or_applied);
    }
    else 
    {
        int situation = 0;
        if(!strcmp(argv[2], "add"))
        {
            situation = 1;
        }
        change_list_of_hooks(situation, argv[4]);
    }
}

int main(int argc, char **argv)
{
    char main_command[100];
    strcpy(main_command, argv[1]);
    Find_a_Repository
        // init>>
        if (!strcmp(main_command, "init"))
    {
        create_hidden_dir();
        return 0;
    }
    // config>>
    if (!strcmp(main_command, "config"))
    {
        Set_Config(argv);
    }
    // add>>
    else if (!strcmp(main_command, "add"))
    {
        if (!strcmp(argv[2], "-f"))
        {
            for (int i = 3; i < argc; i++)
                add(argv[i]);
        }
        else if (!strcmp(argv[2], "-n"))
        {
            check_with_staging_area();
        }
        else
            add(argv[2]);
    }
    // reset>>
    else if (!strcmp(main_command, "reset"))
    {
        reset(argv[2]);
    }
    // status>>
    else if (!strcmp(main_command, "status"))
    {
        status();
    }
    // commit>>
    else if (!strcmp(main_command, "commit"))
    {
        if (argc < 4)
        {
            printf("Commit message please!\n");
            return 0;
        }
        if (commit(argv[3], argv[2]) == 0)
        {
            printf("Commit successfully\n");
            system("sgit log -n 1 ");
        }
    }
    // About shortcut messages>>
    // set_shortcut
    else if (!strcmp(main_command, "set"))
    {
        set_shortcut(argv);
    }
    // replace_shortcut
    else if (!strcmp(main_command, "replace"))
    {
        replace_shortcut(argv);
    }
    // remove_shortcut
    else if (!strcmp(main_command, "remove"))
    {
        remove_shortcut(argv);
    }
    // Log>>
    else if (!strcmp(main_command, "log"))
    {
        LOG(argc, argv);
    }
    // Branch command>>
    else if (!strcmp(main_command, "branch"))
    {
        Run_branch_command(argc, argv);
    }
    // Check out>>
    else if (!strcmp(main_command, "checkout"))
    {
        check_out(argv[2]);
    }
    // grep>>
    else if (!strcmp(main_command, "grep"))
    {
        grep(argc, argv);
    }
    // diff_command>>
    else if (!strcmp(main_command, "diff"))
    {
        if (!strcmp(argv[2], "-f"))
        {
            if (argc == 5)
                diff(argv[3], argv[4], "1-10000", "1-10000");
            else
                diff(argv[3], argv[4], argv[6], argv[8]);
        }
        else if (!strcmp(argv[2], "-c"))
        {
            char name_commit1[256], name_commit2[256];
            sprintf(name_commit1, ".sgit/.commits/number%d", atoi(argv[3]));
            sprintf(name_commit2, ".sgit/.commits/number%d", atoi(argv[4]));
            diff_directories(name_commit1, name_commit2);
        }
    }
    // stash>>
    else if (!strcmp(main_command, "stash"))
    {
        stash_command(argc, argv);
    }
    // tag>>
    else if (!strcmp(main_command, "tag"))
    {
        Run_tag(argc, argv);
    }
    // pre-commit>>
    else if (!strcmp(main_command, "pre-commit"))
    {
        if (argc == 2)
        {
            Check_pre_commit();
        }
        else
            hook(argc, argv);
    }
    // maybe it is an alias>>
    else if (!load_alias(argv[1]))
    {
        printf("\n Yes this was an alias\n");
    }
    // ??? Invalid ???
    else
    {
        printf("\nInvalid\n");
        exit(1);
    }
    return 0;
}