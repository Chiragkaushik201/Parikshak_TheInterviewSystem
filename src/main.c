/********************************************************************************
 *
 *     FILENAME           :    main.c
 *
 *     DESCRIPTION        :    An application for interview analysis - Parikshak.
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
 *     FUNCTION NAME    :   main
 *
 *     DESCRIPTION      :   Driver function for the the program
 *
 *     PARAMETERS       :   None
 *
 *     RETURNS          :   None
 *******************************************************************************/
int main()
{
    /* Local variables */
    int main_menu_choice = 0,  /* Integer variable to store main menu choice */
        admin_choice = 0,      /* Integer variable to store admin choice */
        candidate_choice = 0,  /* Integer variable to store candidate choice */
        main_loop_cond = TRUE, /* Loop control condition for main menu */
        admn_loop_cond = TRUE, /* Loop control condition for admin menu */
        cand_loop_cond = TRUE; /* Loop control condition for candidate menu */

    TopicNode *topic_list_head = NULL;          /* Initialize Topic Node */
    QuestionNode *question_list_head = NULL;    /* Initialize Question Node */
    CandidateNode *candidate_list_head = NULL;  /* Initialize Candidate Node */
    InterviewNode *interview_list_head = NULL;  /* Initialize Interview Node */
    TestNode *test_list_head = NULL;            /* Initialize Head of test Node */
    TestNode *test_list_tail = NULL;            /* Initialize Tail of Test Node */
    QuestionGenNode *question_data_head = NULL; /* Initialize head of QuestionGenNode */

    read_candidate_data(&candidate_list_head);

    /****************************** Program starts here ***************************/
    while (main_loop_cond)
    {
        /********************* Main Menu **********************/
        system("clear");
        printf("\n************** Main Menu **************\n");
        printf("\n1. Login as admin");
        printf("\n2. Login as Candidate");
        printf("\n3. Register as Candidate");
        printf("\n0. Exit\n");

        printf("\nPlease enter your choice: ");
        scanf("%d", &main_menu_choice);
        getchar();

        switch (main_menu_choice)
        {
        /********************* Quit application **********************/
        case 0:
        {
            printf("\nThanks for using this application!\n");
            main_loop_cond = FALSE;
        }
        break;

        /********************* If main menu choice is Admin **********************/
        case 1:
        {
            /**************** Admin Login ***************** */
            admn_loop_cond = admin_login();
            if (admn_loop_cond == EXIT_FAILURE)
            {
                printf("\nLogin Failed!\n");
                admn_loop_cond = FALSE;
                printf("\nPress enter to continue... ");
                getchar();
            }
            else
            {
                printf("\nLogin Successful!\n");
                admn_loop_cond = TRUE;
            }

            while (admn_loop_cond)
            {
                printf("\n************** Admin Menu **************\n");
                printf("\n1. Manage topics");
                printf("\n2. Manage questions:");
                printf("\n3. Manage Tests");
                printf("\n4. Generate questions for test:");
                printf("\n5. Manage candidates");
                printf("\n6. Manage interviews:");
                printf("\n7. Calculate marks:");
                printf("\n8. Display marks:");
                printf("\n0. Back to Main menu\n");

                printf("\nPlease enter your choice: ");
                scanf("%d", &admin_choice);
                getchar();

                switch (admin_choice)
                {
                    while (TRUE)
                    {
                    case 0: /* Back to main menu */
                    {
                        printf("\nGoing back to main menu...\n");
                        admn_loop_cond = FALSE;
                    } /* end Back to main menu */
                    break;

                    case 1: /* Manage topics */
                    {
                        manage_topics(&topic_list_head);
                    }
                    break; /* end Manage topics */

                    case 2: /* Manage questions */
                    {
                        manage_questions(&question_list_head);
                    }
                    break; /* end Manage questions */

                    case 3: /* Manage tests */
                    {
                        manage_tests(&test_list_head, &test_list_tail);
                    }
                    break; /* end Manage tests */

                    case 4: /* Generate questions for test */
                    {
                        question_generation(&question_data_head);
                    }
                    break; /* end Generate questions for test */

                    case 5: /* Manage candidates */
                    {
                        manage_candidates(&candidate_list_head);
                    }
                    break; /* end Manage candidates */

                    case 6: /* Manage interviews */
                    {
                        manage_interviews(&interview_list_head);
                    }
                    break; /* Manage interviews */

                    case 7: /* Calculate marks */
                    {
                        int calculate_marks_flag = calculate_marks();
                        if (calculate_marks_flag == EXIT_FAILURE)
                        {
                            printf("\nCalculation of Marks Failed!\n");
                        }
                        else
                        {
                            printf("\nCalculated Marks Successfully!\n");
                        }
                    }
                    break; /* end Calculate marks */

                    case 8: /* Display marks */
                    {
                        display_marks();
                    }
                    break; /* end Display marks */

                    default:
                    {
                        printf("\nInvalid input!\n");
                        printf("\nPress enter to continue... ");
                        getchar();
                    }
                    break;
                    }
                }
            }
        }
        break; /* end main menu Admin choice */

        /********************* If main menu choice is Candidate **********************/
        case 2:
        {
            /**************** Candidate Login ***************** */
            int candidate_id = candidate_login(candidate_list_head);
            if (candidate_id == EXIT_FAILURE)
            {
                printf("\nLogin Failed!\n");
                cand_loop_cond = FALSE;
                printf("\nPress enter to continue... ");
                getchar();
            }
            else if (candidate_id != EXIT_FAILURE)
            {
                printf("\nLogin Successful!\n");
                cand_loop_cond = TRUE;
            }

            while (cand_loop_cond)
            {
                printf("\n************** Candidate Menu **************\n");
                printf("\n 1. Manage Profile");
                printf("\n 2. Appear for test");
                printf("\n 3. Check marks");
                printf("\n 0. Back to main menu\n");

                printf("\nPlease enter your choice: ");
                scanf("%d", &candidate_choice);
                getchar();

                switch (candidate_choice)
                {
                case 0: /* Back to main menu */
                {
                    printf("\nGoing back to main menu...\n");
                    cand_loop_cond = FALSE;
                } /* end Back to main menu */
                break;

                case 1: /* Manage profile */
                {
                    modify_candidate(&candidate_list_head);
                }
                break; /* end Manage profile */

                case 2: /* Appear for test */
                {
                    appear_for_test(candidate_id);
                }
                break; /* end Appear for test */

                case 3: /* Check marks */
                {
                    check_marks(candidate_id);
                }
                break; /* end Check marks */

                default:
                {
                    printf("\nInvalid input!\n");
                    printf("\nPress enter to continue... ");
                    getchar();
                }
                break;
                }
            }
        }
        break; /* end Candidate choice */

        /****************** If main menu choice is Register candidate *******************/
        case 3:
        {
            printf("\n************** Register Candidate **************");
            register_candidates(&candidate_list_head);
            printf("\nPress enter to continue... ");
            getchar();
        }
        break; /* end Register candidate */

        /****************** Invalid choice input *******************/
        default:
        {
            printf("\nInvalid input!\n");
            printf("\nPress enter to continue... ");
            getchar();
        }
        break; /* end Invalid choice input */
        }
    }

    /* Free dynamically allocated memory */
    free_candidate_mem(&candidate_list_head);
    free_question_mem(&question_list_head);
    free_topic_mem(&topic_list_head);
    free_interview_mem(&interview_list_head);
    free_test(&test_list_head, &test_list_tail);
    free_questiongen(&question_data_head);

    return EXIT_SUCCESS;
}