/********************************************************************************
 *     FILENAME           :    interview.c
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
 *     FUNCTION NAME    :   create_interview_node
 *
 *     DESCRIPTION      :   Function to create a Interview node
 *
 *     PARAMETERS       :   Node **, char buff[]
 *
 *     RETURNS          :   None
 *********************************************************************************/
void create_interview_node(
    InterviewNode **interview_list_head, /* Head of Interview linked list */
    char buff[])                         /* buff array that stores 1 line of Interview.txt */
{
    if (*interview_list_head == NULL)
    {
        /* Allocate memory for new head */
        InterviewNode *new_head = (InterviewNode *)malloc(sizeof(InterviewNode));

        /* Allocate memory for new interview_detail */
        new_head->interview_detail = (char *)malloc((MAX_BUFF_LEN + 1) * sizeof(char));

        /* Copy new interview_detail to linked list */
        strcpy(new_head->interview_detail, buff);

        /* Set head node */
        *interview_list_head = new_head;

        /* Set next node null */
        (*interview_list_head)->next = NULL;
        new_head = NULL;
    }
    else
    {
        /* Iterate to last node */
        InterviewNode *temp = *interview_list_head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        /* Allocate memory for new node */
        InterviewNode *new_node = (InterviewNode *)malloc(sizeof(InterviewNode));

        /* Allocate memory for new interview_detail */
        new_node->interview_detail = (char *)malloc((MAX_BUFF_LEN + 1) * sizeof(char));

        /* Copy new interview_detail to linked list */
        strcpy(new_node->interview_detail, buff);

        /* Set next node null */
        new_node->next = NULL;

        /* Set last node */
        temp->next = new_node;
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   read_interview_data
 *
 *     DESCRIPTION      :   Read data from Interview.txt and store in linked list
 *
 *     PARAMETERS       :   InterviewNode **
 *
 *     RETURNS          :   Total number of lines (unsigned int)
 *******************************************************************************/
unsigned int read_interview_data(InterviewNode **interview_list_head)
{
    /* Local variables */
    char const *const Interview_file = "../data/interviews.txt";
    unsigned int total_words = 0;
    FILE *Interview_filepointer = NULL;
    char buff[MAX_BUFF_LEN];

    /******************* Open File *******************/
    Interview_filepointer = fopen(Interview_file, APPENDMODE);

    /* Check */
    if (Interview_filepointer == NULL)
    {
        printf("Cannot open interview.txt file\n");
        return FALSE;
    }

    /* read file and store each line in a global Interview linked list*/
    while (fgets(buff, MAX_BUFF_LEN, Interview_filepointer))
    {
        create_interview_node(&(*interview_list_head), buff);
        strcpy(buff, "");
        total_words++;
    }

    fclose(Interview_filepointer);

    return total_words;
}

/********************************************************************************
 *     FUNCTION NAME    :   display_Interview_data
 *
 *     DESCRIPTION      :   Iterate on cadidate linked list and display its content
 *
 *     PARAMETERS       :   InterviewNode **
 *
 *     RETURNS          :   Total number of lines (unsigned int)
 *******************************************************************************/
void display_interview_data(InterviewNode *interview_list_head)
{
    printf("\n");
    while (interview_list_head != NULL)
    {
        printf("%s", interview_list_head->interview_detail);
        interview_list_head = interview_list_head->next;
    }
    printf("\n");
}

/********************************************************************************
 *     FUNCTION NAME    :   free_Interview_mem
 *
 *     DESCRIPTION      :   Function to free memory allocated on Interview list
 *
 *     PARAMETERS       :   InterviewNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void free_interview_mem(InterviewNode **interview_list_head)
{
    InterviewNode *curr = *interview_list_head;
    while (curr != NULL)
    {
        char *str = curr->interview_detail;
        curr = curr->next;
        free(str);
    }

    curr = *interview_list_head;
    while (curr != NULL)
    {
        InterviewNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    *interview_list_head = NULL;
}

/********************************************************************************
 *     FUNCTION NAME    :   save_interviews
 *
 *     DESCRIPTION      :   Function to write data to interviews.txt
 *
 *     PARAMETERS       :   InterviewNode **
 *
 *     RETURNS          :   EXIT_SUCCESS or EXIT_FAILURE
 *******************************************************************************/
int save_interviews(InterviewNode **candidate_list_head)
{
    char const *const interview_file = "../data/interviews.txt";
    FILE *interview_filepointer = NULL;

    /******************* Open File *******************/
    interview_filepointer = fopen(interview_file, WRITEFILE);

    /* Check */
    if (interview_filepointer == NULL)
    {
        printf("Cannot open interviews.txt file\n");
        return EXIT_FAILURE;
    }

    InterviewNode *temp = *candidate_list_head;
    while (temp != NULL)
    {
        fprintf(interview_filepointer, "%s", temp->interview_detail);
        temp = temp->next;
    }

    fclose(interview_filepointer);
    return EXIT_SUCCESS;
}
