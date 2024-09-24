/********************************************************************************
 *     FILENAME           :    question.c
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
 *     FUNCTION NAME    :   create_question_node
 *
 *     DESCRIPTION      :   Function to create a question node
 *
 *     PARAMETERS       :   Node **, char buff[]
 *
 *     RETURNS          :   None
 *********************************************************************************/
void create_question_node(
    QuestionNode **question_list_head, /* Head of question linked list */
    char buff[])                       /* buff array that stores 1 line of question.txt */
{
    if (*question_list_head == NULL)
    {
        /* Allocate memory for new head */
        QuestionNode *new_head = (QuestionNode *)malloc(sizeof(QuestionNode));

        /* Allocate memory for new question_detail */
        new_head->question_detail = (char *)malloc((MAX_BUFF_LEN + 1) * sizeof(char));

        /* Copy new question_detail to linked list */
        strcpy(new_head->question_detail, buff);

        /* Set head node */
        *question_list_head = new_head;

        /* Set next node null */
        (*question_list_head)->next = NULL;
        new_head = NULL;
    }
    else
    {
        /* Iterate to last node */
        QuestionNode *temp = *question_list_head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        /* Allocate memory for new node */
        QuestionNode *new_node = (QuestionNode *)malloc(sizeof(QuestionNode));

        /* Allocate memory for new question_detail */
        new_node->question_detail = (char *)malloc((MAX_BUFF_LEN + 1) * sizeof(char));

        /* Copy new question_detail to linked list */
        strcpy(new_node->question_detail, buff);

        /* Set next node null */
        new_node->next = NULL;

        /* Set last node */
        temp->next = new_node;
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   read_question_data
 *
 *     DESCRIPTION      :   Read data from question.txt and store in linked list
 *
 *     PARAMETERS       :   QuestionNode **
 *
 *     RETURNS          :   Total number of lines (unsigned int)
 *******************************************************************************/
unsigned int read_question_data(QuestionNode **question_list_head)
{
    /* Local variables */
    unsigned int total_words = 0;
    char const *const question_file = "../data/questions.txt";
    FILE *question_filepointer = NULL;
    char buff[MAX_BUFF_LEN];

    /******************* Open File *******************/
    question_filepointer = fopen(question_file, APPENDMODE);

    /* Check */
    if (question_filepointer == NULL)
    {
        printf("Cannot open question.txt file\n");
        return FALSE;
    }

    /* read file and store each word in a global question linked list*/
    while (fgets(buff, MAX_BUFF_LEN, question_filepointer))
    {
        create_question_node(&(*question_list_head), buff);
        strcpy(buff, "");
        total_words++;
    }

    fclose(question_filepointer);

    return total_words;
}

/********************************************************************************
 *     FUNCTION NAME    :   display_question_data
 *
 *     DESCRIPTION      :   Iterate on cadidate linked list and display its content
 *
 *     PARAMETERS       :   QuestionNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void display_question_data(QuestionNode *question_list_head)
{
    printf("\n");
    while (question_list_head != NULL)
    {
        printf("%s", question_list_head->question_detail);
        question_list_head = question_list_head->next;
    }
    printf("\n");
}

/********************************************************************************
 *     FUNCTION NAME    :   free_question_mem
 *
 *     DESCRIPTION      :   Function to free memory allocated on question list
 *
 *     PARAMETERS       :   QuestionNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void free_question_mem(QuestionNode **question_list_head)
{
    QuestionNode *curr = *question_list_head;
    while (curr != NULL)
    {
        char *str = curr->question_detail;
        curr = curr->next;
        free(str);
    }

    curr = *question_list_head;
    while (curr != NULL)
    {
        QuestionNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    *question_list_head = NULL;
}

/********************************************************************************
 *     FUNCTION NAME    :   save_questions
 *
 *     DESCRIPTION      :   Function to write data to questions.txt
 *
 *     PARAMETERS       :   QuestionNode **
 *
 *     RETURNS          :   EXIT_SUCCESS or EXIT_FAILURE
 *******************************************************************************/
int save_questions(QuestionNode **question_list_head)
{
    char const *const question_file = "../data/questions.txt";
    FILE *question_filepointer = NULL;

    /******************* Open File *******************/
    question_filepointer = fopen(question_file, WRITEFILE);

    /* Check */
    if (question_filepointer == NULL)
    {
        printf("Cannot open topics.txt file\n");
        return EXIT_FAILURE;
    }

    QuestionNode *temp = *question_list_head;
    while (temp != NULL)
    {
        fprintf(question_filepointer, "%s", temp->question_detail);
        temp = temp->next;
    }

    fclose(question_filepointer);
    return EXIT_SUCCESS;
}