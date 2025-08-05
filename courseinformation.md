# Course Description for Computer Systems fall 2025/26

CompSys is giving a general introduction to computer systems. You will learn how computers works at a basic but fundamental level, how this reflects to the programs that you write, and understand the performance characteristic for these. We will cover topics from Machine architecture, Operating Systems, Computer Networks, and basic IT-Security. We will also introduce you to the C programming language, which will be used throughout the course.

Make sure that you read all the following carefully and be aware of updates.

### Maintain your programming skills!
CompSys have gotten a reputation of being both a hard and informative course. As you can see below (and the course description), we will cover a lot of different topics that conceptually are very different, in a short time. It is therefore important that you are ready for the course when we start in September, avoiding to fall behind during the first weeks.

We do not ask you to read ahead in the material. Also do not start to learn C, which we will use in CompSys. However, most of you are still inexperienced programmers and CompSys in very heavy on programming and program understanding. You need to think of programming as a _craft_, like playing an instrument. You have during the first year learned the basics of how it works. But if you lay it away over the summer (do not program for two months) you will lose much of these skills that you have gain over the first year. 

You can find resources at last years [DIKU Summer of Programming](https://github.com/diku-summer-programming/fun). You can use it to get inspiration for your ideas.


### Github as course page
Most material will be posted to Github in this repository. We recommend that you clone it to your machine and that you follow the updates that are made, by reading the log.


## Short on Course Structure
In the following is given a short overall description of the course. More details can be found further down.

### Teaching Material
We will use material from the following sources:

 * [COD] Computer Organization and Design, RISC-V Edition: The Hardware Software Interface, David A. Hennessy and John L. Patterson, 2nd edition, Morgan Kaufmann, ISBN: 978-0128203316
 * [OSTEP] Operating Systems: Three Easy Pieces, Remzi H. Arpaci-Dusseau and Andrea C. Arpaci-Dusseau. https://pages.cs.wisc.edu/~remzi/OSTEP/ 
 * [BOH] Randal E. Bryant and David R. O'Hallaron. Computer Systems: A Programmers Perspective, 3rd and global edition (We will only use small sections of this book, provided as a pdf with the resources directory.)
 * [KR] Computer Networking: A Top-Down Approach, James F. Kurose and Keith W. Ross, Pearson, 8th and Global Edition, 2021, ISBN 13: 978-0135928608.
 * [JG] Modern C, Jens Gustedt, Oct. 10, 2019, http://modernc.gforge.inria.fr/.

COD and KR will be available at Academic Books at Biocenteret:

  https://www.academicbooks.dk/da/pensumlister


### General outline
The general outline of CompSys will be the following:

 * Week 36-37: Introduction to the abstract computing machine, C programming and data representation
 * Week 38: Memory hierarchy and caching
 * Week 39-41: Operating systems
 * Week 42: Fall break
 * Week 43-45: Computer networks - application and transport layer
 * Week 46: No activities (reexam week)
 * Week 47: Computer networks - security and efficiency
 * Week 48-51: Machine architecture and assembler programming
 * Week 52-1: Christmas vacation
 * Week 2: Computer networks and security - network and link layer
 * Week 3: Exam preparation and question hour
 * Week 4: Exam

### Teaching in Block 1 exam period
Be aware that CompSys is a semester course, which means that we will be teaching (including having normal exercise and assignments) throughout the exam period (weeks 44 and 45) of Block 1.

### Exam
The exam is a written 4-hour open-book exam and will be held on Wednesday Jan 21st. Course syllabus is all reading material, including the assignments.
We will later publish example sets based on the previous exam iteration and further details on the exam procedure. It will be possible to get limited feedback on the exam performance afterwards.

### Exercises and Cafées
The course will have both class exercises and open café sessions. The class exercises will fill focus on smaller exercises that will provide practice in using the material presented in the lectures and videos. They are perhaps the main learning point for the course as you are expected to be able to practice and apply the theories and principles explained through the course. 

The café sessions will, on the other hand, mainly be your possibility to get help with the assignments. However, it will also be possible to ask about exercises and other material. Also teachers will (mainly on Wednesdays) also be presents, so you can ask anything in an informal setting.

### Assignments and qualification for the exam
To qualify for the exam, a minimum number of points must be gained through the assignments. On purpose, to achieve this limit requires a basic understanding of the programming tasks of the assignments (including presentation of this though test and a report), but not a full understanding.

It is also important to note, that the main purpose of the assignment is _not_ to prepare you for the exam; that is what the theory parts of the exercise classes are for. The assignments will focus on larger implementations and the practical learning goals of the course. Some questions in the exam will relate to the assignments, but qualifying of the exam (and even fully solving the assignments) will not be enough preparation to pass the exam. You need to make the exercises and the best way is to come to the exercise classes.

## Manning

Teachers:

 * Michael Kirkedal Thomsen (course organiser)
 * David Marchant
 * Finn Schirmer Andersen

TAs:

  * Carl August Gjerris Hartmann
  * Emil Viggo Dalsgaard 
  * Mads Presfeldt
  * Malte Emil Wechter 
  * Philip Shun Buenaventura Jensen
  * Tobias Andersen 


## Lectures

### Block 1
 * Mondays at 15:15-17:00 in DIKU, Store UP1
 * Wednesdays at 15:15-17:00 in DIKU, Store UP1

### Block 2
 * TBD


## Exercise Classes
Exercise clases will introduce many of the smaller concepts and techniques we will be exploring in this course. They are mostly smaller progamming and theory tasks that prepare you for the tasks in the assignments and the exam. 

 * Mondays 15:15-17:00
 * Wednesdays 13:15-15:00

 Please disregard the location stated at skema.ku.dk or in the myUCPH app. Please refer to the plan below:

<!--See [skema.ku.dk](https://skema.ku.dk/tt/tt.asp?SDB=KU2425&language=DK&folder=Reporting&style=textspreadsheet&type=module&idtype=id&id=125310&weeks=6-16&days=1-5&periods=1-68&width=0&height=0&template=SWSCUST2+module+textspreadsheet) for Block 1 room details.

 -->
#### Block 1
  * Class 1: Benjamin
    * Monday: NBB 2.3.I.164
    * Wednesday: NBB 2.3.I.164
  * Class 2: Christian and Riasat
    * Monday: Biocenter 4-0-02
    * Wednesday: DIKU 1-0-34
  * Class 3: Emil
    * Monday: NBB 2.3.H.142
    * Wednesday: NBB 2.2.I.158
  * Class 4: Jóhann
    * Monday: Biocenter 4-0-02 - Sharing room with Christian and Riasat
    * Wednesday: DIKU 1-0-22 
  * Class 5: Lea and Tobias A
    * Monday: NBB 2.1.H.142 and NBB 2.0.G.064/070 (if needed)
    * Wednesday: NBB 2.1.H.142
  * Class 6: Malte
    * Monday: NBB 2.0.G.064/070
    * Wednesday: NBB 2.2.H.142
  * Class 7: Tobias NH
    * Monday: NBB 2.0.G.064/070
    * Wednesday: NBB 2.3.H.142


Make sure that you and your study group joins a class in the Absalon Course Room -> People -> Class


#### Block 2

 * Class 1: Benjamin
   * Monday: NBB 2.0.G.064/070
   * Wednesday: NBB 2.0.G.064/070
 * Class 2: Christian and Riasat
   * Monday: NBB 2.3.H.142
   * Wednesday: NBB 2.3.H.142
 * Class 3: Emil
   * Monday: NBB 2.3.I.164
   * Wednesday: NBB 2.3.I.164
 * Class 4: Lea
   * Monday: NBB 2.0.G.064/070
   * Wednesday: NBB 2.0.G.064/070
 * Class 5: Tobias A
   * Monday: NBB 2.0.G.064/070
   * Wednesday: NBB 2.0.G.064/070
 * Class 6: Malte
   * Monday: NBB 2.3.H.142
   * Wednesday: NBB 2.3.H.142
 * Class 7: Tobias NH
   * Monday: NBB 2.3.I.164
   * Wednesday: NBB 2.3.I.164

### Room details
Map of Nørre Campus:
https://nexs.ku.dk/kontakt/findvej/kort_norre-campus/

 * Biocenter, Ole Maaløes Vej 5, https://www.biocenter.ku.dk/kort/
 * DIKU, No further explanation needed
 * NBB, Niels Bohr Building, Jagtvej 155 (other side of Jagtvej)
 * HCØ, C103 is first floor in building 2
 * NEXS Aud Syd + Nord is at Nørre Alle 51 (almost at the Royal Library)


## Cafées (expected times)
Cafées will be manned with either 2, 3 or 4 TAs. 

 * Wednesdays 15:15-17:00
   * This sessions have a café structure and are dedicated to help with assignments and other open questions.
 * Fridays 14:15-16:00
   * TA organised café classes for help with assignments and exercises.

### Rooms

#### Block 1
In the overflow you are welcome to sit and work. You can come to the other rooms to ask for help.

Wednesday: 
  * NBB 2.3.I.164
  * NBB 2.3.H.142
  * NBB 2.2.H.142 -- Only manned in weeks with assignment deadlines; otherwise overflow room.
  * NBB 2.1.H.142 -- Overflow room

Friday: 
  * DIKU 1-0-30
  * DIKU 1-0-37
  * DIKU 1-0-26 -- Only manned in weeks with assignment deadlines; otherwise overflow room.
  * DIKU 1-0-14 -- Overflow room.

#### Block 2

Wednesday (expect Week 48):
  * NBB 2.3.H.142
  * NBB 2.3.I.164
  * NBB 2.2.H.142 -- Only in weeks with assignment deadlines.

Wednesday (Week 48, only):
  * NBB 2.0.G.064/070
  * NBB 2.2.H.142

Friday: 
  * NBB 2.2.H.142
  * NBB 2.3.H.142
  * NBB 2.1.H.142 -- Only in weeks with assignment deadlines.
  * NBB 2.1.I.156 -- Overflow room.



## Study group formation
Online on Absalon or Discord.


## Assignment

There are 6 assignment in total during the course with deadline roughly every two to three weeks. The assignments will be graded with points from 0 to 6 depending on the assignment. It is _not_ possible to re-hand-in any of the assignments. The details will be the following:


| Title                                         | Expected deadline         | Topic | Maximum points |
| --------------------------------------------- | ------------------------- | ----- | -------------- |
| A0: Quicksort in RISC-V assembly              | Sunday Week 38 @ 16:00    | None  |       4 points |
| A1: Dynamic memory and caching                | Sunday Week 40 @ 16:00    | OS    |       4 points |
| A2: Concurrency                               | Sunday Week 43 @ 16:00    | OS    |       4 points |
| A3: Client network distribution and security  | Sunday Week 47 @ 16:00    | CN    |       6 points |
| A4: Architecture.                             | Sunday Week 50 @ 16:00    | Arc   |       6 points |
| A5: Theoretical catch up                      | Wednesday Week 02 @ 20:00 | None  |       2 points |

Assignments are made to be solved in groups of preferably three students, but groups of two active students will also do. We strongly encourage not to work alone. Groups cannot be larger than three students. Each group must make their own solutions and must share implementations and report with other. You are allowed to discuss material and ideas.

The final assignment will only be theoretical.

### Feedback
Feedback to assignments will be given by TAs on the course; we try to match with the TA of the exercise class. Feedback will focus on what could be approved in the assignment relating to both technical implementations, and report structure and material. The feedback may thus be useful for later assignment. The feedbeck will not be complete, so it can be useful also to talk with your TA at the exercises. Feedback will not give a direct justification of the evaluation in number of points.

Correction of submissions will be available after about two weeks.

### Hand-in
We will use the group hand-ins on Absalon.

If you need to update any part of your submission on Absalon (e.g. the source code or the report), you must resubmit the entire work. That include the unchanged work. We will only assess the latest submission.

When your TA has corrected your submission all members of the group will be given the evaluation (comments and points). If some of your group members have gotten the evaluation, but you are missing, please, contact the course responsible. It is there very important that _your report always contain both names and KU-ids of all group members_, as the report is then used for resolution.

## Exam qualification

To qualify for the exam you are required to achieve at least 50 % of the total number of points in the assignments. That is 13 out of the total 26 points.

Furthermore, it is required that you show a reasonable understanding of all parts (ARK, OS, CN) of the course. This is firstly interpreted as achieving points at least 40 % points in each the of topics. To optimise your understanding of the course, and since all assignments are in the syllabus, we encourage you to work with and hand in all sets.

Mapping of topics to assignments:

|                      | A0 | A1 | A2 | A3 | A4 | A5 |
| ---------------------|----|----|----|----|----|----|
| Operating System     |    |  X |  X |    |    |    |
| Computer network     |    |    |    |  X |    |    |
| Machine architecture |    |    |    |    |  X |    |

The rule about 40 % of points for assignments in each topic, is included to make sure that you will uphold the learning goals for the course. We will teach you about many different abstractions and you should learn something about all of them. Without this rule you could attend the exam without e.g. learning anything about computer networks by getting enough points in the beginning of the course. The 40 % is chosen as it should be "easier" than the general rule of 50 %; it will therefore be:

  * Operating System (A1+A2): 3 of the possible 8 points.
  * Computer network (A3): 2 of the possible 6 points.
  * Machine architecture (A4): 2 of the possible 6 points.

If you qualified for the exam the previous year, you can take the exam as a re-exam. If you qualified earlier years, then contact the course organiser.

