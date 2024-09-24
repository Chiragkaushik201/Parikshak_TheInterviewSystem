# ********************** Compiler *************************** # 
CC       = gcc
CFLAGS   = -c -g -Wall -Werror -Wno-unused-variable

# ************************ Paths *************************** # 
OBJ	     = ../obj
SRC	     = ../src
INC	     = ../inc
BIN	     = ../bin
MAKE	 = ../make
REP      = ../report

# ******************* Additional flags ************************ # 
# path
INCDIR   = -I $(INC)

# valgrind
VALFLAG  = --tool=memcheck --show-reachable=yes --leak-check=full \
	--verbose --log-file=valgrind_report.txt

# splint
LINTFLAG = -predboolint -nullstate -compdestroy

#Gcov
GFLAGS   = -fprofile-arcs -ftest-coverage
COVG	 = --coverage

# *********************** File names *************************** # 
UTIL     = utility
MAIN     = main
ADMIN    = admin
CAND	 = candidate
QUES     = question
TOPIC    = topic
INVEW    = interview

# ********************** Link all files ************************* # 
all : $(OBJ)/$(MAIN).o $(OBJ)/$(ADMIN).o $(OBJ)/$(CAND).o \
	$(OBJ)/$(QUES).o $(OBJ)/$(TOPIC).o $(OBJ)/$(INVEW).o

	$(CC) $(COVG) $(OBJ)/$(MAIN).o $(OBJ)/$(ADMIN).o $(OBJ)/$(CAND).o \
	$(OBJ)/$(QUES).o $(OBJ)/$(TOPIC).o $(OBJ)/$(INVEW).o -o $(MAIN)
	mv $(MAIN) $(BIN)/

# ********************** Create main.o *************************** # 
$(OBJ)/$(MAIN).o : $(SRC)/$(MAIN).c $(INC)/$(UTIL).h
	$(CC) $(GFLAGS) $(CFLAGS) $(SRC)/$(MAIN).c $(INCDIR)
	mv $(MAIN).o $(OBJ)
	mv $(MAIN).gcno $(BIN)/

# ********************** Create admin.o *************************** # 
$(OBJ)/$(ADMIN).o : $(SRC)/$(ADMIN).c $(INC)/$(UTIL).h
	$(CC) $(GFLAGS) $(CFLAGS) $(SRC)/$(ADMIN).c $(INCDIR)
	mv $(ADMIN).o $(OBJ)
	mv $(ADMIN).gcno $(BIN)/

# ********************** Create candidate.o *************************** # 
$(OBJ)/$(CAND).o : $(SRC)/$(CAND).c $(INC)/$(UTIL).h
	$(CC) $(GFLAGS) $(CFLAGS) $(SRC)/$(CAND).c $(INCDIR)
	mv $(CAND).o $(OBJ)
	mv $(CAND).gcno $(BIN)/

# ********************** Create question.o *************************** # 
$(OBJ)/$(QUES).o : $(SRC)/$(QUES).c $(INC)/$(UTIL).h
	$(CC) $(GFLAGS) $(CFLAGS) $(SRC)/$(QUES).c $(INCDIR)
	mv $(QUES).o $(OBJ)
	mv $(QUES).gcno $(BIN)/

# ********************** Create topic.o *************************** # 
$(OBJ)/$(TOPIC).o : $(SRC)/$(TOPIC).c $(INC)/$(UTIL).h
	$(CC) $(GFLAGS) $(CFLAGS) $(SRC)/$(TOPIC).c $(INCDIR)
	mv $(TOPIC).o $(OBJ)
	mv $(TOPIC).gcno $(BIN)/

# ********************** Create interview.o *************************** # 
$(OBJ)/$(INVEW).o : $(SRC)/$(INVEW).c $(INC)/$(UTIL).h
	$(CC) $(GFLAGS) $(CFLAGS) $(SRC)/$(INVEW).c $(INCDIR)
	mv $(INVEW).o $(OBJ)
	mv $(INVEW).gcno $(BIN)/

# ********************** Run valgrind *************************** # 
valgrind: $(BIN)/$(MAIN)
	valgrind $(VALFLAG) $(BIN)/$(MAIN)
	mv valgrind_report.txt $(REP)/

# ********************** Run splint *************************** # 
# splint for main.c
splint_main: $(SRC)/$(MAIN).c $(INC)/$(UTIL).h
	splint $(INCDIR) $(LINTFLAG) $(SRC)/$(MAIN).c  > $(REP)/splint_main.txt

# splint for admin.c
splint_admin: $(SRC)/$(ADMIN).c $(INC)/$(UTIL).h
	splint $(INCDIR) $(LINTFLAG) $(SRC)/$(ADMIN).c  > $(REP)/splint_admin.txt

# splint for candidate.c
splint_candidate: $(SRC)/$(CAND).c $(INC)/$(UTIL).h
	splint $(INCDIR) $(LINTFLAG) $(SRC)/$(CAND).c  > $(REP)/splint_candidate.txt

# splint for question.c
splint_question: $(SRC)/$(QUES).c $(INC)/$(UTIL).h
	splint $(INCDIR) $(LINTFLAG) $(SRC)/$(QUES).c  > $(REP)/splint_question.txt

# splint for interview.c
splint_interview: $(SRC)/$(INVEW).c $(INC)/$(UTIL).h
	splint $(INCDIR) $(LINTFLAG) $(SRC)/$(INVEW).c  > $(REP)/splint_interview.txt

# splint for topic.c
splint_topic: $(SRC)/$(TOPIC).c $(INC)/$(UTIL).h
	splint $(INCDIR) $(LINTFLAG) $(SRC)/$(TOPIC).c  > $(REP)/splint_topic.txt

# ********************** Run Gcov *************************** # 
gcov: $(BIN)/$(MAIN).gcno $(BIN)/$(ADMIN).gcno $(BIN)/$(CAND).gcno \
	$(BIN)/$(INVEW).gcno $(BIN)/$(QUES).gcno $(BIN)/$(TOPIC).gcno \
	$(MAIN).gcda $(ADMIN).gcda $(CAND).gcda $(INVEW).gcda $(QUES).gcda $(TOPIC).gcda \

	mv ./*.gcda $(BIN)/	  # move all gcda to bin
	gcov $(BIN)/*.gcno    # run all bin/*.gcno
	mv *.c.gcov $(REP)/   # move all report generated to rep

# ********************** Run Gprof *************************** # 
gprof: $(SRC)/$(MAIN).c $(SRC)/$(ADMIN).c $(SRC)/$(CAND).c \
	$(SRC)/$(INVEW).c $(SRC)/$(QUES).c $(SRC)/$(TOPIC).c $(INC)/$(UTIL).h

	$(CC) -Wall -pg $(SRC)/*.c $(INCDIR) -o gprof_out
	./gprof_out

	mv gmon.out $(BIN)/
	gprof gprof_out $(BIN)/gmon.out > $(MAKE)/gprof_report.txt # run gprof and redirect output
	mv $(MAKE)/gprof_report.txt $(REP)/		# move gprof report to report/
	rm -f gprof_out

# ********************** Run program *************************** # 
run: $(BIN)/$(MAIN)
	$(BIN)/$(MAIN)

# ********************** Delete obj files *************************** # 
clean:
	rm -f $(OBJ)/*
	rm -f $(BIN)/*
	rm -f $(MAKE)/gprof_out
	rm -f $(MAKE)/*.gcda
	rm -f $(REP)/*
