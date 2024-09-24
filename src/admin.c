/********************************************************************************
 *     FILENAME           :    admin.c
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

/********************************************************************************
 *                             LOCAL FUNCTIONS
 ********************************************************************************/

/* 1. Manage Topics*/
int search_modify_topic(TopicNode **, char *);
void modify_topic(TopicNode **);
int search_delete_topic(TopicNode **, char *);
void add_topic(TopicNode **);
void delete_topic(TopicNode **);

/* 2. Manage Questions */
int search_modify_question(QuestionNode **, char *);
void modify_question(QuestionNode **);
int search_delete_question(QuestionNode **, char *);
void delete_question(QuestionNode **);
void add_question(QuestionNode **);

/* 3. Manage Tests */
void add_test(TestNode **, TestNode **);
void modify_test(TestNode **, TestNode **);
void delete_test(TestNode **, TestNode **);
void questionpaper_generation(TestNode **);
int testid_line(char *);
void read_test_data(TestNode **, TestNode **);
int add_testnode(TestNode **, TestNode **, char *);
int updatefile(TestNode **, TestNode **);
void delete_test_node(TestNode **, TestNode **, int);

/* 4. Question generation */
void topicwise_generation(QuestionGenNode **, char *, char *, char *, char *);
void read_questiongen_data(QuestionGenNode **);

/* 5. Manage Candidates*/
int search_modify_candidate(CandidateNode **, char *);
void modify_candidate(CandidateNode **);
int search_delete_candidate(CandidateNode **, char *);
void delete_candidate(CandidateNode **);

/* 6. Manage Interviews */
int search_modify_interview(InterviewNode **, char *);
void modify_interview(InterviewNode **);
int search_delete_interview(InterviewNode **, char *);
void delete_interview(InterviewNode **);
void add_interview(InterviewNode **);

/********************************************************************************
 *     FUNCTION NAME    :   admin_login
 *
 *     DESCRIPTION      :   Validate admin credentials taken from stdin
 *
 *     PARAMETERS       :   None
 *
 *     RETURNS          :   EXIT_SUCCESS or EXIT_FAILURE
 *******************************************************************************/
int admin_login(void)
{
    /* Local variables */
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];

    /* Input Username from stdin */
    printf("\nEnter your username : ");
    fgets(username, USERNAME_MAX_LEN, stdin);
    username[strlen(username) - 1] = '\0';

    /* Input Password from stdin */
    printf("\nEnter your password : ");
    fgets(password, USERNAME_MAX_LEN, stdin);
    password[strlen(password) - 1] = '\0';

    /* Validate Username - If strcmp doesn't give 0 */
    if (strcmp(username, USERNAME) != FALSE)
    {
        return EXIT_FAILURE;
    }

    /* Validate Password - If strcmp doesn't give 0 */
    else if (strcmp(password, PASSWORD) != FALSE)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**********************************************************************************************************
 *                               Requirement - 1 Manage Topics
 *********************************************************************************************************/
void manage_topics(TopicNode **topic_list_head)
{
    int mang_topic_choice = 0,  /* Manage topic choice */
        mang_topic_cond = TRUE; /* Manage topic condition */

    read_topic_data(&(*topic_list_head));

    while (mang_topic_cond)
    {
        printf("\n************** Topic Menu **************\n");
        printf("\n1. Add Topic");
        printf("\n2. Modify Topic");
        printf("\n3. Delete Topic");
        printf("\n4. Display Topics");
        printf("\n0. Back to main menu\n");

        printf("\nPlease enter your choice: ");
        scanf("%d", &mang_topic_choice);
        getchar();

        switch (mang_topic_choice)
        {
        case 0:
        {
            printf("Going back to previous menu... \n");
            mang_topic_cond = FALSE;
            return;
        }

        case 1:
        {
            add_topic(&(*topic_list_head));
        }
        break;

        case 2:
        {
            modify_topic(&(*topic_list_head));
        }
        break;

        case 3:
        {
            delete_topic(&(*topic_list_head));
        }
        break;
        case 4:
        {
            display_topic_data(*topic_list_head);
        }
        break;
        default:
        {
            printf("Invalid choice!\n");
        }
        break;
        }
    }
}

// if found returns line number else return FALSE
int search_topic(TopicNode **topic_list_head, char *topic_id)
{
    TopicNode *curr = *topic_list_head;
    char *t_id = NULL;
    char *copy_string = NULL;
    int line_number = 0;

    while (curr != NULL)
    {
        line_number++;
        copy_string = (char *)malloc((strlen(curr->topic_detail) + 1) * sizeof(char));
        strcpy(copy_string, curr->topic_detail);
        t_id = strtok(copy_string, DELIMITER);

        if (strcmp(t_id, topic_id) == 0)
        {
            free(copy_string);
            return line_number;
        }
        curr = curr->next;
        free(copy_string);
    }

    return FALSE;
}
/********************************************************************************
 *     FUNCTION NAME    :   add_topic()
 *
 *     DESCRIPTION      :   Input new topic deatails and store it in linked list
 *
 *     PARAMETERS       :   TopicNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void add_topic(TopicNode **topic_list_head)
{
    int retval = -1;

    char topic_id[TOPIC_ID_MAX_LEN],
        topic_desc[TOPIC_DESC_MAX_LEN],
        topic_instructor[TOPIC_INST_MAX_LEN],
        total_questions[TOTAL_QUES_MAX_LEN],
        new_details[MAX_BUFF_LEN];

    printf("\nEnter topic id: ");
    fgets(topic_id, TOPIC_ID_MAX_LEN, stdin);
    topic_id[strlen(topic_id) - 1] = '\0';

    if (search_topic(&(*topic_list_head), topic_id) != FALSE)
    {
        printf("\nTopic id already exist!\n");
        return;
    }

    printf("\nEnter topic description: ");
    fgets(topic_desc, TOPIC_DESC_MAX_LEN, stdin);
    topic_desc[strlen(topic_desc) - 1] = '\0';

    printf("\nEnter topic instructor: ");
    fgets(topic_instructor, TOPIC_INST_MAX_LEN, stdin);
    topic_instructor[strlen(topic_instructor) - 1] = '\0';

    printf("\nEnter total questions: ");
    fgets(total_questions, TOTAL_QUES_MAX_LEN, stdin);
    total_questions[strlen(total_questions) - 1] = '\0';

    sprintf(new_details, "%s,%s,%s,%s\n", topic_id, topic_desc, topic_instructor, total_questions);

    create_topic_node(&(*topic_list_head), new_details);
    display_topic_data(*topic_list_head);

    retval = save_topics(&(*topic_list_head));

    if (retval == EXIT_FAILURE)
    {
        printf("\nCannot update topics.txt");
    }

    else
    {
        printf("Topic added!\n");
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   search_modify_topic
 *
 *     DESCRIPTION      :   Helper function for modify_topic() that searches
 *                          existing topic in topic linked list and prompts
 *                          admin to enter modified details and store the modified
 *                          details in cadidate linked list
 *
 *     PARAMETERS       :   TopicNode **, char *
 *
 *     RETURNS          :   TRUE or FALSE
 *******************************************************************************/
int search_modify_topic(TopicNode **topic_list_head, char topic_id[])
{
    TopicNode *curr = *topic_list_head;
    char new_details[MAX_BUFF_LEN];
    int retval = -1;

    char topic_desc[TOPIC_DESC_MAX_LEN],
        topic_instructor[TOPIC_INST_MAX_LEN],
        total_questions[TOTAL_QUES_MAX_LEN];

    retval = search_topic(&(*topic_list_head), topic_id);

    if (retval == FALSE)
    {
        return FALSE;
    }
    else
    {
        for (int i = 1; i < retval; i++)
            curr = curr->next;

        printf("\nEnter topic description: ");
        fgets(topic_desc, TOPIC_DESC_MAX_LEN, stdin);
        topic_desc[strlen(topic_desc) - 1] = '\0';

        printf("\nEnter topic instructor: ");
        fgets(topic_instructor, TOPIC_INST_MAX_LEN, stdin);
        topic_instructor[strlen(topic_instructor) - 1] = '\0';

        printf("\nEnter total questions: ");
        fgets(total_questions, TOTAL_QUES_MAX_LEN, stdin);
        total_questions[strlen(total_questions) - 1] = '\0';

        sprintf(new_details, "%s,%s,%s,%s\n", topic_id, topic_desc, topic_instructor, total_questions);

        new_details[strlen(new_details) - 1] = '\n';
        new_details[strlen(new_details)] = '\0';

        strcpy(curr->topic_detail, new_details);
        save_topics(&(*topic_list_head));

        return TRUE;
    }

    return FALSE;
}

