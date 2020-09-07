Roll Number: BT17CSE026


Language Used: C/C++

Initially I though this question is similar to a number game I saw in a youtube video by a famous (education/knowledge/paradox/quiz/mathematics) related youtube channel VSauce2.0 (https://www.youtube.com/watch?v=dUXW3Kh_kxo). But after few minutes of analysis it was pretty clear that the problem is different. The very first thing came to mind was recurence relation F(p1,p2,move) = OR(F(p1-1,p2,!move),F(p1,p2-1,!move)) with base, this can pretty much solve the problem, more over we can construct a table because this problem has overlapping subproblems and in this way a table is contructed, tough in the code I have simple contructed the table for 10x10 for which I preety muc knew the pattern but for generalised chase the above given F works well.
