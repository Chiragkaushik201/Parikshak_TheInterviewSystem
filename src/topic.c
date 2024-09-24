/********************************************************************************
 *     FILENAME           :    topic.c
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
 *     FUNCTION NAME    :   create_topic_node
 *
 *     DESCRIPTION      :   Function to create a topic node
 *
 *     PARAMETERS       :   Node **, char buff[]
 *
 *     RETURNS          :   None
 *********************************************************************************/
void create_topic_node(
    TopicNode **topic_list_head, /* Head of topic linked list */
    char buff[])                 /* buff array that stores 1 line of topic.txt */
{
    if (*topic_list_head == NULL)
    {
        /* Allocate memory for new head */
        TopicNode *new_head = (TopicNode *)malloc(sizeof(TopicNode));

        if (new_head != NULL)
        {
            /* Allocate memory for new topic_detail */
            new_head->topic_detail = (char *)malloc((MAX_BUFF_LEN + 1) * sizeof(char));

            /* Copy new topic_detail to linked list */
            if (new_head->topic_detail != NULL)
                strcpy(new_head->topic_detail, buff);

            /* Set head node */
            *topic_list_head = new_head;

            /* Set next node null */
            (*topic_list_head)->next = NULL;
            new_head = NULL;
        }
    }

    else
    {
        /* Iterate to last node */
        TopicNode *temp = *topic_list_head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        /* Allocate memory for new node */
        TopicNode *new_node = (TopicNode *)malloc(sizeof(TopicNode));

        if (new_node != NULL)
        {
            /* Allocate memory for new topic_detail */
            new_node->topic_detail = (char *)malloc((MAX_BUFF_LEN + 1) * sizeof(char));
            if (new_node->topic_detail != NULL)
                /* Copy new topic_detail to linked list */
                strcpy(new_node->topic_detail, buff);

            /* Set next node null */
            new_node->next = NULL;

            /* Set last node */
            temp->next = new_node;
        }
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   read_topic_data
 *
 *     DESCRIPTION      :   Read data from topic.txt and store in linked list
 *
 *     PARAMETERS       :   TopicNode **
 *
 *     RETURNS          :   Total number of lines (unsigned int)
 *******************************************************************************/
unsigned int read_topic_data(TopicNode **topic_list_head)
{
    /* Local variables */
    unsigned int total_words = 0;
    char const *const topic_file = "../data/topics.txt";
    FILE *topic_filepointer = NULL;
    char buff[MAX_BUFF_LEN];

    /******************* Open File *******************/
    topic_filepointer = fopen(topic_file, APPENDMODE);

    /* Check */
    if (topic_filepointer == NULL)
    {
        printf("Cannot open topic.txt file\n");
        return FALSE;
    }

    /* read file and store each word in a global topic linked list*/
    while (fgets(buff, MAX_BUFF_LEN, topic_filepointer))
    {
        create_topic_node(&(*topic_list_head), buff);
        strcpy(buff, "");
        total_words++;
    }

    fclose(topic_filepointer);

    return total_words;
}

/********************************************************************************
 *     FUNCTION NAME    :   display_topic_data
 *
 *     DESCRIPTION      :   Iterate on cadidate linked list and display its content
 *
 *     PARAMETERS       :   TopicNode **
 *
 *     RETURNS          :   Total number of lines (unsigned int)
 *******************************************************************************/
void display_topic_data(TopicNode *topic_list_head)
{
    printf("\n");
    while (topic_list_head != NULL)
    {
        printf("%s", topic_list_head->topic_detail);
        topic_list_head = topic_list_head->next;
    }
    printf("\n");
}

/********************************************************************************
 *     FUNCTION NAME    :   free_topic_mem
 *
 *     DESCRIPTION      :   Function to free memory allocated on topic list
 *
 *     PARAMETERS       :   TopicNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void free_topic_mem(TopicNode **topic_list_head)
{
    TopicNode *curr = *topic_list_head;
    while (curr != NULL)
    {
        char *str = curr->topic_detail;
        curr = curr->next;
        free(str);
    }

    curr = *topic_list_head;
    while (curr != NULL)
    {
        TopicNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    *topic_list_head = NULL;
}

/********************************************************************************
 *     FUNCTION NAME    :   save_topics
 *
 *     DESCRIPTION      :   Function to write data to topics.txt
 *
 *     PARAMETERS       :   TopicNode **
 *
 *     RETURNS          :   EXIT_SUCCESS or EXIT_FAILURE
 *******************************************************************************/
int save_topics(TopicNode **topic_list_head)
{
    char const *const topic_file = "../data/topics.txt";
    FILE *topic_filepointer = NULL;

    /******************* Open File *******************/
    topic_filepointer = fopen(topic_file, WRITEFILE);

    /* Check */
    if (topic_filepointer == NULL)
    {
        printf("Cannot open topics.txt file\n");
        return EXIT_FAILURE;
    }

    TopicNode *temp = *topic_list_head;
    while (temp != NULL)
    {
        fprintf(topic_filepointer, "%s", temp->topic_detail);
        temp = temp->next;
    }

    fclose(topic_filepointer);
    return EXIT_SUCCESS;
}