/********************************************************************************
 *     FUNCTION NAME    :   modify_topic
 *
 *     DESCRIPTION      :   Prompts user to enter topic id, calls search_modify_topic()
 *                          and prints whether modification is failed or successful
 *
 *     PARAMETERS       :   TopicNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void modify_topic(TopicNode **topic_list_head)
{
    char topic_id[MAX_BUFF_LEN];
    int ret_val = -1;

    printf("\nPlease enter topic id: ");
    fgets(topic_id, MAX_BUFF_LEN, stdin);
    topic_id[strlen(topic_id) - 1] = '\0';

    ret_val = search_modify_topic(&(*topic_list_head), topic_id);

    if (ret_val == FALSE)
    {
        printf("\nTopic not found!\n");
        return;
    }
    else
    {
        printf("\nTopic modification successful!\n");
        display_topic_data(*topic_list_head); // if required
        return;
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   search_delete_topic
 *
 *     DESCRIPTION      :   Helper function for delete_topic() that searches
 *                          existing topic in topic linked list and if the
 *                          topic is found, deletes it otherwise return false.
 *
 *     PARAMETERS       :   TopicNode **, char *
 *
 *     RETURNS          :   TRUE or FALSE
 *******************************************************************************/
int search_delete_topic(TopicNode **topic_list_head, char topic_id[])
{
    TopicNode *curr = *topic_list_head;
    int retval = -1;

    if (curr == NULL)
    {
        return FALSE;
    }

    retval = search_topic(&(*topic_list_head), topic_id);
    if (retval == FALSE)
    {
        return FALSE;
    }

    if (curr != NULL && retval == 1)
    {
        (*topic_list_head) = (*topic_list_head)->next;
        curr->next = NULL;
        free(curr->topic_detail);
        free(curr);
        save_topics(&(*topic_list_head));
        return TRUE;
    }

    /* Iterate to correct position in order to delete node */
    for (int i = 1; i < retval - 1; i++)
        curr = curr->next;

    if (curr->next == NULL)
    {
        return FALSE;
    }

    TopicNode *del = curr->next;
    curr->next = curr->next->next;
    del->next = NULL;
    free(del->topic_detail);
    free(del);
    save_topics(&(*topic_list_head));

    return TRUE;
}

/********************************************************************************
 *     FUNCTION NAME    :   delete_topic
 *
 *     DESCRIPTION      :   Deletes the given topic using topic_id from linked list
 *
 *     PARAMETERS       :   TopicNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void delete_topic(TopicNode **topic_list_head)
{
    char topic_id[MAX_BUFF_LEN];
    int ret_val = -1;

    printf("\nPlease enter topic id: ");
    fgets(topic_id, MAX_BUFF_LEN, stdin);
    topic_id[strlen(topic_id) - 1] = '\0';

    ret_val = search_delete_topic(&(*topic_list_head), topic_id);

    if (ret_val == FALSE)
    {
        printf("\nTopic not found!\n");
        return;
    }
    else
    {
        printf("\nTopic deletion successful!\n");
        display_topic_data(*topic_list_head); // if required
        return;
    }
}

/**********************************************************************************************************
 *                               Requirement - 2 Manage Questions
 *********************************************************************************************************/
void manage_questions(QuestionNode **question_list_head)
{
    int mang_question_choice = 0,  /* Manage question choice */
        mang_question_cond = TRUE; /* Manage question condition */

    read_question_data(&(*question_list_head));

    while (mang_question_cond)
    {
        printf("\n************** Question Menu **************\n");
        printf("\n1. Add Question");
        printf("\n2. Modify Question");
        printf("\n3. Delete Question");
        printf("\n4. Display Questions");
        printf("\n0. Back to main menu\n");

        printf("\nPlease enter your choice: ");
        scanf("%d", &mang_question_choice);
        getchar();

        switch (mang_question_choice)
        {
        case 0:
        {
            printf("Going back to previous menu... \n");
            mang_question_cond = FALSE;
            return;
        }

        case 1:
        {
            add_question(&(*question_list_head));
        }
        break;

        case 2:
        {
            modify_question(&(*question_list_head));
        }
        break;

        case 3:
        {
            delete_question(&(*question_list_head));
        }
        break;
        case 4:
        {
            display_question_data(*question_list_head);
        }
        break;
        default:
        {
            printf("Invalid choice!\n");
        }
        break;
        }
    }
}

// if found returns line number else return FALSE
int search_question(QuestionNode **question_list_head, char question_id[])
{
    QuestionNode *curr = *question_list_head;
    char *q_id = NULL;
    char *copy_string;
    int line_number = 0;

    while (curr != NULL)
    {
        line_number++;
        copy_string = (char *)malloc((strlen(curr->question_detail) + 1) * sizeof(char));
        strcpy(copy_string, curr->question_detail);
        q_id = strtok(copy_string, DELIMITER);
        q_id = strtok(NULL, DELIMITER);

        if (strcmp(q_id, question_id) == 0)
        {
            free(copy_string);
            return line_number;
        }

        curr = curr->next;
        free(copy_string);
    }

    return FALSE;
}
/********************************************************************************
 *     FUNCTION NAME    :   add_question()
 *
 *     DESCRIPTION      :   Input new question deatails and store it in linked list
 *
 *     PARAMETERS       :   QuestionNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void add_question(QuestionNode **question_list_head)
{
    int retval = -1;

    char topic_id[TOPIC_ID_MAX_LEN],
        question_id[QUES_ID_MAX_LEN],
        question_text[QUES_TEXT_MAX_LEN],
        option_1_text[OPTION_TEXT_MAX_LEN],
        option_2_text[OPTION_TEXT_MAX_LEN],
        option_3_text[OPTION_TEXT_MAX_LEN],
        option_4_text[OPTION_TEXT_MAX_LEN],
        answer_option[TOPIC_ID_MAX_LEN],
        new_details[MAX_BUFF_LEN];

    printf("\nEnter question id: ");
    fgets(question_id, QUES_ID_MAX_LEN, stdin);
    question_id[strlen(question_id) - 1] = '\0';

    if (search_question(&(*question_list_head), question_id) != FALSE)
    {
        printf("\nQuestion id already exist!\n");
        return;
    }

    printf("\nEnter topic id: ");
    fgets(topic_id, TOPIC_ID_MAX_LEN, stdin);
    topic_id[strlen(topic_id) - 1] = '\0';

    printf("\nEnter question text: ");
    fgets(question_text, QUES_TEXT_MAX_LEN, stdin);
    question_text[strlen(question_text) - 1] = '\0';

    printf("\nEnter option 1 text: ");
    fgets(option_1_text, OPTION_TEXT_MAX_LEN, stdin);
    option_1_text[strlen(option_1_text) - 1] = '\0';

    printf("\nEnter option 2 text: ");
    fgets(option_2_text, OPTION_TEXT_MAX_LEN, stdin);
    option_2_text[strlen(option_2_text) - 1] = '\0';

    printf("\nEnter option 3 text: ");
    fgets(option_3_text, OPTION_TEXT_MAX_LEN, stdin);
    option_3_text[strlen(option_3_text) - 1] = '\0';

    printf("\nEnter option 4 text: ");
    fgets(option_4_text, OPTION_TEXT_MAX_LEN, stdin);
    option_4_text[strlen(option_4_text) - 1] = '\0';

    printf("\nEnter answer option: ");
    fgets(answer_option, TOPIC_ID_MAX_LEN, stdin);
    answer_option[strlen(answer_option) - 1] = '\0';

    sprintf(new_details, "%s,%s,%s,%s,%s,%s,%s,%s\n", topic_id, question_id, question_text,
            option_1_text, option_2_text, option_3_text, option_4_text, answer_option);

    create_question_node(&(*question_list_head), new_details);
    display_question_data(*question_list_head);

    retval = save_questions(&(*question_list_head));

    if (retval == EXIT_FAILURE)
    {
        printf("\nCannot update questions.txt");
    }

    else
    {
        printf("File updated\n");
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   search_modify_question
 *
 *     DESCRIPTION      :   Helper function for modify_question() that searches
 *                          existing question in question linked list and prompts
 *                          admin to enter modified details and store the modified
 *                          details in cadidate linked list
 *
 *     PARAMETERS       :   QuestionNode **, char *
 *
 *     RETURNS          :   TRUE or FALSE
 *******************************************************************************/
