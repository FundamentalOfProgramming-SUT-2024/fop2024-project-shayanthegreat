#include "scoreboard.h"
#include "main.h"
#include "connect.h"
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int get_folders_in_directory(char *path, char folders[MAX_FOLDERS][MAX_NAME_LEN]) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    int folder_count = 0;

    if (dir == NULL) {
        perror("opendir");
        return -1;  // Return error if directory can't be opened
    }

    while ((entry = readdir(dir)) != NULL) {
        // Check if entry is a directory (excluding '.' and '..')
        if (entry->d_type == 4 && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            // Store the folder name in the array
            if (folder_count < MAX_FOLDERS) {
                strncpy(folders[folder_count], entry->d_name, MAX_NAME_LEN - 1);
                folders[folder_count][MAX_NAME_LEN - 1] = '\0';  // Ensure null termination
                folder_count++;
            } else {
                printf("Reached the maximum folder limit!\n");
                break;
            }
        }
    }
    closedir(dir);
    return folder_count;
}

int compare_users(const void *a, const void *b) {
    const Userinfo *userA = (const Userinfo *)a;
    const Userinfo *userB = (const Userinfo *)b;

    if (userA->user_point != userB->user_point) {
        return userB->user_point - userA->user_point;
    }
    return userB->user_gold - userA->user_gold;
}

void sort_users(Userinfo *USERS, int n) {
    qsort(USERS, n, sizeof(Userinfo), compare_users);
}
void lister(int n, char folders[MAX_FOLDERS][MAX_NAME_LEN]) {
    Userinfo *USERS = malloc(n * sizeof(Userinfo));
    for (int i = 0; i < n; i++) {
        USERS[i] = Fetch_user2(folders[i]);
        strcpy(USERS[i].user_name,folders[i]);
    }
    sort_users(USERS, n);
    start_color();
    init_color(COLOR_YELLOW, 1000, 800, 400);
    init_color(COLOR_ORANGE, 1000, 647, 0);
    init_color(COLOR_GOLD, 1000, 843, 0);
    init_color(COLOR_SILVER, 753, 753, 753);
    init_color(COLOR_BRONZE, 804, 498, 196);
    init_pair(110, COLOR_RED, COLOR_BLACK);
    init_pair(111, COLOR_GREEN, COLOR_BLACK);
    init_pair(95, COLOR_RED, COLOR_BLACK);
    init_pair(85, COLOR_BLACK, COLOR_RED);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_ORANGE, COLOR_BLACK);
    init_pair(5, COLOR_GOLD, COLOR_BLACK);
    init_pair(6, COLOR_SILVER, COLOR_BLACK);
    init_pair(7, COLOR_BRONZE, COLOR_BLACK);
    
    // Create scrolling functionality
    int scroll_offset = 0;
    int ch;

    while (1) {
        clear();  // Clear the screen for each iteration
        
        attron(A_BOLD | COLOR_PAIR(5) | A_BLINK);
        mvprintw(LINES / 3, COLS / 2 - 5, "SCOREBOARD!");
        attroff(A_BOLD | COLOR_PAIR(5) | A_BLINK);

        attron(A_BOLD | COLOR_PAIR(5));
        mvprintw(LINES / 2 - 3, COLS / 3, "+------+----------------+----------+-----------+------------+-----------------+");
        attroff(A_BOLD | COLOR_PAIR(5));

        attron(COLOR_PAIR(3));
        mvprintw(LINES / 2 - 2, COLS / 3, "| Rank | Username       | Golds    | Points    | Experience | Games Finished  |");
        attroff(COLOR_PAIR(3));

        attron(A_BOLD | COLOR_PAIR(5));
        mvprintw(LINES / 2 - 1, COLS / 3, "+------+----------------+----------+-----------+------------+-----------------+");
        attroff(A_BOLD | COLOR_PAIR(5));
        int nowwww = time(NULL);
        for (int i = 0; i < 5; i++) {
            int index = i + scroll_offset;
            if (index >= n) break;
            if (index == 0) {
                attron(A_BOLD | COLOR_PAIR(5));
                mvprintw(LINES / 2 + i, COLS / 3 - 12, "Goat   🏅");
                mvprintw(LINES / 2 + i, COLS / 3, "| %-4d | %-14s | %-8d | %-9d | %-10d | %-15d |",
                         1, USERS[index].user_name, USERS[index].user_gold, USERS[index].user_point,
                         nowwww-USERS[index].user_exp, USERS[index].user_game);
                attroff(A_BOLD | COLOR_PAIR(5));
            } else if (index == 1) {
                attron(A_BOLD | COLOR_PAIR(6));
                mvprintw(LINES / 2 + i, COLS / 3 - 12, "Legend 🥈");
                mvprintw(LINES / 2 + i, COLS / 3, "| %-4d | %-14s | %-8d | %-9d | %-10d | %-15d |",
                         2, USERS[index].user_name, USERS[index].user_gold, USERS[index].user_point,
                         nowwww-USERS[index].user_exp, USERS[index].user_game);
                attroff(A_BOLD | COLOR_PAIR(6));
            } else if (index == 2) {
                attron(A_BOLD | COLOR_PAIR(7));
                mvprintw(LINES / 2 + i, COLS / 3 - 12, "PRO    🥉");
                mvprintw(LINES / 2 + i, COLS / 3, "| %-4d | %-14s | %-8d | %-9d | %-10d | %-15d |",
                         3, USERS[index].user_name, USERS[index].user_gold, USERS[index].user_point,
                         nowwww-USERS[index].user_exp, USERS[index].user_game);
                attroff(A_BOLD | COLOR_PAIR(7));
            } else {
                mvprintw(LINES / 2 + i, COLS / 3, "| %-4d | %-14s | %-8d | %-9d | %-10d | %-15d |",
                         index + 1, USERS[index].user_name, USERS[index].user_gold, USERS[index].user_point,
                         nowwww-USERS[index].user_exp, USERS[index].user_game);
            }
            if(strcmp(USERS[index].user_name,userinfo->user_name) == 0){
                mvprintw(LINES / 2 + i, COLS / 3-3, "->");
            }
        }

        // Table footer

        attron(A_BOLD | COLOR_PAIR(5));
        mvprintw(LINES / 2 + 5, COLS / 3, "+------+----------------+----------+-----------+------------+-----------------+");

        attroff(A_BOLD | COLOR_PAIR(5));
        refresh();

        // Get user input for scrolling
        ch = getch();
        if (ch == KEY_DOWN && scroll_offset + 5 < n) {
            scroll_offset++;
        } else if (ch == KEY_UP && scroll_offset > 0) {
            scroll_offset--;
        } else if (ch == 'q') {
            break;  // Exit on 'q'
        }
    }
    
    free(USERS);
    clear();
}
