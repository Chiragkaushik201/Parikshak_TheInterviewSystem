/********************************************************************************
 *     FILENAME           :    utility.h
 *
 *     DESCRIPTION        :    Header file for the program
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
#ifndef __UTILITY_H_
#define __UTILITY_H_

/********************************************************************************
 *                               HEADER FILES
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/********************************************************************************
 *                                GLOBAL DATA
 ********************************************************************************/
typedef struct CandidateNode
{
    char *candidate_detail;
    struct CandidateNode *next;
} CandidateNode;

typedef struct QuestionNode
{
    char *question_detail;
    struct QuestionNode *next;
} QuestionNode;

typedef struct TopicNode
{
    char *topic_detail;
    struct TopicNode *next;
} TopicNode;

typedef struct InterviewNode
{
    char *interview_detail;
    struct InterviewNode *next;
} InterviewNode;

typedef struct TestNode
{
    char *test_detail;
    struct TestNode *next;
} TestNode;

typedef struct QuestionGenNode
{
    char *data;
    struct QuestionGenNode *next;
} QuestionGenNode;
/********************************************************************************
 *                                MACROS
 ********************************************************************************/
#define TRUE 1
#define FALSE 0
#define APPENDMODE "a+"
#define READFILE "r"
#define WRITEFILE "w"
#define DELIMITTESTLINE ","
#define TESTLINE 150
#define TESTNODESIZE 300
#define TESTIDSIZE 6
#define TESTDESCRP 80
#define OPTIONLEN   20
#define MAX_BUFF_LEN 800
#define USERNAME_MAX_LEN 30
#define PASSWORD_MAX_LEN 30
#define MAX_LEN 100
#define CAND_ID_LEN 6
#define DELIMITER ","

#define USERNAME "admin" /* Encrypt TODO */
#define PASSWORD "admin" /* Encrypt TODO */

#define TOPIC_ID_MAX_LEN 4
#define TOPIC_DESC_MAX_LEN 80
#define TOPIC_INST_MAX_LEN 40
#define TOTAL_QUES_MAX_LEN 4

#define QUES_ID_MAX_LEN 5
#define QUES_TEXT_MAX_LEN 200
#define OPTION_TEXT_MAX_LEN 80

#define USER_MAX_LEN 15
#define PASS_MAX_LEN 15
#define CAND_ID_MAX_LEN 10
#define CAND_NAME_MAX_LEN 25
#define UID_NO_MAX_LEN 15
#define ADD_MAX_LEN 80
#define QUAL_MAX_LEN 50

#define DATE_MAX_LEN 15
#define ATTENDED_MAX_LEN 4
#define TOPIC_MARKS_MAX_LEN 4

/********************************************************************************
 *                             FUNCTIONS
 ********************************************************************************/

extern void create_candidate_node(CandidateNode **, char *); /* local to candidate.c */
extern void create_question_node(QuestionNode **, char *);   /* local to question.c*/
extern void create_topic_node(TopicNode **, char *);         /* local to topic.c*/
extern void create_interview_node(InterviewNode **, char *); /* local to interview.c*/

/* question.c */
extern unsigned int read_question_data(QuestionNode **);
extern void display_question_data(QuestionNode *);
extern void free_question_mem(QuestionNode **);
extern int save_questions(QuestionNode **);

/* candidate.c */
extern void register_candidates(CandidateNode **);
extern unsigned int read_candidate_data(CandidateNode **);
extern void display_candidate_data(CandidateNode *);
extern void free_candidate_mem(CandidateNode **);
extern void modify_candidate(CandidateNode **candidate_list_head);
extern int check_marks(int candidate_id);
extern int candidate_login(CandidateNode *);
extern int save_candidates(CandidateNode **);
extern int appear_for_test(int candidate_id);
extern int print_questions(int candidate_id,int test_id,int n);
extern int candidate_check(int cand_id,int n);
extern int topic_marks(int cand_id, int n,int test_id);
extern int calculate(int candidate_id,int n,int test_id);


/* check and display */
extern int candidate_id_check(int cand_id);
extern int results_check(int cand_id);
extern int topic_marks_calculation(int cand_id, int n);
extern int calculate_marks(void);
extern int display_marks(void);

/* topic.c */
extern unsigned int read_topic_data(TopicNode **);
extern void display_topic_data(TopicNode *);
extern void free_topic_mem(TopicNode **);
extern int save_topics(TopicNode **);

/* interview.c */
extern unsigned int read_interview_data(InterviewNode **);
extern void display_interview_data(InterviewNode *);
extern void free_interview_mem(InterviewNode **);
extern int save_interviews(InterviewNode **);

/* admin.c */
extern int admin_login(void);
extern void manage_topics(TopicNode **);
extern void manage_questions(QuestionNode **);
extern void manage_candidates(CandidateNode **);
extern void manage_interviews(InterviewNode **);
extern void manage_tests(TestNode **, TestNode **);
extern void question_generation(QuestionGenNode **);
extern void free_test(TestNode **,TestNode**);
extern void free_questiongen(QuestionGenNode **);

/* test.c */
extern void display_test_data(TestNode **, TestNode **);

#endif // end __UTILITY_H_