int search_modify_question(QuestionNode **question_list_head, char question_id[])
{
    QuestionNode *curr = *question_list_head;
    int retval = -1;

    char topic_id[TOPIC_ID_MAX_LEN],
        question_text[QUES_TEXT_MAX_LEN],
        option_1_text[OPTION_TEXT_MAX_LEN],
        option_2_text[OPTION_TEXT_MAX_LEN],
        option_3_text[OPTION_TEXT_MAX_LEN],
        option_4_text[OPTION_TEXT_MAX_LEN],
        answer_option[TOPIC_ID_MAX_LEN],
        new_details[MAX_BUFF_LEN];

    retval = search_question(&(*question_list_head), question_id);

    if (retval == FALSE)
    {
        return FALSE;
    }

    else
    {
        for (int i = 1; i < retval; i++)
            curr = curr->next;

        printf("\nEnter topic id: ");
        fgets(topic_id, TOPIC_ID_MAX_LEN, stdin);
        topic_id[strlen(topic_id) - 1] = '\0';

        printf("\nEnter question text: ");
        fgets(question_text, QUES_TEXT_MAX_LEN, stdin);
        question_text[strlen(question_text) - 1] = '\0';

        printf("\nEnter option 1 text: ");
        fgets(option_1_text, OPTION_TEXT_MAX_LEN, stdin);
        option_1_text[strlen(option_1_text) - 1] = '\0';

        printf("\nEnter option 2 text: ");
        fgets(option_2_text, OPTION_TEXT_MAX_LEN, stdin);
        option_2_text[strlen(option_2_text) - 1] = '\0';

        printf("\nEnter option 3 text: ");
        fgets(option_3_text, OPTION_TEXT_MAX_LEN, stdin);
        option_3_text[strlen(option_3_text) - 1] = '\0';

        printf("\nEnter option 4 text: ");
        fgets(option_4_text, OPTION_TEXT_MAX_LEN, stdin);
        option_4_text[strlen(option_4_text) - 1] = '\0';

        printf("\nEnter answer option: ");
        fgets(answer_option, TOPIC_ID_MAX_LEN, stdin);
        answer_option[strlen(answer_option) - 1] = '\0';

        sprintf(new_details, "%s,%s,%s,%s,%s,%s,%s,%s\n", topic_id, question_id, question_text,
                option_1_text, option_2_text, option_3_text, option_4_text, answer_option);

        new_details[strlen(new_details) - 1] = '\n';
        new_details[strlen(new_details)] = '\0';

        strcpy(curr->question_detail, new_details);
        save_questions(&(*question_list_head));

        return TRUE;
    }

    return FALSE;
}

/********************************************************************************
 *     FUNCTION NAME    :   modify_question
 *
 *     DESCRIPTION      :   Prompts user to enter question id, calls search_modify_question()
 *                          and prints whether modification is failed or successful
 *
 *     PARAMETERS       :   QuestionNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void modify_question(QuestionNode **question_list_head)
{
    char question_id[MAX_BUFF_LEN];
    int ret_val = -1;

    printf("\nPlease enter question id: ");
    fgets(question_id, MAX_BUFF_LEN, stdin);
    question_id[strlen(question_id) - 1] = '\0';

    ret_val = search_modify_question(&(*question_list_head), question_id);

    if (ret_val == FALSE)
    {
        printf("\nQuestion not found!\n");
        return;
    }
    else
    {
        printf("\nQuestion modification successful!\n");
        display_question_data(*question_list_head); // if required
        return;
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   search_delete_question
 *
 *     DESCRIPTION      :   Helper function for delete_question() that searches
 *                          existing question in question linked list and if the
 *                          question is found, deletes it otherwise return false.
 *
 *     PARAMETERS       :   QuestionNode **, char *
 *
 *     RETURNS          :   TRUE or FALSE
 *******************************************************************************/
int search_delete_question(QuestionNode **question_list_head, char question_id[])
{
    QuestionNode *curr = *question_list_head;
    int retval = -1;

    if (curr == NULL)
    {
        return FALSE;
    }

    retval = search_question(&(*question_list_head), question_id);

    if (retval == FALSE)
    {
        return FALSE;
    }

    if (curr != NULL && retval == 1)
    {
        (*question_list_head) = (*question_list_head)->next;
        curr->next = NULL;
        free(curr->question_detail);
        free(curr);
        save_questions(&(*question_list_head));
        return TRUE;
    }

    /* Iterate to correct position in order to delete node */
    for (int i = 1; i < retval - 1; i++)
        curr = curr->next;

    if (curr->next == NULL)
    {
        return FALSE;
    }

    QuestionNode *del = curr->next;
    curr->next = curr->next->next;
    del->next = NULL;
    free(del->question_detail);
    free(del);
    save_questions(&(*question_list_head));

    return TRUE;
}

/********************************************************************************
 *     FUNCTION NAME    :   delete_question
 *
 *     DESCRIPTION      :   Deletes the given question using question_id from linked list
 *
 *     PARAMETERS       :   QuestionNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void delete_question(QuestionNode **question_list_head)
{
    char question_id[MAX_BUFF_LEN];
    int ret_val = -1;

    printf("\nPlease enter question id: ");
    fgets(question_id, MAX_BUFF_LEN, stdin);
    question_id[strlen(question_id) - 1] = '\0';

    ret_val = search_delete_question(&(*question_list_head), question_id);

    if (ret_val == FALSE)
    {
        printf("\nQuestion not found!\n");
        return;
    }
    else
    {
        printf("\nQuestion deletion successful!\n");
        display_question_data(*question_list_head); // if required
        return;
    }
}

/**********************************************************************************************************
 *                               Requirement - 3 Manage Test
 *********************************************************************************************************/
/********************************************************************************
 *     FUNCTION NAME    :   testid_line
 *
 *     DESCRIPTION      :   checks whether the testid is present in file or not
 *
 *     PARAMETERS       :   testid of char * type
 *
 *     RETURNS          :   line number at which testid is present in file
 *******************************************************************************/
int testid_line(char *testid_check)
{
    FILE *fptr;
    char line[TESTLINE];
    fptr = fopen("../data/tests.txt", READFILE);
    int line_number = 0;
    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        line_number = line_number + 1;
        char *copied_string;
        copied_string = (char *)malloc(sizeof(line));
        strcpy(copied_string, line);
        char *tok = strtok(copied_string, DELIMITTESTLINE);

        if (strcmp(tok, testid_check) == 0)
        {
            fclose(fptr);
            free(copied_string);
            return line_number;
        }
        free(copied_string);
    }
    fclose(fptr);
    return 0;
}

/********************************************************************************
 *     FUNCTION NAME    :   read_test_data
 *
 *     DESCRIPTION      :   Extracts data from file
 *
 *     PARAMETERS       :   head and tail of linked list
 *
 *     RETURNS          :   NULL
 *******************************************************************************/
void read_test_data(TestNode **Test_list_head, TestNode **Test_list_tail)
{
    FILE *ptr;
    ptr = fopen("../data/tests.txt", "r");
    char line[TESTLINE];
    while (fgets(line, sizeof(line), ptr) != NULL)
    {
        if (*Test_list_head == NULL)
        {
            // ALLOCATING MEMORY FOR NEW HEAD
            TestNode *newhead = (TestNode *)malloc(TESTNODESIZE * sizeof(char));

            /* Allocate memory for new testdetail */
            newhead->test_detail = (char *)malloc((TESTLINE) * sizeof(char));

            /* Copy new testdetails to linked list */
            strcpy(newhead->test_detail, line);

            newhead->next = NULL;

            /* Set head and tail node */
            *Test_list_head = newhead;
            *Test_list_tail = newhead;
        }
        else
        {
            // traversing through linked list
            TestNode *temp;
            temp = *Test_list_head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            // ALLOCATING MEMORY FOR NEW NODE
            TestNode *new_node = (TestNode *)malloc(sizeof(TestNode));

            // MEMORY for data allocation
            new_node->test_detail = (char *)malloc(sizeof(char) * TESTLINE);

            // adding data to node
            strcpy(new_node->test_detail, line);

            new_node->next = NULL;
            temp->next = new_node;

            *Test_list_tail = new_node;
        }
    }
    fclose(ptr);
}

/********************************************************************************
 *     FUNCTION NAME    :   manage_tests
 *
 *     DESCRIPTION      :   3rd option in admin menu section calls all other required local functions
 *
 *     PARAMETERS       :   head and tail of linked list
 *
 *     RETURNS          :   NULL
 *******************************************************************************/
