/*****************************
 * NAME- Martin Hochman
 * PROJECT- Práce s textem
 * DATE- 15.11.2020
 * ***************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 1025
#define MAX_SIZE_CLM 100
#define ERROR_EXIT -1

//irow R - vloží řádek tabulky před řádek R > 0 (insert-row).
void irow(char separator, int count_of_cols)
{
    for (int op = 1; op < count_of_cols; op++)
    {
        fprintf(stdout, "%c", separator);
    }
    fprintf(stdout, "\n");
}
//cset C STR - do buňky ve sloupci C bude nastaven řetězec STR.
void cset(int pos_cset, char *text_cset, char *line, char *separator, char end_sign)
{
    int actual_col = 1;
    int op = 0;
    bool cset_pass = false;
    do
    {
        if (actual_col == pos_cset && !cset_pass)
        {
            fprintf(stdout, "%s", text_cset);
            cset_pass = true;
        }
        if (strchr(separator, line[op]) != NULL)
        {
            actual_col++;
            fprintf(stdout, "%c", separator[0]);
            if (actual_col == pos_cset && !cset_pass)
            {
                fprintf(stdout, "%s", text_cset);
                cset_pass = true;
            }
        }
        else if (actual_col != pos_cset)
        {
            fprintf(stdout, "%c", line[op]);
        }
        op++;
    } while (line[op] != end_sign);
    fprintf(stdout, "\n");
}
//tolower C - řetězec ve sloupci C bude převeden na malá písmena.
void tolower_column(int pos_tolower, char *line, char *separator, char end_sign)
{
    int actual_col = 1;
    int op = 0;
    do
    {
        if (actual_col == pos_tolower)
        {
            if (line[op] > 64 && line[op] < 91)
                line[op] += 32;
        }
        if (strchr(separator, line[op]) != NULL)
        {
            actual_col++;
        }
        fprintf(stdout, "%c", line[op]);
        op++;
    } while (line[op] != end_sign);
    fprintf(stdout, "\n");
}
//toupper C - řetězec ve sloupci C bude převeden na velká písmena.
void toupper_column(int pos_toupper, char *line, char *separator, char end_sign)
{
    int actual_col = 1;
    int op = 0;
    do
    {
        if (actual_col == pos_toupper)
        {
            if (line[op] > 96 && line[op] < 123)
                line[op] -= 32;
        }
        if (strchr(separator, line[op]) != NULL)
        {
            actual_col++;
        }
        fprintf(stdout, "%c", line[op]);
        op++;
    } while (line[op] != end_sign);
    fprintf(stdout, "\n");
}
//int C - odstraní desetinnou část čísla ve sloupci C.
void convert_column_to_int(char *int_column, char *line, int pos_int, char *separator, char end_sign)
{
    int int_number = atoi(int_column);
    int actual_col = 1;
    bool int_pass = false;
    for (int op = 0; line[op] != end_sign; op++)
    {
        if (actual_col == pos_int && !int_pass)
        {
            fprintf(stdout, "%d", int_number);
            int_pass = true;
        }
        if (strchr(separator, line[op]) != NULL)
        {
            actual_col++;
            fprintf(stdout, "%c", separator[0]);
        }
        else if (actual_col != pos_int)
        {
            fprintf(stdout, "%c", line[op]);
        }
    }
    fprintf(stdout, "\n");
}
//round C - ve sloupci C zaokrouhlí číslo na celé číslo.
void round_number_in_column(char *line, int pos_round, char *round_column, char *separator, char end_sign)
{
    float number = atof(round_column);
    if (number < 0)
        number -= 0.5;
    else
        number += 0.5;
    int rounded_number = number;
    int actual_col = 1;
    bool round_pass = false;
    for (int op = 0; line[op] != end_sign; op++)
    {
        if (actual_col == pos_round && !round_pass)
        {
            fprintf(stdout, "%d", rounded_number);
            round_pass = true;
        }
        if (strchr(separator, line[op]) != NULL)
        {
            actual_col++;
            fprintf(stdout, "%c", separator[0]);
        }
        else if (actual_col != pos_round)
        {
            fprintf(stdout, "%c", line[op]);
        }
    }
    fprintf(stdout, "\n");
}
//copy N M - přepíše obsah buněk ve sloupci M hodnotami ze sloupce N.
void copy(char *line, char *copy_column, int pos_copy, char *separator, char end_sign)
{
    int actual_col = 1;
    bool copy_pass = false;
    for (int op = 0; line[op] != end_sign; op++)
    {
        if (actual_col == pos_copy && !copy_pass)
        {
            fprintf(stdout, "%s", copy_column);
            copy_pass = true;
        }
        if (strchr(separator, line[op]) != NULL)
        {
            actual_col++;
            fprintf(stdout, "%c", separator[0]);
            if (actual_col == pos_copy)
            {
                fprintf(stdout, "%s", copy_column);
                copy_pass = true;
            }
        }
        else if (actual_col != pos_copy)
        {
            fprintf(stdout, "%c", line[op]);
        }
    }
    fprintf(stdout, "\n");
}
//swap N M - zamění hodnoty buněk ve sloupcích N a M.
void swap(char *line, int pos_swap_n, int pos_swap_m, char *swap_m_column, char *swap_n_column, char *separator, char end_sign)
{
    int actual_col = 1;
    bool swap_m_pass = false;
    bool swap_n_pass = false;
    for (int op = 0; line[op] != end_sign; op++)
    {
        if (actual_col == pos_swap_n && !swap_m_pass)
        {
            fprintf(stdout, "%s", swap_m_column);
            swap_m_pass = true;
        }
        if (actual_col == pos_swap_m && !swap_n_pass)
        {
            fprintf(stdout, "%s", swap_n_column);
            swap_n_pass = true;
        }
        if (strchr(separator, line[op]) != NULL)
        {
            actual_col++;
            fprintf(stdout, "%c", separator[0]);
            if (actual_col == pos_swap_n && !swap_m_pass)
            {
                fprintf(stdout, "%s", swap_m_column);
                swap_m_pass = true;
            }
            if (actual_col == pos_swap_m && !swap_n_pass)
            {
                fprintf(stdout, "%s", swap_n_column);
                swap_n_pass = true;
            }
        }
        else if (actual_col != pos_swap_n && actual_col != pos_swap_m)
        {
            fprintf(stdout, "%c", line[op]);
        }
    }
    fprintf(stdout, "\n");
}
//move N M - přesune sloupec N před sloupec M.
void move(int pos_move_n, int pos_move_m, char *line, char *move_column, char *separator, char end_sign)
{
    int actual_col = 1;
    int op = 0;
    bool move_pass = false;
    do
    {
        if (actual_col == pos_move_m && !move_pass)
        {
            fprintf(stdout, "%s", move_column);
            actual_col++;
            fprintf(stdout, "%c", separator[0]);
            op--;
            move_pass = true;
        }
        else if (strchr(separator, line[op]) != NULL)
        {
            actual_col++;
            if (actual_col - 1 != pos_move_n)
            {
                fprintf(stdout, "%c", separator[0]);
            }
        }
        else
        {
            if (pos_move_n > pos_move_m && (actual_col != pos_move_m && (actual_col - 1) != pos_move_n))
            {
                fprintf(stdout, "%c", line[op]);
            }
            if (pos_move_n < pos_move_m && (actual_col != pos_move_m && actual_col != pos_move_n))
            {
                fprintf(stdout, "%c", line[op]);
            }
        }
        op++;
    } while (line[op] != end_sign);

    fprintf(stdout, "\n");
}
//Zkontroluje jestli aktuální řádek je v selekci rows
bool rows(int actual_row, int position_n, int position_m)
{
    if (actual_row >= position_n && actual_row <= position_m)
    {
        return true;
    }
    else
    {
        if (actual_row >= position_n && position_m == -1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
//zkontroluje jestli daný sloupec začíná daným textem
bool beginswith(char *line, char *beginswith_text, int pos_beginswith, char *separator, char end_sign)
{
    int actual_col = 1;
    char column_text[MAX_SIZE_CLM];
    int column_index = 0;
    for (int op = 0; line[op] != end_sign; op++)
    {
        if (strchr(separator, line[op]) != NULL)
        {
            actual_col++;
        }
        else if (actual_col == pos_beginswith)
        {
            column_text[column_index] = line[op];
            column_index++;
        }
    }
    char *pos = strstr(column_text, beginswith_text);
    if (pos - column_text == 0)
        return true;
    else
        return false;
}
//zkontroluje jestli daný sloupec obsahuje daný text
bool contains(char *line, char *contains_text, int pos_contains, char *separator, char end_sign)
{
    int actual_col = 1;
    char column_text[MAX_SIZE_CLM];
    int column_index = 0;
    for (int op = 0; line[op] != end_sign; op++)
    {
        if (strchr(separator, line[op]) != NULL)
        {
            actual_col++;
        }
        else if (actual_col == pos_contains)
        {
            column_text[column_index] = line[op];
            column_index++;
        }
    }
    char *pos = strstr(column_text, contains_text);
    if (pos)
        return true;
    else
        return false;
}

int main(int argc, char **argv)
{
    char line[MAX_SIZE];
    char *separator = " ";
    int read_line = 0;
    int index = 0;
    int x = 0;
    int actual_row = 0;
    int count_cols = 1;
    int actual_col = 1;

    //Proměnné pro úpravu tabulky
    int pos_irow = 0;
    int pos_drow_r = 0;
    int pos_drow_n = 0;
    int pos_drow_m = 0;
    int pos_icol = 0;
    int pos_dcol_c = 0;
    int pos_dcols_n = 0;
    int pos_dcols_m = 0;

    bool irow_active = false;
    bool arow_active = false;
    bool drow_r_active = false;
    bool drow_n_m_active = false;
    bool icol_active = false;
    bool sep_vlozen = false;
    bool acol_active = false;
    bool dcol_active = false;
    bool dcols_active = false;
    bool write_allowed = true;

    //Proměnné pro zpracování dat
    int pos_cset = 0;
    int pos_tolower = 0;
    int pos_toupper = 0;
    int pos_round = 0;
    int length_round = 0;
    int pos_int = 0;
    int length_int = 0;
    int pos_copy_n = 0;
    int pos_copy_m = 0;
    int length_copy = 0;
    int pos_swap_n = 0;
    int pos_swap_m = 0;
    int length_swap_n = 0;
    int length_swap_m = 0;
    int pos_move_n = 0;
    int pos_move_m = 0;
    int length_move = 0;

    char *text_cset;
    char int_column[MAX_SIZE_CLM];
    char round_column[MAX_SIZE_CLM];
    char copy_column[MAX_SIZE_CLM];
    char swap_n_column[MAX_SIZE_CLM];
    char swap_m_column[MAX_SIZE_CLM];
    char move_column[MAX_SIZE_CLM];

    bool cset_active = false;
    bool tolower_active = false;
    bool toupper_active = false;
    bool round_active = false;
    bool int_active = false;
    bool copy_active = false;
    bool swap_active = false;
    bool move_active = false;

    //Proměnné pro selekcí řádků
    int pos_rows_n = 0;
    int pos_rows_m = 0;
    int pos_beginswith = 0;
    int pos_contains = 0;

    char *beginswith_text;
    char *contains_text;

    bool rows_active = false;
    bool last_row_active = false;
    bool beginswith_active = false;
    bool contains_active = false;
    bool selected_work = false;

    //uloží separátory
    if (argc > 2 && strcmp(argv[1], "-d") == 0)
    {
        separator = argv[2];
        index += 2;
    }

    //***PROCHÁZENÍ ARGUMENTŮ
    for (; index < argc; index++)
    {
        //irow R - vloží řádek tabulky před řádek R > 0 (insert-row).
        if (strcmp(argv[index], "irow") == 0)
        {
            pos_irow = atoi(argv[index + 1]);
            if (pos_irow > 0)
            {
                pos_irow--;
                irow_active = true;
                index++;
            }
            else
            {
                fprintf(stdout, "irow musí být větší než 0");
                return ERROR_EXIT;
            }
        }
        //arow - přidá nový řádek tabulky na konec tabulky (append-row).
        if (strcmp(argv[index], "arow") == 0)
        {
            arow_active = true;
        }
        //drow R - odstraní řádek číslo R > 0 (delete-row).
        if (strcmp(argv[index], "drow") == 0)
        {
            pos_drow_r = atoi(argv[index + 1]);
            if (pos_drow_r > 0)
            {
                drow_r_active = true;
                pos_drow_r--;
                index++;
            }
            else
            {
                fprintf(stdout, "drow musí být větší než 0");
                return ERROR_EXIT;
            }
        }
        //drows N M - odstraní řádky N až M (N <= M). V případě N=M se příkaz chová stejně jako drow N.
        if (strcmp(argv[index], "drows") == 0)
        {
            pos_drow_n = atoi(argv[index + 1]);
            pos_drow_m = atoi(argv[index + 2]);
            if (pos_drow_n > 0)
            {
                if (pos_drow_n <= pos_drow_m)
                {
                    if (pos_drow_n == pos_drow_m)
                    {
                        drow_r_active = true;
                        pos_drow_r = pos_drow_n - 1;
                        index++;
                    }
                    else
                    {
                        drow_n_m_active = true;
                        pos_drow_n--;
                        pos_drow_m--;
                        index += 2;
                    }
                }
                else
                {
                    fprintf(stdout, "N nemůže být větší než M");
                    return ERROR_EXIT;
                }
            }
            else
            {
                fprintf(stdout, "drow musí být větší než 0");
                return ERROR_EXIT;
            }
        }
        //icol C - vloží prázdný sloupec před sloupec daný číslem C.
        if (strcmp(argv[index], "icol") == 0)
        {
            pos_icol = atoi(argv[index + 1]);
            if (pos_icol > 0)
            {
                icol_active = true;
                index++;
            }
            else
            {
                fprintf(stdout, "icol musí být větší než 0");
                return ERROR_EXIT;
            }
        }
        //acol - přidá prázdný sloupec za poslední sloupec.
        if (strcmp(argv[index], "acol") == 0)
        {
            acol_active = true;
        }
        //dcol C - odstraní sloupec číslo C.
        if (strcmp(argv[index], "dcol") == 0)
        {
            pos_dcol_c = atoi(argv[index + 1]);
            if (pos_dcol_c > 0)
            {
                dcol_active = true;
                index++;
            }
            else
            {
                fprintf(stdout, "dcol musí být větší než 0");
                return ERROR_EXIT;
            }
        }
        //dcols N M - odstraní sloupce N až M (N <= M). V případě N=M se příkaz chová stejně jako dcol N.
        if (strcmp(argv[index], "dcols") == 0)
        {
            pos_dcols_n = atoi(argv[index + 1]);
            pos_dcols_m = atoi(argv[index + 2]);
            if (pos_dcols_n > 0)
            {
                if (pos_dcols_n <= pos_dcols_m)
                {
                    if (pos_dcols_n == pos_dcols_m)
                    {
                        pos_dcol_c = pos_dcols_n;
                        dcol_active = true;
                        index += 2;
                    }
                    else
                    {
                        dcols_active = true;
                        index += 2;
                    }
                }
                else
                {
                    fprintf(stdout, "N nemůže být větší než M");
                    return ERROR_EXIT;
                }
            }
            else
            {
                fprintf(stdout, "dcols musí být větší než 0");
                return ERROR_EXIT;
            }
        }
        //Zpracování dat
        //cset C STR - do buňky ve sloupci C bude nastaven řetězec STR.
        if (strcmp(argv[index], "cset") == 0)
        {
            pos_cset = atoi(argv[index + 1]);
            if (pos_cset > 0)
            {
                text_cset = argv[index + 2];
                cset_active = true;
                index += 2;
            }
            else
            {
                fprintf(stdout, "cset musí být větší než 0");
                return ERROR_EXIT;
            }
        }
        //tolower C - řetězec ve sloupci C bude převeden na malá písmena.
        if (strcmp(argv[index], "tolower") == 0)
        {
            pos_tolower = atoi(argv[index + 1]);
            if (pos_tolower > 0)
            {
                tolower_active = true;
                index++;
            }
            else
            {
                fprintf(stdout, "tolower musí být větší než 0");
                return ERROR_EXIT;
            }
        }
        //toupper C - řetězec ve sloupce C bude převeden na velká písmena.
        if (strcmp(argv[index], "toupper") == 0)
        {
            pos_toupper = atoi(argv[index + 1]);
            if (pos_toupper > 0)
            {
                toupper_active = true;
                index++;
            }
            else
            {
                fprintf(stdout, "toupper musí být větší než 0");
                return ERROR_EXIT;
            }
        }
        //zkontroluje jestli argument = round C
        if (strcmp(argv[index], "round") == 0)
        {
            pos_round = atoi(argv[index + 1]);
            if (pos_round > 0)
            {
                round_active = true;
                index++;
            }
            else
            {
                fprintf(stdout, "round musí být větší než 0");
                return ERROR_EXIT;
            }
        }
        //zkontroluje jestli argument = int C
        if (strcmp(argv[index], "int") == 0)
        {
            pos_int = atoi(argv[index + 1]);
            if (pos_int > 0)
            {
                int_active = true;
                index++;
            }
            else
            {
                fprintf(stdout, "int musí být větší než 0");
                return ERROR_EXIT;
            }
        }
        //zkontroluje jestli argument = copy N M
        if (strcmp(argv[index], "copy") == 0)
        {
            pos_copy_n = atoi(argv[index + 1]);
            pos_copy_m = atoi(argv[index + 2]);
            if (pos_copy_n > 0 && pos_copy_m > 0)
            {
                copy_active = true;
                index += 2;
            }
            else
            {
                fprintf(stdout, "copy musí být větší než 0");
                return ERROR_EXIT;
            }
        }
        //zkontroluje jestli argument = swap N M
        if (strcmp(argv[index], "swap") == 0)
        {
            pos_swap_n = atoi(argv[index + 1]);
            pos_swap_m = atoi(argv[index + 2]);
            if (pos_swap_n > 0 && pos_swap_m > 0)
            {
                swap_active = true;
                index += 2;
            }
            else
            {
                fprintf(stdout, "špatně zadaný parametry swap");
                return ERROR_EXIT;
            }
        }
        //zkontroluje jestli argument = move N M
        if (strcmp(argv[index], "move") == 0)
        {
            pos_move_n = atoi(argv[index + 1]);
            pos_move_m = atoi(argv[index + 2]);
            if (pos_move_n > 0 && pos_move_m > 0)
            {
                move_active = true;
                index += 2;
            }
            else
            {
                fprintf(stdout, "špatně zadaný parametry move");
                return ERROR_EXIT;
            }
        }
        //SELEKCE
        if (strcmp(argv[index], "rows") == 0)
        {
            if (strcmp(argv[index + 1], "-") == 0 && strcmp(argv[index + 2], "-") == 0)
            {
                pos_rows_n = -1;
                pos_rows_m = -1;
                last_row_active = true;
                index += 2;
            }
            else
            {
                pos_rows_n = atoi(argv[index + 1]);
                if (pos_rows_n > 0)
                {
                    pos_rows_n--;
                    if (strcmp(argv[index + 2], "-") == 0)
                    {
                        pos_rows_m = -1;
                        last_row_active = true;
                    }
                    else
                    {
                        pos_rows_m = atoi(argv[index + 2]);
                        if (pos_rows_m <= pos_rows_n)
                        {
                            int help = pos_rows_n;
                            pos_rows_n = pos_rows_m;
                            pos_rows_m = help;
                        }
                        pos_rows_m--;
                    }
                    rows_active = true;
                    index += 2;
                }
                else
                {
                    fprintf(stdout, "Rows musí být větší než 0");
                    return ERROR_EXIT;
                }
            }
        }
        if (strcmp(argv[index], "beginswith") == 0)
        {
            pos_beginswith = atoi(argv[index + 1]);
            if (pos_beginswith > 0)
            {
                beginswith_text = argv[index + 2];
                beginswith_active = true;
                index += 2;
            }
            else
            {
                fprintf(stdout, "Beginswith musí být větší než 0");
                return ERROR_EXIT;
            }
        }
        if (strcmp(argv[index], "contains") == 0)
        {
            pos_contains = atoi(argv[index + 1]);
            if (pos_contains > 0)
            {
                contains_text = argv[index + 2];
                contains_active = true;
                index += 2;
            }
            else
            {
                fprintf(stdout, "Contains musí být větší než 0");
                return ERROR_EXIT;
            }
        }
    }
    //***ZPRACOVANÁNÍ JEDNOTLIVÝCH METOD
    while ((x = getc(stdin)) != EOF)
    {
        line[read_line] = x;
        read_line++;

        //***POČÍTAČ ŘÁDKŮ
        if (strcmp((char *)(&x), "\n") == 0)
        {
            if (acol_active)
            {
                fprintf(stdout, "%c", separator[0]);
            }
            if (irow_active)
            {
                if (pos_irow == actual_row)
                {
                    irow(separator[0], count_cols);
                    actual_row++;
                }
            }
            // Kontroluje jestli se s aktuálním řádkem má pracovat podle zvolené selekce
            if (rows_active)
            {
                selected_work = rows(actual_row, pos_rows_n, pos_rows_m);
            }
            if (beginswith_active)
            {
                selected_work = beginswith(line, beginswith_text, pos_beginswith, separator, '\n');
            }
            if (contains_active)
            {
                selected_work = contains(line, contains_text, pos_contains, separator, '\n');
            }
            //Pokud s aktuálním řádkem nemá pracovat promaže se pole dané metody
            if (!selected_work)
            {
                if (swap_active)
                {
                    memset(swap_n_column, 0, sizeof swap_n_column);
                    memset(swap_m_column, 0, sizeof swap_m_column);
                }
                if (copy_active)
                {
                    memset(copy_column, 0, sizeof copy_column);
                }
                if (move_active)
                {
                    memset(move_column, 0, sizeof move_column);
                }
                if (int_active)
                {
                    memset(int_column, 0, sizeof int_column);
                }
                if (round_active)
                {
                    memset(round_column, 0, sizeof round_column);
                }
            }

            //***ÚPRAVA DAT, POKUD JSOU V SELEKCI
            if (selected_work)
            {
                //CSET
                if (cset_active)
                {
                    cset(pos_cset, text_cset, line, separator, '\n');
                }
                //TOLOWER
                if (tolower_active)
                {
                    tolower_column(pos_tolower, line, separator, '\n');
                }
                //TOUPPER
                if (toupper_active)
                {
                    toupper_column(pos_toupper, line, separator, '\n');
                }
                //INT
                if (int_active)
                {
                    convert_column_to_int(int_column, line, pos_int, separator, '\n');
                    memset(int_column, 0, sizeof int_column);
                }
                //ROUND
                if (round_active)
                {
                    round_number_in_column(line, pos_round, round_column, separator, '\n');
                    memset(round_column, 0, sizeof round_column);
                }
                //COPY
                if (copy_active)
                {
                    copy(line, copy_column, pos_copy_m, separator, '\n');
                    memset(copy_column, 0, sizeof copy_column);
                }
                //SWAP
                if (swap_active)
                {
                    swap(line, pos_swap_n, pos_swap_m, swap_m_column, swap_n_column, separator, '\n');
                    memset(swap_m_column, 0, sizeof swap_m_column);
                    memset(swap_n_column, 0, sizeof swap_n_column);
                }
                //MOVE
                if (move_active)
                {
                    move(pos_move_n, pos_move_m, line, move_column, separator, '\n');
                    memset(move_column, 0, sizeof move_column);
                }
            }
            //Celý řádek se vypíše pouze pokud není v selekci a pracuje se s celým řádkem a úpravou dat, jinak se vypisuje po znacích
            else if (!arow_active && !dcol_active && !dcols_active && !icol_active && !acol_active && !drow_n_m_active && !drow_r_active)
            {
                fprintf(stdout, "%s", line);
            }

            actual_col = 1;
            actual_row++;
            memset(line, 0, sizeof line);
            read_line = 0;
            length_copy = 0;
            length_swap_n = 0;
            length_swap_m = 0;
            length_move = 0;
            length_round = 0;
            length_int = 0;
            sep_vlozen = false;
            if (dcol_active || dcols_active)
            {
                write_allowed = true;
            }
        }
        else
        {
            //dcol pokud C je 1
            if (dcol_active && pos_dcol_c == 1)
            {
                if (pos_dcol_c == actual_col)
                {
                    write_allowed = false;
                }
                else
                {
                    write_allowed = true;
                }
            }
            //dcols pokud N je 1
            if (dcols_active && pos_dcols_n == 1)
            {
                if (actual_col <= pos_dcols_m && actual_col >= pos_dcols_n)
                {
                    write_allowed = false;
                }
                else
                {
                    write_allowed = true;
                }
            }
            //icol pokud pozice vložení je 1
            if (pos_icol == 1 && icol_active)
            {
                if (actual_col == pos_icol && !sep_vlozen)
                {
                    fprintf(stdout, "%c", separator[0]);
                    sep_vlozen = true;
                }
            }
            //***KONTROLUJE AKTUÁLNÍ SLOUPEC
            if (strcmp((char *)(&x), separator) == 0)
            {
                if (cset_active)
                {
                    write_allowed = true;
                }
                if (actual_row == 0)
                {
                    count_cols++;
                }
                actual_col++;
            }
            else
            {
                //Ukládá hodnoty ve sloupci, které chceme kopírovat, do pole
                if (copy_active && pos_copy_n == actual_col)
                {
                    copy_column[length_copy] = x;
                    length_copy++;
                }
                //Ukladá hodnoty ve sloupcích, které chceme prohodit, do pole
                if (swap_active)
                {
                    if (pos_swap_n == actual_col)
                    {
                        swap_n_column[length_swap_n] = x;
                        length_swap_n++;
                    }
                    if (pos_swap_m == actual_col)
                    {
                        swap_m_column[length_swap_m] = x;
                        length_swap_m++;
                    }
                }
                //Ukládá hodnoty ve sloupci, který chceme přesunout, do pole
                if (move_active && pos_move_n == actual_col)
                {
                    move_column[length_move] = x;
                    length_move++;
                }
                //Ukládá hodnoty ve sloupci, který chceme zaokrouhlit, do pole
                if (round_active && pos_round == actual_col)
                {
                    round_column[length_round] = x;
                    length_round++;
                }
                //Ukládá hodnoty ve sloupci, které chceme převést na celé číslo, do pole
                if (int_active && pos_int == actual_col)
                {
                    int_column[length_int] = x;
                    length_int++;
                }
            }
            //icol pokud pozice vložení je větší než 1
            if (pos_icol > 1 && icol_active)
            {
                if (actual_col == pos_icol && !sep_vlozen)
                {
                    fprintf(stdout, "%c", separator[0]);
                    sep_vlozen = true;
                }
            }
            //drow R
            if (drow_r_active)
            {
                if (actual_row == pos_drow_r)
                {
                    write_allowed = false;
                }
                else if (!write_allowed)
                {
                    write_allowed = true;
                }
            }
            //drow N M
            if (drow_n_m_active)
            {
                if ((actual_row <= pos_drow_m) && (actual_row >= pos_drow_n))
                {
                    write_allowed = false;
                }
                else if (!write_allowed)
                {
                    write_allowed = true;
                }
            }
            //dcol pokud C je větší než 1
            if (dcol_active && pos_dcol_c > 1)
            {
                if (pos_dcol_c == actual_col)
                {
                    write_allowed = false;
                }
                else
                {
                    write_allowed = true;
                }
            }
            //dcols pokud N je větší než 1
            if (dcols_active && pos_dcols_n > 1)
            {
                if (actual_col <= pos_dcols_m && actual_col >= pos_dcols_n)
                {
                    write_allowed = false;
                }
                else
                {
                    write_allowed = true;
                }
            }
        }
        //Vypisuje se po znacích pouze pokud se nejedná o úpravu dat
        if (write_allowed && !cset_active && !tolower_active && !toupper_active && !irow_active && !copy_active && !swap_active && !move_active && !round_active && !int_active)
        {
            fprintf(stdout, "%c", x);
        }
    }
    //*******************************Pracuje pouze s posledním řádkem*********************************
    //Zkontroluje jestli poslední řádek prochází danou selekcí
    if (beginswith_active)
    {
        selected_work = beginswith(line, beginswith_text, pos_beginswith, separator, '\0');
    }
    if (contains_active)
    {
        selected_work = contains(line, contains_text, pos_contains, separator, '\0');
    }
    if (last_row_active || (beginswith_active && selected_work) || (contains_active && selected_work))
    {
        //COPY
        if (copy_active)
        {
            copy(line, copy_column, pos_copy_m, separator, '\0');
        }
        //CSET
        if (cset_active)
        {
            cset(pos_cset, text_cset, line, separator, '\0');
        }
        //TOLOWER
        if (tolower_active)
        {
            tolower_column(pos_tolower, line, separator, '\0');
        }
        //TOUPPER
        if (toupper_active)
        {
            toupper_column(pos_toupper, line, separator, '\0');
        }
        //INT
        if (int_active)
        {
            convert_column_to_int(int_column, line, pos_int, separator, '\0');
            memset(int_column, 0, sizeof int_column);
        }
        //ROUND
        if (round_active)
        {
            round_number_in_column(line, pos_round, round_column, separator, '\0');
            memset(round_column, 0, sizeof round_column);
        }
        //SWAP
        if (swap_active)
        {
            swap(line, pos_swap_n, pos_swap_m, swap_m_column, swap_n_column, separator, '\0');
            memset(swap_m_column, 0, sizeof swap_m_column);
            memset(swap_n_column, 0, sizeof swap_n_column);
        }
        //MOVE
        if (move_active)
        {
            move(pos_move_n, pos_move_m, line, move_column, separator, '\0');
            memset(move_column, 0, sizeof move_column);
        }
    }
    //Pokud řádek není v selekci, tak se vypíše, kromě prací s tabulkou, to se vypisuje po znacích 
    else if (!arow_active && !dcol_active && !dcols_active && !icol_active && !acol_active && !drow_n_m_active && !drow_r_active)
    {
        if (irow_active && actual_row == pos_irow)
        {
            irow(separator[0], count_cols);
        }
        fprintf(stdout, "%s", line);
    }
    // arow
    if (arow_active)
    {
        fprintf(stdout, "\n");
        irow(separator[0], count_cols);
    }
    // acol
    if (acol_active)
    {
        fprintf(stdout, "%c", separator[0]);
    }
}