/********************************************************************************
 *     FILENAME           :    candidate.c
 *
 *     DESCRIPTION        :    Implementation of functions provided by utility.h
 *
 *     REVISION HISTORY   :
 *
 *     DATE                NAME              REFERENCE               REASON
 *     --------------------------------------------------------------------
 *     ==========        ==========          ==========            ==========
 *
 *     Copyright © 2022 Capgemini Group  All Rights Reserved
 *
 ********************************************************************************/

/********************************************************************************
 *                               HEADER FILES
 ********************************************************************************/
#include <utility.h>

/**********************************************************************************
 *     FUNCTION NAME    :   create_candidate_node
 *
 *     DESCRIPTION      :   Function to create a candidate node
 *
 *     PARAMETERS       :   Node **, char buff[]
 *
 *     RETURNS          :   None
 *********************************************************************************/
void create_candidate_node(
    CandidateNode **candidate_list_head, /* Head of candidate linked list */
    char buff[])                         /* buff array that stores 1 line of candidate.txt */
{
    if (*candidate_list_head == NULL)
    {
        /* Allocate memory for new head */
        CandidateNode *new_head = (CandidateNode *)malloc(sizeof(CandidateNode));

        /* Allocate memory for new candidate_detail */
        new_head->candidate_detail = (char *)malloc((MAX_BUFF_LEN + 1) * sizeof(char));

        /* Copy new candidate_detail to linked list */
        strcpy(new_head->candidate_detail, buff);

        /* Set head node */
        *candidate_list_head = new_head;

        /* Set next node null */
        (*candidate_list_head)->next = NULL;
        new_head = NULL;
    }
    else
    {
        /* Iterate to last node */
        CandidateNode *temp = *candidate_list_head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        /* Allocate memory for new node */
        CandidateNode *new_node = (CandidateNode *)malloc(sizeof(CandidateNode));

        /* Allocate memory for new candidate_detail */
        new_node->candidate_detail = (char *)malloc((MAX_BUFF_LEN + 1) * sizeof(char));

        /* Copy new candidate_detail to linked list */
        strcpy(new_node->candidate_detail, buff);

        /* Set next node null */
        new_node->next = NULL;

        /* Set last node */
        temp->next = new_node;
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   read_candidate_data
 *
 *     DESCRIPTION      :   Read data from candidate.txt and store in linked list
 *
 *     PARAMETERS       :   CandidateNode **
 *
 *     RETURNS          :   Total number of lines (unsigned int)
 *******************************************************************************/
unsigned int read_candidate_data(CandidateNode **candidate_list_head)
{
    /* Local variables */
    char const *const candidate_file = "../data/candidates.txt";
    unsigned int total_words = 0;
    FILE *candidate_filepointer = NULL;
    char buff[MAX_BUFF_LEN];

    /******************* Open File *******************/
    candidate_filepointer = fopen(candidate_file, APPENDMODE);

    /* Check */
    if (candidate_filepointer == NULL)
    {
        printf("Cannot open candidate.txt file\n");
        return FALSE;
    }

    /* read file and store each line in a global candidate linked list*/
    while (fgets(buff, MAX_BUFF_LEN, candidate_filepointer))
    {
        create_candidate_node(&(*candidate_list_head), buff);
        strcpy(buff, "");
        total_words++;
    }

    fclose(candidate_filepointer);

    return total_words;
}

/********************************************************************************
 *     FUNCTION NAME    :   display_candidate_data
 *
 *     DESCRIPTION      :   Iterate on cadidate linked list and display its content
 *
 *     PARAMETERS       :   CandidateNode **
 *
 *     RETURNS          :   Total number of lines (unsigned int)
 *******************************************************************************/
void display_candidate_data(CandidateNode *candidate_list_head)
{
    printf("\n");
    while (candidate_list_head != NULL)
    {
        printf("%s", candidate_list_head->candidate_detail);
        candidate_list_head = candidate_list_head->next;
    }
    printf("\n");
}

/********************************************************************************
 *     FUNCTION NAME    :   free_candidate_mem
 *
 *     DESCRIPTION      :   Function to free memory allocated on candidate list
 *
 *     PARAMETERS       :   CandidateNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void free_candidate_mem(CandidateNode **candidate_list_head)
{
    CandidateNode *curr = *candidate_list_head;
    while (curr != NULL)
    {
        char *str = curr->candidate_detail;
        curr = curr->next;
        free(str);
    }

    curr = *candidate_list_head;
    while (curr != NULL)
    {
        CandidateNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    *candidate_list_head = NULL;
}

/********************************************************************************
 *     FUNCTION NAME    :   candidate_login
 *
 *     DESCRIPTION      :   Prompts candidate to enter username and passowrd and
 *                          verifies these credentials with database, if verified,
 *                          candidate login is successful else login failed
 *
 *     PARAMETERS       :   CandidateNode *
 *
 *     RETURNS          :   None
 *******************************************************************************/
int candidate_login(CandidateNode *candidate_list_head)
{
    char username_input[MAX_BUFF_LEN],
        passowrd_input[MAX_BUFF_LEN];

    int candidate_id = 0;

    char *username_db,
        *password_db,
        *candidate_db,
        *copy_string;

    printf("\nEnter candidate username: ");
    fgets(username_input, MAX_BUFF_LEN, stdin);
    username_input[strlen(username_input) - 1] = '\0';

    printf("\nEnter candidate passowrd: ");
    fgets(passowrd_input, MAX_BUFF_LEN, stdin);
    passowrd_input[strlen(passowrd_input) - 1] = '\0';

    while (candidate_list_head != NULL)
    {
        copy_string = (char *)malloc((strlen(candidate_list_head->candidate_detail) + 1) * sizeof(char));
        strcpy(copy_string, candidate_list_head->candidate_detail);

        username_db = strtok(copy_string, DELIMITER);
        password_db = strtok(NULL, DELIMITER);
        candidate_db = strtok(NULL, DELIMITER);
        candidate_id = atoi(candidate_db);

        if (strcmp(username_input, username_db) == 0 && strcmp(passowrd_input, password_db) == 0)
        {
            free(copy_string);
            return candidate_id;
        }

        candidate_list_head = candidate_list_head->next;
        free(copy_string);
    }

    return EXIT_FAILURE;
}

/********************************************************************************
 *     FUNCTION NAME    :   check_marks
 *
 *     DESCRIPTION      :   candidate can check his marks
 *
 *     PARAMETERS       :   none
 *
 *     RETURNS          :   EXIT_SUCCESS or EXIT_FAILURE
 *******************************************************************************/
int check_marks(int candidate_id)
{
    /* Local variables */
    int test_id = 0;
    int flag1 = 0;
    int flag2 = 0;
    char *ptr = NULL;
    char string1[MAX_LEN];
    int n = 1;

    /*file pointers*/
    FILE *file1, *file2;

    /* Input candidate id from stdin */
    printf("\nEnter the Test id : ");
    scanf("%d", &test_id); // get candidate id from the candidate

    if ((file1 = fopen("../data/CandidateAnswers1.txt", "r")))
    {
        while (fgets(string1, MAX_LEN, file1))
        {
            if (feof(file1))
            {
                break;
            }
            // fgets(string1, MAX_LEN, file1);
            ptr = strtok(string1, DELIMITER);
            if (atoi(ptr) != candidate_id)
            {
                continue;
            }
            else if (atoi(ptr) == candidate_id)
            {
                ptr = strtok(NULL, DELIMITER);
                if (atoi(ptr) == test_id)
                {
                    flag1 = 1;
                }
                else
                {
                    continue;
                }
            }
        }
    }

    if (flag1 == 0)
    {
        printf("\nResults not present");
        return EXIT_FAILURE;
    }
    else if (flag1 == 1)
    {
        file2 = fopen("../data/interviews.txt", "r");
        while (fgets(string1, MAX_LEN, file2))
        {
            n = 1;
            // fgets(string1, MAX_LEN, file2);
            ptr = strtok(string1, DELIMITER);
            if (atoi(ptr) != candidate_id)
            {
                continue;
            }
            else if (atoi(ptr) == candidate_id)
            {
                flag2 = 1;
                printf("\n Candidate Id : %d", candidate_id);
                ptr = strtok(NULL, DELIMITER);
                if (atoi(ptr) == test_id)
                {
                    printf("\n Test Id : %d", test_id);
                    ptr = strtok(NULL, DELIMITER);
                    printf("\n date : %s", ptr);
                    ptr = strtok(NULL, DELIMITER);
                    printf("\n Attempted : %s", ptr);
                    ptr = strtok(NULL, DELIMITER);
                    while (ptr != NULL)
                    {
                        printf("\n Topic %d Marks : %s", n, ptr);
                        ptr = strtok(NULL, DELIMITER);
                        n++;
                    }
                }
            }
        }
    }

    if (flag2 == 0)
    {
        printf("\nResults were not calculated, Contact adminstrator");
    }
    ptr = NULL;

    // closing files
    fclose(file1);
    fclose(file2);

    return EXIT_SUCCESS;
}

/********************************************************************************
 *     FUNCTION NAME    :   check_marks
 *
 *     DESCRIPTION      :   candidate can check his marks
 *
 *     PARAMETERS       :   none
 *
 *     RETURNS          :   EXIT_SUCCESS or EXIT_FAILURE
 *******************************************************************************/
int appear_for_test(int candidate_id)
{
    // Local variables
    int n;
    int i;
    char string1[MAX_LEN];
    char date[DATE_MAX_LEN];
    char *arr1[8];
    // char *arr2[3];
    int arr3[3];
    char *ptr = NULL;
    int test_id;
    char attempt = 'N';

    // file pointers
    FILE *file1, *file2;

    file1 = fopen("../data/Topic1Questions.txt", "r");
    while (!feof(file1))
    {
        if (feof(file1))
        {
            break;
        }
        fgets(string1, MAX_LEN, file1);
        ptr = strtok(string1, DELIMITER);
    }

    test_id = atoi(ptr);

    file1 = fopen("../data/CandidateAnswers1.txt", "r"); // can us results.txt file as well
    while (!feof(file1))
    {
        if (feof(file1))
        {
            break;
        }
        fgets(string1, MAX_LEN, file1);
        ptr = strtok(string1, DELIMITER);
        if (atoi(ptr) != candidate_id)
        {
            continue;
        }
        else if (atoi(ptr) == candidate_id)
        {
            ptr = strtok(NULL, DELIMITER);
            if (atoi(ptr) == test_id)
            {
                attempt = 'Y';
                printf("\nTest Already Attempted\n");
                return EXIT_SUCCESS;
            }
            else
            {
                continue;
            }
        }
    }

    // input date
    printf("\nEnter today's date in dd/mm/yyyy format :");
    fgets(date, DATE_MAX_LEN, stdin);
    date[strcspn(date, "\n")] = 0;

    // attempted check

    for (n = 1; n <= 3; n++)
    {
        print_questions(candidate_id, test_id, n);
    }
    attempt = 'Y';

    // printf("\nSuccess");
    n = 1;
    for (i = 0; i <= 2; i++)
    {
        arr3[i] = calculate(candidate_id, n, test_id);
        n++;
    }

    file2 = fopen("../data/interviews.txt", "a");
    fprintf(file2, "%d,%d,%s,%c,%d,%d,%d\n", candidate_id, test_id, date, attempt, arr3[0], arr3[1], arr3[2]);
    printf("\nResults :\n Candidate Id : %d\n Test Id : %d\n Date : %s\n Attempted : %c\n Topic 1 Marks : %d\n Topic 2 Marks : %d\n Topic 3 Marks : %d\n", candidate_id, test_id, date, attempt, arr3[0], arr3[1], arr3[2]);

    ptr = NULL;
    fclose(file1);
    fclose(file2);
    return EXIT_SUCCESS;
}

/********************************************************************************
 *     FUNCTION NAME    :   print_questions
 *
 *     DESCRIPTION      :   prints questions
 *
 *     PARAMETERS       :   candidate_id,test_id,n
 *
 *     RETURNS          :   EXIT_SUCCESS or EXIT_FAILURE
 *******************************************************************************/
int print_questions(int candidate_id, int test_id, int n)
{

    // Local variables
    int k = 1;
    int ans;
    char string1[MAX_LEN];
    char string2[MAX_LEN];
    char *arr1[8];
    char *ptr = NULL;
    char ch;
    char *copystring;

    // file pointers
    FILE *file1, *file2;

    if (n == 1)
    {
        file1 = fopen("../data/Topic1Questions.txt", "r");
        file2 = fopen("../data/CandidateAnswers1.txt", "a");
        printf("\nTopic 1 test \n");
    }
    else if (n == 2)
    {
        file1 = fopen("../data/Topic2Questions.txt", "r");
        file2 = fopen("../data/CandidateAnswers2.txt", "a");
        printf("\nTopic 2 test \n");
    }
    else if (n == 3)
    {
        file1 = fopen("../data/Topic3Questions.txt", "r");
        file2 = fopen("../data/CandidateAnswers3.txt", "a");
        printf("\nTopic 3 test \n");
    }

    while (fgets(string1, MAX_LEN, file1))
    {
        if (feof(file1))
        {
            break;
        }
        // fgets(string1, MAX_LEN, file1);
        // copystring = (char *) malloc((strlen(string1)+1)*sizeof(char));
        // strcpy(copystring,string1);
        ptr = strtok(string1, DELIMITER);
        int i = 0;
        while (ptr != NULL)
        {
            arr1[i] = ptr;
            // printf("%s ",ptr);
            ptr = strtok(NULL, DELIMITER);
            i++;
        }

        printf("%d. %s\n", k, arr1[2]);
        k++;
        printf("1.%s 2.%s 3.%s 4.%s\n", arr1[3], arr1[4], arr1[5], arr1[6]);
        printf("Enter the correct option :");
        scanf("%d", &ans);
        fprintf(file2, "%d,%d,%s,%d\n", candidate_id, test_id, arr1[1], ans);
    }

    ptr = NULL;
    fclose(file1);
    fclose(file2);
    return EXIT_SUCCESS;
}

/********************************************************************************
 *     FUNCTION NAME    :   candidate_id_check
 *
 *     DESCRIPTION      :   Checks candidate id is correct or not    // If candidate id not present in candidate list/wrong candidate entered - FAILURE
 *
 *     PARAMETERS       :   cand_id
 *
 *     RETURNS          :   flag
 *******************************************************************************/
int candidate_check(int cand_id, int n)
{
    /* Local variables */
    int flag1 = FALSE;
    char string1[MAX_LEN];
    char *ptr = NULL;

    /*file pointers*/
    FILE *file1;

    if (n == 1)
    {
        file1 = fopen("../data/CandidateAnswers1.txt", "r");
    }
    else if (n == 2)
    {
        file1 = fopen("../data/CandidateAnswers2.txt", "r");
    }
    else if (n == 3)
    {
        file1 = fopen("../data/CandidateAnswers3.txt", "r");
    }
    while (!feof(file1))
    {
        if (feof(file1))
        {
            break;
        }
        fgets(string1, MAX_LEN, file1);
        ptr = strtok(string1, DELIMITER);
        if (atoi(ptr) != cand_id)
        {
            continue;
        }
        else if (atoi(ptr) == cand_id)
        {
            flag1 = TRUE;
            return flag1;
        }
    }

    fclose(file1);
    return flag1;
}

/********************************************************************************
 *     FUNCTION NAME    :  topic_marks_calculation
 *
 *     DESCRIPTION      :   Checks results already calculated or not
 *
 *     PARAMETERS       :   cand_id
 *
 *     RETURNS          :   flag
 *******************************************************************************/
int topic_marks(int candidate_id, int n, int test_id)
{
    /* Local variables */
    int marks = 0;
    char *arr1[4];
    char *arr2[8];
    char string1[MAX_LEN];
    char string2[MAX_LEN];
    char *ptr = NULL;

    /*file pointers*/
    FILE *file, *file1;
    if (n == 1)
    {
        file1 = fopen("../data/CandidateAnswers1.txt", "r");
        // printf("\nfile opened - 1");
    }
    else if (n == 2)
    {
        file1 = fopen("../data/CandidateAnswers2.txt", "r");
        // printf("\nfile opened - 1");
    }
    else if (n == 3)
    {
        file1 = fopen("../data/CandidateAnswers3.txt", "r");
        // printf("\nfile opened - 1");
    }
    while (!feof(file1))
    {
        if (feof(file1))
        {
            break;
        }
        // printf("\nIn while loop 1");
        fgets(string1, MAX_LEN, file1);
        ptr = strtok(string1, DELIMITER);
        if (atoi(ptr) != candidate_id)
        {
            continue;
        }
        else if (atoi(ptr) == candidate_id)
        {
            int i = 0;
            arr1[i] = ptr;
            i = i + 1;
            ptr = strtok(NULL, DELIMITER);
            if (atoi(ptr) == test_id)
            {
                while (ptr != NULL)
                {
                    // printf("\nIn while loop 2");
                    arr1[i] = ptr;
                    ptr = strtok(NULL, DELIMITER);
                    i++;
                }
            }
            else
            {
                continue;
            }

            int a1 = atoi(arr1[1]);

            // open questions.txt file
            file = fopen("../data/questions.txt", "r");

            while (!feof(file))
            {
                if (feof(file))
                {
                    break;
                }
                // printf("\nIn while loop 3");
                fgets(string2, MAX_LEN, file);
                ptr = strtok(string2, DELIMITER);
                int i = 0;
                while (ptr != NULL)
                {
                    arr2[i] = ptr;
                    ptr = strtok(NULL, DELIMITER);
                    i++;
                }
                if (a1 == test_id && atoi(arr1[2]) == atoi(arr2[1]))
                {
                    // printf("\nIn marks calculation");
                    if (atoi(arr1[3]) == atoi(arr2[7]))
                    {

                        // printf("%d",marks);
                        marks++;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }

    ptr = NULL;
    arr1[4] = NULL;
    arr2[8] = NULL;

    // closing files
    fclose(file1);
    fclose(file);

    return marks;
}

/********************************************************************************
 *     FUNCTION NAME    :   calculate_marks
 *
 *     DESCRIPTION      :   Calculate marks of of all tests appeared by the candidate and store them in interviews.txt file.
 *
 *     PARAMETERS       :   cand_id
 *
 *     RETURNS          :   EXIT_SUCCESS or EXIT_FAILURE
 *******************************************************************************/
int calculate(int candidate_id, int n, int test_id)
{
    /* Local variables */
    int cand_id;
    int marks = 0;
    bool flag1 = FALSE;
    char string1[MAX_LEN];
    char *ptr = NULL;

    flag1 = candidate_check(candidate_id, n);

    if (flag1)
    {
        if (n == 1)
        {
            marks = topic_marks(candidate_id, n, test_id);
        }
        else if (n == 2)
        {
            marks = topic_marks(candidate_id, n, test_id);
        }
        else if (n == 3)
        {
            marks = topic_marks(candidate_id, n, test_id);
        }
        else
        {
            printf("\nError opening CandidateAnswers.txt files");
            return EXIT_FAILURE;
        }
    }
    else if (flag1 == 0)
    {
        printf("\nCandidate Id Mismatch");
        return EXIT_FAILURE;
    }
    return marks;
}

/********************************************************************************
 *     FUNCTION NAME    :   save_candidates
 *
 *     DESCRIPTION      :   Function to write data to candidates.txt
 *
 *     PARAMETERS       :   CandidateNode **
 *
 *     RETURNS          :   EXIT_SUCCESS or EXIT_FAILURE
 *******************************************************************************/
int save_candidates(CandidateNode **candidate_list_head)
{
    char const *const candidate_file = "../data/candidates.txt";
    FILE *candidate_filepointer = NULL;

    /******************* Open File *******************/
    candidate_filepointer = fopen(candidate_file, WRITEFILE);

    /* Check */
    if (candidate_filepointer == NULL)
    {
        printf("Cannot open candidates.txt file\n");
        return EXIT_FAILURE;
    }

    CandidateNode *temp = *candidate_list_head;
    while (temp != NULL)
    {
        fprintf(candidate_filepointer, "%s", temp->candidate_detail);
        temp = temp->next;
    }

    fclose(candidate_filepointer);
    return EXIT_SUCCESS;
}