void manage_tests(TestNode **Test_list_head, TestNode **Test_list_tail)
{
    read_test_data((&(*Test_list_head)), (&(*Test_list_tail)));
    int manage_test_choice = 0;
    int manage_test_cond = TRUE;

    while (manage_test_cond)
    {
        printf("\n************** Tests Menu **************\n");
        printf("\n1. Add Test");
        printf("\n2. Modify Test");
        printf("\n3. Delete Test");
        printf("\n4. Display Tests");
        printf("\n0. Back to main menu\n");

        printf("\nPlease enter your choice: ");
        scanf("%d", &manage_test_choice);
        getchar();

        switch (manage_test_choice)
        {
        case 0: // Quit
        {
            printf("Going back to previous menu... \n");
            manage_test_cond = FALSE;
            return;
        }
        break;
        case 1:
        {
            add_test((&(*Test_list_head)), (&(*Test_list_tail)));
        }
        break;
        case 2:
        {
            modify_test((&(*Test_list_head)), (&(*Test_list_tail)));
        }
        break;
        case 3:
        {
            delete_test((&(*Test_list_head)), (&(*Test_list_tail)));
        }
        break;
        case 4:
        {
            display_test_data(&(*Test_list_head), &(*Test_list_tail));
        }
        break;
        default:
        {
            printf("Invalid choice!\n");
        }
        break;
        }
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   delete_test
 *
 *     DESCRIPTION      :   deleting test data in file for given testid
 *
 *     PARAMETERS       :   head and tail of linked list
 *
 *     RETURNS          :   NULL
 *******************************************************************************/
void delete_test(TestNode **testhead, TestNode **testtail)
{
    int retval = 0;
    int line_number = 0;
    int flag = 1;
    char testid[TESTIDSIZE];
    char line[TESTLINE];
    char copiedline[TESTLINE];
    char *tok;
    FILE *ptr = fopen("../data/interviews.txt", "r");
    printf("\nEnter the test id: ");
    fgets(testid, TESTIDSIZE, stdin);
    testid[strlen(testid) - 1] = '\0';
    while (fgets(line, TESTLINE, ptr) != NULL)
    {
        strcpy(copiedline, line);
        tok = strtok(copiedline, DELIMITTESTLINE);
        tok = strtok(NULL, DELIMITTESTLINE);
        if (strcmp(testid, tok) == 0)
        {
            flag = 0;
            printf("Cant delete testid, as interview is scheduled.\n");
            break;
        }
    }
    if (flag == 1)
    {
        line_number = testid_line(testid);

        delete_test_node((&(*testhead)), (&(*testtail)), line_number - 1);
        retval = updatefile((&(*testhead)), (&(*testtail)));

        if (retval == 0)
        {
            printf("Unable to update file\n");
        }
    }
    fclose(ptr);
}

/********************************************************************************
 *     FUNCTION NAME    :   delete_test_node
 *
 *     DESCRIPTION      :   deleting  a node at given index in linkedlists
 *
 *     PARAMETERS       :   head and tail of linked list and index
 *
 *     RETURNS          :   NULL
 *******************************************************************************/
void delete_test_node(TestNode **testhead, TestNode **testtail, int index)
{
    TestNode *curr = *testhead;
    if (index > 0)
    {
        TestNode *p = *testhead;
        TestNode *q = (*testhead)->next;
        for (int i = 0; i < index - 1; i++)
        {
            p = p->next;
            q = q->next;
        }

        p->next = q->next;
        free(q->test_detail);
        free(q);
    }
    if (index == 0)
    {

        *testhead = (*testhead)->next;
        curr->next = NULL;
        free(curr->test_detail);
        free(curr);
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   maodify_tests
 *
 *     DESCRIPTION      :   to make modifications in testdata for given testid
 *
 *     PARAMETERS       :   head and tail of linked list
 *
 *     RETURNS          :   NULL
 *******************************************************************************/
void modify_test(TestNode **testnode_head, TestNode **testnode_tail)
{
    char *test_descrp = (char *)malloc(sizeof(char) * TESTDESCRP),
         *test_topic1 = (char *)malloc(sizeof(char) * TESTIDSIZE),
         *test_topic2 = (char *)malloc(sizeof(char) * TESTIDSIZE),
         *test_topic3 = (char *)malloc(sizeof(char) * TESTIDSIZE);

    char *test_id = (char *)malloc(sizeof(char) * TESTIDSIZE);
    int line_number = 1;
    char string[TESTLINE];
    int retval = 0;

    printf("\nEnter the test id to be modified: ");

    fgets(test_id, TESTIDSIZE, stdin);
    test_id[strlen(test_id) - 1] = '\0';
    line_number = testid_line(test_id);

    if (!line_number)
    {
        printf("Invalid test id!\n");
    }
    else
    {
        printf("\nEnter Description: ");
        fgets(test_descrp, TESTDESCRP, stdin);
        test_descrp[strlen(test_descrp) - 1] = '\0';

        printf("Enter Test topic1: ");
        fgets(test_topic1, TESTIDSIZE, stdin);
        test_topic1[strlen(test_topic1) - 1] = '\0';

        printf("Enter Test topic2: ");
        fgets(test_topic2, TESTIDSIZE, stdin);
        test_topic2[strlen(test_topic2) - 1] = '\0';

        printf("Enter Test topic3: ");
        fgets(test_topic3, TESTIDSIZE, stdin);
        test_topic3[strlen(test_topic3) - 1] = '\0';

        sprintf(string, "%s,%s,%s,%s,%s\n", test_id, test_descrp, test_topic1, test_topic2, test_topic3);

        delete_test_node((&(*testnode_head)), (&(*testnode_tail)), (line_number - 1));

        retval = add_testnode((&(*testnode_head)), (&(*testnode_tail)), string);

        if (retval == 0)
        {
            printf("unable to update linkedlist\n");
        }
        retval = updatefile((&(*testnode_head)), (&(*testnode_tail)));
        if (retval == 0)
        {
            printf("Unable to update file\n");
        }
    }
    free(test_topic1);
    free(test_descrp);
    free(test_topic2);
    free(test_topic3);
    free(test_id);
}

/********************************************************************************
 *     FUNCTION NAME    :   display
 *
 *     DESCRIPTION      :   to display linked list
 *
 *     PARAMETERS       :   head and tail of linked list
 *
 *     RETURNS          :   NULL
 *******************************************************************************/
void display_test_data(TestNode **testnode_head, TestNode **testnode_tail) // modified
{
    if (*testnode_head == NULL)
    {
        printf("\nNo Tests are present\n");
    }
    else
    {
        TestNode *temp = *testnode_head;
        printf("\n");
        while (temp != NULL)
        {
            printf("%s", temp->test_detail);
            temp = temp->next;
        }
        printf("\n");
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   add_test
 *
 *     DESCRIPTION      :   add new data entry for tests in file
 *
 *     PARAMETERS       :   head and tail of linked list
 *
 *     RETURNS          :   NULL
 *******************************************************************************/
void add_test(TestNode **testnode_head, TestNode **testnode_tail)
{
    char *test_id = (char *)malloc(sizeof(char) * TESTIDSIZE),
         *test_descrp = (char *)malloc(sizeof(char) * TESTDESCRP),
         *test_topic1 = (char *)malloc(sizeof(char) * TESTIDSIZE),
         *test_topic2 = (char *)malloc(sizeof(char) * TESTIDSIZE),
         *test_topic3 = (char *)malloc(sizeof(char) * TESTIDSIZE);

    char *string = (char *)malloc(sizeof(char) * MAX_BUFF_LEN);
    int retval = 0;
    int retval1 = 0;

    printf("\nEnter Test ID: ");
    fgets(test_id, TESTIDSIZE, stdin);
    test_id[strlen(test_id) - 1] = '\0';

    retval1 = testid_line(test_id);
    if (retval1 != 0)
    {
        printf("\nID already exists, cannot add at line :%d!!\n", retval1);
    }
    else
    {
        printf("\nEnter Description: ");
        fgets(test_descrp, TESTDESCRP, stdin);
        test_descrp[strlen(test_descrp) - 1] = '\0';

        printf("\nEnter Test topic1: ");
        fgets(test_topic1, TESTIDSIZE, stdin);
        test_topic1[strlen(test_topic1) - 1] = '\0';

        printf("\nEnter Test topic2: ");
        fgets(test_topic2, TESTIDSIZE, stdin);
        test_topic2[strlen(test_topic2) - 1] = '\0';

        printf("\nEnter Test topic3: ");
        fgets(test_topic3, TESTIDSIZE, stdin);
        test_topic3[strlen(test_topic3) - 1] = '\0';

        sprintf(string, "%s,%s,%s,%s,%s\n", test_id, test_descrp, test_topic1, test_topic2, test_topic3);
        retval = add_testnode((&(*testnode_head)), (&(*testnode_tail)), string);

        if (retval == 0)
        {
            printf("unable to update linkedlist\n");
        }

        retval = updatefile((&(*testnode_head)), (&(*testnode_tail)));

        if (retval == 0)
        {
            printf("Unable to update file\n");
        }
    }
    free(string);
    free(test_descrp);
    free(test_id);
    free(test_topic1);
    free(test_topic2);
    free(test_topic3);
}

/********************************************************************************
 *     FUNCTION NAME    :   updatefile
 *
 *     DESCRIPTION      :   writing the data of linked list in file
 *
 *     PARAMETERS       :   head and tail of linked list
 *
 *     RETURNS          :   EXIT_SUCCESS or EXIT_FAILURE
 *******************************************************************************/
int updatefile(TestNode **Testnodehead, TestNode **testnodetail)
{
    FILE *ptr;
    ptr = fopen("../data/tests.txt", WRITEFILE);
    TestNode *temp = *Testnodehead;

    while (temp != NULL)
    {
        fprintf(ptr, "%s", temp->test_detail);
        temp = temp->next;
    }

    printf("\nFile updated!\n");
    fclose(ptr);
    return TRUE;
}

/********************************************************************************
 *     FUNCTION NAME    :   add_testnode
 *
 *     DESCRIPTION      :   adding a node at last in linkedlist
 *
 *     PARAMETERS       :   head and tail of linked list and data to be stored in node
 *
 *     RETURNS          :   NULL
 *******************************************************************************/
int add_testnode(TestNode **Test_list_head, TestNode **Test_list_tail, char *string) // modified
{
    TestNode *newnode = (TestNode *)malloc(sizeof(TestNode));
    newnode->test_detail = (char *)malloc(sizeof(char) * TESTLINE);
    strcpy(newnode->test_detail, string);
    if (*Test_list_head == NULL)
    {
        *Test_list_head = newnode;
        newnode->next = NULL;
    }
    else
    {
        TestNode *temp = *Test_list_head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        newnode->next = NULL;
        temp->next = newnode;

        *Test_list_tail = newnode;
    }
    return TRUE;
}

void free_test(TestNode **head, TestNode **tail)
{
    TestNode *curr = *head;
    while (curr != NULL)
    {
        char *str = curr->test_detail;
        curr = curr->next;
        free(str);
    }

    curr = *head;
    while (curr != NULL)
    {
        TestNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    *head = NULL;
    *tail = NULL;
}
/**********************************************************************************************************
 *                               Requirement - 5 Question generation
 *********************************************************************************************************/
/********************************************************************************
 *     FUNCTION NAME    :   question_generation
 *
 *     DESCRIPTION      :   extracts data from questions.txt to linked lists
 *
 *     PARAMETERS       :   QuestionGenNode **
 *
 *     RETURNS          :   NULL
 *******************************************************************************/
void question_generation(QuestionGenNode **questionhead)
{
    FILE *ptrquestion;
    FILE *ptrtest;

    char *line = (char *)malloc(sizeof(char) * TESTLINE);
    char *testid = (char *)malloc(sizeof(char) * TESTIDSIZE);
    char *topicid1 = (char *)malloc(sizeof(char) * TESTIDSIZE);
    char *topicid2 = (char *)malloc(sizeof(char) * TESTIDSIZE);
    char *topicid3 = (char *)malloc(sizeof(char) * TESTIDSIZE);

    int i = 0;
    char *tok, *copiedtestline, *tok1;
    QuestionGenNode *temp = NULL;
    printf("\nEnter the testid: ");
    fgets(testid, TESTIDSIZE, stdin);
    testid[strcspn(testid, "\n")] = 0;

    ptrquestion = fopen("../data/questions.txt", READFILE);
    ptrtest = fopen("../data/tests.txt", READFILE);
    copiedtestline = (char *)malloc((sizeof(char) * TESTLINE) + 1);

    while (fgets(line, TESTLINE, ptrtest) != NULL)
    {
        strcpy(copiedtestline, line);
        copiedtestline[strlen(copiedtestline) - 1] = '\0';
        tok = strtok(copiedtestline, DELIMITTESTLINE);
        if (strcmp(tok, testid) == 0)
        {
            tok = strtok(NULL, DELIMITTESTLINE);
            tok = strtok(NULL, DELIMITTESTLINE);
            strcpy(topicid1, tok);

            tok = strtok(NULL, DELIMITTESTLINE);
            strcpy(topicid2, tok);

            tok = strtok(NULL, DELIMITTESTLINE);
            strcpy(topicid3, tok);
            topicid3[strcspn(topicid3, "\n")] = 0;
            break;
        }
    }

    read_questiongen_data(&(*questionhead));
    topicwise_generation((&(*questionhead)), testid, topicid1, topicid2, topicid3);
    printf("Question paper  generated!\n");
    fclose(ptrquestion);
    fclose(ptrtest);
    free(line);
    free(testid);
    free(topicid1);
    free(topicid2);
    free(topicid3);
    free(copiedtestline);
    getchar();
}

void read_questiongen_data(QuestionGenNode **questionhead)
{
    FILE *ptr;
    ptr = fopen("../data/questions.txt", "r");
    char line[TESTLINE];
    while (fgets(line, sizeof(line), ptr) != NULL)
    {
        if (*questionhead == NULL)
        {
            // ALLOCATING MEMORY FOR NEW HEAD
            QuestionGenNode *newhead = (QuestionGenNode *)malloc(TESTNODESIZE * sizeof(char));

            /* Allocate memory for new testdetail */
            newhead->data = (char *)malloc((TESTLINE) * sizeof(char));

            /* Copy new testdetails to linked list */
            strcpy(newhead->data, line);

            newhead->next = NULL;

            /* Set head and tail node */
            *questionhead = newhead;
        }
        else
        {
            // traversing through linked list
            QuestionGenNode *temp;
            temp = *questionhead;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            // ALLOCATING MEMORY FOR NEW NODE
            QuestionGenNode *new_node = (QuestionGenNode *)malloc(sizeof(QuestionGenNode));

            // MEMORY for data allocation
            new_node->data = (char *)malloc(sizeof(char) * TESTLINE);

            // adding data to node
            strcpy(new_node->data, line);

            new_node->next = NULL;
            temp->next = new_node;
        }
    }
    fclose(ptr);
}

// Displaying the question node
void display1(QuestionGenNode **testnode_head)
{
    QuestionGenNode *temp = *testnode_head;
    while (temp != NULL)
    {
        printf("%s", temp->data);
        temp = temp->next;
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   topicwisegeenration
 *
 *     DESCRIPTION      :   Generates question files for three topics seperately
 *
 *     PARAMETERS       :   QuestionNode **
 *
 *     RETURNS          :   NULL
 *******************************************************************************/
void topicwise_generation(QuestionGenNode **questionhead, char *testid, char *topicid1, char *topicid2, char *topicid3)
{
    FILE *ptrtopic1, *ptrtopic2, *ptrtopic3;
    int quesno = 0;
    char *tok = NULL;
    char *tok1;
    char string[MAX_BUFF_LEN];
    char questionid[TESTIDSIZE],
        question[TESTDESCRP],
        option1[OPTIONLEN],
        option2[OPTIONLEN],
        option3[OPTIONLEN],
        option4[OPTIONLEN],
        correctoption[TESTIDSIZE];
    printf("\nEnter the total number of questions in each topic: ");
    scanf("%d", &quesno);
    int topic1 = 0;
    int topic2 = 0;
    int topic3 = 0;
    char line[TESTLINE];

    ptrtopic1 = fopen("../data/Topic1Questions.txt", "w");
    ptrtopic2 = fopen("../data/Topic2Questions.txt", "w");
    ptrtopic3 = fopen("../data/Topic3Questions.txt", "w");
    QuestionGenNode *temp;
    // temp = (QuestionGenNode *)malloc(sizeof(QuestionGenNode));
    temp = *questionhead;
    while (temp->next != NULL)
    {
        strcpy(line, temp->data);
        tok = strtok(line, DELIMITTESTLINE);

        tok1 = (char *)malloc(sizeof(tok));
        strcpy(tok1, tok);
        strcpy(questionid, strtok(NULL, DELIMITTESTLINE));
        strcpy(question, strtok(NULL, DELIMITTESTLINE));
        strcpy(option1, strtok(NULL, DELIMITTESTLINE));
        strcpy(option2, strtok(NULL, DELIMITTESTLINE));
        strcpy(option3, strtok(NULL, DELIMITTESTLINE));
        strcpy(option4, strtok(NULL, DELIMITTESTLINE));
        strcpy(correctoption, strtok(NULL, DELIMITTESTLINE));
        sprintf(string, "%s,%s,%s,%s,%s,%s,%s,%s", testid, questionid, question, option1, option2, option3, option4, correctoption);
        if ((!(strcmp(tok1, topicid1)) && (topic1 < quesno)))
        {
            fprintf(ptrtopic1, "%s", string);
            topic1++;
        }
        if ((!(strcmp(tok1, topicid2)) && (topic2 < quesno)))
        {
            fprintf(ptrtopic2, "%s", string);
            topic2++;
        }
        if ((!(strcmp(tok1, topicid3)) && (topic3 < quesno)))
        {
            fprintf(ptrtopic3, "%s", string);
            topic3++;
        }
        temp = temp->next;
        free(tok1);
    }
    fclose(ptrtopic1);
    fclose(ptrtopic2);
    fclose(ptrtopic3);
}

void free_questiongen(QuestionGenNode **head)
{
    QuestionGenNode *curr = *head;
    while (curr != NULL)
    {
        char *str = curr->data;
        curr = curr->next;
        free(str);
    }

    curr = *head;
    while (curr != NULL)
    {
        QuestionGenNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    *head = NULL;
}

/**********************************************************************************************************
 *                               Requirement - 5 Manage Candidates
 *********************************************************************************************************/

/********************************************************************************
 *     FUNCTION NAME    :   manage_candidates
 *
 *     DESCRIPTION      :   Allows admin to modify / delete candidates
 *
 *     PARAMETERS       :   CandidateNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void manage_candidates(CandidateNode **candidate_list_head)
{
    int mang_cand_choice = 0,  /* Manage candidate choice */
        mang_cand_cond = TRUE; /* Manage candidate condition */

    while (mang_cand_cond)
    {
        printf("\n************** Candidate Menu **************\n");
        printf("\n1. Modify Candidate");
        printf("\n2. Delete Candidate");
        printf("\n3. Display Candidates");
        printf("\n0. Back to main menu\n");

        printf("\nPlease enter your choice: ");
        scanf("%d", &mang_cand_choice);
        getchar();

        switch (mang_cand_choice)
        {
        case 0:
        {
            printf("Going back to previous menu... \n");
            mang_cand_cond = FALSE;
            return;
        }

        case 1:
        {
            modify_candidate(&(*candidate_list_head));
        }
        break;

        case 2:
        {
            delete_candidate(&(*candidate_list_head));
        }
        break;

        case 3:
        {
            display_candidate_data(*candidate_list_head);
        }
        break;

        default:
        {
            printf("Invalid choice!\n");
        }
        break;
        }
    }
}

// if FLAG = 0 searches for username => if found returns line number else return FALSE
// if FLAG = 1 searches for candidate id => if found return line number else FALSE
int search_candidate(CandidateNode **candidate_list_head, char *candidate_detail, int FLAG)
{
    CandidateNode *curr = *candidate_list_head;
    char *c_detail = NULL;
    char *copy_string = NULL;
    int line_number = 0;

    while (curr != NULL)
    {
        line_number++;
        copy_string = (char *)malloc((strlen(curr->candidate_detail) + 1) * sizeof(char));
        strcpy(copy_string, curr->candidate_detail);
        c_detail = strtok(copy_string, DELIMITER);

        if (FLAG == TRUE)
        {
            c_detail = strtok(NULL, DELIMITER);
            c_detail = strtok(NULL, DELIMITER);
        }

        if (strcmp(c_detail, candidate_detail) == 0)
        {
            free(copy_string);
            return line_number;
        }
        curr = curr->next;
        free(copy_string);
    }

    return FALSE;
}

/********************************************************************************
 *     FUNCTION NAME    :   search_modify_candidate
 *
 *     DESCRIPTION      :   Helper function for modify_candidate() that searches
 *                          existing candidate in candidate linked list and prompts
 *                          admin to enter modified details and store the modified
 *                          details in cadidate linked list
 *
 *     PARAMETERS       :   CandidateNode **, char *
 *
 *     RETURNS          :   Integer NOT_FOUND (0), SUCCESS (1), ALREADY_EXIST (-1)
 *******************************************************************************/
int search_modify_candidate(CandidateNode **candidate_list_head, char candidate_id[])
{
    CandidateNode *curr = *candidate_list_head;
    int retval = -1;

    const int not_found_err = 0,
              modification_success = 1,
              already_exist_err = -1;

    char username[USER_MAX_LEN],
        password[PASS_MAX_LEN],
        candidate_name[CAND_NAME_MAX_LEN],
        aadhar_no[UID_NO_MAX_LEN],
        address[ADD_MAX_LEN],
        qualification[QUAL_MAX_LEN],
        new_details[MAX_BUFF_LEN];

    retval = search_candidate(&(*candidate_list_head), candidate_id, TRUE);

    if (retval == FALSE)
    {
        return not_found_err;
    }
    else
    {
        for (int i = 1; i < retval; i++)
            curr = curr->next;

        printf("\nEnter new username: ");
        fgets(username, USER_MAX_LEN, stdin);
        username[strlen(username) - 1] = '\0';

        if (FALSE != search_candidate(&(*candidate_list_head), username, FALSE))
        {
            printf("\nUsername already exist!\n");
            return already_exist_err;
        }

        printf("\nEnter password: ");
        fgets(password, USER_MAX_LEN, stdin);
        password[strlen(password) - 1] = '\0';

        printf("\nEnter candidate id: ");
        fgets(candidate_id, CAND_ID_MAX_LEN, stdin);
        candidate_id[strlen(candidate_id) - 1] = '\0';

        if (FALSE != search_candidate(&(*candidate_list_head), candidate_id, TRUE))
        {
            printf("\nCandidate id already exist!\n");
            return already_exist_err;
        }

        printf("\nEnter candidate name: ");
        fgets(candidate_name, CAND_NAME_MAX_LEN, stdin);
        candidate_name[strlen(candidate_name) - 1] = '\0';

        printf("\nEnter aadhar number: ");
        fgets(aadhar_no, UID_NO_MAX_LEN, stdin);
        aadhar_no[strlen(aadhar_no) - 1] = '\0';

        printf("\nEnter address: ");
        fgets(address, ADD_MAX_LEN, stdin);
        address[strlen(address) - 1] = '\0';

        printf("\nEnter qualification: ");
        fgets(qualification, QUAL_MAX_LEN, stdin);
        qualification[strlen(qualification) - 1] = '\0';

        sprintf(new_details, "%s,%s,%s,%s,%s,%s,%s\n", username, password, candidate_id, candidate_name,
                aadhar_no, address, qualification);

        strcpy(curr->candidate_detail, new_details);
        save_candidates(&(*candidate_list_head));
        return modification_success;
    }

    return FALSE;
}

/********************************************************************************
 *     FUNCTION NAME    :   modify_candidate
 *
 *     DESCRIPTION      :   Prompts user to enter candidate id, calls search_modify_candidate()
 *                          and prints whether modification is failed or successful
 *
 *     PARAMETERS       :   CandidateNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void modify_candidate(CandidateNode **candidate_list_head)
{
    char candidate_id[MAX_BUFF_LEN];
    int retval = -1;

    const int not_found_err = 0,
              modification_success = 1,
              already_exist_err = -1;

    printf("\nPlease enter candidate id: ");
    fgets(candidate_id, MAX_BUFF_LEN, stdin);
    candidate_id[strlen(candidate_id) - 1] = '\0';

    retval = search_modify_candidate(&(*candidate_list_head), candidate_id);

    if (retval == not_found_err)
    {
        printf("\nCandidate not found!\n");
        return;
    }
    else if (retval == modification_success)
    {
        printf("\nCandidate modification successful!\n");
        return;
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   search_delete_candidate
 *
 *     DESCRIPTION      :   Helper function for delete_candidate() that searches
 *                          existing candidate in candidate linked list and if the
 *                          candidate is found, deletes it otherwise return false.
 *
 *     PARAMETERS       :   CandidateNode **, char *
 *
 *     RETURNS          :   TRUE or FALSE
 *******************************************************************************/
int search_delete_candidate(CandidateNode **candidate_list_head, char candidate_id[])
{
    CandidateNode *curr = *candidate_list_head;
    int retval = -1;

    if (curr == NULL)
    {
        return FALSE;
    }

    retval = search_candidate(&(*candidate_list_head), candidate_id, TRUE);

    if (retval == FALSE)
    {
        return FALSE;
    }

    if (curr != NULL && retval == 1)
    {
        (*candidate_list_head) = (*candidate_list_head)->next;
        curr->next = NULL;
        free(curr->candidate_detail);
        free(curr);
        save_candidates(&(*candidate_list_head));
        return TRUE;
    }

    /* Iterate to correct position in order to delete node */
    for (int i = 1; i < retval - 1; i++)
        curr = curr->next;

    if (curr->next == NULL)
    {
        return FALSE;
    }

    CandidateNode *del = curr->next;
    curr->next = curr->next->next;
    del->next = NULL;
    free(del->candidate_detail);
    free(del);
    save_candidates(&(*candidate_list_head));

    return TRUE;
}

/********************************************************************************
 *     FUNCTION NAME    :   delete_candidate
 *
 *     DESCRIPTION      :   Deletes the given candidate using candidate_id from linked list
 *
 *     PARAMETERS       :   CandidateNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void delete_candidate(CandidateNode **candidate_list_head)
{
    char candidate_id[CAND_ID_MAX_LEN];
    int retval = -1;

    printf("\nPlease enter candidate id: ");
    fgets(candidate_id, CAND_ID_MAX_LEN, stdin);
    candidate_id[strlen(candidate_id) - 1] = '\0';

    retval = search_delete_candidate(&(*candidate_list_head), candidate_id);

    if (retval == FALSE)
    {
        printf("\nCandidate not found!\n");
        return;
    }
    else
    {
        printf("\nCandidate deletion successful!\n");
        display_candidate_data(*candidate_list_head); // if required
        return;
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   register_candidates()
 *
 *     DESCRIPTION      :   Input new candidate deatails and store it in linked list
 *
 *     PARAMETERS       :   CandidateNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void register_candidates(CandidateNode **candidate_list_head)
{
    int retval = -1;

    char username[USER_MAX_LEN],
        password[PASS_MAX_LEN],
        candidate_id[CAND_ID_MAX_LEN],
        candidate_name[CAND_NAME_MAX_LEN],
        aadhar_no[UID_NO_MAX_LEN],
        address[ADD_MAX_LEN],
        qualification[QUAL_MAX_LEN],
        new_details[MAX_BUFF_LEN];

    printf("\nEnter username: ");
    fgets(username, USER_MAX_LEN, stdin);
    username[strlen(username) - 1] = '\0';

    if (search_candidate(&(*candidate_list_head), username, FALSE))
    {
        printf("\nUsername already exist!\n");
        return;
    }

    printf("\nEnter password: ");
    fgets(password, USER_MAX_LEN, stdin);
    password[strlen(password) - 1] = '\0';

    printf("\nEnter candidate id: ");
    fgets(candidate_id, CAND_ID_MAX_LEN, stdin);
    candidate_id[strlen(candidate_id) - 1] = '\0';

    if (search_candidate(&(*candidate_list_head), candidate_id, TRUE))
    {
        printf("\nCandidate id already exist!\n");
        return;
    }

    printf("\nEnter candidate name: ");
    fgets(candidate_name, CAND_NAME_MAX_LEN, stdin);
    candidate_name[strlen(candidate_name) - 1] = '\0';

    printf("\nEnter aadhar number: ");
    fgets(aadhar_no, UID_NO_MAX_LEN, stdin);
    aadhar_no[strlen(aadhar_no) - 1] = '\0';

    printf("\nEnter address: ");
    fgets(address, ADD_MAX_LEN, stdin);
    address[strlen(address) - 1] = '\0';

    printf("\nEnter qualification: ");
    fgets(qualification, QUAL_MAX_LEN, stdin);
    qualification[strlen(qualification) - 1] = '\0';

    sprintf(new_details, "%s,%s,%s,%s,%s,%s,%s\n", username, password, candidate_id, candidate_name,
            aadhar_no, address, qualification);

    create_candidate_node(&(*candidate_list_head), new_details);

    retval = save_candidates(&(*candidate_list_head));
    if (retval == EXIT_FAILURE)
    {
        printf("\nCannot update candidates.txt");
    }
    else
    {
        printf("\nCandidate registered!\n");
    }
}

/**********************************************************************************************************
 *                               Requirement - 6 Manage interviews
 *********************************************************************************************************/
void manage_interviews(InterviewNode **interview_list_head)
{
    int mang_interview_choice = 0,  /* Manage interview choice */
        mang_interview_cond = TRUE; /* Manage interview condition */

    read_interview_data(&(*interview_list_head));

    while (mang_interview_cond)
    {
        printf("\n************** Interview Menu **************\n");
        printf("\n1. Add Interview");
        printf("\n2. Modify Interview");
        printf("\n3. Delete Interview");
        printf("\n4. Display Interviews");
        printf("\n0. Back to main menu\n");

        printf("\nPlease enter your choice: ");
        scanf("%d", &mang_interview_choice);
        getchar();

        switch (mang_interview_choice)
        {
        case 0:
        {
            printf("Going back to previous menu... \n");
            mang_interview_cond = FALSE;
            return;
        }

        case 1:
        {
            add_interview(&(*interview_list_head));
        }
        break;

        case 2:
        {
            modify_interview(&(*interview_list_head));
        }
        break;

        case 3:
        {
            delete_interview(&(*interview_list_head));
        }
        break;
        case 4:
        {
            display_interview_data(*interview_list_head);
        }
        break;
        default:
        {
            printf("Invalid choice!\n");
        }
        break;
        }
    }
}

// if found returns line number else return FALSE
int search_interview(InterviewNode **interview_list_head, char candidate_id[])
{
    InterviewNode *curr = *interview_list_head;
    char *c_id = NULL;
    char *copy_string;
    int line_number = 0;

    while (curr != NULL)
    {
        line_number++;
        copy_string = (char *)malloc((strlen(curr->interview_detail) + 1) * sizeof(char));
        strcpy(copy_string, curr->interview_detail);
        c_id = strtok(copy_string, DELIMITER);

        if (strcmp(c_id, candidate_id) == 0)
        {
            free(copy_string);
            return line_number;
        }

        curr = curr->next;
        free(copy_string);
    }

    return FALSE;
}

/********************************************************************************
 *     FUNCTION NAME    :   add_interview()
 *
 *     DESCRIPTION      :   Input new interview deatails and store it in linked list
 *
 *     PARAMETERS       :   InterviewNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void add_interview(InterviewNode **interview_list_head)
{
    int retval = -1;
    char candidate_id[CAND_ID_MAX_LEN],
        test_id[TESTIDSIZE],
        date_of_interview[DATE_MAX_LEN],
        has_attended[ATTENDED_MAX_LEN],
        topic_1_marks[TOPIC_MARKS_MAX_LEN],
        topic_2_marks[TOPIC_MARKS_MAX_LEN],
        topic_3_marks[TOPIC_MARKS_MAX_LEN],
        new_details[MAX_BUFF_LEN];

    printf("\nEnter candidate id: ");
    fgets(candidate_id, CAND_ID_MAX_LEN, stdin);
    candidate_id[strlen(candidate_id) - 1] = '\0';

    if (search_interview(&(*interview_list_head), candidate_id) != FALSE)
    {
        printf("\nCandidate id already exist!\n");
        return;
    }

    printf("\nEnter test id: ");
    fgets(test_id, TESTIDSIZE, stdin);
    test_id[strlen(test_id) - 1] = '\0';

    printf("\nEnter date dd/mm/yyyy: ");
    fgets(date_of_interview, DATE_MAX_LEN, stdin);
    date_of_interview[strlen(date_of_interview) - 1] = '\0';

    printf("\nCandidate appeared for test? Y/N: ");
    fgets(has_attended, ATTENDED_MAX_LEN, stdin);
    has_attended[strlen(has_attended) - 1] = '\0';

    printf("\nTopic 1 marks: ");
    fgets(topic_1_marks, TOPIC_ID_MAX_LEN, stdin);
    topic_1_marks[strlen(topic_1_marks) - 1] = '\0';

    printf("\nTopic 2 marks: ");
    fgets(topic_2_marks, TOPIC_ID_MAX_LEN, stdin);
    topic_2_marks[strlen(topic_2_marks) - 1] = '\0';

    printf("\nTopic 3 marks: ");
    fgets(topic_3_marks, TOPIC_ID_MAX_LEN, stdin);
    topic_3_marks[strlen(topic_3_marks) - 1] = '\0';

    sprintf(new_details, "%s,%s,%s,%s,%s,%s,%s\n", candidate_id, test_id, date_of_interview, has_attended,
            topic_1_marks, topic_2_marks, topic_3_marks);

    create_interview_node(&(*interview_list_head), new_details);
    display_interview_data(*interview_list_head);

    retval = save_interviews(&(*interview_list_head));

    if (retval == EXIT_FAILURE)
    {
        printf("\nCannot update interviews.txt");
    }

    else
    {
        printf("Interview added\n");
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   search_modify_interview
 *
 *     DESCRIPTION      :   Helper function for modify_interview() that searches
 *                          existing interview in interview linked list and prompts
 *                          admin to enter modified details and store the modified
 *                          details in cadidate linked list
 *
 *     PARAMETERS       :   InterviewNode **, char *
 *
 *     RETURNS          :   TRUE or FALSE
 *******************************************************************************/
int search_modify_interview(InterviewNode **interview_list_head, char candidate_id[])
{
    InterviewNode *curr = *interview_list_head;
    int retval = -1;

    char test_id[TESTIDSIZE],
        date_of_interview[DATE_MAX_LEN],
        has_attended[ATTENDED_MAX_LEN],
        topic_1_marks[TOPIC_MARKS_MAX_LEN],
        topic_2_marks[TOPIC_MARKS_MAX_LEN],
        topic_3_marks[TOPIC_MARKS_MAX_LEN],
        new_details[MAX_BUFF_LEN];

    retval = search_interview(&(*interview_list_head), candidate_id);

    if (retval == FALSE)
    {
        return FALSE;
    }
    else
    {
        for (int i = 1; i < retval; i++)
            curr = curr->next;

        printf("\nEnter test id: ");
        fgets(test_id, TESTIDSIZE, stdin);
        test_id[strlen(test_id) - 1] = '\0';

        printf("\nEnter date dd/mm/yyyy: ");
        fgets(date_of_interview, DATE_MAX_LEN, stdin);
        date_of_interview[strlen(date_of_interview) - 1] = '\0';

        printf("\nCandidate appeared for test? Y/N: ");
        fgets(has_attended, ATTENDED_MAX_LEN, stdin);
        has_attended[strlen(has_attended) - 1] = '\0';

        printf("\nTopic 1 marks: ");
        fgets(topic_1_marks, TOPIC_ID_MAX_LEN, stdin);
        topic_1_marks[strlen(topic_1_marks) - 1] = '\0';

        printf("\nTopic 2 marks: ");
        fgets(topic_2_marks, TOPIC_ID_MAX_LEN, stdin);
        topic_2_marks[strlen(topic_2_marks) - 1] = '\0';

        printf("\nTopic 3 marks: ");
        fgets(topic_3_marks, TOPIC_ID_MAX_LEN, stdin);
        topic_3_marks[strlen(topic_3_marks) - 1] = '\0';

        sprintf(new_details, "%s,%s,%s,%s,%s,%s,%s\n", candidate_id, test_id, date_of_interview, has_attended,
                topic_1_marks, topic_2_marks, topic_3_marks);

        strcpy(curr->interview_detail, new_details);
        save_interviews(&(*interview_list_head));

        return TRUE;
    }

    return FALSE;
}

/********************************************************************************
 *     FUNCTION NAME    :   modify_interview
 *
 *     DESCRIPTION      :   Prompts user to enter interview id, calls search_modify_interview()
 *                          and prints whether modification is failed or successful
 *
 *     PARAMETERS       :   InterviewNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void modify_interview(InterviewNode **interview_list_head)
{
    char candidate_id[MAX_BUFF_LEN];
    int ret_val = -1;

    printf("\nPlease enter candidate id: ");
    fgets(candidate_id, MAX_BUFF_LEN, stdin);
    candidate_id[strlen(candidate_id) - 1] = '\0';

    ret_val = search_modify_interview(&(*interview_list_head), candidate_id);

    if (ret_val == FALSE)
    {
        printf("\nInterview not found!\n");
        return;
    }
    else
    {
        printf("\nInterview modification successful!\n");
        return;
    }
}

/********************************************************************************
 *     FUNCTION NAME    :   search_delete_interview
 *
 *     DESCRIPTION      :   Helper function for delete_interview() that searches
 *                          existing interview in interview linked list and if the
 *                          interview is found, deletes it otherwise return false.
 *
 *     PARAMETERS       :   InterviewNode **, char *
 *
 *     RETURNS          :   TRUE or FALSE
 *******************************************************************************/
int search_delete_interview(InterviewNode **interview_list_head, char candidate_id[])
{
    InterviewNode *curr = *interview_list_head;
    int retval = -1;

    if (curr == NULL)
    {
        return FALSE;
    }

    retval = search_interview(&(*interview_list_head), candidate_id);

    if (retval == FALSE)
    {
        return FALSE;
    }

    if (curr != NULL && retval == 1)
    {
        (*interview_list_head) = (*interview_list_head)->next;
        curr->next = NULL;
        free(curr->interview_detail);
        free(curr);
        save_interviews(&(*interview_list_head));
        return TRUE;
    }

    /* Iterate to correct position in order to delete node */
    for (int i = 1; i < retval - 1; i++)
        curr = curr->next;

    if (curr->next == NULL)
    {
        return FALSE;
    }

    InterviewNode *del = curr->next;
    curr->next = curr->next->next;
    del->next = NULL;
    free(del->interview_detail);
    free(del);
    save_interviews(&(*interview_list_head));

    return TRUE;
}

/********************************************************************************
 *     FUNCTION NAME    :   delete_interview
 *
 *     DESCRIPTION      :   Deletes the given question using question_id from linked list
 *
 *     PARAMETERS       :   InterviewNode **
 *
 *     RETURNS          :   None
 *******************************************************************************/
void delete_interview(InterviewNode **interview_list_head)
{
    char candidate_id[MAX_BUFF_LEN];
    int ret_val = -1;

    printf("\nPlease enter candidate id: ");
    fgets(candidate_id, MAX_BUFF_LEN, stdin);
    candidate_id[strlen(candidate_id) - 1] = '\0';

    ret_val = search_delete_interview(&(*interview_list_head), candidate_id);

    if (ret_val == FALSE)
    {
        printf("\nInterview not found!\n");
        return;
    }
    else
    {
        printf("\nInterview deletion successful!\n");
        display_interview_data(*interview_list_head); // if required
        return;
    }
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
int candidate_id_check(int cand_id)
{
    /* Local variables */
    int flag1 = FALSE;
    char string1[MAX_LEN];
    char *ptr = NULL;

    /*file pointers*/
    FILE *file1;

    if ((file1 = fopen("../data/CandidateAnswers1.txt", "r")))
    {
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
int topic_marks_calculation(int cand_id, int n)
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
            int i = 0;
            while (ptr != NULL)
            {
                arr1[i] = ptr;
                ptr = strtok(NULL, DELIMITER);
                i++;
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
                fgets(string2, MAX_LEN, file);
                ptr = strtok(string2, DELIMITER);
                int i = 0;
                while (ptr != NULL)
                {
                    arr2[i] = ptr;
                    ptr = strtok(NULL, DELIMITER);
                    i++;
                }
                if (atoi(arr1[2]) == atoi(arr2[1])) // a1 == atoi(arr2[0]) && atoi(arr1[2]) == atoi(arr2[1]
                {
                    if (atoi(arr1[3]) == atoi(arr2[7]))
                    {
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
 *     DESCRIPTION      :   Calculate marks of of all tests appeared by the candidate
 *                          and store them in interviews.txt file.
 *
 *     PARAMETERS       :   cand_id
 *
 *     RETURNS          :   EXIT_SUCCESS or EXIT_FAILURE
 *******************************************************************************/
int calculate_marks(void)
{
    /* Local variables */
    int cand_id;
    int test_id;
    int marks1 = 0;
    int marks2 = 0;
    int marks3 = 0;
    int n = 0;
    bool flag1 = FALSE;
    bool flag2 = FALSE;
    char string1[MAX_LEN];
    char *ptr = NULL;

    /*file pointers*/
    FILE *file1, *file2;

    /* Input candidate id from stdin */
    printf("\nEnter your Candidate id : ");
    scanf("%d", &cand_id); // get candidate id from the admin

    flag1 = candidate_id_check(cand_id);
    // flag2 = results_check(cand_id);

    if ((file1 = fopen("../data/results.txt", "r")))
    {
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
                flag2 = TRUE;
            }
        }
        fclose(file1);
    }

    file2 = fopen("../data/tests.txt", "r");
    while (!feof(file2))
    {
        if (feof(file2))
        {
            break;
        }
        fgets(string1, MAX_LEN, file2);
        ptr = strtok(string1, DELIMITER);
    }

    test_id = atoi(ptr);
    fclose(file2);

    if (flag1 && !(flag2))
    {
        if ((file2 = fopen("../data/CandidateAnswers1.txt", "r")))
        {
            // printf("\n CandidateAnswers1 opened successfully in read mode");
            n = 1;
            marks1 = topic_marks_calculation(cand_id, n);
            fclose(file2);
        }
        else
        {
            printf("\nError opening CandidateAnswers1.txt file");
            return EXIT_FAILURE;
        }

        if ((file2 = fopen("../data/CandidateAnswers2.txt", "r")))
        {
            // printf("\n CandidateAnswers2 opened successfully in read mode");
            n = 2;
            marks2 = topic_marks_calculation(cand_id, n);
            fclose(file2);
        }
        else
        {
            printf("\nError opening CandidateAnswers2s.txt file");
            return EXIT_FAILURE;
        }

        if ((file2 = fopen("../data/CandidateAnswers3.txt", "r")))
        {
            // printf("\n CandidateAnswers3 opened successfully in read mode");
            n = 3;
            marks3 = topic_marks_calculation(cand_id, n);
            fclose(file2);
        }
        else
        {
            printf("\nError opening CandidateAnswers3.txt file");
            return EXIT_FAILURE;
        }

        if (!(flag2))
        {
            file1 = fopen("../data/results.txt", "a");
            fprintf(file1, "%d,%d,%d,%d,%d\n", cand_id, test_id, marks1, marks2, marks3);
            fclose(file1);
        }
    }
    else if (flag1 == 0)
    {
        printf("\nCandidate Id Mismatch");
        return EXIT_FAILURE;
    }
    else if (flag2 == 1)
    {
        printf("\nResults already Calculated");
    }
    return EXIT_SUCCESS;
}

/********************************************************************************
 *     FUNCTION NAME    :   display_marks
 *
 *     DESCRIPTION      :   To display calculated marks in interviews.txt file.
 *
 *     PARAMETERS       :   cand_id
 *
 *     RETURNS          :   EXIT_SUCCESS or EXIT_FAILURE
 *******************************************************************************/
int display_marks(void)
{

    /* Local variables */
    int cand_id;
    int flag = 0;
    char string[MAX_LEN];
    char *ptr = NULL;
    int n = 1; // for iteration

    /* Input candidate id from stdin */
    printf("\nEnter your Candidate Id : ");
    scanf("%d", &cand_id); // get candidate id from the console
    // printf("Entered Candidate Id : %d", cand_id);

    /*file pointers*/
    FILE *file1;

    /*open file and read the data*/
    if ((file1 = fopen("../data/results.txt", "r")))
    {
        while (fgets(string, MAX_LEN, file1))
        {
            if (feof(file1))
            {
                break;
            }
            // fgets(string, MAX_LEN, file1);
            ptr = strtok(string, DELIMITER);
            if (atoi(ptr) == cand_id)
            {
                flag = 1;
                printf("\n Candidate Id : %d", cand_id);
                ptr = strtok(NULL, DELIMITER);
                printf("\n Test id : %s", ptr);
                ptr = strtok(NULL, DELIMITER);
                while (ptr != NULL)
                {
                    printf("\n Topic %d Marks : %s", n, ptr);
                    ptr = strtok(NULL, DELIMITER);
                    n++;
                }
            }
            else if (atoi(ptr) != cand_id)
            {
                continue;
            }
        }
        if (flag == 0)
        {
            printf("\nResult was not calculated for %d\n", cand_id);
        }
    }
    else
    {
        printf("\nError opening results.txt file");
        return EXIT_FAILURE;
    }

    /*closing files*/
    fclose(file1);
    return EXIT_SUCCESS;
}