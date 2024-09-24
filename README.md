<h1 align="center"> Parikshak - Interview System </h1>

## List of commands:

#### All commands given below are to be run from make directory

- Create obj file for main
  `make ../obj/main.o`

<br/>

- Create obj file for admin
  `make ../obj/admin.o`

<br/>

- Create obj file for candidate
  `make ../obj/candidate.o`

<br/>

- Link all files
  `make all` or `make`

<br/>

- Run splint on main.c
  `make splint_main`

<br/>

- Run splint on admin.c
  `make splint_admin`

<br/>

- Run splint on candidate.c
  `make splint_candidate`

<br/>

- Run <b>main.out</b>
  `make run`

<br/>

- Delete all <b>.o</b> and <b>.out</b> files
  `make clean`

<br/>

- Run valgrind on <b>main.out</b> file
  `make valgrind`
